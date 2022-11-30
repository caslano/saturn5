
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