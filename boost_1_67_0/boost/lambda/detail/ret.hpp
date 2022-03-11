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