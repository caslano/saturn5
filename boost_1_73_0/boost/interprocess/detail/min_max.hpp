//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_MIN_MAX_HPP
#define BOOST_INTERPROCESS_DETAIL_MIN_MAX_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

namespace boost {
namespace interprocess {

template<class T>
const T &max_value(const T &a, const T &b)
{  return a > b ? a : b;   }

template<class T>
const T &min_value(const T &a, const T &b)
{  return a < b ? a : b;   }

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_DETAIL_MIN_MAX_HPP


/* min_max.hpp
92l1G+3roBzJCcaeyihYlrzAjmJFCEiEACJ8DxFUA2jW3Plkbpm5WzU+SaAhN2R+7mf8JO+EwuY7n+Enuc8ImVf+1Arltrd5mjAdQ0hFN6noB5ULS1atGXlb+ekF+PSGVpSZV/yYETt+auSvROXKVb7EE0GvkaMD51ICP0pgrJUEnkcC7L4Oqdi8y9kn8v+nqmqc9E3uw7NOE88grTuu1kwcEH4/fWFQ9kGf5m72NwEJYaRg
*/