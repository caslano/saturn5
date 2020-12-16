//
// redirect_error.hpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_REDIRECT_ERROR_HPP
#define BOOST_ASIO_REDIRECT_ERROR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/system/error_code.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// Completion token type used to specify that an error produced by an
/// asynchronous operation is captured to an error_code variable.
/**
 * The redirect_error_t class is used to indicate that any error_code produced
 * by an asynchronous operation is captured to a specified variable.
 */
template <typename CompletionToken>
class redirect_error_t
{
public:
  /// Constructor. 
  template <typename T>
  redirect_error_t(BOOST_ASIO_MOVE_ARG(T) completion_token,
      boost::system::error_code& ec)
    : token_(BOOST_ASIO_MOVE_CAST(T)(completion_token)),
      ec_(ec)
  {
  }

//private:
  CompletionToken token_;
  boost::system::error_code& ec_;
};

/// Create a completion token to capture error_code values to a variable.
template <typename CompletionToken>
inline redirect_error_t<typename decay<CompletionToken>::type> redirect_error(
    BOOST_ASIO_MOVE_ARG(CompletionToken) completion_token,
    boost::system::error_code& ec)
{
  return redirect_error_t<typename decay<CompletionToken>::type>(
      BOOST_ASIO_MOVE_CAST(CompletionToken)(completion_token), ec);
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/redirect_error.hpp>

#endif // BOOST_ASIO_REDIRECT_ERROR_HPP

/* redirect_error.hpp
fMpcoIxWXFqQ68D5KFLlgcclcfag+MGQhuFl2BLHpJbJRai+dX3i94yArKhdjJWm3oZOl03UtohqC44uM5ZC4Y1yyb0Z7gedelJopwz8kAxaMcPvN5CkItPMFkj+XedY6hJMgujFpibBBC10WYg0TY+WHqwNBAboeAcWWRFl5hFzcR4wz+eEo3RDRpFicVu3kWPqytF/bX7YfrKUL+GG5NbVMZcgfI/hcnwOn2iVQxPQPznP+r5rOeKrEbah+YDwGJ7kx2LEz0c8zSPLEb8Y8e1IDiN+JeL3R/w2xO9C2J7kUy7qKyJMdMdlET9PwvB0fn8hO98pz7Xq31L9M8db5V23HKu+ZDg3/nnSAsTPL8LvBSy/dIqH5bmIfU8YHSsv018Zz74n8HsHufG/p69AfNpY67oh85hmvqfvYf2259J+zvq9pAPSv4xDb2Oq/27WPoLe1tTuqXksPvJaD2oPRqf2m4/1bZeg/TIxXhX6bz7+r43fCbVyHK6c1/T4ndlm7+b3/+BqcV9I+57cUI14TdGvqeb7uRY0+K2h7JVgaEtu0pTcajge0hPEd1chdUo/V9U0Gaq4UikGmu6Jb393csiwTOIEg2pwjgMnaOIJUl/EM09GChPeirbZWXntrLwR1aPBGYP5HrrZLJpNV0qvhLlP/CB/RA1AcetUxAmXVwAWy5zFcNKBWu/ohAXKcEhYpuPhYvnlQRDdZi40gFMExdIQ3W3EcRn7edj3ibUE/c61G3gtVKPyevmD0uIYpBcLZ7bfWOBylRUU5ZvyatE6KBJg587UZOTnTSbOpc1GXMc5pjlLZ45PobLZoT4YbhIkpegfyVKYPViZJNIwKYMutsaKWBxZLE6nWOnAz5xK9AJsMgXaLIbXI7mggZUS2cIsv5jxZJ4sOnMsjAfJkzlhI9xFCDdnJiffbpiWXDhyqRc3fd5UZtirwnKLr4DKJBg5oj1aeH6gBmvZRdPTEd47pGXlJrfuYimvnRclJ7fDrfZOfm35fnsy2xfjOqI+n68jeLy/Z1+oX+HKc+QJNQh3mcue72hRv9VH59YmdSdnzlRrPRcnuP/F7+vOmdyMfiWmy/VP5iP+toz466nFMTrb/zeT33KMt4CVfyXij860STrLb91UOncx6K1N9M1x6G3M6z+kd+hptF9b83kG0rfkGvH3M6/zCyV93UyD3s5EV4DO89/fvN4vJH0epCON6OVI5/exJxRI/AGJ+g/jteX9V0jrdXb/cUrTfL+48O8ZF3/Vie98btM5RXHpZEcJzvy0brBrGpkbtIVJSYTGZR5odpaUzqQovsEWzQnwRyq9o7OyEAF+X5FLepBeD5opqAoi6WRRFENROJVp0BC+NugXRuFK0J6R5ajCHM7vxFyoXDENE7NaVb6jyFFiL8TFD/jlu9wiU43TXca9FuDH5ORxCt5LuL5fcuHJFeylfKbspXym7qV8CvdSPtP2Uj5Feymf/yUbInvDJbfOgFNTtsq4H+eMiX1a1v7kUq/Bc8Blya0PL261d/Pj7qGSpu/PrytJcL51bNPrmc0lTc+/9TnW+TcVwydyO0v+ffNvjRqtDvnIDrXXciJgz811uFzuPIcrt6TAWQo2Cbier/g+4JbBWs5/cIHQyoDlsXVfcvww4MjkwiVyi/Zyfl+23rP8nDftGX//VZdcPwb8FQl2K9dgfQtGJFffRG753bL+u+5tWTtEL+xu1Ydn43vzdOP7IdJxjOP+gNGJNr+saX35XRjvIr6/nCHx5ynx9fcVRqf8Uqc3LW9Gz/j3yAc0g2n4PfXSz9afrrKJpSUOR2O7nC5pb1NjdjgZ2ibWpxa1JZ4Oi98y/gw20mdysnQdpnQLnNk=
*/