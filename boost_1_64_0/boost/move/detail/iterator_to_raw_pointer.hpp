//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_MOVE_DETAIL_ITERATOR_TO_RAW_POINTER_HPP
#define BOOST_MOVE_DETAIL_ITERATOR_TO_RAW_POINTER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/move/detail/iterator_traits.hpp>
#include <boost/move/detail/to_raw_pointer.hpp>
#include <boost/move/detail/pointer_element.hpp>

namespace boost {
namespace movelib {
namespace detail {

template <class T>
inline T* iterator_to_pointer(T* i)
{  return i; }

template <class Iterator>
inline typename boost::movelib::iterator_traits<Iterator>::pointer
   iterator_to_pointer(const Iterator &i)
{  return i.operator->();  }

template <class Iterator>
struct iterator_to_element_ptr
{
   typedef typename boost::movelib::iterator_traits<Iterator>::pointer  pointer;
   typedef typename boost::movelib::pointer_element<pointer>::type      element_type;
   typedef element_type* type;
};

}  //namespace detail {

template <class Iterator>
inline typename boost::movelib::detail::iterator_to_element_ptr<Iterator>::type
   iterator_to_raw_pointer(const Iterator &i)
{
   return ::boost::movelib::to_raw_pointer
      (  ::boost::movelib::detail::iterator_to_pointer(i)   );
}

}  //namespace movelib {
}  //namespace boost {

#endif   //#ifndef BOOST_MOVE_DETAIL_ITERATOR_TO_RAW_POINTER_HPP

/* iterator_to_raw_pointer.hpp
gKXqtby+82hxV8MOdwoNQp0kHbnCfpehSmydud2cruXyOw6hdAWdpqal93RLM3RL0d7syVcb9iGQIJv9tu/8reycVuynnrKf/IVWyl61Wb5eKLEW2BEYcRwsH16xS//CVlAsrA+rMp6e3pXwfVnC9/UJ33clfA/uif8eS3g/JP69K9KEe+M29h6vmvB3b79AxSfaF/bBEYGT+v2kI0+VTlUUklBbWJAsSArBb1OtpJhkD4y2N0FfY2JtXmjPkwBh4kpCLB6MzG301Fi/sRAwgxg/gmH2cSIbuyPU+zVF1Ss70uRwjJcAQvtVQajIQci4SXZ+WkjzVzccEsxAKmVDh9jsmY/96M8uqpsS5P6zFpqJx/gOGRm4zgHZ5OzzEfQs+tE6zuu/Daad1wSCK/Orl8BvqD/93xDxRke4GOIgZ2EN4j7F0SloBCw2DdBZweMLmgCeQd+iAdYvsNnOojVqLcGnB4T9+Wq23tlHU8tLS7hDxUeIaexa7sxmjk6wxtdWDBHb6BYzVP3R45xOE1wgOBz59wkWtnMPmVbfcbW6xLT6DKOhtqkocTWj84IlvWnyntkj1D6QWlSTucY7PK+uHWKs1Ea300s6IHlZ9bP+0OggO+rmokVK/FIU+/otRlIMZ5Ms0X7WukZL/3mWLt0t7BMhqV1gL+nwLzyMWvFj+H3rBn1EnTpPnUNN3tf2xp8POQnfAyz/mmvWa3LoJEJn9uWHshCijQoibBwFIaPOj0k0zW0fk39tdHN5q69nrvvEOVoisek450IB39wrnAsFsaHLjUijdF4WyUTCh1uraDx4jTgMt58jN4sj8FTO6ZXntOKcTrpf9L7C8NvhEFcWHmo/s8B1zUCnj7SHjRJJ/Dif/U4BfSTGYryfHfp9hCzRmACS5WMD+UJbOE/uRNlS7TjrEVmBheGD11mw/OuHRv51eaPyrwDLv8DHifxLgpMIznx86v8j8Gtj8evJfnMSy7/KmrJXWZckj1l7RXPymDLAO/rfspb0ZWe9H98f+zSNnw8vbUx+uBnv7T+sbKq/Jxca+5/k8rCHTGiveyGPv8n6pp6WNP7i5sb/YkGS/Uez8LVFcfrvlS3Joy4qiNN/twh/7CiNj1vmNIaPOfvi8REAvP2jFU3ho3pkkv1DpLnxrR8Zp/9d0UJ/FdNjvk+/O8gPnPhJDV1O2NM/6L7m9HNEpvbeEdjh8VegjtG2AoG6dQPNx/+gpWMv/T4ytYsGcAidklp4no1zYhQHNauD0DeS2dBlLHUJ6qOUZiN3AB/P0wF39kZfStz5dTba64j2jNIIhxKfRZns5AcWg56VFQSarJ3rs1bf1j9o7zlJSW2fpOHoeWzO/52Whn3jUaZ9Rls6a5+blvw79t2QdsXrv+e44y2NzvPTxWK8B2okWm3hC8MXhIfbwQvM/YXewBXAAp+jhD8BdYuy5J3HvhEqUnMPK0Rl+abGgL2jOO6w72tNNi/HcXN3T9fNdUErvyP/ZrdO9iirKKHAHClgnaafs6zUnsrtsBaYa0AYtEKW7TPDygxtgB3Lz7cfbmMCTiBGonVSn5QgFnABrRbWGtdy0BEOTtKBBRGHteH5ig5CuP3xAcVO62ihQ9rhrd/ksYyu5A7EJB5Jgcx9ZZ5GVA/rYjOmC3hMd5zPY4oqBUQH5uhvkVjSB0XJvp0fs//yyeDc9gx39kMn2Q+aSAdM2JSp4vvI/tu1L4wL4aHoLxu6TCA0MxtMWSd6WZ0NLmaELyRc3PATzULCgAGJL+0+J/C2+cb8o+P/R8ytPW6Ys5/8diXdm9xu6ueb5GzQ7tZJTrZxfsWDZC7rTZ2QsZXOC6UWn8SngB+EfWKwzM9v6EjjkPA=
*/