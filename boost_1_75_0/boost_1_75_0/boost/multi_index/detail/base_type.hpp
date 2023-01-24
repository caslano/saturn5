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
lrI7vTnYyrtcTODwCcyHbmOH75Vwq5Qp0UpBia4xUSITBl87gWdkJa/GckQwc53FxArotggL1oP4F8hYjoZr1fHkBFrCyxN3Ey36HGjRcu7vh1xTRFpQEPXmXBMNqQAI8AMrYD9svm4iX8/lNkuO8nOJ7Cw2RVlnLGYaeSYXacViQXcqjBvf8A0T3RE3EK7ECr97sUZ1xHWES3ZXkRRPxCWXsrwicVGmj0GFKZKXotlEXlbp5MX1u6omqu5CNS88Zf/kZOhXpy+xSqeJVkt2wfS49ChfjMTKlHcnEMeqC4eFUe+Sx1YBZivyqMWwYsTXPvukjrfzxSEM2/QnbXqkdu6TPInaaojPpekxz6lRNrPwJiQwj4qYvgk6QNECoEsnYEhaYgXAc1qDR0ASZUBy/gkdkl+fMCD58YlgSJY+yYQlFhfnS0hTaGiuRZpCidGZeAsKIgEFoRwi8YKSJAAlqQuT63lt+Z/Q1ipTihkrDepRql0r1eRsnUbcAo8RiaCInPHVRCKimpCIauWXkRy6VTuSqcDRkcJXISpjOFGBERw8BDJNhFsyob9bSZNPuBOPwUb+dxjs39G/rE84UBasN/CfUMqyfugvvFv2/q462odsEIOqSf9Y8gaiZj+9EWmRa2TvadRmLyRF4IxM2PkVFYSR1qMClzvtjJSX3ldVuIKcpYY0sfCUUsgX98PF/aRxxYtP8kXEhiPKoUIr
*/