/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2007-2013
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_TREE_ITERATOR_HPP
#define BOOST_INTRUSIVE_TREE_ITERATOR_HPP

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
#include <boost/intrusive/detail/bstree_algorithms_base.hpp>

namespace boost {
namespace intrusive {

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                   Implementation of the tree iterator                   //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

// tree_iterator provides some basic functions for a
// node oriented bidirectional iterator:
template<class ValueTraits, bool IsConst>
class tree_iterator
{
   private:
   typedef iiterator< ValueTraits, IsConst
                    , std::bidirectional_iterator_tag>   types_t;
   typedef typename types_t::value_traits                value_traits;
   typedef typename types_t::node_traits                 node_traits;
   typedef typename types_t::node                        node;
   typedef typename types_t::node_ptr                    node_ptr;
   typedef typename types_t::const_value_traits_ptr      const_value_traits_ptr;
   typedef bstree_algorithms_base<node_traits>           node_algorithms;

   static const bool stateful_value_traits = types_t::stateful_value_traits;

   void unspecified_bool_type_func() const {}
   typedef void (tree_iterator::*unspecified_bool_type)() const;
   class nat;
   typedef typename
      detail::if_c< IsConst
                  , tree_iterator<value_traits, false>
                  , nat>::type                           nonconst_iterator;

   public:
   typedef typename types_t::iterator_type::difference_type    difference_type;
   typedef typename types_t::iterator_type::value_type         value_type;
   typedef typename types_t::iterator_type::pointer            pointer;
   typedef typename types_t::iterator_type::reference          reference;
   typedef typename types_t::iterator_type::iterator_category  iterator_category;

   BOOST_INTRUSIVE_FORCEINLINE tree_iterator()
   {}

   BOOST_INTRUSIVE_FORCEINLINE explicit tree_iterator(const node_ptr & nodeptr, const const_value_traits_ptr &traits_ptr)
      : members_(nodeptr, traits_ptr)
   {}

   BOOST_INTRUSIVE_FORCEINLINE tree_iterator(const tree_iterator &other)
      :  members_(other.pointed_node(), other.get_value_traits())
   {}

   BOOST_INTRUSIVE_FORCEINLINE tree_iterator(const nonconst_iterator &other)
      :  members_(other.pointed_node(), other.get_value_traits())
   {}

   BOOST_INTRUSIVE_FORCEINLINE tree_iterator &operator=(const tree_iterator &other)
   {  members_.nodeptr_ = other.members_.nodeptr_;  return *this;  }

   BOOST_INTRUSIVE_FORCEINLINE tree_iterator &operator=(const node_ptr &nodeptr)
   {  members_.nodeptr_ = nodeptr;  return *this;  }

   BOOST_INTRUSIVE_FORCEINLINE node_ptr pointed_node() const
   { return members_.nodeptr_; }

   public:
   BOOST_INTRUSIVE_FORCEINLINE tree_iterator& operator++()
   {
      members_.nodeptr_ = node_algorithms::next_node(members_.nodeptr_);
      return *this;
   }

   tree_iterator operator++(int)
   {
      tree_iterator result (*this);
      members_.nodeptr_ = node_algorithms::next_node(members_.nodeptr_);
      return result;
   }

   BOOST_INTRUSIVE_FORCEINLINE tree_iterator& operator--()
   {
      members_.nodeptr_ = node_algorithms::prev_node(members_.nodeptr_);
      return *this;
   }

   tree_iterator operator--(int)
   {
      tree_iterator result (*this);
      members_.nodeptr_ = node_algorithms::prev_node(members_.nodeptr_);
      return result;
   }

   BOOST_INTRUSIVE_FORCEINLINE tree_iterator&  go_left()
   {
      members_.nodeptr_ = node_traits::get_left(members_.nodeptr_);
      return *this;
   }

   BOOST_INTRUSIVE_FORCEINLINE tree_iterator&  go_right()
   {
      members_.nodeptr_ = node_traits::get_right(members_.nodeptr_);
      return *this;
   }

   BOOST_INTRUSIVE_FORCEINLINE tree_iterator&  go_parent()
   {
      members_.nodeptr_ = node_traits::get_parent(members_.nodeptr_);
      return *this;
   }

   BOOST_INTRUSIVE_FORCEINLINE operator unspecified_bool_type() const
   {  return members_.nodeptr_ ? &tree_iterator::unspecified_bool_type_func : 0;   }

   BOOST_INTRUSIVE_FORCEINLINE bool operator! () const
   {  return !members_.nodeptr_;   }

   BOOST_INTRUSIVE_FORCEINLINE friend bool operator== (const tree_iterator& l, const tree_iterator& r)
   { return l.pointed_node() == r.pointed_node(); }

   BOOST_INTRUSIVE_FORCEINLINE friend bool operator!= (const tree_iterator& l, const tree_iterator& r)
   {  return !(l == r);   }

   BOOST_INTRUSIVE_FORCEINLINE reference operator*() const
   {  return *operator->();   }

   BOOST_INTRUSIVE_FORCEINLINE pointer operator->() const
   { return this->operator_arrow(detail::bool_<stateful_value_traits>()); }

   BOOST_INTRUSIVE_FORCEINLINE const_value_traits_ptr get_value_traits() const
   {  return members_.get_ptr();  }

   tree_iterator end_iterator_from_it() const
   {
      return tree_iterator(node_algorithms::get_header(this->pointed_node()), this->get_value_traits());
   }

   tree_iterator<value_traits, false> unconst() const
   {  return tree_iterator<value_traits, false>(this->pointed_node(), this->get_value_traits());   }

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

#endif //BOOST_INTRUSIVE_TREE_ITERATOR_HPP

/* tree_iterator.hpp
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
*/