
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