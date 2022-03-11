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