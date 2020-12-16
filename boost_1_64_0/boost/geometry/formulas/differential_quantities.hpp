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
T7GoCR1LsPM0i7LqfnmHRX3oneRLmgR0v8eiYjoecizK8j6L8rw30+ApCy0qhNb8DrYXrTlvkUUNo+1nWtSl2EG0ZgwbQ2v+CptEa875gEXZaCvNNy3muWjNYiwPbV9iUbuwfZRN80VsBK3ZdBZ5ojX3YZNo+1KLuups6k7+mgXLyBOt+RlsOVrzSawUHT7Hoh4/l3ZeSByeZ1HtWIz+0vwBFkcbvMCiRtGa77zQohTp81ZY1BewUfQY/PpKi8pZRBlWWdT2fIvKRyfgCReRJzoClxSShvTl8LFL6C/8sSKLes860uBPwGon/YvWPHIp/YvWPKGEdkZH4L3rScO9mstLLaoObdtIe15GO+iywZMup33QYXj1hynzIvQVFnWzC78uG3yw3KIOo1WFRe3ADn6A/OGPsVfwT8CdldRRlxP+GMs5M9PgpVUW5UBrurFCdAReVk17ocPwArdFlaM1f4DtQGv+BrsTrfkqFkWX15AGO4TWvMhDfKI1/ZiNsikvcX4ladBx+EfMThp/nUUd5yOGdRngK9gO0mj+oN6iwmjN0/w8Cx2CD11tUQ+g7QGLygzSjtoPf7mVmEGHr7GorzbRzmjbNtp+O/GPjlxL+bEmB/fusCgn5kFPwA9fRz+iQ3ASG9ZprreoPqxZ65BFlWB+dN4NxCQWQcdvtKjTbyLN4kyDn8Ja0JqPYvvQ9p0WFcDiDsoG999M36ETuxibt1B30tjg65oZJ/id8Gsftahn0fbd9C32ClrdytyyhzbUaT5mUd+/3aKe0vrjFlWDOdF+uAvL08+CXVguOgYPYDnoBHwOK0RPwMw7iAe0DZ6BlaEdcDVWrvOHNdj4B8gf7sIm0GHYhWXp/OEBbBJ/Aj6H2XX+MPMTxIDOH56BZev84WpM6fzhISzvrEyD77uTMY7WDGJ1aM3dn6Kd0ZodWAQdb7GoU++mndF58LR7mENoz3L48F7aDe2/l7bCQugJePF9FrVnSabBa7EoWrMhQh+hNa/FxtCad2GH0Zp3tVNfnqXZgS1E2zst6g5shPxj8INdlIn05bCom3rh1/wUVorWrIpSL10e+PRnmefR9n0WdcP99JfWX7SoHqyUfBLwnAcsajPa+VWLqv0a/b6Ue+GH49QRrXn11y3qxLMzDd6GOdDqIYu6aT/5oB3fZP7BHqDMmosPMD+gNZ/DJtCaL2FZ5Kl53LeoC1rzu5gDrZkxQt3QcbjuYeIErfnGbzN+0Zpnf4exgNa8HduH1uzHRnT5H2VOSzDfno2GPz/E+F2C/r5FvfA0z9Xt86xF3f8cbYjf8Qv6bZzxq9PATb8kBpZlGsx8gTGL1jwFS6BtL1nUrYcZs7ruL9N3k8yJ+B1/tKit2GH8micdIT7xay7BctAhaP0TY1Cnh3uw5WjN015hjKA1ezA/2vZn1lOshTw1618lrtCa92L70ZoX/4W+Q4/Bq5RVvci9YbgPs55DzMyxqg9YrOpUtN1qVRfMtarN6DC8JtOq5qNj8JR5VrUcnQc7sSJ0HD6HlaInoCuLNLnUBf4RK0I7j7Oqa7GF6DB8Gjusn3W8VTmxZ/W98MOvs6ql+l44ieWj4/Ot6pLXU050DD6DvUj60AlW9VPsVPzqDVb1Duwg/jFYb7Oq/TpP+Mgbrao5jzRvsqrVmP2CTINPYUvRms9hRWjHm61qK9ZCes3HT7SqGFrzF9gIWvM32FNo/0lWtQvr120Fu7C96Bg8gD2ATsDnsH26PDDzZKvqQNvgGdghtAOuxp5CO2ENthPth7uwoM4fdmE7dP7wALZH5w+fw+7U+cPsBZT/XO59j1V990yei445rGrJYtpwBX0NT1piVcMf5FnwtLPoC9I=
*/