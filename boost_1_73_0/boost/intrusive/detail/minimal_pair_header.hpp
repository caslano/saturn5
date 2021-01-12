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
P4LwBoRZjdGr/KgUkWy5Vb5M6TVaSTAPbR1m/NmWZQCRNvdzVAOJbJiBn3YRmHOnO9JQQqFsCMTTIgFPlLHIbwbze/Ew+S+ok9ilI6N1Eh0wN6KytUsS64FPqo42PzZPV9kqVTZnIJUNZ7ktlTCZ9aZKTQsp9tHYcLMR9M3dSZncUc1MKPNvr7T3O3MSgi56l4yqs490RUqp3E1oE9aD1ckqd8AnReVuVy44Tq9O9jPQCOjl
*/