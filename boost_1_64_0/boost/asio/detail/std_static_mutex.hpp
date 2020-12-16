//
// detail/std_static_mutex.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_STD_STATIC_MUTEX_HPP
#define BOOST_ASIO_DETAIL_STD_STATIC_MUTEX_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR)

#include <mutex>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/scoped_lock.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class std_event;

class std_static_mutex
  : private noncopyable
{
public:
  typedef boost::asio::detail::scoped_lock<std_static_mutex> scoped_lock;

  // Constructor.
  std_static_mutex(int)
  {
  }

  // Destructor.
  ~std_static_mutex()
  {
  }

  // Initialise the mutex.
  void init()
  {
    // Nothing to do.
  }

  // Lock the mutex.
  void lock()
  {
    mutex_.lock();
  }

  // Unlock the mutex.
  void unlock()
  {
    mutex_.unlock();
  }

private:
  friend class std_event;
  std::mutex mutex_;
};

#define BOOST_ASIO_STD_STATIC_MUTEX_INIT 0

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR)

#endif // BOOST_ASIO_DETAIL_STD_STATIC_MUTEX_HPP

/* std_static_mutex.hpp
Xs1Zf+amb3PXR/5T1j0TfRs6ZdG3+f/mO0f2afXwDWP7+yXb3/Rd5u9F5m9v37Ic0ixkrW4Za4DxDvqE5kZPIN/6sKGDXAubXGEZ8TW1yY0JI75CS74/4csiVw0WiNy5iDSFHWBL8bcRfy/Y0ZI1u+Cl4v+d+CfCTnAW7Axvl3DrYFe4Hl5o1+PI9dYRXb+rHidMuRKfnJwTOakrmx4nTLnkfeHJtQlTLiMMuXq+9xV5j6J+dNgkjzwYyK8KMwCeDgeKfm6Q1E8OHAaHwjyYLvrHDHi36HVXil53ExwNt8Mr4B9hpujxJsGX4Xj4qvhfhxPgm+J/V9I5DLPgfyX9eNEDN4NjYUt4CRwCL4M3iv54ERwGH4UXwc/glfBvcCr8FmbDGMphGjwWpn7q6MuMM9OxdDxQMT3Vjscjuqrj0VUNzv1l9VWHHv916qy+e/zE6q2SthJOxbH1xOmvem+N6LBOhA5rzAHqBvcobj/uCC75FdLAjcAV4tbiSnDf4dJe/e3psyK/yC/yi/wiv/B+J0//P3XGiZj/f6bo/9t01br9QX0uyRx5UY9+fTIz+gwfkN5bTAC8uv1rWvPNaHT7oTrlFWrv1D/ocdKQiLTeQ3Sny7sE6NkJU3k9O3GF6NmPutgdbHG7tikFYevZ87qG6NlNmYxx0LPf14XrcUlXq9rD17WT78D0JkSHpvcA6aV5x/onMNYfkqYldbAysA4kTEOv/qKmdx6EZcb3A8+n6O9lJhnI+Sw5b6/D3OTy8+Krw5VSh0a3UVP5Sd8/BwKqY6QZVAbtYkLLYDXxZewRe4MJTmXg3A4zbHm8rmbg/JVBct6ex8UVyOPyoDwSv8zpCNo7PdbYnJp9nR7qwvFiyc90h/zIfJTbnXU4EraNbW0IyXvgXrYid6qZj35E++90nZf9pT5fpP0ZJnx913nUNeHnWuY0mX8jYbi7GlGmcTL/8X7cfZrydxjz2X22A7c7jMd3NOWv8+s4r8Z9TruM00fmv5y0cfe1etx9T7UPWt0566fC2R9ces+Gl5Y9WPHxdedx6F//uLuz/sFtPL7i+iXvGKk8l6VvzSpjrHuLyMU7yDW22+yHGV/anvDkMsKQm2VJHwM3O+xL01z2ETwHtpex+c6wJcyAreBlsDUcB9vAmbAtvB6eB++C7eAqeD5cK2Ptb4Q5Rpr9GmMSr1Xclj8yRnp8Y6SR8dGTNz6647WTO0YaGR89/vHRN6izH3BpJfhxWbglJZEx0KDfL/T9Pz435wTY//u+/zM622z7MVG9aMTwHgOGjrhIBgD09//0cr7/m3fi+ej9TgmNyGZn37hTwHcXYSr0/T/Q/l1FXPL9b1u3x+X7v3i3y7VV0Na+qLP7GMAEhzGAu5WtvVu5VNLe3thnRssJ+V7sLfb2JbuNvX1omlaZNn8Stql8LwbZ3Mu33+da5jz5dvSFqRNoc6/NvcX2z8g00PF2t62Vc3Mr5cL/xnOyO+8YZHfe3dhbyXUE2Ul2iXGxIy+uhB15ceVti93syJNjXezIiythR15cjh15ceVtU8OxI/e11UVi032HrKe1ECrb1DbP+mxTK95WCWvaVIa7farINdZy2FnY2qkuvHzL305FlhIQG9Wh2j/d00nsU+lz+OkO2KzJdbGWmeBpYVUJmR+i8rpcn6/nCbLdNHNWntHn+xp704e1v4anFsfUvA61N9qsOMpW2T1WqZUUn2DvM8Q+UuQejfPZbl6h16Ya6TZfRORL4nxrtV2dFA1D7DdF7hhyj3ttM2P9fbWkjT9W7C2vb2W3tQxv7cv2zwXaVma42FaODrKtFDtMudd9dRmxr/w1jPMcOk+XW7tL9j84+qfreyad+1U=
*/