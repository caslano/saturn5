/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_BASE_TYPE_HPP
#define BOOST_MULTI_INDEX_DETAIL_BASE_TYPE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/detail/workaround.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/size.hpp>
#include <boost/multi_index/detail/index_base.hpp>
#include <boost/multi_index/detail/is_index_list.hpp>
#include <boost/static_assert.hpp>

namespace boost{

namespace multi_index{

namespace detail{

/* MPL machinery to construct a linear hierarchy of indices out of
 * a index list.
 */

struct index_applier
{
  template<typename IndexSpecifierMeta,typename SuperMeta>
  struct apply
  {
    typedef typename IndexSpecifierMeta::type            index_specifier;
    typedef typename index_specifier::
      BOOST_NESTED_TEMPLATE index_class<SuperMeta>::type type;
  }; 
};

template<int N,typename Value,typename IndexSpecifierList,typename Allocator>
struct nth_layer
{
  BOOST_STATIC_CONSTANT(int,length=mpl::size<IndexSpecifierList>::value);

  typedef typename  mpl::eval_if_c<
    N==length,
    mpl::identity<index_base<Value,IndexSpecifierList,Allocator> >,
    mpl::apply2<
      index_applier,
      mpl::at_c<IndexSpecifierList,N>,
      nth_layer<N+1,Value,IndexSpecifierList,Allocator>
    >
  >::type type;
};

template<typename Value,typename IndexSpecifierList,typename Allocator>
struct multi_index_base_type:nth_layer<0,Value,IndexSpecifierList,Allocator>
{
  BOOST_STATIC_ASSERT(detail::is_index_list<IndexSpecifierList>::value);
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* base_type.hpp
3wjMYghR8SMt6dlV1O7ziOOmzolmfBUAltDCW1gRlmjtuJvHrKdzTRPkmNLrVNagLhb4GDSNuyxczsCZ6Nc/uXijgn1H6eSKNMSc78lJeCs1UfsqgcOYrC646HMnrN9bgO3Tkih1Ua3/qr8+7T5qeV/vzOHuPX4T85EJ+TL07nVbF09hBX6Mk0Cv5CcOipFAP0z3NCYB5KT9FOusdScnR2bDjsQiytbYSMNR/FfJByIcPl0d4lJrCH0ROg9GlaV5oezpILnMN/v8UBlBSZ/Tvak9DZbMA5vuUYzQJ86ufApTLJ0bAxJT0hYF3wfapyuAUyign3kJcHQdg+6Umq9/xsY6c+ok7i+BNosUiyHqV1l5Xq2xsNa0XdlClo5ybnraDfbRBbNZvzbzsW8BI+5kv6cnH32AIfNHT+gytfGUfcTbMgxb0bnyA86Mp8FQ7GPNx1WaEUuKwBeIVJS46+9AaLUKj4C9777iECpRD3VlWAAiaZYsvS2M8EcKLteYYnABDJDlddMJB1UlWkALIRVAuYan2yR+1XuWYLI2WsoFYygb6CJfdS3rwJDgCA==
*/