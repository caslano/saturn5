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
B7wHOB64BXg28HngBP7W2TnA94H5wC+AE61wYKTzQNwlApoDugW0E/QtKANr1QLQWpC/tet60BbQdtAermVjsX7tBhoJmgKyr223cn0bORTpgIaAxoMKQG7QKtAmrn0PgI5yDZzOdXARqA60GbQNtBd02Gd97AatAq0H3c/18nbgEZArF/mC0kHjQaUgN2g5aK3PWvoIyDUcaYMyQLmgClAdyLPOftO21k4GpYNyQVO49l7B9fcW0HbQHp+1+Eiux6tBdaA1oA2gbaBdoL2gFVeEGfeDdoOsndwMUH5d09fg/0l3mvX/55XOKnBX1PYprK6ZdUru/2tjrf15LrmCa//B3OcdBDoC/23xMleqnle2uNCTeWEJ2KtcUO1Z1/4jSfRy3Iu0c0mmwfnRBJmzz7MCq/nRy+KfpubL78bj7r0AdfY88xmLhzjhgXNAz3kr1+z7Wa59oMhkjF1tdOVy11QEWCYrPstEXRD34uoyzfxYG7a6j113Jkf878G3LAKn7y7d2SvTsOt3VGfaz8JHi38PnW4I4url357yTxD/tzDGQ4MT9CzoJZBvfaTFBj6/tNdHjF1ng3LiWSjfQR4MF+XRy2D5UJeqjWZQ1/1xE+UHWuN6q2S8T/BTl5b+WID1KWlQRmBC1Wd7z+97i/9MczhmJg8jha9AI8xQTX3r0lpYXLGgTP2edz/xf8RMxr/LQKtBb4LamZA/6FcgTRtAutp6VHolN4h/b6x2nRKmxHqJOyntOk4/S6BOPE45UlG/1ghbBx5Xx9ZjAuTUNsmDge/t6OobZfepb76jPOz9dBX3Ms5l4tNAzVC3RYmausWlfOULywKqV8T3+V0RpKRdxzIsda4WeMLKFYJ6HS2E19cH++Rs8R+LOaRL3XWYmGTJOXD7EJ1c5a5RliPec9cR35FfL9lO52e0GzM4A3TI4kM3tpfj9tEA+0ydv3Gd5b9R/OPUXuHdJ1luu65fNzZA6y6X7sCJwEnWnld9O1HFyC+kPgj7gbqrln3wmIRvb2r3tBJ97y2tLSuxZA0WN2E/6Eh9vTpuNIcZR80Itf/0kbxvpd/rsrctg2kWSmWpO8vMJLFvcHjSOypxojRtT88jdrXUntYn4j/Kofke6HhBXGFGqx/I8OxD3N8g3+vBdwvhu4/iO1yeEyWtBFtaCd5pMe8qK19VL0nJcg+Y0i/7Sp4HSlrJtrSSfcoxw4pstRc2YM/+4wXCyxtmS3sY297MOPH/UPzdNh1hz/2P7cS/o4P+Vvw5CyrnqXvwuot/nEPSl/F2eB+OF3KPnjdv7vnVTHsD/KZI3I9N1oPELbSNNxsZ/7xoGceLSwqlz6u7K+MkfncH4zMM2xTr4oZk6gWy7abIc3tzlnG+yPs6VPB9MRgT4o5TN1AS+t9CBFgB6oHnRepv+zu+J16Edpgep0jdn1yq2+/U/s5SSDTqm/YWx8cC9F91t7L3Hb/sl/b73lS/4nxChZX+IWFjVVjV7iVsghpb0b4ZP1mFrfKEk3qdYfHEukaaUlcSjnXoeb9JvVd1wzuJqUtKve6rzXqd/58ArfFsbzvv8ay4YrbvWKa++4ck7EIz3sjWjWdISzueqTZS1F50Q7Xjlj0uxwqrECpuM4kbrRujEFc/RmnGJIRt2piE8NoxSem7C19Oc7CBtSlIMxYhDe1YpOblrSSNHmZvSHElUtCNQUzD+6yMc8ZfSPzVHh7hpP8rndep4r/POBMruB7oj82s/al4tFd4JtPm65po+RtzcCH8HfgZwgn6jfc9iVKvp6fPePaSpzuavjfc1L3ndyKt978675LpB0NX33X5ptZ7d959/XP+9lD97w1/Va87md384XFfb1q3MeU=
*/