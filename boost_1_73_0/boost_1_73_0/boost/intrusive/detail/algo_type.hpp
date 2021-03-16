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
3wMz93Trvbnll9uAmdhX4NzKG302/Vtg7u8Xn29PoviMSmOWwI124UvDDb42xGAfDo//Pg6Ab8AIg306RuBGufD9BXw9gwY7nhf/fdDXzybnG2xLSODc7N31eH47Cgx2WmF8vkzUL2uBeWCawA104aPviVwxA7gL4vPRjy60LzHY/D8KXGcXvi9xOXSRwYZeEv/5PZwMOweY4XMFLseF7wbcx32VBgtVCVwbF74XcR9NwKwJx7/fMJ7ztEUGe3E=
*/