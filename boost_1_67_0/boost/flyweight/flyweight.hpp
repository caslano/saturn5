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