
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
cFl2WqW4xDHiNBsBIyBUHF4Osve0EdS6e14gM8XmA4lAqrU4BrzcSNOT+7/NlQX7ERaEnMmM11G9EOoEgZ/0Ci6jkuKYVTmydMv9UyUd5SB1iOddT29GT33k9rdOZ+CT/tlE2YbUwybv9mq418+fMgKWEqDyu6DdmrkjdZsFGFuCAqibwN0aZEY56PJIOSLqF7RK4oJCFWykdMM+IBj8CDe9xIcjLFn/y5hrgABLtD4lP9X4y4BnMNlfnuJ8jXvR66N2NYK34NDhYuD8kJ5wuLG9kbrhZuBEgwmCA+Bq4Bzg3pHJqazp+MWd1e/ElJ8xglVhxSR+/kW+fzMevoYKTgRODjl2QnQMtK3iLLlMxq+lboVFs/kj+F7AgbAcnFwtdxqYIE5FRE2U6J1zNQQPhvAtIjsoXy8iHPh6fc38fT6QTqAW/aASex4kLcxjCfd4GE/8pc0Uucgt0uAzMhWJWRg5F0dt1vLhmpuVqYYdd/WYrGyN6hSnWQiDktoTKK2G1aBJs5RcwEbWg8sy+sUs3FL1ye4Wz4XiixpRp4mM4EzCHyJ8fg2EAO5MBgSzUlFzmumJ8YM38zjLmAUsZi5sQqmYcd1DOGS081uXH8DoRZu05zka0wm2QgC/uIxoJ0S5gs1yxKPMSGdaWVeVphzTrsK7lGQumlKEtSyD2LnRiC+J+rXdMrq4GfvDm9nmFTctLLjpe2EgN/01lezg
*/