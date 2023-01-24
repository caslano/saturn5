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
y9TvdxN2EkF4/bg8eB6c57tDHUW5rV9ZDl7j50RJJ5MB7C/eZw77vjk5O6m5cVeHTrWWvKtYRi0sEuPgCzwGaIfqlt0Eebet/dLUctAVbf5gAGI9wc3za3IJ9Ug3q0SABgj8W/TufHrWHwj3SgqMZEgjA4gqilh7DmtLX0h3dSMpgIi/NL5XpJJBC1TBOYk1Z90GTKm37/iA77zv73MZy5YzOzrDHAppk0Hd3Xv14aCUwTHST4+XIuPPD0rjxjdPr2E+NOo3zaEAgtfXZXyFt4sJtIpUciiDuH/WYL485Fbj+XnOf+gq+9nevq0yXBh/kiet8DltByrx5Pi3lC6wWYui8reUzvp/I+KcfP8dEUdx+rbkDhaUkxX3gx95E8EIQvgMv5qSgLlLeS5jZAfPnojw+U8dOQzrjYXqNtIQxQ1Bag/1Ui0Ynn2es6/n6U0ckSXOu0XHVNctHA5ZcqttOcqZxw0cmnZlSmhICQKxGkhrrhedjp6NlcIVPqsWNI9T3pcBU0LgdVeQEPhi47H5kpHguXNJGwo/OwszEoR4LZ6eNhuOLEn/R1/CPeK117pNHJT+Xb3YGNOqwWF8nv9wJmtJEJgXmJdgIiz2qRc2OAw+GglPARvTrPKb+L3M7GpACgRQaoZZRARDvI6Z54n0MmfY22DNt0/9ILg2GD2IIvmqX9fOhrsU83DWSQz5dOgClV9JRWTCDDMaM+p9
*/