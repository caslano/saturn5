// Boost Lambda Library  lambda_functor_base.hpp -----------------------------
//
// Copyright (C) 1999, 2000 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org

// ------------------------------------------------------------

#ifndef BOOST_LAMBDA_LAMBDA_FUNCTOR_BASE_HPP
#define BOOST_LAMBDA_LAMBDA_FUNCTOR_BASE_HPP

#include "boost/type_traits/add_reference.hpp"
#include "boost/type_traits/add_const.hpp"
#include "boost/type_traits/remove_const.hpp"
#include "boost/lambda/detail/lambda_fwd.hpp"
#include "boost/lambda/detail/lambda_traits.hpp"

namespace boost { 
namespace lambda {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

  // for return type deductions we wrap bound argument to this class,
  // which fulfils the base class contract for lambda_functors
template <class T>
class identity {

  T elem;
public:
  
  typedef T element_t;

  // take all parameters as const references. Note that non-const references
  // stay as they are.
  typedef typename boost::add_reference<
    typename boost::add_const<T>::type
  >::type par_t;

  explicit identity(par_t t) : elem(t) {}

  template <typename SigArgs> 
  struct sig { typedef typename boost::remove_const<element_t>::type type; };

  template<class RET, CALL_TEMPLATE_ARGS>
  RET call(CALL_FORMAL_ARGS) const { CALL_USE_ARGS; return elem; }
};

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

template <class T> 
inline lambda_functor<identity<T&> > var(T& t) { return identity<T&>(t); }

  // for lambda functors, var is an identity operator. It was forbidden
  // at some point, but we might want to var something that can be a 
  // non-lambda functor or a lambda functor.
template <class T>
lambda_functor<T> var(const lambda_functor<T>& t) { return t; }

template <class T> struct var_type {
  typedef lambda_functor<identity<T&> > type;
};


template <class T> 
inline 
lambda_functor<identity<typename bound_argument_conversion<const T>::type> >
constant(const T& t) { 
  return identity<typename bound_argument_conversion<const T>::type>(t); 
}
template <class T>
lambda_functor<T> constant(const lambda_functor<T>& t) { return t; }

template <class T> struct constant_type {
  typedef 
   lambda_functor<
     identity<typename bound_argument_conversion<const T>::type> 
   > type;
};



template <class T> 
inline lambda_functor<identity<const T&> > constant_ref(const T& t) { 
  return identity<const T&>(t); 
}
template <class T>
lambda_functor<T> constant_ref(const lambda_functor<T>& t) { return t; }

template <class T> struct constant_ref_type {
  typedef 
   lambda_functor<identity<const T&> > type;
};



  // as_lambda_functor turns any types to lambda functors 
  // non-lambda_functors will be bound argument types
template <class T>
struct as_lambda_functor { 
  typedef typename 
    detail::remove_reference_and_cv<T>::type plain_T;
  typedef typename 
    detail::IF<is_lambda_functor<plain_T>::value, 
      plain_T,
      lambda_functor<
        identity<typename bound_argument_conversion<T>::type> 
      >
    >::RET type; 
};

// turns arbitrary objects into lambda functors
template <class T> 
inline 
lambda_functor<identity<typename bound_argument_conversion<const T>::type> > 
to_lambda_functor(const T& t) { 
  return identity<typename bound_argument_conversion<const T>::type>(t);
}

template <class T> 
inline lambda_functor<T> 
to_lambda_functor(const lambda_functor<T>& t) { 
  return t;
}

namespace detail {   



// In a call constify_rvals<T>::go(x)
// x should be of type T. If T is a non-reference type, do
// returns x as const reference. 
// Otherwise the type doesn't change.
// The purpose of this class is to avoid 
// 'cannot bind temporaries to non-const references' errors.
template <class T> struct constify_rvals {
  template<class U>
  static inline const U& go(const U& u) { return u; }
};

template <class T> struct constify_rvals<T&> {
  template<class U>
  static inline U& go(U& u) { return u; }
};

  // check whether one of the elements of a tuple (cons list) is of type
  // null_type. Needed, because the compiler goes ahead and instantiates
  // sig template for nullary case even if the nullary operator() is not
  // called
template <class T> struct is_null_type 
{ BOOST_STATIC_CONSTANT(bool, value = false); };

template <> struct is_null_type<null_type> 
{ BOOST_STATIC_CONSTANT(bool, value = true); };

template<class Tuple> struct has_null_type {
  BOOST_STATIC_CONSTANT(bool, value = (is_null_type<typename Tuple::head_type>::value || has_null_type<typename Tuple::tail_type>::value));
};
template<> struct has_null_type<null_type> {
  BOOST_STATIC_CONSTANT(bool, value = false);
};


// helpers -------------------


template<class Args, class SigArgs>
class deduce_argument_types_ {
  typedef typename as_lambda_functor<typename Args::head_type>::type lf_t;
  typedef typename lf_t::inherited::template sig<SigArgs>::type el_t;  
public:
  typedef
    boost::tuples::cons<
      el_t, 
      typename deduce_argument_types_<typename Args::tail_type, SigArgs>::type
    > type;
};

template<class SigArgs>
class deduce_argument_types_<null_type, SigArgs> {
public:
  typedef null_type type; 
};


//  // note that tuples cannot have plain function types as elements.
//  // Hence, all other types will be non-const, except references to 
//  // functions.
//  template <class T> struct remove_reference_except_from_functions {
//    typedef typename boost::remove_reference<T>::type t;
//    typedef typename detail::IF<boost::is_function<t>::value, T, t>::RET type;
//  };

template<class Args, class SigArgs>
class deduce_non_ref_argument_types_ {
  typedef typename as_lambda_functor<typename Args::head_type>::type lf_t;
  typedef typename lf_t::inherited::template sig<SigArgs>::type el_t;  
public:
  typedef
    boost::tuples::cons<
  //      typename detail::remove_reference_except_from_functions<el_t>::type, 
      typename boost::remove_reference<el_t>::type, 
      typename deduce_non_ref_argument_types_<typename Args::tail_type, SigArgs>::type
    > type;
};

template<class SigArgs>
class deduce_non_ref_argument_types_<null_type, SigArgs> {
public:
  typedef null_type type; 
};

  // -------------

// take stored Args and Open Args, and return a const list with 
// deduced elements (real return types)
template<class Args, class SigArgs>
class deduce_argument_types {
  typedef typename deduce_argument_types_<Args, SigArgs>::type t1;
public:
  typedef typename detail::IF<
    has_null_type<t1>::value, null_type, t1
  >::RET type; 
};

// take stored Args and Open Args, and return a const list with 
// deduced elements (references are stripped from the element types)

template<class Args, class SigArgs>
class deduce_non_ref_argument_types {
  typedef typename deduce_non_ref_argument_types_<Args, SigArgs>::type t1;
public:
  typedef typename detail::IF<
    has_null_type<t1>::value, null_type, t1
  >::RET type; 
};

template <int N, class Args, class SigArgs>
struct nth_return_type_sig {
  typedef typename 
          as_lambda_functor<
            typename boost::tuples::element<N, Args>::type 
  //            typename tuple_element_as_reference<N, Args>::type 
        >::type lf_type;

  typedef typename lf_type::inherited::template sig<SigArgs>::type type;  
};

template<int N, class Tuple> struct element_or_null {
  typedef typename boost::tuples::element<N, Tuple>::type type;
};

template<int N> struct element_or_null<N, null_type> {
  typedef null_type type;
};


   
   
} // end detail
   
 // -- lambda_functor base ---------------------

// the explicit_return_type_action case -----------------------------------
template<class RET, class Args>
class lambda_functor_base<explicit_return_type_action<RET>, Args> 
{
public:
  Args args;

  typedef RET result_type;

  explicit lambda_functor_base(const Args& a) : args(a) {}

  template <class SigArgs> struct sig { typedef RET type; };

  template<class RET_, CALL_TEMPLATE_ARGS>
  RET call(CALL_FORMAL_ARGS) const 
  {
    return detail::constify_rvals<RET>::go(
     detail::r_select<RET>::go(boost::tuples::get<0>(args), CALL_ACTUAL_ARGS));
  }
};

// the protect_action case -----------------------------------
template<class Args>
class lambda_functor_base<protect_action, Args>
{
public:
  Args args;
public:

  explicit lambda_functor_base(const Args& a) : args(a) {}


  template<class RET, CALL_TEMPLATE_ARGS>
  RET call(CALL_FORMAL_ARGS) const 
  {
     CALL_USE_ARGS;
     return boost::tuples::get<0>(args);
  }

  template<class SigArgs> struct sig { 
    //    typedef typename detail::tuple_element_as_reference<0, SigArgs>::type type;
    typedef typename boost::tuples::element<0, Args>::type type;
  };
};

// Do nothing --------------------------------------------------------
class do_nothing_action {};

template<class Args>
class lambda_functor_base<do_nothing_action, Args> {
  //  Args args;
public:
  //  explicit lambda_functor_base(const Args& a) {}
  lambda_functor_base() {}


  template<class RET, CALL_TEMPLATE_ARGS> RET call(CALL_FORMAL_ARGS) const {
    return CALL_USE_ARGS;
  }

  template<class SigArgs> struct sig { typedef void type; };
};  


//  These specializations provide a shorter notation to define actions.
//  These lambda_functor_base instances take care of the recursive evaluation
//  of the arguments and pass the evaluated arguments to the apply function
//  of an action class. To make action X work with these classes, one must
//  instantiate the lambda_functor_base as:
//  lambda_functor_base<action<ARITY, X>, Args>
//  Where ARITY is the arity of the apply function in X

//  The return type is queried as:
//  return_type_N<X, EvaluatedArgumentTypes>::type
//  for which there must be a specialization.

//  Function actions, casts, throws,... all go via these classes.


template<class Act, class Args>  
class lambda_functor_base<action<0, Act>, Args>           
{  
public:  
//  Args args; not needed
  explicit lambda_functor_base(const Args& /*a*/) {}  
  
  template<class SigArgs> struct sig {  
    typedef typename return_type_N<Act, null_type>::type type;
  };
  
  template<class RET, CALL_TEMPLATE_ARGS>  
  RET call(CALL_FORMAL_ARGS) const {  
    CALL_USE_ARGS;
    return Act::template apply<RET>();
  }
};


#if defined BOOST_LAMBDA_LAMBDA_FUNCTOR_BASE_FIRST_PART  
#error "Multiple defines of BOOST_LAMBDA_LAMBDA_FUNCTOR_BASE_FIRST_PART"  
#endif  
  
  
#define BOOST_LAMBDA_LAMBDA_FUNCTOR_BASE_FIRST_PART(ARITY)             \
template<class Act, class Args>                                        \
class lambda_functor_base<action<ARITY, Act>, Args>                    \
{                                                                      \
public:                                                                \
  Args args;                                                           \
                                                                       \
  explicit lambda_functor_base(const Args& a) : args(a) {}             \
                                                                       \
  template<class SigArgs> struct sig {                                 \
    typedef typename                                                   \
    detail::deduce_argument_types<Args, SigArgs>::type rets_t;         \
  public:                                                              \
    typedef typename                                                   \
      return_type_N_prot<Act, rets_t>::type type;                      \
  };                                                                   \
                                                                       \
                                                                       \
  template<class RET, CALL_TEMPLATE_ARGS>                              \
  RET call(CALL_FORMAL_ARGS) const {                                   \
    using boost::tuples::get;                                          \
    using detail::constify_rvals;                                      \
    using detail::r_select;                                            \
    using detail::element_or_null;                                     \
    using detail::deduce_argument_types;                                

BOOST_LAMBDA_LAMBDA_FUNCTOR_BASE_FIRST_PART(1)

  typedef typename
    deduce_argument_types<Args, tuple<CALL_REFERENCE_TYPES> >::type rets_t;
  typedef typename element_or_null<0, rets_t>::type rt0;

  return Act::template apply<RET>(
    constify_rvals<rt0>::go(r_select<rt0>::go(get<0>(args), CALL_ACTUAL_ARGS))
    );
  }
};


BOOST_LAMBDA_LAMBDA_FUNCTOR_BASE_FIRST_PART(2)
  
  typedef typename 
    deduce_argument_types<Args, tuple<CALL_REFERENCE_TYPES> >::type rets_t;
  typedef typename element_or_null<0, rets_t>::type rt0;
  typedef typename element_or_null<1, rets_t>::type rt1;

  return Act::template apply<RET>(
    constify_rvals<rt0>::go(r_select<rt0>::go(get<0>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt1>::go(r_select<rt1>::go(get<1>(args), CALL_ACTUAL_ARGS))
    );
  }
};

BOOST_LAMBDA_LAMBDA_FUNCTOR_BASE_FIRST_PART(3)

  typedef typename 
    deduce_argument_types<Args, tuple<CALL_REFERENCE_TYPES> >::type rets_t;

  typedef typename element_or_null<0, rets_t>::type rt0;
  typedef typename element_or_null<1, rets_t>::type rt1;
  typedef typename element_or_null<2, rets_t>::type rt2;

  return Act::template apply<RET>(
    constify_rvals<rt0>::go(r_select<rt0>::go(get<0>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt1>::go(r_select<rt1>::go(get<1>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt2>::go(r_select<rt2>::go(get<2>(args), CALL_ACTUAL_ARGS))
    );
  }
};

BOOST_LAMBDA_LAMBDA_FUNCTOR_BASE_FIRST_PART(4)
  typedef typename 
    deduce_argument_types<Args, tuple<CALL_REFERENCE_TYPES> >::type rets_t;
  typedef typename element_or_null<0, rets_t>::type rt0;
  typedef typename element_or_null<1, rets_t>::type rt1;
  typedef typename element_or_null<2, rets_t>::type rt2;
  typedef typename element_or_null<3, rets_t>::type rt3;

  return Act::template apply<RET>(
    constify_rvals<rt0>::go(r_select<rt0>::go(get<0>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt1>::go(r_select<rt1>::go(get<1>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt2>::go(r_select<rt2>::go(get<2>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt3>::go(r_select<rt3>::go(get<3>(args), CALL_ACTUAL_ARGS))
    );
  }
};

BOOST_LAMBDA_LAMBDA_FUNCTOR_BASE_FIRST_PART(5)
  typedef typename 
    deduce_argument_types<Args, tuple<CALL_REFERENCE_TYPES> >::type rets_t;
  typedef typename element_or_null<0, rets_t>::type rt0;
  typedef typename element_or_null<1, rets_t>::type rt1;
  typedef typename element_or_null<2, rets_t>::type rt2;
  typedef typename element_or_null<3, rets_t>::type rt3;
  typedef typename element_or_null<4, rets_t>::type rt4;

  return Act::template apply<RET>(
    constify_rvals<rt0>::go(r_select<rt0>::go(get<0>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt1>::go(r_select<rt1>::go(get<1>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt2>::go(r_select<rt2>::go(get<2>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt3>::go(r_select<rt3>::go(get<3>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt4>::go(r_select<rt4>::go(get<4>(args), CALL_ACTUAL_ARGS))
    );
  }
};

BOOST_LAMBDA_LAMBDA_FUNCTOR_BASE_FIRST_PART(6)

  typedef typename 
    deduce_argument_types<Args, tuple<CALL_REFERENCE_TYPES> >::type rets_t;
  typedef typename element_or_null<0, rets_t>::type rt0;
  typedef typename element_or_null<1, rets_t>::type rt1;
  typedef typename element_or_null<2, rets_t>::type rt2;
  typedef typename element_or_null<3, rets_t>::type rt3;
  typedef typename element_or_null<4, rets_t>::type rt4;
  typedef typename element_or_null<5, rets_t>::type rt5;


    return Act::template apply<RET>(
    constify_rvals<rt0>::go(r_select<rt0>::go(get<0>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt1>::go(r_select<rt1>::go(get<1>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt2>::go(r_select<rt2>::go(get<2>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt3>::go(r_select<rt3>::go(get<3>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt4>::go(r_select<rt4>::go(get<4>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt5>::go(r_select<rt5>::go(get<5>(args), CALL_ACTUAL_ARGS)) 
    );
  }
};

BOOST_LAMBDA_LAMBDA_FUNCTOR_BASE_FIRST_PART(7)
  typedef typename 
    deduce_argument_types<Args, tuple<CALL_REFERENCE_TYPES> >::type rets_t;
  typedef typename element_or_null<0, rets_t>::type rt0;
  typedef typename element_or_null<1, rets_t>::type rt1;
  typedef typename element_or_null<2, rets_t>::type rt2;
  typedef typename element_or_null<3, rets_t>::type rt3;
  typedef typename element_or_null<4, rets_t>::type rt4;
  typedef typename element_or_null<5, rets_t>::type rt5;
  typedef typename element_or_null<6, rets_t>::type rt6;


  return Act::template apply<RET>(
    constify_rvals<rt0>::go(r_select<rt0>::go(get<0>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt1>::go(r_select<rt1>::go(get<1>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt2>::go(r_select<rt2>::go(get<2>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt3>::go(r_select<rt3>::go(get<3>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt4>::go(r_select<rt4>::go(get<4>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt5>::go(r_select<rt5>::go(get<5>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt6>::go(r_select<rt6>::go(get<6>(args), CALL_ACTUAL_ARGS))
    );
  }
};

BOOST_LAMBDA_LAMBDA_FUNCTOR_BASE_FIRST_PART(8)
  typedef typename 
    deduce_argument_types<Args, tuple<CALL_REFERENCE_TYPES> >::type rets_t;
  typedef typename element_or_null<0, rets_t>::type rt0;
  typedef typename element_or_null<1, rets_t>::type rt1;
  typedef typename element_or_null<2, rets_t>::type rt2;
  typedef typename element_or_null<3, rets_t>::type rt3;
  typedef typename element_or_null<4, rets_t>::type rt4;
  typedef typename element_or_null<5, rets_t>::type rt5;
  typedef typename element_or_null<6, rets_t>::type rt6;
  typedef typename element_or_null<7, rets_t>::type rt7;

  return Act::template apply<RET>(
    constify_rvals<rt0>::go(r_select<rt0>::go(get<0>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt1>::go(r_select<rt1>::go(get<1>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt2>::go(r_select<rt2>::go(get<2>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt3>::go(r_select<rt3>::go(get<3>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt4>::go(r_select<rt4>::go(get<4>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt5>::go(r_select<rt5>::go(get<5>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt6>::go(r_select<rt6>::go(get<6>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt7>::go(r_select<rt7>::go(get<7>(args), CALL_ACTUAL_ARGS))
    );
  }
};

BOOST_LAMBDA_LAMBDA_FUNCTOR_BASE_FIRST_PART(9)
  typedef typename 
    deduce_argument_types<Args, tuple<CALL_REFERENCE_TYPES> >::type rets_t;
  typedef typename element_or_null<0, rets_t>::type rt0;
  typedef typename element_or_null<1, rets_t>::type rt1;
  typedef typename element_or_null<2, rets_t>::type rt2;
  typedef typename element_or_null<3, rets_t>::type rt3;
  typedef typename element_or_null<4, rets_t>::type rt4;
  typedef typename element_or_null<5, rets_t>::type rt5;
  typedef typename element_or_null<6, rets_t>::type rt6;
  typedef typename element_or_null<7, rets_t>::type rt7;
  typedef typename element_or_null<8, rets_t>::type rt8;

  return Act::template apply<RET>(
    constify_rvals<rt0>::go(r_select<rt0>::go(get<0>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt1>::go(r_select<rt1>::go(get<1>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt2>::go(r_select<rt2>::go(get<2>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt3>::go(r_select<rt3>::go(get<3>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt4>::go(r_select<rt4>::go(get<4>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt5>::go(r_select<rt5>::go(get<5>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt6>::go(r_select<rt6>::go(get<6>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt7>::go(r_select<rt7>::go(get<7>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt8>::go(r_select<rt8>::go(get<8>(args), CALL_ACTUAL_ARGS))
    );
  }
};

BOOST_LAMBDA_LAMBDA_FUNCTOR_BASE_FIRST_PART(10) 
  typedef typename 
    deduce_argument_types<Args, tuple<CALL_REFERENCE_TYPES> >::type rets_t;
  typedef typename element_or_null<0, rets_t>::type rt0;
  typedef typename element_or_null<1, rets_t>::type rt1;
  typedef typename element_or_null<2, rets_t>::type rt2;
  typedef typename element_or_null<3, rets_t>::type rt3;
  typedef typename element_or_null<4, rets_t>::type rt4;
  typedef typename element_or_null<5, rets_t>::type rt5;
  typedef typename element_or_null<6, rets_t>::type rt6;
  typedef typename element_or_null<7, rets_t>::type rt7;
  typedef typename element_or_null<8, rets_t>::type rt8;
  typedef typename element_or_null<9, rets_t>::type rt9;

  return Act::template apply<RET>(
    constify_rvals<rt0>::go(r_select<rt0>::go(get<0>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt1>::go(r_select<rt1>::go(get<1>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt2>::go(r_select<rt2>::go(get<2>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt3>::go(r_select<rt3>::go(get<3>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt4>::go(r_select<rt4>::go(get<4>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt5>::go(r_select<rt5>::go(get<5>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt6>::go(r_select<rt6>::go(get<6>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt7>::go(r_select<rt7>::go(get<7>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt8>::go(r_select<rt8>::go(get<8>(args), CALL_ACTUAL_ARGS)),
    constify_rvals<rt9>::go(r_select<rt9>::go(get<9>(args), CALL_ACTUAL_ARGS)) 
    );
  }
};

#undef BOOST_LAMBDA_LAMBDA_FUNCTOR_BASE_FIRST_PART


} // namespace lambda
} // namespace boost

#endif

/* lambda_functor_base.hpp
DGkxXuta/a6M90LuiehmCZfBcAE24ZowXCTtPU31Hhz2w/zfWO+zB+cS6ieJe6b6A1vRjtCb9gPwyF6GRNpNQGI3kf8fprNc903oL5lOKEj23tKe4gSmUE/DeZ7yCNqjRtLuNIp7fEZzHj2TewzGcD59LOVIBV7K+e4x3DORyvnuNM5zZzJ8bh32JgStCqx1f8K+L37ZPQquirPfp5BQce72KqRVnNv9CqUV//yehY0V/7p9C//snoU41JdkUDZoMWgNaPsq/xzk/+PlAk3+143/c4rTzbWz5sj/5437zTPN1uKPasu15n8Ho5Wz6z0y9lxvdU/Pm5E1Tfwqv5tn9eOiq7bwA6hN4pc9I93qnT4DmcMRS4XpMt8wP1rpc4W2cxzzhVE5fnwX+DjkKnhd3qsHjBiXMurK9OyigvQqGRvrMUdWXubs2UgiO8d6xsESCdtdtbA9E4Rx8715trx3F85Q3L+wA+cvrBT/l4yWfA+/W55bGw2xS7Eb9jWUIbd/Bp4Gec/L6/QGzzSyeU+3pvelpDd51ozplentRnq/Ef8XjLY8k+Q2eV5jNEZ59kEe7oPm9wIDjFC12rDf38A0bM/rOCZ+ragf5GS3+Xwh3s9Dqp//wfy2Ff9AyJPvmz89N4EUZR1jY6ZxQMIkKbd8M6OjyLgTeasam0w3i0jvkTgsMk015iLVDSCT74lOIkeB9ds1nSXeKNHVLvOsEwm30jD5Nwn/7MLMrGmS3h5reihTVDj9raWOIn8cpHPImHUzw86YlTklx3wX5Jjpdon/j0YkdHMxaA/IbYQo8wxEDAnkjMzro6Fz52xPkFvpMyAq9Flcwid7MH5l8gXmncHjjWsQeEpMnnol2z1Oj+b7inxR5CsHXyrqjXNBSoDLGR7g9DgamukMhfti0AIzDs+CbN/wXp79Lspcb8FYiyyi86c6yZrwadY1wX8UndfX6/Y+kGeHxGlSS8QRaO7J5jjxNwhUAhx3npBeD9nnLM5aueCNqnF7lIwrOR73beMcX5rtNgJlbJ27+tJ0Y9uCm9Q/rtlFXRU3qSOoN3CTeoO0e4cFSNoYGUdUP/Msrr6S6wZ4tgDmAvdGozyEn32TzITqzsm+b7Lo9u8SNsquX2K81vk/6eZ1P1H/TTnL0fCeofqD8Nue+8W4rH0cjpNhXNIuJa5RhrfPfF+eWyD/EbqNOsVtpDEZpXmvWqS/iblG3ONUoO1eK522bd+SKWF3ogcN1X3LzeIWekbf4pXtB/FvavYtEucsqUyT9RzGOvGfD98WtjL69EG6b+kkPD/Y9T2S7lbxD9L7kKbKc3PdF0XJ86Aa+yKbfkZ/a9YtYUcYZl+ww42xTpC3v0j2OOud2a94+eYFsc8IKinzOIOVTZsXvjVePk/JHs3jE9dO8CyUNBdkWuM6Tr4o8mXUY/9T8h36nyZm/yPp7EL4oHrsf0IWhNnIIjxp9XT/46pL/1P+ZvX+x/FW9f6nOeII8Ol/VocR2ff0Oou+J+mts+t7pE9h22Tfw/4IbayWfqZxZToq36efcXFibTrIwfVu61Dhdr9l089QGtt+xn4dOOOx2iumZlvPDPpc/Ifa9iMM69tGdNs7IP4ToVOHsvnvlbr+gfCMR/yGpf1mVu1B2WP6n6/Lu708Byuz/sTXhz6CWZeDE+zqu/CUBbP91G95RtvhvCbqi1lHfnpe06wT7fecXZ0QP+rVWraLuK6/E8jgmtVXIEfGHmvZ4qRWy/utfk/U9Yn7NSRMO9XK/uwuxmlfzo2AReIfYlvODCs6D4JCykELROcxZ+i8MXl6NWC7Dgj2OFEGdWnbU/ZUb9tLzGe27bruofhSt7Wa9d+P+vfwzLRLDbg=
*/