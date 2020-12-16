// - casts.hpp -- BLambda Library -------------
//
// Copyright (C) 2000 Gary Powell (powellg@amazon.com)
// Copyright (C) 1999, 2000 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org

// -----------------------------------------------

#if !defined(BOOST_LAMBDA_CASTS_HPP)
#define BOOST_LAMBDA_CASTS_HPP

#include "boost/lambda/detail/suppress_unused.hpp"
#include "boost/lambda/core.hpp"

#include <typeinfo>

namespace boost { 
namespace lambda {

template<class Act, class Args>
struct return_type_N;

template<class T> class cast_action;

template<class T> class static_cast_action;
template<class T> class dynamic_cast_action;
template<class T> class const_cast_action;
template<class T> class reinterpret_cast_action;

class typeid_action;
class sizeof_action;

// Cast actions

template<class T> class cast_action<static_cast_action<T> > 
{
public:
  template<class RET, class Arg1>
  static RET apply(Arg1 &a1) {
    return static_cast<RET>(a1);
  }
};

template<class T> class cast_action<dynamic_cast_action<T> > {
public:
  template<class RET, class Arg1>
  static RET apply(Arg1 &a1) {
    return dynamic_cast<RET>(a1);
  }
};

template<class T> class cast_action<const_cast_action<T> > {
public:
  template<class RET, class Arg1>
  static RET apply(Arg1 &a1) {
    return const_cast<RET>(a1);
  }
};

template<class T> class cast_action<reinterpret_cast_action<T> > {
public:
  template<class RET, class Arg1>
  static RET apply(Arg1 &a1) {
    return reinterpret_cast<RET>(a1);
  }
};

// typeid action
class typeid_action {
public:
  template<class RET, class Arg1>
  static RET apply(Arg1 &a1) {
    detail::suppress_unused_variable_warnings(a1);
    return typeid(a1);
  }
};

// sizeof action
class sizeof_action
{
public:
  template<class RET, class Arg1>
  static RET apply(Arg1 &a1) {
    return sizeof(a1);
  }
};


// return types of casting lambda_functors (all "T" type.)

template<template <class> class cast_type, class T, class A>
struct return_type_N<cast_action< cast_type<T> >, A> { 
  typedef T type;
};

// return type of typeid_action
template<class A>
struct return_type_N<typeid_action, A> { 
  typedef std::type_info const & type;
};

// return type of sizeof_action

template<class A>
struct return_type_N<sizeof_action, A> { 
  typedef std::size_t type;
};


// the four cast & typeid overloads.
// casts can take ordinary variables (not just lambda functors)

// static_cast 
template <class T, class Arg1>
inline const lambda_functor<
  lambda_functor_base<
    action<1, cast_action<static_cast_action<T> > >, 
    tuple<typename const_copy_argument <const Arg1>::type>
  > 
>
ll_static_cast(const Arg1& a1) { 
  return 
    lambda_functor_base<
      action<1, cast_action<static_cast_action<T> > >, 
      tuple<typename const_copy_argument <const Arg1>::type> 
    >
  ( tuple<typename const_copy_argument <const Arg1>::type>(a1));
}

// dynamic_cast
template <class T, class Arg1>
inline const lambda_functor<
  lambda_functor_base<
    action<1, cast_action<dynamic_cast_action<T> > >, 
    tuple<typename const_copy_argument <const Arg1>::type>
  > 
>
ll_dynamic_cast(const Arg1& a1) { 
  return 
    lambda_functor_base<
      action<1, cast_action<dynamic_cast_action<T> > >, 
      tuple<typename const_copy_argument <const Arg1>::type>
    > 
  ( tuple<typename const_copy_argument <const Arg1>::type>(a1));
}

// const_cast
template <class T, class Arg1>
inline const lambda_functor<
  lambda_functor_base<
    action<1, cast_action<const_cast_action<T> > >, 
    tuple<typename const_copy_argument <const Arg1>::type>
  > 
>
ll_const_cast(const Arg1& a1) { 
  return 
      lambda_functor_base<
        action<1, cast_action<const_cast_action<T> > >, 
        tuple<typename const_copy_argument <const Arg1>::type>
      > 
      ( tuple<typename const_copy_argument <const Arg1>::type>(a1));
}

// reinterpret_cast
template <class T, class Arg1>
inline const lambda_functor<
  lambda_functor_base<
    action<1, cast_action<reinterpret_cast_action<T> > >, 
    tuple<typename const_copy_argument <const Arg1>::type>
  > 
>
ll_reinterpret_cast(const Arg1& a1) { 
  return 
      lambda_functor_base<
        action<1, cast_action<reinterpret_cast_action<T> > >, 
        tuple<typename const_copy_argument <const Arg1>::type> 
      > 
      ( tuple<typename const_copy_argument <const Arg1>::type>(a1));
}

// typeid
// can be applied to a normal variable as well (can refer to a polymorphic
// class object)
template <class Arg1>
inline const lambda_functor<
  lambda_functor_base<
    action<1, typeid_action>, 
    tuple<typename const_copy_argument <const Arg1>::type>
  > 
>
ll_typeid(const Arg1& a1) { 
  return 
      lambda_functor_base<
        action<1, typeid_action>, 
        tuple<typename const_copy_argument <const Arg1>::type>
      > 
      ( tuple<typename const_copy_argument <const Arg1>::type>(a1));
}

// sizeof(expression)
// Always takes a lambda expression (if not, built in sizeof will do)
template <class Arg1>
inline const lambda_functor<
  lambda_functor_base<
    action<1, sizeof_action>, 
    tuple<lambda_functor<Arg1> >
  > 
>
ll_sizeof(const lambda_functor<Arg1>& a1) { 
  return 
      lambda_functor_base<
        action<1, sizeof_action>, 
        tuple<lambda_functor<Arg1> >
      > 
      ( tuple<lambda_functor<Arg1> >(a1));
}

} // namespace lambda 
} // namespace boost

#endif

/* casts.hpp
pLS/7GEMzuzbObd/cSnfhvXod57iMmxvA2eJ33TNvgXj4f5NnJwlFKj1fh1xy9PtYahwunfgw8StI2mc9QrtFL9u8TtZ7THUE7dU0h6/YUqP1JcpRq3Px6t0M/PbuU+Ab8JvBV7nZw+yTLswks6wSdak0Vaml1J/mq1cVJ4X8Ps05Yk4AtvX0uVvJT/wTpb1athk+Ntqy9+IchcUKXrlT52L7xR/1xvt9XtVjMf01X0u4RNF0EPeFzCaw7em7hFee1dEtZuGEj6StGmcI3S8/s2H6u1I7Wf/TdxGI54B6oy5jcSVwbrwxO2whZ+s/L7dv8otkfl6Segl2OfPRquOr5a/KLQ5B9ucrt3F1FyH1d71N2rxRvUaTi83o7E3Bd4HTLTaouRprsVacieUuWZWa4v8xnXiL0nfFgdo61nV0/Pinq/TU8+w+jpOAj4o7vWq16kmLFaY7uLSDJXnO7Msd5d8T0QHWXFJPG6+KcHfrH4sv5fwd8ZlRaXayAqJqwtePo9V/OfvA8h/UE15CLtL6BKzHvkjVs7K7/0S/lqVt6dYnp53AJ4QOsSIIy+rimusGYGXQiWM+u1ln+/tpN7AXippXC7fGyPfVqU/f47PdyGIOvupK2HWYizpo+L5XH5rJ9/lsn1XOtptKNz/hTb7FeyhFNv/bMfravkexMm2aYST+ouQcC7xU/IzrXiy9c0x8ttVp6QL398ebXSaid9vGri7+Zj4O17/29KDVxiR7Q763+PU70H629MNfO820D1FeaPYM75y3M9ivyphpZVxP68SGMb9m3rcv2kAnM79ld8Am1C3SjfgTL6xOhs4jHrocoFXAwuB16h9Ho5jHCOzfPZ5GnOfpAnTbcr9ymbAxsDm3Ddrwf2Tlox3lYffc2zLYltcakXGfZ0Q7t8kc/8mg/twF3Ifrif3layw53N/sif3JS8ClnKfbyb3+WZzn+9q7vMt4z7fCsa72ra/95SHd5EfZ/nso2bxzdoc7isNBQ6nfr21wBHAjdTb9wxwFPB54Gi+IXAl9z/HAj8BjgMeAo4HmkgvHxgHLAC2ABYC2wInAvub3G8CFgMLgZOB9wFLuI8n+0du6Gpzh9VaJ34G/Ga6w2p93y/P7f0+rBv0CtgHYbe5g3slQRM0QfPLMWdr/Z8Lvd6na/3/NQbvtlwLZnCtegNsG9ipsLtaYAzqp9aCRj01v3epNeDV4j4Ec64YzdqA4bnuosyDdq1Hf9q9hVhgsbhHa9cB9jTqyby3QPztxRww0bhS8vQNvvUw7BHYP1J3ewu7TEAt5qpVc1OX0DaZJM5Tq+0LSPr1OL+Nwl2IRUi3vdyFmGKTAwh8Thro+bf+PNv/3PaJRiZ+fzPsyoUR5uyMmFZzo9LfHFvf33n2mddzGKhex9Olv1EvHxD4XPt0zfGr5sxs7+yrK3zmzNHWnA6YwDlsKt+tagi8EpjEOXgycCrd1yMynBWe8Dzxl3JuiLnkSZ0d/lJ0IWJuG/D54d7gnDdogiZogiZogiZoguYXZc70+/+ubpa1Vv+nrgfAWvsfta392zsov+uz9l+XybV/N0O79n9V3If6W/sjfO3W/vTnd+3/dKb/tb89jRa2tf8629r/O3zr97DHbGv/vDO89rfSb+Gz9k+qWvuf0nlUWrqJ36848O2FHw16/LHXr098s2X9lksCX0vq1+aBv/GsX/sHvkauWtuyPtkWM3zWtvFc26ZwbXsu17aNuLZtDyzkuc5Uuhed5Nu9h9xhJzyjsK3h0CCC67P/snclgFFVV/T/mckCCZCEJIQkQAiLQAKEECBsISBLBMSwihpMQhIgEJKYDAiKGoQqIkVUtKJUqUVFqxa3Fi1VXGo=
*/