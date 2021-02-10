//
// windows/random_access_handle.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_WINDOWS_RANDOM_ACCESS_HANDLE_HPP
#define BOOST_ASIO_WINDOWS_RANDOM_ACCESS_HANDLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_WINDOWS_RANDOM_ACCESS_HANDLE) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/windows/basic_random_access_handle.hpp>

namespace boost {
namespace asio {
namespace windows {

/// Typedef for the typical usage of a random-access handle.
typedef basic_random_access_handle<> random_access_handle;

} // namespace windows
} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_WINDOWS_RANDOM_ACCESS_HANDLE)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_WINDOWS_RANDOM_ACCESS_HANDLE_HPP

/* random_access_handle.hpp
ErydKaK3s9H5Wf9lv9C0V2OX1fd9FG3t/NJJvbWnXjC5dIRwT2DfKkyxRr+iOwrJLmbJ8Va+7ja75+JPIc8sFOSnzOXe1XIf6lm7utCZc0Rf0GHmUe874cAR9GGb5GcN25SbT1BLAwQKAAAACAAtZ0pSi7BP87wAAAAQAQAALQAJAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL3NzbC1uby1yZXZva2UuZFVUBQABtkgkYGWNvWrDMBRGdz3FN7ZQmQ6BgLfQQlMIGepCZ0W6toUvukFXLtXbR02GBrp+P+ccJE09VNkmsZm+ZSGzJz73eI3qTkzwlAt+G+9KlAQ/k18UD4OfXUrEj2YXAoUe226z6Z7Niys0Sa49Cqux1pq/KT7nqJDzFVSIWeHXzCiCcKeLY2wy+m/tzNfu4/h+fGvwOxKLKCVtGWEYDlBq1FjqE1wKOFWsGtN0u4zsJlRZ4XQxo2TQj/OFa2td6cwFUEsDBAoAAAAIAC1nSlKNJ+QPtAAAAPwAAAAoAAkAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvc3NsLXJlcWQuZFVUBQABtkgkYF2PwWpCMRRE9/crZtdVUmkXheykUFp40uDLD8jLfRqMuTE3Kv59reDG
*/