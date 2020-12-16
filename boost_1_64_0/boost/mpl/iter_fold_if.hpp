
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
CG7hw/pQ40N0WgCeVqFAiBPryFvqUhuWUXBkoOjZmaKSARPNvC2WYNqXyoQO9BcLXkwFL1Y1gheIfTUcfHGroL5H/djUCaegPfhY/h8sNuH/YU78ipkvXjTIxep14z/USQlE/gtvK5VCmJHMRz9S+VrEk1LRew1SMSnFy2TasB0ECzoS+CZyPdlG2xFtyVnUZFtIsKKBMi93B05xBhSaPV5MxoVG458u8GNIeNh155Hvous4ClZKgGB4Hbo9Bh2EhUcNjhWzKAr/9mToiD7/+hb0iKe6lXsTP3kmvKBwSRKDDJNxEia6ipRDk2E3gfuPEs+XT8AmUVFJmW3REtxoJFQw6h61xCONsxQ1K4trwxalhfJDg41W+gdm2F42sIKsTU6n3Ml8SGBdGv5AP1WcWAjZTCe9eV6aCYm5vs6WRts1do4CIS7h+kULq/9QXvKjSN/f+JNqtsHWJ/NsoS/QbCRnowOMh1QuFIZjbZmquZlkKycO1IGprbQoWlS2Cop+R/tWtdr6J1NyLA6udkRxkLndFgVbkhEO1my8qGjEudTdwnmELwO7aBIxda5QvvGyBdRKgSIUkJeBvAIo19gEINVvO2oBBA43PMlZW0U+rudfRXJomAk5RG/eV+mcWcjZW+QYb6t0PCt4k8BoVFtDLZPPia4R6dZYfNcC8DHAaQrAJwFqLAAvA4wQAHAO+2X8Rn+pj2X//5r1X9O2wae2C4EKB9MWfy/j+I/l9M16QdkouzSscWJo8nK7rFIKVFrTGwvFs/lFxtlUCkr+3TDD+1Dq90Lhgyveof7exhwGgjfwagv1+QQkz2CQN9ANgzmB36lw3mgDP4zAYz0l1YqnLL7upl1hz2QtTaXvRDoOZul/ZLE0eU9i4tRWvv/lpRRo9c1MirFS0XpHNYYhVvO/cq2L/W5hzm1lu55Rrai8zALEvhGH/PNILsHCpa5X+MURtGqCXRFugUn2aasJ43nyqvTnRRMEkx5dBfnNEgUVeIlOmQ9abhYuS6EHMPOS3lj9Qh/93kSQFnkZ5ZMiQdrOK8MHqXxIX59sNsqRC8/QWqNR9UD9s2g1xsmNbgHCT2K8oFQA7gUsFM++hKRCw1Mnu/nTr6xxO5HK4hGJNCG4iui3MbJO1jLXVssA1FJLtSDLu93KStdZZuBVm8NtX6NQYRouMIlKGlPkIf1xHwLaOqZ9JQWTT9jgWAvo+VdA6EcEWsh6N9G4ok5NXFtTbqCyxs2qka/82aJvOuXgcWRyozU5uhwCRpfVkO81/XWW7B8aZuSkXI8nTU09O2u+Be5Q7/DkJ2qEVF6hmrb0S6umFLSsmUcp8i5PtQJ8fu4i+tYpys+xldpGObFmSTNsRSemqlmSEWxyipNclVdAeUr13WjPGC4yYFFt5Nh11XxeWS2acA31lxIyRS7mTSM1D0H66lnujaiSQ6ZaUftMkyWWclzivZJRzoyFC7AO16N0ndGomD+fwFXjmiH06qgzkTW5i8WRd0QWbEG006yjQU78rYwawrtcX8ohvIMrwFNQVr/fxHvL4ZQDjqfaqi6FUG5koYS8HW6r7jNFXvlMUrqPME5WiDc1WsWPcErWSK33QVvxfVm/cxpTHukrqn13pcWgXQ7K8wgbUiNb+Y0pOyQfR7xpCc73HBoF0N9mQ/ECT5OvyeqvBHAzH8MYC1Qrm97QePAWPyR0bhFeBM0S0rdxi0LnCl0ePbqwDuUVmoPc4TJYpR/utsngg1ZqGYya8ij4hMqHMGiVMpgknFOQU2hexedDCIv6nySQ/8s//L5LijHyQzmeChzhvjLI9xiFKn9IrPxUw6Py01V+9Pmv2WR/P10pH9h/icfJRxf7rs7EujM=
*/