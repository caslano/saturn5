
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
wflwEDwOjoULIuXqORKOdyj3BJV7kspdpHJPVrmnqNxTYS5cbBy3OpXb3+G4nal2Pwt2gmfDDHiOsc5Jg/LvpPzmOifnK/8FOt5LdNwuglvDpXAEvETl8Xc9v3GNU3nkw16tXax6jodpcFfVcze4McyDOXB3uD/Mh0VwT3gwnAhPgwXwQjgJXgP3g7fA/eEDcAp8BR4AP4MHyr5C8XKPnuPgUtnZHZ4rOwep3tuqvw+GPeF2ar8hcADcHg6GQ+FIuAMcB4fBiXBHOAUOh2VwBPTDkfBwuBOshznwRDgKngl3hhfBXSLrc+k5UM+HmbZ1Wfxq10NkZ7XatUbtGoCbw1qdZzPgBHioeV1R+cMc+ufhKv8I2A/OUnlHwi3hUXBbeLTO3zrjvGtSueurLPO8G2ns16L9OrW6n56JQI9W90Pa2C8rJfkY5PqjWFvmqP9PDHJLbkc3DtmNQ/7b4pCXc641IylHp3qykMnILORy5GHkXaRzHX9DChA/shhZhnyIdD6GdVKQyUgAORdZhjQjqbNTPdnIZKQOWYosRz5EUudw3iAFSD1y0xw3xtlNbnKTm9zkJje5yU1ucpOb/s70V63/R3TTH7L+nxXD/02aJxIDM1Sx9bVIcP5OMfwtmxkxZIopTCTeI5l1yMLxtg2y4RLZcKFsWLS5aQMmJLjWnD2Ob4X0ozwq3sqnmPvXpPelcAxjphlfU1sZit1RIyQY82vasKERBxQqrbCsqpqXKiq9HJIa5zZSbNBNmc6xQSmKmy+R7YVqs7otHG3H9MTj1WR3q3Y1bBG2y12/y42VSD5W4otgrMRxJ+x25kkbH/zb+IYDfvgoY+3GvzdWYqZH1z1Y67DOT6F8EFNhOiyWb7ZEPgkvHAhLYQ4sg3vAaXASLIcHwQpYCQ+Gh0AflH5d87gWOuifIP17yHeVDzPlm8qCe8F9YYHKnwSr4T7wGDgZLoL7wvPhfvJh7R/xnenaB19z8J1lSf9Wqv/28u3sIF/uMLijfE67yuc0RT6nYvk8/PI5zYA58kHtLB//aHg7zIVPy1f3PBwHX4LjzW+56PpTIjvNb2B0k53dZWc63AyuD4fC3vKVbSQfVIbs3AQGr6NwaTvWh/m/+GRcf4zrj/m7/DHZ9diPlCOL6l2fiJvc5Ka/L/1V7/+XFQVW+f1/69n/uzRP5P2qTD13765nyF3D72/1i16DfBqrPpdWB18yKaEsX2mgNKFnSevZ0en79edK70GK6y/Xs2uDo17pTOL7pU5rCGSsFv5enr4JCw8cSF37x75fWlZU60vkXaJ47/vURr+zGGnv5bLhULV3jd7Xa9g4jg2FvJvKEWzvvEv43T1KK/SFv2ev42LaaK7LHlayntZaTYOv0CfyN4m8j0NxvPSVhE2WDUW+aVHvu/pKK2Ped43YxrZfxllzDUcGdbPucY/Q9tW27Zds2ymbRm9n27YPtG0vsG3fYtt+17bddbPo7eGRbeM7se5cyD92LsT5+7H/vDmSTUus39e984JNdv521BdnzD7v1S9L+j3y986RjPPo/qD7Ro4tXnemEaeZBWfB7eGRMBcepbmBo401rhtU3kEqz1zjukRxsF7YBZbCPnAa3NzKA7eF0+FO0A93g9VwH1gDS2AAlsPayBq2uvbrnpBjW8M2XXrNuO7+cD04AvaCozWXMAX2kZ4N4RGaW5gN+8Oz4caac9lMcxybw7vgFprjGABfhlnwG82xrIADYRr2ZcP14DawLxwUicvV/UP3lRxbXO4+Oh6TYbrmfrbR3E8enAIL4QGyvxDWwKkqn4JD137dE3KQDfj3Nyp/e5U/FKZpLmh9zQVlaC5omOaC9tBcUAUcqXbaCZ4=
*/