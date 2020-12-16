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
103H2NfN9ZK7AZp3VUuuLo7cYMkNkdxQ+7x3ii23VXLbJPce+7zHkVspuVWSW237aZdcJ4dcF8nlwo6wq+V3ulBy3SVn+zu+UnI71A7shN3gVVa7Uin5hY52pYfkeynfPJgFz4E5sLeul3zYD/aB42FfOFHxJsH+ak/OhnPhAFiq454etXH0KJce66THeumxWXpcJj0ulx4bpMdG6bFZelRIj0rpcYX02Gz7502PrUex9CiRHqXSY7n0WCg9FkmPxdJjidGDeNLjIulxsfRYJj2WW/XhsPTIdNSHDOmRCTNMG2PNBZAc7R33rGj/nulJ+DVrHhP/7hsT/+8aD9+UsfD/S77M/hXj4c/0WPj/hXHw+xnrfoTwOiHrY/j9Iiwj7CTsJxwm1BJS76BshFLCdsJ+wiHCa4TUj3OMMIdQSdhHeJzwMiGwv3ksffNf81/zX/Nf81/zX/Nf899/49+/bfz/GfT/tzsnoP5Vs5aA+fs6wawLQfhQaHxpe6sfLAHfdidN/Adc/UNKK2j3n/l9fy+YY4cDMXyUIetet54+TL8fsqP5Bt2d7RSnL7PXTBrpAc+33DL5Gdol3iRWx/BHdl0C/dvxfOWor+5d0S+1wvRLzavePzJv9I5P/aTfqkt+1GvLguZ+qX+ydzXwURRXfAMBAoSQhOQIH2IgIJ9CpIigFMJH+BIxJEFRsUlIAqSEEJMDolI9hLZYqaaKGlvUiNTSlrZRQdOKNkVUVLRRqeJHa6xarUYbERFtrP3v3H+XudvZzV4u/bC9y+/lf7f7Zua9N29md2dn3vyvv5dCErRitlf2J0dAyaA9xtxqvt/oy/cbKdK+ZXHA/sAk4AC+DzoFeDrwVOAkYCpwOnAwMBM4BJgNHApcCjwNuAI4nLE+RgCvAo4CbgGOBt4MPB14HzCdsVjGAx+jHHWR2ByRccjIOGRkHPIrMg7pjYwTRj6RT+QT+fxHPtGgb/6rn/9LS5b5n/zDf/a/zqOZa7fm8tm/mrH/bwAt6ovfMXz298eIxuLrzDmZ2W3vAdAX+KhIOxVyKvcAQN6W+deIk62eJyrz4tKMz8riKikOb704XyzGBrrqifS88paVyXOLfyR4Nmld8Mc1AfhUFFeuLRVf+1PubYLvOi0e/8dB+lWQfwjGC7rh3C+g5wjIupVjAjptx7G6dsacD5jPTf0D4h4wtgAUwVGk1b/r87m7q9bFO4/NpACvEOlmqOqDeUZxTX3guuHF4tw0Zd0wHXiNefBibT5+057i/EjNg3XFCzrBdtDp+7Bfz5iunWKH9jDneU9B2us57qLn9bVEM7aBOX6zROTVLWCPg0SeyxPnkmD3TmKNsgf5Qi+R38Ng2Ac66GIOudP4TZJiLdIkTqZewfkt80CvQfEms46wMNTFuFm3Hjr/eFXdIC/FmlHJLl+K872V9cO0wudvScMBPW2et8rLtrbhyy+/NPZoWJB8Mh705qC+jZ+ZKA/2PzuhFemSka/CXnZrSEVZkAHHKIPk7/I6/tksLBN0M/jze9CW/vnp0xfMOV/uhYJtqrIh84gK9i2lzcir9LNV4tww+FkfjT4G3xV2o/86zt2f31ZfANnMGBmyn82loz5LGZ8BVcA2DaZtsDZQMopdv/yE4N+POKkxCjsxP67VwLgoviFfXKSwmsDc/yMJ+JLg+xX6xir1mgaLDctEWg++vS7O/RzzN7uZMSg0lCPn/5ng2YbcPYH1wL7sLXF+J+LjdkceHBMObheCp5vU35uLjk2ePj3Bg9qciLqMZX+BNbNiDf4OMDwG2sX6/R3xIeBG0f+3L3a6seYJ9sUx2b7/HWsW1GOB//ox45vFmPEDTYuSRn732oPvLaw=
*/