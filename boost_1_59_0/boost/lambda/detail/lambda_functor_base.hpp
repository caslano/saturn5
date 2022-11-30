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
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
*/