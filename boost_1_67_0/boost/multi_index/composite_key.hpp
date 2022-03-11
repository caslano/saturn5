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