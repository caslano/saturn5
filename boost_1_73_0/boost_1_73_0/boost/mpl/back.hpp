
#ifndef BOOST_MPL_BACK_HPP_INCLUDED
#define BOOST_MPL_BACK_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/back_fwd.hpp>
#include <boost/mpl/aux_/back_impl.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct back
    : back_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,back,(Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, back)

}}

#endif // BOOST_MPL_BACK_HPP_INCLUDED

/* back.hpp
7wbpBaTDbJhmVPXtds7aggyiBknbhS/FCtm1JUwTkvm2whh+DrzSQpkPIEvhPIaPP2bJ1ex6MmG/k1mFUgmdga+91NZ35d/RPIYyg9EoXhmUQVmTQZvEGkHoI+BJubChBQr00qkqZoFd7lndRzHudU58tBzkfCcCqXCtVezXaiObw3jP5piVIVQvNEbRgrU6dq5LEegAG4+gjA8kUux7LDdOH7M8po2ZVot0lF4SQHtmkBuxxlYEiMbsd/pHDxYeFkjaIki7rjQGspZHU1Ahbyshp8hamKKdLeP86IZwJtPsKIJO7+7nfNfzJZH+7vZq3PgTnVpuIVKxs1oosRESShEHQAMHvrThgOVPTW4kJBC7lXAE4vmfk7AToKGhRqisb+iISF5psnKNi91upycP7vTTg+E8Mtnh5PQ8BSsjMc0z2swNe3/22A1hZvBmvR67khIrCp3xs94bwwxHvf88KKpKKymiNfhzUtd1QgyvExIKjbQFFj3Wo8m6afLGLjE0ZgOKvDrm/IUR3r1+/gFQSwMECgAAAAgALWdKUtJCzEj6AQAAdQMAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNTE4VVQFAAG2SCRgdVNRb9owEH73rziBqr4MkgDdpsxFmti0
*/