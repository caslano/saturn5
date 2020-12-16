/* Copyright 2003-2019 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_MEM_FUN_HPP
#define BOOST_MULTI_INDEX_MEM_FUN_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/mpl/if.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/enable_if.hpp>

#if !defined(BOOST_NO_SFINAE)
#include <boost/type_traits/is_convertible.hpp>
#endif

namespace boost{

template<class T> class reference_wrapper; /* fwd decl. */

namespace multi_index{

/* mem_fun implements a read-only key extractor based on a given non-const
 * member function of a class.
 * Also, the following variations are provided:
 *   const_mem_fun:    const member functions
 *   volatile_mem_fun: volatile member functions
 *   cv_mem_fun:       const volatile member functions
 *   ref_mem_fun:      ref-qualifed member functions (C++11)
 *   cref_mem_fun:     const ref-qualifed member functions (C++11)
 *   vref_mem_fun:     volatile ref-qualifed member functions (C++11)
 *   cvref_mem_fun:    const volatile ref-qualifed member functions (C++11)
 *
 * All of these classes are overloaded to support boost::referece_wrappers
 * of T and "chained pointers" to T's. By chained pointer to T we mean a type
 * P such that, given a p of Type P
 *   *...n...*x is convertible to T&, for some n>=1.
 * Examples of chained pointers are raw and smart pointers, iterators and
 * arbitrary combinations of these (vg. T** or unique_ptr<T*>.)
 */

namespace detail{

template<
  class Class,typename Type,
  typename PtrToMemberFunctionType,PtrToMemberFunctionType PtrToMemberFunction
>
struct const_mem_fun_impl
{
  typedef typename remove_reference<Type>::type result_type;

  template<typename ChainedPtr>

#if !defined(BOOST_NO_SFINAE)
  typename disable_if<
    is_convertible<const ChainedPtr&,const Class&>,Type>::type
#else
  Type
#endif

  operator()(const ChainedPtr& x)const
  {
    return operator()(*x);
  }

  Type operator()(const Class& x)const
  {
    return (x.*PtrToMemberFunction)();
  }

  Type operator()(const reference_wrapper<const Class>& x)const
  { 
    return operator()(x.get());
  }

  Type operator()(const reference_wrapper<Class>& x)const
  { 
    return operator()(x.get());
  }
};

template<
  class Class,typename Type,
  typename PtrToMemberFunctionType,PtrToMemberFunctionType PtrToMemberFunction
>
struct mem_fun_impl
{
  typedef typename remove_reference<Type>::type result_type;

  template<typename ChainedPtr>

#if !defined(BOOST_NO_SFINAE)
  typename disable_if<
    is_convertible<ChainedPtr&,Class&>,Type>::type
#else
  Type
#endif

  operator()(const ChainedPtr& x)const
  {
    return operator()(*x);
  }

  Type operator()(Class& x)const
  {
    return (x.*PtrToMemberFunction)();
  }

  Type operator()(const reference_wrapper<Class>& x)const
  { 
    return operator()(x.get());
  }
};

} /* namespace multi_index::detail */

template<class Class,typename Type,Type (Class::*PtrToMemberFunction)()const>
struct const_mem_fun:detail::const_mem_fun_impl<
  Class,Type,Type (Class::*)()const,PtrToMemberFunction
>{};

template<
  class Class,typename Type,
  Type (Class::*PtrToMemberFunction)()const volatile
>
struct cv_mem_fun:detail::const_mem_fun_impl<
  Class,Type,Type (Class::*)()const volatile,PtrToMemberFunction
>{};

template<class Class,typename Type,Type (Class::*PtrToMemberFunction)()>
struct mem_fun:
  detail::mem_fun_impl<Class,Type,Type (Class::*)(),PtrToMemberFunction>{};

template<
  class Class,typename Type,Type (Class::*PtrToMemberFunction)()volatile
>
struct volatile_mem_fun:detail::mem_fun_impl<
  Class,Type,Type (Class::*)()volatile,PtrToMemberFunction
>{};

#if !defined(BOOST_NO_CXX11_REF_QUALIFIERS)

template<
  class Class,typename Type,Type (Class::*PtrToMemberFunction)()const&
>
struct cref_mem_fun:detail::const_mem_fun_impl<
  Class,Type,Type (Class::*)()const&,PtrToMemberFunction
>{};

template<
  class Class,typename Type,
  Type (Class::*PtrToMemberFunction)()const volatile&
>
struct cvref_mem_fun:detail::const_mem_fun_impl<
  Class,Type,Type (Class::*)()const volatile&,PtrToMemberFunction
>{};

template<class Class,typename Type,Type (Class::*PtrToMemberFunction)()&>
struct ref_mem_fun:
  detail::mem_fun_impl<Class,Type,Type (Class::*)()&,PtrToMemberFunction>{};

template<
  class Class,typename Type,Type (Class::*PtrToMemberFunction)()volatile&
>
struct vref_mem_fun:detail::mem_fun_impl<
  Class,Type,Type (Class::*)()volatile&,PtrToMemberFunction
>{};

#endif

/* MSVC++ 6.0 has problems with const member functions as non-type template
 * parameters, somehow it takes them as non-const. const_mem_fun_explicit
 * workarounds this deficiency by accepting an extra type parameter that
 * specifies the signature of the member function. The workaround was found at:
 *   Daniel, C.:"Re: weird typedef problem in VC",
 *   news:microsoft.public.vc.language, 21st nov 2002, 
 *   http://groups.google.com/groups?
 *     hl=en&lr=&ie=UTF-8&selm=ukwvg3O0BHA.1512%40tkmsftngp05
 *
 * MSVC++ 6.0 support has been dropped and [const_]mem_fun_explicit is
 * deprecated.
 */

template<
  class Class,typename Type,
  typename PtrToMemberFunctionType,PtrToMemberFunctionType PtrToMemberFunction
>
struct const_mem_fun_explicit
{
  typedef typename remove_reference<Type>::type result_type;

  template<typename ChainedPtr>

#if !defined(BOOST_NO_SFINAE)
  typename disable_if<
    is_convertible<const ChainedPtr&,const Class&>,Type>::type
#else
  Type
#endif

  operator()(const ChainedPtr& x)const
  {
    return operator()(*x);
  }

  Type operator()(const Class& x)const
  {
    return (x.*PtrToMemberFunction)();
  }

  Type operator()(const reference_wrapper<const Class>& x)const
  { 
    return operator()(x.get());
  }

  Type operator()(const reference_wrapper<Class>& x)const
  { 
    return operator()(x.get());
  }
};

template<
  class Class,typename Type,
  typename PtrToMemberFunctionType,PtrToMemberFunctionType PtrToMemberFunction
>
struct mem_fun_explicit
{
  typedef typename remove_reference<Type>::type result_type;

  template<typename ChainedPtr>

#if !defined(BOOST_NO_SFINAE)
  typename disable_if<
    is_convertible<ChainedPtr&,Class&>,Type>::type
#else
  Type
#endif

  operator()(const ChainedPtr& x)const
  {
    return operator()(*x);
  }

  Type operator()(Class& x)const
  {
    return (x.*PtrToMemberFunction)();
  }

  Type operator()(const reference_wrapper<Class>& x)const
  { 
    return operator()(x.get());
  }
};

/* BOOST_MULTI_INDEX_CONST_MEM_FUN and BOOST_MULTI_INDEX_MEM_FUN used to
 * resolve to [const_]mem_fun_explicit for MSVC++ 6.0 and to
 * [const_]mem_fun otherwise. Support for this compiler having been dropped,
 * they are now just wrappers over [const_]mem_fun kept for backwards-
 * compatibility reasons.
 */

#define BOOST_MULTI_INDEX_CONST_MEM_FUN(Class,Type,MemberFunName) \
::boost::multi_index::const_mem_fun< Class,Type,&Class::MemberFunName >
#define BOOST_MULTI_INDEX_MEM_FUN(Class,Type,MemberFunName) \
::boost::multi_index::mem_fun< Class,Type,&Class::MemberFunName >

} /* namespace multi_index */

} /* namespace boost */

#endif

/* mem_fun.hpp
ydivD2N0t1bnLRjrqIPYXpUqiwWHuF3bWnHVP+l4a8Vx/3yX2jGbg75aKxC3PN6GwzMCxJ1v4gZtZViaaMNhuuQOI+JqmPS1ReSc2c7oZvYRN7mD4czksM5eZOIG6GAQ87Rrp4lRk2udFiTWSleNzfbgJk6HJSdpPfEaGgMPIQdd9aSCyPjCNYEOvQllKLWG+oyeuhZgWPUh7ZeEBiVdpP7DdjEa1ALSDl+b0vjdvVdTmmSjb4Y/cx1Cq44nB2uE9wfXJfT+Jr4tUbTdQIPzKTLYqsTxHC69XhsGj9BQ1tl2HBylIWbf9VswcKRGMGfaMXCshpjdN6CYGrLYhXuUiHkhw7CiYdkm9nAMLxrx9c1xWDT2zodhWLYRc+yGTYx5/+g7FAP3tx+okkIZ4V6TjiJYPLE3od4AnUK7NMPJF2OerQ+qPb6eUeUwVmGeK6EDfAd0zsDpC1e5tgcs8/U+jUrPs4ur9j1irveTdC06mAdu4oWBLe53AGbblvV+N8PbbukERZkJ5QKDLJBdWJdeLPW8PczfpyoVBqq7KdG/3txRtMVNqRud6K0hbbnDaRBNeS+uJ0hjd+Wfq75jDVYKK52bxpFOWmJIn5pAOmmBYbqXka4afbhP3s6+s3Is7eA0KMcd0Pcm0lqDBeJemeNW1ZE/od91Eug5q0jmgxPpWJlIO34NpDXuRPzAoKmlh/oQvibSSYXPMRmHr4UYWulI/wTSeaVjP9iFdKhAHkPx2pxmlvudBh3KjT5Er4M0mJKG6zd8x7Ed5RF/jwHxDEw6sOOduJvvNumyyFp9AnfE9b0RPCd+FI/hVlpRnjqBoI0FY4uO3T2U51AZZ15aFqXAcpqxvfbxNJK8sEvHSYYMJI2D+nzlUca5Y1aGaVCmwljazby5lG+2cLLS8cJAyL5Nsza2ofNW8ryVeRincZkBA7apWZ7jlCcToeuXiZ3rzQrbFuCdg3WjPKUXJkloZcJY2s3yPJ3ypSIr/QJOFYcLfsWwpvP2QoovRZR7TpFlheCjk+8/Xkd5CpEWvhfA1r2tD6CN4FGGbcIPoxL8YjWHI9qAdV18hfE6MpNpHkROKRrDlJ/N/pLx2aLwI6tIIleYw7diwzr8J6/D0i9D34szMRyZhk/NR/M69KxAwim+WYf7KE8hytjKgtIuBBv9Rr6mKM+h2IvjAHNF7iZYGH+H4meD2A1Sy8mELLPy3dKw44SPNnwLZ1boJZkjKkPuAchVdaaL/a6DZ4yM1xNFnkR5kLuiOppcmF9VB4Un5EEdaFPYxr62dzH+XIAHLtlHbIEHwAvLawPJPZA+P/rwSL8/Lx2bNOKRvozJcYXj5UUcu+FQTlcKWK5ODo0zy3cy3kAUiWNbTuIPedVQPQBmInKevWHrfsr4MxEXaRYVONAlu972wukMRg9kffYS70ueE5VuahVidQ1rAEreNWMnTS6zOyVxHsLNKMVGzTFdfEtB8Y4l8tT2U7eMkQP8i8Hh6GN7/bXVFXliBTEV+z30CkDWhMNUVipSNyxjx/KUKDIwgaWP9pUXjjF7RGh5cWY7Fc+mPIQ+gHe/sP+nNJ3Z2IvK0CkVh1JO8W6O7lPHlnmfcnwntxyZyCZcOoUjfihrv6ueyMAA4rnFcfFEJscTCVxYinPy5kg38NCfra/nV8abiShJw6iwMoGVeaArfROqyzSQIZkj9JFCz/Dfu2zcH7CKFByoETnyGa/MAa+N+92y9m16ei/otzBV8GCOQH/VtLTb3AjpxNLJYzm+hdg5JRCtnBjLs2eswV4UyC4VD/121Cqj4UvvFT0eVyxzwyzOhTwFusc06un6Pfsm2XfINtMzP3RHvBtv7E0oRu9fzj6GYOQ=
*/