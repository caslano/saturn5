//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2008-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_CONTAINERS_FLAT_SET_HPP
#define BOOST_INTERPROCESS_CONTAINERS_FLAT_SET_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/container/flat_set.hpp>
#include <boost/interprocess/containers/containers_fwd.hpp>

namespace boost {
namespace interprocess {

using boost::container::flat_set;
using boost::container::flat_multiset;

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif //   #ifndef  BOOST_INTERPROCESS_CONTAINERS_FLAT_SET_HPP

/* flat_set.hpp
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
*/