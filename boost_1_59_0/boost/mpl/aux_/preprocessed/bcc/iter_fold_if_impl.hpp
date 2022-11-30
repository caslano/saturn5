
// Copyright Aleksey Gurtovoy 2001-2004
// Copyright David Abrahams 2001-2002
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "iter_fold_if_impl.hpp" header
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