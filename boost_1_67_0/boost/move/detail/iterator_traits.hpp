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
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
*/