
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