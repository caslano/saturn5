//
// detail/pipe_select_interrupter.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_PIPE_SELECT_INTERRUPTER_HPP
#define BOOST_ASIO_DETAIL_PIPE_SELECT_INTERRUPTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_WINDOWS)
#if !defined(BOOST_ASIO_WINDOWS_RUNTIME)
#if !defined(__CYGWIN__)
#if !defined(__SYMBIAN32__)
#if !defined(BOOST_ASIO_HAS_EVENTFD)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class pipe_select_interrupter
{
public:
  // Constructor.
  BOOST_ASIO_DECL pipe_select_interrupter();

  // Destructor.
  BOOST_ASIO_DECL ~pipe_select_interrupter();

  // Recreate the interrupter's descriptors. Used after a fork.
  BOOST_ASIO_DECL void recreate();

  // Interrupt the select call.
  BOOST_ASIO_DECL void interrupt();

  // Reset the select interrupter. Returns true if the reset was successful.
  BOOST_ASIO_DECL bool reset();

  // Get the read descriptor to be passed to select.
  int read_descriptor() const
  {
    return read_descriptor_;
  }

private:
  // Open the descriptors. Throws on error.
  BOOST_ASIO_DECL void open_descriptors();

  // Close the descriptors.
  BOOST_ASIO_DECL void close_descriptors();

  // The read end of a connection used to interrupt the select call. This file
  // descriptor is passed to select such that when it is time to stop, a single
  // byte will be written on the other end of the connection and this
  // descriptor will become readable.
  int read_descriptor_;

  // The write end of a connection used to interrupt the select call. A single
  // byte may be written to this to wake up the select which is waiting for the
  // other end to become readable.
  int write_descriptor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/pipe_select_interrupter.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // !defined(BOOST_ASIO_HAS_EVENTFD)
#endif // !defined(__SYMBIAN32__)
#endif // !defined(__CYGWIN__)
#endif // !defined(BOOST_ASIO_WINDOWS_RUNTIME)
#endif // !defined(BOOST_ASIO_WINDOWS)

#endif // BOOST_ASIO_DETAIL_PIPE_SELECT_INTERRUPTER_HPP

/* pipe_select_interrupter.hpp
x6XCFEpJG+0yNeUqIyjvAAyNtNM0Z587RZVLC0mRfFpKiuTUVqRIXq1FiuTWElIkv7YgRXJsQb1rFJMiebaCFMm1GSmSb4tIkZxbTork3bakSO6texnVGSIjS3Jw5eVWCQvTizzJH6XkST5uRZ7k5FrkSV4uIU9ycwvwVMrPBWAqlKOLSZU8XUGu5OqMXMnXRaRLzi4HXQt5uy0IC+TuuiRN/i4jadrXKp20hpMWypeRtNRJmzhpK5DGdFZlM5LWc9ISJ20M0ujPVkrenEskreOkxbNE2YnziaStnTQjaUp3EUnjbpYSyz5Lbd1ffGQDsdYka9rNHJA17WfOyZp2NBtkTXuafWctJWtKBCvSpkzQIm1KBQlpUy5YkDYlg4C0KRvEpE3poCBtygcG2lpKCBF5U0bIyZtSwpa8KSd0yZuSQkbelBVK8qa9zJC8KS+k5E2JYUXelBla5E1+PCFvyg0L8qbkEJA3ZYeYvCk9FORN+cHImxJERN6UIXLyphSxJW/KEV3ypiSRkTdlidJ5Q5qQ142UJ1Lypn3UFXnDLCRvLfLGnU6lAOZt8rZw3jbOW+C8dZy32HkbOW+F87Z23mwWyEHTC8V0qU7a0knbOmlNJ63rpA2ctEzZmKSVJC3aa1rDOQvz7j63a998Qs60c77LyVmLnCnBJ+RMyXNBzpQ9A3Km9BmTM+XPgpwpgRo5UwaNyJlSaE7OlEO35ExJtEvOlEUzcqY0WjpnVR4NLyLl0ZSUKZGuSJkyaYuUKZUmpEy5dOGUbcBYQMaUTGMypmxakDGlUyNjyqcRGVNCzcmYMuqWjCmldsmYcmpGxpRUS2esyqohGVNaTcmY8uqKjCmxtsiYMmvijI2dsYUztiFj9FvaPUTCUdIkY4UztnbGzBlrO2ORMzZ0xnJnbOmMbZ2xplIaGKP3gqZlTtrcSSudtIaTFjppfSctddImJI3+q8qhcaVpIE3vZ3okTW9oxiRN72g2JI3+q94rikma9jgKkqZdDiNp2ueISJp2OnKSpr2OLUnTbkeXpGm/IyNp2vEonbSGkxaSNO16wInVO5Irkqadj5b2+sEanVi977Yga9r/CMiadkBisqY9kIKsaRfESJv2QSK9ExiBM7ix/4Svt+mtswdn9GkH7p6clc4ZfNoDj589cPmNm6N8fvKR9Z/t88GZ3gcOyRl92l/i9/uv5PjJWUTO6NUe+H5wRq/2h70/aNPeG7zagwQweUsGCOnVHiQB0KZ9OCNt9GovSgXIBI8kAuQBpoF6/ww5gCmAGYAJgP7/ee7fLP3I4lfy/8s/LQG0ThngVTMAE8DL/T/dP73/Tu9P4Pof9/wZdOuB53e3/79x+P9Hf3+Mu0/ovF7q8fOP7Kt/kMd/ucOXvz/a3dPb09nL19PV/0s8vd4f0c3Tyz/TycPH08X/GR6++AjfJJaHp4P/T/h3und6dzp3+na6dnp2Onb69ZW/j7Vbpy6fPqZ/elW3Tq9Opw6fTpdOj06HTn9Od05vTmdOX05XTk9ORw7tMbpxevEn3LeZtd5Ygg/+GckJ/c+PeQ+55qx78DYydLYOTwaMdapEZ7TCN1YenAvo3TujdXAuQLPt7adKejon5N7o9pQQuOiRCc2wOedX/U6+jdkV3z1DJ3fdpLN2NUkO3ssvdbLu8L38ECoCz0MKtAvV5oSSix7/YN03FpnZ0+/Y+yBhRQqgJAEUJEXFt6h178cYU2cFPej+ZGbRGxvh4/7Zvbw6dSSv1KRPokvCvzLCv1NQe6g78kZ9+iK6Inoid0TwQ3RDOuWX0QeRHU2utqbWUBNreW3xG3sPvX54PoF6umYnHDyDtH53vzo4ddjW2Zr03p2Tfs4=
*/