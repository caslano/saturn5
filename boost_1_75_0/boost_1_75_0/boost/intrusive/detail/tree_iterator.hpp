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
HH9wMf8oCEWlOHDn9x5hps3xIdlw+t7wTlieViXOUlcam4TJ/U/J64IcFwqngwGgGA8NjvtTpHa0Dm6E3kfJ5xOh8zZACa4Pehde7rqED87G15Zpk0c3RMibG0aKUKuHK6gza2PHiYYbx4YqQ12WfzwoqOv0m88H4Vmt4+7js2VnUBTFgewyS4DUlInsIwU89/ULR+zZmOuLGRPNq7fS0D+YzJ8cHRr/p2jRy48Hc4HBKUYIkb84GRRvtXjmNVixl3khJLZatZdfGh8af+p10hqffrl0PdsnGRe4ejMaE4qx97OX66xsQyygMiUm6lyIN+F2mJ4Cb8VjE/Z9goPqj3gDOgSD+ntvzYKdQXXD2ras+OjWdaW9K2eFVzTx7cHsEgY11nyLc8xmGbr99vMZg4R9FuumbsQEAgXV/NW87IV+UWtbNm4ksoMOFDVuQZsOL8Aj1XsEOm/1XDXeZMP4Y7aNEKJ7u7t9H4FwSn7WmRKdg129Lzl5QQCxIPF10LW+S2A1n9ayATkc7e9K1gAGMpWJ5v/p1eDiLHtKZU/8ywuCzPAMKD1thFx7dKzqefijHMW/WE8dBa6pfqY/Y7TtN3MrOqUo/XpFn2UrkbcEBL6DsRXd60kbrSCUL1uErtwuH7Lv108cmUKS2/KnfCsYQ8TOXns5oUeeFLeNbavt0U1gwblaxI+Ulm5x5L8yedBET3v6f2Ey52cugX8x
*/