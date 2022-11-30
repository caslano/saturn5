/*=============================================================================
    Phoenix V1.2.1
    Copyright (c) 2001-2002 Joel de Guzman

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_SPIRIT_CLASSIC_PHOENIX_STATEMENTS_HPP
#define BOOST_SPIRIT_CLASSIC_PHOENIX_STATEMENTS_HPP

///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/classic/phoenix/composite.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace phoenix {

///////////////////////////////////////////////////////////////////////////////
//
//  sequential_composite
//
//      Two or more actors separated by the comma generates a
//      sequential_composite which is a composite actor. Example:
//
//          actor,
//          actor,
//          actor
//
//      The actors are evaluated sequentially. The result type of this
//      is void. Note that the last actor should not have a trailing
//      comma.
//
///////////////////////////////////////////////////////////////////////////////
template <typename A0, typename A1>
struct sequential_composite {

    typedef sequential_composite<A0, A1> self_t;

    template <typename TupleT>
    struct result { typedef void type; };

    sequential_composite(A0 const& _0, A1 const& _1)
    :   a0(_0), a1(_1) {}

    template <typename TupleT>
    void
    eval(TupleT const& args) const
    {
        a0.eval(args);
        a1.eval(args);
    }

    A0 a0; A1 a1; //  actors
};

//////////////////////////////////
template <typename BaseT0, typename BaseT1>
inline actor<sequential_composite<actor<BaseT0>, actor<BaseT1> > >
operator,(actor<BaseT0> const& _0, actor<BaseT1> const& _1)
{
    return sequential_composite<actor<BaseT0>, actor<BaseT1> >(_0, _1);
}

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
//      where condition is an actor that evaluates to bool. If condition
//      is true, the true_statement (again an actor) is executed
//      otherwise, the false_statement (another actor) is executed. The
//      result type of this is void. Note the trailing underscore after
//      if_ and the leading dot and the trailing underscore before
//      and after .else_.
//
///////////////////////////////////////////////////////////////////////////////
template <typename CondT, typename ThenT, typename ElseT>
struct if_then_else_composite {

    typedef if_then_else_composite<CondT, ThenT, ElseT> self_t;

    template <typename TupleT>
    struct result {

        typedef void type;
    };

    if_then_else_composite(
        CondT const& cond_,
        ThenT const& then_,
        ElseT const& else__)
    :   cond(cond_), then(then_), else_(else__) {}

    template <typename TupleT>
    void eval(TupleT const& args) const
    {
        if (cond.eval(args))
            then.eval(args);
        else
            else_.eval(args);
    }

    CondT cond; ThenT then; ElseT else_; //  actors
};

//////////////////////////////////
template <typename CondT, typename ThenT>
struct else_gen {

    else_gen(CondT const& cond_, ThenT const& then_)
    :   cond(cond_), then(then_) {}

    template <typename ElseT>
    actor<if_then_else_composite<CondT, ThenT,
        typename as_actor<ElseT>::type> >
    operator[](ElseT const& else_)
    {
        typedef if_then_else_composite<CondT, ThenT,
            typename as_actor<ElseT>::type>
        result;

        return result(cond, then, as_actor<ElseT>::convert(else_));
    }

    CondT cond; ThenT then;
};

//////////////////////////////////
template <typename CondT, typename ThenT>
struct if_then_composite {

    typedef if_then_composite<CondT, ThenT> self_t;

    template <typename TupleT>
    struct result { typedef void type; };

    if_then_composite(CondT const& cond_, ThenT const& then_)
    :   cond(cond_), then(then_), else_(cond, then) {}

    template <typename TupleT>
    void eval(TupleT const& args) const
    {
        if (cond.eval(args))
            then.eval(args);
    }

    CondT cond; ThenT then; //  actors
    else_gen<CondT, ThenT> else_;
};

//////////////////////////////////
template <typename CondT>
struct if_gen {

    if_gen(CondT const& cond_)
    :   cond(cond_) {}

    template <typename ThenT>
    actor<if_then_composite<
        typename as_actor<CondT>::type,
        typename as_actor<ThenT>::type> >
    operator[](ThenT const& then) const
    {
        typedef if_then_composite<
            typename as_actor<CondT>::type,
            typename as_actor<ThenT>::type>
        result;

        return result(
            as_actor<CondT>::convert(cond),
            as_actor<ThenT>::convert(then));
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

///////////////////////////////////////////////////////////////////////////////
//
//  while_composite
//
//      This composite has the form:
//
//          while_(condition)
//          [
//              statement
//          ]
//
//      While the condition (an actor) evaluates to true, statement
//      (another actor) is executed. The result type of this is void.
//      Note the trailing underscore after while_.
//
///////////////////////////////////////////////////////////////////////////////
template <typename CondT, typename DoT>
struct while_composite {

    typedef while_composite<CondT, DoT> self_t;

    template <typename TupleT>
    struct result { typedef void type; };

    while_composite(CondT const& cond_, DoT const& do__)
    :   cond(cond_), do_(do__) {}

    template <typename TupleT>
    void eval(TupleT const& args) const
    {
        while (cond.eval(args))
            do_.eval(args);
    }

    CondT cond;
    DoT do_;
};

//////////////////////////////////
template <typename CondT>
struct while_gen {

    while_gen(CondT const& cond_)
    :   cond(cond_) {}

    template <typename DoT>
    actor<while_composite<
        typename as_actor<CondT>::type,
        typename as_actor<DoT>::type> >
    operator[](DoT const& do_) const
    {
        typedef while_composite<
            typename as_actor<CondT>::type,
            typename as_actor<DoT>::type>
        result;

        return result(
            as_actor<CondT>::convert(cond),
            as_actor<DoT>::convert(do_));
    }

    CondT cond;
};

//////////////////////////////////
template <typename CondT>
inline while_gen<CondT>
while_(CondT const& cond)
{
    return while_gen<CondT>(cond);
}

///////////////////////////////////////////////////////////////////////////////
//
//  do_composite
//
//      This composite has the form:
//
//          do_
//          [
//              statement
//          ]
//          .while_(condition)
//
//      While the condition (an actor) evaluates to true, statement
//      (another actor) is executed. The statement is executed at least
//      once. The result type of this is void. Note the trailing
//      underscore after do_ and the leading dot and the trailing
//      underscore before and after .while_.
//
///////////////////////////////////////////////////////////////////////////////
template <typename DoT, typename CondT>
struct do_composite {

    typedef do_composite<DoT, CondT> self_t;

    template <typename TupleT>
    struct result { typedef void type; };

    do_composite(DoT const& do__, CondT const& cond_)
    :   do_(do__), cond(cond_) {}

    template <typename TupleT>
    void eval(TupleT const& args) const
    {
        do
            do_.eval(args);
        while (cond.eval(args));
    }

    DoT do_;
    CondT cond;
};

////////////////////////////////////
template <typename DoT>
struct do_gen2 {

    do_gen2(DoT const& do__)
    :   do_(do__) {}

    template <typename CondT>
    actor<do_composite<
        typename as_actor<DoT>::type,
        typename as_actor<CondT>::type> >
    while_(CondT const& cond) const
    {
        typedef do_composite<
            typename as_actor<DoT>::type,
            typename as_actor<CondT>::type>
        result;

        return result(
            as_actor<DoT>::convert(do_),
            as_actor<CondT>::convert(cond));
    }

    DoT do_;
};

////////////////////////////////////
struct do_gen {

    template <typename DoT>
    do_gen2<DoT>
    operator[](DoT const& do_) const
    {
        return do_gen2<DoT>(do_);
    }
};

do_gen const do_ = do_gen();

///////////////////////////////////////////////////////////////////////////////
//
//  for_composite
//
//      This statement has the form:
//
//          for_(init, condition, step)
//          [
//              statement
//          ]
//
//      Where init, condition, step and statement are all actors. init
//      is executed once before entering the for-loop. The for-loop
//      exits once condition evaluates to false. At each loop iteration,
//      step and statement is called. The result of this statement is
//      void. Note the trailing underscore after for_.
//
///////////////////////////////////////////////////////////////////////////////
template <typename InitT, typename CondT, typename StepT, typename DoT>
struct for_composite {

    typedef composite<InitT, CondT, StepT, DoT> self_t;

    template <typename TupleT>
    struct result { typedef void type; };

    for_composite(
        InitT const& init_,
        CondT const& cond_,
        StepT const& step_,
        DoT const& do__)
    :   init(init_), cond(cond_), step(step_), do_(do__) {}

    template <typename TupleT>
    void
    eval(TupleT const& args) const
    {
        for (init.eval(args); cond.eval(args); step.eval(args))
            do_.eval(args);
    }

    InitT init; CondT cond; StepT step; DoT do_; //  actors
};

//////////////////////////////////
template <typename InitT, typename CondT, typename StepT>
struct for_gen {

    for_gen(
        InitT const& init_,
        CondT const& cond_,
        StepT const& step_)
    :   init(init_), cond(cond_), step(step_) {}

    template <typename DoT>
    actor<for_composite<
        typename as_actor<InitT>::type,
        typename as_actor<CondT>::type,
        typename as_actor<StepT>::type,
        typename as_actor<DoT>::type> >
    operator[](DoT const& do_) const
    {
        typedef for_composite<
            typename as_actor<InitT>::type,
            typename as_actor<CondT>::type,
            typename as_actor<StepT>::type,
            typename as_actor<DoT>::type>
        result;

        return result(
            as_actor<InitT>::convert(init),
            as_actor<CondT>::convert(cond),
            as_actor<StepT>::convert(step),
            as_actor<DoT>::convert(do_));
    }

    InitT init; CondT cond; StepT step;
};

//////////////////////////////////
template <typename InitT, typename CondT, typename StepT>
inline for_gen<InitT, CondT, StepT>
for_(InitT const& init, CondT const& cond, StepT const& step)
{
    return for_gen<InitT, CondT, StepT>(init, cond, step);
}

}   //  namespace phoenix

#endif

/* statements.hpp
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
*/