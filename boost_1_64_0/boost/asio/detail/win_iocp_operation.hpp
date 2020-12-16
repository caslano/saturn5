//
// detail/win_iocp_operation.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_OPERATION_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_OPERATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)

#include <boost/asio/detail/handler_tracking.hpp>
#include <boost/asio/detail/op_queue.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/system/error_code.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class win_iocp_io_context;

// Base class for all operations. A function pointer is used instead of virtual
// functions to avoid the associated overhead.
class win_iocp_operation
  : public OVERLAPPED
    BOOST_ASIO_ALSO_INHERIT_TRACKED_HANDLER
{
public:
  typedef win_iocp_operation operation_type;

  void complete(void* owner, const boost::system::error_code& ec,
      std::size_t bytes_transferred)
  {
    func_(owner, this, ec, bytes_transferred);
  }

  void destroy()
  {
    func_(0, this, boost::system::error_code(), 0);
  }

protected:
  typedef void (*func_type)(
      void*, win_iocp_operation*,
      const boost::system::error_code&, std::size_t);

  win_iocp_operation(func_type func)
    : next_(0),
      func_(func)
  {
    reset();
  }

  // Prevents deletion through this type.
  ~win_iocp_operation()
  {
  }

  void reset()
  {
    Internal = 0;
    InternalHigh = 0;
    Offset = 0;
    OffsetHigh = 0;
    hEvent = 0;
    ready_ = 0;
  }

private:
  friend class op_queue_access;
  friend class win_iocp_io_context;
  win_iocp_operation* next_;
  func_type func_;
  long ready_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_IOCP)

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_OPERATION_HPP

/* win_iocp_operation.hpp
7nh4F+wL79ZyfQOeqfax8B54kbrPg9XwFng/3AQf1Os/DO2LPQY7wsfhEPgEzIRPwSmwBk6DT8Pp8Bk4Cz4LF8FNcCX8E7wdboZPwOfhc/DP8DW4Bb4OX4A74YvwA/gStOz3BZgMX4Zd4DbYHb6m81U74GnwdTgJvqHlVmX20ZIWva9JcJXe1+46Hu2h4/l0mAn7wBGwr85T9INnw5NgIRwGy+FAeDE8BS6Bg7V/zIRr4FB4GzwdrtNwj8De8FG12+ncY+keTfidPlf287NT03m2R8fbcAycrPXtPLgOng8fgtwTif9CvZ9T4Q6YAz32+zWMg9NgPCyATWEhbA5nwJawCCbDi/S5+Qk8Fs7U+lAKO8NynW+cBU+Ac2AGnA9PgT+Dw+A8eAZcaOYVde+hrvOrDuu/jwvq53PrKVdp5OQvRK6NL+i9q55yNfWU21VPOeuD+sml1lMus55yufWUq6ynXFU95WrqKberFrnY4PL7sH5yqfWUy6ynXG495SrrKVdVT7maesrtCpJrEyaXFzw++Khuuc1eXd+p61XtdugcfXeWkwK4bkf4C9hd7b3VPgxW6vz7IjgbLoU18FL4PFwOt8DL4avqvl3d31b3T+EKuA9eAWPsM/tgG7gStoO/hh3h1XAwXAVPg9fA4XANzIK3wPPgTbAQ/h4uhevgzfAeuAneC9+HD8Kv4Hpoj3MfgsnwYXgC3AD7wadhNnwGFsPN8OfwebgEvgCvgi/Cu+Ar8AW4A34E34AeH+//sA18F54M34MXwPdhPvwIzoN74FXwY3gb/Bt8An4Fv4bfwTJ7PGrLwe/hKuhhXLoXNoXxsYH70Q22xH4abAuzYQrMh+3gRfA+5FbAargZ3m+nHz4L/wb/ANPiGC/BXnAnPBm+A0+BjYjnLPg19ly4D5bCL+Ec+AlcBu30XQu98Ebog7fCV+1y03DVGu4h+Ch8DT4G34DXwT3wN/AzmEx4e311+6D5uNSPos/HnWb3fzATtoZDYTu1O+Gzagk/SsOP1vBj7PBqH0t6Fn7steL5mNMTk42Zj6nCrO3BWk7MXkx7KlYWphKzHrMLk4t7zB1ea+DtXmvsEK9VglmLqcHsK/NaO2G/nsicQtjbYbnXSsNkYTrjtuF+rzUZ/yL8KuBq3Ksxm/m9A7ON32ORK8Hsx74KrsMcwH0LTOxF2mAq9J8KbcPkwBBMAaYf7pmnEo7ft2Gm8HsDHIl7CWYh162EqzDVmKX477RlYQ32RCYYtsIt2Pdj+mEfiynBrLT9MHsxA08jH5j9dpyw/RzyykvaCn6nweHYs+F8zDrcNp0GcVuOfRs8gNmN21rsMZlclwmNnpgN2DdjeuK2C2ZWIAtzYcsTiRf3NDi2jPzyuxL3FTAbt7WwAFZgqnGvwb4DU419M+ZABXa48nauN5d4MAexZ9pELhe2H4rJIAy/h/A7G7OV3+sIU4PZx++e+M/HvQ2TLhmYHfcji9sUTDb2ErjDLme4CvsKZKsxt2HfBmtgm9P5DTPhHmS3zoOYvbbfT8kH7ksxGT8lHNyMaXkH/vAgMhn8LsLP3xs5m7ywroFp2GtgNizALMSswKzD7MF9E+yJ7DY4kjh2w0zsBZj9/D5AXmL6cC3MQtw6w57zyRNmKWYI9lW4r8Wswz4Z+26YS1wVfUgn7gew74VpCyjn4aTtAcLa8cB+2CdjKjBrbBJuI6zCfwW/q+EmzE7c9mMSRyBPPNtwS+N3FsZ++S+HqzDrMS2xL0SmMxyCqboDedz3YnJtP8wKzDrMZuRqYMszSDe/1yPb5mLCYXrilg1Hwq3I7MLsx8T349on00bgV4LfCkw1ZgumDX574RA4FlOCsc4kDcg=
*/