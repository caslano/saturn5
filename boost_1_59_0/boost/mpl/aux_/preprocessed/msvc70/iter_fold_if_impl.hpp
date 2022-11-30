
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