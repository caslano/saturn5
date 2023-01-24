
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
HVEHbqCj7reb5UmuEZXL+uweZGevW2whHNoIYsebK8ux6MOG49j7wEbyQtnWxrdrwukLKxmHPI27gruTb7D0+kggnTXXL2ds0vhuJclQOr4meorjbS6aNTKrHY26fq0+ntq76rUw3eStB+2N841KslDaxmepeAZyfW1YGyxPj27u/kgk1iSFGUwk4di5TrdFzjTLCdD2ZySefnPUGfDERW2m2rDHOd8ud9oaPl3yclNIhrE9uhSM2/TYUYkiOGFC5/hquQ3zxiGkx98cpC48SbX/IHfEbkF1fKVVJBHyeP6ZsVuQRNLKboX820Pe8RUoSaViG/njM69fhVKCNI3WIHFsmQpRgzn+49fwJBG8Ej4NMC3NiUS67gmvccQX37q0cV5DrlVwRnNE6W6DIecSTjipG8HP1ujr2NrxYyvT3MNdKjZzxsTMpGFbrmMrVZrQkzKHOusVUdGzScyJRbesN2dDem3VAlL9Bczu/urPJa5Qrzzvvb2vFnt/gUqKAZQOiOFLfKDkSaQkG9LA+hW/uS/vdfMg1AKTfiy8oVjPtYbhCwX7+A7ww3h7UjOdkMGYTS+HZCC29a2X23TOZR2dcA95UP12LoB6YScM9PJVn1tnUisqgNivSaV383uTL8nUfRfkTafOXE/chnrXkdAH1Mkt2xKmy5a5yCMUv5AC79/MwNkECAgyDEnZlBmiTMXa9OYheNkZZuxI5z0m
*/