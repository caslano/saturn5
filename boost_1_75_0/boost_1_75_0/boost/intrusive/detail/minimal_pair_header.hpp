/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2014-2015
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTRUSIVE_DETAIL_MINIMAL_PAIR_HEADER_HPP
#define BOOST_INTRUSIVE_DETAIL_MINIMAL_PAIR_HEADER_HPP
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif
#
#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#//Try to avoid including <utility>, as it's quite big in C++11
#if defined(BOOST_GNU_STDLIB)
#  include <bits/stl_pair.h>
#else
#  include <utility>    //Fallback
#endif
#
#endif //BOOST_INTRUSIVE_DETAIL_MINIMAL_PAIR_HEADER_HPP

/* minimal_pair_header.hpp
FP0JVhgNYsUxTnN6TI0Wo0oTfyq9HYcnOz3ikU7jjHgSJVxVGQ8dYnLjrHHjdH+C3JWZd8IQIy+aHPK3p33vJAd787Q/jD9svXLPa/poXummxVgrc/MRtbXKD/Herctt6sP6l6+MnOaKqjT5mbOS78aISiRXo5dNWNiLKLSCL9Q++OK4E9iTkKcg1elkvOEQ/4vE8Fg9aExRIWw3EMlRu61YFKcN3wYeMFeyzrymX+WK7a+sPgoZKyMCwV3/4kfZRAcIvNpHwMVarQc/wSQEEXYNJBTP4bjjwcDgPPRkdgAXPK8OelQD52g3wga+NejQD/76m/DJhpg6j+nZO/CVWHr6rThp64duCtiPEYM+hSoklFU46QQxETMcPQgwOSZB3k1Ahg2k1GudeB2AAb77q6sHvZa9aSiLokgglpbAAbirwynln+hOAG+uDzn2gQYFoSblldNwkCSRgd4Ho9+vmm9WNT10YGVrD6j+neGAnhW4qlJNGfIT9CMsB++a+MTrE1vK9bhC/BZqvNj+WbjtqS3aptfr2eWhYoOPQP1TY5eLPPp1HvJOMC5zyk8ArjDUeA/O8Q86X6m3ku7+Tzr/l5ixf29rNR1tTV2s/r2rxfT8Nqwt7tJcCTRfTaQAX5mxiTQQyLXQjid8eKI+kzacX3Gi0ZF3ivFlM1QUMDyr8PCwYymf1yZPe9vAiOMEDkhT7g39/I/WLbuCf7Ru
*/