//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2008-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_CONTAINERS_STABLE_VECTOR_HPP
#define BOOST_INTERPROCESS_CONTAINERS_STABLE_VECTOR_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/container/stable_vector.hpp>
#include <boost/interprocess/containers/containers_fwd.hpp>

namespace boost {
   namespace interprocess {

      using boost::container::stable_vector;

   }  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif //   #ifndef  BOOST_INTERPROCESS_CONTAINERS_STABLE_VECTOR_HPP

/* stable_vector.hpp
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
*/