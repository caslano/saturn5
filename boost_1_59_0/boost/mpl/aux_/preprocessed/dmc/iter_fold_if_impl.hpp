
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