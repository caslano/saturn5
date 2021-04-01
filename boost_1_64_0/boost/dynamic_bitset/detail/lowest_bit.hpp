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
jAe75uEADUL9rIkYPzDv+i+QIx4+xSIiFBPbEtw6uv+cBH18Go0aAF3H30vAVAgrV1kNOjdc8cby9QixwSFo+8MDC16s7h3H6HQNJOf8dn+WXke0sJjwdrX2vUHzFeiCLBSmeC1+nmjkFjp4znYPnA+VR1L89T3sqsXq20WfNbNVUClpK+YEfKZ+IpNwWJ2P6ab1BgtKuVG9ewZNJlcL5CwBU2HjKmgFPdngJputpb6mh3aOhIwytWPrMZ64rqU5SRH8CBMfOvyI8Ln2iCObancC2P23hQuZUgPhC5MwoO3sRyPoFk3iynAndMpYSDiLCRl6QL29hYhnHk1/eTntvPDQLgsbTeDyoqEsG+/3EYVhwhng2ZrBgy7a/mZ2HU+L6I0eZeE5ZEUx8NmA4W+YxbPLkvqcicRu7AbMMhVz7y5PhSdyRDob+9r+UWBoIHSP0PmkQZJe2/DL4sfm27snl7BL5ETpokkbHiqhCk6STXYkdLUv44vAgEQeP88vPIuuvs3nri5PIqa249Brev43q3TPcewJzuRsElWqtxuNVQHrf3WpH5DbCUWoag==
*/