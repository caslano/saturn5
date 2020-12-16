
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "apply.hpp" header
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
L2UrpppRt4GqxZ3frFDm637Z78KLtq5bxouxA4YPo3pcy4jj7o8gqRzaLmi23vUikWWBNwhzmxqJah412iZwmbTcXqXPxyDaVoOr7DU7YAzXA/6NNtMpTy5P/Zvt7OTYtBbnxfzF+Pa648/gs+5Ysync5PHT4NbuOwbXPvuOwfNYN+Ot3e2x8k3/WXpFxvtN2/Xj7drlxdvOeAs7G8c7quXtoLbuMN4Xxq6f3kkt3nsY716Pvn680rPueF2b/3RB0+UOI9yKyG00Y75t9yy4oboz2Tkiv/o1utZ0au2s/FohK1Addq/rj4QTUUsbygYGo4+1GobxHRD1gRj5jvAq/Gq2gQC/Oxwb7n+MxN0QfZzHNvUM9EdqKGBu99bFIwsP405UIjrMsXM0oiFuM5rnq89vg2fMujosg2IZxTgq7Ti19dhjNoyMZou17TL/MI07ZBmVt6ILiABoMDHkuEzKpTtW+wAG/TUOGytxPFccQXLql1HIc8XRkYydRINbY6Vt3SVc6v3bdIdtdzf4ACG3PRfZjlEBWOO6ts+5YjI9kp2sruON3JFwfLB9pIyY5raKofMd8oeFGzEak+PL2iN4qyA3ij9oVGNF5o/bGKWNRB+DYXR/rC86POJOSzCM2eE6s2Jsj/T2VZ+Jc8DrwmrfcHLqw7xj4wtr5q+RvcwVrZOv8nCbxcJ1Foe+bTphmJxr1T3nHjfmdGaGGQU/mnQ/I72yy0rbKb62RS6PCMjAV21nJ2WciMLhdj45jrEl3xYnq32bmllTfNLtOtCaPFu0JDfmmMx9ltLKOrDO5fRxMgaQcOQ+oOoWDYeefE8ZXV4z0JLTxAx333M3gtEHh38HPTZ51EA7sWAmVkTm8NILl0Ghk8FYzz+GR8FuQ9nVxuTutjxgxu3al4y5jW55isNDbFsYcpYr6kAgbDRn5x0LJ4K7KyxwdV2a3FYdT+uZIfchOTyq7ITpOzxRcEvKTmtZN8ayzDMOaX0Y3Mor5egbydtG1+/f4A1+0YiUCa9R3jXFuIgkhjfFE9FeEwdQCqgYUsOkLtnph6LYymh/l+KmJtYeaD3Y6uiUf6wHWV77gRZtJFcdFS/FDolRe6e15uGWg6EVHiQdnRgLNFhiOD7uoBvXmMHI8ONiyBF4b3RDSB4cBA7gSePOrhUrV3WvDvdE3D8twAVxZKxn4aysHjyrlCnjBHzojZeT+cyD6wDni3eEl2E+yk4LwPSQlUT1Qb+4gpG/ewbrIwL/PmzEF1YjA9HwMNeHBgeqV86ecG8o8bhY1L//Vtcyfb/Zbw4PPs688HppmCFYTGJe1+XaaN13lSW3FeCAM7Lwqc5nJlxfB5ofaRzkpRhzP9A90kuzk8Y7G9atRe6cCH6hZYGQLD3R9f2DlmB3ez5/o4O91g0ePzwDtjx1g3MsjCMX8v8gjq0PFzDf4y98Mq+4b9CvzKUtT/0beZncNpbHDNGNzitVn93v2IK/xyTz1f54gbr7nf57q6Xftwa7HhUI3qTfp/7I4uA/tvyLvSsPiKpa48OiIqKOioqKelVUNFQ2FXdWAUVAQNOyYGBGIQdmnBkUX1q474pLZWmFS2VphUtlZYY77rhUvrLCpZ6VFS69rKze79z7He7CYNBb/3hXL9/c7zv7+b7fWe4558rv7+58p34HOAN+lOHOxXNQV/V7XI8z7eh9uRyXHjzl2oPk79XhLkU4RYowivE8sy2FS9cF8rMFlD0/h1vppwR+WLzFGv5B4j+v4Z8HP5zSzq+FeLcqjmmQ0N9xMd41lucWLeT3/5Xqd5rXakj7k5r47oDfDe9yn9LwPW5JZbgOv1cp+L7gv4IyW6txHwB+5kM6/dM18J+pga8=
*/