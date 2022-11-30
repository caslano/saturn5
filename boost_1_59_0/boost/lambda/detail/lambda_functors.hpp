// Boost Lambda Library -  lambda_functors.hpp -------------------------------

// Copyright (C) 1999, 2000 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org

// ------------------------------------------------

#ifndef BOOST_LAMBDA_LAMBDA_FUNCTORS_HPP
#define BOOST_LAMBDA_LAMBDA_FUNCTORS_HPP

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/utility/result_of.hpp>

#if BOOST_WORKAROUND(BOOST_MSVC, == 1310)

#include <boost/mpl/or.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_array.hpp>

#define BOOST_LAMBDA_DISABLE_IF_ARRAY1(A1, R1)\
  typename lazy_disable_if<is_array<A1>, typename R1 >::type
#define BOOST_LAMBDA_DISABLE_IF_ARRAY2(A1, A2, R1, R2) \
  typename lazy_disable_if<mpl::or_<is_array<A1>, is_array<A2> >, typename R1, R2 >::type
#define BOOST_LAMBDA_DISABLE_IF_ARRAY3(A1, A2, A3, R1, R2, R3) \
  typename lazy_disable_if<mpl::or_<is_array<A1>, is_array<A2>, is_array<A3> >, typename R1, R2, R3 >::type

#else

#define BOOST_LAMBDA_DISABLE_IF_ARRAY1(A1, R1) typename R1::type
#define BOOST_LAMBDA_DISABLE_IF_ARRAY2(A1, A2, R1, R2) typename R1, R2::type
#define BOOST_LAMBDA_DISABLE_IF_ARRAY3(A1, A2, A3, R1, R2, R3) typename R1, R2, R3::type

#endif

namespace boost { 
namespace lambda {

// -- lambda_functor --------------------------------------------
// --------------------------------------------------------------

//inline const null_type const_null_type() { return null_type(); }

namespace detail {
namespace {

  static const null_type constant_null_type = null_type();

} // unnamed
} // detail

class unused {};

#define cnull_type() detail::constant_null_type

// -- free variables types -------------------------------------------------- 
 
  // helper to work around the case where the nullary return type deduction 
  // is always performed, even though the functor is not nullary  
namespace detail {
  template<int N, class Tuple> struct get_element_or_null_type {
    typedef typename 
      detail::tuple_element_as_reference<N, Tuple>::type type;
  };
  template<int N> struct get_element_or_null_type<N, null_type> {
    typedef null_type type;
  };
}

template <int I> struct placeholder;

template<> struct placeholder<FIRST> {

  template<class SigArgs> struct sig {
    typedef typename detail::get_element_or_null_type<0, SigArgs>::type type;
  };

  template<class RET, CALL_TEMPLATE_ARGS> 
  RET call(CALL_FORMAL_ARGS) const { 
    BOOST_STATIC_ASSERT(boost::is_reference<RET>::value); 
    CALL_USE_ARGS; // does nothing, prevents warnings for unused args
    return a; 
  }
};

template<> struct placeholder<SECOND> {

  template<class SigArgs> struct sig {
    typedef typename detail::get_element_or_null_type<1, SigArgs>::type type;
  };

  template<class RET, CALL_TEMPLATE_ARGS> 
  RET call(CALL_FORMAL_ARGS) const { CALL_USE_ARGS; return b; }
};

template<> struct placeholder<THIRD> {

  template<class SigArgs> struct sig {
    typedef typename detail::get_element_or_null_type<2, SigArgs>::type type;
  };

  template<class RET, CALL_TEMPLATE_ARGS> 
  RET call(CALL_FORMAL_ARGS) const { CALL_USE_ARGS; return c; }
};

template<> struct placeholder<EXCEPTION> {

  template<class SigArgs> struct sig {
    typedef typename detail::get_element_or_null_type<3, SigArgs>::type type;
  };

  template<class RET, CALL_TEMPLATE_ARGS> 
  RET call(CALL_FORMAL_ARGS) const { CALL_USE_ARGS; return env; }
};
   
typedef const lambda_functor<placeholder<FIRST> >  placeholder1_type;
typedef const lambda_functor<placeholder<SECOND> > placeholder2_type;
typedef const lambda_functor<placeholder<THIRD> >  placeholder3_type;
   

///////////////////////////////////////////////////////////////////////////////


// free variables are lambda_functors. This is to allow uniform handling with 
// other lambda_functors.
// -------------------------------------------------------------------

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

// -- lambda_functor NONE ------------------------------------------------
template <class T>
class lambda_functor : public T 
{

BOOST_STATIC_CONSTANT(int, arity_bits = get_arity<T>::value);
 
public:
  typedef T inherited;

  lambda_functor() {}
  lambda_functor(const lambda_functor& l) : inherited(l) {}

  lambda_functor(const T& t) : inherited(t) {}

  template <class SigArgs> struct sig {
    typedef typename inherited::template 
      sig<typename SigArgs::tail_type>::type type;
  };

  // Note that this return type deduction template is instantiated, even 
  // if the nullary 
  // operator() is not called at all. One must make sure that it does not fail.
  typedef typename 
    inherited::template sig<null_type>::type
      nullary_return_type;

  // Support for boost::result_of.
  template <class Sig> struct result;
  template <class F>
  struct result<F()> {
    typedef nullary_return_type type;
  };
  template <class F, class A>
  struct result<F(A)> {
    typedef typename sig<tuple<F, A> >::type type;
  };
  template <class F, class A, class B>
  struct result<F(A, B)> {
    typedef typename sig<tuple<F, A, B> >::type type;
  };
  template <class F, class A, class B, class C>
  struct result<F(A, B, C)> {
    typedef typename sig<tuple<F, A, B, C> >::type type;
  };

  nullary_return_type operator()() const { 
    return inherited::template 
      call<nullary_return_type>
        (cnull_type(), cnull_type(), cnull_type(), cnull_type()); 
  }

  template<class A>
  typename inherited::template sig<tuple<A&> >::type
  operator()(A& a) const { 
    return inherited::template call<
      typename inherited::template sig<tuple<A&> >::type
    >(a, cnull_type(), cnull_type(), cnull_type());
  }

  template<class A>
  BOOST_LAMBDA_DISABLE_IF_ARRAY1(A, inherited::template sig<tuple<A const&> >)
  operator()(A const& a) const { 
    return inherited::template call<
      typename inherited::template sig<tuple<A const&> >::type
    >(a, cnull_type(), cnull_type(), cnull_type());
  }

  template<class A, class B>
  typename inherited::template sig<tuple<A&, B&> >::type
  operator()(A& a, B& b) const { 
    return inherited::template call<
      typename inherited::template sig<tuple<A&, B&> >::type
    >(a, b, cnull_type(), cnull_type()); 
  }

  template<class A, class B>
  BOOST_LAMBDA_DISABLE_IF_ARRAY2(A, B, inherited::template sig<tuple<A const&, B&> >)
  operator()(A const& a, B& b) const { 
    return inherited::template call<
      typename inherited::template sig<tuple<A const&, B&> >::type
    >(a, b, cnull_type(), cnull_type()); 
  }

  template<class A, class B>
  BOOST_LAMBDA_DISABLE_IF_ARRAY2(A, B, inherited::template sig<tuple<A&, B const&> >)
  operator()(A& a, B const& b) const { 
    return inherited::template call<
      typename inherited::template sig<tuple<A&, B const&> >::type
    >(a, b, cnull_type(), cnull_type()); 
  }

  template<class A, class B>
  BOOST_LAMBDA_DISABLE_IF_ARRAY2(A, B, inherited::template sig<tuple<A const&, B const&> >)
  operator()(A const& a, B const& b) const { 
    return inherited::template call<
      typename inherited::template sig<tuple<A const&, B const&> >::type
    >(a, b, cnull_type(), cnull_type()); 
  }

  template<class A, class B, class C>
  typename inherited::template sig<tuple<A&, B&, C&> >::type
  operator()(A& a, B& b, C& c) const
  { 
    return inherited::template call<
      typename inherited::template sig<tuple<A&, B&, C&> >::type
    >(a, b, c, cnull_type()); 
  }

  template<class A, class B, class C>
  BOOST_LAMBDA_DISABLE_IF_ARRAY3(A, B, C, inherited::template sig<tuple<A const&, B const&, C const&> >)
  operator()(A const& a, B const& b, C const& c) const
  { 
    return inherited::template call<
      typename inherited::template sig<tuple<A const&, B const&, C const&> >::type
    >(a, b, c, cnull_type()); 
  }

  // for internal calls with env
  template<CALL_TEMPLATE_ARGS>
  typename inherited::template sig<tuple<CALL_REFERENCE_TYPES> >::type
  internal_call(CALL_FORMAL_ARGS) const { 
     return inherited::template 
       call<typename inherited::template 
         sig<tuple<CALL_REFERENCE_TYPES> >::type>(CALL_ACTUAL_ARGS); 
  }

  template<class A>
  const lambda_functor<lambda_functor_base<
                  other_action<assignment_action>,
                  boost::tuple<lambda_functor,
                  typename const_copy_argument <const A>::type> > >
  operator=(const A& a) const {
    return lambda_functor_base<
                  other_action<assignment_action>,
                  boost::tuple<lambda_functor,
                  typename const_copy_argument <const A>::type> >
     (  boost::tuple<lambda_functor,
             typename const_copy_argument <const A>::type>(*this, a) );
  }

  template<class A> 
  const lambda_functor<lambda_functor_base< 
                  other_action<subscript_action>, 
                  boost::tuple<lambda_functor, 
                        typename const_copy_argument <const A>::type> > > 
  operator[](const A& a) const { 
    return lambda_functor_base< 
                  other_action<subscript_action>, 
                  boost::tuple<lambda_functor, 
                        typename const_copy_argument <const A>::type> >
     ( boost::tuple<lambda_functor, 
             typename const_copy_argument <const A>::type>(*this, a ) ); 
  } 
};

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

} // namespace lambda
} // namespace boost

namespace boost {

#if !defined(BOOST_RESULT_OF_USE_DECLTYPE) || defined(BOOST_NO_CXX11_DECLTYPE)

template<class T>
struct result_of<boost::lambda::lambda_functor<T>()>
{
    typedef typename boost::lambda::lambda_functor<T>::nullary_return_type type;
};

template<class T>
struct result_of<const boost::lambda::lambda_functor<T>()>
{
    typedef typename boost::lambda::lambda_functor<T>::nullary_return_type type;
};

#endif

template<class T>
struct tr1_result_of<boost::lambda::lambda_functor<T>()>
{
    typedef typename boost::lambda::lambda_functor<T>::nullary_return_type type;
};

template<class T>
struct tr1_result_of<const boost::lambda::lambda_functor<T>()>
{
    typedef typename boost::lambda::lambda_functor<T>::nullary_return_type type;
};

}

// is_placeholder

#include <boost/is_placeholder.hpp>

namespace boost
{

template<> struct is_placeholder< lambda::lambda_functor< lambda::placeholder<lambda::FIRST> > >
{
    enum _vt { value = 1 };
};

template<> struct is_placeholder< lambda::lambda_functor< lambda::placeholder<lambda::SECOND> > >
{
    enum _vt { value = 2 };
};

template<> struct is_placeholder< lambda::lambda_functor< lambda::placeholder<lambda::THIRD> > >
{
    enum _vt { value = 3 };
};

} // namespace boost

#endif

/* lambda_functors.hpp
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
*/