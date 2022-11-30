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

#ifndef BOOST_INTRUSIVE_SLIST_ITERATOR_HPP
#define BOOST_INTRUSIVE_SLIST_ITERATOR_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/detail/workaround.hpp>
#include <boost/intrusive/detail/std_fwd.hpp>
#include <boost/intrusive/detail/iiterator.hpp>
#include <boost/intrusive/detail/mpl.hpp>

namespace boost {
namespace intrusive {


// slist_iterator provides some basic functions for a
// node oriented bidirectional iterator:
template<class ValueTraits, bool IsConst>
class slist_iterator
{
   private:
   typedef iiterator
      <ValueTraits, IsConst, std::forward_iterator_tag> types_t;

   static const bool stateful_value_traits =                types_t::stateful_value_traits;

   typedef ValueTraits                                      value_traits;
   typedef typename types_t::node_traits                    node_traits;

   typedef typename types_t::node                           node;
   typedef typename types_t::node_ptr                       node_ptr;
   typedef typename types_t::const_value_traits_ptr         const_value_traits_ptr;
   class nat;
   typedef typename
      detail::if_c< IsConst
                  , slist_iterator<value_traits, false>
                  , nat>::type                              nonconst_iterator;

   public:
   typedef typename types_t::iterator_type::difference_type    difference_type;
   typedef typename types_t::iterator_type::value_type         value_type;
   typedef typename types_t::iterator_type::pointer            pointer;
   typedef typename types_t::iterator_type::reference          reference;
   typedef typename types_t::iterator_type::iterator_category  iterator_category;

   BOOST_INTRUSIVE_FORCEINLINE slist_iterator()
   {}

   BOOST_INTRUSIVE_FORCEINLINE explicit slist_iterator(node_ptr nodeptr, const_value_traits_ptr traits_ptr)
      : members_(nodeptr, traits_ptr)
   {}

   BOOST_INTRUSIVE_FORCEINLINE slist_iterator(const slist_iterator &other)
      :  members_(other.pointed_node(), other.get_value_traits())
   {}

   BOOST_INTRUSIVE_FORCEINLINE slist_iterator(const nonconst_iterator &other)
      :  members_(other.pointed_node(), other.get_value_traits())
   {}

   BOOST_INTRUSIVE_FORCEINLINE slist_iterator &operator=(const slist_iterator &other)
   {  members_.nodeptr_ = other.members_.nodeptr_;  return *this;  }

   BOOST_INTRUSIVE_FORCEINLINE node_ptr pointed_node() const
   { return members_.nodeptr_; }

   BOOST_INTRUSIVE_FORCEINLINE slist_iterator &operator=(node_ptr n)
   {  members_.nodeptr_ = n;  return static_cast<slist_iterator&>(*this);  }

   BOOST_INTRUSIVE_FORCEINLINE const_value_traits_ptr get_value_traits() const
   {  return members_.get_ptr(); }

   public:
   BOOST_INTRUSIVE_FORCEINLINE slist_iterator& operator++()
   {
      members_.nodeptr_ = node_traits::get_next(members_.nodeptr_);
      return static_cast<slist_iterator&> (*this);
   }

   BOOST_INTRUSIVE_FORCEINLINE slist_iterator operator++(int)
   {
      slist_iterator result (*this);
      members_.nodeptr_ = node_traits::get_next(members_.nodeptr_);
      return result;
   }

   BOOST_INTRUSIVE_FORCEINLINE friend bool operator== (const slist_iterator& l, const slist_iterator& r)
   {  return l.pointed_node() == r.pointed_node();   }

   BOOST_INTRUSIVE_FORCEINLINE friend bool operator!= (const slist_iterator& l, const slist_iterator& r)
   {  return !(l == r);   }

   BOOST_INTRUSIVE_FORCEINLINE reference operator*() const
   {  return *operator->();   }

   BOOST_INTRUSIVE_FORCEINLINE pointer operator->() const
   { return this->operator_arrow(detail::bool_<stateful_value_traits>()); }

   BOOST_INTRUSIVE_FORCEINLINE slist_iterator<ValueTraits, false> unconst() const
   {  return slist_iterator<ValueTraits, false>(this->pointed_node(), this->get_value_traits());   }

   private:

   BOOST_INTRUSIVE_FORCEINLINE pointer operator_arrow(detail::false_) const
   { return ValueTraits::to_value_ptr(members_.nodeptr_); }

   BOOST_INTRUSIVE_FORCEINLINE pointer operator_arrow(detail::true_) const
   { return this->get_value_traits()->to_value_ptr(members_.nodeptr_); }

   iiterator_members<node_ptr, const_value_traits_ptr, stateful_value_traits> members_;
};

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_SLIST_ITERATOR_HPP

/* slist_iterator.hpp
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
*/