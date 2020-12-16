
#ifndef BOOST_MPL_ITER_FOLD_HPP_INCLUDED
#define BOOST_MPL_ITER_FOLD_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
// Copyright David Abrahams 2001-2002
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
#include <boost/mpl/O1_size.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/aux_/iter_fold_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(State)
    , typename BOOST_MPL_AUX_NA_PARAM(ForwardOp)
    >
struct iter_fold
{
    typedef typename aux::iter_fold_impl<
          ::boost::mpl::O1_size<Sequence>::value
        , typename begin<Sequence>::type
        , typename end<Sequence>::type
        , State
        , typename lambda<ForwardOp>::type
        >::state type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,iter_fold,(Sequence,State,ForwardOp))
};

BOOST_MPL_AUX_NA_SPEC(3, iter_fold)

}}

#endif // BOOST_MPL_ITER_FOLD_HPP_INCLUDED

/* iter_fold.hpp
NVvZO3k1MNxUm2rv0q7IUmy29QAW2h/r0EpFDJ6/6kLEJLfy6/W2IFX6983f4aDSpVfYwpkVufVGqngzalMX3/L8HrVtGfCDUjxgcXvHjVe33qB/oMCgm/TQ6ypk3mi6TsAjcwVBycsHLfPLWpj8eRPFF5L8d0HGtLjnDeG/GQtGufGbrkBfJr656IEiJ76lZCxo5BfMiimDyjtQfoGTUo6jFDJfz/8ildLoOhqAbxiCilvoqllWQU+fHMGKyAve0CPYJ14V86FNO0lVQ58zeX7+L0WNDJ8TI0PFovdscnF1QRJLDKUQf+FQ/u/SFiKOVwaNz0whSLUX/XRbk000zhvi96hOWPt9GKv9RA/qkvSdxb+BeFBBM2VQOC+cnGU6ZnRpyCL3WRDfVRHvVMT/VpCFxO6KimMUraBirhhfPLQa3viJX7JWcIeE0/Qu9YKdZxtd+Ocl+ocFup1ntbCiqbuUc/fGvUcOAUFRY4Z+ot40yCVslDN6gmeOz97Y6S7uXCIFLfZEDrTndoeN14FgIqbVzO8UwV0aUqi8HWkWIdX1lYbV95MTWWygH6GsOs+nqqjVYpy4mD29aZkP+cBqWRQ30AsFgRFnL3ivg0M7URLFyynfmc4xQOgrBQtKK+GAXW8LGJC7WvUhQkwQo5idql3BXTZ2usq6NBzcRtAoTLqWrpJ0raElYS07kMgTdSJOAE2cSky81lRCsuNHhaS8bh7fAkqlDPfcsPZ9QuD6GI4ZMTbTtq/l5jajbhqTzaOLW8sGi0G6fodHDFJUzt+7Y8DSxTtNbegVSmbwkzJHT8iakW6jO3SZQIMHGNNcYuqFMiSx62QCCrjx2pmdWef9pJglpuDo8ZnU2Jadkr8eyFEQj3/Upc6pN+efSPc56f/dSGw0Tfj57iP+/xP7fBNOU9hgrKYu09e0ncL//FTyzwiTKYt+1P1a4MOpIIWbYa30MiGgcXpDyyffB07XcqoTG2a9nqcTff7xUD782WalO+pmzRJhNRM1sXfEuCzHzU6H+cgm9s4cql0r6JAdGxUa/15EVuiu7uF4Qmko52EM/lNQl9pmvutEhbh+xVjoxjLCmbTBYcIHVfnyH5RDQUqnPU2kvmneRcuC0DqH7VRaVrv910Tdhq0SNuV2Z7w2WIHDXDiOZ0UeoQYOJW1dxzTcXdoT+gZFaW5Wu+p3oPMvbUXTWMbziGhJOtIy69sV/6Ae0O46x7yr2tN+/GNqj7aFZgpW/CRUIHtLTmIdzbiHegp0rtlp7SgPgMLdhwcoLADDG7SlQPrMoMiq75s64DOj9H0v5C9GGAlehNkIFFFwyrj2rYI2zC9EPbe9Ldcq3m/KoqSIOG6l7tB7IeJ+q4i/loPIn2L8X03vaPU3H0QfIc45zSmNKicaVUl3HWc99B5lIxIcYayLwFioMV6Mtao1ehVV1LbFobZNUdsQgbvlK4W7O6htI41FPy/gTwvqNwhOZpRQy2icARtU2HfE4qfb2BbdRoWN2qiefBojQjve4pExx4OTnLtJORX3702niO0ZiclDmRtpMfobPeS8mQP6nG64nao1V6E1B4vWqHpKe7MJzljOAC55mOgNZbNUMJ6gRG6ZyHWbm5Cb2QlZ+Et81Pl0Lu2R6Wgy8rgG4/lsnP/TXLTfx6uE0erEtWQJQgQnNgCdhFFUGchfWVGwks3qRwn/NNTQhRBgnXmivOwJBzk1HWVUModm+i8iBr/aBC41dIXl9wk6zfxUgq+o4LhLK9g9bgVX8hnX+/BLXO9yrqZ4OSxdyznvNRG0iQyMtJmALvcMLVRrIE2wuXPB2cAHk+UNAH6G5OIayqwsf5nk4J+rLXkyD25UlP1MURBhgnw=
*/