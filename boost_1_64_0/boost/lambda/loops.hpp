// Boost Lambda Library -- loops.hpp ----------------------------------------

// Copyright (C) 1999, 2000 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
// Copyright (C) 2000 Gary Powell (powellg@amazon.com)
// Copyright (c) 2001-2002 Joel de Guzman
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org

// --------------------------------------------------------------------------

#if !defined(BOOST_LAMBDA_LOOPS_HPP)
#define BOOST_LAMBDA_LOOPS_HPP

#include "boost/lambda/core.hpp"

namespace boost { 
namespace lambda {

// -- loop control structure actions ----------------------

class forloop_action {};
class forloop_no_body_action {};
class whileloop_action {};
class whileloop_no_body_action {};
class dowhileloop_action {};
class dowhileloop_no_body_action {};


// For loop
template <class Arg1, class Arg2, class Arg3, class Arg4>
inline const 
lambda_functor<
  lambda_functor_base<
    forloop_action, 
    tuple<lambda_functor<Arg1>, lambda_functor<Arg2>, 
          lambda_functor<Arg3>, lambda_functor<Arg4> >
  > 
>
for_loop(const lambda_functor<Arg1>& a1, const lambda_functor<Arg2>& a2, 
         const lambda_functor<Arg3>& a3, const lambda_functor<Arg4>& a4) { 
  return 
      lambda_functor_base<
        forloop_action, 
        tuple<lambda_functor<Arg1>, lambda_functor<Arg2>, 
              lambda_functor<Arg3>, lambda_functor<Arg4> >
      > 
    ( tuple<lambda_functor<Arg1>, lambda_functor<Arg2>, 
            lambda_functor<Arg3>, lambda_functor<Arg4> >(a1, a2, a3, a4)
    );
}

// No body case.
template <class Arg1, class Arg2, class Arg3>
inline const 
lambda_functor<
  lambda_functor_base<
    forloop_no_body_action, 
    tuple<lambda_functor<Arg1>, lambda_functor<Arg2>, lambda_functor<Arg3> >
  > 
>
for_loop(const lambda_functor<Arg1>& a1, const lambda_functor<Arg2>& a2, 
         const lambda_functor<Arg3>& a3) { 
  return 
      lambda_functor_base<
        forloop_no_body_action, 
        tuple<lambda_functor<Arg1>, lambda_functor<Arg2>, 
              lambda_functor<Arg3> >
      > 
      ( tuple<lambda_functor<Arg1>, lambda_functor<Arg2>, 
               lambda_functor<Arg3> >(a1, a2, a3) );
}

// While loop
template <class Arg1, class Arg2>
inline const 
lambda_functor<
  lambda_functor_base<
    whileloop_action, 
    tuple<lambda_functor<Arg1>, lambda_functor<Arg2> >
  > 
>
while_loop(const lambda_functor<Arg1>& a1, const lambda_functor<Arg2>& a2) { 
  return 
      lambda_functor_base<
        whileloop_action, 
        tuple<lambda_functor<Arg1>, lambda_functor<Arg2> >
      > 
      ( tuple<lambda_functor<Arg1>, lambda_functor<Arg2> >(a1, a2));
}

// No body case.
template <class Arg1>
inline const 
lambda_functor<
  lambda_functor_base<
    whileloop_no_body_action, 
    tuple<lambda_functor<Arg1> >
  > 
>
while_loop(const lambda_functor<Arg1>& a1) { 
  return 
      lambda_functor_base<
        whileloop_no_body_action, 
        tuple<lambda_functor<Arg1> >
      > 
      ( tuple<lambda_functor<Arg1> >(a1) );
}


// Do While loop
template <class Arg1, class Arg2>
inline const 
lambda_functor<
  lambda_functor_base<
    dowhileloop_action, 
    tuple<lambda_functor<Arg1>, lambda_functor<Arg2> >
  > 
>
do_while_loop(const lambda_functor<Arg1>& a1, const lambda_functor<Arg2>& a2) {
  return 
      lambda_functor_base<
        dowhileloop_action, 
        tuple<lambda_functor<Arg1>, lambda_functor<Arg2> >
      > 
      ( tuple<lambda_functor<Arg1>, lambda_functor<Arg2> >(a1, a2));
}

// No body case.
template <class Arg1>
inline const 
lambda_functor<
  lambda_functor_base<
    dowhileloop_no_body_action, 
    tuple<lambda_functor<Arg1> >
  > 
>
do_while_loop(const lambda_functor<Arg1>& a1) { 
  return 
      lambda_functor_base<
        dowhileloop_no_body_action, 
        tuple<lambda_functor<Arg1> >
      > 
      ( tuple<lambda_functor<Arg1> >(a1));
}


// Control loop lambda_functor_base specializations.

// Specialization for for_loop.
template<class Args>
class 
lambda_functor_base<forloop_action, Args> {
public:
  Args args;
  template <class T> struct sig { typedef void type; };
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template<class RET, CALL_TEMPLATE_ARGS>
  RET call(CALL_FORMAL_ARGS) const {
    for(detail::select(boost::tuples::get<0>(args), CALL_ACTUAL_ARGS); 
        detail::select(boost::tuples::get<1>(args), CALL_ACTUAL_ARGS); 
        detail::select(boost::tuples::get<2>(args), CALL_ACTUAL_ARGS))
      
      detail::select(boost::tuples::get<3>(args), CALL_ACTUAL_ARGS);
  }
};

// No body case
template<class Args>
class 
lambda_functor_base<forloop_no_body_action, Args> {
public:
  Args args;
  template <class T> struct sig { typedef void type; };
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template<class RET, CALL_TEMPLATE_ARGS>
  RET call(CALL_FORMAL_ARGS) const {
    for(detail::select(boost::tuples::get<0>(args), CALL_ACTUAL_ARGS); 
        detail::select(boost::tuples::get<1>(args), CALL_ACTUAL_ARGS); 
        detail::select(boost::tuples::get<2>(args), CALL_ACTUAL_ARGS)) {}
   }
};


// Specialization for while_loop.
template<class Args>
class 
lambda_functor_base<whileloop_action, Args> {
public:
  Args args;
  template <class T> struct sig { typedef void type; };
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template<class RET, CALL_TEMPLATE_ARGS>
  RET call(CALL_FORMAL_ARGS) const {
    while(detail::select(boost::tuples::get<0>(args), CALL_ACTUAL_ARGS))
      
      detail::select(boost::tuples::get<1>(args), CALL_ACTUAL_ARGS);
  }
};

// No body case
template<class Args> 
class 
lambda_functor_base<whileloop_no_body_action, Args> {
public:
  Args args;
  template <class T> struct sig { typedef void type; };
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template<class RET, CALL_TEMPLATE_ARGS>
  RET call(CALL_FORMAL_ARGS) const {
          while(detail::select(boost::tuples::get<0>(args), CALL_ACTUAL_ARGS)) {}
  }
};

// Specialization for do_while_loop.
// Note that the first argument is the condition.
template<class Args>
class 
lambda_functor_base<dowhileloop_action, Args> {
public:
  Args args;
  template <class T> struct sig { typedef void type; };
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template<class RET, CALL_TEMPLATE_ARGS>
  RET call(CALL_FORMAL_ARGS) const {
    do {
      detail::select(boost::tuples::get<1>(args), CALL_ACTUAL_ARGS);      
    } while (detail::select(boost::tuples::get<0>(args), CALL_ACTUAL_ARGS) );
  }
};

// No body case
template<class Args>
class 
lambda_functor_base<dowhileloop_no_body_action, Args> {
public:
  Args args;
  template <class T> struct sig { typedef void type; };
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template<class RET, CALL_TEMPLATE_ARGS>
  RET call(CALL_FORMAL_ARGS) const {
          do {} while (detail::select(boost::tuples::get<0>(args), CALL_ACTUAL_ARGS) );
  }
};

  // The code below is from Joel de Guzman, some name changes etc. 
  // has been made.

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
//      While the condition (an lambda_functor) evaluates to true, statement
//      (another lambda_functor) is executed. The result type of this is void.
//      Note the trailing underscore after while_.
//
///////////////////////////////////////////////////////////////////////////////
template <typename CondT, typename DoT>
struct while_composite {

    typedef while_composite<CondT, DoT> self_t;

    template <class SigArgs>
    struct sig { typedef void type; };

    while_composite(CondT const& cond_, DoT const& do__)
    :   cond(cond_), do_(do__) {}

    template <class Ret, CALL_TEMPLATE_ARGS>
    Ret call(CALL_FORMAL_ARGS) const
    {
        while (cond.internal_call(CALL_ACTUAL_ARGS))
            do_.internal_call(CALL_ACTUAL_ARGS);
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
    lambda_functor<while_composite<
        typename as_lambda_functor<CondT>::type,
        typename as_lambda_functor<DoT>::type> >
    operator[](DoT const& do_) const
    {
        typedef while_composite<
            typename as_lambda_functor<CondT>::type,
            typename as_lambda_functor<DoT>::type>
        result;

        return result(
            to_lambda_functor(cond),
            to_lambda_functor(do_));
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
//      While the condition (an lambda_functor) evaluates to true, statement
//      (another lambda_functor) is executed. The statement is executed at least
//      once. The result type of this is void. Note the trailing
//      underscore after do_ and the leading dot and the trailing
//      underscore before and after .while_.
//
///////////////////////////////////////////////////////////////////////////////
template <typename DoT, typename CondT>
struct do_composite {

    typedef do_composite<DoT, CondT> self_t;

    template <class SigArgs>
    struct sig { typedef void type; };

    do_composite(DoT const& do__, CondT const& cond_)
    :   do_(do__), cond(cond_) {}

    template <class Ret, CALL_TEMPLATE_ARGS>
    Ret call(CALL_FORMAL_ARGS) const
    {
        do
            do_.internal_call(CALL_ACTUAL_ARGS);
        while (cond.internal_call(CALL_ACTUAL_ARGS));
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
    lambda_functor<do_composite<
        typename as_lambda_functor<DoT>::type,
        typename as_lambda_functor<CondT>::type> >
    while_(CondT const& cond) const
    {
        typedef do_composite<
            typename as_lambda_functor<DoT>::type,
            typename as_lambda_functor<CondT>::type>
        result;

        return result(
            to_lambda_functor(do_),
            to_lambda_functor(cond));
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
//      Where init, condition, step and statement are all lambda_functors. init
//      is executed once before entering the for-loop. The for-loop
//      exits once condition evaluates to false. At each loop iteration,
//      step and statement is called. The result of this statement is
//      void. Note the trailing underscore after for_.
//
///////////////////////////////////////////////////////////////////////////////
template <typename InitT, typename CondT, typename StepT, typename DoT>
struct for_composite {

    template <class SigArgs>
    struct sig { typedef void type; };

    for_composite(
        InitT const& init_,
        CondT const& cond_,
        StepT const& step_,
        DoT const& do__)
    :   init(init_), cond(cond_), step(step_), do_(do__) {}

    template <class Ret, CALL_TEMPLATE_ARGS>
    Ret
    call(CALL_FORMAL_ARGS) const
    {
        for (init.internal_call(CALL_ACTUAL_ARGS); cond.internal_call(CALL_ACTUAL_ARGS); step.internal_call(CALL_ACTUAL_ARGS))
            do_.internal_call(CALL_ACTUAL_ARGS);
    }

    InitT init; CondT cond; StepT step; DoT do_; //  lambda_functors
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
    lambda_functor<for_composite<
        typename as_lambda_functor<InitT>::type,
        typename as_lambda_functor<CondT>::type,
        typename as_lambda_functor<StepT>::type,
        typename as_lambda_functor<DoT>::type> >
    operator[](DoT const& do_) const
    {
        typedef for_composite<
            typename as_lambda_functor<InitT>::type,
            typename as_lambda_functor<CondT>::type,
            typename as_lambda_functor<StepT>::type,
            typename as_lambda_functor<DoT>::type>
        result;

        return result(
            to_lambda_functor(init),
            to_lambda_functor(cond),
            to_lambda_functor(step),
            to_lambda_functor(do_));
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

} // lambda
} // boost

#endif // BOOST_LAMBDA_LOOPS_HPP

/* loops.hpp
avsz02LdMy2WV9N/EV7bh5Qu9Z563lXebzBvTX9mWtr+pOu/CK/tT0ov92PxX6by/oB5a/oy09L1LU1fZnjfvlW28HjfUnqItt9BcMbKfYnIL8rWt0rLZzOfeI4DX0jaFaY1Zo81o7x1GtkmCiWt9/hsGufEWc+t7elWVZZxHGb+rSSMS93x/47kc6U5CPE6mylGkRmt9JM/Eb8rRB/752KwMAeKs8fvIO0r+aebzc0YW54lVdXsdOruiFjeHco8HXHHf//l49YSx11DGd+DfHthTGlOfeh/IqNvScds9B3oe5I17hQEOO5Yes2WnKjXHOA4JH3JexxSfYLjkGZsifUztiRoxpbkAMYWtC15d4+0a7yj3OzjTWkECw5qzntxLrDmD3H28Ubup9aNN/r5QZx2fqCfC8T5nQvov/1x2m+//lsf5/dbr/+2x/mMDaxHTd/3TtsTtpG+z/D+vo/S3tR3VOkJa93YaCPQdnjqv4fSDikX1Q5dtvbN998q3XmW08euaQhtgc6mbed42qzujTpu14QJc5PtVSU+67BIY696SPyHgsfzJe678afGZrW/Zz7O+/FHmuCPaNms5kZ7latJ9qq50YHbqzKsX3vVy8T/oHE2Yq8Dae8Kjtbaq6pv0izxjwBvIWrM7ibzxkxdP0R6+jrpyjo5S/wHm13EAhJfF9qwdjRhIWM6vOoqLdbCwOxZW+IcVHqa8AaeMJYn1P/defyEPv0NvtsZrd5Z5ZQxf7F611+eZ6rnrNNiJ+vpFwdpU/KOWY9v0052bwuv9tNkG1nE19rIduV6a7/4P2TmQHt4Ler1FVCUGWJMAK0GacfuFlpbWf24zbBdUZeIKzar09t4bFVPbLsaSD9siu0q+yvapiFuFBMfSdvVXO9xqEl2q7lRgdut5kY1zW7VnnaRxm51jPjnYC+guVqXdWnCb5r9EJtVj0zDY/Q2qxu8Zdoke9UN+nKr8eeRqFNnr0p7F7+6Anqdg6af/TfVLuRK0YEYP+6TZ5d3+OjOGy7us+RP5cWL/NuL6O1pmm5Hcqp0I/R2JP7te/T2Q023Q9LbGzVdB0WvU+LPDsm/vdGXas1Rv4eyhvYqvLuZezCypwc/77ubX+bd268CC3hH7TyfO2utdN5U603ZS5B05Dc+mM7fqTvyGXAU9eQLqR8/m/rxFcAu5nE9+WupH38f9d+38e7h53jn8A7eOfw+9ee/5h22cVZ7AHYHtgYOBcZTTz4RWA5MBl4B7EA9+RTgGqCV/x3ATsBNfKbODOfUWLtQTkpnhnfyNrfCADN5924W7+IdDNwPHM73tO/g3BH9gOnZ7TuGUAdnKO2PcmjfMYxyzGW6w3n38Qimi3Jw/oO0WA8d5S5ffneY7mja5+QBU2kHlMY7k3oBL+ed2WezPBOA2Xw/kHcl5QGnMP9zgZN5p9Ys2gtdxru0ltIuaDntgq5lOquAM2m/U8Y7jmfRjmQO8A+0/3mR9j67gPOBbzD+m7TvOQysBbagnU474CJgD6AVLh14KTCTz7yTinMEjFuUk/1Oqispp2Us73LaKa1ju70KaMW5Gvhz4DXAl4ArgW8BVwEjke5PgW2B1wHHWvkAzwXeAFwJvBH4M+BNwD8Bbwa+AbwF+DZwnWov/BYDR2nay8/J7+20N9oAbA3cyHZ3H+/Q+gVwJJ+ZLr91+H5q0u1ts4OLt9nBDaSdUX+2n2zgGXy/xGZvEvuTsEbv0Yp6PGhz0hSbE1euZXfy47E5+U/Ym2ShTeWBSkF1oA2gbaD9INdVQR3AoAu6oPtxOxdo5uk7/7dWuj/47D/eiJQ9vfxFll5/rbuqulouw07E+1TgHnnvngNN/1L4Wuts8Zs=
*/