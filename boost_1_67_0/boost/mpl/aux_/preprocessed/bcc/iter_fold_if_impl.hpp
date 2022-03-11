
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