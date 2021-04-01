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
zoCVTmc/KBHr7ujMr87ylU+RAz/oGi3XekilGP3+JCdgincpKpcefKHGYO7k8YmGZIw4E3uVeC1Q3gwNtX4riBEAxsVUvv0gxcU1rPraXWSixJ7HINPyxyJtyq7E6p6DF0UG8ps8efklEH032Fq05JZi5dktlsaz0dv/y5dM5crVJATWso1C2exloRulRQHDrZFpbOR3OmEaTCebxphwCG/J8uIk7ADd6ITYaRhZ3VY8nG6cJ1hBHYohQbdoedf7Olx7QiI64sckQsYsi3zIPTIRiUhKSMsMub1oj+kng3Dfrqd5ebNvgWlY0TbwYrgM5oCTFReeMxjqhO0oD39yz9+DO+WgFSzIEtp0dIddYuqoC0jm0wX5tD16qg7EhBvwmAqicAqKMdHGvOUtgdF9OtBHfN9TSNZQY46yWvNXGlUFUEl3FFiQ0Y6Q95rVtNHGPrU+2QsaVxjhTijfM9vO++iWCwdXC3R3TsSvZP1S5XEtLo8r5A11TxDNbrPAa4Tmy4O6l+E9FnYvVTJKR/IZJGLszn6qPirFSrN2fbNzSJSgn7QmdjNFgxHa3A==
*/