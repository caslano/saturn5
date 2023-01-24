
#ifndef BOOST_MPL_ITER_FOLD_IF_HPP_INCLUDED
#define BOOST_MPL_ITER_FOLD_IF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright Eric Friedman 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/mpl/always.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/aux_/iter_fold_if_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

namespace aux {

template< typename Predicate, typename LastIterator >
struct iter_fold_if_pred
{
    template< typename State, typename Iterator > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : and_<
              not_< is_same<Iterator,LastIterator> >
            , apply1<Predicate,Iterator>
            >
    {
#else
    {
        typedef and_<
              not_< is_same<Iterator,LastIterator> >
            , apply1<Predicate,Iterator>
            > type;
#endif
    };
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(State)
    , typename BOOST_MPL_AUX_NA_PARAM(ForwardOp)
    , typename BOOST_MPL_AUX_NA_PARAM(ForwardPredicate)
    , typename BOOST_MPL_AUX_NA_PARAM(BackwardOp)
    , typename BOOST_MPL_AUX_NA_PARAM(BackwardPredicate)
    >
struct iter_fold_if
{

    typedef typename begin<Sequence>::type first_;
    typedef typename end<Sequence>::type last_;

    typedef typename eval_if<
          is_na<BackwardPredicate>
        , if_< is_na<BackwardOp>, always<false_>, always<true_> >
        , identity<BackwardPredicate>
        >::type backward_pred_;

// cwpro8 doesn't like 'cut-off' type here (use typedef instead)
#if !BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3003)) && !BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(600))
    struct result_ :
#else
    typedef
#endif
        aux::iter_fold_if_impl<
          first_
        , State
        , ForwardOp
        , protect< aux::iter_fold_if_pred< ForwardPredicate,last_ > >
        , BackwardOp
        , backward_pred_
        >
#if !BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3003)) && !BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(600))
    { };
#else
    result_;
#endif

public:

    typedef pair<
          typename result_::state
        , typename result_::iterator
        > type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          6
        , iter_fold_if
        , (Sequence,State,ForwardOp,ForwardPredicate,BackwardOp,BackwardPredicate)
        )
};

BOOST_MPL_AUX_NA_SPEC(6, iter_fold_if)

}}

#endif // BOOST_MPL_ITER_FOLD_IF_HPP_INCLUDED

/* iter_fold_if.hpp
g5bh3XlsOhD68By+Qno4fFkn2/lHFxl2/fyXeCqpy8GuWi5DyUvL2yFkaEJ/CLBmi/YNAhExFXbCt3eLmDf9sjl9q7BE6dfa+VIvduM0eOZTMebI/86u4HPna/b7APKrC02OVlkO8AuabJ6wao8xuEIOGHaJDp5u7/H0aZO4coR59KKtoD4GHNSwyyHU/qIS7bnhv4i+EG532gbB9sIE2a+Qtdj3LkkpUvYv9PQh5fktfenBvfYCkKa4j7xNcJAIpyFCYZuhNwUZdDTfxxIyti22rSW7wcdRD8LYlcK9I1/sRSCqDr3bOJcW9C7YlkqHpg4vPPaVQgpOPoe/HFbc3Vbcxm1Lwkw+fyQPZKSpzSi5zthG6j24/WVPL7sv5NX5nxDRm/8MEenaWtq42P59Rcf9SxePpE9Twxu1DzYmQQPX1hwsDfQm0Avj5L1hQkfA6Cvnofow0k+mII74MpwqM1tA+v4WDxtvUkr1jsCBgZtwk9B0CqfKH8jeqcylt4ivpEiilk0LBc+yfHk7sSiLs4yA8XY6gZpb0DeVtnfzL8fX2j0vJBL9L7oPxy88gcYvP7Hyje7xs3Wg2hjd6VVFGAou6kXv8NFfPb4Yc2V4ZntKcUsZ7EdK49+26E9YM18ETFYFz/fRbMlacNYRtCnPpLHF227Au16QHJHvXiknacrEbDGURGeZyCw35LLdOuU/D8PxvYrhHx87KjKh
*/