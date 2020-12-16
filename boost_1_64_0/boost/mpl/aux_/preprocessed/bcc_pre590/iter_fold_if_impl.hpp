
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
dVivoVJrbVMzc9Oyc6q3sVQxBr+KLyWOMaC79q1Cp+33DQ3d+mEB6nkiJijusdD223cX5VyD8CB+W+6Q0/iXUyGrbVeU0WXTj+Me5gSTHTYozfdK29cN9Brtb9OubV/aom7olnnc4ZrgOsq8FuFR0Wl9w2XOyi8siqXv/joyS/9uXGHTPzNzqtGLzEvDft55CdLH4JnUf60QtuCe1f3C85JdEMv47JEX6uT48uJsyzspYx7Hj3EIj0sf95DRWAvz9oFYra9XyuyaK2UXmAgpt0vGyv6Oa7gPWXH01YXmt/nFRWHtvSs7WCOWt3kHGHkp6G/nxbR0M9zEXt4baG/NmdYOpjWK7XQYwlO4b7mdlqP/x2430WUvM46+vhJCmDkN5XmC8ljnh8mTD+v2Mfhv8JKn3JYnzH6nra+ext/ppkN99aCcVhypdpLGGFlsPVaIvKRl2HYcu1eMiUdF2hzcKnrL/D45FU8oYQ4czyYzsvNTC9PTMH/IL5CVTmH1NvTkmepJYMl8iTt1sP5uOAxTp02smGe3oxx7KEcrytES4Tkp0wGmTFOnFWriOTHY7qsY51rirtTuxRMmZE5lX+C13saga2VfeKYhrg2QfGaiHG0br6nJUycOMGMt7ecN0DJ9IUz3LKevwFns11MQXsQ9SSp7Wrvs1H5Dknv2HNZr+PCKPt0kxj7NvDj6MG1Km7kE2yvH8KI4+u/NLMG+PpW5s09lLvOQOXVQDyNzpxhllnnHdwPD5x2Remi7U+Z29CvpzBfXvNsbMg/M++6wecYu/Y57inIrru1wxt1W6+8Ilcl6uaG77bWqa+uXAM/Kv4J7SgdVlgXEzsiIZdyoyGtikDJ762Ejz6JB4fLQ3inl+Z765RuEndInKU9BgViJzU47K6b5NOc61KvO9RHVpXPtg2umDN124umrbjjn+oPB12XtNsTIk5GvoxYPMMQ+/zJrtLA1ZTrcRXKvobJ/3iTzsinFZtPCc47D+YKZ9/OeJrxnvMPGemLknMKlW6dOUz26FXIdqMd30Ie6/WdKvaYho5SPa0i95vQjeIMpGyO7+d5uqP3dLlvj+8N8JnPePxHcJf1waEXZllROCyraX5sYyvbXmoNV+kVOtfehmkSWI23Ysyxyinh3mO1p3reb3wvT8lIL4Bg4M4/7Na4x17ZBbte/ex8rPS87w+m/j3VIvUH710Y+2tKvb+yMm/f+vh3G8ZF68jVNV9ct1EHprGfUV+Xvgw11/vHVcP6eOkvastx+FPXRj5J2pvmtq2/vYH2PY98eg7BK+vYIU98mm7A2XZgZQ992+hYuSCsqQm1oX2Jd8lpqDvNVh/cWFo+fhO1K3GvXO69V3tvY3R5ceVhJ/4f3MA93Mg8FIx15MMql+jwc5chDmsmTLX+akQb3OGQfH6YDxvOe4xwyF+cVF2ZmpFJ0tsGK+W14Xo5RYd5iXt5gXoaMcuQlL19qpNq8/Jb1Ie3xZtTDimP0/emlo+z2+BPtdk+13Ha8c6xIO95FXFysZv5vZv7HXeDI/3Ts0qenTc34L2uTFeOW+X0RttvC6rYv/ei9yby9Lv+WcSvF5A1TdLbSGPw3V47rdSP36WydFbGW4Pzb1i9ufWjP9WcZfWHP21o7xmeuIV2+AS9hnooRdstc80KTp+x2hanJwwe1Te01aOTAXsOSR/TqWf16qCJv5fhS4RDoKOc+qqOs1da8Pc86GLlnas8xj/OWtSxM1n6DRvTq02vYf0BObScp9FP4AuV8tmL+N1rlLJjWQR/yYOoWiz++oxxzwGkd3GNwdp57TExr4x6/0tq6n92ktWMbqfjeXmU/k7KXU/bvKPvXCG+L7BdVyH52avr42Ps=
*/