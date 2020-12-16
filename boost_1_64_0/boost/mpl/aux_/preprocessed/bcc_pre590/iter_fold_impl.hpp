
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "iter_fold_impl.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

/// forward declaration

template<
      int N
    , typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl;

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl< 0,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef state0 state;
    typedef iter0 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl< 1,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef typename apply2< ForwardOp,state0,iter0 >::type state1;
    typedef typename mpl::next<iter0>::type iter1;
    

    typedef state1 state;
    typedef iter1 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl< 2,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef typename apply2< ForwardOp,state0,iter0 >::type state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp,state1,iter1 >::type state2;
    typedef typename mpl::next<iter1>::type iter2;
    

    typedef state2 state;
    typedef iter2 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl< 3,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef typename apply2< ForwardOp,state0,iter0 >::type state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp,state1,iter1 >::type state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp,state2,iter2 >::type state3;
    typedef typename mpl::next<iter2>::type iter3;
    

    typedef state3 state;
    typedef iter3 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl< 4,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef typename apply2< ForwardOp,state0,iter0 >::type state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp,state1,iter1 >::type state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp,state2,iter2 >::type state3;
    typedef typename mpl::next<iter2>::type iter3;
    typedef typename apply2< ForwardOp,state3,iter3 >::type state4;
    typedef typename mpl::next<iter3>::type iter4;
    

    typedef state4 state;
    typedef iter4 iterator;
};

template<
      int N
    , typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl
{
    typedef iter_fold_impl<
          4
        , First
        , Last
        , State
        , ForwardOp
        > chunk_;

    typedef iter_fold_impl<
          ( (N - 4) < 0 ? 0 : N - 4 )
        , typename chunk_::iterator
        , Last
        , typename chunk_::state
        , ForwardOp
        > res_;

    typedef typename res_::state state;
    typedef typename res_::iterator iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl< -1,First,Last,State,ForwardOp >
    : iter_fold_impl<
          -1
        , typename mpl::next<First>::type
        , Last
        , typename apply2< ForwardOp,State,First >::type
        , ForwardOp
        >
{
};

template<
      typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl< -1,Last,Last,State,ForwardOp >
{
    typedef State state;
    typedef Last iterator;
};

}}}

/* iter_fold_impl.hpp
rcgIdw/02+Lwi2Haru2rurhwamU+9sjcMmzOuJgLnIFcX5zn0zLdOsaWK7xME2NeXzjK9+zw8rX3HtMbyt9l99FdZj3pg/BeltldCO+Jzhtry5aVWRJXPWOmHy6Hy/+Cul9gXXMsgrH9MD8L7rovsSg3+9Mhyp1FuTMQyqTvpxq5RS2lYv5c7fw78pmDuwwRR8Tzkcj9X8rp8I2ZZeSAPg9bH+/5vSb+MtcPL4If4Z6dKndhu2yXHohZF9t6IOpzQdvXRWFe5kRb3zJf9ryzdcXzIt5j6xDq5Mp4pGVYLv9wI06I9K3wKfJXZ3yF74HkHj1kHd2z1/Aew/oNGdFv8KBUVH48fgg+4frNme6eEyJ9Hnwu41tV6ZrCiT9dL/8H3ShHUmLkHtJ+mUNVytFj8KDeqaOSB4zsVeG9IpZ9HKcPkI2JkWVcLn3WI414y/ZvzKMzT11PjCzbr0WveqVXkF8g25zx+B1ZVc+kWTk3uh4JSBTyukG4j7QnPGQ5IHvbHrIYzxq/QA5Tv3zeR98atu+wZpHpfye63CP9eNvX37zblyv99c0i6/57mUdUpt+n1yBMdgaY8xjx+TDp2CCy7judFJnfv8uXdK/0TO3H5fsF80VX3ddvEF73tixPeMjyA74kesoSv3+Tjg1i6N/NI2X4UcadShkGD+k1aPjwAanDRwzrN6hP6oTsvIw4ZNgQ1gYKgmyDDhk2N49sAz9L/48mA/RMLOVQMZacafzr5+IBa6ZLx/Y9OTLvvkbQA1HS/SW6gPmvbA+160RvDztO9q6L1VHkiVcfRK8Lu0zGnBIpQwBlsjXd5WunV8oISIIx55eUSfewMhlRzy6T8HXerlMiz2acgVTKKI/ZmUzPjeu53+m4K43fa/P7+LB0151Kv4Scj12GEJK9kQymm10g+1sTskuqX4NVpLtX9K9zH0TK37GHWSdybey9f8e5T+Sa214z87prjjmEfvY6M09nIxyGPG1knsxTGIv5iaFfVfMMptJHqPN5S/jeauqwzMLinCLXHH4T5TweIcC6P0IKJ1PlxJt5MZ1zqSh3rg3dvqzov+8hlsUDCLVQFm0q00AFFxbA52BhtfVbz07HnnM71qVTws/j8RnBiEz6mW6k32+zv7tkXUyfeQc4xy4X4p46E4ysGBeyM1LNJgmfP8VQJqaNOPpAMef60Z4hl7v3Ylx+qjLyizz34ljP9jkR7m1loOxLWqo/mvEmD5brORfuzMuw94N5TVIuqtyDL5jI9Uj4nnsr2ixlWV0LHo2yWp5lyqpit0udMsaxN2TKi/3dsefFa6b7he15TeC9lf2X1+x7G3vsjzWJogMSI5+L2H2de6QH+L0yk1qMJt79lfv3OfnTU3PR5bLN9XLX9eyMvDSN62B4XKb46f8/2132B3he1Pu91Og+u7x9ZEX3YeX9Pma092Tjf2/U+/3Z6L6/vN8zjf4+qff7ttHez43fN1q879XOCcj120e9EDxy/g8bmm16s1mLW/t3i+5b7FUTz/7FiTedsS3v0Oyv126Zs/aE+62oPtbON+//FuzMnf9t+akvvXFNjyatPuz0dPT3iz8z7+fO77a2fUlHa9K1XVvsfbRN4x7RfKb9eu8jy74amiPPf6vcSX4dd3ZZfP5PW1hzaQtrHm1hzadPqgW0hbsQvNhSm6slltpafcAytlSNbfcVtIV7HW1fXQ+iKowt1Z2W2lCVveybwG9oe/fv4GrayL0d/B24BjzCp7Z464FrwXPAu8FzfWqDtzt4L9gHvI+27pAGz3DjbLfJp86ptjGfJ1uaz1PABubcsdqqPA3sac5uqC3U08HJ5kyH2vo6A1xgzmipbePW4B2SFngn2BY=
*/