
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