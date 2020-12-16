// Boost Lambda Library  ret.hpp -----------------------------------------

// Copyright (C) 1999, 2000 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org


#ifndef BOOST_LAMBDA_RET_HPP
#define BOOST_LAMBDA_RET_HPP

namespace boost { 
namespace lambda {

  // TODO:

//  Add specializations for function references for ret, protect and unlambda
//  e.g void foo(); unlambda(foo); fails, as it would add a const qualifier
  // for a function type. 
  // on the other hand unlambda(*foo) does work


// -- ret -------------------------
// the explicit return type template 

  // TODO: It'd be nice to make ret a nop for other than lambda functors
  // but causes an ambiguiyty with gcc (not with KCC), check what is the
  // right interpretation.

  //  // ret for others than lambda functors has no effect
  // template <class U, class T>
  // inline const T& ret(const T& t) { return t; }


template<class RET, class Arg>
inline const 
lambda_functor<
  lambda_functor_base<
    explicit_return_type_action<RET>, 
    tuple<lambda_functor<Arg> >
  > 
>
ret(const lambda_functor<Arg>& a1)
{
  return  
    lambda_functor_base<
      explicit_return_type_action<RET>, 
      tuple<lambda_functor<Arg> >
    > 
    (tuple<lambda_functor<Arg> >(a1));
}

// protect ------------------

  // protecting others than lambda functors has no effect
template <class T>
inline const T& protect(const T& t) { return t; }

template<class Arg>
inline const 
lambda_functor<
  lambda_functor_base<
    protect_action, 
    tuple<lambda_functor<Arg> >
  > 
>
protect(const lambda_functor<Arg>& a1)
{
  return 
      lambda_functor_base<
        protect_action, 
        tuple<lambda_functor<Arg> >
      > 
    (tuple<lambda_functor<Arg> >(a1));
}
   
// -------------------------------------------------------------------

// Hides the lambda functorness of a lambda functor. 
// After this, the functor is immune to argument substitution, etc.
// This can be used, e.g. to make it safe to pass lambda functors as 
// arguments to functions, which might use them as target functions

// note, unlambda and protect are different things. Protect hides the lambda
// functor for one application, unlambda for good.

template <class LambdaFunctor>
class non_lambda_functor
{
  LambdaFunctor lf;
public:
  
  // This functor defines the result_type typedef.
  // The result type must be deducible without knowing the arguments

  template <class SigArgs> struct sig {
    typedef typename 
      LambdaFunctor::inherited:: 
        template sig<typename SigArgs::tail_type>::type type;
  };

  explicit non_lambda_functor(const LambdaFunctor& a) : lf(a) {}

  typename LambdaFunctor::nullary_return_type  
  operator()() const {
    return lf.template 
      call<typename LambdaFunctor::nullary_return_type>
        (cnull_type(), cnull_type(), cnull_type(), cnull_type()); 
  }

  template<class A>
  typename sig<tuple<const non_lambda_functor, A&> >::type 
  operator()(A& a) const {
    return lf.template call<typename sig<tuple<const non_lambda_functor, A&> >::type >(a, cnull_type(), cnull_type(), cnull_type()); 
  }

  template<class A, class B>
  typename sig<tuple<const non_lambda_functor, A&, B&> >::type 
  operator()(A& a, B& b) const {
    return lf.template call<typename sig<tuple<const non_lambda_functor, A&, B&> >::type >(a, b, cnull_type(), cnull_type()); 
  }

  template<class A, class B, class C>
  typename sig<tuple<const non_lambda_functor, A&, B&, C&> >::type 
  operator()(A& a, B& b, C& c) const {
    return lf.template call<typename sig<tuple<const non_lambda_functor, A&, B&, C&> >::type>(a, b, c, cnull_type()); 
  }
};

template <class Arg>
inline const Arg& unlambda(const Arg& a) { return a; }

template <class Arg>
inline const non_lambda_functor<lambda_functor<Arg> > 
unlambda(const lambda_functor<Arg>& a)
{
  return non_lambda_functor<lambda_functor<Arg> >(a);
}

  // Due to a language restriction, lambda functors cannot be made to
  // accept non-const rvalue arguments. Usually iterators do not return 
  // temporaries, but sometimes they do. That's why a workaround is provided.
  // Note, that this potentially breaks const correctness, so be careful!

// any lambda functor can be turned into a const_incorrect_lambda_functor
// The operator() takes arguments as consts and then casts constness
// away. So this breaks const correctness!!! but is a necessary workaround
// in some cases due to language limitations.
// Note, that this is not a lambda_functor anymore, so it can not be used
// as a sub lambda expression.

template <class LambdaFunctor>
struct const_incorrect_lambda_functor {
  LambdaFunctor lf;
public:

  explicit const_incorrect_lambda_functor(const LambdaFunctor& a) : lf(a) {}

  template <class SigArgs> struct sig {
    typedef typename
      LambdaFunctor::inherited::template 
        sig<typename SigArgs::tail_type>::type type;
  };

  // The nullary case is not needed (no arguments, no parameter type problems)

  template<class A>
  typename sig<tuple<const const_incorrect_lambda_functor, A&> >::type
  operator()(const A& a) const {
    return lf.template call<typename sig<tuple<const const_incorrect_lambda_functor, A&> >::type >(const_cast<A&>(a), cnull_type(), cnull_type(), cnull_type());
  }

  template<class A, class B>
  typename sig<tuple<const const_incorrect_lambda_functor, A&, B&> >::type
  operator()(const A& a, const B& b) const {
    return lf.template call<typename sig<tuple<const const_incorrect_lambda_functor, A&, B&> >::type >(const_cast<A&>(a), const_cast<B&>(b), cnull_type(), cnull_type());
  }

  template<class A, class B, class C>
  typename sig<tuple<const const_incorrect_lambda_functor, A&, B&, C&> >::type
  operator()(const A& a, const B& b, const C& c) const {
    return lf.template call<typename sig<tuple<const const_incorrect_lambda_functor, A&, B&, C&> >::type>(const_cast<A&>(a), const_cast<B&>(b), const_cast<C&>(c), cnull_type());
  }
};

// ------------------------------------------------------------------------
// any lambda functor can be turned into a const_parameter_lambda_functor
// The operator() takes arguments as const.
// This is useful if lambda functors are called with non-const rvalues.
// Note, that this is not a lambda_functor anymore, so it can not be used
// as a sub lambda expression.

template <class LambdaFunctor>
struct const_parameter_lambda_functor {
  LambdaFunctor lf;
public:

  explicit const_parameter_lambda_functor(const LambdaFunctor& a) : lf(a) {}

  template <class SigArgs> struct sig {
    typedef typename
      LambdaFunctor::inherited::template 
        sig<typename SigArgs::tail_type>::type type;
  };

  // The nullary case is not needed: no arguments, no constness problems.

  template<class A>
  typename sig<tuple<const const_parameter_lambda_functor, const A&> >::type
  operator()(const A& a) const {
    return lf.template call<typename sig<tuple<const const_parameter_lambda_functor, const A&> >::type >(a, cnull_type(), cnull_type(), cnull_type());
  }

  template<class A, class B>
  typename sig<tuple<const const_parameter_lambda_functor, const A&, const B&> >::type
  operator()(const A& a, const B& b) const {
    return lf.template call<typename sig<tuple<const const_parameter_lambda_functor, const A&, const B&> >::type >(a, b, cnull_type(), cnull_type());
  }

  template<class A, class B, class C>
  typename sig<tuple<const const_parameter_lambda_functor, const A&, const B&, const C&>
>::type
  operator()(const A& a, const B& b, const C& c) const {
    return lf.template call<typename sig<tuple<const const_parameter_lambda_functor, const A&, const B&, const C&> >::type>(a, b, c, cnull_type());
  }
};

template <class Arg>
inline const const_incorrect_lambda_functor<lambda_functor<Arg> >
break_const(const lambda_functor<Arg>& lf)
{
  return const_incorrect_lambda_functor<lambda_functor<Arg> >(lf);
}


template <class Arg>
inline const const_parameter_lambda_functor<lambda_functor<Arg> >
const_parameters(const lambda_functor<Arg>& lf)
{
  return const_parameter_lambda_functor<lambda_functor<Arg> >(lf);
}

// make void ------------------------------------------------
// make_void( x ) turns a lambda functor x with some return type y into
// another lambda functor, which has a void return type
// when called, the original return type is discarded

// we use this action. The action class will be called, which means that
// the wrapped lambda functor is evaluated, but we just don't do anything
// with the result.
struct voidifier_action {
  template<class Ret, class A> static void apply(A&) {}
};

template<class Args> struct return_type_N<voidifier_action, Args> {
  typedef void type;
};

template<class Arg1>
inline const 
lambda_functor<
  lambda_functor_base<
    action<1, voidifier_action>,
    tuple<lambda_functor<Arg1> >
  > 
> 
make_void(const lambda_functor<Arg1>& a1) { 
return 
    lambda_functor_base<
      action<1, voidifier_action>,
      tuple<lambda_functor<Arg1> >
    > 
  (tuple<lambda_functor<Arg1> > (a1));
}

// for non-lambda functors, make_void does nothing 
// (the argument gets evaluated immediately)

template<class Arg1>
inline const 
lambda_functor<
  lambda_functor_base<do_nothing_action, null_type> 
> 
make_void(const Arg1&) { 
return 
    lambda_functor_base<do_nothing_action, null_type>();
}

// std_functor -----------------------------------------------------

//  The STL uses the result_type typedef as the convention to let binders know
//  the return type of a function object. 
//  LL uses the sig template.
//  To let LL know that the function object has the result_type typedef 
//  defined, it can be wrapped with the std_functor function.


// Just inherit form the template parameter (the standard functor), 
// and provide a sig template. So we have a class which is still the
// same functor + the sig template.

template<class T>
struct result_type_to_sig : public T {
  template<class Args> struct sig { typedef typename T::result_type type; };
  result_type_to_sig(const T& t) : T(t) {}
};

template<class F>
inline result_type_to_sig<F> std_functor(const F& f) { return f; }


} // namespace lambda 
} // namespace boost

#endif








/* ret.hpp
nqseu27+OV9ZkTS046Hwe8DVD3LgvnHX3l6dLv/2Uw/88qmP1LC8l9EO3+TyH/xm2ZJ1Pf6y5XDqlF/Wz3v1nPDnyveQeK1+/rGd771167Hbu21NGRD/+eXh94yz783X8r32Wnqe/UN5osf3+JjDT5cPrc3Z+84f/rG4f/hz3z8Sew7/PLt/4V/vuHfjuOvSj8Q9cHfLz6G377XX8r0I7XsItu558EVKfrIWKB58lyrYx7h+2Lh+1Lhe2nwt7Xsj8ALQI3LNfYpBGwL79nDfpEa+Ay6nv2ejYnFxALA38FzguTwbfRhwCM8aHwosAo7mmePnA6cD84AL6X6f6y/wceAI4GrgJTxjfCTwdfLtAuYAfwUcCDxMdze8C/VeNKgHGN4uoDtAimeeOzzz/CzgBIbnCuBsnmU+n2eYL+BZ52uBPuAGuj8FLARu4/1LwEuB+3mG+kd0/7OEgfu8AN9jeIy9AWXPQodnRyfzjOi+wMPAfJ4VPZpn348BHuFZur8HFgMbuRfjn3km9WdAP/CvwK8BjwHvBv5dNcXnC55R/Q/gwzx7X9IS+te4wPi1Y/xigTvo/ys8m/9tYDzwXbrzjGbu5QJbMJ7mGc09afcMoOt+OjAN2AuYCTwD2AeYBcwB9gYOBfbh2f996U+u3mOFYyyeM5MXMz8uAcYBHzTkfBHkFlLuPsrdb8iVRJB7hHLLKPeoIeePIPdNys2j3HxDriaCXCXlqig3l3JFoFrKTXTlKD+BcmXg6wycCewFvJn53w/sC5wFvIhngvuAc1hu/Ua4FNcDd7eE6wOeIb2fZ+v/TDXLZUWQO0i5Dyn3C8rlgfI9crGgHMpV0w5fY7y+DnTlbzfTjfIJFn8fovy3Kb/UTLcIcndR7m7K1VDO515Tbijl4kAFlLuOcjcAk4A3AnsAi4E9gaXADGAJcIh7T70z9Lpo1F3U2wk0mXoTqbcLy1VX6kkCngFMBp4J7MH6uTv1pwJHAtOAY/mcZ+ZzPS/aKd6bZ+ZvYHo9DezCvWBTgBuBPbknbBbwOWA/4PPAHOD3gYOBm4F5wC3AEdwztgC4lWeFv8Q9O18GTgTu4JnhrwCnAOuAM4A7ucfo6zxDfBfw68A3uMfnbtZ3bwIXcS/ah4B7gMuAbwNXAN9hfqsOrAkGVDDeCaByxjufe4qOYj09GniapG+TXccCc7nn6VDgeNbbPiDc1GUM/+XAcuAVDL/PyO+19L+3Jb+/S7u/R7v/hGfO76P8eFAd5XtRvgNoOOVXUn4VMIF7+SYB1wDTgWuBpwOfNMptI/V1sZQDd2tSF4cDE4EXAynH9YJ2ufMoN4xy5wMD4c+l3BmW8O+h3NvABDfdgMnAHwNPA+4F9nLtZOgriaDvBerbTH1bqO8H1Pci9W019NVG0Pcq9dVR307qe436Xqe+XUCdXhH0PUl966hvPfVtoL6nqO9poE6vCHYfRH3n0u65RjiStoUPxxWUu5Lh8DEcVzEcVzMc1xj68iPoG019BdQ3hvrGUt846htv6PNH0Hc99U2mvhuo70bqK6a+EkPfygj67qO++6nvAepbRH2LqW+JoW9vBH0zqe9m6ruF+sqpbxb1zTb0qZfC67ud+u6gvjup7y7qu5v6asxyFUHfI9S3jPoepb7HqO+71Lec+opAJdQ3yNLPeIj1zMPANOB32C4sB2a4+llvPQYc4OoHDuRz5mPO1bS3v0+zvfse29+NRru9KYLcWso9Sbl1lMvjfMBw/Yz+tE820JU7GyjfwIAB+YYI8t0o353yKZRPNeTVy+HlMyl/OuV7Uf4MQz4rgnwHysdRPp7yHYG6P015m90ep91W0G5PGHbzRfD3Zcptp9wO9s8=
*/