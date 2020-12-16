//
// detail/thread_group.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_THREAD_GROUP_HPP
#define BOOST_ASIO_DETAIL_THREAD_GROUP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/scoped_ptr.hpp>
#include <boost/asio/detail/thread.hpp>

namespace boost {
namespace asio {
namespace detail {

class thread_group
{
public:
  // Constructor initialises an empty thread group.
  thread_group()
    : first_(0)
  {
  }

  // Destructor joins any remaining threads in the group.
  ~thread_group()
  {
    join();
  }

  // Create a new thread in the group.
  template <typename Function>
  void create_thread(Function f)
  {
    first_ = new item(f, first_);
  }

  // Create new threads in the group.
  template <typename Function>
  void create_threads(Function f, std::size_t num_threads)
  {
    for (std::size_t i = 0; i < num_threads; ++i)
      create_thread(f);
  }

  // Wait for all threads in the group to exit.
  void join()
  {
    while (first_)
    {
      first_->thread_.join();
      item* tmp = first_;
      first_ = first_->next_;
      delete tmp;
    }
  }

  // Test whether the group is empty.
  bool empty() const
  {
    return first_ == 0;
  }

private:
  // Structure used to track a single thread in the group.
  struct item
  {
    template <typename Function>
    explicit item(Function f, item* next)
      : thread_(f),
        next_(next)
    {
    }

    boost::asio::detail::thread thread_;
    item* next_;
  };

  // The first thread in the group.
  item* first_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_THREAD_GROUP_HPP

/* thread_group.hpp
d0/eKHHrtJ4okm7FPLXPL237C28J5J/j2zvnuPAsh/xzfITnHLf3/d26TTujs7e10UVcoc8VMtN7G7viSHN8qS7TIeoxMnOcy4TP82UyFjny7NxOnSMn9/zwsZjC+2DG7CrL30c9KTcf2k33UVsr3D92dhTxKAPPrsUp8hsY6ijz4hsVGM3RBsIxyrNrQqbz2XWB5j8Vndji4Dw4X3w0m3vH7O2aff1bNM80RoH5Iz7LO1+gzqUHdVSpS1RUjf77alWOnuwmtvJJGaI/iIjqmX+Jzj9N/N/LNUTDKjCWD2ieZNISc0SnO2kdgRvo3+70ze5q3mYlJ6WndrAC+99H9fL7Gefetekncr/ZdEav1tdKk3RAplYhusr3dmH+05dpUGVG9LZf9L95brYTHRfk51yV3ud+R9fNuu+mlk6nUre+P4aGjn1Fm9D51wPaF56iC8LH/uCp1S5jL+Ms/JnhfWF8Qhyi87OoubVLH0a243aT234flYsd+YUix9nQibsgv5scPhkn+zM/aK8iZcbQplR4OEfqJn0u1XyboO1GfwSfLR/q/G3ZG0qRuUUZGe9UM/er9dxU+1nX6bxjbf0l+k/SX+kXqvyOkjbX0vzHZMm7xRIfIvJMqGIsF6Xy7OinfcQc79A5EZ7l8OQpntSZ5rkxVniyhOd9eAYpnuSe6d353/5N1eQzUubDb7q97fW4Loswn+vt7yuZz3cbXZBqM/bITRq5w55fq8Tv+hzR4ZoEPs2cKrrQPva8y/pjNE8Fajye6hviX0Z4dzM6zmfpdO+E8Dki3wTCv4tOz4D/dJ0eovkTnbE4hH+w0QtboNMDbdefMnO69N90wz9QpytJn+Rvn+bvpvmnVZQePMtuDy9lEuz2/dyr5nvFPOOSFmm7HBML4zyd3iyEn142z8geOj8l9Fnsn65Gl+scVTe7HEEe1HqmVJZNlXukXD1rNc9LPAEekm92qRs5M7Vccm1fZZX9OX+MLtc54VR/mzln2qznfUUa9yw3/UfbqTk9x8zV9l1k3gvP7fAM8+tIdXLoSAnPang+4DroSLUyOlJhPOvgGa6u07bmbaOP1TGUpytzsrGX9onytJfN+mvd1Uct3/e084Ao4ncpPar5i4J6VO3kNwlz2fgtmRh6Lxk99kRb7AnRYxc+Ne/gE/2rbvqcnlshsYoHt7f0kSwNag0N4f7MuSjsHvPZfyvyq3a60ka0Itr42e/nNzrI70nZe+sEvoaMuSF18RyX7xF1P68OvZ+FdzujV3moTv9sed3P8Btb3Ar4y0kDCZo/OfT+LDLX3yYYH0anE2z88jwXW4bJOn+dTu9tynez3VMVpdi7VM6yvTMv1TybsKbQKuTetP9ue1LzJBt9z0adnidpItTpdKpD/7Kz2qvVeddamXLtFGta5ewZauDMs0LKX6R1OgN7ET59Lk/OwcRRp8/do21yhrb3+995Vs3/1jPSE/Oa0JcU/mLScr/UpCe29fLzYL4ZjgaH9I38vRTwZbba3CNhv49A89s+OfR+mGjOMZZhvgQW6LHg+gHdV4htGavhYj1H1UNsCo9Qf+ywUF+GwtMmmCdxxUabvHYRfesouVLMGkWpTmeY9OQQ3e2Kjs62DoZ5TUhbfcPG5+eNGz7SN3xMkW+PQnl/JMNH230hutvS/mD+ZJM/2uS3089m5XOhK/Xn6+eu/DaJ0t6XayvZfMbe15yjvjBbyhSZnH1Fvl7QORurHwFGRvWBIj6VnOsvIpvw9zXzrzSKuOLyfRK+lmFsJd7v5NSdLx7KM+CSgO687fN0TH7xyLEjfNO0+wr39RraKWWzRA6HXYDJN993zdCfH+2iP3+2h11A7cZO2cZRvqQ=
*/