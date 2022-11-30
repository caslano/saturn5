// Boost.Geometry

// Copyright (c) 2016-2019 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_INVERSE_DIFFERENTIAL_QUANTITIES_HPP
#define BOOST_GEOMETRY_FORMULAS_INVERSE_DIFFERENTIAL_QUANTITIES_HPP

#include <boost/geometry/core/assert.hpp>

#include <boost/geometry/util/condition.hpp>
#include <boost/geometry/util/math.hpp>


namespace boost { namespace geometry { namespace formula
{

/*!
\brief The solution of a part of the inverse problem - differential quantities.
\author See
- Charles F.F Karney, Algorithms for geodesics, 2011
https://arxiv.org/pdf/1109.4448.pdf
*/
template <
    typename CT,
    bool EnableReducedLength,
    bool EnableGeodesicScale,
    unsigned int Order = 2,
    bool ApproxF = true
>
class differential_quantities
{
public:
    static inline void apply(CT const& lon1, CT const& lat1,
                             CT const& lon2, CT const& lat2,
                             CT const& azimuth, CT const& reverse_azimuth,
                             CT const& b, CT const& f,
                             CT & reduced_length, CT & geodesic_scale)
    {
        CT const dlon = lon2 - lon1;
        CT const sin_lat1 = sin(lat1);
        CT const cos_lat1 = cos(lat1);
        CT const sin_lat2 = sin(lat2);
        CT const cos_lat2 = cos(lat2);

        apply(dlon, sin_lat1, cos_lat1, sin_lat2, cos_lat2,
              azimuth, reverse_azimuth,
              b, f,
              reduced_length, geodesic_scale);
    }

    static inline void apply(CT const& dlon,
                             CT const& sin_lat1, CT const& cos_lat1,
                             CT const& sin_lat2, CT const& cos_lat2,
                             CT const& azimuth, CT const& reverse_azimuth,
                             CT const& b, CT const& f,
                             CT & reduced_length, CT & geodesic_scale)
    {
        CT const c0 = 0;
        CT const c1 = 1;
        CT const one_minus_f = c1 - f;

        CT sin_bet1 = one_minus_f * sin_lat1;
        CT sin_bet2 = one_minus_f * sin_lat2;
            
        // equator
        if (math::equals(sin_bet1, c0) && math::equals(sin_bet2, c0))
        {
            CT const sig_12 = dlon / one_minus_f;
            if (BOOST_GEOMETRY_CONDITION(EnableReducedLength))
            {
                BOOST_GEOMETRY_ASSERT((-math::pi<CT>() <= azimuth && azimuth <= math::pi<CT>()));

                int azi_sign = math::sign(azimuth) >= 0 ? 1 : -1; // for antipodal
                CT m12 = azi_sign * sin(sig_12) * b;
                reduced_length = m12;
            }
                
            if (BOOST_GEOMETRY_CONDITION(EnableGeodesicScale))
            {
                CT M12 = cos(sig_12);
                geodesic_scale = M12;
            }
        }
        else
        {
            CT const c2 = 2;
            CT const e2 = f * (c2 - f);
            CT const ep2 = e2 / math::sqr(one_minus_f);

            CT const sin_alp1 = sin(azimuth);
            CT const cos_alp1 = cos(azimuth);
            //CT const sin_alp2 = sin(reverse_azimuth);
            CT const cos_alp2 = cos(reverse_azimuth);

            CT cos_bet1 = cos_lat1;
            CT cos_bet2 = cos_lat2;

            normalize(sin_bet1, cos_bet1);
            normalize(sin_bet2, cos_bet2);

            CT sin_sig1 = sin_bet1;
            CT cos_sig1 = cos_alp1 * cos_bet1;
            CT sin_sig2 = sin_bet2;
            CT cos_sig2 = cos_alp2 * cos_bet2;

            normalize(sin_sig1, cos_sig1);
            normalize(sin_sig2, cos_sig2);

            CT const sin_alp0 = sin_alp1 * cos_bet1;
            CT const cos_alp0_sqr = c1 - math::sqr(sin_alp0);

            CT const J12 = BOOST_GEOMETRY_CONDITION(ApproxF) ?
                           J12_f(sin_sig1, cos_sig1, sin_sig2, cos_sig2, cos_alp0_sqr, f) :
                           J12_ep_sqr(sin_sig1, cos_sig1, sin_sig2, cos_sig2, cos_alp0_sqr, ep2) ;

            CT const dn1 = math::sqrt(c1 + ep2 * math::sqr(sin_bet1));
            CT const dn2 = math::sqrt(c1 + ep2 * math::sqr(sin_bet2));

            if (BOOST_GEOMETRY_CONDITION(EnableReducedLength))
            {
                CT const m12_b = dn2 * (cos_sig1 * sin_sig2)
                               - dn1 * (sin_sig1 * cos_sig2)
                               - cos_sig1 * cos_sig2 * J12;
                CT const m12 = m12_b * b;

                reduced_length = m12;
            }

            if (BOOST_GEOMETRY_CONDITION(EnableGeodesicScale))
            {
                CT const cos_sig12 = cos_sig1 * cos_sig2 + sin_sig1 * sin_sig2;
                CT const t = ep2 * (cos_bet1 - cos_bet2) * (cos_bet1 + cos_bet2) / (dn1 + dn2);
                CT const M12 = cos_sig12 + (t * sin_sig2 - cos_sig2 * J12) * sin_sig1 / dn1;

                geodesic_scale = M12;
            }
        }
    }

private:
    /*! Approximation of J12, expanded into taylor series in f
        Maxima script:
        ep2: f * (2-f) / ((1-f)^2);
        k2: ca02 * ep2;
        assume(f < 1);
        assume(sig > 0);
        I1(sig):= integrate(sqrt(1 + k2 * sin(s)^2), s, 0, sig);
        I2(sig):= integrate(1/sqrt(1 + k2 * sin(s)^2), s, 0, sig);
        J(sig):= I1(sig) - I2(sig);
        S: taylor(J(sig), f, 0, 3);
        S1: factor( 2*integrate(sin(s)^2,s,0,sig)*ca02*f );
        S2: factor( ((integrate(-6*ca02^2*sin(s)^4+6*ca02*sin(s)^2,s,0,sig)+integrate(-2*ca02^2*sin(s)^4+6*ca02*sin(s)^2,s,0,sig))*f^2)/4 );
        S3: factor( ((integrate(30*ca02^3*sin(s)^6-54*ca02^2*sin(s)^4+24*ca02*sin(s)^2,s,0,sig)+integrate(6*ca02^3*sin(s)^6-18*ca02^2*sin(s)^4+24*ca02*sin(s)^2,s,0,sig))*f^3)/12 );
    */
    static inline CT J12_f(CT const& sin_sig1, CT const& cos_sig1,
                           CT const& sin_sig2, CT const& cos_sig2,
                           CT const& cos_alp0_sqr, CT const& f)
    {
        if (Order == 0)
        {
            return 0;
        }

        CT const c2 = 2;

        CT const sig_12 = atan2(cos_sig1 * sin_sig2 - sin_sig1 * cos_sig2,
                                cos_sig1 * cos_sig2 + sin_sig1 * sin_sig2);
        CT const sin_2sig1 = c2 * cos_sig1 * sin_sig1; // sin(2sig1)
        CT const sin_2sig2 = c2 * cos_sig2 * sin_sig2; // sin(2sig2)
        CT const sin_2sig_12 = sin_2sig2 - sin_2sig1;
        CT const L1 = sig_12 - sin_2sig_12 / c2;

        if (Order == 1)
        {
            return cos_alp0_sqr * f * L1;
        }
        
        CT const sin_4sig1 = c2 * sin_2sig1 * (math::sqr(cos_sig1) - math::sqr(sin_sig1)); // sin(4sig1)
        CT const sin_4sig2 = c2 * sin_2sig2 * (math::sqr(cos_sig2) - math::sqr(sin_sig2)); // sin(4sig2)
        CT const sin_4sig_12 = sin_4sig2 - sin_4sig1;
        
        CT const c8 = 8;
        CT const c12 = 12;
        CT const c16 = 16;
        CT const c24 = 24;

        CT const L2 = -( cos_alp0_sqr * sin_4sig_12
                         + (-c8 * cos_alp0_sqr + c12) * sin_2sig_12
                         + (c12 * cos_alp0_sqr - c24) * sig_12)
                       / c16;

        if (Order == 2)
        {
            return cos_alp0_sqr * f * (L1 + f * L2);
        }

        CT const c4 = 4;
        CT const c9 = 9;
        CT const c48 = 48;
        CT const c60 = 60;
        CT const c64 = 64;
        CT const c96 = 96;
        CT const c128 = 128;
        CT const c144 = 144;

        CT const cos_alp0_quad = math::sqr(cos_alp0_sqr);
        CT const sin3_2sig1 = math::sqr(sin_2sig1) * sin_2sig1;
        CT const sin3_2sig2 = math::sqr(sin_2sig2) * sin_2sig2;
        CT const sin3_2sig_12 = sin3_2sig2 - sin3_2sig1;

        CT const A = (c9 * cos_alp0_quad - c12 * cos_alp0_sqr) * sin_4sig_12;
        CT const B = c4 * cos_alp0_quad * sin3_2sig_12;
        CT const C = (-c48 * cos_alp0_quad + c96 * cos_alp0_sqr - c64) * sin_2sig_12;
        CT const D = (c60 * cos_alp0_quad - c144 * cos_alp0_sqr + c128) * sig_12;

        CT const L3 = (A + B + C + D) / c64;

        // Order 3 and higher
        return cos_alp0_sqr * f * (L1 + f * (L2 + f * L3));
    }

    /*! Approximation of J12, expanded into taylor series in e'^2
        Maxima script:
        k2: ca02 * ep2;
        assume(sig > 0);
        I1(sig):= integrate(sqrt(1 + k2 * sin(s)^2), s, 0, sig);
        I2(sig):= integrate(1/sqrt(1 + k2 * sin(s)^2), s, 0, sig);
        J(sig):= I1(sig) - I2(sig);
        S: taylor(J(sig), ep2, 0, 3);
        S1: factor( integrate(sin(s)^2,s,0,sig)*ca02*ep2 );
        S2: factor( (integrate(sin(s)^4,s,0,sig)*ca02^2*ep2^2)/2 );
        S3: factor( (3*integrate(sin(s)^6,s,0,sig)*ca02^3*ep2^3)/8 );
    */
    static inline CT J12_ep_sqr(CT const& sin_sig1, CT const& cos_sig1,
                                CT const& sin_sig2, CT const& cos_sig2,
                                CT const& cos_alp0_sqr, CT const& ep_sqr)
    {
        if (Order == 0)
        {
            return 0;
        }

        CT const c2 = 2;
        CT const c4 = 4;

        CT const c2a0ep2 = cos_alp0_sqr * ep_sqr;

        CT const sig_12 = atan2(cos_sig1 * sin_sig2 - sin_sig1 * cos_sig2,
                                cos_sig1 * cos_sig2 + sin_sig1 * sin_sig2); // sig2 - sig1
        CT const sin_2sig1 = c2 * cos_sig1 * sin_sig1; // sin(2sig1)
        CT const sin_2sig2 = c2 * cos_sig2 * sin_sig2; // sin(2sig2)
        CT const sin_2sig_12 = sin_2sig2 - sin_2sig1;

        CT const L1 = (c2 * sig_12 - sin_2sig_12) / c4;

        if (Order == 1)
        {
            return c2a0ep2 * L1;
        }

        CT const c8 = 8;
        CT const c64 = 64;
        
        CT const sin_4sig1 = c2 * sin_2sig1 * (math::sqr(cos_sig1) - math::sqr(sin_sig1)); // sin(4sig1)
        CT const sin_4sig2 = c2 * sin_2sig2 * (math::sqr(cos_sig2) - math::sqr(sin_sig2)); // sin(4sig2)
        CT const sin_4sig_12 = sin_4sig2 - sin_4sig1;
        
        CT const L2 = (sin_4sig_12 - c8 * sin_2sig_12 + 12 * sig_12) / c64;

        if (Order == 2)
        {
            return c2a0ep2 * (L1 + c2a0ep2 * L2);
        }

        CT const sin3_2sig1 = math::sqr(sin_2sig1) * sin_2sig1;
        CT const sin3_2sig2 = math::sqr(sin_2sig2) * sin_2sig2;
        CT const sin3_2sig_12 = sin3_2sig2 - sin3_2sig1;

        CT const c9 = 9;
        CT const c48 = 48;
        CT const c60 = 60;
        CT const c512 = 512;

        CT const L3 = (c9 * sin_4sig_12 + c4 * sin3_2sig_12 - c48 * sin_2sig_12 + c60 * sig_12) / c512;

        // Order 3 and higher
        return c2a0ep2 * (L1 + c2a0ep2 * (L2 + c2a0ep2 * L3));
    }

    static inline void normalize(CT & x, CT & y)
    {
        CT const len = math::sqrt(math::sqr(x) + math::sqr(y));
        x /= len;
        y /= len;
    }
};

}}} // namespace boost::geometry::formula


#endif // BOOST_GEOMETRY_FORMULAS_INVERSE_DIFFERENTIAL_QUANTITIES_HPP

/* differential_quantities.hpp
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
*/