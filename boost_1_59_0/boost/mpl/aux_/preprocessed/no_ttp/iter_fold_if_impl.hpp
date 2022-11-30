
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