/* Copyright 2006-2014 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_HASHED_FACTORY_HPP
#define BOOST_FLYWEIGHT_HASHED_FACTORY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/flyweight/factory_tag.hpp>
#include <boost/flyweight/hashed_factory_fwd.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/if.hpp>

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#include <utility>
#endif

/* Flyweight factory based on a hashed container implemented
 * with Boost.MultiIndex.
 */

namespace boost{

namespace flyweights{

template<
  typename Entry,typename Key,
  typename Hash,typename Pred,typename Allocator
>
class hashed_factory_class:public factory_marker
{
  struct index_list:
    boost::mpl::vector1<
      multi_index::hashed_unique<
        multi_index::identity<Entry>,
        typename boost::mpl::if_<
          mpl::is_na<Hash>,
          hash<Key>,
          Hash
        >::type,
        typename boost::mpl::if_<
          mpl::is_na<Pred>,
          std::equal_to<Key>,
          Pred
        >::type
      >
    >
  {};

  typedef multi_index::multi_index_container<
    Entry,
    index_list,
    typename boost::mpl::if_<
      mpl::is_na<Allocator>,
      std::allocator<Entry>,
      Allocator
    >::type
  > container_type;

public:
  typedef const Entry* handle_type;
  
  handle_type insert(const Entry& x)
  {
    return &*cont.insert(x).first;
  }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
  handle_type insert(Entry&& x)
  {
    return &*cont.insert(std::move(x)).first;
  }
#endif

  void erase(handle_type h)
  {
    cont.erase(cont.iterator_to(*h));
  }

  static const Entry& entry(handle_type h){return *h;}

private:  
  container_type cont;

public:
  typedef hashed_factory_class type;
  BOOST_MPL_AUX_LAMBDA_SUPPORT(
    5,hashed_factory_class,(Entry,Key,Hash,Pred,Allocator))
};

/* hashed_factory_class specifier */

template<
  typename Hash,typename Pred,typename Allocator
  BOOST_FLYWEIGHT_NOT_A_PLACEHOLDER_EXPRESSION_DEF
>
struct hashed_factory:factory_marker
{
  template<typename Entry,typename Key>
  struct apply:
    mpl::apply2<
      hashed_factory_class<
        boost::mpl::_1,boost::mpl::_2,Hash,Pred,Allocator
      >,
      Entry,Key
    >
  {};
};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* hashed_factory.hpp
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
*/