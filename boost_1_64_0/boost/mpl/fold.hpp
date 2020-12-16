
#ifndef BOOST_MPL_FOLD_HPP_INCLUDED
#define BOOST_MPL_FOLD_HPP_INCLUDED

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
#include <boost/mpl/aux_/fold_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(State)
    , typename BOOST_MPL_AUX_NA_PARAM(ForwardOp)
    >
struct fold
{
    typedef typename aux::fold_impl<
          ::boost::mpl::O1_size<Sequence>::value
        , typename begin<Sequence>::type
        , typename end<Sequence>::type
        , State
        , ForwardOp
        >::state type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,fold,(Sequence,State,ForwardOp))
};

BOOST_MPL_AUX_NA_SPEC(3, fold)

}}

#endif // BOOST_MPL_FOLD_HPP_INCLUDED

/* fold.hpp
BmfDX0wEElRNFdddgLqx16QM7GN5t5lhggd+rqSmGQDP/jWF5cvmkdywjA58Yh3IhiBasoo2iJveD+ISCTM++KIJR6/A94Dt+6ad9D1zBXld0n0UclPFEwhsvnvR+GNWkHtsX/6k/L8yFo2mb4QuNqeDJprRbslXkwj3EmCI5rzLz8AWTq+yQZQt7pmn6kgA/SNeNlRE4Rz9lYM08tYWVewXVa9ZxR22KhaYVZxHVSD7n4UjWvqclaXGcX/tJLe3LXGrkEVL4Bm6pK54SWExXaIACw/qYVQwBUDRJiDbUyrBCGSZFb4MjrOszMTzilPs2OvNfJGFPXK9KJaIGP+nLtbAOA4psp8s2EOHIeGP1sFjla5hW1dYvqq6F6m1sh4j91ZSIWWU06PnrE3UxAy6a80de7mxDyz31vQrX0W0SQMHd9q1yLCKaLbxd3SohjZ+9WKrEwvl2aZyerrif4WJYL+XG+IF24iESCRJGlOnD0QQ2ICnii9WMtG01zOvGcimOXAOizlnjXREcewlkakNkXFmkvjw2HgRH7zw727C7dUQF3m/8Zrai5Jg97U+imMQjIdMGHMBY7qCsZG+i1DJhZfpDe/r+erhxavxIBaCJMiEG0xA1wHQKQIoNocXMTGfMq/Eevpqa/WaJLUok/0yY/JINW+qjwtvNGHOAczXLhCYJ3FvM0RIulTa0dGt5U1kXkuePDAN6CzeW1/qdQBmvILqi+PtyRIWDpDGkAv1IVWf8Ou60eFaflolqqW3xsm4sCISfdhFzvhkWSmaZdo/Hx9+ywSQcwuJIZ/2A++gdLdLic0DSGAiqjoXPa0Xh9zwLouedLVXq2qj+kTv+0N0tewGfzMZUQ4kVsDxw43xOUgqLF5PMTDfN2HdomH1ULCGC5NFXLvuKOxnGhvYX0FeB+3rAy6IedBxsxaetiHfzVV0S7juM+FXa/i/Givw36ZXMOxTTtLqHKFa3Fi5llv6eWLpm6U0jAAYKU/tYG9lr3CrmXOeznmh5IzNpkaA+hA4dgkKERnTlqB8GbFhbJ0H91Q1rwAvx4K3lih1BT0vo+clprrT8JaCPWBSUMDg3FLh/2Zk029PxqRBAIL1cp/oV9AuH3h+iz6YWSPct/iS/xzua+53S2hHqUzHwfjKC5Wc3aHyOLIzHk/0HImE75Vx2PxVxQ0ibhYLjPsLzBvUrDsm+0qmA1NZWPv/MuBjMuJnhzrwmSv4LBN8zonDp0syfP76jUPBZwDhA8vlbFND/v4gu5lQb+h9AtFR2TC7PoqQ1+cZaEV6lVJ9Skv1+8sSzdWQDixO0RaXudriciBQU0poCqQ/EIG+xWgvjfaVlFr2zoVd5Gq0KbqSCbqS8a7KPN1+bdY5vnW7tTbOz2T7ylMkrXY2qeGD9hBEY/xkBsiKEF8sk60XDnieEL7xWJ6pscyzYRlMiqWuFXWmhi9R7WFeLfKD62z7meZzPKwnSTzmOnehhwjywvBaJsivR75B1PiT0cLPONIN9M9dRSgkybJHZILk/AZyzpecsSqsv7Gz9FI02KSxXKGx2ma3jmt+QeQygAh/j94AZcho7bxyel05Nd8vg0SdXXvzGOoKy3HRD8rAuZUv5kkzxPnWrenoV4++UOYHKQK+q0/vcolXtpRFWuHqzisYzKkCuKDLE5uOeGW54TupWdKifX/qGTA25XGmhFiJ6I0b6EHid+PKhunXSGyOC69yBbSF6QV++EiE79FQlblEeuaBydqnyStfk9dEV2WOfaZNxExDkMVsoCqnTEYnDLskBFztx1pK7i8o9JhTyYGRa4Ysy3Bx9L/LzD5bwFQwi6jgrFGaCjoAAUBISd+VBKSPCaSGgcwmIB8=
*/