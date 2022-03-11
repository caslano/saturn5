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

#ifndef BOOST_INTRUSIVE_DETAIL_ITERATOR_HPP
#define BOOST_INTRUSIVE_DETAIL_ITERATOR_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <cstddef>
#include <boost/intrusive/detail/std_fwd.hpp>
#include <boost/intrusive/detail/workaround.hpp>
#include <boost/move/detail/iterator_traits.hpp>
#include <boost/move/detail/meta_utils_core.hpp>

namespace boost{
namespace iterators{

struct incrementable_traversal_tag;
struct single_pass_traversal_tag;
struct forward_traversal_tag;
struct bidirectional_traversal_tag;
struct random_access_traversal_tag;

namespace detail{

template <class Category, class Traversal>
struct iterator_category_with_traversal;

} //namespace boost{
} //namespace iterators{
} //namespace detail{

namespace boost {
namespace intrusive {

using boost::movelib::iterator_traits;

////////////////////
//    iterator
////////////////////
template<class Category, class T, class Difference, class Pointer, class Reference>
struct iterator
{
   typedef Category     iterator_category;
   typedef T            value_type;
   typedef Difference   difference_type;
   typedef Pointer      pointer;
   typedef Reference    reference;
};

////////////////////////////////////////
//    iterator_[dis|en]able_if_boost_iterator
////////////////////////////////////////
template<class I>
struct is_boost_iterator
{
   static const bool value = false;
};

template<class Category, class Traversal>
struct is_boost_iterator< boost::iterators::detail::iterator_category_with_traversal<Category, Traversal> >
{
   static const bool value = true;
};

template<class I, class R = void>
struct iterator_enable_if_boost_iterator
   : ::boost::move_detail::enable_if_c
      < is_boost_iterator<typename boost::intrusive::iterator_traits<I>::iterator_category >::value
      , R>
{};

////////////////////////////////////////
//    iterator_[dis|en]able_if_tag
////////////////////////////////////////
template<class I, class Tag, class R = void>
struct iterator_enable_if_tag
   : ::boost::move_detail::enable_if_c
      < ::boost::move_detail::is_same
         < typename boost::intrusive::iterator_traits<I>::iterator_category 
         , Tag
         >::value
         , R>
{};

template<class I, class Tag, class R = void>
struct iterator_disable_if_tag
   : ::boost::move_detail::enable_if_c
      < !::boost::move_detail::is_same
         < typename boost::intrusive::iterator_traits<I>::iterator_category 
         , Tag
         >::value
         , R>
{};

////////////////////////////////////////
//    iterator_[dis|en]able_if_tag
////////////////////////////////////////
template<class I, class Tag, class Tag2, class R = void>
struct iterator_enable_if_convertible_tag
   : ::boost::move_detail::enable_if_c
      < ::boost::move_detail::is_same_or_convertible
         < typename boost::intrusive::iterator_traits<I>::iterator_category 
         , Tag
         >::value &&
        !::boost::move_detail::is_same_or_convertible
         < typename boost::intrusive::iterator_traits<I>::iterator_category 
         , Tag2
         >::value
         , R>
{};

////////////////////////////////////////
//    iterator_[dis|en]able_if_tag_difference_type
////////////////////////////////////////
template<class I, class Tag>
struct iterator_enable_if_tag_difference_type
   : iterator_enable_if_tag<I, Tag, typename boost::intrusive::iterator_traits<I>::difference_type>
{};

template<class I, class Tag>
struct iterator_disable_if_tag_difference_type
   : iterator_disable_if_tag<I, Tag, typename boost::intrusive::iterator_traits<I>::difference_type>
{};

////////////////////
//    advance
////////////////////

template<class InputIt, class Distance>
BOOST_INTRUSIVE_FORCEINLINE typename iterator_enable_if_tag<InputIt, std::input_iterator_tag>::type
   iterator_advance(InputIt& it, Distance n)
{
   while(n--)
      ++it;
}

template<class InputIt, class Distance>
typename iterator_enable_if_tag<InputIt, std::forward_iterator_tag>::type
   iterator_advance(InputIt& it, Distance n)
{
   while(n--)
      ++it;
}

template<class InputIt, class Distance>
BOOST_INTRUSIVE_FORCEINLINE typename iterator_enable_if_tag<InputIt, std::bidirectional_iterator_tag>::type
   iterator_advance(InputIt& it, Distance n)
{
   for (; 0 < n; --n)
      ++it;
   for (; n < 0; ++n)
      --it;
}

template<class InputIt, class Distance>
BOOST_INTRUSIVE_FORCEINLINE typename iterator_enable_if_tag<InputIt, std::random_access_iterator_tag>::type
   iterator_advance(InputIt& it, Distance n)
{
   it += n;
}

template<class InputIt, class Distance>
BOOST_INTRUSIVE_FORCEINLINE typename iterator_enable_if_convertible_tag
   <InputIt, const boost::iterators::incrementable_traversal_tag&, const boost::iterators::single_pass_traversal_tag&>::type
   iterator_advance(InputIt& it, Distance n)
{
   while(n--)
      ++it;
}

template<class InputIt, class Distance>
BOOST_INTRUSIVE_FORCEINLINE typename iterator_enable_if_convertible_tag
   <InputIt, const boost::iterators::single_pass_traversal_tag &, const boost::iterators::forward_traversal_tag&>::type
   iterator_advance(InputIt& it, Distance n)
{
   while(n--)
      ++it;
}

template<class InputIt, class Distance>
BOOST_INTRUSIVE_FORCEINLINE typename iterator_enable_if_convertible_tag
   <InputIt, const boost::iterators::forward_traversal_tag&, const boost::iterators::bidirectional_traversal_tag&>::type
   iterator_advance(InputIt& it, Distance n)
{
   while(n--)
      ++it;
}

template<class InputIt, class Distance>
BOOST_INTRUSIVE_FORCEINLINE typename iterator_enable_if_convertible_tag
   <InputIt, const boost::iterators::bidirectional_traversal_tag&, const boost::iterators::random_access_traversal_tag&>::type
   iterator_advance(InputIt& it, Distance n)
{
   for (; 0 < n; --n)
      ++it;
   for (; n < 0; ++n)
      --it;
}

class fake{};

template<class InputIt, class Distance>
BOOST_INTRUSIVE_FORCEINLINE typename iterator_enable_if_convertible_tag
   <InputIt, const boost::iterators::random_access_traversal_tag&, const fake&>::type
   iterator_advance(InputIt& it, Distance n)
{
   it += n;
}

////////////////////
//    distance
////////////////////
template<class InputIt> inline
typename iterator_disable_if_tag_difference_type
   <InputIt, std::random_access_iterator_tag>::type
      iterator_distance(InputIt first, InputIt last)
{
   typename iterator_traits<InputIt>::difference_type off = 0;
   while(first != last){
      ++off;
      ++first;
   }
   return off;
}

template<class InputIt>
BOOST_INTRUSIVE_FORCEINLINE typename iterator_enable_if_tag_difference_type
   <InputIt, std::random_access_iterator_tag>::type
      iterator_distance(InputIt first, InputIt last)
{
   typename iterator_traits<InputIt>::difference_type off = last - first;
   return off;
}

template<class I>
BOOST_INTRUSIVE_FORCEINLINE typename iterator_traits<I>::pointer iterator_arrow_result(const I &i)
{  return i.operator->();  }

template<class T>
BOOST_INTRUSIVE_FORCEINLINE T * iterator_arrow_result(T *p)
{  return p;   }

} //namespace intrusive
} //namespace boost

#endif //BOOST_INTRUSIVE_DETAIL_ITERATOR_HPP

/* iterator.hpp
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
*/