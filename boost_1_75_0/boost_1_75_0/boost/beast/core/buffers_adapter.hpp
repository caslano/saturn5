//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_BUFFERS_ADAPTER_HPP
#define BOOST_BEAST_BUFFERS_ADAPTER_HPP

#include <boost/beast/core/detail/config.hpp>

#ifdef BOOST_BEAST_ALLOW_DEPRECATED

#include <boost/beast/core/buffers_adaptor.hpp>

namespace boost {
namespace beast {

template<class MutableBufferSequence>
using buffers_adapter = buffers_adaptor<MutableBufferSequence>;

} // beast
} // boost

#else

// The new filename is <boost/beast/core/buffers_adaptor.hpp>
#error The file <boost/beast/core/buffers_adapter.hpp> is deprecated, define BOOST_BEAST_ALLOW_DEPRECATED to disable this error

#endif

#endif

/* buffers_adapter.hpp
wAuHElA0qIwCEOOITETp4HumKKqxo1SfoG+caFy+6ys4A4zTsPQlLIbBsDhxrm6+rgghLdQhdx8Wq5Ik3yeBApH3Dd3E1OuL7kSD2Pqm5BOWEUJfilD3PivDe9B2n9ksnkSqX86YgR5RfCmMW4E40oTG4lViXyloDowsGpA4RoiOEt+xSrFmGmYoor0yYA8K7bFuDOytXm0GFqAgQnsljdH2+wZrh16nPmP3RK3W4SbawjN6JYLkwKXOc21HF1dleb1hK1siF4NryL7yl3eGUAoYio1B0QVQbF5sTgzYN9tHOMzILkV/NvsTGbLxR8H7sBO5I7F3J1VRwX+ehctTgsYUgWUHijMHnKtoIqkoX8eEmtg87dTCYN9Al67bTabCmcmFhlse/sYA7kSv53BctaXEj/3svnNh3fTOK9m2bw8aXvlak/KLyGSPYRtxzyURNgxxuSW2SbO4tmr8cPM4Da/LXhcQLvhcA9x2Z6tyk5/Zbyz0FgCM3gLcQkHKlxiOloJNHSwWspoleYtoBBBhbUHC6QVLaVh7rtp8PpZ1Qr7bzL73+h9XXI9KbPlYb3mK5C9z85L0999KRJJ1uAyrZr6XIVxFcjeLQxduwcrrth6N7aRxPe95w07UmqpGnMkxJqfiJgrC+vnNb6CIIURFXkj/odaQjRw4PR+GPUvzMGWy1Ghqi2bAp+v8S1jEy+qxupDVPTqLnfWnLSPX
*/