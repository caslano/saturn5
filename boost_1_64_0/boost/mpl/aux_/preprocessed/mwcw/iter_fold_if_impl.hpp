
// Copyright Aleksey Gurtovoy 2001-2004
// Copyright David Abrahams 2001-2002
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/iter_fold_if_impl.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< typename Iterator, typename State >
struct iter_fold_if_null_step
{
    typedef State state;
    typedef Iterator iterator;
};

template< bool >
struct iter_fold_if_step_impl
{
    template<
          typename Iterator
        , typename State
        , typename StateOp
        , typename IteratorOp
        >
    struct result_
    {
        typedef typename apply2< StateOp,State,Iterator >::type state;
        typedef typename IteratorOp::type iterator;
    };
};

template<>
struct iter_fold_if_step_impl<false>
{
    template<
          typename Iterator
        , typename State
        , typename StateOp
        , typename IteratorOp
        >
    struct result_
    {
        typedef State state;
        typedef Iterator iterator;
    };
};

template<
      typename Iterator
    , typename State
    , typename ForwardOp
    , typename Predicate
    >
struct iter_fold_if_forward_step
{
    typedef typename apply2< Predicate,State,Iterator >::type not_last;
    typedef typename iter_fold_if_step_impl<
          BOOST_MPL_AUX_MSVC_VALUE_WKND(not_last)::value
        >::template result_< Iterator,State,ForwardOp, mpl::next<Iterator> > impl_;

    typedef typename impl_::state state;
    typedef typename impl_::iterator iterator;
};

template<
      typename Iterator
    , typename State
    , typename BackwardOp
    , typename Predicate
    >
struct iter_fold_if_backward_step
{
    typedef typename apply2< Predicate,State,Iterator >::type not_last;
    typedef typename iter_fold_if_step_impl<
          BOOST_MPL_AUX_MSVC_VALUE_WKND(not_last)::value
        >::template result_< Iterator,State,BackwardOp, identity<Iterator> > impl_;

    typedef typename impl_::state state;
    typedef typename impl_::iterator iterator;
};

template<
      typename Iterator
    , typename State
    , typename ForwardOp
    , typename ForwardPredicate
    , typename BackwardOp
    , typename BackwardPredicate
    >
struct iter_fold_if_impl
{
 private:
    typedef iter_fold_if_null_step< Iterator,State > forward_step0;
    typedef iter_fold_if_forward_step< typename forward_step0::iterator, typename forward_step0::state, ForwardOp, ForwardPredicate > forward_step1;
    typedef iter_fold_if_forward_step< typename forward_step1::iterator, typename forward_step1::state, ForwardOp, ForwardPredicate > forward_step2;
    typedef iter_fold_if_forward_step< typename forward_step2::iterator, typename forward_step2::state, ForwardOp, ForwardPredicate > forward_step3;
    typedef iter_fold_if_forward_step< typename forward_step3::iterator, typename forward_step3::state, ForwardOp, ForwardPredicate > forward_step4;
    

    typedef typename if_<
          typename forward_step4::not_last
        , iter_fold_if_impl<
              typename forward_step4::iterator
            , typename forward_step4::state
            , ForwardOp
            , ForwardPredicate
            , BackwardOp
            , BackwardPredicate
            >
        , iter_fold_if_null_step<
              typename forward_step4::iterator
            , typename forward_step4::state
            >
        >::type backward_step4;

    typedef iter_fold_if_backward_step< typename forward_step3::iterator, typename backward_step4::state, BackwardOp, BackwardPredicate > backward_step3;
    typedef iter_fold_if_backward_step< typename forward_step2::iterator, typename backward_step3::state, BackwardOp, BackwardPredicate > backward_step2;
    typedef iter_fold_if_backward_step< typename forward_step1::iterator, typename backward_step2::state, BackwardOp, BackwardPredicate > backward_step1;
    typedef iter_fold_if_backward_step< typename forward_step0::iterator, typename backward_step1::state, BackwardOp, BackwardPredicate > backward_step0;
    

 public:
    typedef typename backward_step0::state state;
    typedef typename backward_step4::iterator iterator;
};

}}}

/* iter_fold_if_impl.hpp
Mf6sUdKHv6d/2+/YmcduPe3zO57ICH5Omv34wtCNV/OMS1MfltpZvXe3jkv7WOPItsJe8BPYF34KE+FncBL83LQXvkv62kifeS/8kt08+0udBFvBk6H7vlFIqe4brPuawETd11H7UnWCnWFnmAC7yI4Y8/550nOq9Jj3YTpG6TkWtoeLpe94pe8EOAgugxPhiXAqLNG+ZqfADHgqXALPgCVwueJPDVNfDkxR/OFwrOJfpHTkwZYwH0ZBF9wXHg2TYQEcDwultwzx9MdA6W0DV0vvwdI7Ae4JJ8KucBLsDSfDwXAKnABTYSqcBtPhdFgMZ8Bj4Sx4BpwNV8LD4PXwcPggnAMfgWnwNZgOv4Lz4Dcww1se6p+Bd9uUx2naT3A5bAPPhNFwBUyE58Bh8Fw4HJ4Hc2ApLIbnw1PhBfAyeCG8A14EVR7qoyHtNuVxqerj5Yr3CtgHXqn4r4Zj4DVwErwWeuu59O5pU8+/Unl8DZvBb6B3HKjuG2HzvM2WPYfBtvBwaPiGYRI8Eu4P02C1vnLpS7DR11X6usE9YXfYE8YqnT1hPOzl1ac+EDjURt8I6RsJW8ADYBwcJT2j4WA4xqQvXfoG1NLH39IXLvuawu6wGewF94T9YIT0pSOrpC9T+sz7132n5/t7PVc/wC5wGxwBf9Tz9bPqfxU8DP6i5+BXbzmpPwIm2dg9T/U2A3aEmbAbzIL9YbbKbb4pH1w70NdH+vpKX5z09ZO+/tI3wKRv4w70jZe+A6UvRfoOkr6DpW+Cudx/8K+vpfRFSl8r6WstfW2kL8pc7jvQ9570VcBY+IHq44fS95H0fWx63sqkr73N8/ai6tFLsB0sN91Xrvua29y3RPcthU3hCabfowrdF2/ze5St53s+jIYLYBzMgf3hQtWjy8Lkn4YPSE8kPFt6Vqi+ng1j4bmwDzwPjoalcDy8AE6BF8LZ8CKYAS+Gi+AlcDG8FJ4EL4OXQ8SYy30FvAeuhOvgVdCTTvm14TSbdG5U/jwKo+FjcCh8HB4CN5nyq2QHeu6TnvXSc7/0PCg9G0x6Kneg5w7puVN6yqTnbum5R3pKEI+/FUrPXrBIegYp35Pg3nAw7AyHqhz2g/3gMJgAR+r9cYDKIxlOhKPhDDhG75HxcA480PQ9UCE7Rtj8/nRXPYqFzWAP0/6f3WAvuC/sDfeH/K3nSz5OyPlaz9cher6m6jmdBnvD6TARzoBD4KHQ+7u0A33tpa+D9O0jfR2lr5P0dTb/LknfSBt9SdI3GPaAQ2BfOFR69oPD4DCTvpgq//b9oXz7U/kWZtgHZN/u0tvI9F3gkr4km3J5TfXsdRgB34CRcLPeU2/pPfU2HATfqXnf4Ivz/556W+X9DmwHt8Dq+yp03z42972v+ypge/iB+fn9xf93c5zu66f63V/1eQBMhPHSMwtJl56DpacpnCg9R6m88mEMdMGe8GgYDwuVv8VwDDwWjoeLzb9X0r/EpvxWqfyu13O3Gg6EN8Ej4Rp4LLzZm275i+ABNul+SuX3NIyGz8Au8Fk4Aj4nuzYjZdLDN4ehx33989Jzl+y6B0bBtbADvBd2h+vgAPggHAM3wEnwETgHboTZ8HGYCzfB0+CT8DL4NLzabR+8xW0XLIPPwxfhC/AV+BLcDMvhB/Bl+AV8Ff4MX4PuRLwBm8A3lU8xYfLpyNfD9ALj7yilb6YpP2N03Rib/LxB+Xmj8vMmOBzeDJPhLTCqcXDzdNYEMFenqLLh5usMrcd6n6sqQzN/5/lKyxyeXbbmZ/Q063yeqsq/d+3P3t/tuvU/U74LbJ7Pv3UN0AX3hoctR9Ygm5AKpOm68LB4ZCKSiyxH1iBPI18hEffx/0g=
*/