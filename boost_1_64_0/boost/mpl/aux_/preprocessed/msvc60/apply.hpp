
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

{
    typedef typename apply_wrap0<
          typename lambda<F>::type
       
        >::type type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          1
        , apply0
        , (F )
        )
};

/// workaround for ETI bug
template<>
struct apply0<int>
{
    typedef int type;
};

template<
      typename F, typename T1
    >
struct apply1

{
    typedef typename apply_wrap1<
          typename lambda<F>::type
        , T1
        >::type type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          2
        , apply1
        , (F, T1)
        )
};

/// workaround for ETI bug
template<>
struct apply1< int,int >
{
    typedef int type;
};

template<
      typename F, typename T1, typename T2
    >
struct apply2

{
    typedef typename apply_wrap2<
          typename lambda<F>::type
        , T1, T2
        >::type type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          3
        , apply2
        , (F, T1, T2)
        )
};

/// workaround for ETI bug
template<>
struct apply2< int,int,int >
{
    typedef int type;
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply3

{
    typedef typename apply_wrap3<
          typename lambda<F>::type
        , T1, T2, T3
        >::type type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          4
        , apply3
        , (F, T1, T2, T3)
        )
};

/// workaround for ETI bug
template<>
struct apply3< int,int,int,int >
{
    typedef int type;
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply4

{
    typedef typename apply_wrap4<
          typename lambda<F>::type
        , T1, T2, T3, T4
        >::type type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , apply4
        , (F, T1, T2, T3, T4)
        )
};

/// workaround for ETI bug
template<>
struct apply4< int,int,int,int,int >
{
    typedef int type;
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply5

{
    typedef typename apply_wrap5<
          typename lambda<F>::type
        , T1, T2, T3, T4, T5
        >::type type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          6
        , apply5
        , (F, T1, T2, T3, T4, T5)
        )
};

/// workaround for ETI bug
template<>
struct apply5< int,int,int,int,int,int >
{
    typedef int type;
};

}}


/* apply.hpp
0Y56/hg7cmQ7hTPwE5xDvRfgG/gpHub49Bnash1OYwcaSs9gFH6OyjHwO7l/cdo51fNiL6HtVN1umn7ur58Zu4H/30XO19pQtaQlLWlJS1q64tPf2v+fnBKh5LC0/n08oi+/DUCJ93eoxv/rJA7Ol+f/5eES5fr/5ob4cEKQT1gInxzGo9fojg/Tp8nz15z+cgxAwxYPt+T1hIXJyeXxcRHnYxTFFDO+yXSSxHg2ZdMSM9rJ9C3y/w5l0/L/yuc/1omYmjeQawFkurdhurNp2ri8a9n0Lcbl3UzTxuXdTdPG5T1lWo/KtBfOpl4ip5fHpO91Yjo1zfRst1SWSdanmmJaZX2TJcYtLpuW8hSVTVMeW4mJ5f2YI3Fz2TIS93rLNguXmD5VngOYhEtZtyy7itssWp+gT+ZpgEpwz5a76DMBbdlulvZl2y2RLVd529nKtkslT49JTQHZfhXry+4i9SX1YarvIqm/xNiKZWf7mWL+GZfwDAjiUOZ/cN/pt4bqYx5f8sO86S91eqYh69ZEmf/s5HkhhVevfGrhlpYFRzbfl0McZVh+sLP+p1tDo7tbzo5usuAr/fHatxHU1biRJwzl2mfdcleYp2e2d8Pu/W9pP7xt9W0HT3VT5h976obffIqH7x0cuKh0zMcd76h9m4UScy5uIMcBOT4488dYZduXPQdTnkXmgF2xDfZDR/RGJ/TFdjgKO+B4dMZJ2BFDsRPOwM44B6/D2/F6fBC74CbsiluxG76A3XEHuuEh7IHHsSfmYy/8EN3xNLJuxmes4e/YH6+mTAOwCQ5Cb/TGYeiDE3AoTsVhGIW+GIvDcT2OxI04Gl/GMbgH/fFtHIsf4E34GU7C8xiCRTgZW1GnN6MjTsV+OA0HYRhOxnCchhE4D6fjItThWtTjBozG3TgDs3EmHsZYPIZx+D4m4I+YiBcwCS3ZzinYDFOxNc5CJ5yNQ3AODsV5OBbn4024AEPwVlyAC3EhLsENuBSfxuX4HN6OO3EF7sM78BjehXmYLtur0VVybJNjnjO5PX+XysFrleyH96Ed3o+d8AHZLx9ED7Nnug3CR9APH5X9cS1G4Tq8DR/DFfg43o8b8DF8Qva/J3E7bsZPcAt+ilvRWp7x1gy34QB8GQfhq7J/vYaj8HWciLswAndjNL6JCbgHkzAbvfDg2AYWBeRSstJ20fk2Y/uFp7RhrCEX08YQF9DAYjv5CLmQbB1ImwRZad/YhDnKNH/bjavY1nGE6U2oG29s81iGB8lu3sb2D6cJfAZZ3Q7iFdTAIpzc6LyVxTLMITsN4T3I68i7VO0k1hMbWLiT08irybvIJ8mlyvybGlgkkTN9KAPmqdpTPCfxjJidtKXgDPIC5lmHsCwOwg1kdXtLEnnBZMrHOnmd19pctKQlLWlJS3Wb6i3+r6Pn/72mGv/vJP1HOnJTcjj5WvpHNlhXjCVnRKTMCIvRGWLIir+kVfeFp5ITWJ7YzdTWcFY+65B81n7ycqUvuqnps5IidDrWNwwMn2v4vEY1+DxnKz4z0UIVn5K5wAAM82yk3zoqOTFe5sl9B5nHcuqYW5k3U6ZLzZ9dL2Wxkhg8UWLwWFyhlKVZpbJEztBHxhpKI20ndvVYHgeZxz0TKsTZMfL/xeryqp7fnyTPUi9UthllHQuvKWWT5f4gOfN3JFn9HPUhDWofowcZ5pee3NvokYVLVo088VNEzJTrCmiLMswfERDpeDqk2K1xklPBor4lb7LPGGLfd+cff+uPH+8tnnt3h9bb0qdcXX3MTYzI/KKhgU6zXFem73YYtLJxwYVzPIvZsJ6Oexakl7qEvLEibfSLt7/+wpHq2wCqbkuofdvAK4aY+5k=
*/