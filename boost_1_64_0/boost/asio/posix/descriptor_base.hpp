//
// posix/descriptor_base.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_POSIX_DESCRIPTOR_BASE_HPP
#define BOOST_ASIO_POSIX_DESCRIPTOR_BASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_POSIX_STREAM_DESCRIPTOR) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/detail/io_control.hpp>
#include <boost/asio/detail/socket_option.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace posix {

/// The descriptor_base class is used as a base for the descriptor class as a
/// place to define the associated IO control commands.
class descriptor_base
{
public:
  /// Wait types.
  /**
   * For use with descriptor::wait() and descriptor::async_wait().
   */
  enum wait_type
  {
    /// Wait for a descriptor to become ready to read.
    wait_read,

    /// Wait for a descriptor to become ready to write.
    wait_write,

    /// Wait for a descriptor to have error conditions pending.
    wait_error
  };

  /// IO control command to get the amount of data that can be read without
  /// blocking.
  /**
   * Implements the FIONREAD IO control command.
   *
   * @par Example
   * @code
   * boost::asio::posix::stream_descriptor descriptor(my_context);
   * ...
   * boost::asio::descriptor_base::bytes_readable command(true);
   * descriptor.io_control(command);
   * std::size_t bytes_readable = command.get();
   * @endcode
   *
   * @par Concepts:
   * IoControlCommand.
   */
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined bytes_readable;
#else
  typedef boost::asio::detail::io_control::bytes_readable bytes_readable;
#endif

protected:
  /// Protected destructor to prevent deletion through this type.
  ~descriptor_base()
  {
  }
};

} // namespace posix
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_POSIX_STREAM_DESCRIPTOR)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_POSIX_DESCRIPTOR_BASE_HPP

/* descriptor_base.hpp
mQcsE/9lSQl1x/TP8yR+meY7xj/FmijxWAMV/zOh3tZ4ymQc+zfp3FN+Id/KpmIFebRVg3sEp/UIWu88Y4ak0STjcol5xljfurmZ+EqJn5sUj5cDF6buniXxtTLuVORG625FWX3F5ur4+cNpQlOflKs2fcxZyDI9n0A9aAXXRfNvxrB05xim7eB+oekLzTzOHUT/JknYPCtXwiCypZCwqUmjSMVOfxdhxRK2KUnPULjPZOq8o1xoFspYX6Tj00XRM5VVZRV1Gy2HTblLhHZJUs9Qb3nGfcQtkbDypNH02VW0n5xM+k4583hzxvyMUWlJyYVp6cmpGWdyAjKpUO+s0n77Ezgbe5mzn+uNTbwHb5W6QFxh1Facpj+f9DPk3Oa3STuLVFMLY+1ka5akJ/QzCbOrdyq0fx0XDc/kd2+cjX1whBkcnKPn1DppO2rTTvd40OrT1+xI6GuYl0q5UFcJi9fVAuWnrhDuqiuGh/phxgtLw4v0fIrh0fD7wIuE3pShq92/0dt7vuOHU6kLt8XOd8wpXTap7OKV58/w2ED5wVTPOQ/4um4DhfR8baA828cr41FoWwNkVFshQTLC166tEOK7bivkB1M7thUSG2Oa+3rzdQ31ZrfJ14LS0rJ5C1asLFs836H3LdN8bPJ0Q++kpzK75VsU9sq3Fdo2X/lE54HytXWg87Zu6HzLtM7r/JhPnq6D/6jJ08IFyxasmLO0bNmcCxeI0qPjeq6PvZ9u6Jz0fOt6W5ZXvuvF6IGffKp0K1BG+NrVO/Fd1/vXcjvWeyxfVdnefD0/iRRNvkqWzCs9u6x08UKyV7Z42fkX2coXuX82yZMv+Lque9LztUFV3M8r48+hLQ6W0RRAkJzFHei/uBv6/9mkjvU/WfN22CdvLxXSX9/uPMfX7hk+aLtu98ucz0uQq9HHdt9x5Gp1y2Xa4a8LffrzbtQF0nPJNT3W9/X3P/e4+/ZTO/e4+/aOzz3uvv2ff+4xlq+8XG++XiFfbe58abUO1Dn0HfTn3ajXvy7suF7H+vNCnQj/ADcM90Vck92fR/PDO0tlTXXlptgx44gVn9cSz4SooamswnEWPfxOm+8uzWcsnSLhSZFz4JoSXFp+SnOmWVPrLWl8UO146llkpc/F30viHxF/jeEfH/justzQzFN/yLpQ0ujp++6SB/aQ+I9bvcw3WOvNO0mqxO2Lz+9VD+sdNmP7Cc0DltxFoPPp69RlZJOH7A7P6M/N0jpZYuagqm8NX2XeReM6VdurOv8VvQltjWeu7K7Xg9ROXovW6UZcvX3+/53ueiBflEXi7xnUAf2+LEZbzBmtzMCyWGLosnzfVUK7iCOFAVY/7/uN6mtGO+/tffQ7LdIlr9G8L+og75ba0luieT8f10jed+1y512/1pO85Wfp94VlDbVVpl0rj/ZXzVP98w+N5D/+rtW5vOVq3vIlb+bZJo88LzGPpp0/pIZ1T+p5+9/irrTLNyGPuoomL+H6Xk68+72cfCrfKLPe2v8O/FiaGclT9R0cv/sdfInhG67fEyKL8H0Pi+7Jwpcs/evG6np5XsS8u18qdDc52qv2l7qmnynxRxzxGxpaMC5aoGsNKRL/c2s6/5dxeu9hnme/Z6dQ9jnopp/9HnwFr8Fh+/PCXmmpmUkD0tIze6YYO87QQeN3F1KlpD2Ltb0kz/P7qG34HUKTprbiaTXib7DGWJlGz6TU0tRUXe+8p+NaocuQNejCgYztuCy5h6PFeweS0oTJTzY0rEFvS1xXdt6P8sRIzpvmU3bQ5uIEO7FvFKuHyEx9M3VD66H3/Tpb6IPntg8NVftaCDpQsdbeP7rTUzfNYiFdUNB6ofKNde4XmT0=
*/