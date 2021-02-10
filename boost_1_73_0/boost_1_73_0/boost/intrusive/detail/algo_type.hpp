/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2014-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_ALGO_TYPE_HPP
#define BOOST_INTRUSIVE_DETAIL_ALGO_TYPE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

enum algo_types
{
   CircularListAlgorithms,
   CircularSListAlgorithms,
   LinearSListAlgorithms,
   CommonSListAlgorithms,
   BsTreeAlgorithms,
   RbTreeAlgorithms,
   AvlTreeAlgorithms,
   SgTreeAlgorithms,
   SplayTreeAlgorithms,
   TreapAlgorithms,
   UnorderedAlgorithms,
   UnorderedCircularSlistAlgorithms,
   AnyAlgorithm
};

template<algo_types AlgoType, class NodeTraits>
struct get_algo;

template<algo_types AlgoType, class ValueTraits, class NodePtrCompare, class ExtraChecker>
struct get_node_checker;

} //namespace intrusive
} //namespace boost

#endif //BOOST_INTRUSIVE_DETAIL_ALGO_TYPE_HPP

/* algo_type.hpp
K2YMmDFgxoAZQ+lnDOv1aTfNGFDRttQxgciyfPmjAsoEt8sdFShTeFvd+ULaOn5FThIQAVc6As7D9Jfb8kdVyc0SLUBlXZVNOFanYb5hvmG+Yb4rar6jqvVmcd1R4TfNR5g3fwVV5aCt9KhsxBeQ8XGw7YvEFv+t5IQZuYBPtWf6+GK2GW9pFojANeCa7eAaed9lj+GaxOi9ypyh+qLyBkrBGjPYZvtmNmkDjRWd54CzwFngrLLMkBLqim17EckIokCVZfDDds1p0hZkAllkJAsUoAWdbDedVNEzKh8PYdIClqmyU5OyJgkoB1MfkBJIqRhS8v5GdgxWrMESarKEGg7SIktUcKICrgHXgGvUm5EER8iOwUoz2KZqbKPczGaFbbZtngPOAmeBs1SeIUVuHs42K6rMLlc521iLdsWwdVXi1tWqT3mi6UPCNAckBBICCWEOw2UXVGXIRKr/xcg1KOMBGqrOXEj+9iiQGcgMZFY+MlNpTsW+b6pM7KMMg+BbkiCOasyCOG2oAotwZxF89Q88U02egZNVCYLCNAf0k0Q/qvpH0rdggYswWQJbga0i2Yp5b1aZWAUL7KCPatGHKr6W5E1bICGQEEgIcxguu7kqQyZYGAcNbRENKTgXkr/NC2QGMgOZlY/M8s2p
*/