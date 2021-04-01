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
SOqeL9FkCh8Rkhi9QEh2xiSYAtQPnedPqvXdzeCII5PZXEgnOYwn7SkEmUIGvIgyl57o3PURnYrc5fTSJCwIZHwuSDV5iliVHADnDS9JhHjGqVELjtQ7mKqS1cb1cZ9SopznyIDf5S4bM0TG/dPmuaGwNFgEfwFKnrHg8Kt90AQQcG6yW/hclCvngpK0DGNLshK1xzxr+GRy/lHNja6gdvH36jNIjtTHfflLi9RBb7HoExRfGyyKiOucDcHeorSY33B9HPxARWhYLlXKnqUI5sTzh2hLHki551/KOh9kzLegHY29j6nWPuRVhM05Gg+K/UgUVDo1xYBpDWlKbowrPc8DYtXzLCmZjbu6j7x0l4+P1gybm8yOMxNC4Abtq8ki57nHg3mbTLzZT7lV+ZE9CXcM6TuMqxp/QaqxxQgLfGGoV+G8qbcseFgOsrSqbXrt4M6KiHDjL7XqlTQjC+bIq1kCaZAVYUMQIpHMywD2t//QYcrkvI//ZiH42lX+3jS6ytJHupE0Uy5/qjRzZJK8Qxe2CsK2hAtsFA8HcMY5q6pqfK3vxgYOKbAf9w==
*/