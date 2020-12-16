//
// detail/handler_cont_helpers.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_HANDLER_CONT_HELPERS_HPP
#define BOOST_ASIO_DETAIL_HANDLER_CONT_HELPERS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/handler_continuation_hook.hpp>

#include <boost/asio/detail/push_options.hpp>

// Calls to asio_handler_is_continuation must be made from a namespace that
// does not contain overloads of this function. This namespace is defined here
// for that purpose.
namespace boost_asio_handler_cont_helpers {

template <typename Context>
inline bool is_continuation(Context& context)
{
#if !defined(BOOST_ASIO_HAS_HANDLER_HOOKS)
  return false;
#else
  using boost::asio::asio_handler_is_continuation;
  return asio_handler_is_continuation(
      boost::asio::detail::addressof(context));
#endif
}

} // namespace boost_asio_handler_cont_helpers

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_HANDLER_CONT_HELPERS_HPP

/* handler_cont_helpers.hpp
O91jkY9H7EadQ+5DTBycHOYzEJNQu7wRMQV1DflmxB43V8gHvgvHjDqF/DLEGPTJIs9FTEAdIF+MyKKuI9+J6EbdQi69G89ltx65/z2457v1yAe+F89Z1CnklyFybpvIcxFbUZeQr0Zc5h6LfCdiJ2rvfTguxA7UaeQexF2ofeSbp+MYXT0DY8njev4S5gT5Z4ht7rGz8FjELvdY5OMR21HnkFci7nD7RX5xLx6Px7aQnzUf1yLq+nyMYT6OAbXnYzuIRajTyNUFuLegTvbhvoS4B3WuD9vsQxvqCvK1iIobD/If+zBO139hm3f2QozHbR956iI8F1D7yGchau6xi/BYxIB77CLsZzHOC+rskjbvGsTEL2M9cn0p9o3a5YsKmE/UyPi7thgz6vQynNvluFZRB8jnrsC5Qe3yfYgqapcP78e2UFeQj1iJsaHOIl+PGPMVbOcUPNcC9EfdRL7utDavgDpYg/cqRZz3nZi3dXjdPAPXPGqXn3Imxo0aGX8XC/OA2tuA17SzMU48to58YAn3dtQuVy5AP9Qub0dMdX0uxP32ItwfUIcZMYTa5QUfwJyjdvlsRBLbT25u886/BMe7031Gxjx9CMeLPhnktyB247hyyEsQe9ycIG9C3OOOHXn8pbiu8FiXL9yCPqhdTlyObd08OcwdiCNQuzwFkUGdugLXD2I7+meQT0bsQO0j/wix86uTw/y6D2NuUbu8CrEbtcsfQoy5ZXKYG4hJqF3eg5iC2uVDq5gT1BXk8z+C84H9NpGfeiWeD9iOy69E5FG7XEAEqF3+IGIzapcHXKBuIR95VZvnYzsuz0asQY2M77zRH7XLX0BsQ+3yuq04B6hdfuHVbV4TtctnIvagzlyD1xpEEtt3+VUfw1yhdvkdiGNRpz+Oc4fI4VhKyFcgdu7EvpBvRNyBuoF8N2KXu66Qx38C5xH9k8hTED7qDHIB0UTt8ocQLdQuX7sN9+rG5DB/F5FCjYzvdfDajNrloxBZ1C7PRkxD7fJ8RAG1yxsR61GnP4X3Bp/Ga4Sbf+TvISqoXT5pAPOF2uX5iJ2oa8g3IoruPCLfjSigbiGP/QzOizsW5Gcham77yDMRFdQB8gcRJ39tcph/gpiG2uUJn8XzGrXLT0FsRO3y4YitqF2eitiBOkDuvBbnGttsIh9xHa5zrM8gX4PYhfUuH3c9rnnULr8XsQe1y/2Iiejv8lXX4/GokfEZAufRbafe5i1H7EZdQr7083huom4hj70B9wpsJ4n8fMSEW9EH+Q7EGNSZL+B+hdiD/jXkVTtwfWO9y6ffhOcUamS8HuLaRl0fxL3lS5hP1C5v/ArmCrXLDcR21JWdbd5vEOnbsN+b8Zp7M9qw3uVrEHehdvl6hIc+Lr/8qzhG1CXksbfg2kCdRt6FyKP2Gm3eFsRU1A3kP9yK+5s7lttw3d6Gx6KuId+ImIS6gfxLxBr0z+zCcwjRj7qJfC9ilxvb13HeETvdvpCP+zrW78J9CXmZW4+6hHwFYiLqOvI3ERNQt5DH3o7z+HXcc5BfjNiNOoP8FsQ21D7yOsRW1CXkKxAbUdeRv4lYj7qJfK/bjhvPNzAexG43HuTjEduwLx/5LMRWNwbk2xFT3BiQxw/hekCdRD4McZIbA/LbEFNR55BXIu75M0n3H3/VfAdw/MP31/1acWexttXXRRLCF7FQXDQa2e6mWchcWwjh2mKNcEcjk7mbWCz2ZY1GuMyPELsjCbHLWkK4SEK4iIWw5/u7P16P12tnn/M5n/M559zaHvthTA8/gDU6PedfX2CyMd38XUyK8XwO7oxnwbdgnq7xshgf1+XO542P6/JgLI3r8hFYEvPwmZgZe8g=
*/