//
// basic_streambuf_fwd.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_BASIC_STREAMBUF_FWD_HPP
#define BOOST_ASIO_BASIC_STREAMBUF_FWD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_NO_IOSTREAM)

#include <memory>

namespace boost {
namespace asio {

template <typename Allocator = std::allocator<char> >
class basic_streambuf;

template <typename Allocator = std::allocator<char> >
class basic_streambuf_ref;

} // namespace asio
} // namespace boost

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

#endif // BOOST_ASIO_BASIC_STREAMBUF_FWD_HPP

/* basic_streambuf_fwd.hpp
ZcA39rXedXiVO61Op4iOh8ZPV6vwE8GPpHYJn83XzzB9QwHzM3Xpiuk2EOSKE76RWZB7helI3RriRWAP/A9/a7bOxPRBzaMogLiEs1vRqu4EISF/WSOwJ/tgWztI6yLw48zNzIHZoM2cCMeauZ8RmSC1wrFlZxWvemLtrtTrRxU6wn+vCDIWSdmuAQbcJ7XWh4DOcRESQ6AcPApmrC1yMHawGAds1MgiP3sIyi62CajqbPaKe/ZlkMR5G0fZU2Hjc0fHp1ZVxVjdxBBK2SARcRTwi0gfmxeYcgRq/AQv3NRq7vBus8xC+l0kwSB4Q5iHmwo8vkvywMFZjKE+oqzsaVAPRVA7F0fG+9mj9VuHeSkYQyU5OT7kChIhqqplisZhCTt6hk2I+WbJfKHWX8wgYfdEXXDZOCLJWQqLwOs6LtGrWS1qoBTPDb0/kAY9UrxexCrQ7FM2FSAoQvY7D3gL3KlSu6Jjq8jAdVI4BAw06OsiL1vBvxMNW+wu2KjTHjyd0oAcTTj0hzqo8WEczKDMspANbpiXImAOBHlXcK5m0DiDmlPsYPI6ZMhqGidSNHjI73bAzGbnHID8WhoQS2gK0XLDcnCGbWwOnParBhXtuDCw5tTWR7XfDuWgWcWUi1tyQTCINoaGzw/mCHFw
*/