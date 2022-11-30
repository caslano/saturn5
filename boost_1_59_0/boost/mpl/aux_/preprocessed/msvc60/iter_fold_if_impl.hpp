
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