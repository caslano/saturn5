//
// ssl/detail/verify_callback.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SSL_DETAIL_VERIFY_CALLBACK_HPP
#define BOOST_ASIO_SSL_DETAIL_VERIFY_CALLBACK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/ssl/verify_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ssl {
namespace detail {

class verify_callback_base
{
public:
  virtual ~verify_callback_base()
  {
  }

  virtual bool call(bool preverified, verify_context& ctx) = 0;
};

template <typename VerifyCallback>
class verify_callback : public verify_callback_base
{
public:
  explicit verify_callback(VerifyCallback callback)
    : callback_(callback)
  {
  }

  virtual bool call(bool preverified, verify_context& ctx)
  {
    return callback_(preverified, ctx);
  }

private:
  VerifyCallback callback_;
};

} // namespace detail
} // namespace ssl
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_SSL_DETAIL_VERIFY_CALLBACK_HPP

/* verify_callback.hpp
y7OW5VnH8pSzPAgreXcQ+asoX035WspXG69rY0PrZy1jQ+tnbWND62dp2aH1M3d2aP2snnzDLfUAWdZDKjCZvlJTJeyXbw4in0X50ZQfI/IIG9s7O7R+5hrnnM9M5vMZ5pPLfBBW8rlB5PMofwnl54s8wsbxbVxo/awxSD5PMZ8fMp+nJR+EjeNeEPkfU/55yv9E5BE2jgfjQ+tnE8eH1s+KxjuXp4Ll2cDyVLI8CCv5hiDymyi/mfJXUx5hyONHvY/Bux7K6/y1Bl/mA4D3AOPp03wwcC9wGH2WZ9Jn+Wj6Oh9PX+czGT+H8XnAbwMX0ff5cp6nj2e+Y0AaUg6zj+cbmf+X6FP5JuZ3M33Q3sI9Ehroi/arTP9WoK7X14Dl9EHvAe4G1tHX/DX0Rb8H+HXg3Tyf1BM2uR8+HEHNoGOgM6CER6O0HNAqUD2oCaT7sfXE9NC2g+jP1tGX7WYbf7YHHrb6tDX7s7X6sj0JsvqwdfBfa/FX276v2lD81IqPWpN/WqNvWqNfWlCu2Ret1Q8tZNaiPoEBvmeV39mznyjfsxa/s1afs2Z/s8dRx9q6KPibDeprFn5mjT5mg/uXLUN4OygB6e5DvdK/LP3KKl+y4ke2BfE+H7JnHkZ9TgrNf6zrjNGHrL3/2NjvIw2QvQ9Zq99Y+oxV/mL3g7Zebecj1tk3bC7SD/QPm416COYTdqHyBWv1A3vBuqhu9wWbBzL6frX6fDX7e52L/0fQn0+CYh+L0rJBC0Ee0C7QQVArKOoHUVoWaCHIA7oNtB90DHQalHAAuoBWgbaCGkEHQcdBbaDYxyEPmgsqAm0FNYIOg94FRT+BeFAeqAy0A9QEOgJqA7mexBgEWgWqB+0GHQQdB50GJRxEPGgFaDNoN6gF1AqKegppg/JAFaDbQAdAx0CnQa4fQm/QQlAFqAHUDDoGOgNKeDrsjzZ8hI/w8f99fNr+/8qqS4tLago3lVfqDgC75v8vVYuOW4EHAHeBu3DOrIULZ8+as6Bw3uLllyy9dDGKLz7sPsnCBBvnsrdGmOeyU0G3Q77hHJnjm7P0cnfBpYUFeUvnzZpbuAbFr8T2j/rntdz/MaMX9573z2lTdkDIc6QZMs/pS+P8uLtFHvuaTDGvD5wWiZ+Ab4bfxuRRi21ZUSOo9MLyEtQdyqn559bjNZ9MtCFuNfcaVnE23xxb5yejgZBH+Ysl7FLh1XrZVT03s+xJhn1xv4eYo3ZlX4eZ2zV11dWllbUof7v1qNfZW6yzMSnmOltB33vJzHMA6FoE2hzyba9t27rYtj1SveXMzjCXsyCK69dZxkzQN1BOV6q1nJjRLmdBreXk3HaGyA1W5UY6al57mKwpoTFTZoHiSZK1A9O00PemVToa9khGHjjHPKg7ymTbRlk9OacBGkhMhbzbTneovV4+0zeug9BP+nVfK3Jp1N2XTqLyqXWjhCPUHH2xK3Rde4iuzA86raVOPw3oq0epUxHb87OgGxHT6KQT/S5QJxySh1qr8CORm65Nwq9vX9gPXKGVXS/nKyznywHl3Gz0B8j+mQ+7SxtmU059nJbC2tc96ppyA0PuH4H1OW6YfX1W9OaePLSRK0AHh6JtbctZV1lYVbmmlPUZL+WUE8pnXJnIzdcGII9zQSw/00sSuSeG6nJ6Z2MfUfHL2q1zr35A0U/yVutfkC7OMV3ofC91xnmz/8po67VpJ9qm1U7nmvbHLq/cAEPbbQQ7dVPxg0JuO2O/p25sT6YL3T6gbosHmtfDnYy2tztXmo1udZViIA42B5mu2dw5afY2d1sf+zLm2pVxU3V5bWlh0HLmdrGci1Q5zXV5jH74EJDDBfrjELzTM5WzuLY=
*/