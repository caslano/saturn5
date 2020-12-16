//
// windows/overlapped_ptr.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_WINDOWS_OVERLAPPED_PTR_HPP
#define BOOST_ASIO_WINDOWS_OVERLAPPED_PTR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_WINDOWS_OVERLAPPED_PTR) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/win_iocp_overlapped_ptr.hpp>
#include <boost/asio/io_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace windows {

/// Wraps a handler to create an OVERLAPPED object for use with overlapped I/O.
/**
 * A special-purpose smart pointer used to wrap an application handler so that
 * it can be passed as the LPOVERLAPPED argument to overlapped I/O functions.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
class overlapped_ptr
  : private noncopyable
{
public:
  /// Construct an empty overlapped_ptr.
  overlapped_ptr()
    : impl_()
  {
  }

  /// Construct an overlapped_ptr to contain the specified handler.
  template <typename ExecutionContext, typename Handler>
  explicit overlapped_ptr(ExecutionContext& context,
      BOOST_ASIO_MOVE_ARG(Handler) handler,
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : impl_(context.get_executor(), BOOST_ASIO_MOVE_CAST(Handler)(handler))
  {
  }

  /// Construct an overlapped_ptr to contain the specified handler.
  template <typename Executor, typename Handler>
  explicit overlapped_ptr(const Executor& ex,
      BOOST_ASIO_MOVE_ARG(Handler) handler,
      typename enable_if<
        is_executor<Executor>::value
      >::type* = 0)
    : impl_(ex, BOOST_ASIO_MOVE_CAST(Handler)(handler))
  {
  }

  /// Destructor automatically frees the OVERLAPPED object unless released.
  ~overlapped_ptr()
  {
  }

  /// Reset to empty.
  void reset()
  {
    impl_.reset();
  }

  /// Reset to contain the specified handler, freeing any current OVERLAPPED
  /// object.
  template <typename ExecutionContext, typename Handler>
  void reset(ExecutionContext& context, BOOST_ASIO_MOVE_ARG(Handler) handler,
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
  {
    impl_.reset(context.get_executor(), BOOST_ASIO_MOVE_CAST(Handler)(handler));
  }

  /// Reset to contain the specified handler, freeing any current OVERLAPPED
  /// object.
  template <typename Executor, typename Handler>
  void reset(const Executor& ex, BOOST_ASIO_MOVE_ARG(Handler) handler,
      typename enable_if<
        is_executor<Executor>::value
      >::type* = 0)
  {
    impl_.reset(ex, BOOST_ASIO_MOVE_CAST(Handler)(handler));
  }

  /// Get the contained OVERLAPPED object.
  OVERLAPPED* get()
  {
    return impl_.get();
  }

  /// Get the contained OVERLAPPED object.
  const OVERLAPPED* get() const
  {
    return impl_.get();
  }

  /// Release ownership of the OVERLAPPED object.
  OVERLAPPED* release()
  {
    return impl_.release();
  }

  /// Post completion notification for overlapped operation. Releases ownership.
  void complete(const boost::system::error_code& ec,
      std::size_t bytes_transferred)
  {
    impl_.complete(ec, bytes_transferred);
  }

private:
  detail::win_iocp_overlapped_ptr impl_;
};

} // namespace windows
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_WINDOWS_OVERLAPPED_PTR)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_WINDOWS_OVERLAPPED_PTR_HPP

/* overlapped_ptr.hpp
pk/zINNneJDpx3qQ6XOrQX5fRPL7wuSo1o8OMn1lPBckls3YMqh65PcMx7vgPJgq1wioPP6/Jsvx0bxWQGN2N+f9ydqzfyfVXY1y/gBdzteNbnSjG93oRje60Y1u/i/MrV7/zyH/3wzZPxTr1nWvh7h3m4VBpKcjOeoPWKbZE3AyizJlQfb9r5uDHRIQp6+zPyDHRlenWRuwSO5V9k8KJ4K4X4DjteZ9w5zrCPaXx7qSexjcgf1oP8AgL3MEOHwHuc+YD4W3afabKIkXMI414vv3p32GAg3CIpxhitsKmEG8PnkIpZEVNFHMFdOUBaKX4R5Rx1givjEuELtMC8Qj5rki32eBSLEsEOHWBeJL2Nd8F4jVfgtEpv9K0TVgrggOnCv68ZrlJZReM/isECuUNDHOMFTEGscIf9NQccqULirMd4ilPulijGWoaGtNFz6+Q8Vx33Sx1e92sdA/XQwLGC4094MnL+Ta5U0p7Z5BRuGvDdPOESYc7EdhTEGu91zS1hGmFlifnksnPBej9rnECTU+7/8fT2F+F2ARX+NF7BOHYZ807MPe9/vEUOxW0NS8T1yBfd9nn9hg2SdKrPvEQN99ooHfPnHJ7x2x13+3mMFzN67Qe9sd+IrwV44rVtHKMEVsNViFwViAHcpWiQyTVTxlKhCxZquYZ54iBvpMFx/6WEWMJU9ssVjFT5YCMddqFQetU0S6r1Vs8i0QbfzMYqbfFHHVzyoG+xeIA/5W0Shging1oFws4DXlX6Rn8WTALGHBmcNEU2W4OA1eUYaJbYbeItLoJ5YZw8QG4zAxxhQmSkzDRbw5SzxkDhA+PmGigc9wXEdtcclnmNhqCRPvWIaLRdYwsc46TGT41hElvmmilV+YSPUbJhT/MBHlP1wc8W8pugT4Uv+RuMZa6jGy/wjlx2UfyRyeo6LtI3Ld67Cm1XM5jc7UzNsp8F5OB1I4hcupI14rT+WUjyXJcppJ7vHeyimHby/L6XByT/BaTh8dQ3uyVVlOx1IaY39FOZ0nQjTldDelF/OLy+nwKsrpdEq7V5Xl9BEKY66ynBbQc+lcZTmdT2Ee/oXldJ94R1NO+9E17amWcrpDU0596B62VHM5jRVJ1VBOy/0FmTvASLAz2ABhCwuc5bTIVpw1yXa3CJXldFr2XfDQ9K9z+A8pH9R3K3P95fGW5B4B91pyN/V3L3OO/chMU3EcOdtfZCqlhi1mR75MmUZ7VBgCRbES6diHjNLahzcaYuht3GW8zfKKEsRl9/Up9E1SIrlcHaOwrS1GYRVNxBLTa6ZFitwfpxjHsGJ9nJituJfzUL6uvndRXWEIFZ8pgzh/XKI0+/kloXY6JmqivPqJlgY/8QnsfONtoqMJ/qaaYrnZDzt71MQOW35iiaWmSLRaRLp1qfjYiji+oZXKaxCfM5+uK0MJ52cg6J6irAacr0AZYQ7i51CriPZYwf3wvdMzXGm+QzGbwvn+CwopLd90ZaXZZDEo7uU/ks9Zj87xDx+1/G8SimmLydfgOP8cSiPHslaYTetNVoOsD+jdbDWgXjFE8jVE0DU0tBpFgOEZw+2GZHOMIZSvZRedY4vBJPwMleoYvo4Qil9hGYJ9V4L4/OOm2Z+H47wvUjqB1lHKaLPj3nfQO/lB4Prlvkuvl6h+ucIk7pB77LzMzyyI80DwdLiR59zqM5nGF5TuSb+jvrnXLJvh9nWZuWw6y0wol9n6zjJ5XWs036jexLO+w9vazd70IN7WdPa+RvN20tes/Gjt8wUnOo6oO/rrXSdOTSi5cX0N9C8oT9yu5rbETjACdj8/6EZQi1D7AowGW4HDELgZOAqMAX+j2P1tYGtQMQjRBjwCxoE=
*/