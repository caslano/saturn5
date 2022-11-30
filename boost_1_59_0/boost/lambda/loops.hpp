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
NGVM10gP5wcWIgl4tGNpuk57pZgETPpiIH58oQwsj4hXL3Uzn4NtVobXT99gGLksLY+2Y0RGomgm43PoOSwWx6/dp5y9RroDt6H93PZITlZ+L6ND8al8i7HCdsQWelMVeIaoNlEimTRE72iHg1cTcOUtsVqIcev6YhqyrqWJ6V7xG9I5QwnAFrs+u5p7DVex0/sQC47nKNRI5kWVny+rMek8jCAAq/6M0NKOhkkWjg3p8kOBAe9BhEXVTOf0x8HtTqPnypPNTuzTfEjc76krV/57c81FzqliOX1GeCBgamO1Bu6hXkme8oO7dDXIyxR/g4oncYA0wHlnC9cRWBu6Y3soQuwYLEN4cXC/1ITZ7Wa33onXrNd5vbcZOEdlOAladHXjXe74bVsOe8cxDqotDywNT2ik+1WaQh2zETNNAWqqlv6D4hhfdBgOlEaGPWMis/aho94InTigV1Ap7DeObADUEOuIo9KI9y6w/5umyNDxzMkTzvL+OnGhzU5Nl8zFRsFkI00+cO+POk9ozMyI0vTNzrIS7WaCf6E8HB2NiUJDKeexkdSyIEPX3opEBWo93v7FshgcuNS4TP7t7uOBaiJhC22+AE4755ugj0S04BBL9V6PwJy99bi7Md2mgt1gRYwtCvEjAL/q4VOlqMThYVDUQKONvosmF7BHZPMyy/HEWKKosdX2zMMvG+5g6kSsUXyZLgdj5LZMWdHINw2KkgwFg6f8x4SEQ+c1Z/uItbN2uuc1TB88ko0Ao7mTqV6ZrmyymxpWPRg/bDICYFUcTO5SyY+cYIBJ8FsOxcSaEPFBVL/E5U2QNeCcpUKsGbplPrpNEoCDqkcfVS/npHDDKUqaJWavHFSBa3AT+4i73/fbaa2kERW2mtZCWjQic9QE9RqDJbq0lKuT98i6BgFbQfTx0qouO6Y57ivcD5Cz1Nhd4MrI502/gMQ4NBUZ3JdZj2BLdkmsrsNaZqANv7PT0BpmrhU/eKxG0BonYUJQGATUcCGXz33rAygLAtx6fb8W9qq0uAAY4wN9xKCfoDfoMT/cAONKO2AF/9IlLXTQPwP5wBnj2ioNT486qEPaJ5ygsC0IIGys5Q+QQ8FKel+0vRh6ZBli8vFlOSoov69eeaYPfQCLYIhGrAb9eM3/EM+bvsVexsEx6x4uuKKtA4EP1T6WBqeJLEl3dt9qTUJlueNQqJdFtHGvIxPkbeoPbHMuMue6eZOFXeFmlACDHUybPfscCIHwPv4f+7PgEgrsbbJk40e1Bd0WxXEngwVU2zBV13LO3UHi1nLd8ztrZkUuHm6dfec54n8CWvv6jLvRsXkg5MLTuwD3WEtEur+4yYl5ZNakj/OrWcjzDbq6SnojeaWtSq4cgq80sELxhgWBysAusYQlx/EWy1ASmvY+BXm/M3Ouag5IzVRVAg21EGUeR2IfCXfVqoQ1VJHC5WbpC05eIfx5smZ5X6dSCZve0NWvBYIPk9ao9bUSn8Q17/ZrWagIfikm4+4tSEz1pE+5M70NH0P+rDcC28n56YCgMSo0wmv5RYLDn/GKAsV9moGqUG3BhXNM3UYIL+sXp74hiPKS7a5jCmOlrPJz2Wd99tFtdW10aLAL5PGfW2d5eZ9hZWiwq6rWa2r481w9DQQWJl9WfZAO9SskDlMUnCaxhVkGd2zj/XAoZkUGwWd8EbtepzFLuYo2uteLJjTreVQ2DVToLCUyppgqSlso3p1KosoBBBzqDcrw3nKelHH1fKHDUAuRe5Nv2feL1IiJrZn0aBA3ge3yplaqzH18gn4uWammQ5jX+GIk4pReMxCQQmjzP7RX7VXvvUj3KaUmwoc/nPCFl6YG4ghmDmvYFTKDj1V+roowF4SUnzuYLTdfhl/xA56wKzK7/wRQa9iHQ+m7QtEkXKFniyn18shcCHkjB9shkHrRghVFUzRitxOdj2Pxo8GNcXUVlWHyHJz4rQNgQgt86WUZNcvV8W89Wb0K8Nm2kQcytifqAjkEN9PS30ZM0qWa59NowO2MAJ4agPY3WDVOcmamVlnt5ieTLsO6UUHl5m9/5jaKVUEZG2hfeb1puvyefekkwz65Znf5omMiKe9kNIsjcaHgVKmbS1Q2HIi8W7Bc29I/VRBDKW67xUNxrHarNyyjuK6np618PS8/1qG14xc4iviOC0zhtK2cnKQhjbOd8s84W1bSUvUvRP2omk8ywMS1FgeKdI9vV7K9k4RXOEJsiSUHYuLGIFLgPnBjBOPXZKYxUn8P8df2RY1YBdMw8J30nVbQS5CbVXrMOZlhEePecpOiRpmrsFjQon+UHLtmlqrUnmyrVjWYp5ZccAspLUwIAFpHm2heb8oJX06g1ZptbvRlOFqr1e1Ygmi3BvOVX2GR/WPmUsx3f0l2bANAwmWWKTlFPg4SuzDGRJ+9FZ7b7R+OsEYxoJKncJt+KDGx5uzIDocOlOEh0BYGCW+E2Y89Zpiwxejg1gJDqfL5ClYukM8SJ+GQp4EPz/3XeUsz0H59UDMLMZc/d3w9EJfkwKhVd0DOmure6+B4XaqwwgAJCNhJVPW90eXbXcZ7kR339BnpoE2Uz6plj1iCsUkpGs6yHUsOEp5S0VOpzPfDK1kIl8sXP+0BGPHy6uuU3ek3BXfQSF6wirDB5VFhGfzVZ+nK0fAyzEhTUP6oFtRGP+/ZjFoSh/lCIxZe74v6xEC+/i/UfpOOjtjV8rWMHpc0n8NJjDQ+mdTnajuTwsWkgX3AYH9PRbKwqvq0DkAKyja/I0R4mXPV6F+j7Z/MnG1F3QjoD2n9W/mueqWxlvPV2uIO5NMDkSLZG6iXCMEthwY6IGPggDk94Xp1yktgICeyHhNIrt5qFK7103uaDSG6Ov1k3NsiI/KW3zgu343hiRQtOQvE9MfU9W1box20kcOEriXGQMMrb/Axp+J31j96WkDqeAB0pDl9u1TjC5VkfQkLc3+/D+PkGc2Q9wTRZHWeSq6z3DBXUsqWr7YMX+3QQ784F9knMztYmCUzU90QgYNAgaaJemMQPQ4IVk+yFeVFU142gwZ5tG63tlZBAaH4CMOycVkbI/39mMh0FxjiAS//R7k7nQHFPh5yD7VFCB6887hLDfxKZuAdo4vQNmNVNhkIMNR30+FTSYyIMCK5lsiwJ7R4naho+UmFmXc0w+0EljdRNTpGcFYzgOAPlHB8rmkJjnfcN80C9DrZIgg3bJuRcvKvqqiqszmMfLwU2KLmNHsV+jNIpgcm60XQI3lLb9INCzYukmMOVeX3EggRAQC3LoN62ZUPsuHi8B1mef1PgEAAe1CeT+xbcXmRE/a61GjujV5cEoy6zxhdrcmRlZujpRDoB0pQumcJRm50aSb5h7wgsgBO+qUi7S0ze7pjr/vbDfTH973LA6s4G4d7AF7QaI+nlo4C2NAzUJ2T1F5L1g1U1pd15vRdWpmyVRmt0qzpd876/YiRH5EzyH2Hvlt8eige8v2JdCONucESaGBJi5Xacxm3TC+2wzgCecHIesAp7Id6maPyp2aT1BHTkYqhaKqsyKrJUmX6ymWHWnutYqCVXCTNQ0eHxADF1ppF5lRm4hwvn2MUOuIiJOUCHfDvJm/plWtCmmeVl+zzhttMMCV07uw6HB7F9gbzK/gDpkI+IglPXRgQCs3YqDButVd3CRU3udblWBp0UQf7Tv2f/SA/qqyGOi1MjHjhiaMPiTaBXvfErFuA63J8ioDYr1YcsuhGzWGAJpzSXhmBil0ARF/hZG/0zkXsNU0SBKvDWD++KRPhAeVSp4N/skPdmcAky7lKVI5z7X8iQSr3+/UnKqlnXAhE8tihNVWynjeShMD92ecMqVEZIhCfMHwAKWAh/S9KAbsg0EfeZ0Y1ahj+A3xpTffKx6nNcKPjwgxj0WgqEL4v7wwm2ktd81gnRZ8KQwjMPikM+3v3nLse8OmI/skgbi9DwGDIJHwIVM8595a10P1VKTCq/dSehSvbzTwgSzi1vPj5HwWfrwQHcWc8F8ky6IXkS310v7N7xmZeTNn+PCpnl92SV3F0UVBdbkhdTBs6Da+4SY9XJIPsFqFgljMJZnEpak/qvLjz2XA7E0b0Bf9IBXtFBqEfqrpZ4LuQm4Q7dAGzbDLD5B2NYuetQ18WO5gIarWIoKyj4pNuSbu1Bs9Mqq4FMJkYKNk0Bgy7gKTaj7Phr5vmYMJjaBj6jSUBQrCE3p53BHnpEKUnwkwa5ypqLVQ/XH9sE+C536W/xhJB5LW6fpFp+49mj4FPLWDPyvM8/IZY/Gk32s1n8sHSGe6MjGXowYjLJMrVJLtjo0NwnQnPlke1rWuUceIRnj+TBDCAEIHvmmPSvS/qfEZqrTIy6EOJNHYmZrqur5JwIxtVuzT4QkIa3bbkMbpjms0V+EnyLzEXi53uZXdmAJt7GVGO7MN2+x6leAYhZvhGAGXTaK9EJYt5z3nJdzltnJWbQlTibUnEpTGk6ygL//oh0a9ucKUMrrWNPQojjpTx0e+N2xtRqHMQ7KxSG7e75oL8G2GCAYUWf3/OKT6DKEm9yj4i05eBSseYgOrcfIKWgBJUJslBhsI7Z/Wq9H3zOTC/WljI22Og4P5NKioWgSKocnfCNxL6TbiIjPFwneMFmPlb1neWZVp+tXGzK91Mi7MNCurNTSCM8F8vdxop1NTgQ/JVTXZtjg6nraCEi5AARU5PX5rQ1PnZoaAy+u5GJqF0Q6fxsRdWWCDhPQBPvo9gywCjepKHQchlfeRRM1kKB/g8uWnloLDDImvNWSpKK6lPglrhvnV4IsGwJlWx2eskrKs/JGSRtbQEBz4aIfTFcgZ6lalBPxl/UzdTLYsKmDW51R2+s1NhFUapg4eFOOW5XunoZ+iFosmzz4Dy5VyyPYXeDbHq+ql4LZvb8P7pqESW4e+HgzcEQp6rNiuRmlbpybeG+iyORyQ9wUySagg5gCqtXGm4W37iPASZLk1Udigss4hOAJ4ZbVE+dobX86wQLzJnC8QXXmISGca//eEOAXDl8KWwiK/Euq71IQyRW0KJW2WpA9tFX+3+5EUXXYNfoj503n10hZG+wy/n8/rA+2i3Mu/XA50AtXIdZtapwaHyXFIN7d9chrjSnMP1jgFI91AbAklxclKufcxFIKfUBk71lFwHX6hpyPjwNq8k4gcDJDBMs9zlySwMftFEfoUDawrHBG3m5Zi92Ik+lhrwlFKSOIf/oVC4rOybRHdb+YRgNBW/jGAoYkHjxqFIHbT+FhZcG67jH5QNrGZ2iHotW83mhZixhaXm1L5BydFOJXv/ZqJOspVBuHAjnp9EzrhkKK9kJ3rbew66vyPXLzCZsuKkI+nCu0Pjun3v53OP+MyAM5qGKpuda8OjKRhozp/1hwjjsgcVVd7Wf6jg1YCXhUPtjyFOdAkrh1P7NHH+erbkPdXr4fxdSRuqIq7fKIB17ENwN7xCFgiFMcW7dAzDn9Exd4E6svTi6IHuJq8VAggkcj+0WToU/acQKIOUr+x2A43Oc09aaP65nsouy9UuVp7BX5afl4hCb7Jeo/zNhf4VdFkCHKa53s5z4qbdR8wyY8GzjSgn/MG8cvlC36ukPfIQ+dHJHMTGf2TLxpToeBZvYJNO/KjQ2FToDfv2f9nlqUYk+fmWj9Fj3v22H8ZVEHA6QKmp0HPVGb7KYXB0j/KbG1LxLX502fUuEm3fXCcu8MQMHaiZ4lWGA4C1JdV9UGabWjdpyCRdSfyMZJCAXbSRgEtYQm8YIVojSRLvn2m/wIpRJKHvm2QdCR8CDv5pZJYZj1O1iMqNS3Pa5Gab8LkETYhFfueq26ZAJYuBYy6QcinNawjHUuT5gH3Y7wei5uzN1jIXRibIP9cxRkEhQG+Q8sO7X87JlOTQFMC2IV8Mjz83y/5yqwbij/ZgsobFdBya0qLvxTup5beQgSdK18T1TJSojj0BlLJIGu2WX624B0hWWKc/n0LK31h8Z7qWWFfwVPyrDF8x/WdiV8Gd/9JLo0/udlXTRK0SLk/ZQipdorWyhj05S3ulzQ4oxaiCn7FzVERHlhLSHDiD3FVM695xykXgKonNLBwICZPV/nMHmaKRtcuwS/FFPm3bkbT3zewNFKnh45z9wqEr3oagAmikSfhS0H9QIoOc1hla8ngb5Igx6Fwh7Y0zzAn8/Y1kqbPTKSvpD4lu7xW9inkt+0/tNpKD6eHFMu2JdkooLzjI06DMKdhSecAIgtii8j7L7K922hks7EIp1aP8Fml7o1N0zQEI18Zx5R1q9jziYkRex2nDtyIB6eJSbo8j7kLSMn2BtJjB+RE76Yr045ZwgibGrapknAZxvlIejhzS//GEOCixqRiE2r3w/RCGVnx7NJ/aEk53Ifige5B5JTUl4R/VgRsS5LMs7Kh2ASYl2WpV4c4Upn0KfkVUVz6gH6CO4CI11QqXW9+0r8no3ytLKNTkbOGulrOeBLfkj+qbbEpOu7CtOnADZ1IZIOWZ8oG5WsnUk8TTedKB/EX4DwZZUAwouFIaXcL33Is93sMyRSo0tL8szGhTZQi+ZZiRpNNuWYRqtBLsMhGFRW3CRdETzDdHo1Rp7Pr9VBd1wqii1+z06fi3WuXKKiGpTSzl3yguXdzzr45R733AL4fItNqiB/zKzS/EwnahrVt14mbNBh7ivwDNXznbH5czDyDSqsvHH6a1QvoBrVagbloKAIDkNxY2fPRreyK/UzCWqI365W4rZEIS2sW1bfg31rrsS47ob2VfwV4ixWdxRCKiFLhtzpKXJEyLEcShuKN+JGpYsuLaqc3kIfgoDWkArrgmKFbsGDGtUU77XzLX/szXbsIyZCUATx4834oan5ry79GrkrWawgYdkqeB+nVCCk5q/PxEZLucWHPfg++WlRSxhmgbSdeKa2ZWRo5tw9s7odUyymchFQ7umSq1+Sy9pTWIoJTmzhF+Cc1JC0R7hWXUBFX1fzx7+obdkFBZwBoWrQLuDZTqPfeEHTywpnEBd4kw7rTDd6txjXu8OSycsLkDDMHhgCx8N3g/aIibnm1Cp2hR63CzHdsspfa8eC+1GRuNjgjOxJcCq6I+im6SOuhhT7abrcV9YWZoXxPcosv/sIldNIODDI3SLVwE18K+IWy+b9mxGxDh8kB2lO5dtXsBK74J17Fr/4bVej6bsH0eA4NbXePvKjYoe6kGoJ6gYtoYkdvaqn0vhn5uE1ZtxKBwJv3XwaF1kvpoU1nDXTdJzPimTGPpzLkDq8jD6/jkAuDjsbWyzPTXTrvZkgLzdpbRu4R8S/KldX8aieiaE1+M0+XyCvzD9jKTvmLNLgdD9uOZaoYDYXgf08eWbfCoiNOYyqarXDxnZodFnT05DNfoIvtZoIqIGo0yI/RZ5me4rQCtTGysa2NvIbukN2ExCodAhufN+6JswSnen1r9ugxD3MJFiFiZwfmnf8XHlTojB6SKaHQKll0dy+q3KHkTDpglv/rd9uBbD7fyQlatvGUzHYbpX3NYC/Xj5neKrE72ya9UHIMaVSedbnu1iP8NCwBAUuj/fc3GztISepn4Db15KXCt9oQVuYSKVnW/YdjXuhAdLQIHVt67rTfdr2USvK8lgjqlimXgFm31KE7/6CgiB5rK3MK+xqy0vsT10tqPWV8v
*/