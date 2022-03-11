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
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
*/