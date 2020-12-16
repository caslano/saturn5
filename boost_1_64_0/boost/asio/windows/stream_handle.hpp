//
// windows/stream_handle.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_WINDOWS_STREAM_HANDLE_HPP
#define BOOST_ASIO_WINDOWS_STREAM_HANDLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_WINDOWS_STREAM_HANDLE) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/windows/basic_stream_handle.hpp>

namespace boost {
namespace asio {
namespace windows {

/// Typedef for the typical usage of a stream-oriented handle.
typedef basic_stream_handle<> stream_handle;

} // namespace windows
} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_WINDOWS_STREAM_HANDLE)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_WINDOWS_STREAM_HANDLE_HPP

/* stream_handle.hpp
zmAOmAFO5L0N7wTngJPAxWABuBacAm4Ai8BnwGLwOXAGuB+cCX4IzgKPg3PAi+B80A/PeSEYAvYHa4MDwAbgQDABXAx2AZeAPcGlYH/wXnAguFzw3pCy3qN6l95fCOxqLryreI2mB8A24ENgR94rMhl8BEwDHwUzwLXgePAxcD64jt9XGXg/+HvwSXATeAjcAvrgvM+r1wX+GRwDvgLawDfBRLA8CXIX7ElYVaZLK7TLdcUs2x2DPQvZa0BXyGKwT8Puhz0Hm9nNQHLfInADLMl/oFYGfLq7XQ7slWyXBXPActgKlguv4ndJD1f5MCLFIJJhr+K8OeAG2Jy2SAv2ImzjeKf8eK6nQQT3wm/YYtjHYF+BPQkb3Bv3A6vKl4fBsRo5s+btkFs3G0QsmAob0Q5pgQPAqD64HlitHHoZNhMdGtaPTCL2o+uXRXVT/eYW6/+18v9N2f9voWbsfzLX7yR08Nr/I8Pwnejh2lbLzS7KzcrL0YynL4BL7qvO4Y3X7K9Vv/lW2S5AGvzNd/RFxBi5zwo2zF7PiCu4qDTn9RRm5+TgnrIAujbNfIDiKYLOQe1GjjMVWsha7AcpifxuwxnNfC8Ujwblc/uR49XRzHOYMG1KPtLl9mceHV8hWiEVbkdynNqcJsVBmk6ZagIdX49rUShOnowTLvw4jpqLQvkaCujYaFFTRPJ1Oa49QupnhSiUbeTjdMws253Pk7sZH1fEKXL7yTULMnl+Q9w13lWy1HPxs3VZD5Gem9vaBvys4Jchw9GzcJERys08th8XEwj6gz/FC9TDld7z+Fzb+En2Ny0qvWu+f44XTDJ4uvpsyX1ZFCL1bbD7RUCl983PmuP+Q7RDSPQR0P25vXtKN02ex6jMQuzXYA+Lmu7vnMLmybBXRTHyxXbYk/IaKq9FEcPXoZm7oskXeSKUdb2lFGaESBaBdO+q64T9mrT5SOqY5tKxjaKPsIqRqKnuA3ksAOWfcO6HK6Zw5WhfRYvpuBrKY5TWeLkv/RIKk4ZymUDph8K1iPweFEbybSzuQoqhyGNGymNsb2Auzc3KazyXhv1c981Q23Vp1KZ+ct3GXgtNxn+mjO+4peCTjtnIg9RGvnryDesjc+ev6vPRpey80U1Oo31Gbf9zy6PXttpVcHX++Q0vLdhQ/xmEV1T/wgP5i7/7ptneQ7/tGRX7aeJrt1628CYbPUr3dfug8ZGfZlyM9S2MOj2v/WVcz1wj7Q16x9umwMVX/thw25GGMU/06+ZNFrnxffpvVPaK6qv6j2/ZdMTTiedtXz7/98N/S3gb/nfS8/wmZXDU9JiVy3dEJK30Pf3PL9BX3Ur1/2DWob0/f3f/xbvvq1/r+eWjkVeWkn/k67OXX22U8eqSkn7PLv7z1v3eZCPvMtDPlM5v/jxrQ/CR8M39FpwdM/lyxjpvspR32e487XHK30P+rpbiRwA4mTN8DrxU2sBaYBEYCRbzeqqFYDS7G4D5YFN2NwPvBGPZ3QqcCMaz+zzvz5/G53+Zz18DXMTnD4VXbd5LtR5Yl89XD+wG1meZLgEcwrLbcJbdssAYcALLbpPAFuB8luHUc7RiGaEN+Hs1Hb6us7KOo3qfrku975OwgmW9YJbtWoI9wM5gCl9XT7AX2AvsB/YGB4N9wGF8fBQ4EMwEB4NjwTTwHnAIuBTMAleAqeBDYF/wYXA4uBYcAW4AM8D9HP4gmAmeBH8Dfsr+6j11Ba1q3wvoD2ax7FjewiB2wZ6DjWoJ2QC2FHYb7GnYsfB3lYcqyUIkB10EtbJQcCukCUaD7WAdctFk2FLY1bAVGjlpZ6vKslIMy0slLDMtBctht8PugT3N+rSabVxlqWFgOZg=
*/