//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//! \file

#ifndef BOOST_MOVE_DETAIL_ITERATOR_TRAITS_HPP
#define BOOST_MOVE_DETAIL_ITERATOR_TRAITS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <cstddef>
#include <boost/move/detail/type_traits.hpp>

#include <boost/move/detail/std_ns_begin.hpp>
BOOST_MOVE_STD_NS_BEG

struct input_iterator_tag;
struct forward_iterator_tag;
struct bidirectional_iterator_tag;
struct random_access_iterator_tag;
struct output_iterator_tag;

BOOST_MOVE_STD_NS_END
#include <boost/move/detail/std_ns_end.hpp>

namespace boost{  namespace movelib{

template<class Iterator>
struct iterator_traits
{
   typedef typename Iterator::difference_type   difference_type;
   typedef typename Iterator::value_type        value_type;
   typedef typename Iterator::pointer           pointer;
   typedef typename Iterator::reference         reference;
   typedef typename Iterator::iterator_category iterator_category;
   typedef typename boost::move_detail::make_unsigned<difference_type>::type size_type;
};

template<class T>
struct iterator_traits<T*>
{
   typedef std::ptrdiff_t                    difference_type;
   typedef T                                 value_type;
   typedef T*                                pointer;
   typedef T&                                reference;
   typedef std::random_access_iterator_tag   iterator_category;
   typedef typename boost::move_detail::make_unsigned<difference_type>::type size_type;
};

template<class T>
struct iterator_traits<const T*>
{
   typedef std::ptrdiff_t                    difference_type;
   typedef T                                 value_type;
   typedef const T*                          pointer;
   typedef const T&                          reference;
   typedef std::random_access_iterator_tag   iterator_category;
   typedef typename boost::move_detail::make_unsigned<difference_type>::type size_type;
};

}} //namespace boost {  namespace movelib{

#endif //#ifndef BOOST_MOVE_DETAIL_ITERATOR_TRAITS_HPP

/* iterator_traits.hpp
/Ar5QyU4uujJ8cJoCtam0n9VNe4qPcXQ/ynseaSKF8aHvEbRzuW8KAd8CAAlsvAW59F74TYK/Pg4ATdtwTZjjvP9vpbiYPsiwna/8ySH2QSCqOpGIghrp4E4gSFSBEIPpjK9qcEQ8gZiC1/nA0ZV7F3i47DNtLthmgo/EFlsva/bgUjHHn0J718UIj3tuIDGB1lsjLQ+SDFHAHdp9rlxXcp3d0n1BKG0TCgEIEMY3688EnmsvTx7YRxvZW4Mms0yAsNn8U3JUp/9hYLFJxmL22n/fpmAxd3nyP5Nq9pR39AgdRfaj6dxv9hSgvtlYuB8B/b0wfw4+p8w9v+RjdLDLHUCXJEpZkp05WaWvhURHx3950VU/91HcP10Lj+Mc/PBsW51TFZ4knPofzmldTHyTf0VFzn3kUEygUF7w6w4EtUtfKhea9Npaj3TZGqP5RY//gG+uawmeHJ5EeG99Pir41SP9Y2lS/gorpKP9R9Ipw9mCVD/peZHxMBfCMpdxtq/afsHK8G+whvtryKpTtX5JEXXeLKXvzIG3ilvWX+s7psnMwd7LevWfKrmV0USZS3WBzvDnFQod8oU6fx2RqTf/hgUpY42DVpspj2HD5kt3tJqPbQXxKz8gRsXTcu/Sa8m7Z8uBfSkD0L9dofvuXmZn1IJAT7MACsrmp5G2MaHm6VNiUAOcSoV+EYX+i9j5177OI/DbByXxGzEJOdEmZ9NwYIcd/WpFNSO0p2U7cszHg5N5jsImUAL86d31+gfunfXoXp6cszjjgI33GIUtM7HWNuLHBX+iV4AcIi1j5+s1RjMB/yQMBCezhB8CcmR18lVO/GvLnD276myS3vZf2fvWsDjqorwvpLcptvuDaR0LQECTaGY8pBUrAS0rV0MtYtJJIBCFQXqdaHIYxcKNCklDXS7DRSlWrQoSFFQ0KqlD2xLC7UtWCTVqFWDBgxwwwYNGu0CW+L8M/e1ryZFqC82327uPc85c+bMmTNnzpyrLssYv++JnGuO3zk0fqd9yhQnRvEEUW6M1WHxi9mXmvRy3OkmCWiwOMlo1uVnm82yWIFiioZlhKwhzXQs+eSVS8D/juf1jTFnRz/FvuoVMQqQc8Vpw8Wfjxmsyjyo3Csyac5sFdRWOWYrjVBy4ieFpd09XFoy7YcunFLwPJB+DE3g2ee5/JcPfd71pMb890sqhjr1jllnjVfpcAStH8VI9kgNITRaPy7rZm2RvE6V16Gp04HvZpK7TXsFQ28HGgoswoY3D2qSx8QALUhJks+zCEtuF2LzeLZT3bGPU7cjKG34i0zDE5k7CSW68TItqN2HHtj2gjEDnM6Dyy+b/Zgm2VRJ5OZTpTPxzOSl8NhX4jOlYTADS0O4gugTJJronUW890Dmkv3iYy5kb+HsNxh4kXn+k4IMV2wST/h+UrMb0pfTZDLLRbFqQpmKTEDrZdL+ENsoAT/A6L2R4xElStjxH9v3llxEW+P14c/a/UmqfWyWmjt3DHc5hHoTdckXWUlXzkq6NCvl6JFdYfphZ1zGS3uVQq0ca4YUNbL0n4DH0vnBe52YdIj9XGwUfGuYVmfXZiD8YkE48Cx+TWPjkDgKj2GmxSk9ss/0ck6rmmnLOa2f0/rttH6k5QDxlZf86vAas7/2nXGRjW9Bswm2Y9C8aA0aeE92AG8ucqT9oxxoHoKgMX+VgWygYbj6UmvWyJV/SC6PnIKUmCjqJKVTl3IOwIRfQ6dBLNkOQXWAmCB5MOQRqQJGe4EVpFZTSuTjQbxFBvFbXKLa/P/Tzv15y+hZsYRNhb1FCY/Cvothzh+tZzlkFBII3kuTuDDNeJkZ1LZbHAjK80c/ypiQlZnZgdhMShk=
*/