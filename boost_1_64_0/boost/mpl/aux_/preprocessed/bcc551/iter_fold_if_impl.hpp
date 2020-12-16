
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
opsrDns4Xk/QOyNbCfQ0LjI2GBG8LLfhjQ1G3/kU5CqLscZfyyHwejZYJ9GtUQfVvz36u5LQ+bYTJ+xtYGC2sxcqpQAys/WBnUnClZmBGk5eQEvuBwMsAGdiMpyvdfDhz6AXsDC6yigYaqL+lj5TX4fM7px+BTykpKEBHUtCHbbkK/D+xTdA4Jvwx6uJJWDIV5BiVpI50G+XsVuKw/ntZ82xX9h90eG/Gi5DN3Taf4O3AE+4F5A9JyO1+wnYFK5sCWg81KqmcN8T6Sy8UbMPui4B+nUkSwFKbYa72gwe8Hicl3lw6bZACx3XbuMui+kx0PSD0TtaA3eWYAwzxoNb3DLuGcFQIBY07CDUuavQeCliAe6QBN7AAQqdRsdqMt5quQy2FGKXsBuhT7Adqmh/aKf37OV2Q3gW0+BUBzqRq7t43yVQ3+DLF/EyvM+8b/weoHBlLYbqtB4ysvXof/4J93wTbxmUYuWhv2uzhkzgpLeGA/QF28q+Qq/oYXYcFeEGFHkjbTQy0YOY7Si9ht5en69/iv2dh7cKm8IJW2v8zONFXyShH6NO3hdBcmDA50EWuBdvGFTBW2MbzIPmWaBEOLyXHegIuGMF21Vs09bQyZeK9d4Ld6EnZrm2t9LPK8KVRAwF4bq+q4bCrdtCD6HqbQbTnGjsM97l5URl0QjqYYAYg97e1Uge35WFzKJgWDE48TvtUHzjAWeAOxTVOce9jwpdDW5FI+8i3imAcz4qfz/VgTO0BDt8Oc5/TczLdOzs43AkCrCiLIJ9jUzpO6iiGNTZV6A13oWKe0lvjaefDh30J70lPJiifCq8v2s8C1zjDDyXojICe/sAOoxDzRg4fa+YU4C2c9CV1Bru1nRk2KHw967bKc4KJ8udgDcLlZRwvz+xDXkNGVFd9IjvontwF+FaKVy5MVh1V3QADEC6sQ3zf0UroMdgf29Aatgb2X8yUHgpmNLXxjZRBUr/OjglHEO3EzzCFDhWB+HVNPQcOGOjvYVw6E94P/s4H65Mx9CBdCUL0fv4NTkKPGmOLHU2/MEsdZd6GD7NL2oMZdgrjYEvnZC4fETnwbcYhMS5ml4IGryaQY1VYJ69sD/bmG3hY07GWz0bkM7rWNkx2JmfwsPs5bwKD60SWG2CewcOWk2swyrsyXNYCyUz3K9Vc8l8JPQXcQ+l1SPsGHKs2lpDkYpEsqIdjfea1ttxbks3Ht/Q2e2GfZLoHkUNCPd5ZnnyDUlXO6BjNdf65zdsgu1QOw1V6As31cf7cEVgiEP28Q/vO+jBeqieykdZL6Ez+R97a/1OdV/PhSsTMNRQR6rFfD8hiZuiJfb4t3CoXThmLwO7xsO/mAuXJcc+Yp8FhoUjOarpNHJag9H1dYbhbKbBSyyCtwSiobpGwr+dhh77O/AtQ73SXlUvFm+FNPXawsVdDBW2AVf2a9QFXBtDBClPaoH7O8i+OyPnKYW3WITaRG0Pf1GhRWlN2gh+WnM4S4VYNKvHOByZM0DJO+jh6KkNRD/DRCiza9oDoPQFfh3oUhkugQYmOkgkQ6mskMS8Cm7RAmlOHjoU5vi9xeFKbGCPILOktCctqNXCDvyDPk7/xxzgZfGKmG3iDn1uiLtDarIKbtFQkQts/Ri9ADX//r4SdE0WzuNa8El8ODLC//6dZItxFR2iMdAttt3YjsOMxtt/9Ym2OksDn42OUBIxjIUvWhkMbar+3xPyGNxVIAXsj2qT+u95uYjBc8chzf+7UtglFBLh84mYwNvoOO2fagX1CJ2hnqXa6XYWOGUO2FcumFewE4U3lTQnDuvaH71fqeguy0ISluMojSN83+a+Gkyj4G/ughNR2ZyDrocA9uJZMVQ=
*/