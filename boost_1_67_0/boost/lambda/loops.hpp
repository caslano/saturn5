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
+WymPgs5DlW9W4Uyk4Gl+X2QDFs0ElF7vUMln5JjpOUs7Hx6D95npFJcJaF4sGsXo9cKGSJZxLJo80PKA0/CWKRx9d437m7WUYpcQ9VI8CLj5aXceGw3b9Iu8v6DfHfurCB+dH7k3lrn1vLcsaA+cTzMKNJUZtrBNvbfIz0tc6yeTKky5SfgchHu41jg8TsWJFPZWPlgNq1h9gZisrPuwYRVFqtMT1e/8K7hwei8jleaxTcgldg7HUC1Vx1x23JtpdP4PeIApSo09UxvM1CPTTRQCfzxtbv2sfRgzoQeLMIatEEP/nzf/ZZrqZNyvDiIlmj+Rp/HOGlOLOkmYbIyfurPcKpkQHt6qEniaC9kGKKYXADSM7p8cCWPUd/13UE/px9CZS9quL+UxlgEW9zjXPBSDm8LP3TzM4kL7eXa7Oy55RLw/g1RSJb7QOjBEPvBChdf/XgC85itkHprHodllhKTRb4Orpm9dc3cTalO1mCkv0UMwDYuc2V9NvEUuCZ4LI/OLDh9/V5kPZIm2TkXnybDcHQWdADekeVYtRxILKi581o+hmHSHRPH12Byk9uLJnxAzRHF2tV170jYQh3zUrUktO3a1VkYJoExnh/Iyedhunms0vbHezkAVwHmiSVSW2W9ue/Bof+q0JgkgBQ4q4V9BgYH8IhotpmDaf9akxSCTCkpvFwaXWJmjXyJlbkMmK8YpVp4RnpPtRWLhbe6PtwFygfdKj1pE3ibuikghd8dEEr89nZIK5tj2lkMVEGf6goXNVqYmutcCwYJrFay7luQoxDtWQP8Dzti+X0tdyt9Xabre+7ZdiO8Wkekv++RlzGHt9c5y6VRwbTsQBaAS2aKzPg/NPvxTko7QG2wvWjTguZiAS+FwgYkQdfzASgOPn/+eXAWQYqbu9A+Z5U4/0Jj1/EAtWUMSJPKRsNBLnvVjgFTY4G4ys2X+TzrgStXQuwH2mbaRhJd+o87x9jFdsSD99/etog5PN6wO4myR+mIghtpesgMLOopRSL9OLgx9gpdgrPrqZjDKJe5KdrKa83IxKStkN86oPtSx2vTeeH/nqI8WeUe+tJt9aFPcRUR8L6mZSsowEeN9UrFpRyHpq/dwy0DShVvvuhLJu2MR/CW6F6poyeKcKTP0tZMDzmw91fNRj5POI6BT7n8FFz+cY68HXiuhqmJawWu6VlSfJNvfvhXby8tZv0LQKSo3qtwUJVPBF34OpxxRtTIuv9KSztqDIGgRPYgY2yHZFqKS8r4WYAmnau5/M6JkaVCjeNEBe4trV0W9+jB206CwZwzSEXv/8qPbetZT8q55g+wiew6U0KNYp2EGDgsFjD8VV5CpBaUNIla/1UVecPz6jUcz0+xhHdLQDmv9WgQaOI71r1YEyPNLggqHnAZmbDh3FX+guxkkvOYhIWYjgYF9zxhlCbX3mWPNkIcJ9eos6zxlM4yjfVtMJNt05KL5LSNRXhG/tgRceKM+MYAMx1dJRVra9bTRIqNs6lhGyE/WrIl9+liboCmZ0oG+qLiCsagFsvQ7uPM09JZgZt2lOLDsdmsChaVWOofKKPX0tFsEuN0K2HAZlMCCsZ+BdiQxLQzZAfl7sar41fLdjYfVKRMLjw/S3Bxp9VAilRAdZ7+aFHXerHzrXVjRLMuu4+tw6G77ThZRdQ8bs/ZWJiu0UR47q/0VJW+yR2SdqYogLxpC1TAOkpI3U0nUSQBcadvTEJlFcihMzqUUrbGlVdazlOtlsibnrCBuNDTuANNt3Cwl1IwqWB/th4uI9CzQHWBjcbGdgZVko/UILDRMw/a86cbvHdmH8fe/v79/Q3gAQQI/BP0J/hPyJ/QP2F/wv9E/In8E/Un+k/Mn9g/cX/i/yT8SfyT9Cf5T8qf1D9pf9L/ZPzJ/JP1J/tPzp/cP3l/8v8U/Cn8U/Sn+E/Jn9I/ZX/K/1T8qfxT9af6T82f2j91f+r/NPxp/NP0p/lPy5/WP21/2v90/On80/Wn+0/Pn94/fX/6/wz8Gfwz9Gf4z8if0T9jf8b/TPyZ/DP1Z/rPzJ/ZP3N/5v8s/Fn8s/Rn+c/Kn9U/a3/W/2z82fyz9Wf7z86f3T97f/b/HPw5/HP05/jPyZ/TP2d/zv9c/Ln8c/Xn+s/Nn9s/d3/u/zz8efzz9Of5z8uf1z9vf97/fPz5/PP15/vPzx8A3r/7L/tYrs15aeOXVlXEcg6YsI5GcMScdlmXCzgIU6WCz7dCb3nNph4RXfrdka1Gi7CykEWWF9GYuq73eXsaz9895x3RvKDZyEOusSBvKWWI+uUeb3WNJ57TOM3U9QqeqWsrQZUpOg9PiDHlBp9uVdaCvnzSPUk8kN28e4Mkj3E39sEiFCMT95wCc8NyQbJ5bQvKxDMS6c72upT+47bgxHNQkZdW/KmhWzcZcO2x2b2HjAvHjvPSNF5uAajH0H1cAW7R2mR/otffsHhI1dfsWa3iVQQmfx5DayDFgsKAl+vHeKSyUE5E3+NWZ9Rwts9bd6252JXxhMrr1zhKuHQ1LoDFVlk5FzVHTeymGS6BG9Leh4O2jqDmMYRrQmfy5N8eSaLGZlFRO/X5zbWHWsvi9Z9Q4j1Je+6r6KihNoI9wDDC5oHneXIaFcubxVGeLsqNBS/rrJJFrYA1Tsp745Yhsod8x0gjAydZK5uB4vmwy0ZZ0hN8BSjpkRirTiucCPSIprSvYz2ZK6t2xMeivZ8vI466R2wPr5fwqB5IMkYQ/XsiYVydF/qcBk7SmgfDPitwO7AkTAda8m614z52UsBg2gQcZ7wWaVRjptfaSLNDTeXwYzruqP8KSFW9bmqk0JlXsKKGqM7MwuaThan6t/bOZg4quMQ6s4VnTzp1x9+4MVCXLfnfjUbWRuLBv5rqZ/vpl6IqFl9narjCAXimIYK4FZZ8UgC3BTaVBDh47FZZckOrl7RtYfs6zZTDmU9VVDIE77ZaXMHPq5gbucy1e0pktVeHYI3rUMy5Ci/7GeBkWRcjj9jLTcDAikewePySX841gWl07Aj3HY9VaOeIVvYdUHuHzkdjsz5nJ2ilsnXV+R3FgG2eS+P6aYRtR5ZJu7M0ygoDA4Fk5z5z9szbBhNRPNf0D+t67/LEwe5rhdQ+x7vHCDqAoNohNLhFIVK2SHsAyiafO9pumD9StYLZJSgRBa2MWVQNvWZGuHBj3NnasrZE/D4fHuwfzfZZTqIhHkVtqnuIdPhlWCcp1IeOYxsuB8VfzTjStu99deVpESUtHFz6aelPnLm+53V9YEmJMCm33MimPGvw8WoVkcs27TYZGoF38TM6C3Z27axbFx/DPIJP5iUGxw7EsNqnDOXiqX4OC8mfXJAXEPzV7YaUVKipKK4FsdIRtGrOR2ysZBtg60q2dIEl+nIEyqcsa0w6JuHaqQvqi8a2vj113HMjLY4bmUReslcJkJPbUk0I03deaRykyYopLRo5lZE8GmdYMtTYHOcxMGqwzheddAnnHBqtNFgodDENCi7KMs+UFZAYmczKJfwX7CJsOlX2FsSf7Uwu4XR5L77dl/MpBLnMKNHhECk9fLWQ/sMW3leqBilnKK8zGFazZDuLgH+mycfEBQpMq5Z2Xa6dLrXGteiuR3fdRZ9w132oDs+vlcBl7X/kY27vwKNgoNSj8wANH7Su2nMwMjxDyj24Z6ekXrKkpywqmyRpuZ10aB8XmSp9v6jSsF/IzkoYdwBXIGwT139ZvsH4pPBaZPHBNg9f+jf6k9SNYhSslpnJVlWWqB7AK4UJUeghffJz+wllvRPQwmytVSVD7NJvXqykowSCAwLn6uuO9dsr31hXElt3dIXq/bRbpcTLwnG+4kkGpbXEoyfl359GEmxMdEKLJrkL1qd+wlrcpXjeVhN75SEvsTeWS4mdeCl1juVHgQqVm1lTKEL2aOnR1OfxwUbBCvuT92repnecmaFayibOVtxCaTKTouAeq4SncBMSMutw/ingRs3a1p6IjF4NeYlYD3bu7ITx6+CKDOD2FemSId5iRwyFJ2sllnnxF5oW3aoQgD6P+Mwyfe2K5J1cWRQL3cHxzcqmTfvdCgudwSc/il596ZGE3yA+N8s2TtZ/Rk1IOZoig0goTgKiBkszHR14ui1JAXDjFxr2h7nKWs1rdzM1+ByhNkQ7/BaVznhBueNvNOSiz0kZGXP5lG9taahO6oTixylvB74+oSXl+knLexRLKxn3nTlUiINJ/02HY51bVQtJ7nlwWXtYaLQrP3MS9C9hsCSaY2N6BFBkQiFbKFz0FHB4goEuD068hFzPT9Bq2LZVf92LmWHPtGhpaboNbtAosUNuNzkR9Nu58g6jbnya0b7fV4cO1AyFF9YKzbIGegCLmieAOCX4+FwG8JnsWLDmgpm6oh6Lpy6gQM5JR1Lspt7ytUvljoDriVk/gyGxtxyNhImbrFxn9SUGl+fxGWa8CXQZLNn4FPxmwVFQjHUkv7bZ9EItQb35KPsekQ2pifhKwkL5i1ADc6qYUVhRZixoSP/0zf6IWiLfqER1zNh0FhMXnMGKpvLm3GcO6TkQihGwid7N1QGV6Uja837a7nMIOo5Hf3eG6PcXeJjUE4JSq12/7v9gOHm80+hjtT1eD7SV/FNY0FAplL0q/5znmr40N5fHXBHr4DRm1sqfCkF7GGE+FGzWSjJ2DLYsfwtIPg8jff511U9mm5eFhnL1Up3GwWklK0XtTN2zRvxxgnw27oX/4KAcGm6gs3bES7hRL5KEvTSsYY+qPomDLKqlJBQLMC29mWj0FpGa9jTQB4O0tW1AjA2Im/bcCE4d2E0SM5CJ9SHWO3/M1LSF3+zEh4qN38yFgfvyqm+oaDm8P6C+XunsKGjQvVt1MkRoxXN+BKc3WDFXkFpmEThvDSOxApZ+tWrVRLo3xRw39rgbB8z3pNKT3GbMB5SDJ+tlEBDFs2jOFsCbcz+HKR3OlgElGmOsxyEslOp0fn6qQ/XXVnjviWfPtFE9Grin8f5ainRmI3701IHENwpHZqOPCbNayE3Vv9xV90MsQ1xaHLiB3HvXuP0ol+6q2mq0qkCXGZ7mRNbtzRNvAxLtjmPE+XrBSxkA1FxaAKDC1gWSnRwfCSqFRuKJ6+Qwvq2EJql3XdvGia54+mJbfXRmJthdQCmLgsgLpY2noVMqOe+pfP2vGwHJHAuq+E7k0RxzWsA2k0MCEuu7MvE/RYN01KKzndgmf2PGKdlXi8rx451DgXejxF7/MeT7S5AT8muy4SE/rB0inw+Q+d9hqSeHJkVNLIJWis3jjtGkGKcTZnLjkapY0P3DokhpCTIi3abwDthioms2D8H+G2G9HIlCjRFht8Gkr1QnRG2f0UBDaemHpe7hCJQ0RUltjLJo7VhV/upjMooGUs3j7cpAx4gt94LuFQlpMcrEJ44GV1s9j+g1GgyiPZpLWsltsZqUCwFxshiuCCgCz950i2Br2X3Idt6t8MEyg0OpvrfiXsv4MvJOJrppt7rLdaDxR3QZ/JDgobyUBuW2qU2+uEjNhOrttnS7minBwVbGyr3HnYo0moqj13oVxXaafRZyKfQhEIPo/9Dv8jWHOIF0bD3qzHaTwtXdsaPqdOvXesOSfPNv+MkHz42FRR4ZlKY4Gc5KkeslM/7LYCvFMKrqabnrKhPnXbKhXBaewO+a2aVmJcUeUjKgLL6xU/w4g18l/DQogRuYhcdnQw/mIXNPBAPztE+CtyhAhsfM78ymAlezz6jvkJ+tFR2ml6pzR3+39YMMnZQm3+1QsVEpLxcYWDEmgMKq5rIQteuHXGof6xqo4pieOBUjdiBWaKS63ORxE/Dst2qYMITS+I5xhETxFkpt4ik7sdBRC+Eej5kVtRK72SyjvpAwTnF9DFUmcw16XhlprdJq3iydhmATI8lsx/CCO9ZHGBp0x33nGjYLNtoRT3ocrXvX1akSB8cSiG8dJLJ95N5q0CT6SgRsNMmyYY6zInXkhTXyd8Btv1FxxrnFgc3FZKpT1pNFwB8jB8CIC2AIeLJgsqF60X4tSriDibfIsqindP092BfbW4PM+jjDkpKQWPMuIlu5ggiXNXXqFdzSbrh79MS/Uz+KxoQTNHk1xa/Rw8ACs6Wbj/MaroBiBqY0XESmXJP/xPAhmQAnTqZ6MQ2CEFYxLxJUUfeeeHEPh4at2gJtaov0IhLSgz2Ox+4kvZNm+a78XguBK5fE1+g2w1jY01QVhZPvgTerQG47gKye7uqXKpRS6B3I/Y9XxX3CxwCL5cifMsdI6ulf+0lVd4UCNJegfJb8fnXI6IlKB5J4JBKvfr4LnDdvst0lYzM3RvtU/uky3mk/6u5SLeJ4gYM7mwJBYheKIy6A1tTvb4ZXRmetrQDPSkQy6hh31OigX9GeMUW6aG5Us5hCHfmRQEnlsE3mKT+nXHWv4W0qJ+NAG1BHf7eOKGu/Ut/4HWab8fnJ6VuUcdEb9pVMal9itMs6bF7H2JoVCGTEYXoh/z6hL5fLcH+Eb7rBo3gHK902Vz7h9YM5b/vmNBCoQ4m6sWY46gQQbLMtOhalFO4Z44V3j36vLRjB8fWmmUM6pK9jo0roQZV+SfDSYZlk6EkqstB/mECfz2dCk/a2Fa73B9+PnkupGNVncIpY80JYLzs9H/SxUwxTx5Fi1L0a+ppV2EPt3ouMhXnarxuhB9OZNz8MHiV+1qTtSM+WvRwyOUDsP9lWfM5D9mbxuMlh8A/FEmuIB0aH02KKrr37kHo8SXOoiUvf4xxg8dSr/KH4OaUM9z/j1gRgJ0FjapXoRgckMLVmYm9G9Azr7MT681s/je+XFKUNHy2hbBsbVUojr8wCbVw6eEicIpiZBAJ5GbzRY9RrDkT/8ZhUC3y399XuaJYoSxr0M6a2Wmc5IlqA+6zZJ0Fs/eAfHIBfUvGsDSYT7jwLicDL0EtvIDoOozp1OFt7R+LWV7gACzb6iltlWn7ewxCOwlVMOxZ88/JxJBuII5Y4NfstVKbmba2xAWh4xxtdVWaGs/qmrmX++HwnqePx6ifHDQRqhV59IbkErUSufp6Rmy8X4tWA7IdsetwI/M1+7/UJD6WuuiNfgf26xUruFHRmCClwpXYRQq34/sJeGU3Kl8gzKi5sFJPP2W0mbJeEoYUWvVZJ3/s9bmRjtJuewv6ccJrQL2yRmCb1QxHW7K0n9BmGfERZNA1knIXL9MH0b3xH4Ovh2FfpzMrsrwtB7AMfrfIGd75rvuZyPz/O9kv0pDhE3W/9HRhTE0OlPovcwuQFoVN3CJhV2Syi+3UOJ73k/ND5gaQlRiE55PetZRn/f2EZbVBKgxL+TNef3wx6sYGwVCAq6Cu/CczptGcw5CvWHKEKkJCHyxgAcLmxqtyGGz2bpZhE4jJkIl9EWWink/hl+oMoLZpRVk5Tw+jRoFSmPL+1ykcDkuu7GK6tlT+olmflJDVGnj+/GK+7sIky/aKuHxqV9OTaX7sDAEzj/jXQ5X1gLVNq+AEfOF29hQCIN1D8UI2/cvAlKfgPGTe9jCEoNweNE9SOi47d+w4KYLhTbd3nLKhJ8qrU1mxNwzH5I0aSbAxj561qBVi/UL0IjlZ1O9fMkMaCW+tDtd+QfvMuw01UIbKm/ojDZN0qivgxEU92JAJYD70lmBcLdE1FZsQ0GfNmr5MyZPs0ABT98bC05o0qliHhOM3mIlHHJzb75Ngs7LbVjO5VK/OfFCjO7j12KWOTOLSpIvju10mkWXoNjmL9mU3EFY6VNI5JVvEW8ovLNSOY9fmoNPDMvgmYmUUq8vs8itbFORta7+AjjKbbNv4i45OhmtfDB/eq1yJdgq4pC9iiOyk7M8zU+uS308Soer/UgtajvsEx7zIyRfE98mlQ5mcZBG9F8aCtnI5RBKk9t+4W3E7dxRsChTeHm3J0DlfZXJmWYoSvRwH7ARWayLKIIMh9gHtmykEWjM6VPD8Z2DVHMarhJ63JT83nqK9fYu4A6CwI//hc4YGQjaGQ+5ZJWfWzPTJtbyCrnfYgWZAaD/M08rK+8Si/kJFGUmlPxeHf5CIwTmZsBgRmzCDpPKgCPhOTtkib61StWqKKG/qYGfUhNWxqdFH+8Vj/56YuC0dUPjDIF9QwjzyfLtnNLTPALVIyDD2tcf5sYBhvWTBfUS3C9ADC+FxM868Cu+PJiOY/WLwGtB/svABubyEi01rEU7qFEKuAVgsKuyjoV0tJ2iBhdIsf8N88MkyLBDFX3fzQAcIVZi0XiQptJNbEaHFH9BWlxXwRhueGQPPHSzecxE5E6e61INC6x4namA019/W3pKB65bv++FRWFey2Fr2mQ5PdCRWH7qL4GF+ztRdyDWl3+LITSEAoFzQmBTv9JrBU6BuCnKg5V/prIH3qJlaJwQkZcjKPniolSnAA2vOFBBu0donK6eijd//yG4X2l4UcwDo0dBnZlAaS6utuWxvNqmJnVTRdRYaTQM3xakluzdVro3/5X7WdGlvlf61YJl85xg2LsuHO8n2LOa0CMpz8Ay4pMe4GsVrNXdnB3B3D2lKCTLoa2X2agZhuZdlJbX83o2aMGTOsE0llXSVD8W0pnEdUo1xZgYmjF9AIRMWmJOpIPkkTqN0lThsbE08SUtCxI9eg+k3F5IZEe9yitBhfFslAEZmQtAhjmW6n/eu/9Zx4Itb3tzF5OpMxAJm6mSlYWa+gjT5RI3128u62YpXD8XnjZwp334/IAlSVtE/ELar+Y3jbh1DJmy7Nlir1kuvCH8R7SWngha1RXKw+Mz08fh+kYd0na3xoe1hR7ybT5ILu/SXyQ/D5/95ysZJsbTjs1glTIySf8PesGD0aOEIWVSP58KdbdR5+eDZjsVlGg2IywF/aK3ZF+faacQaWL/LA+Xg30QDzXddQK7QiKzPh43bYLnsF2sP/PSB9xf/2AD4AlKG0ynl55HtA8Mn9IuzIzWMP7F+/b5z1gAPQ32BFCK7SEWy/CQTjFrjEL9zwec9Nm1TRvfy6sgDUqbh2/xYEAmJgVxXBGMLp8jG/VGLVR1rk4+ulitM0We/bJD3TICnB9IU1JvzHbJpT4EackitpClbBQOLkTZxl1+9zGbt8v0nvrbuwM0/Ennl+vzVk4dDa+1mwtIt/g1Z9I/Xs3eEAMIBHFMYULGheDHGfVI+TnjlnPJeJi1JLkCUmKZsEBwLP970d7qy8a1g=
*/