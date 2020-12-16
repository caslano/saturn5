// -----------------------------------------------------------
// lowest_bit.hpp
//
//           Position of the lowest bit 'on'
//
//         Copyright (c) 2003-2004, 2008 Gennaro Prota
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// -----------------------------------------------------------

#ifndef BOOST_LOWEST_BIT_HPP_GP_20030301
#define BOOST_LOWEST_BIT_HPP_GP_20030301

#include "boost/integer/integer_log2.hpp"
#include "boost/assert.hpp"

namespace boost {
namespace detail {

    template <typename T>
    int lowest_bit(T x) {

        BOOST_ASSERT(x >= 1); // PRE

        // clear all bits on except the rightmost one,
        // then calculate the logarithm base 2
        //
        return boost::integer_log2<T>( x - ( x & (x-1) ) );

    }

}
}


#endif // include guard

/* lowest_bit.hpp
/Y0AeYerED1/sKybjxopwo9UK6qKaOAPv8SNBk34tvYEVoq/jGpSZaTUm/MdJez625m7vGiWO7wPRR9zj49kia/IEl/uFo/qut7sM3wwWVmWKMNBjtvJUhrpL8F20u7xf9JSEIlHLYrFh9HBEM3d5dW4EvJpEM/dZVWbZ1OL3vttatHy1DI4qt1L+fke/n+o7FViNdGkogeVOAonU34z+79PZc+u5Gp45JOpl4tlVg/+YS0vnXFq9xpo4EQiq792S1bq6czxXBin/ht9qrahuasINltkQCWhemq+fG88RO+wZI8O8+JyQWv69lPkeBz3xPz9YCk7BDQpDozgDWkERYhC90IoRP4IvohzjoIWxmYuWgtBqdchlen/tKgZw4oH+Hze5Mrd2pOnWA7hiZRDeLrUQ0ohpNQSUo5tbwmpwN6yhMTwvMESElfMwCEJCElYQpIQkrSE4FVmrSWkDkLqLCH1EFJvCWmAkAZLSBOENOkhy0k8uwW/LOEtFN5iD19J4Svt4W0U3mYPX0/h6+3hGyh8gz18E4VvsodvpvDN9vB2Cm+3h3dS+OfJPKFpz/qWSTQ8hBcnKamMgjUkwDfu+3P3w9tTKYFctAweU+cUaSrWC1DavhSizseoMpiUusZUbS6gHcjg4H7wJRxDg+6armVVCC2EDzEacwY9tvr20nyu7v/tJG39JevkFeJw2A9ilvtWbX6eivbUt9TCeeM52RdO2/4ZwQ3Y5XA3R1vzl4vQiNzfRSj0pOBy47Gs8wEfI0YTkDz7/MHpIcjw4n9ZlmyQmZnZVcRFZVyU4ohlEbsX7dEDf70L/oY+wN/kgr+5D/BXuuC3SXxv8z33l9G7/hpgyVzBhaGIqIqIIWqv3v8c8Usz4Zf3DX48E36ib/AbMuE39Q1+MhN+bd/g12XCr99bfCs/L3Hh55Ys/Gw9mvp2tdzNrpH6qefCi+Y2YUiqRLfvQXP7wUozPr5cmIZu7qQzquVVQW/OMjLvN6NZ9qMRy37UKZF9vY7aFmoP+dfb82/oXf5N9vybe5d/pT2/0Ofx1H6Gh/ZJVOjgCU/+/i35Sy35y3udP27Jn+h1/gZL/qZe509a8tf2On+dJX99b/Nb98NRuRF20c/nYfpEXG7tQugvKUGXNAbEVNu82N1UJO2BebGP2RD/FOxjOpqW/PsEQVkc5847Sh5b0vG9eZT2sF8TCxVa/HXqqsHhfCoe1TzFNo6hA8shp5pnbtPozO2Gb/CZ24185jZvmDhzmwQUu4rFoeYJ+0IJNcDBqCNOoPsPo6iYTHpahaYerm575hK1EYLaDVZqeQBAx3YQdzFNvKFvqBO+YwqsJ3yjZFXKyYbmAgJ+4Wy+RjKBNx4lgJv1s7danBz4KaaOBnVbbcoIZkQ0L6vZr5zEF3p4lDlM7LFFQHfSgIvAL/Q8r/vq1/rewM/H/PQYij75MpcP/3zDOh7LYi/k5HE09Bx8mAmv6XTAdJ2yWpn1/OhfY+369O8O4LeWLOcflJVyzc7nXO72r3rQu+oAj/SSOr3JGXLZyB1AeUxqH9bIfL2RT9ogBB7GCChlXjshnWWAVUL8uVP8PFK52QjMOSih9GK7O5U3jcRQ4YMApjScUCbmoG4lnkxNSHxwnwBLHLdMIM3H+CNwbp1FLjZgLPxjwsWj+JG8VSwnjduSBzpZCf35nYiBxOYgxhsBCDufQEV8yT2EQDp+SBw/fnyMc4lBtR6VDVuk8idGUQFZEz8xplOUsTlglrGUq9ncEQBCHYmOnQHy8LS1HYhA6+FvdOoh8k6EvM4xX4QYloNKmJ4b6rF5U+LeKJzYuox+QmNjwfE3ItTPFxPeK1JOtRbnpbtxXrrflH8=
*/