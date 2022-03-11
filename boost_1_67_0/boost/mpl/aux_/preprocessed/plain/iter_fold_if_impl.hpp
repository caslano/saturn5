
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