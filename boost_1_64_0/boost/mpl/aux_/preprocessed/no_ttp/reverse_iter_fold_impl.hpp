
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/reverse_iter_fold_impl.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

/// forward declaration

template<
      long N
    , typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl;

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< 0,First,Last,State,BackwardOp,ForwardOp >
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef fwd_state0 bkwd_state0;
    typedef bkwd_state0 state;
    typedef iter0 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< 1,First,Last,State,BackwardOp,ForwardOp >
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    

    typedef fwd_state1 bkwd_state1;
    typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
    typedef bkwd_state0 state;
    typedef iter1 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< 2,First,Last,State,BackwardOp,ForwardOp >
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp,fwd_state1,iter1 >::type fwd_state2;
    typedef typename mpl::next<iter1>::type iter2;
    

    typedef fwd_state2 bkwd_state2;
    typedef typename apply2< BackwardOp,bkwd_state2,iter1 >::type bkwd_state1;
    typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
    

    typedef bkwd_state0 state;
    typedef iter2 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< 3,First,Last,State,BackwardOp,ForwardOp >
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp,fwd_state1,iter1 >::type fwd_state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp,fwd_state2,iter2 >::type fwd_state3;
    typedef typename mpl::next<iter2>::type iter3;
    

    typedef fwd_state3 bkwd_state3;
    typedef typename apply2< BackwardOp,bkwd_state3,iter2 >::type bkwd_state2;
    typedef typename apply2< BackwardOp,bkwd_state2,iter1 >::type bkwd_state1;
    typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
    

    typedef bkwd_state0 state;
    typedef iter3 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< 4,First,Last,State,BackwardOp,ForwardOp >
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp,fwd_state1,iter1 >::type fwd_state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp,fwd_state2,iter2 >::type fwd_state3;
    typedef typename mpl::next<iter2>::type iter3;
    typedef typename apply2< ForwardOp,fwd_state3,iter3 >::type fwd_state4;
    typedef typename mpl::next<iter3>::type iter4;
    

    typedef fwd_state4 bkwd_state4;
    typedef typename apply2< BackwardOp,bkwd_state4,iter3 >::type bkwd_state3;
    typedef typename apply2< BackwardOp,bkwd_state3,iter2 >::type bkwd_state2;
    typedef typename apply2< BackwardOp,bkwd_state2,iter1 >::type bkwd_state1;
    typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
    

    typedef bkwd_state0 state;
    typedef iter4 iterator;
};

template<
      long N
    , typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp,fwd_state1,iter1 >::type fwd_state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp,fwd_state2,iter2 >::type fwd_state3;
    typedef typename mpl::next<iter2>::type iter3;
    typedef typename apply2< ForwardOp,fwd_state3,iter3 >::type fwd_state4;
    typedef typename mpl::next<iter3>::type iter4;
    

    typedef reverse_iter_fold_impl<
          ( (N - 4) < 0 ? 0 : N - 4 )
        , iter4
        , Last
        , fwd_state4
        , BackwardOp
        , ForwardOp
        > nested_chunk;

    typedef typename nested_chunk::state bkwd_state4;
    typedef typename apply2< BackwardOp,bkwd_state4,iter3 >::type bkwd_state3;
    typedef typename apply2< BackwardOp,bkwd_state3,iter2 >::type bkwd_state2;
    typedef typename apply2< BackwardOp,bkwd_state2,iter1 >::type bkwd_state1;
    typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
    

    typedef bkwd_state0 state;
    typedef typename nested_chunk::iterator iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< -1,First,Last,State,BackwardOp,ForwardOp >
{
    typedef reverse_iter_fold_impl<
          -1
        , typename mpl::next<First>::type
        , Last
        , typename apply2< ForwardOp,State,First >::type
        , BackwardOp
        , ForwardOp
        > nested_step;

    typedef typename apply2<
          BackwardOp
        , typename nested_step::state
        , First
        >::type state;

    typedef typename nested_step::iterator iterator;
};

template<
      typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< -1,Last,Last,State,BackwardOp,ForwardOp >
{
    typedef State state;
    typedef Last iterator;
};

}}}

/* reverse_iter_fold_impl.hpp
/cmWEE0Xqo8K6QtdY5+8Iv3lpxHUfbFnLuQ+juznTvXxtv3bse6+ccszlHE5ZWBS9p8p5N1xv2cZC23vPfCOtu7fnve13opngf/T3tc60VLfdbT04V+PfuqrF/YnD3vrzQ82vdEw/aIH6eR3BjYnXHB6ljRM7tuNwGY4Un2/T+J11ojXUeJ1wo7YWeKl6OT7HQslXnOMk3hd5b5dd+yLPTAIe+Jg7IUzsTfGYR80Y1/chIFYgP3V930lvbZO+XSuj2mD7W31GvKdKd+lxHOo1/iB5HMn6nEXdsCHsCvuwVD8EUbjXpyBj+A8PICJeBBTsAjN+ChuwEOYjz/G7XgEf4hH8Sf4GJ7E4/gSPoFX8Umswqfwb/gT/Cf+DDuS96dxMJ7EofgcLsTTuAGfx434Au7Bl/AAnsXj+DI+i+fwNJ63lbN8r2IPjXJ+Xcr5DeyGb6qe+Twr8dpJPPX97ksS731shb/CtviBKn5RLfHflvi/lPgXJf47SHzml+8c+S5SxoeofjuPku08GvU4RrbzONnO4zEIJ2Ao3o8jcSKOwUkYhZMxBqfgHIxGA07FZJyGKTgdF+EMXI4zcT3OwjyMxW04G3fgHNyDcfhjnIevoQHfwnh8FxPxChrxU0zG67gAG0n9VBd8ELthGk7DdHwQMzATs3EJ5uAqXIxrcAn+AJfhq7gc38EV+B6uxk9wHZbjevwSN+A13Ijf4Sb0ZTvkYRfMx/64BUNxK0ZgAUbjNpyO2zENK3a5dx+/Ts8Je94Rrf2O6HyvBnlP9InTDf+u6Ca7uY9NCCcYCbmEIsIZwiVCxW7PfWnP4Bk8g2fwDJ7BM3gGz+AZPINn8Aye4d85NET9vzH55uv/lXr+11X1/HFS330HtkXlvtdS5bm3CdZ64YkR4wyxwwwhgyx1XvHaq7+B+5jkYbilvslXd5ul/it4onY9bWaO2VZPm0NgnEfy7HWVV1tzDxGVefRoex+0TPPDQHKv1MBnphqr6ywlXs7C9Oo6S4nHuG3Z3RmfxYzpxurlnKiuO2OcWVCZ56RMS5XxY/LuaV60bRkvlnFepm5ZxinGw9uyDNW7yotUdfTKPIdlnGWQUPX7josZj6XMezVSbtDa33d8hnkzfK3PA9rfdzzc+r5rqcefJnXpk3G50n5iorUetHo/Ss1IzqS3gMRMY/X7E8I1NprzM6p/ofxMZJKPsn1kGitrnebjVPayjWpsRz+n7eHvtD18pf7zHpZlYqIhM9FsTeOssg8xXSbb6iuVvFanQHyp65zERLJnSJAX07eifYsXGzpPad/CX2zP+cl2M0kaFyUN5rClUcq0u1legpS9vKtate0c64svSl3+VkILwmbCSqVOepJlW2QvTDUZErIzaOLtTrsG1TYwWcsflTyTsrr8zQSaB5gTFji2EWEC4/Y8p6rWXdkWi2QZ1rYOSxPTErKzpW5ZypdVJzX1s5Cu62K16xpd1wVqP0vouu5Wu67XdZ2u9jOVrutoteuq6153W9e61brW6YYFKtMnRDw31jD0u7w2hwKXf2q+N8fls5Mu69p/aymfc+/Gfv54Wofyf+4sivio29NUOL3aQplefHV2lx/FH2++8c6SRr7fPHbadZ30Ckvd8B0/z955x9OfvN/ljt/PjUv6SO+6Ll+7Dth1Hbx23bDrunlLf7yN5DtLvst8CH34HCN1ZslSx7YAO2EK9sCFGIjpOBgzMAwzMQJNeD8uwqmYhfGYjRvQjPmYg9txMRbhMnwbl+N7uAI/w5V4G3lahR1wNYbgGozCtUo6uA5n43rMxA24CHNxOW7ElbgJV+Nm3Ix5mI/5eBC34KO4FZ/BAnwVt+FruANLsBDfw534R9w=
*/