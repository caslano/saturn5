/* Copyright 2003-2015 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_COMPOSITE_KEY_HPP
#define BOOST_MULTI_INDEX_COMPOSITE_KEY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/functional/hash_fwd.hpp>
#include <boost/multi_index/detail/access_specifier.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/list/at.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp> 
#include <boost/static_assert.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>
#include <functional>

#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
#include <boost/ref.hpp>
#endif

#if !defined(BOOST_NO_SFINAE)
#include <boost/type_traits/is_convertible.hpp>
#endif

#if !defined(BOOST_NO_CXX11_HDR_TUPLE)&&\
    !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#include <boost/multi_index/detail/cons_stdtuple.hpp>
#endif

/* A composite key stores n key extractors and "computes" the
 * result on a given value as a packed reference to the value and
 * the composite key itself. Actual invocations to the component
 * key extractors are lazily performed when executing an operation
 * on composite_key results (equality, comparison, hashing.)
 * As the other key extractors in Boost.MultiIndex, composite_key<T,...>
 * is  overloaded to work on chained pointers to T and reference_wrappers
 * of T.
 */

/* This user_definable macro limits the number of elements of a composite
 * key; useful for shortening resulting symbol names (MSVC++ 6.0, for
 * instance has problems coping with very long symbol names.)
 * NB: This cannot exceed the maximum number of arguments of
 * boost::tuple. In Boost 1.32, the limit is 10.
 */

#if !defined(BOOST_MULTI_INDEX_LIMIT_COMPOSITE_KEY_SIZE)
#define BOOST_MULTI_INDEX_LIMIT_COMPOSITE_KEY_SIZE 10
#endif

/* maximum number of key extractors in a composite key */

#if BOOST_MULTI_INDEX_LIMIT_COMPOSITE_KEY_SIZE<10 /* max length of a tuple */
#define BOOST_MULTI_INDEX_COMPOSITE_KEY_SIZE \
  BOOST_MULTI_INDEX_LIMIT_COMPOSITE_KEY_SIZE
#else
#define BOOST_MULTI_INDEX_COMPOSITE_KEY_SIZE 10
#endif

/* BOOST_PP_ENUM of BOOST_MULTI_INDEX_COMPOSITE_KEY_SIZE elements */

#define BOOST_MULTI_INDEX_CK_ENUM(macro,data)                                \
  BOOST_PP_ENUM(BOOST_MULTI_INDEX_COMPOSITE_KEY_SIZE,macro,data)

/* BOOST_PP_ENUM_PARAMS of BOOST_MULTI_INDEX_COMPOSITE_KEY_SIZE elements */

#define BOOST_MULTI_INDEX_CK_ENUM_PARAMS(param)                              \
  BOOST_PP_ENUM_PARAMS(BOOST_MULTI_INDEX_COMPOSITE_KEY_SIZE,param)

/* if n==0 ->   text0
 * otherwise -> textn=tuples::null_type
 */

#define BOOST_MULTI_INDEX_CK_TEMPLATE_PARM(z,n,text)                         \
  typename BOOST_PP_CAT(text,n) BOOST_PP_EXPR_IF(n,=tuples::null_type)

/* const textn& kn=textn() */

#define BOOST_MULTI_INDEX_CK_CTOR_ARG(z,n,text)                              \
  const BOOST_PP_CAT(text,n)& BOOST_PP_CAT(k,n) = BOOST_PP_CAT(text,n)()

/* typename list(0)<list(1),n>::type */

#define BOOST_MULTI_INDEX_CK_APPLY_METAFUNCTION_N(z,n,list)                  \
  BOOST_DEDUCED_TYPENAME BOOST_PP_LIST_AT(list,0)<                           \
    BOOST_PP_LIST_AT(list,1),n                                               \
  >::type

namespace boost{

template<class T> class reference_wrapper; /* fwd decl. */

namespace multi_index{

namespace detail{

/* n-th key extractor of a composite key */

template<typename CompositeKey,int N>
struct nth_key_from_value
{
  typedef typename CompositeKey::key_extractor_tuple key_extractor_tuple;
  typedef typename mpl::eval_if_c<
    N<tuples::length<key_extractor_tuple>::value,
    tuples::element<N,key_extractor_tuple>,
    mpl::identity<tuples::null_type>
  >::type                                            type;
};

/* nth_composite_key_##name<CompositeKey,N>::type yields
 * functor<nth_key_from_value<CompositeKey,N> >, or tuples::null_type
 * if N exceeds the length of the composite key.
 */

#define BOOST_MULTI_INDEX_CK_NTH_COMPOSITE_KEY_FUNCTOR(name,functor)         \
template<typename KeyFromValue>                                              \
struct BOOST_PP_CAT(key_,name)                                               \
{                                                                            \
  typedef functor<typename KeyFromValue::result_type> type;                  \
};                                                                           \
                                                                             \
template<>                                                                   \
struct BOOST_PP_CAT(key_,name)<tuples::null_type>                            \
{                                                                            \
  typedef tuples::null_type type;                                            \
};                                                                           \
                                                                             \
template<typename CompositeKey,int  N>                                       \
struct BOOST_PP_CAT(nth_composite_key_,name)                                 \
{                                                                            \
  typedef typename nth_key_from_value<CompositeKey,N>::type key_from_value;  \
  typedef typename BOOST_PP_CAT(key_,name)<key_from_value>::type type;       \
};

/* nth_composite_key_equal_to
 * nth_composite_key_less
 * nth_composite_key_greater
 * nth_composite_key_hash
 */

BOOST_MULTI_INDEX_CK_NTH_COMPOSITE_KEY_FUNCTOR(equal_to,std::equal_to)
BOOST_MULTI_INDEX_CK_NTH_COMPOSITE_KEY_FUNCTOR(less,std::less)
BOOST_MULTI_INDEX_CK_NTH_COMPOSITE_KEY_FUNCTOR(greater,std::greater)
BOOST_MULTI_INDEX_CK_NTH_COMPOSITE_KEY_FUNCTOR(hash,boost::hash)

/* used for defining equality and comparison ops of composite_key_result */

#define BOOST_MULTI_INDEX_CK_IDENTITY_ENUM_MACRO(z,n,text) text

struct generic_operator_equal
{
  template<typename T,typename Q>
  bool operator()(const T& x,const Q& y)const{return x==y;}
};

typedef tuple<
  BOOST_MULTI_INDEX_CK_ENUM(
    BOOST_MULTI_INDEX_CK_IDENTITY_ENUM_MACRO,
    detail::generic_operator_equal)>          generic_operator_equal_tuple;

struct generic_operator_less
{
  template<typename T,typename Q>
  bool operator()(const T& x,const Q& y)const{return x<y;}
};

typedef tuple<
  BOOST_MULTI_INDEX_CK_ENUM(
    BOOST_MULTI_INDEX_CK_IDENTITY_ENUM_MACRO,
    detail::generic_operator_less)>           generic_operator_less_tuple;

/* Metaprogramming machinery for implementing equality, comparison and
 * hashing operations of composite_key_result.
 *
 * equal_* checks for equality between composite_key_results and
 * between those and tuples, accepting a tuple of basic equality functors.
 * compare_* does lexicographical comparison.
 * hash_* computes a combination of elementwise hash values.
 */

template
<
  typename KeyCons1,typename Value1,
  typename KeyCons2, typename Value2,
  typename EqualCons
>
struct equal_ckey_ckey; /* fwd decl. */

template
<
  typename KeyCons1,typename Value1,
  typename KeyCons2, typename Value2,
  typename EqualCons
>
struct equal_ckey_ckey_terminal
{
  static bool compare(
    const KeyCons1&,const Value1&,
    const KeyCons2&,const Value2&,
    const EqualCons&)
  {
    return true;
  }
};

template
<
  typename KeyCons1,typename Value1,
  typename KeyCons2, typename Value2,
  typename EqualCons
>
struct equal_ckey_ckey_normal
{
  static bool compare(
    const KeyCons1& c0,const Value1& v0,
    const KeyCons2& c1,const Value2& v1,
    const EqualCons& eq)
  {
    if(!eq.get_head()(c0.get_head()(v0),c1.get_head()(v1)))return false;
    return equal_ckey_ckey<
      BOOST_DEDUCED_TYPENAME KeyCons1::tail_type,Value1,
      BOOST_DEDUCED_TYPENAME KeyCons2::tail_type,Value2,
      BOOST_DEDUCED_TYPENAME EqualCons::tail_type
    >::compare(c0.get_tail(),v0,c1.get_tail(),v1,eq.get_tail());
  }
};

template
<
  typename KeyCons1,typename Value1,
  typename KeyCons2, typename Value2,
  typename EqualCons
>
struct equal_ckey_ckey:
  mpl::if_<
    mpl::or_<
      is_same<KeyCons1,tuples::null_type>,
      is_same<KeyCons2,tuples::null_type>
    >,
    equal_ckey_ckey_terminal<KeyCons1,Value1,KeyCons2,Value2,EqualCons>,
    equal_ckey_ckey_normal<KeyCons1,Value1,KeyCons2,Value2,EqualCons>
  >::type
{
};

template
<
  typename KeyCons,typename Value,
  typename ValCons,typename EqualCons
>
struct equal_ckey_cval; /* fwd decl. */

template
<
  typename KeyCons,typename Value,
  typename ValCons,typename EqualCons
>
struct equal_ckey_cval_terminal
{
  static bool compare(
    const KeyCons&,const Value&,const ValCons&,const EqualCons&)
  {
    return true;
  }

  static bool compare(
    const ValCons&,const KeyCons&,const Value&,const EqualCons&)
  {
    return true;
  }
};

template
<
  typename KeyCons,typename Value,
  typename ValCons,typename EqualCons
>
struct equal_ckey_cval_normal
{
  static bool compare(
    const KeyCons& c,const Value& v,const ValCons& vc,
    const EqualCons& eq)
  {
    if(!eq.get_head()(c.get_head()(v),vc.get_head()))return false;
    return equal_ckey_cval<
      BOOST_DEDUCED_TYPENAME KeyCons::tail_type,Value,
      BOOST_DEDUCED_TYPENAME ValCons::tail_type,
      BOOST_DEDUCED_TYPENAME EqualCons::tail_type
    >::compare(c.get_tail(),v,vc.get_tail(),eq.get_tail());
  }

  static bool compare(
    const ValCons& vc,const KeyCons& c,const Value& v,
    const EqualCons& eq)
  {
    if(!eq.get_head()(vc.get_head(),c.get_head()(v)))return false;
    return equal_ckey_cval<
      BOOST_DEDUCED_TYPENAME KeyCons::tail_type,Value,
      BOOST_DEDUCED_TYPENAME ValCons::tail_type,
      BOOST_DEDUCED_TYPENAME EqualCons::tail_type
    >::compare(vc.get_tail(),c.get_tail(),v,eq.get_tail());
  }
};

template
<
  typename KeyCons,typename Value,
  typename ValCons,typename EqualCons
>
struct equal_ckey_cval:
  mpl::if_<
    mpl::or_<
      is_same<KeyCons,tuples::null_type>,
      is_same<ValCons,tuples::null_type>
    >,
    equal_ckey_cval_terminal<KeyCons,Value,ValCons,EqualCons>,
    equal_ckey_cval_normal<KeyCons,Value,ValCons,EqualCons>
  >::type
{
};

template
<
  typename KeyCons1,typename Value1,
  typename KeyCons2, typename Value2,
  typename CompareCons
>
struct compare_ckey_ckey; /* fwd decl. */

template
<
  typename KeyCons1,typename Value1,
  typename KeyCons2, typename Value2,
  typename CompareCons
>
struct compare_ckey_ckey_terminal
{
  static bool compare(
    const KeyCons1&,const Value1&,
    const KeyCons2&,const Value2&,
    const CompareCons&)
  {
    return false;
  }
};

template
<
  typename KeyCons1,typename Value1,
  typename KeyCons2, typename Value2,
  typename CompareCons
>
struct compare_ckey_ckey_normal
{
  static bool compare(
    const KeyCons1& c0,const Value1& v0,
    const KeyCons2& c1,const Value2& v1,
    const CompareCons& comp)
  {
    if(comp.get_head()(c0.get_head()(v0),c1.get_head()(v1)))return true;
    if(comp.get_head()(c1.get_head()(v1),c0.get_head()(v0)))return false;
    return compare_ckey_ckey<
      BOOST_DEDUCED_TYPENAME KeyCons1::tail_type,Value1,
      BOOST_DEDUCED_TYPENAME KeyCons2::tail_type,Value2,
      BOOST_DEDUCED_TYPENAME CompareCons::tail_type
    >::compare(c0.get_tail(),v0,c1.get_tail(),v1,comp.get_tail());
  }
};

template
<
  typename KeyCons1,typename Value1,
  typename KeyCons2, typename Value2,
  typename CompareCons
>
struct compare_ckey_ckey:
  mpl::if_<
    mpl::or_<
      is_same<KeyCons1,tuples::null_type>,
      is_same<KeyCons2,tuples::null_type>
    >,
    compare_ckey_ckey_terminal<KeyCons1,Value1,KeyCons2,Value2,CompareCons>,
    compare_ckey_ckey_normal<KeyCons1,Value1,KeyCons2,Value2,CompareCons>
  >::type
{
};

template
<
  typename KeyCons,typename Value,
  typename ValCons,typename CompareCons
>
struct compare_ckey_cval; /* fwd decl. */

template
<
  typename KeyCons,typename Value,
  typename ValCons,typename CompareCons
>
struct compare_ckey_cval_terminal
{
  static bool compare(
    const KeyCons&,const Value&,const ValCons&,const CompareCons&)
  {
    return false;
  }

  static bool compare(
    const ValCons&,const KeyCons&,const Value&,const CompareCons&)
  {
    return false;
  }
};

template
<
  typename KeyCons,typename Value,
  typename ValCons,typename CompareCons
>
struct compare_ckey_cval_normal
{
  static bool compare(
    const KeyCons& c,const Value& v,const ValCons& vc,
    const CompareCons& comp)
  {
    if(comp.get_head()(c.get_head()(v),vc.get_head()))return true;
    if(comp.get_head()(vc.get_head(),c.get_head()(v)))return false;
    return compare_ckey_cval<
      BOOST_DEDUCED_TYPENAME KeyCons::tail_type,Value,
      BOOST_DEDUCED_TYPENAME ValCons::tail_type,
      BOOST_DEDUCED_TYPENAME CompareCons::tail_type
    >::compare(c.get_tail(),v,vc.get_tail(),comp.get_tail());
  }

  static bool compare(
    const ValCons& vc,const KeyCons& c,const Value& v,
    const CompareCons& comp)
  {
    if(comp.get_head()(vc.get_head(),c.get_head()(v)))return true;
    if(comp.get_head()(c.get_head()(v),vc.get_head()))return false;
    return compare_ckey_cval<
      BOOST_DEDUCED_TYPENAME KeyCons::tail_type,Value,
      BOOST_DEDUCED_TYPENAME ValCons::tail_type,
      BOOST_DEDUCED_TYPENAME CompareCons::tail_type
    >::compare(vc.get_tail(),c.get_tail(),v,comp.get_tail());
  }
};

template
<
  typename KeyCons,typename Value,
  typename ValCons,typename CompareCons
>
struct compare_ckey_cval:
  mpl::if_<
    mpl::or_<
      is_same<KeyCons,tuples::null_type>,
      is_same<ValCons,tuples::null_type>
    >,
    compare_ckey_cval_terminal<KeyCons,Value,ValCons,CompareCons>,
    compare_ckey_cval_normal<KeyCons,Value,ValCons,CompareCons>
  >::type
{
};

template<typename KeyCons,typename Value,typename HashCons>
struct hash_ckey; /* fwd decl. */

template<typename KeyCons,typename Value,typename HashCons>
struct hash_ckey_terminal
{
  static std::size_t hash(
    const KeyCons&,const Value&,const HashCons&,std::size_t carry)
  {
    return carry;
  }
};

template<typename KeyCons,typename Value,typename HashCons>
struct hash_ckey_normal
{
  static std::size_t hash(
    const KeyCons& c,const Value& v,const HashCons& h,std::size_t carry=0)
  {
    /* same hashing formula as boost::hash_combine */

    carry^=h.get_head()(c.get_head()(v))+0x9e3779b9+(carry<<6)+(carry>>2);
    return hash_ckey<
      BOOST_DEDUCED_TYPENAME KeyCons::tail_type,Value,
      BOOST_DEDUCED_TYPENAME HashCons::tail_type
    >::hash(c.get_tail(),v,h.get_tail(),carry);
  }
};

template<typename KeyCons,typename Value,typename HashCons>
struct hash_ckey:
  mpl::if_<
    is_same<KeyCons,tuples::null_type>,
    hash_ckey_terminal<KeyCons,Value,HashCons>,
    hash_ckey_normal<KeyCons,Value,HashCons>
  >::type
{
};

template<typename ValCons,typename HashCons>
struct hash_cval; /* fwd decl. */

template<typename ValCons,typename HashCons>
struct hash_cval_terminal
{
  static std::size_t hash(const ValCons&,const HashCons&,std::size_t carry)
  {
    return carry;
  }
};

template<typename ValCons,typename HashCons>
struct hash_cval_normal
{
  static std::size_t hash(
    const ValCons& vc,const HashCons& h,std::size_t carry=0)
  {
    carry^=h.get_head()(vc.get_head())+0x9e3779b9+(carry<<6)+(carry>>2);
    return hash_cval<
      BOOST_DEDUCED_TYPENAME ValCons::tail_type,
      BOOST_DEDUCED_TYPENAME HashCons::tail_type
    >::hash(vc.get_tail(),h.get_tail(),carry);
  }
};

template<typename ValCons,typename HashCons>
struct hash_cval:
  mpl::if_<
    is_same<ValCons,tuples::null_type>,
    hash_cval_terminal<ValCons,HashCons>,
    hash_cval_normal<ValCons,HashCons>
  >::type
{
};

} /* namespace multi_index::detail */

/* composite_key_result */

#if defined(BOOST_MSVC)
#pragma warning(push)
#pragma warning(disable:4512)
#endif

template<typename CompositeKey>
struct composite_key_result
{
  typedef CompositeKey                            composite_key_type;
  typedef typename composite_key_type::value_type value_type;

  composite_key_result(
    const composite_key_type& composite_key_,const value_type& value_):
    composite_key(composite_key_),value(value_)
  {}

  const composite_key_type& composite_key;
  const value_type&         value;
};

#if defined(BOOST_MSVC)
#pragma warning(pop)
#endif

/* composite_key */

template<
  typename Value,
  BOOST_MULTI_INDEX_CK_ENUM(BOOST_MULTI_INDEX_CK_TEMPLATE_PARM,KeyFromValue)
>
struct composite_key:
  private tuple<BOOST_MULTI_INDEX_CK_ENUM_PARAMS(KeyFromValue)>
{
private:
  typedef tuple<BOOST_MULTI_INDEX_CK_ENUM_PARAMS(KeyFromValue)> super;

public:
  typedef super                               key_extractor_tuple;
  typedef Value                               value_type;
  typedef composite_key_result<composite_key> result_type;

  composite_key(
    BOOST_MULTI_INDEX_CK_ENUM(BOOST_MULTI_INDEX_CK_CTOR_ARG,KeyFromValue)):
    super(BOOST_MULTI_INDEX_CK_ENUM_PARAMS(k))
  {}

  composite_key(const key_extractor_tuple& x):super(x){}

  const key_extractor_tuple& key_extractors()const{return *this;}
  key_extractor_tuple&       key_extractors(){return *this;}

  template<typename ChainedPtr>

#if !defined(BOOST_NO_SFINAE)
  typename disable_if<
    is_convertible<const ChainedPtr&,const value_type&>,result_type>::type
#else
  result_type
#endif

  operator()(const ChainedPtr& x)const
  {
    return operator()(*x);
  }

  result_type operator()(const value_type& x)const
  {
    return result_type(*this,x);
  }

  result_type operator()(const reference_wrapper<const value_type>& x)const
  {
    return result_type(*this,x.get());
  }

  result_type operator()(const reference_wrapper<value_type>& x)const
  {
    return result_type(*this,x.get());
  }
};

/* comparison operators */

/* == */

template<typename CompositeKey1,typename CompositeKey2>
inline bool operator==(
  const composite_key_result<CompositeKey1>& x,
  const composite_key_result<CompositeKey2>& y)
{
  typedef typename CompositeKey1::key_extractor_tuple key_extractor_tuple1;
  typedef typename CompositeKey1::value_type          value_type1;
  typedef typename CompositeKey2::key_extractor_tuple key_extractor_tuple2;
  typedef typename CompositeKey2::value_type          value_type2;

  BOOST_STATIC_ASSERT(
    tuples::length<key_extractor_tuple1>::value==
    tuples::length<key_extractor_tuple2>::value);

  return detail::equal_ckey_ckey<
    key_extractor_tuple1,value_type1,
    key_extractor_tuple2,value_type2,
    detail::generic_operator_equal_tuple
  >::compare(
    x.composite_key.key_extractors(),x.value,
    y.composite_key.key_extractors(),y.value,
    detail::generic_operator_equal_tuple());
}

template<
  typename CompositeKey,
  BOOST_MULTI_INDEX_CK_ENUM_PARAMS(typename Value)
>
inline bool operator==(
  const composite_key_result<CompositeKey>& x,
  const tuple<BOOST_MULTI_INDEX_CK_ENUM_PARAMS(Value)>& y)
{
  typedef typename CompositeKey::key_extractor_tuple     key_extractor_tuple;
  typedef typename CompositeKey::value_type              value_type;
  typedef tuple<BOOST_MULTI_INDEX_CK_ENUM_PARAMS(Value)> key_tuple;
  
  BOOST_STATIC_ASSERT(
    tuples::length<key_extractor_tuple>::value==
    tuples::length<key_tuple>::value);

  return detail::equal_ckey_cval<
    key_extractor_tuple,value_type,
    key_tuple,detail::generic_operator_equal_tuple
  >::compare(
    x.composite_key.key_extractors(),x.value,
    y,detail::generic_operator_equal_tuple());
}

template
<
  BOOST_MULTI_INDEX_CK_ENUM_PARAMS(typename Value),
  typename CompositeKey
>
inline bool operator==(
  const tuple<BOOST_MULTI_INDEX_CK_ENUM_PARAMS(Value)>& x,
  const composite_key_result<CompositeKey>& y)
{
  typedef typename CompositeKey::key_extractor_tuple     key_extractor_tuple;
  typedef typename CompositeKey::value_type              value_type;
  typedef tuple<BOOST_MULTI_INDEX_CK_ENUM_PARAMS(Value)> key_tuple;
  
  BOOST_STATIC_ASSERT(
    tuples::length<key_extractor_tuple>::value==
    tuples::length<key_tuple>::value);

  return detail::equal_ckey_cval<
    key_extractor_tuple,value_type,
    key_tuple,detail::generic_operator_equal_tuple
  >::compare(
    x,y.composite_key.key_extractors(),
    y.value,detail::generic_operator_equal_tuple());
}

#if !defined(BOOST_NO_CXX11_HDR_TUPLE)&&\
    !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
template<typename CompositeKey,typename... Values>
inline bool operator==(
  const composite_key_result<CompositeKey>& x,
  const std::tuple<Values...>& y)
{
  typedef typename CompositeKey::key_extractor_tuple key_extractor_tuple;
  typedef typename CompositeKey::value_type          value_type;
  typedef std::tuple<Values...>                      key_tuple;
  typedef typename detail::cons_stdtuple_ctor<
    key_tuple>::result_type                          cons_key_tuple;
  
  BOOST_STATIC_ASSERT(
    static_cast<std::size_t>(tuples::length<key_extractor_tuple>::value)==
    std::tuple_size<key_tuple>::value);

  return detail::equal_ckey_cval<
    key_extractor_tuple,value_type,
    cons_key_tuple,detail::generic_operator_equal_tuple
  >::compare(
    x.composite_key.key_extractors(),x.value,
    detail::make_cons_stdtuple(y),detail::generic_operator_equal_tuple());
}

template<typename CompositeKey,typename... Values>
inline bool operator==(
  const std::tuple<Values...>& x,
  const composite_key_result<CompositeKey>& y)
{
  typedef typename CompositeKey::key_extractor_tuple key_extractor_tuple;
  typedef typename CompositeKey::value_type          value_type;
  typedef std::tuple<Values...>                      key_tuple;
  typedef typename detail::cons_stdtuple_ctor<
    key_tuple>::result_type                          cons_key_tuple;

  BOOST_STATIC_ASSERT(
    static_cast<std::size_t>(tuples::length<key_extractor_tuple>::value)==
    std::tuple_size<key_tuple>::value);

  return detail::equal_ckey_cval<
    key_extractor_tuple,value_type,
    cons_key_tuple,detail::generic_operator_equal_tuple
  >::compare(
    detail::make_cons_stdtuple(x),y.composite_key.key_extractors(),
    y.value,detail::generic_operator_equal_tuple());
}
#endif

/* < */

template<typename CompositeKey1,typename CompositeKey2>
inline bool operator<(
  const composite_key_result<CompositeKey1>& x,
  const composite_key_result<CompositeKey2>& y)
{
  typedef typename CompositeKey1::key_extractor_tuple key_extractor_tuple1;
  typedef typename CompositeKey1::value_type          value_type1;
  typedef typename CompositeKey2::key_extractor_tuple key_extractor_tuple2;
  typedef typename CompositeKey2::value_type          value_type2;

  return detail::compare_ckey_ckey<
   key_extractor_tuple1,value_type1,
   key_extractor_tuple2,value_type2,
   detail::generic_operator_less_tuple
  >::compare(
    x.composite_key.key_extractors(),x.value,
    y.composite_key.key_extractors(),y.value,
    detail::generic_operator_less_tuple());
}

template
<
  typename CompositeKey,
  BOOST_MULTI_INDEX_CK_ENUM_PARAMS(typename Value)
>
inline bool operator<(
  const composite_key_result<CompositeKey>& x,
  const tuple<BOOST_MULTI_INDEX_CK_ENUM_PARAMS(Value)>& y)
{
  typedef typename CompositeKey::key_extractor_tuple     key_extractor_tuple;
  typedef typename CompositeKey::value_type              value_type;
  typedef tuple<BOOST_MULTI_INDEX_CK_ENUM_PARAMS(Value)> key_tuple;
  
  return detail::compare_ckey_cval<
    key_extractor_tuple,value_type,
    key_tuple,detail::generic_operator_less_tuple
  >::compare(
    x.composite_key.key_extractors(),x.value,
    y,detail::generic_operator_less_tuple());
}

template
<
  BOOST_MULTI_INDEX_CK_ENUM_PARAMS(typename Value),
  typename CompositeKey
>
inline bool operator<(
  const tuple<BOOST_MULTI_INDEX_CK_ENUM_PARAMS(Value)>& x,
  const composite_key_result<CompositeKey>& y)
{
  typedef typename CompositeKey::key_extractor_tuple     key_extractor_tuple;
  typedef typename CompositeKey::value_type              value_type;
  typedef tuple<BOOST_MULTI_INDEX_CK_ENUM_PARAMS(Value)> key_tuple;
  
  return detail::compare_ckey_cval<
    key_extractor_tuple,value_type,
    key_tuple,detail::generic_operator_less_tuple
  >::compare(
    x,y.composite_key.key_extractors(),
    y.value,detail::generic_operator_less_tuple());
}

#if !defined(BOOST_NO_CXX11_HDR_TUPLE)&&\
    !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
template<typename CompositeKey,typename... Values>
inline bool operator<(
  const composite_key_result<CompositeKey>& x,
  const std::tuple<Values...>& y)
{
  typedef typename CompositeKey::key_extractor_tuple key_extractor_tuple;
  typedef typename CompositeKey::value_type          value_type;
  typedef std::tuple<Values...>                      key_tuple;
  typedef typename detail::cons_stdtuple_ctor<
    key_tuple>::result_type                          cons_key_tuple;
  
  return detail::compare_ckey_cval<
    key_extractor_tuple,value_type,
    cons_key_tuple,detail::generic_operator_less_tuple
  >::compare(
    x.composite_key.key_extractors(),x.value,
    detail::make_cons_stdtuple(y),detail::generic_operator_less_tuple());
}

template<typename CompositeKey,typename... Values>
inline bool operator<(
  const std::tuple<Values...>& x,
  const composite_key_result<CompositeKey>& y)
{
  typedef typename CompositeKey::key_extractor_tuple key_extractor_tuple;
  typedef typename CompositeKey::value_type          value_type;
  typedef std::tuple<Values...>                      key_tuple;
  typedef typename detail::cons_stdtuple_ctor<
    key_tuple>::result_type                          cons_key_tuple;
  
  return detail::compare_ckey_cval<
    key_extractor_tuple,value_type,
    cons_key_tuple,detail::generic_operator_less_tuple
  >::compare(
    detail::make_cons_stdtuple(x),y.composite_key.key_extractors(),
    y.value,detail::generic_operator_less_tuple());
}
#endif

/* rest of comparison operators */

#define BOOST_MULTI_INDEX_CK_COMPLETE_COMP_OPS(t1,t2,a1,a2)                  \
template<t1,t2> inline bool operator!=(const a1& x,const a2& y)              \
{                                                                            \
  return !(x==y);                                                            \
}                                                                            \
                                                                             \
template<t1,t2> inline bool operator>(const a1& x,const a2& y)               \
{                                                                            \
  return y<x;                                                                \
}                                                                            \
                                                                             \
template<t1,t2> inline bool operator>=(const a1& x,const a2& y)              \
{                                                                            \
  return !(x<y);                                                             \
}                                                                            \
                                                                             \
template<t1,t2> inline bool operator<=(const a1& x,const a2& y)              \
{                                                                            \
  return !(y<x);                                                             \
}

BOOST_MULTI_INDEX_CK_COMPLETE_COMP_OPS(
  typename CompositeKey1,
  typename CompositeKey2,
  composite_key_result<CompositeKey1>,
  composite_key_result<CompositeKey2>
)

BOOST_MULTI_INDEX_CK_COMPLETE_COMP_OPS(
  typename CompositeKey,
  BOOST_MULTI_INDEX_CK_ENUM_PARAMS(typename Value),
  composite_key_result<CompositeKey>,
  tuple<BOOST_MULTI_INDEX_CK_ENUM_PARAMS(Value)>
)

BOOST_MULTI_INDEX_CK_COMPLETE_COMP_OPS(
  BOOST_MULTI_INDEX_CK_ENUM_PARAMS(typename Value),
  typename CompositeKey,
  tuple<BOOST_MULTI_INDEX_CK_ENUM_PARAMS(Value)>,
  composite_key_result<CompositeKey>
)

#if !defined(BOOST_NO_CXX11_HDR_TUPLE)&&\
    !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
BOOST_MULTI_INDEX_CK_COMPLETE_COMP_OPS(
  typename CompositeKey,
  typename... Values,
  composite_key_result<CompositeKey>,
  std::tuple<Values...>
)

BOOST_MULTI_INDEX_CK_COMPLETE_COMP_OPS(
  typename CompositeKey,
  typename... Values,
  std::tuple<Values...>,
  composite_key_result<CompositeKey>
)
#endif

/* composite_key_equal_to */

template
<
  BOOST_MULTI_INDEX_CK_ENUM(BOOST_MULTI_INDEX_CK_TEMPLATE_PARM,Pred)
>
struct composite_key_equal_to:
  private tuple<BOOST_MULTI_INDEX_CK_ENUM_PARAMS(Pred)>
{
private:
  typedef tuple<BOOST_MULTI_INDEX_CK_ENUM_PARAMS(Pred)> super;

public:
  typedef super key_eq_tuple;

  composite_key_equal_to(
    BOOST_MULTI_INDEX_CK_ENUM(BOOST_MULTI_INDEX_CK_CTOR_ARG,Pred)):
    super(BOOST_MULTI_INDEX_CK_ENUM_PARAMS(k))
  {}

  composite_key_equal_to(const key_eq_tuple& x):super(x){}

  const key_eq_tuple& key_eqs()const{return *this;}
  key_eq_tuple&       key_eqs(){return *this;}

  template<typename CompositeKey1,typename CompositeKey2>
  bool operator()(
    const composite_key_result<CompositeKey1> & x,
    const composite_key_result<CompositeKey2> & y)const
  {
    typedef typename CompositeKey1::key_extractor_tuple key_extractor_tuple1;
    typedef typename CompositeKey1::value_type          value_type1;
    typedef typename CompositeKey2::key_extractor_tuple key_extractor_tuple2;
    typedef typename CompositeKey2::value_type          value_type2;

    BOOST_STATIC_ASSERT(
      tuples::length<key_extractor_tuple1>::value<=
      tuples::length<key_eq_tuple>::value&&
      tuples::length<key_extractor_tuple1>::value==
      tuples::length<key_extractor_tuple2>::value);

    return detail::equal_ckey_ckey<
      key_extractor_tuple1,value_type1,
      key_extractor_tuple2,value_type2,
      key_eq_tuple
    >::compare(
      x.composite_key.key_extractors(),x.value,
      y.composite_key.key_extractors(),y.value,
      key_eqs());
  }
  
  template
  <
    typename CompositeKey,
    BOOST_MULTI_INDEX_CK_ENUM_PARAMS(typename Value)
  >
  bool operator()(
    const composite_key_result<CompositeKey>& x,
    const tuple<BOOST_MULTI_INDEX_CK_ENUM_PARAMS(Value)>& y)const
  {
    typedef typename CompositeKey::key_extractor_tuple     key_extractor_tuple;
    typedef typename CompositeKey::value_type              value_type;
    typedef tuple<BOOST_MULTI_INDEX_CK_ENUM_PARAMS(Value)> key_tuple;

    BOOST_STATIC_ASSERT(
      tuples::length<key_extractor_tuple>::value<=
      tuples::length<key_eq_tuple>::value&&
      tuples::length<key_extractor_tuple>::value==
      tuples::length<key_tuple>::value);

    return detail::equal_ckey_cval<
      key_extractor_tuple,value_type,
      key_tuple,key_eq_tuple
    >::compare(x.composite_key.key_extractors(),x.value,y,key_eqs());
  }

  template
  <
    BOOST_MULTI_INDEX_CK_ENUM_PARAMS(typename Value),
    typename CompositeKey
  >
  bool operator()(
    const tuple<BOOST_MULTI_INDEX_CK_ENUM_PARAMS(Value)>& x,
    const composite_key_result<CompositeKey>& y)const
  {
    typedef typename CompositeKey::key_extractor_tuple     key_extractor_tuple;
    typedef typename CompositeKey::value_type              value_type;
    typedef tuple<BOOST_MULTI_INDEX_CK_ENUM_PARAMS(Value)> key_tuple;

    BOOST_STATIC_ASSERT(
      tuples::length<key_tuple>::value<=
      tuples::length<key_eq_tuple>::value&&
      tuples::length<key_tuple>::value==
      tuples::length<key_extractor_tuple>::value);

    return detail::equal_ckey_cval<
      key_extractor_tuple,value_type,
      key_tuple,key_eq_tuple
    >::compare(x,y.composite_key.key_extractors(),y.value,key_eqs());
  }

#if !defined(BOOST_NO_CXX11_HDR_TUPLE)&&\
    !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
  template<typename CompositeKey,typename... Values>
  bool operator()(
    const composite_key_result<CompositeKey>& x,
    const std::tuple<Values...>& y)const
  {
    typedef typename CompositeKey::key_extractor_tuple key_extractor_tuple;
    typedef typename CompositeKey::value_type          value_type;
    typedef std::tuple<Values...>                      key_tuple;
    typedef typename detail::cons_stdtuple_ctor<
      key_tuple>::result_type                          cons_key_tuple;

    BOOST_STATIC_ASSERT(
      tuples::length<key_extractor_tuple>::value<=
      tuples::length<key_eq_tuple>::value&&
      static_cast<std::size_t>(tuples::length<key_extractor_tuple>::value)==
      std::tuple_size<key_tuple>::value);

    return detail::equal_ckey_cval<
      key_extractor_tuple,value_type,
      cons_key_tuple,key_eq_tuple
    >::compare(
      x.composite_key.key_extractors(),x.value,
      detail::make_cons_stdtuple(y),key_eqs());
  }

  template<typename CompositeKey,typename... Values>
  bool operator()(
    const std::tuple<Values...>& x,
    const composite_key_result<CompositeKey>& y)const
  {
    typedef typename CompositeKey::key_extractor_tuple key_extractor_tuple;
    typedef typename CompositeKey::value_type          value_type;
    typedef std::tuple<Values...>                      key_tuple;
    typedef typename detail::cons_stdtuple_ctor<
      key_tuple>::result_type                          cons_key_tuple;

    BOOST_STATIC_ASSERT(
      std::tuple_size<key_tuple>::value<=
      static_cast<std::size_t>(tuples::length<key_eq_tuple>::value)&&
      std::tuple_size<key_tuple>::value==
      static_cast<std::size_t>(tuples::length<key_extractor_tuple>::value));

    return detail::equal_ckey_cval<
      key_extractor_tuple,value_type,
      cons_key_tuple,key_eq_tuple
    >::compare(
      detail::make_cons_stdtuple(x),y.composite_key.key_extractors(),
      y.value,key_eqs());
  }
#endif
};

/* composite_key_compare */

template
<
  BOOST_MULTI_INDEX_CK_ENUM(BOOST_MULTI_INDEX_CK_TEMPLATE_PARM,Compare)
>
struct composite_key_compare:
  private tuple<BOOST_MULTI_INDEX_CK_ENUM_PARAMS(Compare)>
{
private:
  typedef tuple<BOOST_MULTI_INDEX_CK_ENUM_PARAMS(Compare)> super;

public:
  typedef super key_comp_tuple;

  composite_key_compare(
    BOOST_MULTI_INDEX_CK_ENUM(BOOST_MULTI_INDEX_CK_CTOR_ARG,Compare)):
    super(BOOST_MULTI_INDEX_CK_ENUM_PARAMS(k))
  {}

  composite_key_compare(const key_comp_tuple& x):super(x){}

  const key_comp_tuple& key_comps()const{return *this;}
  key_comp_tuple&       key_comps(){return *this;}

  template<typename CompositeKey1,typename CompositeKey2>
  bool operator()(
    const composite_key_result<CompositeKey1> & x,
    const composite_key_result<CompositeKey2> & y)const
  {
    typedef typename CompositeKey1::key_extractor_tuple key_extractor_tuple1;
    typedef typename CompositeKey1::value_type          value_type1;
    typedef typename CompositeKey2::key_extractor_tuple key_extractor_tuple2;
    typedef typename CompositeKey2::value_type          value_type2;

    BOOST_STATIC_ASSERT(
      tuples::length<key_extractor_tuple1>::value<=
      tuples::length<key_comp_tuple>::value||
      tuples::length<key_extractor_tuple2>::value<=
      tuples::length<key_comp_tuple>::value);

    return detail::compare_ckey_ckey<
      key_extractor_tuple1,value_type1,
      key_extractor_tuple2,value_type2,
      key_comp_tuple
    >::compare(
      x.composite_key.key_extractors(),x.value,
      y.composite_key.key_extractors(),y.value,
      key_comps());
  }
  
#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
  template<typename CompositeKey,typename Value>
  bool operator()(
    const composite_key_result<CompositeKey>& x,
    const Value& y)const
  {
    return operator()(x,boost::make_tuple(boost::cref(y)));
  }
#endif

  template
  <
    typename CompositeKey,
    BOOST_MULTI_INDEX_CK_ENUM_PARAMS(typename Value)
  >
  bool operator()(
    const composite_key_result<CompositeKey>& x,
    const tuple<BOOST_MULTI_INDEX_CK_ENUM_PARAMS(Value)>& y)const
  {
    typedef typename CompositeKey::key_extractor_tuple     key_extractor_tuple;
    typedef typename CompositeKey::value_type              value_type;
    typedef tuple<BOOST_MULTI_INDEX_CK_ENUM_PARAMS(Value)> key_tuple;

    BOOST_STATIC_ASSERT(
      tuples::length<key_extractor_tuple>::value<=
      tuples::length<key_comp_tuple>::value||
      tuples::length<key_tuple>::value<=
      tuples::length<key_comp_tuple>::value);

    return detail::compare_ckey_cval<
      key_extractor_tuple,value_type,
      key_tuple,key_comp_tuple
    >::compare(x.composite_key.key_extractors(),x.value,y,key_comps());
  }

#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
  template<typename Value,typename CompositeKey>
  bool operator()(
    const Value& x,
    const composite_key_result<CompositeKey>& y)const
  {
    return operator()(boost::make_tuple(boost::cref(x)),y);
  }
#endif

  template
  <
    BOOST_MULTI_INDEX_CK_ENUM_PARAMS(typename Value),
    typename CompositeKey
  >
  bool operator()(
    const tuple<BOOST_MULTI_INDEX_CK_ENUM_PARAMS(Value)>& x,
    const composite_key_result<CompositeKey>& y)const
  {
    typedef typename CompositeKey::key_extractor_tuple     key_extractor_tuple;
    typedef typename CompositeKey::value_type              value_type;
    typedef tuple<BOOST_MULTI_INDEX_CK_ENUM_PARAMS(Value)> key_tuple;

    BOOST_STATIC_ASSERT(
      tuples::length<key_tuple>::value<=
      tuples::length<key_comp_tuple>::value||
      tuples::length<key_extractor_tuple>::value<=
      tuples::length<key_comp_tuple>::value);

    return detail::compare_ckey_cval<
      key_extractor_tuple,value_type,
      key_tuple,key_comp_tuple
    >::compare(x,y.composite_key.key_extractors(),y.value,key_comps());
  }

#if !defined(BOOST_NO_CXX11_HDR_TUPLE)&&\
    !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
  template<typename CompositeKey,typename... Values>
  bool operator()(
    const composite_key_result<CompositeKey>& x,
    const std::tuple<Values...>& y)const
  {
    typedef typename CompositeKey::key_extractor_tuple key_extractor_tuple;
    typedef typename CompositeKey::value_type          value_type;
    typedef std::tuple<Values...>                      key_tuple;
    typedef typename detail::cons_stdtuple_ctor<
      key_tuple>::result_type                          cons_key_tuple;

    BOOST_STATIC_ASSERT(
      tuples::length<key_extractor_tuple>::value<=
      tuples::length<key_comp_tuple>::value||
      std::tuple_size<key_tuple>::value<=
      static_cast<std::size_t>(tuples::length<key_comp_tuple>::value));

    return detail::compare_ckey_cval<
      key_extractor_tuple,value_type,
      cons_key_tuple,key_comp_tuple
    >::compare(
      x.composite_key.key_extractors(),x.value,
      detail::make_cons_stdtuple(y),key_comps());
  }

  template<typename CompositeKey,typename... Values>
  bool operator()(
    const std::tuple<Values...>& x,
    const composite_key_result<CompositeKey>& y)const
  {
    typedef typename CompositeKey::key_extractor_tuple key_extractor_tuple;
    typedef typename CompositeKey::value_type          value_type;
    typedef std::tuple<Values...>                      key_tuple;
    typedef typename detail::cons_stdtuple_ctor<
      key_tuple>::result_type                          cons_key_tuple;

    BOOST_STATIC_ASSERT(
      std::tuple_size<key_tuple>::value<=
      static_cast<std::size_t>(tuples::length<key_comp_tuple>::value)||
      tuples::length<key_extractor_tuple>::value<=
      tuples::length<key_comp_tuple>::value);

    return detail::compare_ckey_cval<
      key_extractor_tuple,value_type,
      cons_key_tuple,key_comp_tuple
    >::compare(
      detail::make_cons_stdtuple(x),y.composite_key.key_extractors(),
      y.value,key_comps());
  }
#endif
};

/* composite_key_hash */

template
<
  BOOST_MULTI_INDEX_CK_ENUM(BOOST_MULTI_INDEX_CK_TEMPLATE_PARM,Hash)
>
struct composite_key_hash:
  private tuple<BOOST_MULTI_INDEX_CK_ENUM_PARAMS(Hash)>
{
private:
  typedef tuple<BOOST_MULTI_INDEX_CK_ENUM_PARAMS(Hash)> super;

public:
  typedef super key_hasher_tuple;

  composite_key_hash(
    BOOST_MULTI_INDEX_CK_ENUM(BOOST_MULTI_INDEX_CK_CTOR_ARG,Hash)):
    super(BOOST_MULTI_INDEX_CK_ENUM_PARAMS(k))
  {}

  composite_key_hash(const key_hasher_tuple& x):super(x){}

  const key_hasher_tuple& key_hash_functions()const{return *this;}
  key_hasher_tuple&       key_hash_functions(){return *this;}

  template<typename CompositeKey>
  std::size_t operator()(const composite_key_result<CompositeKey> & x)const
  {
    typedef typename CompositeKey::key_extractor_tuple key_extractor_tuple;
    typedef typename CompositeKey::value_type          value_type;

    BOOST_STATIC_ASSERT(
      tuples::length<key_extractor_tuple>::value==
      tuples::length<key_hasher_tuple>::value);

    return detail::hash_ckey<
      key_extractor_tuple,value_type,
      key_hasher_tuple
    >::hash(x.composite_key.key_extractors(),x.value,key_hash_functions());
  }
  
  template<BOOST_MULTI_INDEX_CK_ENUM_PARAMS(typename Value)>
  std::size_t operator()(
    const tuple<BOOST_MULTI_INDEX_CK_ENUM_PARAMS(Value)>& x)const
  {
    typedef tuple<BOOST_MULTI_INDEX_CK_ENUM_PARAMS(Value)> key_tuple;

    BOOST_STATIC_ASSERT(
      tuples::length<key_tuple>::value==
      tuples::length<key_hasher_tuple>::value);

    return detail::hash_cval<
      key_tuple,key_hasher_tuple
    >::hash(x,key_hash_functions());
  }

#if !defined(BOOST_NO_CXX11_HDR_TUPLE)&&\
    !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
  template<typename... Values>
  std::size_t operator()(const std::tuple<Values...>& x)const
  {
    typedef std::tuple<Values...>                key_tuple;
    typedef typename detail::cons_stdtuple_ctor<
      key_tuple>::result_type                    cons_key_tuple;

    BOOST_STATIC_ASSERT(
      std::tuple_size<key_tuple>::value==
      static_cast<std::size_t>(tuples::length<key_hasher_tuple>::value));

    return detail::hash_cval<
      cons_key_tuple,key_hasher_tuple
    >::hash(detail::make_cons_stdtuple(x),key_hash_functions());
  }
#endif
};

/* Instantiations of the former functors with "natural" basic components:
 * composite_key_result_equal_to uses std::equal_to of the values.
 * composite_key_result_less     uses std::less.
 * composite_key_result_greater  uses std::greater.
 * composite_key_result_hash     uses boost::hash.
 */

#define BOOST_MULTI_INDEX_CK_RESULT_EQUAL_TO_SUPER                           \
composite_key_equal_to<                                                      \
    BOOST_MULTI_INDEX_CK_ENUM(                                               \
      BOOST_MULTI_INDEX_CK_APPLY_METAFUNCTION_N,                             \
      /* the argument is a PP list */                                        \
      (detail::nth_composite_key_equal_to,                                   \
        (BOOST_DEDUCED_TYPENAME CompositeKeyResult::composite_key_type,      \
          BOOST_PP_NIL)))                                                    \
  >

template<typename CompositeKeyResult>
struct composite_key_result_equal_to:
BOOST_MULTI_INDEX_PRIVATE_IF_USING_DECL_FOR_TEMPL_FUNCTIONS
BOOST_MULTI_INDEX_CK_RESULT_EQUAL_TO_SUPER
{
private:
  typedef BOOST_MULTI_INDEX_CK_RESULT_EQUAL_TO_SUPER super;

public:
  typedef CompositeKeyResult  first_argument_type;
  typedef first_argument_type second_argument_type;
  typedef bool                result_type;

  using super::operator();
};

#define BOOST_MULTI_INDEX_CK_RESULT_LESS_SUPER                               \
composite_key_compare<                                                       \
    BOOST_MULTI_INDEX_CK_ENUM(                                               \
      BOOST_MULTI_INDEX_CK_APPLY_METAFUNCTION_N,                             \
      /* the argument is a PP list */                                        \
      (detail::nth_composite_key_less,                                       \
        (BOOST_DEDUCED_TYPENAME CompositeKeyResult::composite_key_type,      \
          BOOST_PP_NIL)))                                                    \
  >

template<typename CompositeKeyResult>
struct composite_key_result_less:
BOOST_MULTI_INDEX_PRIVATE_IF_USING_DECL_FOR_TEMPL_FUNCTIONS
BOOST_MULTI_INDEX_CK_RESULT_LESS_SUPER
{
private:
  typedef BOOST_MULTI_INDEX_CK_RESULT_LESS_SUPER super;

public:
  typedef CompositeKeyResult  first_argument_type;
  typedef first_argument_type second_argument_type;
  typedef bool                result_type;

  using super::operator();
};

#define BOOST_MULTI_INDEX_CK_RESULT_GREATER_SUPER                            \
composite_key_compare<                                                       \
    BOOST_MULTI_INDEX_CK_ENUM(                                               \
      BOOST_MULTI_INDEX_CK_APPLY_METAFUNCTION_N,                             \
      /* the argument is a PP list */                                        \
      (detail::nth_composite_key_greater,                                    \
        (BOOST_DEDUCED_TYPENAME CompositeKeyResult::composite_key_type,      \
          BOOST_PP_NIL)))                                                    \
  >

template<typename CompositeKeyResult>
struct composite_key_result_greater:
BOOST_MULTI_INDEX_PRIVATE_IF_USING_DECL_FOR_TEMPL_FUNCTIONS
BOOST_MULTI_INDEX_CK_RESULT_GREATER_SUPER
{
private:
  typedef BOOST_MULTI_INDEX_CK_RESULT_GREATER_SUPER super;

public:
  typedef CompositeKeyResult  first_argument_type;
  typedef first_argument_type second_argument_type;
  typedef bool                result_type;

  using super::operator();
};

#define BOOST_MULTI_INDEX_CK_RESULT_HASH_SUPER                               \
composite_key_hash<                                                          \
    BOOST_MULTI_INDEX_CK_ENUM(                                               \
      BOOST_MULTI_INDEX_CK_APPLY_METAFUNCTION_N,                             \
      /* the argument is a PP list */                                        \
      (detail::nth_composite_key_hash,                                       \
        (BOOST_DEDUCED_TYPENAME CompositeKeyResult::composite_key_type,      \
          BOOST_PP_NIL)))                                                    \
  >

template<typename CompositeKeyResult>
struct composite_key_result_hash:
BOOST_MULTI_INDEX_PRIVATE_IF_USING_DECL_FOR_TEMPL_FUNCTIONS
BOOST_MULTI_INDEX_CK_RESULT_HASH_SUPER
{
private:
  typedef BOOST_MULTI_INDEX_CK_RESULT_HASH_SUPER super;

public:
  typedef CompositeKeyResult argument_type;
  typedef std::size_t        result_type;

  using super::operator();
};

} /* namespace multi_index */

} /* namespace boost */

/* Specializations of std::equal_to, std::less, std::greater and boost::hash
 * for composite_key_results enabling interoperation with tuples of values.
 */

namespace std{

template<typename CompositeKey>
struct equal_to<boost::multi_index::composite_key_result<CompositeKey> >:
  boost::multi_index::composite_key_result_equal_to<
    boost::multi_index::composite_key_result<CompositeKey>
  >
{
};

template<typename CompositeKey>
struct less<boost::multi_index::composite_key_result<CompositeKey> >:
  boost::multi_index::composite_key_result_less<
    boost::multi_index::composite_key_result<CompositeKey>
  >
{
};

template<typename CompositeKey>
struct greater<boost::multi_index::composite_key_result<CompositeKey> >:
  boost::multi_index::composite_key_result_greater<
    boost::multi_index::composite_key_result<CompositeKey>
  >
{
};

} /* namespace std */

namespace boost{

template<typename CompositeKey>
struct hash<boost::multi_index::composite_key_result<CompositeKey> >:
  boost::multi_index::composite_key_result_hash<
    boost::multi_index::composite_key_result<CompositeKey>
  >
{
};

} /* namespace boost */

#undef BOOST_MULTI_INDEX_CK_RESULT_HASH_SUPER
#undef BOOST_MULTI_INDEX_CK_RESULT_GREATER_SUPER
#undef BOOST_MULTI_INDEX_CK_RESULT_LESS_SUPER
#undef BOOST_MULTI_INDEX_CK_RESULT_EQUAL_TO_SUPER
#undef BOOST_MULTI_INDEX_CK_COMPLETE_COMP_OPS
#undef BOOST_MULTI_INDEX_CK_IDENTITY_ENUM_MACRO
#undef BOOST_MULTI_INDEX_CK_NTH_COMPOSITE_KEY_FUNCTOR
#undef BOOST_MULTI_INDEX_CK_APPLY_METAFUNCTION_N
#undef BOOST_MULTI_INDEX_CK_CTOR_ARG
#undef BOOST_MULTI_INDEX_CK_TEMPLATE_PARM
#undef BOOST_MULTI_INDEX_CK_ENUM_PARAMS
#undef BOOST_MULTI_INDEX_CK_ENUM
#undef BOOST_MULTI_INDEX_COMPOSITE_KEY_SIZE

#endif

/* composite_key.hpp
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
*/