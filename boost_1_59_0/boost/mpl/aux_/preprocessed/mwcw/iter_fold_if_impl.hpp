
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