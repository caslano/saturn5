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
DZdUrXPwHdObcCKd5j8P4no/9cN+lx5yUQ9W7WotAQ+x8a9yU1e8L9PlU+HA/DuYeanKY7MqXF8o6GhflIAAaqMQUZkoxf1MI370nIw8jc90uURi9kJ/SOkhk8IWnWPyjuNuWdqgyqn4Eql7tnk3c8Gz8R45vm62AOFb5jRhlvE7DqUSqx1YigYRAkiyx/LdJQX98onr/ARXO0dSOzd9T65gijzuUW3an/zq74/p5U6W8fu1Y8Nbn7SVpeFJJRgTKm0tEi3lkUwr+JeQ15owuqkg7dSju/6WqZZOBbAnn+x+c+lpk2ysQ8o/wSxmfE5QYTTClz9UMcPSIjSchSAC/MT//kpBbWIOwktld/ODCkm8vnDyLNpHstfzBuGG13CouaBL9vqjlQH7Rc9RdgfGtYRSPPBP51k0zPKQ87rDFWaZETcHGn29+QaDpL8WTn2yH1Dc/WMdYQApsUwe392/ivQ072Q2yqmUIGZfzolg2TUrjz5L6y8rK1hmd561uaxh4Ogi8q77ONWKxjWksbD6zvibioEaAMWi0ajbOGwln7J+CKc9smbJ0yFfYE7Fm6AwvvloXr76aFmGqtAvndTfCDPnNchfHlRobOYPQybj0HwLzQ2lILnFt2hO6bS++O00k2Wv4E0w1Ks0l3VbSnH8Nlm75YMzLdP+F2GNbxdfLOf+LmZJSJ1AznBU2Qf0bTq7nu2Manzt76SCmUzM
*/