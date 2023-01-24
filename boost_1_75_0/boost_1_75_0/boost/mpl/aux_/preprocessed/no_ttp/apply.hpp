
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/apply.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename F
    >
struct apply0

    : apply_wrap0<
          typename lambda<F>::type
       
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          1
        , apply0
        , (F )
        )
};

template<
      typename F
    >
struct apply< F,na,na,na,na,na >
    : apply0<F>
{
};

template<
      typename F, typename T1
    >
struct apply1

    : apply_wrap1<
          typename lambda<F>::type
        , T1
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          2
        , apply1
        , (F, T1)
        )
};

template<
      typename F, typename T1
    >
struct apply< F,T1,na,na,na,na >
    : apply1< F,T1 >
{
};

template<
      typename F, typename T1, typename T2
    >
struct apply2

    : apply_wrap2<
          typename lambda<F>::type
        , T1, T2
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          3
        , apply2
        , (F, T1, T2)
        )
};

template<
      typename F, typename T1, typename T2
    >
struct apply< F,T1,T2,na,na,na >
    : apply2< F,T1,T2 >
{
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply3

    : apply_wrap3<
          typename lambda<F>::type
        , T1, T2, T3
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          4
        , apply3
        , (F, T1, T2, T3)
        )
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply< F,T1,T2,T3,na,na >
    : apply3< F,T1,T2,T3 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply4

    : apply_wrap4<
          typename lambda<F>::type
        , T1, T2, T3, T4
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , apply4
        , (F, T1, T2, T3, T4)
        )
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply< F,T1,T2,T3,T4,na >
    : apply4< F,T1,T2,T3,T4 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply5

    : apply_wrap5<
          typename lambda<F>::type
        , T1, T2, T3, T4, T5
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          6
        , apply5
        , (F, T1, T2, T3, T4, T5)
        )
};

/// primary template (not a specialization!)

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply
    : apply5< F,T1,T2,T3,T4,T5 >
{
};

}}


/* apply.hpp
5DO2hLdZieLuVO8CBwF2dgxLgHfbz4qMt2rs5PXxZ9wylGmsZzsGhLIzAqfUNN4x970qllUW40DaMpfzcvsFjIoB9lv1lI1MulQGh3ruQukNbIlB3fIJTRkSO99Z6p4e2jKpndG41pvGZFkyOo8JtaTd2Uocd+EflgTVjzLkcx8hbqY1D3pNJVmdce/pnxdoexj6IFeqA1kmgut7vIE8HQjYu/2YQP3bVaoNi0Ct29mVMDTt9S9I4aSFgm/0nwAveomJlJoCP+3bUp5Zjh7cHcCeChjvBmaMfeuSo4em0UbT3GzRawasyO1I+Osg3+VoBwyTJDF4118MenEEchbe1zrvwOh0AzIr71sGkyA3hRc3gMr7Tg6V68Dfng9IN2SAbkA6tKzM2dps8nz/QKc0bYOFMlF9T+wCfqkMfuTMGFfnnP6Lg4idQyNN49WytROdhAyNPtWEaRaYAHiG0YZp5V8hD1WFNvBd1CWx8jUQV+pKVAs5MInmnSyo2XvPWP5cgGgT2lPaVGSxeX5fK3oInMxZucElwV3bDewJ/HVsD33xhyKw1xUDTk5l1ITowAs/2/SP6IXJkMsHmTMt6MR8VndW5XTXfWvEKQ8BGr2hFg9j/oh2eADa3RlCHbADbuIIlfOAOZR+/hMpjyds90VoZcPqJsAOT+ajNDhwv/j+VJ2euGPuGvEN/LDx+Q2M4RhTuM7uPiM/eLwyNBp8
*/