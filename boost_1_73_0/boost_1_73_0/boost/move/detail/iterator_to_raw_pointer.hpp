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
QMYSPNOwfIBh88JmrhmQsug7gGdRcRTpGimZis8L5ELDqEGWStOR3Dp9r2x0GKcmDEDefUbyuUThsvRHaHc8uPR061zDo1wUx+tTA8cyO7tRa+RrmF3Lut6NWSNfw2w5ztApC2gHcq+D+JdxHetifPUaLwqD3QLsYeos5zXkpcV/sSMYOxvesS096kBzluKfzkwXQ6n4zVSYsEDk8+XUqnkNxrZ9tmTKUwG6Gx4Wze57eWyAhTiskmzr4Cgbq0GXxxBd/4/QzR/pv1BLAwQKAAAACAAtZ0pSR3+PxF4FAADCDQAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE0MDFVVAUAAbZIJGClV/tv4jgQ/t0S/8OIvdW2CBqoetItS5FSGgpXCigJ3cfphNJgwLshjhKnPe7xv9+MzauPu021kUpie+bz+PP4G7eleKbCIONt1hLxXOLrG18/yHSWtVnP98f6B64c33xcBJkIIcjV0rQzriCU8pvgzLwyVqtF4i7M04i1rD1WyzLw7A14PL3naS0TM85aKU+iNQ7PAhWYGa3GSQNO63UYXbPLQPEm+Mu8Cqfv4dc8ooFfoHHWPHvfRJOrG58ZuCbQSmqZbljz4BtnHRkrHqvagMcLtWxCfdfjrxNO
*/