// Boost.Geometry

// Copyright (c) 2015-2018 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_AREA_FORMULAS_HPP
#define BOOST_GEOMETRY_FORMULAS_AREA_FORMULAS_HPP

#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/formulas/flattening.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/math/special_functions/hypot.hpp>

namespace boost { namespace geometry { namespace formula
{

/*!
\brief Formulas for computing spherical and ellipsoidal polygon area.
 The current class computes the area of the trapezoid defined by a segment
 the two meridians passing by the endpoints and the equator.
\author See
- Danielsen JS, The area under the geodesic. Surv Rev 30(232):
61–66, 1989
- Charles F.F Karney, Algorithms for geodesics, 2011
https://arxiv.org/pdf/1109.4448.pdf
*/

template <
        typename CT,
        std::size_t SeriesOrder = 2,
        bool ExpandEpsN = true
>
class area_formulas
{

public:

    //TODO: move the following to a more general space to be used by other
    //      classes as well
    /*
        Evaluate the polynomial in x using Horner's method.
    */
    template <typename NT, typename IteratorType>
    static inline NT horner_evaluate(NT const& x,
                                     IteratorType begin,
                                     IteratorType end)
    {
        NT result(0);
        IteratorType it = end;
        do
        {
            result = result * x + *--it;
        }
        while (it != begin);
        return result;
    }

    /*
        Clenshaw algorithm for summing trigonometric series
        https://en.wikipedia.org/wiki/Clenshaw_algorithm
    */
    template <typename NT, typename IteratorType>
    static inline NT clenshaw_sum(NT const& cosx,
                                  IteratorType begin,
                                  IteratorType end)
    {
        IteratorType it = end;
        bool odd = true;
        CT b_k, b_k1(0), b_k2(0);
        do
        {
            CT c_k = odd ? *--it : NT(0);
            b_k = c_k + NT(2) * cosx * b_k1 - b_k2;
            b_k2 = b_k1;
            b_k1 = b_k;
            odd = !odd;
        }
        while (it != begin);

        return *begin + b_k1 * cosx - b_k2;
    }

    template<typename T>
    static inline void normalize(T& x, T& y)
    {
        T h = boost::math::hypot(x, y);
        x /= h;
        y /= h;
    }

    /*
     Generate and evaluate the series expansion of the following integral

        I4 = -integrate( (t(ep2) - t(k2*sin(sigma1)^2)) / (ep2 - k2*sin(sigma1)^2)
           * sin(sigma1)/2, sigma1, pi/2, sigma )
     where

        t(x) = sqrt(1+1/x)*asinh(sqrt(x)) + x

     valid for ep2 and k2 small.  We substitute k2 = 4 * eps / (1 - eps)^2
     and ep2 = 4 * n / (1 - n)^2 and expand in eps and n.

     The resulting sum of the series is of the form

        sum(C4[l] * cos((2*l+1)*sigma), l, 0, maxpow-1) )

     The above expansion is performed in Computer Algebra System Maxima.
     The C++ code (that yields the function evaluate_coeffs_n below) is generated
     by the following Maxima script and is based on script:
     http://geographiclib.sourceforge.net/html/geod.mac

        // Maxima script begin
        taylordepth:5$
        ataylor(expr,var,ord):=expand(ratdisrep(taylor(expr,var,0,ord)))$
        jtaylor(expr,var1,var2,ord):=block([zz],expand(subst([zz=1],
        ratdisrep(taylor(subst([var1=zz*var1,var2=zz*var2],expr),zz,0,ord)))))$

        compute(maxpow):=block([int,t,intexp,area, x,ep2,k2],
        maxpow:maxpow-1,
        t : sqrt(1+1/x) * asinh(sqrt(x)) + x,
        int:-(tf(ep2) - tf(k2*sin(sigma)^2)) / (ep2 - k2*sin(sigma)^2)
        * sin(sigma)/2,
        int:subst([tf(ep2)=subst([x=ep2],t),
        tf(k2*sin(sigma)^2)=subst([x=k2*sin(sigma)^2],t)],
        int),
        int:subst([abs(sin(sigma))=sin(sigma)],int),
        int:subst([k2=4*eps/(1-eps)^2,ep2=4*n/(1-n)^2],int),
        intexp:jtaylor(int,n,eps,maxpow),
        area:trigreduce(integrate(intexp,sigma)),
        area:expand(area-subst(sigma=%pi/2,area)),
        for i:0 thru maxpow do C4[i]:coeff(area,cos((2*i+1)*sigma)),
        if expand(area-sum(C4[i]*cos((2*i+1)*sigma),i,0,maxpow)) # 0
        then error("left over terms in I4"),
        'done)$

        printcode(maxpow):=
        block([tab2:"    ",tab3:"      "],
        print(" switch (SeriesOrder) {"),
        for nn:1 thru maxpow do block([c],
        print(concat(tab2,"case ",string(nn-1),":")),
        c:0,
        for m:0 thru nn-1 do block(
          [q:jtaylor(subst([n=n],C4[m]),n,eps,nn-1),
          linel:1200],
          for j:m thru nn-1 do (
            print(concat(tab3,"coeffs_n[",c,"] = ",
                string(horner(coeff(q,eps,j))),";")),
            c:c+1)
        ),
        print(concat(tab3,"break;"))),
        print("    }"),
        'done)$

        maxpow:6$
        compute(maxpow)$
        printcode(maxpow)$
        // Maxima script end

     In the resulting code we should replace each number x by CT(x)
     e.g. using the following scirpt:
       sed -e 's/[0-9]\+/CT(&)/g; s/\[CT(/\[/g; s/)\]/\]/g;
               s/case\sCT(/case /g; s/):/:/g'
    */

    static inline void evaluate_coeffs_n(CT const& n, CT coeffs_n[])
    {

        switch (SeriesOrder) {
        case 0:
            coeffs_n[0] = CT(2)/CT(3);
            break;
        case 1:
            coeffs_n[0] = (CT(10)-CT(4)*n)/CT(15);
            coeffs_n[1] = -CT(1)/CT(5);
            coeffs_n[2] = CT(1)/CT(45);
            break;
        case 2:
            coeffs_n[0] = (n*(CT(8)*n-CT(28))+CT(70))/CT(105);
            coeffs_n[1] = (CT(16)*n-CT(7))/CT(35);
            coeffs_n[2] = -CT(2)/CT(105);
            coeffs_n[3] = (CT(7)-CT(16)*n)/CT(315);
            coeffs_n[4] = -CT(2)/CT(105);
            coeffs_n[5] = CT(4)/CT(525);
            break;
        case 3:
            coeffs_n[0] = (n*(n*(CT(4)*n+CT(24))-CT(84))+CT(210))/CT(315);
            coeffs_n[1] = ((CT(48)-CT(32)*n)*n-CT(21))/CT(105);
            coeffs_n[2] = (-CT(32)*n-CT(6))/CT(315);
            coeffs_n[3] = CT(11)/CT(315);
            coeffs_n[4] = (n*(CT(32)*n-CT(48))+CT(21))/CT(945);
            coeffs_n[5] = (CT(64)*n-CT(18))/CT(945);
            coeffs_n[6] = -CT(1)/CT(105);
            coeffs_n[7] = (CT(12)-CT(32)*n)/CT(1575);
            coeffs_n[8] = -CT(8)/CT(1575);
            coeffs_n[9] = CT(8)/CT(2205);
            break;
        case 4:
            coeffs_n[0] = (n*(n*(n*(CT(16)*n+CT(44))+CT(264))-CT(924))+CT(2310))/CT(3465);
            coeffs_n[1] = (n*(n*(CT(48)*n-CT(352))+CT(528))-CT(231))/CT(1155);
            coeffs_n[2] = (n*(CT(1088)*n-CT(352))-CT(66))/CT(3465);
            coeffs_n[3] = (CT(121)-CT(368)*n)/CT(3465);
            coeffs_n[4] = CT(4)/CT(1155);
            coeffs_n[5] = (n*((CT(352)-CT(48)*n)*n-CT(528))+CT(231))/CT(10395);
            coeffs_n[6] = ((CT(704)-CT(896)*n)*n-CT(198))/CT(10395);
            coeffs_n[7] = (CT(80)*n-CT(99))/CT(10395);
            coeffs_n[8] = CT(4)/CT(1155);
            coeffs_n[9] = (n*(CT(320)*n-CT(352))+CT(132))/CT(17325);
            coeffs_n[10] = (CT(384)*n-CT(88))/CT(17325);
            coeffs_n[11] = -CT(8)/CT(1925);
            coeffs_n[12] = (CT(88)-CT(256)*n)/CT(24255);
            coeffs_n[13] = -CT(16)/CT(8085);
            coeffs_n[14] = CT(64)/CT(31185);
            break;
        case 5:
            coeffs_n[0] = (n*(n*(n*(n*(CT(100)*n+CT(208))+CT(572))+CT(3432))-CT(12012))+CT(30030))
                          /CT(45045);
            coeffs_n[1] = (n*(n*(n*(CT(64)*n+CT(624))-CT(4576))+CT(6864))-CT(3003))/CT(15015);
            coeffs_n[2] = (n*((CT(14144)-CT(10656)*n)*n-CT(4576))-CT(858))/CT(45045);
            coeffs_n[3] = ((-CT(224)*n-CT(4784))*n+CT(1573))/CT(45045);
            coeffs_n[4] = (CT(1088)*n+CT(156))/CT(45045);
            coeffs_n[5] = CT(97)/CT(15015);
            coeffs_n[6] = (n*(n*((-CT(64)*n-CT(624))*n+CT(4576))-CT(6864))+CT(3003))/CT(135135);
            coeffs_n[7] = (n*(n*(CT(5952)*n-CT(11648))+CT(9152))-CT(2574))/CT(135135);
            coeffs_n[8] = (n*(CT(5792)*n+CT(1040))-CT(1287))/CT(135135);
            coeffs_n[9] = (CT(468)-CT(2944)*n)/CT(135135);
            coeffs_n[10] = CT(1)/CT(9009);
            coeffs_n[11] = (n*((CT(4160)-CT(1440)*n)*n-CT(4576))+CT(1716))/CT(225225);
            coeffs_n[12] = ((CT(4992)-CT(8448)*n)*n-CT(1144))/CT(225225);
            coeffs_n[13] = (CT(1856)*n-CT(936))/CT(225225);
            coeffs_n[14] = CT(8)/CT(10725);
            coeffs_n[15] = (n*(CT(3584)*n-CT(3328))+CT(1144))/CT(315315);
            coeffs_n[16] = (CT(1024)*n-CT(208))/CT(105105);
            coeffs_n[17] = -CT(136)/CT(63063);
            coeffs_n[18] = (CT(832)-CT(2560)*n)/CT(405405);
            coeffs_n[19] = -CT(128)/CT(135135);
            coeffs_n[20] = CT(128)/CT(99099);
            break;
        }
    }

    /*
       Expand in k2 and ep2.
    */
    static inline void evaluate_coeffs_ep(CT const& ep, CT coeffs_n[])
    {
        switch (SeriesOrder) {
        case 0:
            coeffs_n[0] = CT(2)/CT(3);
            break;
        case 1:
            coeffs_n[0] = (CT(10)-ep)/CT(15);
            coeffs_n[1] = -CT(1)/CT(20);
            coeffs_n[2] = CT(1)/CT(180);
            break;
        case 2:
            coeffs_n[0] = (ep*(CT(4)*ep-CT(7))+CT(70))/CT(105);
            coeffs_n[1] = (CT(4)*ep-CT(7))/CT(140);
            coeffs_n[2] = CT(1)/CT(42);
            coeffs_n[3] = (CT(7)-CT(4)*ep)/CT(1260);
            coeffs_n[4] = -CT(1)/CT(252);
            coeffs_n[5] = CT(1)/CT(2100);
            break;
        case 3:
            coeffs_n[0] = (ep*((CT(12)-CT(8)*ep)*ep-CT(21))+CT(210))/CT(315);
            coeffs_n[1] = ((CT(12)-CT(8)*ep)*ep-CT(21))/CT(420);
            coeffs_n[2] = (CT(3)-CT(2)*ep)/CT(126);
            coeffs_n[3] = -CT(1)/CT(72);
            coeffs_n[4] = (ep*(CT(8)*ep-CT(12))+CT(21))/CT(3780);
            coeffs_n[5] = (CT(2)*ep-CT(3))/CT(756);
            coeffs_n[6] = CT(1)/CT(360);
            coeffs_n[7] = (CT(3)-CT(2)*ep)/CT(6300);
            coeffs_n[8] = -CT(1)/CT(1800);
            coeffs_n[9] = CT(1)/CT(17640);
            break;
        case 4:
            coeffs_n[0] = (ep*(ep*(ep*(CT(64)*ep-CT(88))+CT(132))-CT(231))+CT(2310))/CT(3465);
            coeffs_n[1] = (ep*(ep*(CT(64)*ep-CT(88))+CT(132))-CT(231))/CT(4620);
            coeffs_n[2] = (ep*(CT(16)*ep-CT(22))+CT(33))/CT(1386);
            coeffs_n[3] = (CT(8)*ep-CT(11))/CT(792);
            coeffs_n[4] = CT(1)/CT(110);
            coeffs_n[5] = (ep*((CT(88)-CT(64)*ep)*ep-CT(132))+CT(231))/CT(41580);
            coeffs_n[6] = ((CT(22)-CT(16)*ep)*ep-CT(33))/CT(8316);
            coeffs_n[7] = (CT(11)-CT(8)*ep)/CT(3960);
            coeffs_n[8] = -CT(1)/CT(495);
            coeffs_n[9] = (ep*(CT(16)*ep-CT(22))+CT(33))/CT(69300);
            coeffs_n[10] = (CT(8)*ep-CT(11))/CT(19800);
            coeffs_n[11] = CT(1)/CT(1925);
            coeffs_n[12] = (CT(11)-CT(8)*ep)/CT(194040);
            coeffs_n[13] = -CT(1)/CT(10780);
            coeffs_n[14] = CT(1)/CT(124740);
            break;
        case 5:
            coeffs_n[0] = (ep*(ep*(ep*((CT(832)-CT(640)*ep)*ep-CT(1144))+CT(1716))-CT(3003))+CT(30030))/CT(45045);
            coeffs_n[1] = (ep*(ep*((CT(832)-CT(640)*ep)*ep-CT(1144))+CT(1716))-CT(3003))/CT(60060);
            coeffs_n[2] = (ep*((CT(208)-CT(160)*ep)*ep-CT(286))+CT(429))/CT(18018);
            coeffs_n[3] = ((CT(104)-CT(80)*ep)*ep-CT(143))/CT(10296);
            coeffs_n[4] = (CT(13)-CT(10)*ep)/CT(1430);
            coeffs_n[5] = -CT(1)/CT(156);
            coeffs_n[6] = (ep*(ep*(ep*(CT(640)*ep-CT(832))+CT(1144))-CT(1716))+CT(3003))/CT(540540);
            coeffs_n[7] = (ep*(ep*(CT(160)*ep-CT(208))+CT(286))-CT(429))/CT(108108);
            coeffs_n[8] = (ep*(CT(80)*ep-CT(104))+CT(143))/CT(51480);
            coeffs_n[9] = (CT(10)*ep-CT(13))/CT(6435);
            coeffs_n[10] = CT(5)/CT(3276);
            coeffs_n[11] = (ep*((CT(208)-CT(160)*ep)*ep-CT(286))+CT(429))/CT(900900);
            coeffs_n[12] = ((CT(104)-CT(80)*ep)*ep-CT(143))/CT(257400);
            coeffs_n[13] = (CT(13)-CT(10)*ep)/CT(25025);
            coeffs_n[14] = -CT(1)/CT(2184);
            coeffs_n[15] = (ep*(CT(80)*ep-CT(104))+CT(143))/CT(2522520);
            coeffs_n[16] = (CT(10)*ep-CT(13))/CT(140140);
            coeffs_n[17] = CT(5)/CT(45864);
            coeffs_n[18] = (CT(13)-CT(10)*ep)/CT(1621620);
            coeffs_n[19] = -CT(1)/CT(58968);
            coeffs_n[20] = CT(1)/CT(792792);
            break;
        }
    }

    /*
        Given the set of coefficients coeffs1[] evaluate on var2 and return
        the set of coefficients coeffs2[]
    */

    static inline void evaluate_coeffs_var2(CT const& var2,
                                            CT const coeffs1[],
                                            CT coeffs2[])
    {
        std::size_t begin(0), end(0);
        for(std::size_t i = 0; i <= SeriesOrder; i++)
        {
            end = begin + SeriesOrder + 1 - i;
            coeffs2[i] = ((i==0) ? CT(1) : math::pow(var2, int(i)))
                        * horner_evaluate(var2, coeffs1 + begin, coeffs1 + end);
            begin = end;
        }
    }


    /*
        Compute the spherical excess of a geodesic (or shperical) segment
    */
    template <
                bool LongSegment,
                typename PointOfSegment
             >
    static inline CT spherical(PointOfSegment const& p1,
                               PointOfSegment const& p2)
    {
        CT excess;

        if(LongSegment) // not for segments parallel to equator
        {
            CT cbet1 = cos(geometry::get_as_radian<1>(p1));
            CT sbet1 = sin(geometry::get_as_radian<1>(p1));
            CT cbet2 = cos(geometry::get_as_radian<1>(p2));
            CT sbet2 = sin(geometry::get_as_radian<1>(p2));

            CT omg12 = geometry::get_as_radian<0>(p1)
                     - geometry::get_as_radian<0>(p2);
            CT comg12 = cos(omg12);
            CT somg12 = sin(omg12);

            CT alp1 = atan2(cbet1 * sbet2
                            - sbet1 * cbet2 * comg12,
                            cbet2 * somg12);

            CT alp2 = atan2(cbet1 * sbet2 * comg12
                            - sbet1 * cbet2,
                            cbet1 * somg12);

            excess = alp2 - alp1;

        } else {

            // Trapezoidal formula

            CT tan_lat1 =
                    tan(geometry::get_as_radian<1>(p1) / 2.0);
            CT tan_lat2 =
                    tan(geometry::get_as_radian<1>(p2) / 2.0);

            excess = CT(2.0)
                    * atan(((tan_lat1 + tan_lat2) / (CT(1) + tan_lat1 * tan_lat2))
                           * tan((geometry::get_as_radian<0>(p2)
                                - geometry::get_as_radian<0>(p1)) / 2));
        }

        return excess;
    }

    struct return_type_ellipsoidal
    {
        return_type_ellipsoidal()
            :   spherical_term(0),
                ellipsoidal_term(0)
        {}

        CT spherical_term;
        CT ellipsoidal_term;
    };

    /*
        Compute the ellipsoidal correction of a geodesic (or shperical) segment
    */
    template <
                template <typename, bool, bool, bool, bool, bool> class Inverse,
                typename PointOfSegment,
                typename SpheroidConst
             >
    static inline return_type_ellipsoidal ellipsoidal(PointOfSegment const& p1,
                                                      PointOfSegment const& p2,
                                                      SpheroidConst const& spheroid_const)
    {
        return_type_ellipsoidal result;

        // Azimuth Approximation

        typedef Inverse<CT, false, true, true, false, false> inverse_type;
        typedef typename inverse_type::result_type inverse_result;

        inverse_result i_res = inverse_type::apply(get_as_radian<0>(p1),
                                                   get_as_radian<1>(p1),
                                                   get_as_radian<0>(p2),
                                                   get_as_radian<1>(p2),
                                                   spheroid_const.m_spheroid);

        CT alp1 = i_res.azimuth;
        CT alp2 = i_res.reverse_azimuth;

        // Constants

        CT const ep = spheroid_const.m_ep;
        CT const f = formula::flattening<CT>(spheroid_const.m_spheroid);
        CT const one_minus_f = CT(1) - f;
        std::size_t const series_order_plus_one = SeriesOrder + 1;
        std::size_t const series_order_plus_two = SeriesOrder + 2;

        // Basic trigonometric computations

        CT tan_bet1 = tan(get_as_radian<1>(p1)) * one_minus_f;
        CT tan_bet2 = tan(get_as_radian<1>(p2)) * one_minus_f;
        CT cos_bet1 = cos(atan(tan_bet1));
        CT cos_bet2 = cos(atan(tan_bet2));
        CT sin_bet1 = tan_bet1 * cos_bet1;
        CT sin_bet2 = tan_bet2 * cos_bet2;
        CT sin_alp1 = sin(alp1);
        CT cos_alp1 = cos(alp1);
        CT cos_alp2 = cos(alp2);
        CT sin_alp0 = sin_alp1 * cos_bet1;

        // Spherical term computation

        CT sin_omg1 = sin_alp0 * sin_bet1;
        CT cos_omg1 = cos_alp1 * cos_bet1;
        CT sin_omg2 = sin_alp0 * sin_bet2;
        CT cos_omg2 = cos_alp2 * cos_bet2;
        CT cos_omg12 =  cos_omg1 * cos_omg2 + sin_omg1 * sin_omg2;
        CT excess;

        bool meridian = get<0>(p2) - get<0>(p1) == CT(0)
              || get<1>(p1) == CT(90) || get<1>(p1) == -CT(90)
              || get<1>(p2) == CT(90) || get<1>(p2) == -CT(90);

        if (!meridian && cos_omg12 > -CT(0.7)
                      && sin_bet2 - sin_bet1 < CT(1.75)) // short segment
        {
            CT sin_omg12 =  cos_omg1 * sin_omg2 - sin_omg1 * cos_omg2;
            normalize(sin_omg12, cos_omg12);

            CT cos_omg12p1 = CT(1) + cos_omg12;
            CT cos_bet1p1 = CT(1) + cos_bet1;
            CT cos_bet2p1 = CT(1) + cos_bet2;
            excess = CT(2) * atan2(sin_omg12 * (sin_bet1 * cos_bet2p1 + sin_bet2 * cos_bet1p1),
                                cos_omg12p1 * (sin_bet1 * sin_bet2 + cos_bet1p1 * cos_bet2p1));
        }
        else
        {
            /*
                    CT sin_alp2 = sin(alp2);
                    CT sin_alp12 = sin_alp2 * cos_alp1 - cos_alp2 * sin_alp1;
                    CT cos_alp12 = cos_alp2 * cos_alp1 + sin_alp2 * sin_alp1;
                    excess = atan2(sin_alp12, cos_alp12);
            */
                    excess = alp2 - alp1;
        }

        result.spherical_term = excess;

        // Ellipsoidal term computation (uses integral approximation)

        CT cos_alp0 = math::sqrt(CT(1) - math::sqr(sin_alp0));
        CT cos_sig1 = cos_alp1 * cos_bet1;
        CT cos_sig2 = cos_alp2 * cos_bet2;
        CT sin_sig1 = sin_bet1;
        CT sin_sig2 = sin_bet2;

        normalize(sin_sig1, cos_sig1);
        normalize(sin_sig2, cos_sig2);

        CT coeffs[SeriesOrder + 1];
        const std::size_t coeffs_var_size = (series_order_plus_two
                                            * series_order_plus_one) / 2;
        CT coeffs_var[coeffs_var_size];

        if(ExpandEpsN){ // expand by eps and n

            CT k2 = math::sqr(ep * cos_alp0);
            CT sqrt_k2_plus_one = math::sqrt(CT(1) + k2);
            CT eps = (sqrt_k2_plus_one - CT(1)) / (sqrt_k2_plus_one + CT(1));
            CT n = f / (CT(2) - f);

            // Generate and evaluate the polynomials on n
            // to get the series coefficients (that depend on eps)
            evaluate_coeffs_n(n, coeffs_var);

            // Generate and evaluate the polynomials on eps (i.e. var2 = eps)
            // to get the final series coefficients
            evaluate_coeffs_var2(eps, coeffs_var, coeffs);

        }else{ // expand by k2 and ep

            CT k2 = math::sqr(ep * cos_alp0);
            CT ep2 = math::sqr(ep);

            // Generate and evaluate the polynomials on ep2
            evaluate_coeffs_ep(ep2, coeffs_var);

            // Generate and evaluate the polynomials on k2 (i.e. var2 = k2)
            evaluate_coeffs_var2(k2, coeffs_var, coeffs);

        }

        // Evaluate the trigonometric sum
        CT I12 = clenshaw_sum(cos_sig2, coeffs, coeffs + series_order_plus_one)
               - clenshaw_sum(cos_sig1, coeffs, coeffs + series_order_plus_one);

        // The part of the ellipsodal correction that depends on
        // point coordinates
        result.ellipsoidal_term = cos_alp0 * sin_alp0 * I12;

        return result;
    }

    // Check whenever a segment crosses the prime meridian
    // First normalize to [0,360)
    template <typename PointOfSegment>
    static inline bool crosses_prime_meridian(PointOfSegment const& p1,
                                              PointOfSegment const& p2)
    {
        CT const pi
            = geometry::math::pi<CT>();
        CT const two_pi
            = geometry::math::two_pi<CT>();

        CT p1_lon = get_as_radian<0>(p1)
                                - ( floor( get_as_radian<0>(p1) / two_pi )
                                  * two_pi );
        CT p2_lon = get_as_radian<0>(p2)
                                - ( floor( get_as_radian<0>(p2) / two_pi )
                                  * two_pi );

        CT max_lon = (std::max)(p1_lon, p2_lon);
        CT min_lon = (std::min)(p1_lon, p2_lon);

        return max_lon > pi && min_lon < pi && max_lon - min_lon > pi;
    }

};

}}} // namespace boost::geometry::formula


#endif // BOOST_GEOMETRY_FORMULAS_AREA_FORMULAS_HPP

/* area_formulas.hpp
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
*/