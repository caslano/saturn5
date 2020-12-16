
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "reverse_fold_impl.hpp" header
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
struct reverse_fold_impl;

template< long N >
struct reverse_fold_chunk;

template<> struct reverse_fold_chunk<0>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename BackwardOp
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State fwd_state0;
        typedef fwd_state0 bkwd_state0;
        typedef bkwd_state0 state;
        typedef iter0 iterator;
    };
};

template<> struct reverse_fold_chunk<1>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename BackwardOp
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State fwd_state0;
        typedef typename apply2< ForwardOp, fwd_state0, typename deref<iter0>::type >::type fwd_state1;
        typedef typename mpl::next<iter0>::type iter1;
        

        typedef fwd_state1 bkwd_state1;
        typedef typename apply2< BackwardOp, bkwd_state1, typename deref<iter0>::type >::type bkwd_state0;
        typedef bkwd_state0 state;
        typedef iter1 iterator;
    };
};

template<> struct reverse_fold_chunk<2>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename BackwardOp
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State fwd_state0;
        typedef typename apply2< ForwardOp, fwd_state0, typename deref<iter0>::type >::type fwd_state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp, fwd_state1, typename deref<iter1>::type >::type fwd_state2;
        typedef typename mpl::next<iter1>::type iter2;
        

        typedef fwd_state2 bkwd_state2;
        typedef typename apply2< BackwardOp, bkwd_state2, typename deref<iter1>::type >::type bkwd_state1;
        typedef typename apply2< BackwardOp, bkwd_state1, typename deref<iter0>::type >::type bkwd_state0;
        

        typedef bkwd_state0 state;
        typedef iter2 iterator;
    };
};

template<> struct reverse_fold_chunk<3>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename BackwardOp
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State fwd_state0;
        typedef typename apply2< ForwardOp, fwd_state0, typename deref<iter0>::type >::type fwd_state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp, fwd_state1, typename deref<iter1>::type >::type fwd_state2;
        typedef typename mpl::next<iter1>::type iter2;
        typedef typename apply2< ForwardOp, fwd_state2, typename deref<iter2>::type >::type fwd_state3;
        typedef typename mpl::next<iter2>::type iter3;
        

        typedef fwd_state3 bkwd_state3;
        typedef typename apply2< BackwardOp, bkwd_state3, typename deref<iter2>::type >::type bkwd_state2;
        typedef typename apply2< BackwardOp, bkwd_state2, typename deref<iter1>::type >::type bkwd_state1;
        typedef typename apply2< BackwardOp, bkwd_state1, typename deref<iter0>::type >::type bkwd_state0;
        

        typedef bkwd_state0 state;
        typedef iter3 iterator;
    };
};

template<> struct reverse_fold_chunk<4>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename BackwardOp
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State fwd_state0;
        typedef typename apply2< ForwardOp, fwd_state0, typename deref<iter0>::type >::type fwd_state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp, fwd_state1, typename deref<iter1>::type >::type fwd_state2;
        typedef typename mpl::next<iter1>::type iter2;
        typedef typename apply2< ForwardOp, fwd_state2, typename deref<iter2>::type >::type fwd_state3;
        typedef typename mpl::next<iter2>::type iter3;
        typedef typename apply2< ForwardOp, fwd_state3, typename deref<iter3>::type >::type fwd_state4;
        typedef typename mpl::next<iter3>::type iter4;
        

        typedef fwd_state4 bkwd_state4;
        typedef typename apply2< BackwardOp, bkwd_state4, typename deref<iter3>::type >::type bkwd_state3;
        typedef typename apply2< BackwardOp, bkwd_state3, typename deref<iter2>::type >::type bkwd_state2;
        typedef typename apply2< BackwardOp, bkwd_state2, typename deref<iter1>::type >::type bkwd_state1;
        typedef typename apply2< BackwardOp, bkwd_state1, typename deref<iter0>::type >::type bkwd_state0;
        

        typedef bkwd_state0 state;
        typedef iter4 iterator;
    };
};

template< long N >
struct reverse_fold_chunk
{
    template<
          typename First
        , typename Last
        , typename State
        , typename BackwardOp
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State fwd_state0;
        typedef typename apply2< ForwardOp, fwd_state0, typename deref<iter0>::type >::type fwd_state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp, fwd_state1, typename deref<iter1>::type >::type fwd_state2;
        typedef typename mpl::next<iter1>::type iter2;
        typedef typename apply2< ForwardOp, fwd_state2, typename deref<iter2>::type >::type fwd_state3;
        typedef typename mpl::next<iter2>::type iter3;
        typedef typename apply2< ForwardOp, fwd_state3, typename deref<iter3>::type >::type fwd_state4;
        typedef typename mpl::next<iter3>::type iter4;
        

        typedef reverse_fold_impl<
              ( (N - 4) < 0 ? 0 : N - 4 )
            , iter4
            , Last
            , fwd_state4
            , BackwardOp
            , ForwardOp
            > nested_chunk;

        typedef typename nested_chunk::state bkwd_state4;
        typedef typename apply2< BackwardOp, bkwd_state4, typename deref<iter3>::type >::type bkwd_state3;
        typedef typename apply2< BackwardOp, bkwd_state3, typename deref<iter2>::type >::type bkwd_state2;
        typedef typename apply2< BackwardOp, bkwd_state2, typename deref<iter1>::type >::type bkwd_state1;
        typedef typename apply2< BackwardOp, bkwd_state1, typename deref<iter0>::type >::type bkwd_state0;
        

        typedef bkwd_state0 state;
        typedef typename nested_chunk::iterator iterator;
    };
};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_fold_step;

template<
      typename Last
    , typename State
    >
struct reverse_fold_null_step
{
    typedef Last iterator;
    typedef State state;
};

template<>
struct reverse_fold_chunk< -1 >
{
    template<
          typename First
        , typename Last
        , typename State
        , typename BackwardOp
        , typename ForwardOp
        >
    struct result_
    {
        typedef typename if_<
              typename is_same< First,Last >::type
            , reverse_fold_null_step< Last,State >
            , reverse_fold_step< First,Last,State,BackwardOp,ForwardOp >
            >::type res_;

        typedef typename res_::state state;
        typedef typename res_::iterator iterator;
    };
};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_fold_step
{
    typedef reverse_fold_chunk< -1 >::template result_<
          typename mpl::next<First>::type
        , Last
        , typename apply2<ForwardOp,State, typename deref<First>::type>::type
        , BackwardOp
        , ForwardOp
        > nested_step;

    typedef typename apply2<
          BackwardOp
        , typename nested_step::state
        , typename deref<First>::type
        >::type state;

    typedef typename nested_step::iterator iterator;
};

template<
      long N
    , typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_fold_impl
    : reverse_fold_chunk<N>
        ::template result_< First,Last,State,BackwardOp,ForwardOp >
{
};

}}}

/* reverse_fold_impl.hpp
Zrg3vAX2gbfCw2E5PAreBk+Et8N0eAecBOfCIngnnA7v8j/HNM+i38zz6vFPSFO+DhHyuS3lVdnyId8aAyhQXr35KpSvhUM+xi7l4282ueHz1Vjlhs/H4BU5H/ckv291H+m6d/fe955jsK77YXp/OlzvT0fAbvLz2xMO1/vlCNgXHgUnwpGwAI6C5TAN3gWP1nviaPgZHAO/hWPhb3AcXA+PgZ0UT7gLPE796HjYE07Q++JEIxeeAMfBE+Gx0AVdMB3mwAx4EZwEL4aZsAxmwWvl/3cjzIEPwWnwaZgLX4T5cAUsgDPNemcddvWkEXXR+bX0qozs23JEZcC/pft59phL6fytDyyua3x/l+LKxvd5Ka9rPL+XFXWRfV9mVsbu/zKX71RWRh/zuLoyel+YmsqAP8z6Ssqpi+AXszDgG7P7wg3zj0ld2PB4yK2+t/vKjDd6DUSn72OPjZy7MOA7M2Nhw/xnjvje6kMDF0bnRzN/4ebpS7N6YWR/mtqFdp+apk/E5lcz0Vxj0lzSclIdqfMP6EhKJ80gzSdVkz4lrScl/0gbklJJ6aTppNmkStJ7pIS1tD8pjTSdVE5avjbuqxM/4kf8iB/xI37ED+vRqPH/cnMmbXj8P2PzOp1J/rWlrCeYXd8otqiY2BR8fppZkx3F51ggZ+RnZRRmuchQ5LHvfzQpQfYzsu/XPEAiaQfSmZ345xXPWvaoQUe6JmGFV5g5le9HYYfrW0c/nTKmZZ/mty36o51siyy2nMUkrBJsMcFrpM+p0qeEdBZl9fLqM54WPGY/E5LchT1PDPaadd598Wz2wGV6HVwg+4l7SOcgq9pJlisjNyejKMROk/93sGVV3XKyXMUFilEW+Awb6oK8BIttG+v56BbYr8/oitm4+cimb1P5EOynttlXbVNR7aQvfSGK69XO3j58yd5GWZLZTTJTSLVJ5A+RmZmbnZFf4o7imlivd6oM8K6WzR7rOEzkIOfV4PKzesdi2/Z5W3ubBtlOy0bLW+fs/IDtwyfk8/g26Nrs4y3Ha0Qi+4bzPLoRK6ijbNV0vqijvW5PqW6Hqm4Hks419jIhdZuSXZwQjT2irW42W0j6le265crG/hLJvtAUYu6j1xxku/i25A+JQr7k+eWbe7sw26vPWrV1saV/y4bGc/6Uyc/f6d+2tpq1leZDm3j1vQ1eYNrKpi/9el8X+wJ4dU0Op6vsaY5fxXeD4oGe38nu56G6+O1mEq1xIy025pmFOQZeG3rdD5NzM6ZY92i09rnawHme1S5SfY7msNu7omRmQVa2v7928+ZzFbjt+1wkbB1qX3aIiWW4KqidXNZxn6dTDnY/Md6btZJ1sK7JAHhRJ7OIYJVF/4nx3ny+Y/3XoLip2lt5kvUZjWa7d3MzsC8tKNK962vvoH6ne3m9/j65oCTfNEmwbW16s1C7sr9QuuxNT13NpcjMc0duP9WR5538FqzPP2i1ZWva3PvFnrpH9yBdSekVNpmuQWOGDhw9+AjX4KPSXIeNjMFXoFMSOrikg84n6Vz3LToF2ks62+xr3dJxV7VLd9IP5KuTjnrpiNkvSM8bm+3kuuah1+Bi8yx4y2fbZxm2jho69ohRQ1yTcf6IxYZzepB9X52DjaG7Raht5aV8L7UePbDijKiDnrWeimXyEsd7ou5t9YeWofW/HLnp9cgldGoUbe/UBoH3kh/b2WKn2q7JZS2dr0lpfTph9dkQfYKuiU2P5FahelxlbPvr0cOM47HElL2yU+Q9hGc76HGNsbu16WHZCyoL94ri6O1PBznZVduvCYNF6DNgFjrUhNHBb2IcRVtY61rcOvQ+eKkj1yeMnFht1p/vGGpjvK51aPs=
*/