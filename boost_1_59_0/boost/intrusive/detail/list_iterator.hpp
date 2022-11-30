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

   BOOST_INTRUSIVE_FORCEINLINE explicit list_iterator(node_ptr nodeptr, const_value_traits_ptr traits_ptr)
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

   BOOST_INTRUSIVE_FORCEINLINE list_iterator &operator=(node_ptr nodeptr)
   {  members_.nodeptr_ = nodeptr;  return *this;  }

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