
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