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
GSkzgy0snwYV68vse4ZJo7237rpJwx4/0N+kMTdlTrBl5BgD/3l9oIkzK0V+amyfJEbvdJPHJcG+gakxxxP8yqTROmDGKHE9Fc7UOIBg9aG0Ni3SWvROa5NKvPCxAFHfA/z0nhlqj0uWrdgy9VJ5lM3UuIC21cejxgUoziMzvftx36Tvx+OGNdyPL0GGqIGNuo9uEivMvA8CDIUrtP8X7OvO7yGEzRmkFSKhirCF0I6wlbCN8B61YalJXkf2s+P22fWRN5n96ElYGrpuhuu6aVj7gjkeNGBbzHz8yPX6XdeL0ggqrq4X63rrbo6vDswLW2emYs0WM7nErDXk18csE3ddoBQtNXfG2PJYZr2dCpH9Nr+359QXfEgCY75D4zguGx495she599eO8K9ZkKstSDO3JoPya6NMOQTof1HHhq15tmcV34duPoXt2949YNXxFrDIfk1DdxrRMRamyL5tRfO1JoSya4RcabWBnGvHRF7bRD32h3/nrUjJnCMPzNmdDfpdiHM5PdR9mMq2uKG33+wfhfn1Mc/xfbYDOPT2MiOs37jy0W/zTw48/sJ4k+0fj9oxXnI+s2zhcmrhO0j1u+lpF8AP01YTDoHUkiP34us3xfp9/Ag5bJ+n2f9nmD9Ht/w27T5B40vdp5N9buE31P1+z5+T9Pvh/n9Btzn+VaTf7eDaof3qLEZ2EL+/2EnOAx2hQVwJBwOx8ER8Dw4ChbD0dD4oYNXwgnwNlgEPwTHwM/CQvgwnAyPwKnwWcV7A670/IfBUunXVr89f/shlsB2cCHsARfD4fBiOAsug3PgcjgXLoUlEf79DyifNOVj++vtoHw6wvawk+SWeP6s4FzJtSHMkdwrWkehFnaBP4MD4S/hFHgSToO/gtPhz+Eca32PdZ6PJ3ip0m9HWKb0v0W8FPgc7Aq/CwfB78Pz4A+Uz0twKjwBl8AfwVXwRViu457/5L3Kr8LkF+3HOQivh23hbpgOb4K5Ef6bR8A9cDz8gPS4Bc6W/+YFEf6bN8EP2n7auzb4aT8YZ12I1mHrQhDiyJVL7lLJrbXOY6HkFjjO42aVe6vKuQ0OkZ/sArgLDodXwnHyV3+h5a++0vM5A/+g9NsTypT+n5T+n+Fg+LbO09/glfJ7vh+2hl+FbeBrsC08CdvBX8OWsE7bWh9GvldoW5SvvT7MIeX7FMyAh2GOtrvCr8A87e8Lydtc91+D8+ERncejsAR+Ay7V9huw2PNdArsq/9aEIse6IG3hRl1flTANboKZsALmar93viqV7jTH+XpY5fo87AC/AHvDL8IJ8HE4ET4BJ8FHYZG2Pf/wx5V+ptK3/cP3kt550rc3zID50JOviyOfIflMyWdJPlvyKz2fCnCho937sMr3EbUrH9X19jE4Cn4SjoEf13X3CTgX3glLddzTs1r5dHbo+VkOh/gAbA8/p+v9QWsdmQOS7yt5ex2Zu6Xnp3Qe7oGd4afhWfAzsA88CL370XGl93X7fmStk5EKB8BW8BzYBg6CXeAQeA4cpvZ/OFwKR8LL4Gh4JRwP98IJ8MNwEqyBhfAxOBl+BU6Bz8Cp0NRnb142HOGozzOIF4SzYDt4gertHDgQzoeD4Dw4XNs6D8wzjl1fclVfuqq+dFN96S75k/7cXHNPQ15rtkp+C/FS4Hthd7gDng13wknwKlgEr5a9quGl8Bp4BbwWVsHr4XXwRngbvAneCd8PH4IfgIfgrfBZ+GH4CvyI2qk7YFqQegm7wP2wJzwAe8O7YV94Fxyk7SXwU3AZvEflPeDN0YTDVN7OhNtV3lk8P2TD2bAbLIajYAmcC5fDXXAVvB6uhvvgGlgDt8DH4Tb4FHwvPAKvgt8=
*/