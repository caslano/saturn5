
// Copyright Aleksey Gurtovoy 2001-2004
// Copyright David Abrahams 2001-2002
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "iter_fold_if_impl.hpp" header
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
0fYWPH2IPD9YwfjksEeoK2uwC+1l7egrm2PG3wxvv6yAH8rH5egJ22xLR1Z8zlWKvRi3m7YxTnwA2PMKup1MPCH/WQI+D/slYnvsPgj+Hny/0A/f4CuM9/OJwCgdVuInGp+bSt5g3NKV5H/gL0P/OGCvU9ei21xwTvMiK2PcA71I9P5iIXqLI58h1zOUL4SeWugPrx5s4k5Cv+BbI+AdGQYTyWXwkxxJrDNGnY1Yd+JDtD9I+w/xiWbGHDcF2Wdhr0rog/vWXPJnEXkH3QSBn9QGTS82ZpyTgT9DuZ7yIjzGxcIv9fXw8wRlcSNjYMPtjHUG8WVrgk/6VteSE/HLfhe5iD4XF5K7KM8i15PU/fhhXxE8UqcWk/uRR5nH2DnEvrgGcn429M5ahf/D01j43gRf12LPXcTtj5zkhyr0ADyHcg1+sDadPAn8kuXwkwB/KbRDbzFy7qyAb3HNou7i/PgAMc/xR8Dmg38MvPZB+5ZE/Jo+j0M7DbwXOLfnQ7MAO3IcpNTTFke8beH4Gq4rk5fgh/iIk/H6KF2U1ZQkSgyxsIxcUw7umhzw5tKH8jPKXZTbKBtoe24yY1eQ7+nzEnHwAbaqIcas6C6+HX1jTx/wc8gjG9H7rYuJzwL8D5wTp+HvwK6KQib038BxE774djZ9WpB7IXpJwz+i8YsiZKvH523Ig2/+CfrjwP86gA80whP0x6dyHaLuKmNc+JlWCQ14/L6YU1AfEUHuiSSfToYHyo8on1uxhwPeC/AT7PUO9GviiT14/nE61z30c/U09FBHjmvFPl7yTB60ymkrhn90nOohL6aRy/CJXupz0NtxFM8C/JXxfrcMn5gMHJ3tmEYsUL5DWY8tjiRm3iyA9nT6wHs+eb1lCjkUPWVHkRPEdRj61fB+rx94AzGaj3yZ5BTwvjlffBeCfIiN3kdPg+gsNg7/LIdnriHzwHmrHrpOxqH8lvbTkDE6HR+i/Qt4cCHP0/jsXHy3uIp8gV/dCL8TkxjLDd/46HvT4Zn88BrlLmSbTx2JvJsprzDe8cRGjx//QNZOD34Bjb3g/HQJMZyMTNTHYIfzgX2T4z8sgAY63rIQexcyDrCxjDOdfkll2BafvgAc9zRk8WObCmLRio5SyY0p4BJTp8PvcvzLtpD+wDLRXUYJJR06dvKAD99tRhbgwWhsSw4rqYMfLzJB+0hg8+fBpxNcfOgO4I9D/yH6HpVA/oFOK+1rk/ET+jnL0DMxK55Smwa/34qFJjhfVmFfxthUDA3G//UydET5G+UVxniAvu+54T+Sc8qD8PEoNN3tyBVH3IL3VT4xBP3X4bcHPjYq2CoP3VD8VnhMIn8soB/63sGxF5mXwPeKNMZDb2e2IZugnU484L9Z2PZVjouB374E/DraA+TO6cg3B5tb8RvwrsKvpqBzG+c/BP8CeDmdPi80EdfQe2kasSb8NBtbTiSWOP4BvrcQOWeU4YNu8d58fCaJ/IfdB1rIfeDGAYt24X8p+G8MNmeszzPIOa3g2Ikp/O3oGvoDdy3keDmyliK/B/9Er2Xg5JXQtx5bgruHWE4I4K+05TiIq2p4qsAXFHTOWM/D24/wp79Dcw48pbSQT6g9xciLbXqyaMOWlmxiKgYac4nXdHIQuujKx0fSGJM+r5ADdoprPnofQz8LefwvKxkHWt9jzDbGvod6GXw6crBHOTnPBj/gnwnswVryC3Q2oLt0dBjw4vOMcS42eJa2i4jXJuoLsNmlhYyB3GOhU1UFrXRibjFxwnhfQDfaj10ykB/YLeC20PdlxshGlpPdyCF0Be5VycRdPXaKwl/T0Dm6eIN+RdiusQH+/MR2G/5Kv/U2/MZObsuFppU=
*/