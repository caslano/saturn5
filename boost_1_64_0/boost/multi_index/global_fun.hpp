/* Copyright 2003-2015 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_GLOBAL_FUN_HPP
#define BOOST_MULTI_INDEX_GLOBAL_FUN_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/detail/workaround.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/enable_if.hpp>

#if !defined(BOOST_NO_SFINAE)
#include <boost/type_traits/is_convertible.hpp>
#endif

namespace boost{

template<class T> class reference_wrapper; /* fwd decl. */

namespace multi_index{

namespace detail{

/* global_fun is a read-only key extractor from Value based on a given global
 * (or static member) function with signature:
 *
 *   Type f([const] Value [&]);
 *
 * Additionally, global_fun  and const_global_fun are overloaded to support
 * referece_wrappers of Value and "chained pointers" to Value's. By chained
 * pointer to T we  mean a type P such that, given a p of Type P
 *   *...n...*x is convertible to T&, for some n>=1.
 * Examples of chained pointers are raw and smart pointers, iterators and
 * arbitrary combinations of these (vg. T** or unique_ptr<T*>.)
 */

template<class Value,typename Type,Type (*PtrToFunction)(Value)>
struct const_ref_global_fun_base
{
  typedef typename remove_reference<Type>::type result_type;

  template<typename ChainedPtr>

#if !defined(BOOST_NO_SFINAE)
  typename disable_if<
    is_convertible<const ChainedPtr&,Value>,Type>::type
#else
  Type
#endif

  operator()(const ChainedPtr& x)const
  {
    return operator()(*x);
  }

  Type operator()(Value x)const
  {
    return PtrToFunction(x);
  }

  Type operator()(
    const reference_wrapper<
      typename remove_reference<Value>::type>& x)const
  { 
    return operator()(x.get());
  }

  Type operator()(
    const reference_wrapper<
      typename remove_const<
        typename remove_reference<Value>::type>::type>& x

#if BOOST_WORKAROUND(BOOST_MSVC,==1310)
/* http://lists.boost.org/Archives/boost/2015/10/226135.php */
    ,int=0
#endif

  )const
  { 
    return operator()(x.get());
  }
};

template<class Value,typename Type,Type (*PtrToFunction)(Value)>
struct non_const_ref_global_fun_base
{
  typedef typename remove_reference<Type>::type result_type;

  template<typename ChainedPtr>

#if !defined(BOOST_NO_SFINAE)
  typename disable_if<
    is_convertible<ChainedPtr&,Value>,Type>::type
#else
  Type
#endif

  operator()(const ChainedPtr& x)const
  {
    return operator()(*x);
  }

  Type operator()(Value x)const
  {
    return PtrToFunction(x);
  }

  Type operator()(
    const reference_wrapper<
      typename remove_reference<Value>::type>& x)const
  { 
    return operator()(x.get());
  }
};

template<class Value,typename Type,Type (*PtrToFunction)(Value)>
struct non_ref_global_fun_base
{
  typedef typename remove_reference<Type>::type result_type;

  template<typename ChainedPtr>

#if !defined(BOOST_NO_SFINAE)
  typename disable_if<
    is_convertible<const ChainedPtr&,const Value&>,Type>::type
#else
  Type
#endif

  operator()(const ChainedPtr& x)const
  {
    return operator()(*x);
  }

  Type operator()(const Value& x)const
  {
    return PtrToFunction(x);
  }

  Type operator()(const reference_wrapper<const Value>& x)const
  { 
    return operator()(x.get());
  }

  Type operator()(
    const reference_wrapper<typename remove_const<Value>::type>& x)const
  { 
    return operator()(x.get());
  }
};

} /* namespace multi_index::detail */

template<class Value,typename Type,Type (*PtrToFunction)(Value)>
struct global_fun:
  mpl::if_c<
    is_reference<Value>::value,
    typename mpl::if_c<
      is_const<typename remove_reference<Value>::type>::value,
      detail::const_ref_global_fun_base<Value,Type,PtrToFunction>,
      detail::non_const_ref_global_fun_base<Value,Type,PtrToFunction>
    >::type,
    detail::non_ref_global_fun_base<Value,Type,PtrToFunction>
  >::type
{
};

} /* namespace multi_index */

} /* namespace boost */

#endif

/* global_fun.hpp
iTjNC8T/oXHroTj1K/AowK3H1cQm29Vn8rd9furHQRmG1HeOOhxdPLkMDzLQHnvnkcbWsZaf1haRdV7XTmzCosGjg3yPppIyq+K795Vu5vQ3LnfoGtNL0tKLpSeavDt0oL8OWEQf+lQmE0Ge5DJ1PFHnBxFRMvvN3sNB681x7qdZVO/1HDowYAQAbaz+9H0krFKUVVUVmecLdd8gWK2d9Xsx/KPbPFT0kkPN/ezeI0fufb/owSZP7SyFMt1yv3/rXeLa8g7Uh2LK1Io+3rHw57pZ7BH5DRzXlZvWa9gHO94ZNDpN5xETHeBQg0P9PvGnGrOM3BMf/6MbAZ+bbRxCodyi+T6rLAeQAcq06R2jDQ62bCiBtPsvG07zxo3QcG61e1PDgZfglq/kyS0NtjqnuhT1cKiOJOLf17htib+Pn9vK8LmlGse9zWv3ZLh2JdQ9UceSpuPCvQZ48CxLRbiva9u9OYcb9+/H6cX3AZ5tCL4fVnRfxJnBdxqfmzanMYtLx8LXb7c5uuQRf/z9EKf2GhCP7s9xCILiUw/geKMey/Umxc8ch2qEst/dwTATNOI/fCDDIWiG/+hBHNdB07r7YMSJYfh+3K7vBFzJqK6yGdwRe/hDCAaTcpLvb9cYN3Jhl83EQy0OKRuzD1G9m/qo5uZC4YEc5f71FtwTirw6r/pjsw/ynqFc4wZJS1D9I+8dKmPcIi2YPZHt70PucEvbalpq+D94/3D+yRZ+7wND+dSR6vx+s58ynN/mlBfTfOXiUF/iJv8XDFd8cCjX5OaCyf/XD+fa+T9j9P90uIzJf9R/7EPDubaTwWeYPLq1TJtfno6RvfLh4bInh8jiPtalFlkwsEb2n258oo2j3XVOP87UuU+2cdC95fRTTVzbebaby1mT7z9o43N3l2dNPLd/uo2r3ZFOG32vv8o5tvle0Ddu9H1uaL6ucpGRLvq1b5VBI8u4Z3q9lYcGlZF34xa8rnJrZNI+cqY1XWdoGd1Yo5zhvtevL1Neq09h9PVePXhL43P+lXPrvZklqDePNH3i7zc3mK7Bi4vTYG5kZLYwbwCfad1djCMnzqL/27f/N6HiwPyKZAH6kDTnth3gtFV34hN1A3JYNaKc/2xEDmsSdE/lyijj2EWHvKObGM+uMsjbvpnx7CqD/r2+q3l33N3i3sfFLSB3+2EJ/bRtZXx7SMK9g6tDeY1GEodd90Du8KGI8EfuOYzf7tP79ZxvD+mo9z/IGz6EsvfM90K+3f1hPrx9G3KGdX3Iffi9Odfu9uh+WO8+jGt3aSy/uvcF7u2HPvT1PpTPy3ht+1AelvEzGu5fNfduhiviD/x+Q2UhAzGMF98feHcznKr5GfrnBtk7Gr4xX3+lZW4/VOAa/xn8vCZzcj9ynLvt+thb+S6Gb1uV7/MmNnAetx7f70N+vJHz2i2rY+7hePBT7PNP6qzqkbsnO1iaUxE7aVImZXq3iX4i6e/nOrcapqB86vn+ng7hDnWC0/cl+OMNhG+rJe1+aiPy+LBL1u4/HwXOyROKkKuhBtcwE5v737vLamNlri9zbEsfWz+rvpv50/ceCvkLo+nq/Ep9h2n60Wqt9QXYQznlLq+tLZ8e3+eqBThiP2XYfob9vMamlnt7D2hA/THYjT42SbEd46pfqLHxfer1RVXnzsh91BnPAxRHZej+iem1kXuqfz9QcU9Aupr8Eh31785RLUf7MKUMvxvLyLDxbvxcAuX+Zg2/Ebizp5df0f92Xn+be/mZmUX8Jkbh24m56T193hXzbayf1yObmm9QOKTcLprvEBT5PrXZfIcekJQzfl995Uyvv1a9tKX5Dgk6fhaaC8qs30NjZqzA79k99Xc=
*/