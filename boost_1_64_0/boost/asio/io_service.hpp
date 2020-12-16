//
// io_service.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IO_SERVICE_HPP
#define BOOST_ASIO_IO_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/io_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

#if !defined(BOOST_ASIO_NO_DEPRECATED)
/// Typedef for backwards compatibility.
typedef io_context io_service;
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IO_SERVICE_HPP

/* io_service.hpp
mMjevjG62KCKval48YmEysvREoDx0Tn2e3ycXj5/2o/Gs4ZsHXUx5yMnLCEGrHwwVPQmG+mdSCi2ogP5QUzrkNVpEUT6eCE+RvF8tmME+pN5FJ+NFXC4iXwi0j+SEh8XS4nfLHYdGSKPjH1miPlTqD0pUn3OJ+3ROB3d32ek7Lja6POMbL5YV6TjGqdno0ZOz9nvx3I+NYDRSzSM802TZ6txvrB50kxFFzTVGy464YHG8xle11CnvBsKZ8hrB2cejpThtb1dmn0ppeM6moqWHFbhh6IXRtXKkejCT0ZfMpM2SW98asS3VRhfkIFi5KgadIl+l2/gil60nU2qX6330ukdNO7HKpVONjpX/LVwGIXtwzGd7id3fo7+5mVyvnDcZdGpe5iIlDNT+HmvfFa+9a3joQICxXT4lWz8JG8Q44v5gcbTRad+YanKvY9KYiXlyHZ005rQSvFFHeyKlubbys35Tg8j94MpDrdT9R0CamXENlR6UiCGXc6jeK6CsVWealufUnGLLvZJEceb3TkovMUQDkoej5j01M2mk1tdxXlBnE4qIXmkd/JZbaSQVc1Q9L7BZAruZ/H8lo4fy3ldth1UHsejHWf6WNq0n7DYdHlom9VT5CO2s+pHVlScvg1px03xKUXx4Uo7P4GVrPpCXiS10mQZvXNLe7tLDtgQoQ2rqnBZPimtxvkSdXhyzpfJWX9kYYy8fMbn5XN+mfIZn8rn9VNajEB89pN6tjTfOo9trSQvxreG5SL5YIV4Mb7K5oJywm4jdRevtyVXfyE5+GKG6hvK87dh/iIW55MdUA+W5Tt7cGJy1AVl5eweuHh+1APl5agHyvOpB5z8PFCOx+nrKgrj6BEqSRHdNGG2QDZCDaILVbUh0c6XXjqAGmdoiUN0gkBXXH7spMvfE+yJhHHoo3OTzSfoYfFyKbhcKdWc2P4EIHpZ+xqcRrisdAL7LuX9bJVOaDBP1ynWT+iES8oHaS6nfLHW4umUn1R0/rI6y11a24+vJOrBPNZ627EhG1hxyeWY5mXVL7ezTiZj/vxK/Okr50p/CIXjHhGWv8493s0fWeWOH2tg/Lq5l+SvGL3KLT/+6NLpe3VJ16++tPwvqd+4QpK9K3xRexPkYCFQ1ojm1NpbhGLvwPGD9iTO/Gi9Ij4SZZaiA16wN9DY+oEWD0r/zotbi9BLbG8+c9GPFUwoH9O8LPs3o1nzcvT7Ur/roNKBc1n1FOPKEx695UUrDuy9YcqdX/3sw89+7eT8nlBgweK5s6+67cihlcuXTLl6x/UdVzX7/VWLaqYvWjzvykeHrvfNfWj8zIbTJ74wszfmX1arT68NNAeqdV3Tb77xpVedOzemn7vnxNLTY6enL5g/beFbbrnh6kP7Xz5Hq6qqGjY3P/H2D7zkiTXzq+af/eqJeb+458urcrlm76GRQ7M2NMx58tEjB2u99ZX1d9/xpaseuP+zawq5QOMvzp1ZedONNzxsetUVV/SENy3cEWpfvC28+VGfeN9Lr9UqKiqW69XLF9fMWpwz/Q2HRw8uqqnRas6MnZk1fv+J+rvu+PwjVuqzVt77w889LpdvqR/Zv7/q8Ctf8qizdxyfe2DfC6aePv75Gb29zXoo1Fxz5M37l933wy8+YVbF7NkffP8L1tz8ipc9ut3fNeeDH3jh2m3d1z3y1InPTh3OtTa95dYXPLZmXuW829788mvuvOMzD+uN+paMnTxZ9cFjBxqbfb6KUHfLvOfs6rj20N6Xzp6uTZ++eP6cxxy+8UXWsfpFc2c8olqrrg6F/fMf+O3n1p77wfElD/3mS9cW8hvXrFw255rly6Y97tixEe/B/S+5YlbllVceffNLnnA=
*/