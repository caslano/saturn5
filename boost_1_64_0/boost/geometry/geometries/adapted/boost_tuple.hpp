// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_TUPLE_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_TUPLE_HPP


#include <cstddef>

#include <boost/tuple/tuple.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{


template <typename T1, typename T2, typename T3, typename T4, typename T5,
          typename T6, typename T7, typename T8, typename T9, typename T10>
struct tag<boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> >
{
    typedef point_tag type;
};


template <typename T1, typename T2, typename T3, typename T4, typename T5,
          typename T6, typename T7, typename T8, typename T9, typename T10>
struct coordinate_type<boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> >
{
    typedef T1 type;
};


template <typename T1, typename T2, typename T3, typename T4, typename T5,
          typename T6, typename T7, typename T8, typename T9, typename T10>
struct dimension<boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> >
    : boost::mpl::int_
          <
              boost::tuples::length
                  <
                      boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>
                  >::value
          >
{};


template <typename T1, typename T2, typename T3, typename T4, typename T5,
          typename T6, typename T7, typename T8, typename T9, typename T10,
          std::size_t Dimension>
struct access
    <
        boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>,
        Dimension
    >
{
    static inline T1 get(
        boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> const& point)
    {
        return point.template get<Dimension>();
    }

    static inline void set(
        boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>& point,
        T1 const& value)
    {
        point.template get<Dimension>() = value;
    }
};


} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS


}} // namespace boost::geometry


// Convenience registration macro to bind boost::tuple to a CS
#define BOOST_GEOMETRY_REGISTER_BOOST_TUPLE_CS(CoordinateSystem) \
    namespace boost { namespace geometry { namespace traits { \
    template <typename T1, typename T2, typename T3, typename T4, typename T5, \
              typename T6, typename T7, typename T8, typename T9, typename T10> \
    struct coordinate_system<boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> > \
    { \
        typedef CoordinateSystem type; \
    }; \
    }}}


#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_TUPLE_HPP

/* boost_tuple.hpp
E2ntSuS1QC1SLfN155758IG2I2/c0Gb6W/fV7X4p8toY77VPkddoea/hibxWynutTqS1Xke/Judo154d7Vos77VkkdYmRV5DJWsY7G9D+l2zOGQNwwhd2zESngDHwLFwLBwPT4H58FRYDMfDZXAiPAAnwS7WO0t4NjwbroBT4BNwGtwLz4UtuP4s2B7mwFR4PpQzfaP0G4F+YyCe3O0CafbpGcMWc2BfOBv2h+vhCXAOHKJ6BrwQjlB9JMyDJ6k+Fs6F41W3rlMIJ6meBefBKapPhQvgdNVnwFJ4vuqz4SKYq3oerIBFqs+DlXCh6qWwGl6keiVcDJeoXgtr4aWqL4cXwytUXwmXwatVvwYuhzeoXg/r4E2q3wxXwNtUXw9XwrtUvxuugvervgmuhg+r/gi8Bj6u+ha4Bj6l+tPwevi86tthPfyR6i/BtfAV1V+F6+Cbqv8U3gx/qfoe2ADfVf09+D34geh6tmS0vtvWd+5WfSn1IZgH3rIG6sOl8DS4HGbDy+E8uBKWwythLVwF6+BquAqSp4Gz1OF98Dr4MLwB/gDWw2fhd+FP4S3wbdgAP4C3ar3+HvwrvF3XGN0B28A7YTu4AfaCd8F+8G44Em6EJ8GH4GS4GebAh2EBfATOh4/CUtgIq+H34TL4uLbDJ+Ct8AfwbrgVPgCfgi/Cp+FP4DPwffgc/BN8Hv4Dbofx1lmrsC18ESbDHbAn/BEcAH8MR8GfwFPgK3ACfBVOh6/BHPg6nAd3wYXwl3AZ3ANXw7fgjfBteA98F94L34MPwya4BX4Id8GP4W/hXvgZ/AT+DX4Ko6gL+2Ai/Bx2ggdhH/gXOBgegpnwS3g6PACz4D9gMbQGo4ujAbwExsBrYBxsgC3g47AV/CVsCz+CafCPsAscyf20K5wIu8EzYQI8BybCXNgaFsJ0WAoHwH6xvPO3/MNB8CSYAafBofACmAnz4Cj4XXgivBNOgd+HU+GLcBr8KcyGH8Bz4F44HSbSfs6D3eBMmAFnwVNhDpwKz4fZcDYkr6gX+q4KFul9pQN/b/HJT86k7Q1T4NmwHTwXpsIFsCMsh9PgJTAbynMMvB720H7gePh32Be29JNueDwcDifAUVZ4cAy8Cp4MH4TjYMso7kdwEJwMh8Bz4SQ4AwbOMtT3FTBK7zvOswyf8VO/4fNwHHwB5sMdsAi+DHfAn8Cd8BW4B74KfwNfg7oWVp+7pe/hOu61sHN0rduFen+lj9IzHvV5ES7V+JkzHvUMwF7wpxq/t+FU+Cs4E74Dq+EHcDf8BO6Dn8Lfwc/g+ZL4wJlGfs2XJPNsJXnLdd1nnH0Hf0lwHsyE8+EIuBWOhSXwSrgQ3gtL4f1q/wgsh6/DCvgRvAgehJUw0freA/vBajgELoYnw1qYC5fClfBJuApuhdfBS+E6eAt8Et4D34CbYBN8EH4FH4J/hpthHOl7FKbBRtgXPgEHQiv8YXAr7B1z+LWGuh5Rzw7CDfIOcnD8v2cdYvvTcaPrEOuQdf/F6xCPdg3if/L6Q2vtYczXWH/YGxn+X7z+sPes/4x1h9/2msMt68lfZB/S/nbKHilE1iBbb/cd+x37Hfsd+/1f/2KQRf+i+f8yc65MkVtVubjy21kLEJvqM/u3btZxbndNTzcktz3394XyfSJ7/ISzT5+RO7dmnmNP0u9g78eFY482dd/dMX8cP2p/doh9L5/721G2wz7yPNl0196rxIFnPeKgZnjS79dcV806Bb9zcy33fqVd9P3JObo33RlIOWFucKVbtmebu7S6iLlmYWk3e81tEz9DfD0JX/NDw+ni+HYpe+uZuVVPif0gdqzvqHlk++nsziPH/IsfiP0YfPk132w=
*/