/* Flyweight class. 
 *
 * Copyright 2006-2015 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_FLYWEIGHT_HPP
#define BOOST_FLYWEIGHT_FLYWEIGHT_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <algorithm>
#include <boost/detail/workaround.hpp>
#include <boost/flyweight/detail/default_value_policy.hpp>
#include <boost/flyweight/detail/flyweight_core.hpp>
#include <boost/flyweight/detail/perfect_fwd.hpp>
#include <boost/flyweight/factory_tag.hpp>
#include <boost/flyweight/flyweight_fwd.hpp>
#include <boost/flyweight/locking_tag.hpp>
#include <boost/flyweight/simple_locking_fwd.hpp>
#include <boost/flyweight/static_holder_fwd.hpp>
#include <boost/flyweight/hashed_factory_fwd.hpp>
#include <boost/flyweight/holder_tag.hpp>
#include <boost/flyweight/refcounted_fwd.hpp>
#include <boost/flyweight/tag.hpp>
#include <boost/flyweight/tracking_tag.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/or.hpp>
#include <boost/parameter/binding.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/swap.hpp>

#if !defined(BOOST_NO_SFINAE)&&!defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <initializer_list>
#endif

#if BOOST_WORKAROUND(BOOST_MSVC,BOOST_TESTED_AT(1400))
#pragma warning(push)
#pragma warning(disable:4520)  /* multiple default ctors */
#pragma warning(disable:4521)  /* multiple copy ctors */
#endif

namespace boost{
  
namespace flyweights{

namespace detail{

/* Used for the detection of unmatched template args in a
 * flyweight instantiation.
 */

struct unmatched_arg;

/* Boost.Parameter structures for use in flyweight.
 * NB: these types are derived from instead of typedef'd to force their
 * instantiation, which solves http://bugs.sun.com/view_bug.do?bug_id=6782987
 * as found out by Simon Atanasyan.
 */

struct flyweight_signature:
  parameter::parameters<
    parameter::optional<
      parameter::deduced<tag<> >,
      detail::is_tag<boost::mpl::_>
    >,
    parameter::optional<
      parameter::deduced<tracking<> >,
      is_tracking<boost::mpl::_>
    >,
    parameter::optional<
      parameter::deduced<factory<> >,
      is_factory<boost::mpl::_>
    >,
    parameter::optional<
      parameter::deduced<locking<> >,
      is_locking<boost::mpl::_>
    >,
    parameter::optional<
      parameter::deduced<holder<> >,
      is_holder<boost::mpl::_>
    >
  >
{};

struct flyweight_unmatched_signature:
  parameter::parameters<
    parameter::optional<
      parameter::deduced<
        detail::unmatched_arg
      >,
      mpl::not_<
        mpl::or_<
          detail::is_tag<boost::mpl::_>,
          is_tracking<boost::mpl::_>,
          is_factory<boost::mpl::_>,
          is_locking<boost::mpl::_>,
          is_holder<boost::mpl::_>
        >
      >
    >
  >
{};

} /* namespace flyweights::detail */

template<
  typename T,
  typename Arg1,typename Arg2,typename Arg3,typename Arg4,typename Arg5
>
class flyweight
{
private:
  typedef typename mpl::if_<
    detail::is_value<T>,
    T,
    detail::default_value_policy<T>
  >::type                                 value_policy;
  typedef typename detail::
  flyweight_signature::bind<
    Arg1,Arg2,Arg3,Arg4,Arg5
  >::type                                 args;
  typedef typename parameter::binding<
    args,tag<>,mpl::na
  >::type                                 tag_type;
  typedef typename parameter::binding<
    args,tracking<>,refcounted
  >::type                                 tracking_policy;
  typedef typename parameter::binding<
    args,factory<>,hashed_factory<>
  >::type                                 factory_specifier;
  typedef typename parameter::binding<
    args,locking<>,simple_locking
  >::type                                 locking_policy;
  typedef typename parameter::binding<
    args,holder<>,static_holder
  >::type                                 holder_specifier;

  typedef typename detail::
  flyweight_unmatched_signature::bind<
    Arg1,Arg2,Arg3,Arg4,Arg5
  >::type                                 unmatched_args;
  typedef typename parameter::binding<
    unmatched_args,detail::unmatched_arg,
    detail::unmatched_arg
  >::type                                 unmatched_arg_detected;

  /* You have passed a type in the specification of a flyweight type that
   * could not be interpreted as a valid argument.
   */
  BOOST_MPL_ASSERT_MSG(
  (is_same<unmatched_arg_detected,detail::unmatched_arg>::value),
  INVALID_ARGUMENT_TO_FLYWEIGHT,
  (flyweight));

  typedef detail::flyweight_core<
    value_policy,tag_type,tracking_policy,
    factory_specifier,locking_policy,
    holder_specifier
  >                                            core;
  typedef typename core::handle_type           handle_type;

public:
  typedef typename value_policy::key_type      key_type;
  typedef typename value_policy::value_type    value_type;

  /* static data initialization */

  static bool init(){return core::init();}

  class initializer
  {
  public:
    initializer():b(init()){}
  private:
    bool b;
  };

  /* construct/copy/destroy */

  flyweight():h(core::insert()){}
  
#define BOOST_FLYWEIGHT_PERFECT_FWD_CTR_BODY(args) \
  :h(core::insert(BOOST_FLYWEIGHT_FORWARD(args))){}

  BOOST_FLYWEIGHT_PERFECT_FWD_WITH_ARGS(
    explicit flyweight,
    BOOST_FLYWEIGHT_PERFECT_FWD_CTR_BODY)

#undef BOOST_FLYWEIGHT_PERFECT_FWD_CTR_BODY

#if !defined(BOOST_NO_SFINAE)&&!defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
  template<typename V>
  flyweight(
    std::initializer_list<V> list,
    typename boost::enable_if<
      boost::is_convertible<std::initializer_list<V>,key_type> >::type* =0):
    h(core::insert(list)){} 
#endif

  flyweight(const flyweight& x):h(x.h){}
  flyweight(flyweight& x):h(x.h){}

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
  flyweight(const flyweight&& x):h(x.h){}
  flyweight(flyweight&& x):h(x.h){}
#endif

#if !defined(BOOST_NO_SFINAE)&&!defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
  template<typename V>
  typename boost::enable_if<
    boost::is_convertible<std::initializer_list<V>,key_type>,flyweight&>::type
  operator=(std::initializer_list<V> list)
  {
    return operator=(flyweight(list));
  }
#endif

  flyweight& operator=(const flyweight& x){h=x.h;return *this;}
  flyweight& operator=(const value_type& x){return operator=(flyweight(x));}

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
  flyweight& operator=(value_type&& x)
  {
    return operator=(flyweight(std::move(x)));
  }
#endif

  /* convertibility to underlying type */
  
  const key_type&   get_key()const{return core::key(h);}
  const value_type& get()const{return core::value(h);}
  operator const    value_type&()const{return get();}
  
  /* exact type equality  */
    
  friend bool operator==(const flyweight& x,const flyweight& y)
  {
    return &x.get()==&y.get();
  }

  /* modifiers */

  void swap(flyweight& x){boost::swap(h,x.h);}
  
private:
  handle_type h;
};

#define BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(n)            \
typename Arg##n##1,typename Arg##n##2,typename Arg##n##3, \
typename Arg##n##4,typename Arg##n##5
#define BOOST_FLYWEIGHT_TEMPL_ARGS(n) \
Arg##n##1,Arg##n##2,Arg##n##3,Arg##n##4,Arg##n##5

/* Comparison. Unlike exact type comparison defined above, intertype
 * comparison just forwards to the underlying objects.
 */

template<
  typename T1,BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(1),
  typename T2,BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(2)
>
bool operator==(
  const flyweight<T1,BOOST_FLYWEIGHT_TEMPL_ARGS(1)>& x,
  const flyweight<T2,BOOST_FLYWEIGHT_TEMPL_ARGS(2)>& y)
{
  return x.get()==y.get();
}

template<
  typename T1,BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(1),
  typename T2,BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(2)
>
bool operator<(
  const flyweight<T1,BOOST_FLYWEIGHT_TEMPL_ARGS(1)>& x,
  const flyweight<T2,BOOST_FLYWEIGHT_TEMPL_ARGS(2)>& y)
{
  return x.get()<y.get();
}

#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
template<
  typename T1,BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(1),
  typename T2
>
bool operator==(
  const flyweight<T1,BOOST_FLYWEIGHT_TEMPL_ARGS(1)>& x,const T2& y)
{
  return x.get()==y;
}

template<
  typename T1,
  typename T2,BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(2)
>
bool operator==(
  const T1& x,const flyweight<T2,BOOST_FLYWEIGHT_TEMPL_ARGS(2)>& y)
{
  return x==y.get();
}

template<
  typename T1,BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(1),
  typename T2
>
bool operator<(
  const flyweight<T1,BOOST_FLYWEIGHT_TEMPL_ARGS(1)>& x,const T2& y)
{
  return x.get()<y;
}

template<
  typename T1,
  typename T2,BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(2)
>
bool operator<(
  const T1& x,const flyweight<T2,BOOST_FLYWEIGHT_TEMPL_ARGS(2)>& y)
{
  return x<y.get();
}
#endif /* !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING) */

/* rest of comparison operators */

#define BOOST_FLYWEIGHT_COMPLETE_COMP_OPS(t,a1,a2)                            \
template<t>                                                                   \
inline bool operator!=(const a1& x,const a2& y)                               \
{                                                                             \
  return !(x==y);                                                             \
}                                                                             \
                                                                              \
template<t>                                                                   \
inline bool operator>(const a1& x,const a2& y)                                \
{                                                                             \
  return y<x;                                                                 \
}                                                                             \
                                                                              \
template<t>                                                                   \
inline bool operator>=(const a1& x,const a2& y)                               \
{                                                                             \
  return !(x<y);                                                              \
}                                                                             \
                                                                              \
template<t>                                                                   \
inline bool operator<=(const a1& x,const a2& y)                               \
{                                                                             \
  return !(y<x);                                                              \
}

BOOST_FLYWEIGHT_COMPLETE_COMP_OPS(
  typename T1 BOOST_PP_COMMA()
  BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(1) BOOST_PP_COMMA()
  typename T2 BOOST_PP_COMMA()
  BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(2),
  flyweight<
    T1 BOOST_PP_COMMA() BOOST_FLYWEIGHT_TEMPL_ARGS(1)
  >,
  flyweight<
    T2 BOOST_PP_COMMA() BOOST_FLYWEIGHT_TEMPL_ARGS(2)
  >)

#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
BOOST_FLYWEIGHT_COMPLETE_COMP_OPS(
  typename T1 BOOST_PP_COMMA()
  BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(1) BOOST_PP_COMMA()
  typename T2,
  flyweight<
    T1 BOOST_PP_COMMA() BOOST_FLYWEIGHT_TEMPL_ARGS(1)
  >,
  T2)
  
BOOST_FLYWEIGHT_COMPLETE_COMP_OPS(
  typename T1 BOOST_PP_COMMA()
  typename T2 BOOST_PP_COMMA() 
  BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(2),
  T1,
  flyweight<
    T2 BOOST_PP_COMMA() BOOST_FLYWEIGHT_TEMPL_ARGS(2)
  >)
#endif /* !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING) */

/* specialized algorithms */

template<typename T,BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(_)>
void swap(
  flyweight<T,BOOST_FLYWEIGHT_TEMPL_ARGS(_)>& x,
  flyweight<T,BOOST_FLYWEIGHT_TEMPL_ARGS(_)>& y)
{
  x.swap(y);
}

template<
  BOOST_TEMPLATED_STREAM_ARGS(ElemType,Traits)
  BOOST_TEMPLATED_STREAM_COMMA
  typename T,BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(_)
>
BOOST_TEMPLATED_STREAM(ostream,ElemType,Traits)& operator<<(
  BOOST_TEMPLATED_STREAM(ostream,ElemType,Traits)& out,
  const flyweight<T,BOOST_FLYWEIGHT_TEMPL_ARGS(_)>& x)
{
  return out<<x.get();
}

template<
  BOOST_TEMPLATED_STREAM_ARGS(ElemType,Traits)
  BOOST_TEMPLATED_STREAM_COMMA
  typename T,BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(_)
>
BOOST_TEMPLATED_STREAM(istream,ElemType,Traits)& operator>>(
  BOOST_TEMPLATED_STREAM(istream,ElemType,Traits)& in,
  flyweight<T,BOOST_FLYWEIGHT_TEMPL_ARGS(_)>& x)
{
  typedef typename flyweight<
    T,BOOST_FLYWEIGHT_TEMPL_ARGS(_)
  >::value_type                     value_type;

  /* value_type need not be default ctble but must be copy ctble */
  value_type t(x.get());
  in>>t;
  x=t;
  return in;
}

} /* namespace flyweights */

} /* namespace boost */

#if !defined(BOOST_FLYWEIGHT_DISABLE_HASH_SUPPORT)

/* hash support */

#if !defined(BOOST_NO_CXX11_HDR_FUNCTIONAL)
namespace std{

template<typename T,BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(_)>
BOOST_FLYWEIGHT_STD_HASH_STRUCT_KEYWORD
hash<boost::flyweight<T,BOOST_FLYWEIGHT_TEMPL_ARGS(_)> >
{
public:
  typedef std::size_t                result_type;
  typedef boost::flyweight<
    T,BOOST_FLYWEIGHT_TEMPL_ARGS(_)> argument_type;

  result_type operator()(const argument_type& x)const
  {
    typedef typename argument_type::value_type value_type;

    std::hash<const value_type*> h;
    return h(&x.get());
  }
};

} /* namespace std */
#endif /* !defined(BOOST_NO_CXX11_HDR_FUNCTIONAL) */

namespace boost{
#if !defined(BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP)
namespace flyweights{
#endif

template<typename T,BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(_)>
std::size_t hash_value(const flyweight<T,BOOST_FLYWEIGHT_TEMPL_ARGS(_)>& x)
{
  typedef typename flyweight<
    T,BOOST_FLYWEIGHT_TEMPL_ARGS(_)
  >::value_type                     value_type;

  boost::hash<const value_type*> h;
  return h(&x.get());
}

#if !defined(BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP)
} /* namespace flyweights */
#endif
} /* namespace boost */
#endif /* !defined(BOOST_FLYWEIGHT_DISABLE_HASH_SUPPORT) */

#undef BOOST_FLYWEIGHT_COMPLETE_COMP_OPS
#undef BOOST_FLYWEIGHT_TEMPL_ARGS
#undef BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS

#if BOOST_WORKAROUND(BOOST_MSVC,BOOST_TESTED_AT(1400))
#pragma warning(pop)
#endif

#endif

/* flyweight.hpp
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
*/