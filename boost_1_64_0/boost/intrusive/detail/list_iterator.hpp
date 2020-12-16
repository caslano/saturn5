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
P8Hyaz2ssudNwDVa322Mb5l5Wg9ztR4K4YlwkdZHGewKi+GZ8EKYo8dn6fHZcB4sgyWwCi6Al8FSeK3KfQbXOmPZBGh+2uJWan6Wan6q9DxcCnvB5freeDUcDa+BZ0N0y3ce0pLvApfDXHgFzJM0/Nfp9+HFkg7fbzQ+MsQ33sM0X5NdnrNu1+8h98AseK/28/fDcfA+eLb6P7PH+HXMsYW//9Jne/0z5LIilMuOUC4/QrnyRuT49s8ec+57z2URnjzH18Cedf+d+9KF7kkX2V50h3C+rMb3ojP3oXPfgy6C/ee+w73nBnPOcnHLcTW4bbj9uJjz2fMONwlXhFuJ24DbiTuIS77A5xmGy8ZV4tbhtuD24jx57L+HG40rwq3C3YvbgTuAS8z3eQbjcnHLcRtxu3CHcGkF7IOIy8etxW3G7cEdxCXM9Xl64ibhSnGrcPfiduD24xIK0Yubg6vCrcdtxdXhPEXN++Y1/zX/Nf81//0v/P1b9v9jrtyx2P+vI/v/1XbhGZEHv2gPc2SYopZnTSWqrJC9AX/BsZjxxrHF5Ihl+B7dG/A1Y2/AfH0PlaX4OnZ4bzLPyf69AcdMn55XWlZQlOfXRDbQYs+bjEXDikRcBPbw7bkw6d5wc0bCz/XYK3NYPnzmydO75LX45z/2Dnvv+D/FzQ8/h8V9bsh3v89+U+fOhJvj438f0HOg5yYz6H3gTP0udhZM0vfPTvr+2QeO0/fU8bov+b0X+Ty1OH0mdp6Hq+XZN/RZ933can2WTZbn19DnVJ8+h67UZ0997tRny/rnyiLcuqBnxlxc3UXNz0jNf81/zX/Nf81/zX/Nf81/zX/Nf81///4/H27Rd/f+X8l+WEVzFcfiG4D1Hv+68R6/Q1+lvtH3xH/i9lo2lKfJe3xObk7e6LPsPQtLFhUVV/nX0ryOjJed0Ez7WLdJnM84zrgB7hFytRO24VWeZFTnJHPNDWEhe5yUFJcWOTYfbpbjz3iS+fcU3GTPONf1OKaeVyVvFy8pKK1fZ3pIjrdy1gGeMV3WmbquAzR1dZS1ifMLKua7r+s1ZdeKbOHCcrf1vIZsHLKHZcBqsSdVy/mxHKvxjGCGwSWij3D4loTHG7ZzFjn1uVeO/bT+mLEXwz45ttEzjxL9wOOT/L3ShQO6xqij2ul4WuRe9sSgZTXpPOyJNvK3wLEDGyv1VYaeaR7ZH94qUzTzMWTvhtND9m5QGeYHkE9LJm6xI/MGfllvqzL50eRX1ttOD1hv+1mQrpXI/UV0VVfbMnVBujYi86Yl461+PyGmlaPrrSC53ci9bcn5qvcYtms4W4Fyh2198dW3JkS3Cauvm89J9xcJMTEhcrZ/fxNsWVjXWArXWOg6MblGnHWkr4qctHdnbTDtljBptxIm7U/CaJ+6tvRrOfcSP8BGX04rndOgNmuG8M/nyOyabvQJsnIypC/QvWDRKbKZ3iRpqxoXjZd67jOvfw33BrZvbcNFMyQ95PHza7r4f4q/2tW+30g5/hhzcWY7Ot4V/ec568kPikyycw1NFP8zRpsvd2xTnS/H0OXsR8Q6aC1jKpwnxy9Tv52/FLk+diI/uKW2iTbpIe3BllnV0r6GSsxrSNLcZ6xXtPuxvpJGkvrt8iT626Lq3NTSvp6qv88F5XY9idxu5N6RtFck2zKHkDF1HbZ1+bDbktDG0BVot2V9YmT2kyJp6wH20GNx1rnV8f4s3NfI5ucYbVGMWc9dFub+5PSJJRJnKMe9ni7u9qzR67YG1Nj7U44PcL0HmXFpS/yS1acu95hg2VC7CDfL8QSj3y6db7aDy+V4B2lruVyvNTHaN7Y+2VPfNzZqhyvC/ibQhh/5JUw=
*/