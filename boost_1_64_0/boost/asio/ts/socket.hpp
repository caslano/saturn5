//
// ts/socket.hpp
// ~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_TS_SOCKET_HPP
#define BOOST_ASIO_TS_SOCKET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/socket_base.hpp>
#include <boost/asio/basic_socket.hpp>
#include <boost/asio/basic_datagram_socket.hpp>
#include <boost/asio/basic_stream_socket.hpp>
#include <boost/asio/basic_socket_acceptor.hpp>
#include <boost/asio/basic_socket_streambuf.hpp>
#include <boost/asio/basic_socket_iostream.hpp>
#include <boost/asio/connect.hpp>

#endif // BOOST_ASIO_TS_SOCKET_HPP

/* socket.hpp
uQa4FLhBn7Ph92F+6/aFnLMZALq6wIHULx/Ec0VXAMdTP/oe4FjgP4HjgF7kMR4YAywGpgAnAasCJwNrA6cAmwJLqBc+DNgaeBXrtSfwXQ/4Ketlyq+nWa/NrNdDwAuBjwBvAu6gHvsTwA+BTwENpH0GWMvgOSHgbuAVwOeBVwFfBM4GvgQsB74MXAPcA1wLfBW4EbgfuA14APgk8DWzPOBB4OvA14FHgduAx4CHdD/zmw2wRoR+bsvzXHk8v9UOOBp4MdCkuQS4CtgVuBOYD9wF7AF8F9iTet+9gH8B9qb+dx/qfRdQ77s90A28HKjPYX8ePIftCzmH3YznjFoCU4AtmK4crozpmjr86ZL5LqKox14HOAvYhPrq+cCrqRd/DdtXDpxHPfXHgIuBS83nDcfhZuCzwFvNdgFvA/4IvBOYinLvAtYC3g2sD5xraVfHL6O362O261O26xPL+bvhTLeW6fT5O57rqgk8xvlwHNiB5676WM59vAe8CvgB5+GHwEXAP5FPTwCXAD/S57W4xuf7hU+f1+KP57UcPM/o5vksD3Ak/VNpN+Ba2g24hXYFyoFO4HKGU75wnYwxiSBfEkDnAybzHH4KMB2YCcwGpgKb8RzqIPrHAjOA4/10PNfGtSvlXt4vPNeWB3eQ+VVlva3nFBsyfWNgMs+9pNMfOGd7munbcB5az9mmg64BMJPn1LOAXaUs/7nkbJ5PrwacBqwBXA2sDfwYeB7n2/nAasi7HrAmsD7wpMN/nuKO13GeAO5VuD/DuQ65VA5ce7jBcLPgyuE2gHbnobOfu6jImYvKcxYRz1lUnrGIcsbiIPjuEzjfG+hvuAK4YrjFcJvhDsJ9B1f9MPgGruBw5bmHyl/lr/JX+av8Vf4qf5W/yl/lr/JX+av8/Xd+/279/3EjTNe6eQtR//9l+v+p0Gi+2LzP4BY39qd6IVO/7v/aXHxf5d55nkN/m1O1gV/DPVQHaZ7w753nd2qZ1wphsdoGdRH3NgM0ootAe+qTJa6XjrtS7/2BTt81WaDjB0rad2qIXpTWzboIOkp7gGtAdynqEl+lrqdqvLu6qaAUE+9OMNEXlxR3ftwF/K9PXH0Eet28l413+xZnYo8Azst7RJKNM+8RokLcI4S+jxGwuVwk/lwjYAt8st9+vRGwFc52UUcIbUHYKPjjU25rhDa8Y34jnmTTq/uHI1xf6K9It+ZJS58Xdhs/eURxaP+x70lLXaEPkRZ6LOz7YBz3xNEHZ9cVkjap8DblAT9km6xtKHP6E9/KTG6B+wh0u2xt6CH3gFvryPqT7taz3rFo1sEXUoc2rMM8V3g//gV0ZU9Z6zCgpGjENGwLRKoHaXmnhUf4G9QjqI9oiyePW3QkChhv7eviCvQ19Q90m1LZzygffn/5vMuFPCdlmm3X8/a0O/K8XaPbjukeed6CJtq8ZVz0ecv46PPWNFA3GHWbmPm/O28PZEHeRpi3s3iuYgnqWxM4A2jO29NPW/o82rylzkOtZ0zaS90cC6a9INI8ZlxjrQNXXdIOcXPc8Jus9UqqSNwYM466FiVaj6SqxA2ypJumeaF8l9TdCJSZ9Zzp76HPcYwQfzUVKW2TZ824cQ7xB2m1rtcDuXDncB9IRWXPP7yRZc+p5y3jEF32gO6Xy54XfME7amUvC65TS8yPF6x16D91xOTSMVOmTopQD9Ly/gVXBNnDeC1bHjgHnc9Q2eIKyhZbO7ZSl92DAmoAP6EM3WVtx5llKGkbaj79WPwnLDK1UArmPSukv1HuEskgn0140Qwbhv3rKqIBFSZvOX8+kLT7xV+g86pr4c9iXa8fJK45yoDfUgakOXgpTve7Yr8H5stHku4=
*/