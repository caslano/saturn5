
#ifndef BOOST_MPL_GET_TAG_HPP_INCLUDED
#define BOOST_MPL_GET_TAG_HPP_INCLUDED

// Copyright Sergey Krivonos 2017
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$


#define BOOST_MPL_GET_TAG_DEF(TAG) \
    namespace boost { namespace mpl { \
        template<typename T> \
        struct get_##TAG { \
            typedef typename T::TAG type; \
        }; \
    }}

#endif

/* get_tag.hpp
DUvx1nwYDW0nOuTbOeg744yg3ksdREjxDgl4LJYzXKbgsFSzrRtdnUuObIxPs/wclOaGwCO8izXSEJTV7TBrfjhoIIoMyX4Z7hODCpAw0BfAgIIbug1Cjf4YDTUIEcILbnf5LUr1XjQKs1j/Ie7bHKmaPv94mxPUQKeqwmQ+Af++sCwjTJ4480ZmioGd65i08dmxiGbvy+RZ17vzGsHDJWofQUoyFAIV0lauN4G7nxtDvAuWDOj28Qw1ykc58VmM3hyGf75mcGCpc35nYnRWaINRabCurlfTewaIkksd4IzrQJjMv9qhX6QADg6L8tF4QT2yZ9eiuH8+RhUn9AvUEx4sogF64/r1f+/RZpvDmFZq+iHWRBECyLLp6EXuAZ24jA9d6LO6m7VEOtJTV04yriXdbIG6YrEelWZ01H+SHQrh/MqaqWlRK2TPvHYd1G+2nTRW682T5o5qRRjOKGo8QcyAYL8scqsYTv2RZkBOBqSAMht9ik8fFQTuFah5/u0bBvgOw/Le/0yjXX3whXr8RTH9Z/EZLM9gjXnUqflVHO+0rpE6Rsf97NHxAg==
*/