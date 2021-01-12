// Boost.Geometry

// Copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_PROJECTIONS_SRID_TRAITS_HPP
#define BOOST_GEOMETRY_PROJECTIONS_SRID_TRAITS_HPP


#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_SRID_TRAITS_BEG(AUTH, CODE) \
template<> \
struct AUTH##_traits<CODE> \
{ \
    typedef \

#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_SRID_TRAITS_MID() \
    parameters_type; \
    static inline parameters_type parameters() \
    { \
        return parameters_type \

#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_SRID_TRAITS_END() \
        ; \
    } \
}; \


#endif // BOOST_GEOMETRY_PROJECTIONS_SRID_TRAITS_HPP


/* srid_traits.hpp
aoevOL3Kxmbn+cmgw9qu7Ptt/X8XfJNgbv/+fnizhO73CeAXCua2vz/DF3nyZ8EFTv11v18J9/FV8JM8fDPc/X4o77f68Tb4eYK75fsy+ArP951ugDd4vu/0KfhZnvg9Aj/Sw4MLqb8efgp8jocvg68S6y9u/u+An+p5/tlwX/gH4ed7+q/PwJ/r4d+BDwvu5n/3RUnOvyTugr/kCXH7fh/8aMHd9v1j+Eme91c9Me5/Z0zB
*/