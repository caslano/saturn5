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