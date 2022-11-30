// Boost Lambda Library -- if.hpp ------------------------------------------

// Copyright (C) 1999, 2000 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
// Copyright (C) 2000 Gary Powell (powellg@amazon.com)
// Copyright (C) 2001-2002 Joel de Guzman
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org

// --------------------------------------------------------------------------

#if !defined(BOOST_LAMBDA_IF_HPP)
#define BOOST_LAMBDA_IF_HPP

#include "boost/lambda/core.hpp"

// Arithmetic type promotion needed for if_then_else_return
#include "boost/lambda/detail/operator_actions.hpp"
#include "boost/lambda/detail/operator_return_type_traits.hpp"

namespace boost { 
namespace lambda {

// -- if control construct actions ----------------------

class ifthen_action {};
class ifthenelse_action {};
class ifthenelsereturn_action {};

// Specialization for if_then.
template<class Args>
class 
lambda_functor_base<ifthen_action, Args> {
public:
  Args args;
  template <class T> struct sig { typedef void type; };
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template<class RET, CALL_TEMPLATE_ARGS>
  RET call(CALL_FORMAL_ARGS) const {
    if (detail::select(boost::tuples::get<0>(args), CALL_ACTUAL_ARGS)) 
      detail::select(boost::tuples::get<1>(args), CALL_ACTUAL_ARGS); 
  }
};

// If Then
template <class Arg1, class Arg2>
inline const 
lambda_functor<
  lambda_functor_base<
    ifthen_action, 
    tuple<lambda_functor<Arg1>, lambda_functor<Arg2> >
  > 
>
if_then(const lambda_functor<Arg1>& a1, const lambda_functor<Arg2>& a2) {
  return 
    lambda_functor_base<
      ifthen_action, 
      tuple<lambda_functor<Arg1>, lambda_functor<Arg2> > 
    > 
    ( tuple<lambda_functor<Arg1>, lambda_functor<Arg2> >(a1, a2) );
}


// Specialization for if_then_else.
template<class Args>
class 
lambda_functor_base<ifthenelse_action, Args> {
public:
  Args args;
  template <class T> struct sig { typedef void type; };
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template<class RET, CALL_TEMPLATE_ARGS>
  RET call(CALL_FORMAL_ARGS) const {
    if (detail::select(boost::tuples::get<0>(args), CALL_ACTUAL_ARGS)) 
      detail::select(boost::tuples::get<1>(args), CALL_ACTUAL_ARGS); 
    else 
      detail::select(boost::tuples::get<2>(args), CALL_ACTUAL_ARGS);
  }
};



// If then else

template <class Arg1, class Arg2, class Arg3>
inline const 
lambda_functor<
  lambda_functor_base<
    ifthenelse_action, 
    tuple<lambda_functor<Arg1>, lambda_functor<Arg2>, lambda_functor<Arg3> >
  > 
>
if_then_else(const lambda_functor<Arg1>& a1, const lambda_functor<Arg2>& a2, 
             const lambda_functor<Arg3>& a3) {
  return 
    lambda_functor_base<
      ifthenelse_action, 
      tuple<lambda_functor<Arg1>, lambda_functor<Arg2>, lambda_functor<Arg3> >
    > 
    (tuple<lambda_functor<Arg1>, lambda_functor<Arg2>, lambda_functor<Arg3> >
       (a1, a2, a3) );
}

// Our version of operator?:()

template <class Arg1, class Arg2, class Arg3>
inline const 
  lambda_functor<
    lambda_functor_base<
      other_action<ifthenelsereturn_action>, 
      tuple<lambda_functor<Arg1>,
          typename const_copy_argument<Arg2>::type,
          typename const_copy_argument<Arg3>::type>
  > 
>
if_then_else_return(const lambda_functor<Arg1>& a1, 
                    const Arg2 & a2, 
                    const Arg3 & a3) {
  return 
      lambda_functor_base<
        other_action<ifthenelsereturn_action>, 
        tuple<lambda_functor<Arg1>,
              typename const_copy_argument<Arg2>::type,
              typename const_copy_argument<Arg3>::type>
      > ( tuple<lambda_functor<Arg1>,
              typename const_copy_argument<Arg2>::type,
              typename const_copy_argument<Arg3>::type> (a1, a2, a3) );
}

namespace detail {

// return type specialization for conditional expression begins -----------
// start reading below and move upwards

// PHASE 6:1 
// check if A is conbertible to B and B to A
template<int Phase, bool AtoB, bool BtoA, bool SameType, class A, class B>
struct return_type_2_ifthenelsereturn;

// if A can be converted to B and vice versa -> ambiguous
template<int Phase, class A, class B>
struct return_type_2_ifthenelsereturn<Phase, true, true, false, A, B> {
  typedef 
    detail::return_type_deduction_failure<return_type_2_ifthenelsereturn> type;
  // ambiguous type in conditional expression
};
// if A can be converted to B and vice versa and are of same type
template<int Phase, class A, class B>
struct return_type_2_ifthenelsereturn<Phase, true, true, true, A, B> {
  typedef A type;
};


// A can be converted to B
template<int Phase, class A, class B>
struct return_type_2_ifthenelsereturn<Phase, true, false, false, A, B> {
  typedef B type;
};

// B can be converted to A
template<int Phase, class A, class B>
struct return_type_2_ifthenelsereturn<Phase, false, true, false, A, B> {
  typedef A type;
};

// neither can be converted. Then we drop the potential references, and
// try again
template<class A, class B>
struct return_type_2_ifthenelsereturn<1, false, false, false, A, B> {
  // it is safe to add const, since the result will be an rvalue and thus
  // const anyway. The const are needed eg. if the types 
  // are 'const int*' and 'void *'. The remaining type should be 'const void*'
  typedef const typename boost::remove_reference<A>::type plainA; 
  typedef const typename boost::remove_reference<B>::type plainB; 
  // TODO: Add support for volatile ?

  typedef typename
       return_type_2_ifthenelsereturn<
         2,
         boost::is_convertible<plainA,plainB>::value, 
         boost::is_convertible<plainB,plainA>::value,
         boost::is_same<plainA,plainB>::value,
         plainA, 
         plainB>::type type;
};

// PHASE 6:2
template<class A, class B>
struct return_type_2_ifthenelsereturn<2, false, false, false, A, B> {
  typedef 
    detail::return_type_deduction_failure<return_type_2_ifthenelsereturn> type;
  // types_do_not_match_in_conditional_expression 
};



// PHASE 5: now we know that types are not arithmetic.
template<class A, class B>
struct non_numeric_types {
  typedef typename 
    return_type_2_ifthenelsereturn<
      1, // phase 1 
      is_convertible<A,B>::value, 
      is_convertible<B,A>::value, 
      is_same<A,B>::value,
      A, 
      B>::type type;
};

// PHASE 4 : 
// the base case covers arithmetic types with differing promote codes
// use the type deduction of arithmetic_actions
template<int CodeA, int CodeB, class A, class B>
struct arithmetic_or_not {
  typedef typename
    return_type_2<arithmetic_action<plus_action>, A, B>::type type; 
  // plus_action is just a random pick, has to be a concrete instance
};

// this case covers the case of artihmetic types with the same promote codes. 
// non numeric deduction is used since e.g. integral promotion is not 
// performed with operator ?: 
template<int CodeA, class A, class B>
struct arithmetic_or_not<CodeA, CodeA, A, B> {
  typedef typename non_numeric_types<A, B>::type type; 
};

// if either A or B has promote code -1 it is not an arithmetic type
template<class A, class B>
struct arithmetic_or_not <-1, -1, A, B> {
  typedef typename non_numeric_types<A, B>::type type;
};
template<int CodeB, class A, class B>
struct arithmetic_or_not <-1, CodeB, A, B> {
  typedef typename non_numeric_types<A, B>::type type;
};
template<int CodeA, class A, class B>
struct arithmetic_or_not <CodeA, -1, A, B> {
  typedef typename non_numeric_types<A, B>::type type;
};




// PHASE 3 : Are the types same?
// No, check if they are arithmetic or not
template <class A, class B>
struct same_or_not {
  typedef typename detail::remove_reference_and_cv<A>::type plainA;
  typedef typename detail::remove_reference_and_cv<B>::type plainB;

  typedef typename 
    arithmetic_or_not<
      detail::promote_code<plainA>::value, 
      detail::promote_code<plainB>::value, 
      A, 
      B>::type type;
};
// Yes, clear.
template <class A> struct same_or_not<A, A> {
  typedef A type;
};

} // detail

// PHASE 2 : Perform first the potential array_to_pointer conversion 
template<class A, class B>
struct return_type_2<other_action<ifthenelsereturn_action>, A, B> { 

  typedef typename detail::array_to_pointer<A>::type A1;
  typedef typename detail::array_to_pointer<B>::type B1;

  typedef typename 
    boost::add_const<typename detail::same_or_not<A1, B1>::type>::type type;
};

// PHASE 1 : Deduction is based on the second and third operand


// return type specialization for conditional expression ends -----------


// Specialization of lambda_functor_base for if_then_else_return.
template<class Args>
class 
lambda_functor_base<other_action<ifthenelsereturn_action>, Args> {
public:
  Args args;

  template <class SigArgs> struct sig {
  private:
    typedef typename detail::nth_return_type_sig<1, Args, SigArgs>::type ret1;
    typedef typename detail::nth_return_type_sig<2, Args, SigArgs>::type ret2;
  public:
    typedef typename return_type_2<
      other_action<ifthenelsereturn_action>, ret1, ret2
    >::type type;
  };

public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template<class RET, CALL_TEMPLATE_ARGS>
  RET call(CALL_FORMAL_ARGS) const {
    return (detail::select(boost::tuples::get<0>(args), CALL_ACTUAL_ARGS)) ?
       detail::select(boost::tuples::get<1>(args), CALL_ACTUAL_ARGS) 
    : 
       detail::select(boost::tuples::get<2>(args), CALL_ACTUAL_ARGS);
  }
};

  // The code below is from Joel de Guzman, some name changes etc. 
  // has been made.

///////////////////////////////////////////////////////////////////////////////
//
//  if_then_else_composite
//
//      This composite has two (2) forms:
//
//          if_(condition)
//          [
//              statement
//          ]
//
//      and
//
//          if_(condition)
//          [
//              true_statement
//          ]
//          .else_
//          [
//              false_statement
//          ]
//
//      where condition is an lambda_functor that evaluates to bool. If condition
//      is true, the true_statement (again an lambda_functor) is executed
//      otherwise, the false_statement (another lambda_functor) is executed. The
//      result type of this is void. Note the trailing underscore after
//      if_ and the leading dot and the trailing underscore before
//      and after .else_.
//
///////////////////////////////////////////////////////////////////////////////
template <typename CondT, typename ThenT, typename ElseT>
struct if_then_else_composite {

    typedef if_then_else_composite<CondT, ThenT, ElseT> self_t;

    template <class SigArgs>
    struct sig { typedef void type; };

    if_then_else_composite(
        CondT const& cond_,
        ThenT const& then_,
        ElseT const& else__)
    :   cond(cond_), then(then_), else_(else__) {}

    template <class Ret, CALL_TEMPLATE_ARGS>
    Ret call(CALL_FORMAL_ARGS) const
    {
        if (cond.internal_call(CALL_ACTUAL_ARGS))
            then.internal_call(CALL_ACTUAL_ARGS);
        else
            else_.internal_call(CALL_ACTUAL_ARGS);
    }

    CondT cond; ThenT then; ElseT else_; //  lambda_functors
};

//////////////////////////////////
template <typename CondT, typename ThenT>
struct else_gen {

    else_gen(CondT const& cond_, ThenT const& then_)
    :   cond(cond_), then(then_) {}

    template <typename ElseT>
    lambda_functor<if_then_else_composite<CondT, ThenT,
        typename as_lambda_functor<ElseT>::type> >
    operator[](ElseT const& else_)
    {
        typedef if_then_else_composite<CondT, ThenT,
            typename as_lambda_functor<ElseT>::type>
        result;

        return result(cond, then, to_lambda_functor(else_));
    }

    CondT cond; ThenT then;
};

//////////////////////////////////
template <typename CondT, typename ThenT>
struct if_then_composite {

    template <class SigArgs>
    struct sig { typedef void type; };

    if_then_composite(CondT const& cond_, ThenT const& then_)
    :   cond(cond_), then(then_), else_(cond, then) {}

    template <class Ret, CALL_TEMPLATE_ARGS>
    Ret call(CALL_FORMAL_ARGS) const
    {
      if (cond.internal_call(CALL_ACTUAL_ARGS))
            then.internal_call(CALL_ACTUAL_ARGS);
    }

    CondT cond; ThenT then; //  lambda_functors
    else_gen<CondT, ThenT> else_;
};

//////////////////////////////////
template <typename CondT>
struct if_gen {

    if_gen(CondT const& cond_)
    :   cond(cond_) {}

    template <typename ThenT>
    lambda_functor<if_then_composite<
        typename as_lambda_functor<CondT>::type,
        typename as_lambda_functor<ThenT>::type> >
    operator[](ThenT const& then) const
    {
        typedef if_then_composite<
            typename as_lambda_functor<CondT>::type,
            typename as_lambda_functor<ThenT>::type>
        result;

        return result(
            to_lambda_functor(cond),
            to_lambda_functor(then));
    }

    CondT cond;
};

//////////////////////////////////
template <typename CondT>
inline if_gen<CondT>
if_(CondT const& cond)
{
    return if_gen<CondT>(cond);
}



} // lambda
} // boost

#endif // BOOST_LAMBDA_IF_HPP



/* if.hpp
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
*/