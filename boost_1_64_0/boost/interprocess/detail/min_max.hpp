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
yJB4hoSTiwt48+kXFSbvZmVoMojKyrehlmWhmOhPMw8sUqtYQcg9n9w79Qt+lRfri0V3qByGF89d3gbbfxKQAZ4wY5LS3RMV2lCrxEEYjIuBgtwQ6ApZ9tdMluEoyBDPiVF1y+zwHgq1KcW2iXopJas/iZ/2t4RBkOifVJLB6f3xx6glxQQ2bYkpODC8uvQrFivQUT/TTCispHVIy1pghQIbzJmXBP9VDJh+N1p/KwjlvZEfCGtt9WReu+rkQBAc+B3KvpFeGzrYohsV0XAUlPOR472/TtrX6aeDpSTfctq6Lcn9QVZkJ6KjU6PL8idxR/sH++BQN9sL5/x5X4OTvvQvtoy9CJH8NH0q+hwhyzll+I6CnXy1ropfhHcS6eKD6hDmxtM1UwfyJW3E1ZK2BqDhSeB4IUebaOdt7o0y+4mwBfH2HSo7Rn0alAkAG4m9a2W2xVLX6TcXnxPLdBeHa3t5KZGcXLfPWUHTujQjXVCMSRe7mz/cRdtKslihwiiC3LxBS+sOhudRoo1QdxbHI9H6HEuKAS5EZTarqDiW1ucIlITSShvDnmmpSw==
*/