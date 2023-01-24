
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/iter_fold_impl.hpp" header
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
JcWPwLj7igxGit6E5fJ6C+kZruja5HMMVqplWidIfSyhbXg1T9/Rt29mU8IDXMcJb27eXlFUFDIY8EVwyjt9znEzcTb6rRagEyHpivg9CadYwhQIdVRgbI03A2hEXap4q5jUBPkilxFAeYOzogE/CzHIJLEko29ESPNtUzrMuqXYUHI7dxoDx/oq03sbKay/Ws1speQTzIniV3ACuaM4mtF5HTMpgkQnsJ+/Is37QxC6VH+Q3JTgRgOFKt+hrUQe3XF7Y9sFAjfeV+xTCiFrXhPrzQuGPDrmZAaGbip7/MEXU7Gr0rEcgeaLPd59tsFzx8+Hx9oJ2ag8d1959YJKtLF+ziLo1Q5xxsu709UTevLR6APRb7H2bi6bkrXL9lXUstHz0Wx1A9lwWWPhDoGRoRTEeC0m3gK0WxZifZPTbAaCn7aujeWeFB7Z8Z/GifzgMAszveGyhMwlUqd+HZoCzgE1yFYOA7Hq6OOZt+MhqWI1HObSxCaZVsmstsv0M4lgiNoNn9lI9fz1TnDKN1w/nDmqipTZz6SGmWzIhG4839XyRR0/uX/izCfj7Py2g7aDJTVf9GzWW76SVMuheUJ/VxAAtKrhpp8rCEMO7qV8RqCrku+R4y2yOv3t990tKpMXhBHkKMC5c7am3mExcR/Bxc5ax0LPhGBC2nKb2G0avYcexUk/34oPsXo8kWMgRpLXKZwqHOq4Rca6tzW3
*/