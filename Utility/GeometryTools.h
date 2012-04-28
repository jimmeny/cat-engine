/***************************************************
Copyright (c) 2009 IvanJ.
All rights reserved.

File:    GeometryTools.h
Purpose: 
Version: 0.1

****************************************************/

#pragma once
#include "Utility/CommonDef.h"
#include <algorithm>
#include <limits>

#define MIN_DISTANCE 0.0000000001
#define DISTANCE_RATE 31.0

const double INF = 1E200;
const double EP = 1E-16;
const double PI = 3.14159265;

enum LinkDirection
{
	DIR_POS = 2,
	DIR_NAG = 3,
	DIR_DOUBLE = 1
};

//����Geoģ��ʹ�õĵ����
struct Point
{
	double x;
	double y;
	Point(){};
	Point(double x, double y)
	{
		this->x = x;
		this->y = y;
	}
	bool operator==(const Point &t) const
	{
		return(x == t.x && y == t.y);
	}
	bool operator!=(const Point &t) const
	{
		return(x != t.x || y != t.y);
	}
};

struct LINE           // ֱ�ߵĽ������� a*x+b*y+c=0  Ϊͳһ��ʾ��Լ�� a >= 0
{
	double a;
	double b;
	double c; 
	LINE(double d1=1, double d2=-1, double d3=0) {a=d1; b=d2; c=d3;}
};

class CRect
{
public:
	double dMinx;
	double dMiny;
	double dMaxx;
	double dMaxy;

	CRect()
	{
		dMinx = 999;
		dMiny = 999;
		dMaxx = 0;
		dMaxy = 0;
	}

	const CRect& operator=( const Point& pt )
	{
		dMinx = pt.x;
		dMaxx = pt.x;
		dMiny = pt.y;
		dMaxy = pt.y;
		return( *this ); 
	}

	const CRect& operator+=( const Point& pt )
	{
		dMinx = min(dMinx , pt.x);
		dMiny = min(dMiny , pt.y);
		dMaxx = max(dMaxx , pt.x);
		dMaxy = max(dMaxy , pt.y);
		return (*this);
	}

	//��ptΪ���ĵ�,����һ���ıߵ���Ĵ�ֱ���붼��dDistance��������
	void CreateRect(Point& pt, double dDistance)
	{
		double dRate = dDistance / DISTANCE_RATE / 3600.0;
		dMinx = pt.x - dRate;
		dMiny = pt.y - dRate;
		dMaxx = pt.x + dRate;
		dMaxy = pt.y + dRate;
	}

	//�ж����������Ƿ�����
	bool IsRectJoined( const CRect& rect ) const
	{
		if ( dMaxx <= rect.dMinx || dMinx >= rect.dMaxx )
		{
			return false;
		}
		else
		{
			if ( dMaxy <= rect.dMiny || dMiny >= rect.dMaxy )
			{
				return false;
			}
		}
		return true;
	}

	//�ж��������εĹ�ϵ
	RectToRectRelation RelationOfTwoRect(const CRect& rect)
	{
		if ( FLOAT_EQUAL( dMaxx, rect.dMaxx ) && FLOAT_EQUAL( dMinx, rect.dMinx ) 
			&& FLOAT_EQUAL( dMaxy, rect.dMaxy ) && FLOAT_EQUAL( dMiny, rect.dMiny ) )
		{
			return RRF_EQUAL;
		}
		else if ( IsRectJoined( rect ) )
		{
			if ( dMaxx <= rect.dMaxx && dMinx >= rect.dMinx 
				&& dMaxy <= rect.dMaxy && dMiny >= rect.dMiny ) 
			{
				return RRF_INDEST;//this������Rect
			}
			else if ( rect.dMaxx <= dMaxx && rect.dMinx >= dMinx 
				&& rect.dMaxy <= dMaxy && rect.dMiny >= dMiny )
			{
				return RRF_INSRC;//Rect������this
			}
			else
			{
				return RRF_INTERSECT;//this��Rect�ཻ
			}
		}
		else
		{
			return RRF_DISCRETE;//this��Rect����
		}
	}
};

class GeometryTools
{
public:
	typedef vector<Point> Polyline;
	//�����߶ϵ�λ�ù�ϵ
	enum SectionPos
	{
		NoSection = -1,		//����
		SectionInLine = 0,	//�����߶��м�
		SectionIsStart = 1,	//�����߶����
		SectionIsEnd = 2		//�����߶��յ�
	};

	//��������λ�ù�ϵ
	enum PtToPolygon
	{
		PtOutsidePolygon = -1,	//���ڶ������
		PtOnBorder       = 1,		//���ڶ���α���
		PtInPolygon      = 2		//���ڶ�����ڲ�
	};

	enum PtToRectFlag//����RECT��λ�ù�ϵ���
	{
		PRF_OUTRECT = 0,	//��Ŀ��RECT��
		PRF_INRECT = 1,		//��Ŀ��RECT��
		PRF_ONBORDER = 2	//��Ŀ��RECT�߽�
	};

public:
	GeometryTools(){};
	~GeometryTools(){};
public:
	//��ȡ�߶���X���᷽��ļн�
	static double GetLineAngle( const Point& ptStart, const Point& ptEnd )
	{
		double dAngle = 0;
		if ( FLOAT_EQUAL( ptStart.x, ptEnd.x ) )  //��ֱ����
		{
			if ( ptStart.y > ptEnd.y )//����
			{
				dAngle = 90.0;
			}
			else//����
			{
				dAngle = 270.0;
			}
		}
		else if ( FLOAT_EQUAL( ptStart.y, ptEnd.y ) )//ˮƽ����
		{
			if ( ptEnd.x > ptStart.x )//����
			{
				dAngle = 0.0;
			}
			else//����
			{
				dAngle = 180.0;
			}
		}
		else
		{
			dAngle = ( atan2( ( ptStart.y - ptEnd.y ) * 1.0, ptStart.x - ptEnd.x ) * 180 ) / 3.14159265;

			if ( ptStart.y < ptEnd.y )//����������������
			{
				dAngle += 360;
			}
		}
		return( dAngle );
	}

	//��ȡ�����ļ��ξ���
	static double GetTwoPointDistance( const Point& pt1, const Point& pt2 )
	{
		double d = _hypot( pt1.x - pt2.x, pt1.y - pt2.y );
		return(d);
	}

	//��ȡ�㵽�߶εľ���
	static double GetDistancePointToLine( const Point& pt, const Point& ptStart, 
		const Point& ptEnd, double dMinDistance = MIN_DISTANCE )
	{
		double dAngle1 = GetLineAngle( pt, ptStart );
		double dAngle2 = GetLineAngle( ptEnd, ptStart );
		double dAngle3 = GetLineAngle( pt, ptEnd );
		double dAngle4 = GetLineAngle( ptStart, ptEnd );

		double dA = GetTwoPointDistance( pt, ptStart );
		double dB = GetTwoPointDistance( pt, ptEnd );
		double dC = GetTwoPointDistance( ptStart, ptEnd );

		double dDistance = 0;
		if ( ( fabs( dAngle1 - dAngle2 ) >= 90.0 ) || ( fabs( dAngle3 - dAngle4 ) >= 90.0 ) )
		{
			dDistance = min( dA, dB );
		}
		else if ( FLOAT_EQUAL( dC, 0.0 ) )
		{
			assert( FLOAT_EQUAL( dA, dB ) );
			dDistance = dA;
		}
		else if ( ( dA <= dMinDistance ) || ( dB <= dMinDistance ) )
		{
			dDistance = dMinDistance;
		}    
		else if ( fabs( max( dA, dB ) - min( dA, dB ) - dC ) <= dMinDistance )
		{
			dDistance = min( dA, dB );
		}
		else
		{
			double dS = ( dA + dB + dC ) / 2;
			double dAreaABC = sqrt( dS * ( dS - dA ) * ( dS - dB ) * ( dS - dC ) );
			dDistance = 2.0 * dAreaABC / dC;
		}
		return( dDistance );
	}

	//�жϵ�;��εĹ�ϵ
	static const PtToRectFlag IsPointInRect( const Point& pt, const CRect& bound) 
	{
		PtToRectFlag flag = PRF_OUTRECT;
		if ( pt.x >= bound.dMinx && pt.x <= bound.dMaxx 
			&& pt.y >= bound.dMiny && pt.y <= bound.dMaxy )
		{
			if ( FLOAT_EQUAL( pt.x, bound.dMinx ) || FLOAT_EQUAL( pt.x, bound.dMaxx ) 
				|| pt.y >= bound.dMiny || pt.y <= bound.dMaxy )
			{
				flag = PRF_ONBORDER;//���ھ�������߽硣
			}
			else
			{
				flag = PRF_INRECT;//���ھ��������ڡ�
			}
		}
		return( flag );//���ھ��������ⲿ��
	}

	//�����߶ε�ˮƽ����Ľ���
	static int GetInterSectionOfHLToLine(const Point&ptOrigin,  Point &ptStart,  
		Point &ptEnd, Point&ptInterSection)
	{
		//�����߶ε����Y���ꡢ��СY�����X����,Ԥ���ж��������߶������ཻ������
		if ( ( ptOrigin.y > max( ptStart.y, ptEnd.y ) )
			|| ( ptOrigin.y < min( ptStart.y, ptEnd.y ) )
			|| ( ptOrigin.x < min( ptStart.x, ptEnd.x ) ) )
		{
			return( NoSection );
		}

		//����߶�Ϊˮƽ�߶�,�����Ϊ��ˮƽ�����޽���
		if ( FLOAT_EQUAL(ptEnd.y, ptStart.y) )
		{
			return( NoSection );
		}
		//����߶ε������������,�򽻵�Ϊ�߶����
		if ( FLOAT_EQUAL( ptOrigin.y , ptStart.y ) )
		{
			if (ptOrigin.x < ptStart.x)
			{
				return ( NoSection );
			}
			ptInterSection = ptStart;
			return( SectionIsStart );
		}

		//����߶ε��յ���������,���յ�Ϊ�߶��յ�
		if ( FLOAT_EQUAL( ptOrigin.y , ptEnd.y ) )
		{
			if (ptOrigin.x < ptEnd.x)
			{
				return ( NoSection );
			}
			ptInterSection = ptEnd;
			return( SectionIsEnd );
		}

		//����߶�Ϊ��ֱ�߶�
		if ( FLOAT_EQUAL( ptEnd.x , ptStart.x ))
		{
			ptInterSection.x = ptStart.x;
			ptInterSection.y = ptOrigin.y;
			return( SectionInLine );
		}

		//�߶ε�б��
		double dSlope = ( ptEnd.y - ptStart.y ) * 1.0  /  ( ptEnd.x - ptStart.x );
		ptInterSection.y = ptOrigin.y;
		ptInterSection.x = ( ptOrigin.y - ptStart.y )  * 1.0  / dSlope + ptStart.x;

		if ( ptInterSection.x > ptOrigin.x )
		{
			ptInterSection.x = 0;
			ptInterSection.y = 0;
			return( NoSection );
		}
		return( SectionInLine );
	}

	//һ��Լ��,�ڶ������߽���±߽��ϵĵ���Ϊ���ڶ�����ڲ�,���ұ߽���ϱ߽��ϵĵ���Ϊ���ڶ�����ⲿ(��������Ϣϵͳ�㷨������P27)
	//��Խ������ȫ����: 
	//(1)�������ϵı߰����俪ʼ��,����������ֹ��;
	//(2)�������µı߲������俪ʼ��,��������ֹ��;
	//(3)ˮƽ�߲����봩Խ����;
	//(4)���ߺͶ���εıߵĽ�������ϸ��ڵ�P���ұ�
	//������Ϊ���㷨����Ҫ��������,�ر�����ν���������1�͹���2���ֳ���
	static int GetPosOfPolygon( Point& ptOrigin, Polyline& Polygon)
	{
		CRect bound;
		bound = Polygon[0];
		for ( size_t i = 1; i < Polygon.size(); i++ )
		{
			bound += Polygon[i];
		}
		if ( IsPointInRect( ptOrigin, bound ) == PRF_OUTRECT )
		{
			return( PtOutsidePolygon );
		}

		Point ptStart, ptEnd, pt;

		int iNum = 10000;
		Point ptO(ptOrigin.x * iNum,ptOrigin.y*iNum);
		Point ptS, ptE;

		//�������һ��������Ϊ����,����ڶ�����ڲ� 
		int nCntHL = 0;//ˮƽ��������������ߵıߵĽ��������
		int nReturn = 0;//���������ε�ĳһ���ߵĽ����������ֵ

		double dMin = 1;
		for ( size_t i = 1; i < Polygon.size(); i++ )
		{
			ptStart = Polygon[i - 1];
			ptEnd = Polygon[i];
			ptS = ptStart;
			ptE = ptEnd;

			//����mapptΪԭ��,ˮƽ����������뵱ǰ�ߵĽ������
			nReturn = GetInterSectionOfHLToLine( ptOrigin, ptStart, ptEnd, pt );

			switch( nReturn )
			{
			case SectionInLine:
				{
					nCntHL++;
				}
				break;
			case SectionIsEnd://�������Ϊ��ǰ�߶ε��յ�,���ж϶���ε���һ�����������ߵ�λ�����
				//����߶ε�������һ������ֲ������ߵ�����,�򽻵��������1
				{
					if (ptEnd.y < ptStart.y)
					{  
						nCntHL++;
					}
				}
				break;
			case SectionIsStart:
				{
					if (ptEnd.y > ptStart.y)
					{
						nCntHL++;
					}
				}
				break;
			}
		}

		//�жϽ������������ż��
		if ( nCntHL % 2  == 1 )
		{
			return( PtInPolygon );
		}
		return( PtOutsidePolygon );
	}


	static Point PointSub( Point& fir, Point& sec)
	{
		return Point(fir.x-sec.x,fir.y-sec.y);
	}

	static double PointCrossPow(Point& fir, Point& sec)
	{
		return fir.x * sec.y - sec.x * fir.y;
	}

	static LINE makeline(Point& p1, Point& p2)
	{
		LINE tl;
		int sign = 1;
		tl.a = p2.y - p1.y;
		if(tl.a < 0)
		{
			sign = -1;
			tl.a = sign * tl.a;
		}
		tl.b = sign * (p1.x - p2.x);
		tl.c = sign * (p1.y * p2.x - p1.x * p2.y);
		return tl;
	}

	static bool LineIntersects( Point& firl_p1, Point& firl_p2, 
		Point& secl_p1, Point& secl_p2)
	{
		Point firls_p1(firl_p1.x, firl_p1.y);
		Point firls_p2(firl_p2.x, firl_p2.y);
		Point secls_p1(secl_p1.x, secl_p1.y);
		Point secls_p2(secl_p2.x, secl_p2.y);

		if (max(firls_p1.x, firls_p2.x) < min(secls_p1.x, secls_p2.x) || //������������ϵ������µ�Ƚ�
			max(firls_p1.y, firls_p2.y) < min(secls_p1.y, secls_p2.y) || 
			min(firls_p1.x, firls_p2.x) > max(secls_p1.x, secls_p2.x) || //���µ�����ϵ�Ƚ�                                     
			min(firls_p1.y, firls_p2.y) > max(secls_p1.y, secls_p2.y))
		{
			return false;
		}
		//ͨ������ų�
		//���ÿ���ʵ�飨������Ϣϵͳ�㷨)
		//////////////////////////////////////////////////////////////////////////������
		double pow1 = PointCrossPow(PointSub(firls_p1, secls_p1), PointSub(secls_p2, secls_p1)) *
			PointCrossPow(PointSub(secls_p2, secls_p1), PointSub(firls_p2, secls_p1));
		double pow2 = PointCrossPow(PointSub(secls_p1, firls_p1), PointSub(firls_p2, firls_p1)) *
			PointCrossPow(PointSub(firls_p2, firls_p1), PointSub(secls_p2, firls_p1));
		if (pow1 >= 0 && pow2 >= 0)
		{
			return true;
		}
		return false;
	}

	// �������ֱ�� l1(a1*x+b1*y+c1 = 0), l2(a2*x+b2*y+c2 = 0)�ཻ������true���ҷ��ؽ���p 
	static bool lineintersect(LINE& l1, LINE& l2, Point& p) // �� L1��L2
	{
		double d = l1.a * l2.b - l2.a * l1.b;
		if(abs(d) < EP) // ���ཻ
			return false;
		p.x = (l2.c * l1.b - l1.c * l2.b) / d;
		p.y = (l2.a * l1.c - l1.a * l2.c) / d;
		return true;
	}

	//linestring1:�����и�ĵ�·���ε㴮  linestring2:�����������ε㴮
	//NewLine1:������и����ε㴮		  NewLine2:�и�����յ���ε㴮
	static bool ClipLineByAnother(Polyline& linestring1, Polyline& linestring2, 
		Point& InterPoint, Polyline& NewLine1, Polyline& NewLine2)
	{
		for (size_t i = 1; i < linestring1.size(); i++ )
		{
			for (size_t j = 1; j < linestring2.size(); j++ )
			{
				bool bInter = LineIntersects(linestring1[i - 1], linestring1[i], linestring2[j - 1],linestring2[j]);
				if (bInter == true)
				{
					LINE line1 = makeline(linestring1[i -1], linestring1[i]);
					LINE line2 = makeline(linestring2[j -1], linestring2[j]);
					bool bFlag = lineintersect(line1, line2, InterPoint);
					if (InterPoint == linestring1[i -1])
					{
						NewLine1.assign(linestring1.begin(), linestring1.begin() + i);
						NewLine2.assign(linestring1.begin() + i - 1, linestring1.end());
					}
					else if (InterPoint == linestring1[i])
					{
						NewLine1.assign(linestring1.begin(), linestring1.begin() + i + 1);
						NewLine2.assign(linestring1.begin() + i, linestring1.end());
					}
					else
					{
						NewLine1.assign(linestring1.begin(), linestring1.begin() + i);
						NewLine1.push_back(InterPoint);
						NewLine2.push_back(InterPoint);
						for (; i < linestring1.size(); i++)
						{
							NewLine2.push_back(linestring1[i]);
						}
					}
					return true;
				}
			}
		}
		return false;
	}

	static double GetLengthByCoords(Polyline& road)
	{
		double length = 0;
		for (size_t i = 1; i < road.size(); ++i)
		{
			Point fir_pt = road.at(i);
			Point sec_pt = road.at(i - 1);
			length += sqrt( (sec_pt.x - fir_pt.x) * (sec_pt.x - fir_pt.x) + 
				(sec_pt.y - fir_pt.y) * (sec_pt.y - fir_pt.y) );
		}
		return length;
	}

	// ������������ľ���(��λ����)
	static double ApproxDistance(Point& point1, Point& point2)
	{
		double lat1 = point1.y;
		double lon1 = point1.x;
		double lat2 = point2.y;
		double lon2 = point2.x;
		
		const double DE2RA = 0.01745329252;//degree to radian
		const double ERAD = 6378.137 * 1000;//earth radius(unit km)
		const double FLATTENING = 1.000000/298.257223563;//����// Earth flattening (WGS84)

		lat1 = DE2RA * lat1;
		lon1 = -DE2RA * lon1;
		lat2 = DE2RA * lat2;
		lon2 = -DE2RA * lon2;

		double F = (lat1 + lat2) / 2.0;
		double G = (lat1 - lat2) / 2.0;
		double L = (lon1 - lon2) / 2.0;

		double sing = sin(G);
		double cosl = cos(L);
		double cosf = cos(F);
		double sinl = sin(L);
		double sinf = sin(F);
		double cosg = cos(G);

		double S = sing * sing * cosl * cosl + cosf * cosf * sinl * sinl;
		double C = cosg * cosg * cosl * cosl + sinf * sinf * sinl * sinl;
		double W = atan2(sqrt(S), sqrt(C));
		double R = sqrt((S * C)) / W;
		double H1 = (3 * R - 1.0) / (2.0 * C);
		double H2 = (3 * R + 1.0) / (2.0 * S);
		double D = 2 * W * ERAD;
		return (D * (1 + FLATTENING * H1 * sinf * sinf * cosg * cosg -
			FLATTENING * H2 * cosf * cosf * sing * sing));
	}

	//����㵽���߼����������
	static double GetDistanceOfPtToPolyline(Polyline& polyline, Point& pt)
	{
		double minDist = 99999;
		for (size_t i = 0; i < polyline.size() - 1; i++)
		{
			minDist = min(GetDistOfPtToLineSeg(pt, polyline[i], polyline[i + 1]), minDist);
		}
		return minDist;
	}

	static bool ApexlineTwoSides(Point& ptS, Point& ptE, CRect& rect)
	{
		double dt1, dt2, dt3, dt4;
		dt1 = (ptE.y - ptS.y) * (rect.dMinx - ptS.x) - (ptE.x - ptS.x) * (rect.dMiny - ptS.y);
		dt2 = (ptE.y - ptS.y) * (rect.dMaxx - ptS.x) - (ptE.x - ptS.x) * (rect.dMiny - ptS.y);
		dt3 = (ptE.y - ptS.y) * (rect.dMinx - ptS.x) - (ptE.x - ptS.x) * (rect.dMaxy - ptS.y);
		dt4 = (ptE.y - ptS.y) * (rect.dMaxx - ptS.x) - (ptE.x - ptS.x) * (rect.dMaxy - ptS.y);

		if ((dt1 > 0 && dt2 > 0 && dt3 > 0 && dt4 > 0)
		 || (dt1 < 0 && dt2 < 0 && dt3 < 0 && dt4 < 0))
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	static bool IsLinkCrossRect(Polyline& polyline, CRect& rect)
	{
		for (size_t i = 0; i < polyline.size() - 1; i++)
		{
			Point ptS = polyline[i];
			Point ptE = polyline[i + 1];
			CRect tempRect;
			tempRect = ptS;
			tempRect += ptE;
			if (IsPointInRect(ptS, rect) || IsPointInRect(ptE, rect))
			{
				return true;
			}
			else if (rect.RelationOfTwoRect(tempRect) == RRF_DISCRETE)
			{
				continue;
			}
			else if (ApexlineTwoSides(ptS, ptE, rect))
			{
				return true;
			}
		}
		return false;
	}

	// ���p���߶�l����̾��� ע�⣺np���߶�l�ϵ���p����ĵ㣬��һ���Ǵ���
	static double GetDistOfPtToLineSeg(Point& pt, Point& ptS, Point& ptE)
	{
		double dAngle = GetRelationOfPtToLineSeg(pt, ptS, ptE);
		if (dAngle < 0)
		{
			return ApproxDistance(pt, ptS);
		}
		else if (dAngle > 1)
		{
			return ApproxDistance(pt, ptE);
		}
		else
		{
			Point ptDicular = GetPerpendicular(pt, ptS, ptE);
			return ApproxDistance(pt, ptDicular);
		}
	}

	// ���C���߶�AB����ֱ�ߵĴ��� P
	static Point GetPerpendicular( Point& pt, Point& ptS, Point& ptE)
	{
		double dRel = GetRelationOfPtToLineSeg(pt, ptS, ptE);
		Point ptDicular;
		ptDicular.x = ptS.x + dRel * (ptE.x - ptS.x);
		ptDicular.y = ptS.y + dRel * (ptE.y - ptS.y);
		return ptDicular;
	}

	static double GetRelationOfPtToLineSeg(Point& pt, Point& ptS, Point& ptE)
	{
		double dMulCoord = (pt.x - ptS.x) * (ptE.x - ptS.x) + (pt.y - ptS.y) * (ptE.y - ptS.y);
		double dMulDist  = GetTwoPointDistance(ptS, ptE) * GetTwoPointDistance(ptS, ptE);
		return dMulCoord / dMulDist;
	}

	//��ȡ�߶���x��ļн�
	static double GetAngleOfLineSegToX(Point& ptS, Point& ptE)
	{
		double dX = ptE.x - ptS.x;
		double dY = ptE.y - ptS.y;
		double dAngle = atan2(dY, dX) * 180.0 / 3.1415926535898;
		if ( dAngle == 180.0)
		{
			dAngle = 0;
		}
		else if (dAngle > 90.0)
		{
			dAngle -= 180;
		}
		else if (dAngle < -90.0)
		{ 
			dAngle += 180;
		}
		return dAngle;
	}

	//��ȡ�߶��븺y����ʱ��ļн�
	static double GetAngleOfLineSegToY(Point& ptS, Point& ptE, BYTE ucDirection)
	{
		double dX, dY;
		if (ucDirection == DIR_POS)
		{
			dX = ptS.x - ptE.x;
			dY = ptS.y - ptE.y;
		}
		else
		{
			dX = ptE.x - ptS.x;
			dY = ptE.y - ptS.y;
		}
		double dAngle = atan2(dY, dX) * 180.0 / 3.1415926535898;
		if (dAngle > -90.0)
		{
			dAngle = 270 - dAngle;
		}
		else
		{
			dAngle = -dAngle - 90;
		}
		return dAngle;
	}
};