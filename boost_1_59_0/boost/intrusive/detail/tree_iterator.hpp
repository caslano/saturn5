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

   BOOST_INTRUSIVE_FORCEINLINE explicit tree_iterator(node_ptr nodeptr, const_value_traits_ptr traits_ptr)
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

   BOOST_INTRUSIVE_FORCEINLINE tree_iterator &operator=(node_ptr nodeptr)
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
+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
*/