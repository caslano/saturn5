
#ifndef BOOST_MPL_AUX_PREPROCESSOR_RANGE_HPP_INCLUDED
#define BOOST_MPL_AUX_PREPROCESSOR_RANGE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/preprocessor/seq/subseq.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>

#define BOOST_MPL_PP_RANGE_ITEM(z,n,_) (n)

#define BOOST_MPL_PP_RANGE(first, length) \
    BOOST_PP_SEQ_SUBSEQ( \
        BOOST_PP_REPEAT(BOOST_PP_ADD(first,length), BOOST_MPL_PP_RANGE_ITEM, _), \
        first, length \
    ) \
/**/

#endif // BOOST_MPL_AUX_PREPROCESSOR_RANGE_HPP_INCLUDED

/* range.hpp
bWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDY2M1VUBQABtkgkYM1U207jMBB9t5R/GIH6Aps6LZcVUbYIsQgQXVpB4D11Jo1Fale20wtfv+OkpYB2X1Yr7UppU7sz4zPnnHHi0DqRWRywfbYPaSkt+C2gtzBZ4TAHp8Hg3Oi8Fgja2rCoX19hUk8poXRubmPOhaF1V+gZ3wbw3tezk2OqmkhV6AFLXnC91Ca3A3aTpuPmC66v0vYHlV+tWaGrSi8rLTIntWIJ3+UkvC3jUT6iWaAJrcyRJQStWtP/eeaytjTvdXtwFPVhdBew4aZY3EAlpLjKZvMKuwoddyUa5NJxaXm36x/qHRx4Qr7x09OjKIr657CmTaUD9j1zGENa4xeIzuBeL6Af9SLoHcfHZ3EUwfWPNGCXWjlULhyimroyhihgAaFv4TUo++9g9intI0znJbClrqscJghyqrTB/A8PP/GHT3S+3iDobyCIEsXLf8vWv2Jnw0rCN55qzHZZSZ/Tmk00CwqxjQUHzNNECdslJCqbYUssDU0uDQoHS+lKyLWjx0KmcliWkqibZ4KokgqyidVV7RB2fT49DKkYb6tBQoM1o8T2vHey+IGjNwng5ZjK2Qy9EOeF1pPM7JdI8wThEMLVVtDOzegxvR3HHQ9x
*/