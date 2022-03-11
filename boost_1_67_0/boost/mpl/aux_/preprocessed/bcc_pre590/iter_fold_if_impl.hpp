
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