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
using boost::movelib::iter_difference;
using boost::movelib::iter_value;
using boost::movelib::iter_category;
using boost::movelib::iter_size;


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

////////////////////////////////////////////////////////////////////////////////
//    Conversion from boost::iterator traversals to std tags
////////////////////////////////////////////////////////////////////////////////

template<class Tag>
struct get_std_category_from_tag
{
   typedef Tag type;
};

template <class Category>
struct get_std_category_from_tag
   <boost::iterators::detail::iterator_category_with_traversal
      <Category, boost::iterators::incrementable_traversal_tag> >
{
   typedef std::input_iterator_tag type;
};

template <class Category>
struct get_std_category_from_tag
   <boost::iterators::detail::iterator_category_with_traversal
      <Category, boost::iterators::single_pass_traversal_tag> >
{
   typedef std::input_iterator_tag type;
};

template <class Category>
struct get_std_category_from_tag
   <boost::iterators::detail::iterator_category_with_traversal
      <Category, boost::iterators::forward_traversal_tag> >
{
   typedef std::input_iterator_tag type;
};

template <class Category>
struct get_std_category_from_tag
   <boost::iterators::detail::iterator_category_with_traversal
      <Category, boost::iterators::bidirectional_traversal_tag> >
{
   typedef std::bidirectional_iterator_tag type;
};

template <class Category>
struct get_std_category_from_tag
   <boost::iterators::detail::iterator_category_with_traversal
      <Category, boost::iterators::random_access_traversal_tag> >
{
   typedef std::random_access_iterator_tag type;
};

template<class It>
struct get_std_category_from_it
   : get_std_category_from_tag< typename boost::intrusive::iter_category<It>::type >
{};

////////////////////////////////////////
//    iterator_[dis|en]able_if_tag
////////////////////////////////////////
template<class I, class Tag, class R = void>
struct iterator_enable_if_tag
   : ::boost::move_detail::enable_if_c
      < ::boost::move_detail::is_same
         < typename get_std_category_from_it<I>::type
         , Tag
         >::value
         , R>
{};

template<class I, class Tag, class R = void>
struct iterator_disable_if_tag
   : ::boost::move_detail::enable_if_c
      < !::boost::move_detail::is_same
         < typename get_std_category_from_it<I>::type
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
         < typename get_std_category_from_it<I>::type
         , Tag
         >::value &&
        !::boost::move_detail::is_same_or_convertible
         < typename get_std_category_from_it<I>::type
         , Tag2
         >::value
         , R>
{};

////////////////////////////////////////
//    iterator_[dis|en]able_if_tag_difference_type
////////////////////////////////////////
template<class I, class Tag>
struct iterator_enable_if_tag_difference_type
   : iterator_enable_if_tag<I, Tag, typename boost::intrusive::iter_difference<I>::type>
{};

template<class I, class Tag>
struct iterator_disable_if_tag_difference_type
   : iterator_disable_if_tag<I, Tag, typename boost::intrusive::iter_difference<I>::type>
{};

////////////////////
//    advance
////////////////////

template<class InputIt>
BOOST_INTRUSIVE_FORCEINLINE typename iterator_enable_if_tag<InputIt, std::input_iterator_tag>::type
   iterator_advance(InputIt& it, typename iter_difference<InputIt>::type n)
{
   while(n--)
      ++it;
}

template<class InputIt>
typename iterator_enable_if_tag<InputIt, std::forward_iterator_tag>::type
   iterator_advance(InputIt& it, typename iter_difference<InputIt>::type n)
{
   while(n--)
      ++it;
}

template<class InputIt>
BOOST_INTRUSIVE_FORCEINLINE typename iterator_enable_if_tag<InputIt, std::bidirectional_iterator_tag>::type
   iterator_advance(InputIt& it, typename iter_difference<InputIt>::type n)
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

template<class It>
BOOST_INTRUSIVE_FORCEINLINE 
   void iterator_uadvance(It& it, typename iter_size<It>::type n)
{
   (iterator_advance)(it, (typename iterator_traits<It>::difference_type)n);
}

////////////////////////////////////////
//    iterator_distance
////////////////////////////////////////
template<class InputIt> inline
typename iterator_disable_if_tag_difference_type
   <InputIt, std::random_access_iterator_tag>::type
      iterator_distance(InputIt first, InputIt last)
{
   typename iter_difference<InputIt>::type off = 0;
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
   typename iter_difference<InputIt>::type off = last - first;
   return off;
}

////////////////////////////////////////
//    iterator_udistance
////////////////////////////////////////

template<class It>
BOOST_INTRUSIVE_FORCEINLINE typename iter_size<It>::type
   iterator_udistance(It first, It last)
{
   return (typename iter_size<It>::type)(iterator_distance)(first, last);
}

////////////////////////////////////////
//    iterator_next
////////////////////////////////////////

template<class InputIt>
BOOST_INTRUSIVE_FORCEINLINE InputIt iterator_next(InputIt it, typename iter_difference<InputIt>::type n)
{
   (iterator_advance)(it, n);
   return it;
}

template<class InputIt>
BOOST_INTRUSIVE_FORCEINLINE InputIt iterator_unext(InputIt it, typename iterator_traits<InputIt>::size_type n)
{
   (iterator_uadvance)(it, n);
   return it;
}

////////////////////////////////////////
// iterator_arrow_result
////////////////////////////////////////

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