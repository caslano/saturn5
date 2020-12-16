
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

template< int N >
struct iter_fold_chunk;

template<> struct iter_fold_chunk<0>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State state0;
        typedef state0 state;
        typedef iter0 iterator;
    };

    /// ETI workaround
    template<> struct result_< int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
    };

};

template<> struct iter_fold_chunk<1>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State state0;
        typedef typename apply2< ForwardOp,state0,iter0 >::type state1;
        typedef typename mpl::next<iter0>::type iter1;
        

        typedef state1 state;
        typedef iter1 iterator;
    };

    /// ETI workaround
    template<> struct result_< int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
    };

};

template<> struct iter_fold_chunk<2>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
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

    /// ETI workaround
    template<> struct result_< int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
    };

};

template<> struct iter_fold_chunk<3>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
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

    /// ETI workaround
    template<> struct result_< int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
    };

};

template<> struct iter_fold_chunk<4>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
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

    /// ETI workaround
    template<> struct result_< int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
    };

};

template< int N >
struct iter_fold_chunk
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
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
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_step;

template<
      typename Last
    , typename State
    >
struct iter_fold_null_step
{
    typedef Last iterator;
    typedef State state;
};

template<>
struct iter_fold_chunk< -1 >
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef typename if_<
              typename is_same< First,Last >::type
            , iter_fold_null_step< Last,State >
            , iter_fold_step< First,Last,State,ForwardOp >
            >::type res_;

        typedef typename res_::state state;
        typedef typename res_::iterator iterator;
    };

    /// ETI workaround
    template<> struct result_< int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
    };

};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_step
{
    typedef iter_fold_chunk< -1 >::template result_<
          typename mpl::next<First>::type
        , Last
        , typename apply2< ForwardOp,State,First >::type
        , ForwardOp
        > chunk_;

    typedef typename chunk_::state state;
    typedef typename chunk_::iterator iterator;
};

template<
      int N
    , typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl
    : iter_fold_chunk<N>
        ::template result_< First,Last,State,ForwardOp >
{
};

}}}

/* iter_fold_impl.hpp
QtZpj1z6XzaQdcJeuJX8VHc3rZP5aFDWKY33wM1ONmUrv4DO/WR7Frm6ftJvkGX9jA7rlleca+0vShkfJ59XyXhiYqhpfIuMW+5xHbV+Hi594VnG6dvEYd8fS1CXX7SMb5fxdBmvtZSnjO+3LnOoafyQdTzClOYJjfI+aJ1nmGmeHbZ8WftC2Wubdrll2jHbtFBrXwgybbyMH7bOM8Q0Xi7jafL5BhnPlPFq2zJNaRy3jQ+xpLHTOm24aZ49tnnCwW4/u0LGK2Q8VcZ3WeNcbhrfZx0Ps95PDPoF9xMr+yjTj/drc1fskMTd33QefPHbV23+44Vrr3qh7jO6ez9xV6gyfe/7P+e8f8Mfmn3g9eZj28ccqTLfZ9xrkO8D+Z4IRR/CLjnAIuX5utHoh2OwG47FELwCB2M0DsPxGI9XYiJOwJtwIpbh1bgW4/BHjMdcEp+KczEBV+G1eDtOw0qcga+QvxvxdUxGaRci3wMsW+4jq9uF+Mlzhf7YAQMwEDtib+yEodgZR2AgRmMXnIhdVc8vVko6/jKufn4xQtqfDEdfHIHEY7qct+V8Tjy79sn/lOczz0n+DMTrqIA90QPDsAVGYkuMxVZ4I3rjLGyD/2LvTuCiqOIAjq94ZmoeiFQeiKsiogGigqHibV54oFGpnEtQCASLkpKlmVrSYVFRkVlpYVqhUVlZmVlRWVlZkVlRqVFZGUGaWvab3f+e7goU2vX+n15fZ3Z39u2bZXf/7828ycCzcD62xmuxLeZjOyxGT9yG7fEt9MIPsQN+jt74DXbBX9EHj2JXZFs6X+yK3dAPe2IQ+uFA7IXj0R+jsDfOwgBMwvMwFQMxG4NwIQbL/g7BO7G/tF9FE/mOkO8Obf/u5t97ZP7T7tJ+PaT9+mEA9scQHICDcSCOxlCMxDCMxvNxE4bjZhyM2uscgt44FCMxAtfhMHwch+N+HIHaoW4jcTSOwqtwNH6EY/BTHIueDfk7wDQch0Ycj+txAjbm82EinomTcDhGYiFOxgdwCn6MU7FfY/5uMAyjMAOn4xs4A3fihdiUtorGOLwIL8WLcRVegodxJv6Os7B/U/7O8GaMwdsxFndgHPbg8zAeAzABEzARn0cDvoxJeAQvxSj+IJPxYkzBlXgZlmIqnsHAxhwch2m4AtNxB2ZgS04QuQInYSbejFm4E42ofdln41Sci7fhPNyFOdieN8iVOAPn4524AMvwKvRuxfHGGI1XYwFeo92Oi9CbE5wWYzReiwW4BMvwOvTmx8VSjMZlWIDLsQyvR29+Ad2A0bgCCzAPy/AmPLst523hxXgL3oMrcQ/eip14Y9+GszEf78PbsRzvQP48dHdiPBbgg3gX7sW7sXt7PnswCQvxYbwXK/A+9NOu2YzJeD8W4QNYgQ+iNs/YGkzGtViED2EFPox+fKgWYTKuwyJ8BCtwPfrxgbYBk/FRLMLHsAKL8QfciFW4CY/gE6h9OJdgE3wKW+HT2AE3ow8+g73wWQzGLZiJz+MmfAEr8UUMPpfPYszEl3ATbsNKfBmD+fDfjpn4Cm7CV7ESX8NgvhRKMRNfx034BlbimxjcmfNPMQvfxhJ8B6txJw7owvlBOA/fw834Pv6Ku3CQD+cL4QL8ELfgR/gbluGQrpw/hFfjbtyKn2ADXz4PcTh+hovxc9yG5ejRjfOFcDh+iYvxK9yGe9FDz3lDOBz342L8GrdhBXrwIfsNDsdvcTF+h9vwAHr04LcQDscf8Vo8iNvxJ2zck98aOBp/xmVYhaVYjWf4cV4LjsNDuAIP4w78FVv24nsSJ+FRvBmP4U78Ddv4c74LTkXt+/N6f8Ct6IGHsCH27U1OjwZsjIXYBN/Hptg=
*/