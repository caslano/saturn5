//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2015.
// (C) Copyright Gennaro Prota 2003 - 2004.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_TRANSFORM_ITERATORS_HPP
#define BOOST_INTERPROCESS_DETAIL_TRANSFORM_ITERATORS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

// interprocess
#include <boost/interprocess/interprocess_fwd.hpp>
// container/detail
#include <boost/container/detail/transform_iterator.hpp>

namespace boost {
namespace interprocess {

using boost::container::make_transform_iterator;
using boost::container::transform_iterator;

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_DETAIL_TRANSFORM_ITERATORS_HPP

/* transform_iterator.hpp
DDWIZzJmJHaheTIOtxB8yHdzn+ahjbCmpWYckYUN8DMq9Fx1ALIL3ehCl5vR4dkDhBzwufMLHEy24aL8VkmcL2juR5tY4Ygx0aJWPLTw7BxxjxIidLYPqM+AyHKYGrYBoKH4BI/ppfnhb51f1hd0P1EuUkdDaUlKYWHKrL2dwsw2SB+BcRBLiCTEETsyASAfuvZqZsAsMfKTo6NIbM7FuBZKnxGxvRs9KVYJC72yRwxP/ZBb6iq2AQJlrCwMJX3y2bfsyXPCVWcKB+B0flFWKS3tf41eZCbXg58HZB9eVMmGN0bEnF5JRx9IG7UKOr6hcXk6ZyFVe3O0iPZr81MPmOyym8mci5uxnAUnMjr+eIEf8AQHI3JQH7fmUAOwCbcKfq2sn2GiqWUUmO6Qg3A074d2S2r+MeBCh0Q5uzQmZD9UiOpM/Xsl2fT8pfHEXiL2PnjOyk2GGrU5eVrM1PoAq9yhbdV9bjokJNNuIVqZ/bWMYwbJFrXcvKoZ9P8oRzEb2QCR6emI/y+ZPMxTqWJhFKl0S6uoV3C/cjovJv+XmqKhVGhM4W1evqxQWg==
*/