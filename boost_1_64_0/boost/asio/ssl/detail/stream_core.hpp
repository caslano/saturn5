//
// ssl/detail/stream_core.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SSL_DETAIL_STREAM_CORE_HPP
#define BOOST_ASIO_SSL_DETAIL_STREAM_CORE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)
# include <boost/asio/deadline_timer.hpp>
#else // defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)
# include <boost/asio/steady_timer.hpp>
#endif // defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)
#include <boost/asio/ssl/detail/engine.hpp>
#include <boost/asio/buffer.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ssl {
namespace detail {

struct stream_core
{
  // According to the OpenSSL documentation, this is the buffer size that is
  // sufficient to hold the largest possible TLS record.
  enum { max_tls_record_size = 17 * 1024 };

  template <typename Executor>
  stream_core(SSL_CTX* context, const Executor& ex)
    : engine_(context),
      pending_read_(ex),
      pending_write_(ex),
      output_buffer_space_(max_tls_record_size),
      output_buffer_(boost::asio::buffer(output_buffer_space_)),
      input_buffer_space_(max_tls_record_size),
      input_buffer_(boost::asio::buffer(input_buffer_space_))
  {
    pending_read_.expires_at(neg_infin());
    pending_write_.expires_at(neg_infin());
  }

  ~stream_core()
  {
  }

  // The SSL engine.
  engine engine_;

#if defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)
  // Timer used for storing queued read operations.
  boost::asio::deadline_timer pending_read_;

  // Timer used for storing queued write operations.
  boost::asio::deadline_timer pending_write_;

  // Helper function for obtaining a time value that always fires.
  static boost::asio::deadline_timer::time_type neg_infin()
  {
    return boost::posix_time::neg_infin;
  }

  // Helper function for obtaining a time value that never fires.
  static boost::asio::deadline_timer::time_type pos_infin()
  {
    return boost::posix_time::pos_infin;
  }

  // Helper function to get a timer's expiry time.
  static boost::asio::deadline_timer::time_type expiry(
      const boost::asio::deadline_timer& timer)
  {
    return timer.expires_at();
  }
#else // defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)
  // Timer used for storing queued read operations.
  boost::asio::steady_timer pending_read_;

  // Timer used for storing queued write operations.
  boost::asio::steady_timer pending_write_;

  // Helper function for obtaining a time value that always fires.
  static boost::asio::steady_timer::time_point neg_infin()
  {
    return (boost::asio::steady_timer::time_point::min)();
  }

  // Helper function for obtaining a time value that never fires.
  static boost::asio::steady_timer::time_point pos_infin()
  {
    return (boost::asio::steady_timer::time_point::max)();
  }

  // Helper function to get a timer's expiry time.
  static boost::asio::steady_timer::time_point expiry(
      const boost::asio::steady_timer& timer)
  {
    return timer.expiry();
  }
#endif // defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)

  // Buffer space used to prepare output intended for the transport.
  std::vector<unsigned char> output_buffer_space_;

  // A buffer that may be used to prepare output intended for the transport.
  const boost::asio::mutable_buffer output_buffer_;

  // Buffer space used to read input intended for the engine.
  std::vector<unsigned char> input_buffer_space_;

  // A buffer that may be used to read input intended for the engine.
  const boost::asio::mutable_buffer input_buffer_;

  // The buffer pointing to the engine's unconsumed input.
  boost::asio::const_buffer input_;
};

} // namespace detail
} // namespace ssl
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_SSL_DETAIL_STREAM_CORE_HPP

/* stream_core.hpp
7XQP2h8pk26pnwUS1739MdLGjktGWHXJA5/bVpfgfdLtrAviurdPRtqMLdkjrTY5H3wNXl3KJ5dYn58fC1jDAl5lc1tFx6q6WmWTKl7pcVMIevhsDnmZbA7pI4z0A+6Fz9rosVi/Vis9nJ+FFwb0sZZ29Gnpgj7Iy0kf81qGUVZ9lkK2Telj/1zrNukC/nZ0aeuCLm5nXUw21pBl1WU5ZNOylS6WZ9QCsx7gDaoH4juvR0GIbbJqtFWPz0LWrfSwf95cEXhf344u7i7osiIntP6STd97w6lLMmgVZOuVLh17dvTKJVvmNReouIFKn3tC0Md5TFZzneb+b6PPlfq9hdKnY8+Ozc76IM6sz70d0IfjsqM+vGfHGGO1tdX6vYLSx/zsWBR4n9COjbV2wcaKQuz3O7KtbVICWdc4nw6hPQcKP6QD50sXSFz32lZ/m2uke5xVj7Xgy1V6hPYcmOusB+K616aQvsWmEsZbbepz4PMoPczPgWVmmwJfUJtCfOdtqixEmzox3toWFZBtVDqE9kwHftUWCaa2QFw321SCjU3tnWDVoxJ8R5UeoT3THXXUA3HdbFMJNvfCnolWm6oGnzZe6WH7TOcx2xb4g9oW4jtvW54QbWvaJKsuGyE7UelifT6rDdBjYjt6TOyCHrUh3qdETbba1mbIFik9Qn/W8sokW+YpF0hc9/YTpG99Z2Cjyxb9+UTpEvqzVoOzLojr3r6C9C3rMrDfvxwrqctyUJ3uEzzN5/ezurTGUyibr/h9ylZ5fPvDxgGfFt458EHVEzsd9ZXyx2u+NAaI3D2iu0c2UYoX/XzxS7XzyXO38Mh0r/C4DTwzka7uezaX5ejRC7zYt6m4ep3wLrHhzZN0ZAzCQVX0c6z7Z4U/V0uDJrLn3GTvu4+R+vpS13j/XDf3QfKFF4wOvR28fmelvlQfQV3gHOuC7yjulnPUnT5LoSPOiY6mdRQ7ztXkuA80QJcFXYNyt4w3tZnsK8CFtsaxWPkPfkX4b9XK/GuGmUa8YT/gmtri2roaY3v/0psP/CNmwG9ML6m7HUg791xf3Z0fWHdqn49HXSgzeFaFsB6Xa29NY/xp8eeFNRHi97T/0dgda4e/NfPDJ3MeHbThkjInv6ROfkY77k/U3m9rx/2z2vvjdPbbmniRfv4W7dURecVDCh4Z/07L+JqZUzruZ9Ten6iT31kn/69Ofkad/JI6+nMV/6OcYpN13eJHDjTS8J++mPitFP1GBfhiesPoy4p859jwvW7gyyVftA3fawa+lhDTawtSvlcUHyjDOb2XDXwTg5TvZwY+d4jp1Wc4l+9to4+vIOm9ZeBrzXAu36+M9RJCejB9fq+A9iZfIugg+X5DX6/vA9PoY202fazNpU+4+fSxVkQfa/X0sbaN8TuAH9M36if0QXeGPuj+TJ9rfwU+TJ9ijwH/BjxMX2w/AWpI5yVAJPB1PQh8m+GTzEe1S6ZzfRcY2yXTuX7yjXad5lzfS4ztF2J6rUHKN8jA5xrhmB7QoG8Qe4039rsQ0/OMcC7feQa+xiDpTTX6pBvhXL4cY72EmJ5rpHP5HjXqO9I5vUeM+o50Lt/DRnsJMb3mIOW73qhvkPS2GevZ0f7AZKyXUaGllzvKuXwlxnoJkt4aY/lGOZev2FgvIabXOiq0cd+VFdr4m5vV/jgo+maF1n8bs9rvR9NAR8k3hnxRoGzyDaYv7SRgOjAZOIJhyuO67CyfQfnhlIcs5BE2jguj2+9Pej71QfI5n/lMZz4zmA/CSr4liPwcys+l/DyRR9hfTgi236+QD+bXnfM5wHweZz5PMB+ElbwniPyzlD9E+cMij7DRfseE1r9ax7Rv59K+Y50=
*/