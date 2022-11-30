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
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
*/