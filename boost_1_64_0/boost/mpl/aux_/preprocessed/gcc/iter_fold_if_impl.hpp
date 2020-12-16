
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
HKqrPdrfaRv2tqW/q7+/pvuhzvzRM6/9V/ftxLZ1F7yrtl0X3TcadtRVd6k5vPYs1XvrDqSmzTmRbWi+V2iD0lyj4+Z3hPn8Jc6dptGIclLXwJ6ytVDHyVC1kw5G12fHXOnMMr5NU3OSPWW0tJXWDyLNn6tttKWvHUvxuxqaUmfm0Mal9qxHyIsuWVxpdNLy5itS4/Oz/drOrOdUzu2+cyq1SAZ075n2MZ1Pi4/Z708R7d0V9ZK27XOElmRw/U/2de4uT9XvKbWrc+qJ2cD1FGlTTy0C1FNr/3qy1Av1ZCl3Ugd3Zh9UuTcTWhvl/rdtuU/4Xtpfotzax/zaVjvZtK2e7de2evz9y3du0AAIpotVj1MIbUm8OMx97zS15nR3CalvNIi6M/JDfXvP3YXqd9R3mu/crj7Np9r57jN8kXT1O8CyvdM7+rcltGOZcnc+C+YY400mJ04aM36U69dXbmFOTuXnzWi/ZzKUKo3GSqMRoaNR4Gr+afBdcdy4PfXRnjgK5ljLM72T/3Vl52jWtEmLm+5dO1gw5fGk+Yd2Rpq+PukFpGrEkVmYm8as5Z7svTZ56UJe4uzywqXZieTD/D3ucOZb0p/e2T/9rqSfYpP+/NScwowqpK+6t21rPKR7Tuzvaaz6vab292Se/mdnVvWeT/t7LwPfE2t/L27gez7t71kNfG+w/T26ge4ZDnwv6LkdjM8XLrjv7Zvavr7mi48Of9Zw8bZbqn5Pr/29uwHvVdY9qBq/plPqzmrWe6Au0r2T8dgex6PWo6M78Hrnar3ztF5/73oErdfDZr0fdM/rj9gNf0LPeg6t181mvee03vPYFV8yP1NU652l9czPFF1KvhrgVRiFy7AdXo0d8BpTvssqyfc+pf+B8v2h0i8L07gdjedhPVebwm6tl6p71mZiW0zHrpiBY3EWZmIWLsRsXIaz8VrMwRtxLt6GubgZ87AEHfgSzsO/YAF+gU78GgvxW5yP9cnbAuyIRdgVF2IcXo7TcDHm4hKch1eofji5apwNdab6qYvTVc5e1d31HIOdsA+eg31xBPbDcXgupuF5uAjPxytwIC7FQWikt5xQovTeU3oNcbHSO6Tt+i02xe+wGx7Gvvg9jsKjOAeP4Tz8Ca/WPc5roBquw3DcjrVxN9bBv2NddO9nGgeDsTb72YW6l3A4tsIRqoeROBBHKZ6UMI1rwSLFUwcTFc9ElWsSRmIitsQpKtdUHIDTcCIm4VS8FJ04Az3p7KgknUFKJ1bpDFE6FyidOKUzVOkMUzojlc5opdOimsabaByKkU600S6BxlRD6YQrnZrYCs/Q8VdLx0Md7IV1cTTWw/FYX8dHA23HxtqOTXAlNsXVGImbsBluwTPxUWyJu7AVvoWt8XNsgwewvcrRAUkzrCM2xk46PjpjN+yKU7AHzsGeeCX2wjUYY6SLvbEE+/i2g8aDcCzZbIfXdC/pLozEN7Al/gX7YikOwDdxIr6FU/BtXITvoNLROAzOeTbp7Fc6nyqdz5XOF0rngNL5Uul8hVPxIC7Bb03PJihTOklKx3yP+iidJ0djHRyD9XAstsOLsB/G44U4TumM957PNcYBu9kcZ8/pPPM8tsEXsTO+jF3wFfScz1crnno25/M/63h9GuvgM6bjc73WK7Cpx+v1vXcD1sHV+v67ETvj73Tc3Kzj5hacgmu0396GKqfGGbDP2JRzl8r5OnbEUuyGb2EP3I2Kh7EDgevr74pnj+rrXdXXXtXXPl99MSYgcH2tULlXqtzXmsqxQ+u1sUm/teq5DdbHthiF0TpPtjelX654Wtik30TxNNX6kb716HsPnO+tWm+btvNTpvWitV5dv/VQ63XG2ng=
*/