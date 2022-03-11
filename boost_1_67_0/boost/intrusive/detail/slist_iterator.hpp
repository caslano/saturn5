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

   BOOST_INTRUSIVE_FORCEINLINE explicit slist_iterator(const node_ptr & nodeptr, const const_value_traits_ptr &traits_ptr)
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

   BOOST_INTRUSIVE_FORCEINLINE slist_iterator &operator=(const node_ptr &node)
   {  members_.nodeptr_ = node;  return static_cast<slist_iterator&>(*this);  }

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