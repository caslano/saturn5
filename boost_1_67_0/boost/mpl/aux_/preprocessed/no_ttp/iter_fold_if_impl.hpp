
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