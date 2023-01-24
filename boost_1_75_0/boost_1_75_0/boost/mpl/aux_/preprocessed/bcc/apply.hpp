
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
YjSoz6sAxl5vFIVRv9LNffyBmuAYao5pg9Gkn6UNGyRhP5Vq9TyvDYZULgpj7zDvxFOC8vBie7Ly/qoFRwMd5SBk1y5jEaCD64DDoPrhPrlWC2ubrfUfoze2c0/QRlxF60CoY00pe5F2DzjfBSSneBe6oLKRBcnFfnioJnhoiSjFSvX29Y+GRkjFgKCiHO4/3DuK/5mNGLUTaGHXjrjo/T9Eaxt3xqaGsE3NartnUTs8ppDXkcHdzJ2ZXZndmT2ZWzPbIWJ3Zvstme17Mp0dmU5I7cx07sx07sp07s7s6Mzs2JHZsTOzA95vyezYk9kJ/27N7OrI7OrM7NqR2bVTW7cSG/ZAWJogBwa1SzmlLCzKq5FX6Hq7xThf4PRhXFpr2cda3NH45ZUl9NN4MFGNkmXssX7UKkphaStNlzyoaEbwS8qkjZv/4XRsLEA9rHYe0duCxhOv3fZ+BIGW1QyUM/6OevPLOw95ptqrDM3aqYVnQdOXxj5t9B7SkwLLEJdoBpVE0QhYE2BbpJ9Xkz/vfhCEhqZ2j3UsUKpJShvdivpkxNKuCmTZxEmW9CYb5pjxqSKVieuHzijVFIZWdaR3GaAvA1I9SmhhU+O/YtyIPHI8du0xM7MACymCmskgrpsram0MdRnSBl4taK0ta1wY87LXKBMYzfu8Zhi4rZZdPwf8UUgUH/JNQTBmvRKUVB9OAry47UJUCPbASZk6
*/