//
// is_read_buffered.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IS_READ_BUFFERED_HPP
#define BOOST_ASIO_IS_READ_BUFFERED_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/buffered_read_stream_fwd.hpp>
#include <boost/asio/buffered_stream_fwd.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

namespace detail {

template <typename Stream>
char is_read_buffered_helper(buffered_stream<Stream>* s);

template <typename Stream>
char is_read_buffered_helper(buffered_read_stream<Stream>* s);

struct is_read_buffered_big_type { char data[10]; };
is_read_buffered_big_type is_read_buffered_helper(...);

} // namespace detail

/// The is_read_buffered class is a traits class that may be used to determine
/// whether a stream type supports buffering of read data.
template <typename Stream>
class is_read_buffered
{
public:
#if defined(GENERATING_DOCUMENTATION)
  /// The value member is true only if the Stream type supports buffering of
  /// read data.
  static const bool value;
#else
  BOOST_ASIO_STATIC_CONSTANT(bool,
      value = sizeof(detail::is_read_buffered_helper((Stream*)0)) == 1);
#endif
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IS_READ_BUFFERED_HPP

/* is_read_buffered.hpp
1nwDupd78pPVizU1Z4GkJjcybP5ZCeOZvdFcsNixsB10vCnJ9+ZZpgyvMdd9WauUgXHaZOEB4NyfEztIZJB3PVyUfM+bJEw6CIGxm8lzKFNWcxD0u97g4u2WrB8JQB/93EfLD5gW44iyFjHOYH8SkiGRH7SbjPmIl5qkU5ZJHcqa4KGqnnCa3nx1lm4oEN9Nrkt1SpwZeLL0jTevnEezsZgIhylV/yNB0D4lPOc9+coXJCCy5lIhRjT4EPLZIOjJAgSBjXmGTbZRYVCWsNTCdjN3yi3qBT++zWQrGynNHV0hhwch8GUhCLtkNdgbBQUvAsMZAYHiWUz2NmhW8TPmriKRSUEjvrAOxQiyHU2sDGEELzllm6MIqaVOFfCelm3ielgrUf8ugnKk7qeH63H20huim7JCksuc6xKCHIP3JFrUCkGOoQVGPevxIcDgZMQoeGnj9ESq5xxaqYJO55KuPThqTWEuOz53zCMJ86PL4PQ+1uQdLXVDtZ5Ls+L8zznchRbE71skqlVTSu/noCHjXtfJ7CSiIhyoLdRQfBfFE5L9JVNFSh3+kkeyzA==
*/