/* Copyright 2006-2009 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_SET_FACTORY_HPP
#define BOOST_FLYWEIGHT_SET_FACTORY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/detail/allocator_utilities.hpp>
#include <boost/flyweight/assoc_container_factory.hpp>
#include <boost/flyweight/factory_tag.hpp>
#include <boost/flyweight/set_factory_fwd.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/if.hpp>
#include <set>

/* Particularization of assoc_container_factory_class using a set.
 */

namespace boost{

namespace flyweights{

template<
  typename Entry,typename Key,
  typename Compare,typename Allocator
>
class set_factory_class:
  public assoc_container_factory_class<
    std::set<
      Entry,
      typename boost::mpl::if_<
        mpl::is_na<Compare>,
        std::less<Key>,
        Compare
      >::type,
      typename boost::mpl::if_<
        mpl::is_na<Allocator>,
        std::allocator<Entry>,
        Allocator
      >::type
    >
  >
{
public:
  typedef set_factory_class type;
  BOOST_MPL_AUX_LAMBDA_SUPPORT(
    4,set_factory_class,(Entry,Key,Compare,Allocator))
};

/* set_factory_class specifier */

template<
  typename Compare,typename Allocator
  BOOST_FLYWEIGHT_NOT_A_PLACEHOLDER_EXPRESSION_DEF
>
struct set_factory:factory_marker
{
  template<typename Entry,typename Key>
  struct apply:
    mpl::apply2<
      set_factory_class<
        boost::mpl::_1,boost::mpl::_2,Compare,Allocator
      >,
      Entry,Key
    >
  {};
};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* set_factory.hpp
2P+uiD7KFdhJjJvE3mdpPD2bz8/+v3cNr6rGuZxj0VT1tU8MAjg0D5ZNi+xr8NlRkrh6JBCQcsMRwGGzf5ugrlilbsHRaKhL/iSc1/d1GdiDrsoI3ntXt6B+n2rYgtJR/jij/HEgo83R4MZFSLHHsX2xZN2KE1d6teZwsa+2Hck01Ym1X3DsK4giR8dM1ehXSizfamFfzz+SKeJtacHgSkX8OH2hht2sMlGo+KRCxI/DohIomh2tSIAbSt1SM615tnNRwTJpIzIp5SfRDvxjIAZ0oi6KMdxaBrun0Dm6eGrv/pOpxt768B+1OYSfUpl+SVMSynNB23uwfET2HTrGHLTQuSaNhEdPfv0mi65fZGHPOJ8//iQrtGwBXWLTnfp4XCdUnEqDr4P/b+rc+Vrnzuc+NNi5Jxfxzj1NBeB/82/o3G10x/BVQ5cu5hYbSovEZJeiWCuhHO8z8ESHAd16JY0AFVKvRK1/KtZzvzVE/fieCR8HP08J2IolSC79OIj9O5TOxMbBAT4OShy+RdkIj4F9rIT3sc002fPq8N20EuGRxrcprW/OELECX+J2GRGWO59370fU58IlUex7ynyMsdG/RQEAJSbhtqgI2y0x8kZfXCvy4YxPOUgTqeSQH5WAWPTCfHsHQM2xp3LlMUDTgWe7d8OzJv/8LRkm8WzvdzRfpiEtQDnLqlKWjsVuYM0x0iHfX4YjAIYeRndR
*/