
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
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
*/