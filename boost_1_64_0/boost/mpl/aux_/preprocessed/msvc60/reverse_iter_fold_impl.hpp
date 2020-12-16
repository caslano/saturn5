
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

template< long N >
struct reverse_iter_fold_chunk;

template<> struct reverse_iter_fold_chunk<0>
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

    /// ETI workaround
    template<> struct result_< int,int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
    };

};

template<> struct reverse_iter_fold_chunk<1>
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
        typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
        typedef typename mpl::next<iter0>::type iter1;
        

        typedef fwd_state1 bkwd_state1;
        typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
        typedef bkwd_state0 state;
        typedef iter1 iterator;
    };

    /// ETI workaround
    template<> struct result_< int,int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
    };

};

template<> struct reverse_iter_fold_chunk<2>
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

    /// ETI workaround
    template<> struct result_< int,int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
    };

};

template<> struct reverse_iter_fold_chunk<3>
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

    /// ETI workaround
    template<> struct result_< int,int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
    };

};

template<> struct reverse_iter_fold_chunk<4>
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

    /// ETI workaround
    template<> struct result_< int,int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
    };

};

template< long N >
struct reverse_iter_fold_chunk
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
};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_step;

template<
      typename Last
    , typename State
    >
struct reverse_iter_fold_null_step
{
    typedef Last iterator;
    typedef State state;
};

template<>
struct reverse_iter_fold_chunk< -1 >
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
            , reverse_iter_fold_null_step< Last,State >
            , reverse_iter_fold_step< First,Last,State,BackwardOp,ForwardOp >
            >::type res_;

        typedef typename res_::state state;
        typedef typename res_::iterator iterator;
    };

    /// ETI workaround
    template<> struct result_< int,int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
    };

};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_step
{
    typedef reverse_iter_fold_chunk< -1 >::template result_<
          typename mpl::next<First>::type
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
      long N
    , typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl
    : reverse_iter_fold_chunk<N>
        ::template result_< First,Last,State,BackwardOp,ForwardOp >
{
};

}}}

/* reverse_iter_fold_impl.hpp
uB7j8R6chvdiOlbhXHwAL8AH8VJ8CBfjRqzETXgHPoIbcTNuxi24A7fiO/g4/oZP4HH05Tb0wycxCJ/GYHwGo3Anno3P4Qx8HmfjC3gxvoiXYg3egK/gLfg6rsc3sAbfxE/wLdyHu/EbfAebsi3fQ1/8ALtjLYbgR9gXP8UR+BmOwi9wHH6LKViHefgdFuF+vBC/x4X4A16NP+IG/AkfxIP4CP6Cb+KvuA8PYXNvrqljS/wDe2ITL7YfNsVw9MGp2BzPRV+ch8fhRdgCr8fj8WZsjbuwHb6K7fEt7ICfoj/+gp3RohwnMAADsCt2xSgMxjHYE6dhLyzEE/Ei7INLsS8ux37Wz0decg8L/06R3ye+9LI8/5Pn+TvhdgzBHRiGz+AgfBZPxp0Yi8/hGHweE/EFnIovYiq+hBfiy7gQ38Xl+B7ehu/jeqzFLfgR7sBP8HPciwfwUzyuCdsfW+MX2AW/xFD8CgfjPozDr/EM/AbT8Vucid9hDn6P8/EALsUf8Fr8EdfgT7gRD+Jm/AW34CF8Fn/D9/B3/ADp0JJabIoH0Qt/w2ao/F41x1j0xTHYAtPxeJyJrXAutsMybI+V2AHvwE64Ff3xJeyMtdgFf8EA9GIbBmIX7IrdsRsOw+4Yg0GYhD1wKgbjBdgTizEEF2MorsQT8XrsjbdhH7wL++HjGIZPYzh+igPxEEZgF/bjQdgdI7EHDsZIjMKTMRpH4smYiMNwKo7ADDwVV2AMVmIs3ocj8RkchbswDt/H0fgJnoZ78XT8Bc9A5ffpTGyL49Ef47ErTsQ+mIiDcRJGYZItL4bcxyP398Q45MWYI9/X8rA9FmIXLMLBOA+H4wIcjRfiNLwIM/ESnI+X4hIswRtwId6Ji3AdXobbsBR34FJ8CZfhl1iOdbhCvrddga3wauyDqzAWr8FReB1OxNWYhtfjDLwBL8EbcTmuwXK8GVdjJT6It+EmvB0l34Hc08M+oLx2yHdwijftwVOxF8Zgb4zF/jgS92MFsU3KuVvKOQHlPs/65529cAJ2wgTsihNxME7CoTgZx+MUnIxn4WxMxrl4Nq7Ac/AqTMFbcRreiefiOkzFhu+Jcl8O+hOO3xMHyPfEcOyIA1HyI8j9NGxrWU6dH6Gj9EsAdsdADMGu2Ae7YQR2xyEYhCOxB47BYByHPXEa9sLpGIKFGIoX4onSngSL3CeDidKe5hgn7ekveSkGYCcMx+4YgaNwEMZjJCbgYJT+4V4Y4/7pK/3TT/onDK35GupkudtlOXW+hqnSPynYA6fhIDwXh2MqxmAaZmAmrsIsXI0z8AacibfgLHu93J9iXO9pUu9YqfcMqfdMqXec1Dte6p0o9SZKvZOk3iSpd7LU69dU7j2Re1KUek+12MdmuEs5z4F3YzeswlB8AMPwQYzDh3AsPoxz8RFchtW4ErfgbfgYrsMncCc+ibX4NO7FHfgzPoN/4LPYicbtxEB8HofgCxiNNZiIr2ASvooZ+BrOwrexGN/BhfgeLsf3cR1+gPfjJ/gs7sFduBffxU/xI/wMf8Yv8Hf8Ss77fI3D8Bscid/i6bgfc/F7LMQfcAX+hFfjQbwHf8YH8Rd8BA/hy/gbvo5/4JfYlO31PXphUy+2D/qiD56AzbANHocDsQVG4fE4AVviFGyFyXgCpmIbPB/b4hxsJ/tFmkXuU8GJsj8eh0myP3aS80n+2B7V49+djD0xFnvhKAzFM7APjsd+9rw/cu9Jw3ncGIe8P/Nlv1+A7fEiDMRi7I8X42C8FBOxBKfiQszFRXgRXoaLcDEuxTKswmW4A5fjh3g5foXl2JT2rEBfXIkt8QoMxQqMwCtxCF6N0XgNnoLX4ki8Hk8=
*/