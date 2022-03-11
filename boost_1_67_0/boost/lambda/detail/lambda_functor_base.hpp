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
EoPFVHehx9Ly5b+N4i0CEdX5lP1cdh9hwH4Jzo/JyqcIKi7Ncrjh5fuYgv64Qs2ZTS4r0VH0keqy/j8Oa+0pSYMH6BDc1N96AY+E77cUwABuQV14uN9k7lPwcrjLTaNL3brEOfEP9knYn6AbfVCxfiP3gbA/0PJRVHSy30ltp8YuRvh7SJAqcNz1b74GoBidT4EhKyOYt5Nm96aR8YQtWIQ63EwUREwA1B5dkLeCW2mz0zJPyC4tJ2++eCbaPs9tW34ntMBRjcmbMvrB+J4g8rZ1KcJM/XdXspObiffJYi3EERcPbLtR8Tx/AriXqb6uf6BQREp6dvQRdr5LHzaM67Wnt2dWKU+28oqlF4F9v9VKdRH/pT5XF3z/Aa5rnfjHXj32k6rTufNVNi36EaUzQwY6QwQc6lX30JpdDfPn7YFogkBH4ScJt8XxtnPO9Zb6XCzJTh6yWd7OsJWIug4QDK6LNUDX+B0nFRkXEHSwQWuk6fPa1Rujt9m3P6lkXQUGaaZbOhEB+2ROKTaV36uD5wmelAPNb/uP6nEX/h/WRnVWVcbO5oi8MQ2pth5DAW8tTmActKdRINVZ613kVIv5nxSS2mNT2BgzQg6t4NvW7DC2pgt2Z3cfw+ZGTgADLPzTuo2dsf0GqEfelo32jWzaJ7QwKZnPPGv6L9fVbH6FHSqGVpQGEEhlShs0ZRmxUO+3+yzKozuoSd26tk7tKDj2Jqn1qxh+yQByp+2ra7iX7JmJPCH82fJ48gFEGD9YYQ5fjW+8tTRomIjCxHj091bhKL6HPoYpQQ1oZnplun8SkUidkDBaqbNF1MNiBqwjonFVDSvluNAodkrZ8MLauflPRU6lGC00RCUYf+Nix2Lr4rD3vTRwRpJ4j2HMt25dasf7EstJIAmWj9TqmFaQ2WBDWBoQjeIvImoe/DVOGKXAquHkF1uYkp5Ilrg0Si0/oVzuuKOzFRadbitLWVQeW8CY0cyTaIEAlgk9rwXKkKP4UHir8dlfDd6CWsYoxzdkGE7lkdLV6ZAfxv/kIxDpCup4/HiFVlj2/CUx1ABtOTJUvD6br3xIIdokCfqyJPPtmT3hqbLDOVqEXH0dYQw7JnnBFX8wsLad3eOXmzlna8pcLuJTqifJHcEUJ2NKPMCi7McxhuGQstpp3gUZpyw/0rFJRv0Ym7ZA5dmoXWg0Nw+NFctWucvcy+blsJKWQIcJ8TVcJw5yJX2CQMglYJIQNOVvLgmkn0KqgWqT1W9k33BMGN6+BCDXlwCtPLHAmv43aewvadIGLuKW9LxymuR6oMW8v8YMZYsl4ocO2lVrUtO2r47qF7VCeZwqQ/y4Jxcq4TxufTGCsAHTiVQPvynQ0e3wEUsm73iuhioUjwsX4KmAnWLTpwNRKw/CXQrpxAF0C/nSDRSWemvqgvPFQ1ruZ2i0AcqZZECFx0CDYiBl+Uq0T8wA4necS+LacziKoMJpPKwfUnXMyKgXdn77wde8YHrtFB8ckp6TQ6+GWK8W24/uK7yh8c0TTZqjXMIb94yzGw5pPMQLC7+JRkJViEzYRq9X3DvfrxuiAnE5W9vpAlSoC2iHLl6mROPEx4kz6qmZQI0965SNQpw468Hq8LpF5tJGFB8MUm63KGSLRwr6l0FeSdDPXqNZnBEn/yHsXtWtRPFRcww+lHQnY0P8KN5TfQtcpto6Mw6TsUFrwud5e/F37FH/kzUL+z+dB7l7ZgelY5XWdVy5TfI8VADMzpL+Yq57dnioVkhiJSV6gXWj97E6b/h+tUXh6CaaiMAB/HZLQMji6vVN+Sn1aCFDvJOvqCs8xTdpXWNtrUc2QVfOPxAXBKcQFeehOZ274knZZnKIzprsZVHzin928QucATL4GiifixnN+QC3Lo8tTQEmarARG1xCMUYO6/TI2UGNvwbVdzdOL8OJTHwi23Pyv1LyoCkPQCVcW57wFLwnnmF2fSUpS17DpXd8O+D5kfPH9uog2753SxDegXHM1SyNzTAURS6CCT7vx1VdUGHcambSobiQCgzCTyKwTXLaX71zJuH/MUtRWm8ATIfbhTP2O86LN615JdqF9U+wJsc5WUPBmM/ExlrvpAWtPeAwxtFAwAzcd0MCHS5+EAp5c4Or8CuuwThIBWSarKFLCXaJM7EwKKxKGRIPZbBCbojX3Rru0LKiWR5s1z+BiRHL446B0W0YpJyD9SHHzChpt/Yo0QTN/13GB0rBXn14z2/6256YiF8hqFDNUx7w7ISn5ipsRy9llwaXEclIHdIDNi3VJrcRPkmJbUPAMjLkJQsHOCGklY0z4heJAsGDmXB2Tpd+HLS5q6iFpWtSmHttR55WIVJ/90TskNFDYKwIxrWsB3HV2QmHEi+/8kI/EV29NOs/t6ovo5bG/FBpjzajmNOYgS4wGl1IAxWsRoK4RDbplOZnrW/L9gdNTLoLkRxaDZlO8w4cU3AkLsAPtt3nuKk7TAsOBdD3qZrWdnCmoUDhaipZwSc07YB6FOqZQgxnmIIgUJoT490pLgo6DABXqG3C3B/MnCkMw4/4xgPRe1ucNon833Zt00AC51YLIpo9+flnR+fFfBSGyzEVgOK6F58APomd2hv/Mzb4JwK3W9AUPvfWuA45iRUkYIIqVYHNeIS1OTQpOgjswiIXVlVXuIPp3nl8svmqbVEZjDW2GdAjCVjbasAEilI/+6myI3xarrBkaErFSFL2lszI4VxMXNuCahtXYgVX8/EMgL6V+0m0EB17YUfDx5zVJ4IYccG6QulNlwGQNxrT37gQinyMuX3QkJCwN4o0ccHPT/5P3XC+LIbcEdD6QAfymXAVtb4az8vR+1K4Je5eyLgmEKf82TG/JCQ+LNx0jOiEDdVEIL1z56WVJ7WA2bcxOzdz3Ao/KFv2AlksRPlKjiDAw/D5ekbXyiR05rvlgWjCmrqDd5rFJxnCJaBwSAKfF/6shvip2SEmbrWHKiBMPryXQML21Ki2iXvnCIHZGtCDOSzhdW3RmVXCIib+L5UXw1lFoHpQHfoMgSkJ1RoWf+kE/rgAWAm9d8yzr91Ikb1FS5leiNYAcV3QavLWTOa/DBJwznanQNwmTRykQ+KcN9aqDqXmaymIbH1lAI7F153t9iWwFGKxuE7vsbDqQ5KeRFYQYkHG87ErYJUnkt2g/E1jOAkgAkW97JQ6puqMgkbWEuXAf5f8rwPb0/dhT8UtK6liJylS4e1DwtwGGR+sWFeJsp0YBGfyxeDGXdiIciWzPFsA85Px9lKPuWxHN1Am55AGP6wctgE/LA2lqBT6wMZu8ysCimEO+MO5/5k1JZ95vFmd4tK/TUSZgubHJI2KESB0oPjEj6HiUbhhr45sG/+x4plkoxyk8t7lgAV5A+AUxyrYu7twl3o2Ma2/2EXdjpvA/AMQ7jtVGKDzFoaPlUaLte2D6Z/MhDwiseXspF/vm4+hra6rQL+jiluKoMQki/x1IADpBApGPTXp3LL73PyBOKc/JwsD5YlLAdBmbOVii+fbneM0wYeM0C3XKvkU9mVWEle+Sqm8cNJVIPfORe0rmPLZmgcH3mAB3CyFWxdjKuaLalLXzsVtStf/0/fHzqrfORbAg+zj7cTr3odAW8usA16Yw2Om4cgz2Mk6Qqrn8BWdh/Yjym7qq57vDXdVl6qoHLXrE+ugwzVrtg+Uzv2Y15VQkVNkYSrhcfuFIeuac40+fB2U6/C7D/lUaik7VnAu2hL0yLBP/hTgKPTDtGwri4gDJLV+3pSV5u6puhKHFgUekTPI/oomhSPqqYuM4MwWyWQCzwiQ40izwlqRGsLWqN84W9Sw1TGcQhZWz7cLErM0aLbcXn57MPSgwwJktqS6zSxrpi9zkatOzOF7jg/BZYWnFkdC8A2m1fTtyLW6oVNBHcGZ/4R/9AxCEmZAfkQEdGJLAFxURq4dyuBz1FIyyMiMHMLVUjxA7k4klyRJFDS2FeRxP9KfRsOd8QdZP8Rz7OIOB2pT+XvGFOpFX0Ca3j/t9ANebnXY2visZG+jqMIxZh3GxlaDEFklPcBfmpFBKtmfn+mcNveHMH7bnmKQk0wTtDbpCwRDT+fQLyDjFARRHJ7rFGWqH6OM4aP8oQENpO2Hmb4AZCXGHBHTLo1dKJMkmcmxCRJMBeKv41EbzXYpy7u9+/YtpYwa7cA/ar8qJfuXKRRtLmgbk7axTi1gvidtQzVVJ7NKYJLQBpMjmxG+yXT4etO8jwUq7WT+ry4LfjaAwpN8+WapJVb8a+WiwC9Wc8Fd9cID92WNRnrT7DTYA5ptB78ujVU0fh1E1pjzbiqOcvxgeQWw6XH7HiGKiPlnfssVEePDvyNt0p2kDRN7XmVVpKQaGup1AVtuBZyEsJKrFRx32Yq99acCVFw1WZ7M/fFz0cU6mGwailyYP6rG7nh2GKR5q4c85EYY7JuyB49c3N/GTbRqyGDsH6h4AqzSN/Vb2SbOn9MsxoNX3GiTYB/6GBuV46U+XivcKEw9QWXiABjMvYDydTSs4w7ixvH6QS5SK39XZGEXKh3++Pobb9I9WoPfcNU3forDKKR62+CO4nPwDH25FH1U6CdcneBFykfKpgVWhnuceTRqt2S9FfoXTxkgsGdECDp106WN2XIURmV/8GopRK8cAY2g3L3bLpqI3JKnRYrnhYcLv1D4f02kadyGYg/TdZNbwbjgayZ4iIIdmDd6wA8NUb4qconiGwzAQuo7Ji4B985ySy284+FR5LWY97VhRIBYWMX1iXl+DvUrVJq6DCDYxwQKuvdXi4BMulkYW3vI5oojYsfSvmjccNtcVMOVvi10O7szqiNi6GaOSkYPYxDXnV1G5QuJr5OcihAJ2itknVXYbxuhe+KGxlN5BxQWzpYz//PSOwxaM+ovZVt0XChxbN7s7bjy75lSByPQQMd2xDa7cLD/fBfgEbm1ovZw9HWz5fc8T99fbytESwJTjQBInmVeZIYyJMINshAKzRVaBS8heXqKY6D8WH3BvWaNS5x8I3mpimqO0iDjk/b7YaHoUeb3kVNCWw3ziKyQHAVghUhTYiwkjHjjokw1N+wxLZChjkJjcBAAoCcA0IOGhsO6NZC3eOLA3yN0NuqB1QjFZbSnq+ydEOCy7HrNaqHtnqLHMMPy/VSgBzV9Wb55Hhlj2zzIWeGNB2T6ZDsa/craBU20t7/weSjz+iFHr0kn5/NUWs8pKXfoBxjg4anXfh/8maiEemaTELy8bR7kFGEpSh+DCiWDlE06qqTsxAEa8mvcW7RteSNMvLdvnRAZL8mrZoBh+MfIu4NEE/fUB97bAYseRrIb3G97zxCBeDJfE+fh9Fjp2PVoCOkiC0enc6bt6hkIzw3A1Ui2HM9DA1xCEISmtiO25KQjsCd8jhY/4w5Uccs1Sxv896pmfd3cu8hOfTi92l/kFK/L47GvMRB6XdS85gGA5uWP/b/adKtoZWdMo+4lKfPgUCrcZ5r65zJuyj2lYy0ia3QS//5uaq+luLdSYO+8OCOgRvj2/HIB1QSXnt1Fb2dDcjWwz8n+YtvHxrQ6E6BcIholoUCTzHcuqONiBvzUshS7gEwmVWQ/yPYDg39tC4G0RAvQjFRZ+UT6yS1bFbVlKVwB7R5iVLSwYT+1e3B7+xh7zYYPZXHPXvAdi4WKxIPb1DtmljvvfIqcLgs3ZhXsoNcALehBHMC72oDdFQhEZkoPLlD2l1vqLM7WO1QTFTRwFN6a+BQQrSjFO+V3A6jsV7zVznisLPskzQXTiQgcZNWdH558s5sMeXwaxXtVZTL6i2PFTQhuSSJyB6mQDPP577M4CB7E8CzNQ+f0Gvq6OAH5BYVMVOhbTRCObtSvEfGRPNvOGJ7gyvPR3bkMyR5l9GORb04eq1QNEZ3WWI8Ulu8IZxVclrqYfNLXwmxRSRn8CPj6sz1rohp8sCYwtQd68cEdlbN8y8U7wRBdZDFcYuX4GoMp18gux65p4waqjWnMqFYqD/YnmVpqWuaRqmbgKu5EN1oCQlVTn6IcAIG4jMPzLWO5JyCpGZoVsv1hn72iMAXd6QJOHd/2zGzyvBkfEONj6Ht1uCbjcxK5BIgDj9Qn3l97DvwEHGzEfpxxDZpfAP9gKuw5Z07jWmAsYKf1mhzk2gOemKiFblunt9ahycXYI2gnY893yg0U/S/1JGb0LQSCpxzBzL7B/QD8hKQAAfx+fD34LRTRoL2TQIt3c89nXIGu+Evs7tsRd1sHIB0PMoT/KcqDhwR2cRP6IwFYfSYI6D1mOR7Y93k9HdM1Pd14ZLn2j6I+ePCuHzo+4QhC0UVH3065ce/HWEB92lVI7guGPQ+nEmoAWFPVTk4Cd0ULpAZugOebwj0mmsFrxuwDC5Wd0dxJLo32r7n/ZRM4KiLJVYumAyy6K/8u688x/EeP6vqQfUCGZTgmyzh6VU0z4vS9QkJHRexeW8lOsTIRL7Ko9rgcy7PMlC0YJOCMof3XlmjnZ2LDKavPWPgbwiCMRudaKi4Mh/eYajvkYYry8Sw7iDY0jNCD+3Ud/B3n0Q1pl6crqKSxpxSw3nNTouLCcPP8PFKeUkyhcxS3264YxLNqepnv2VvIx6mw5AIDuJgRdrxRY9rqUjsdXaedLp3igsqB6trbLEZNX/cftN3pXZOQKQ66id7iH8dAvCYjUYR8rq6NcxvYlBOLDGxAq3bVSXbhw9ZeT41iOpxXhu5WgOe9D4Bae6s/YbldIwsIWgi2itDRiJ0TX04ZTff5cEAUtoexa7IYEdwOflFLDhdfzTBUp3JhXt86zlN+8Cr7UXtaAxtYSP2Py/a2jvzXhcjMp8ur7s8Lpnw2d49fj3yheG/reHPQwPz7APTAscs1r7B4cWiNYS2zhgG9C7ZaDj7rZMRbJjutghrgCzRlAgyd/fho6ezBi5rS7+a+6hcoMl4WitM03cVaWRht++mYn1m+RhEunBRkuuI+cgVfIKEhpCa2XGUC6PDNtYoSxu4Ik5EnWCEXzAiKrunU9v/QCxV7RwCXdJQ6E5tNWJRklsG6RYX6LQqGdT9UuVPD6UN2ipVNzInHeU5BiQcYpgda6/9dRpLZ2H1yvIIpQHq9yA2ZhLUkYzruf8UOZAB5XHjvtD7/m2KOF/v3R30kdF+BvyCLSAQw8dqjKu8jq/frcvQb1A3q+DPTM34IdNgotyxsBPAhumPXVAzB+In4qClPBfa2JNsBDTxtrb3qWcHP4QTjdRu7HrwHaiiqe1tHkLhEXKPWv+L2OFzCMXlMvCdfRuVtkpA93xzFIkMon/EGIBmcedq3DHXHHIyCbQIl7FJIghoOHTPF4u9LOoXFVm39BocJLBJQHrm/mRJFXFwKQJDcSLu4+EP3Y6qMJi55Jg6hjWcG2iWDeCbOQwue0VTUNBDdbQxY9KjA7Y3qJlHTWvQgENay1wIqC503ju8E28olqFO0eKrHc2dqsstNFjPU6n2ug7QQm9ZZUQR5WAI6htLas/o2s8nFvlPZt/lBGKrvaSnmNRwMTZwGTkzYrVG8IQSSQ6EuXGAL9nvyVYUq3ab+vkixiIc3kv016OY1YG1ZNYG+Dqm1bmjeQbcG8jBrDciLhF/N6ieIBDCqeb+1snop7EYA8A7itodJbowV8nQ9DMRfd8qQQgK6DahGmm0p3/iWckgoV8IyjsCCtm3z9ruDY9UZrSt+Wk9phQdtIAqU926KEGHxZdNBmMMkmmshAfJqUfy3ot7ZvwcYn9EeQ2Jy6HLiT/J7smTlXeTfqemI+UIG0q/FB/QOJIbR6uNxkSa9/WCRx2jFKnWY8ni+J3Tqe5C37/NY9yHFuBJY1wPsHSSEan8/eJkscILbTfiS5RRkVQRM7LpNyDdLI6kDB/Pbr+AFAYTH43t5TLZNvbYbPtYCcrpmaHudLx915tuRJuFOByrFMVecvw40+LwFZTG/sOL6qSAlm0682aru0IVRmlR1GQsCBcGmKbkrz4Ny2xtsZS7BXjpdLLE+GSdvQOewcGG9MDNJLG1oKvzuHwX4oRMBhJeZq93tHb4L2bynWK3bYTmqA+l4Szn5j7wzMdXzOcHOyO9McQ+SLTKhETNwltT8vl1vn0x6xasmXZs1KQL3cmn7kKzQDslL5YMu8zyCpCmfqWBURYCc7V7I0Cac+sgaG5JT6QXwW9kxxk1/Em2+WofF6HyRxUA+39RbeyfeNXS/zzPhQvFK7ecn8fwL7utCxvcCNxQyM2szK56LNWy3J2ajoXx6FkDDvfoRFIhuOg6nyFE6vzHk0W7d1G5HCK2zAYxaeSF+n5SlaB1VXRIBxsMECyPDATK2jD44lLU6Zu9FXIxJ0/dOT0K26KFPvD2pjPdP+LVVueiIedOvZLDuu/LEC+HxZ1OwOaRroaFKgTRFHsT8LcVUhEE09ysZ1fR0/W3B5Yxm4COZHdwKp3bPwQgdtF5jX/iHhg/u2gBgeC/jgpGESgRHwvbFT6BxDu2ZKj/O54F8RNDxk7Y6rwfnvhY+bQmHAWWRudYrdDQuqd0Xy3pKgLmDrbHt09Rm6V1EyODV6bks6grxiSGZaJ0oThzkqi4YIiEWmRf+ISxI5x0uueDpT6Q+/uzm9UnUoBAY7XtXN8jxRqAOBIe+W78PtLMW/7qvrFZtMLtOpkYsaUQuLQr2vUnr7itLLKNaNtxxAQ3qXPEzWKorOlg1TD9ljNT0kMJ7vWG5T69xBXjMfW/Cj14Q1isxXDMOAmYpvVjwWCOPYC2JuaD3GNGKE/WlzejSu7/CKhF9TROyRnGiFMg9MVVMOSfWTD37rUBiKtfSEDh82VDCsHfg4aHPmglNts3Ra5DihY8ellqQYYsAsGHjoAN+B2qGAPqsT0q4AbKTOd1WmsJpSMgLOXkCvshLrPH4KnORfMmSDRb6UcmTq2/wrk8fuIJDi34j5ein97pwrVyljIbXPtlsB2gz87hai9U6LE11XNMEKJqYsCyPiYyp+R2UkWy11wGcf1CUuaryzhv/gVgi2CqDMBCbMNvJBdVQHnMdjDWJN2/HfaDlqMSxQP/jUlSwc4ha5vi7xPEvRWbJA2y6RR9QSahQbFX2EXBpyw0MX9VAX3RfKkqqMHRUgajqHFyDONN2Gt1H7ZmzIpsv+pmaWDtTP9xYquujXU9jFCwkpaoEhFu+1xWd50/Ut6JuqSipOay82lRNl7L8IYSU9ypQGTZvSZs=
*/