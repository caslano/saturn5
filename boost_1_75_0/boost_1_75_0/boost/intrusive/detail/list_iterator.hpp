/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Olaf Krzikalla 2004-2006.
// (C) Copyright Ion Gaztanaga  2006-2013
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_LIST_ITERATOR_HPP
#define BOOST_INTRUSIVE_LIST_ITERATOR_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/workaround.hpp>
#include <boost/intrusive/detail/std_fwd.hpp>
#include <boost/intrusive/detail/iiterator.hpp>
#include <boost/intrusive/detail/mpl.hpp>

namespace boost {
namespace intrusive {

// list_iterator provides some basic functions for a
// node oriented bidirectional iterator:
template<class ValueTraits, bool IsConst>
class list_iterator
{
   private:
   typedef iiterator
      <ValueTraits, IsConst, std::bidirectional_iterator_tag> types_t;

   static const bool stateful_value_traits =                types_t::stateful_value_traits;

   typedef ValueTraits                                      value_traits;
   typedef typename types_t::node_traits                    node_traits;

   typedef typename types_t::node                           node;
   typedef typename types_t::node_ptr                       node_ptr;
   typedef typename types_t::const_value_traits_ptr         const_value_traits_ptr;
   class nat;
   typedef typename
      detail::if_c< IsConst
                  , list_iterator<value_traits, false>
                  , nat>::type                              nonconst_iterator;

   public:
   typedef typename types_t::iterator_type::difference_type    difference_type;
   typedef typename types_t::iterator_type::value_type         value_type;
   typedef typename types_t::iterator_type::pointer            pointer;
   typedef typename types_t::iterator_type::reference          reference;
   typedef typename types_t::iterator_type::iterator_category  iterator_category;

   BOOST_INTRUSIVE_FORCEINLINE list_iterator()
   {}

   BOOST_INTRUSIVE_FORCEINLINE explicit list_iterator(const node_ptr & nodeptr, const const_value_traits_ptr &traits_ptr)
      : members_(nodeptr, traits_ptr)
   {}

   BOOST_INTRUSIVE_FORCEINLINE list_iterator(const list_iterator &other)
      :  members_(other.pointed_node(), other.get_value_traits())
   {}

   BOOST_INTRUSIVE_FORCEINLINE list_iterator(const nonconst_iterator &other)
      :  members_(other.pointed_node(), other.get_value_traits())
   {}

   BOOST_INTRUSIVE_FORCEINLINE list_iterator &operator=(const list_iterator &other)
   {  members_.nodeptr_ = other.members_.nodeptr_;  return *this;  }

   BOOST_INTRUSIVE_FORCEINLINE node_ptr pointed_node() const
   { return members_.nodeptr_; }

   BOOST_INTRUSIVE_FORCEINLINE list_iterator &operator=(const node_ptr &node)
   {  members_.nodeptr_ = node;  return *this;  }

   BOOST_INTRUSIVE_FORCEINLINE const_value_traits_ptr get_value_traits() const
   {  return members_.get_ptr(); }

   public:
   BOOST_INTRUSIVE_FORCEINLINE list_iterator& operator++()
   {
      node_ptr p = node_traits::get_next(members_.nodeptr_);
      members_.nodeptr_ = p;
      return static_cast<list_iterator&> (*this);
   }

   BOOST_INTRUSIVE_FORCEINLINE list_iterator operator++(int)
   {
      list_iterator result (*this);
      members_.nodeptr_ = node_traits::get_next(members_.nodeptr_);
      return result;
   }

   BOOST_INTRUSIVE_FORCEINLINE list_iterator& operator--()
   {
      members_.nodeptr_ = node_traits::get_previous(members_.nodeptr_);
      return static_cast<list_iterator&> (*this);
   }

   BOOST_INTRUSIVE_FORCEINLINE list_iterator operator--(int)
   {
      list_iterator result (*this);
      members_.nodeptr_ = node_traits::get_previous(members_.nodeptr_);
      return result;
   }

   BOOST_INTRUSIVE_FORCEINLINE friend bool operator== (const list_iterator& l, const list_iterator& r)
   {  return l.pointed_node() == r.pointed_node();   }

   BOOST_INTRUSIVE_FORCEINLINE friend bool operator!= (const list_iterator& l, const list_iterator& r)
   {  return !(l == r); }

   BOOST_INTRUSIVE_FORCEINLINE reference operator*() const
   {  return *operator->();   }

   BOOST_INTRUSIVE_FORCEINLINE pointer operator->() const
   { return this->operator_arrow(detail::bool_<stateful_value_traits>()); }

   BOOST_INTRUSIVE_FORCEINLINE list_iterator<ValueTraits, false> unconst() const
   {  return list_iterator<ValueTraits, false>(this->pointed_node(), this->get_value_traits());   }

   private:
   BOOST_INTRUSIVE_FORCEINLINE pointer operator_arrow(detail::false_) const
   { return ValueTraits::to_value_ptr(members_.nodeptr_); }

   BOOST_INTRUSIVE_FORCEINLINE pointer operator_arrow(detail::true_) const
   { return this->get_value_traits()->to_value_ptr(members_.nodeptr_); }

   iiterator_members<node_ptr, const_value_traits_ptr, stateful_value_traits> members_;
};

} //namespace intrusive
} //namespace boost

#endif //BOOST_INTRUSIVE_LIST_ITERATOR_HPP

/* list_iterator.hpp
schM8L7lmmzdD7EZSjMgooLQy3iTCgA7He03s3MzRj0NEC1sg4RI6m9a1uNCitm0PGPDlsdtAye+KtK6ju+fcIx5UF3dYXTr/ekQPLyi7h7oGFU8oZvZezTT1zC64WSXVmeZ4uZM9d1aPM2XvRNE6Xz84l4jxlQ0E4lxcnObWtHNEXLRTTj5UHJpeTifpRLTHltgzD3hqrBwMCUxRmZNo0AhqKXjcU5pFzx854R3dC7pWFcTi8gbtb2D3GGUM2z/JQ1vnrtG7cvi7nD0r/OgWl2OZebI++upZRpLlpuYgwD9LWVwiUqWfu+6rlWqi0j5vH0yGsN3mZRtfKL5fDC/4BbJN0BGXGn3Df7WDE7ERhFHeQzDgNXByWLGl2KIU3WZ6v59YWLX+rg/CTaXmlCwj3NnWfvxcduHgajFxHV5vdkmpZYtdtTNsqB8bzzozbHoK1N3k9Zg3q4Lurz49VUy3gW3972lWUVq04hpd712gKWK37Fok3ZDtdSU12p2m6fnlkJEZTEwWoFMlW8xI/bnb533y3p0Keep9b/0dQFvq/yEehWC3j/Mnnyfr0Dc0HE2ZKK7Kf8VicpHm/vzi0FJtFlKseHo1lvAvTUpwMdXrVNhGe47Kl2pOXimupJsidCixWC9FE9Xc0BJ9xq2KizSscpi15nZyl6Sur8uq+MEw4oHooPNYWe7LG1xkS0b+ECSZ4XLyytOkK5MCVuD
*/