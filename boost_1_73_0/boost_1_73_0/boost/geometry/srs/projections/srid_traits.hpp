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
g7FYt+rAvWHQ8e7ZF07IVlY6s9OGBjrvCVF/7QREsusrne49k3jjzUX9sdBq40lvDDiadueGdmdkW7/Tm/7QiuSMLoF26b/Vxmanf+daU4kLNbvuqKtuiIVWCf3JGT4Vdanhk9+bml4tZOKG04+ak3DOrw1fKILw2KgyoDfCGvaAUmPcW6n7V28lz+3wbNisScai2jT8B36vjtCMnRLGxjTcQu3fFI+loUGTncmrGI0rG65U5C2O3/Zwnwv9ZQk=
*/