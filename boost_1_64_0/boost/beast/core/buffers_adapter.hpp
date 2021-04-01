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
zZ1HQQif/aT/SYdCzIQ+KSFI1WiPTPH8JLywd1edaX6U+I2t1LgCMnkAK+B886yWOjYMvlshjMQHjjYkjrcU6rGZ/OUx2k3YyH2rfkqiFOa+hI3NLLPylI12HYwQlLgmL1QIMySP901gMhQejiYNMWQ8p4l08YSeNbj3X4K/YhR+Yi0EpUnFUpGBKv9ji1+m0kBB5HXz+CD9cyx8dhUmkaH4Buq/MFl02Lk57C6cvRrSS6PJ0vBidJyVzoN04kbnEXDbefssTLk7uQXcffsocwp+eo6DueM/8A7cvSry3zqAqp2vcMGG+yew3A7ktxrh3qL2Vd7Ywt7ZkizXAkmObjValRy5RFeMKy3HuMBrZCbnpDp7qayBONaoTyNneNBZNl1RoRHYGq+tdg/D2F64jr+ilE13URiCF28jm1GdqDef1x2W1oNhVsCBjQzPAePRIuCF3X0/0m6YqBpZLYIRgP7JRrE4sARDO/WPJUN2wWIeCQKGn9BWsudVTgXcpn1BqqXPpVKdxN3emYLUdYNuhNTjjBp1AT4c1jpIVZBtKfPNEGTfxnKdrd7mNA==
*/