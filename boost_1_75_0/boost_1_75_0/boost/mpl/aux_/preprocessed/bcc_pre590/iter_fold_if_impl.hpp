
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
FY9XpJIpr5vH5yp64Vw7v0ulbBJcsBfNb0kK/aImxGtVmhtVPp3bEpGT2G6JmyCQG5/citYUnyroaOjaybowXlb7knxMy+LIGDHoNa+sBs2MYm2OjS9N+jJ/fKGMay2XmKg8fHJeaMZnV14ryZiadwQayDrizMXL2C3RemPpBma/zQ8aaE8lXdgv6nHq6h1hly55jrLgVrX7HFfHn6qCO0BzbDqh4QbBa5CvforuWGhNbjDwNfQSgrSHVXiOT76PHo58g8YAvYxBGYfqHmOlUHEnD+q6rwpZWee4nCiuTur8iJ5Wmi0+MG9NZvaWu/UUyFT0Z6wTznT9m/u8TZijqnOFWlXxTEOYO+0j457HoHTPtMzACRcaW91Ri/HOsWqppeOqF5cwSnBZmmCIOaBGcvLQ4Jj0kMFfIJvvp13tR+Fvrg6ME7zlmhDDSmgFE/xVqcYCZ0vE3h4aDs/HW8vwlHpuNLraxrTpg2l50LvV1VkaO0enI+czEcKjBF5vXjQ9/Wz9wWDi/UWXZVdNhTyHVOEEAcofOEIieTF2ir45eGqt4BW3DZuzhE9dahFpdg4bZDY2dlG0PlLzqzdyVjckP8WTChN16QvzfksMUKdg1b2duiDu4WsZJx5Db5GSrdAmptkkQz/5zenep9jt80vK2NkbcbX1YsSdGexr+6RZcCUhLX7EwGbANZ3Ial9y9J54kxC9OVfVupY+uJWd
*/