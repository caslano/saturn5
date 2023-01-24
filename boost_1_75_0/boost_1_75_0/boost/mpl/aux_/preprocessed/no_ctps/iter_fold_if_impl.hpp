
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
ee75ntyZU8OAe3oM4TziOZ5355euv9XLPcfyZItD89dq1Siy3Kcw8e602wYPjUT98tHUSsvnVfLU3vZniYXxtCqiy0UffO8u9zhfy7tRFH7uXpAsx04RWEyyYF6rRXHrVVQnkqjGBd/zAlXLZP2UprKsk155IFnpkOQnKSpbTh1xA3FFpxq6lARXZ0XysvLO8kDuPPcmsmQrg+jIPhV0tnJiELtOBjOIicfhp5AU30fjTaU5lTsmYblZ0TlejzmiU8bqrk5lggNFvVSGgCjRUeEY5vXR/DMme965jDzS7F1cgxjUQBJSkTc9e+e73H/2c8b1zeMSwgmj+nV8sev6Uc3xgknFZb2fqAORTL7p7RAaHJSfFjwyb1B1vb55EiWXNP26vKu+w3J1fIUSmOd4T3rF9sQfiNqLCUAAYAHeADABOHBZwlcXVxwYeTA2HP2yjyMGbJ4gcUg3CHQpjpOo2MMZKSRlxt7U7X3BSVMPVH4egmu4fWmOYVDQFkWv8p0r35u3JojcY8buqdpbJNLphsTE6LkUlUz3cgt4vzIPJhuB8j/biHnxEiTyZWXOlWhaJkemaqvMcgTeBIwDIChThOVVrfdr9E6xbVLrZRdLbXu3DeQOJ0jmfThM2FDC3+VtVI4LCX1STohGT7itmYbtR4sms8Kt9oKIyy22rQofPu/BcOwQLrxntyxKj3cHstVE6gKVwKoX6eyPtyrH
*/