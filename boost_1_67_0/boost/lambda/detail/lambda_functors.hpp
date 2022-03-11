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