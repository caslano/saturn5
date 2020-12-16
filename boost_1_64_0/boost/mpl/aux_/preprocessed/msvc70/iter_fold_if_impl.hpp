
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
czANVsCpcDPMgS/AxfBFeBvcAp+AW+GT8CX4EtwGK+F2uBvuhIfgK/AP8FV4HFbCv8E9UFuH5Q0YBd+EbeBbMA7+FvaA+2ECfBf2g7+Hzj3V5W8veK3cr+qe6uVyvy6VPeyXwTh4PewOl8MkeCO8Gt4Ec+HNsBCugHPhLXAevNWzLrz8nUSdpFyzdeE7wWQpLwVeAEfCAXCUlD8aToJj4HQ4VvQYB4vh5XAhHK+sC/8ETIMvwivgSzAd7oAZ7nFW/naC7QzG2ftlvFwP28AHlbmeiZLuOmSKz1zPv8j4VAWj4FHYB34KL4LH4AD4ORwLv4DZ8EtYBL+GdlgNF8Jv4CJ4ErqfDzXo/QHX1YOHYBv4Ryj7JMjfFaK3zz4JW6VdXoJRcJu0y3bYB+6AfeFOOBa+AlPhLjgTVsI8+Jr0jz3SLm/ARfBNZb+DCtEjVvRQ9zuwit1nwoZwFmwF82EHdT2OOvJOL+/6UxCtP0XJN8J3pD4H4RD4PkyEH4j+h2A2PAzz4RF4M/wQroZ/gethFdwCP4Ivw0/g5/BT+BU8Dk/Bz2S/kM/h+fAr2A3+DQ6BJ+FI+C28HP4dzoGn4Dz4T7gUUiH2/QDwFVgPvgHD4J9hODwO68N/wQjYRnsWw/awMYyDTeHRszS38v91XuXPbU7l6c6nDHQu5c9tHqUyhzKg+ZPBriNS23MmT2e+pNlcyarj4QHPl/xvzpU8k3mSp6hj7GfsMY/kISuQTche5ATS+HPWWUHSEBuyCtn5eWgeZegIHaHj53GcI/8/br3aif9f0sLi+Y4v785dkHryfX0S384PdPN8xx+elD5mhLbWsnMGAHrgyg1iX2lt7fgFUF2PuEjZY71emMf3r/oickrylb3DlbXxffxkEeIzHyY+lUuRydTB0t2kDloVLIHHcPvq/ymlWheIH0V0LSjO8fKPrKqrX+d9KjqlGeqUay2w2q2oFdQ65j56GeoxpJ7eTzMNPWyGejCbwdm+eGrPTA+1fe1h0pZyTZScc683LrpW1jO22QYzXTVVa8leI0WHGdIhYkSHtsg16FBZkw6Z2Qszx49JPtO289hMdMsqtduKS730s4Tr9ctEv2p/+k0YPvZM9BtF6Qw+pvqNFf02hRvbLzbej35aB8nPySo4DR1V37r0M0M91fsitr5Ft8d8lnZ/1qinY5v5oPVT+3hVff14m6Pdj1KusqC/OtgGXGZkzNkZaweL/rYG+rHWqt2jhvpr6gc+zkbGBD7Ouuz5bQP9mDFLux90+sggG+SY4aOToQ7rI/RjbD46RPbQ6aAOsGekQzDjq6vtYhoa2ypRr6d0+Nqxk+ue29ZQPzbMofwZpuXLwHqG7YWt/I4HGY30uhWi26oadWNQPQPdZEz1O+afamRst0qdbkYDavD6nc54ajtPP54WafehuY4MpsHt2yL6eZXbv7F+PLVp915P/f5V6oAaTLnHztL7q3uOa2P9mFqi3ZfGddCqEPCYeiyId1fXeDa6iX6cKNXuBb0+MqgGN1YcC+C99dsm+jG1DB0q9Dp4Daq12a6Bjqv2psb2qjLWFVUDf4cIxFaRzfTjw3zKt/QyLV8G1lq0lcm48IyBbgvRLaFm3RhYT1+3QMfVtEhju83Q62Y0sAat3+mMq3sj9eNqM+1eNNNRBtZg3nFEP69yb2uuH1cXafeflOu9CdPpvau2P0vvqq5xLLaFflxdrN2XhnUI/n21fRDvqy67bmqhHyuu0+6H3kY6nd47a/sA3sUyWurH12XokWaox+m9t7aPObPx1dWOh1sa22ypoa7Bv7u2j/H/XWBBlH6suAEdNhjqcPrvr35tZjKWRbfS63cj+h3wq19w77Dtg3w=
*/