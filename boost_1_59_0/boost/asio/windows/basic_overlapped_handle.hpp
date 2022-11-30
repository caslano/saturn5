//
// windows/basic_overlapped_handle.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_WINDOWS_BASIC_OVERLAPPED_HANDLE_HPP
#define BOOST_ASIO_WINDOWS_BASIC_OVERLAPPED_HANDLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_WINDOWS_RANDOM_ACCESS_HANDLE) \
  || defined(BOOST_ASIO_HAS_WINDOWS_STREAM_HANDLE) \
  || defined(GENERATING_DOCUMENTATION)

#include <cstddef>
#include <boost/asio/any_io_executor.hpp>
#include <boost/asio/async_result.hpp>
#include <boost/asio/detail/io_object_impl.hpp>
#include <boost/asio/detail/throw_error.hpp>
#include <boost/asio/detail/win_iocp_handle_service.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/execution_context.hpp>

#if defined(BOOST_ASIO_HAS_MOVE)
# include <utility>
#endif // defined(BOOST_ASIO_HAS_MOVE)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace windows {

/// Provides Windows handle functionality for objects that support
/// overlapped I/O.
/**
 * The windows::overlapped_handle class provides the ability to wrap a Windows
 * handle. The underlying object referred to by the handle must support
 * overlapped I/O.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
template <typename Executor = any_io_executor>
class basic_overlapped_handle
{
public:
  /// The type of the executor associated with the object.
  typedef Executor executor_type;

  /// Rebinds the handle type to another executor.
  template <typename Executor1>
  struct rebind_executor
  {
    /// The handle type when rebound to the specified executor.
    typedef basic_overlapped_handle<Executor1> other;
  };

  /// The native representation of a handle.
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined native_handle_type;
#else
  typedef boost::asio::detail::win_iocp_handle_service::native_handle_type
    native_handle_type;
#endif

  /// An overlapped_handle is always the lowest layer.
  typedef basic_overlapped_handle lowest_layer_type;

  /// Construct an overlapped handle without opening it.
  /**
   * This constructor creates an overlapped handle without opening it.
   *
   * @param ex The I/O executor that the overlapped handle will use, by default,
   * to dispatch handlers for any asynchronous operations performed on the
   * overlapped handle.
   */
  explicit basic_overlapped_handle(const executor_type& ex)
    : impl_(0, ex)
  {
  }

  /// Construct an overlapped handle without opening it.
  /**
   * This constructor creates an overlapped handle without opening it.
   *
   * @param context An execution context which provides the I/O executor that
   * the overlapped handle will use, by default, to dispatch handlers for any
   * asynchronous operations performed on the overlapped handle.
   */
  template <typename ExecutionContext>
  explicit basic_overlapped_handle(ExecutionContext& context,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value,
        defaulted_constraint
      >::type = defaulted_constraint())
    : impl_(0, 0, context)
  {
  }

  /// Construct an overlapped handle on an existing native handle.
  /**
   * This constructor creates an overlapped handle object to hold an existing
   * native handle.
   *
   * @param ex The I/O executor that the overlapped handle will use, by default,
   * to dispatch handlers for any asynchronous operations performed on the
   * overlapped handle.
   *
   * @param native_handle The new underlying handle implementation.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  basic_overlapped_handle(const executor_type& ex,
      const native_handle_type& native_handle)
    : impl_(0, ex)
  {
    boost::system::error_code ec;
    impl_.get_service().assign(impl_.get_implementation(), native_handle, ec);
    boost::asio::detail::throw_error(ec, "assign");
  }

  /// Construct an overlapped handle on an existing native handle.
  /**
   * This constructor creates an overlapped handle object to hold an existing
   * native handle.
   *
   * @param context An execution context which provides the I/O executor that
   * the overlapped handle will use, by default, to dispatch handlers for any
   * asynchronous operations performed on the overlapped handle.
   *
   * @param native_handle The new underlying handle implementation.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  template <typename ExecutionContext>
  basic_overlapped_handle(ExecutionContext& context,
      const native_handle_type& native_handle,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
    : impl_(0, 0, context)
  {
    boost::system::error_code ec;
    impl_.get_service().assign(impl_.get_implementation(), native_handle, ec);
    boost::asio::detail::throw_error(ec, "assign");
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move-construct an overlapped handle from another.
  /**
   * This constructor moves a handle from one object to another.
   *
   * @param other The other overlapped handle object from which the move will
   * occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c overlapped_handle(const executor_type&)
   * constructor.
   */
  basic_overlapped_handle(basic_overlapped_handle&& other)
    : impl_(std::move(other.impl_))
  {
  }

  /// Move-assign an overlapped handle from another.
  /**
   * This assignment operator moves a handle from one object to another.
   *
   * @param other The other overlapped handle object from which the move will
   * occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c overlapped_handle(const executor_type&)
   * constructor.
   */
  basic_overlapped_handle& operator=(basic_overlapped_handle&& other)
  {
    impl_ = std::move(other.impl_);
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Get the executor associated with the object.
  executor_type get_executor() BOOST_ASIO_NOEXCEPT
  {
    return impl_.get_executor();
  }

  /// Get a reference to the lowest layer.
  /**
   * This function returns a reference to the lowest layer in a stack of
   * layers. Since an overlapped_handle cannot contain any further layers, it
   * simply returns a reference to itself.
   *
   * @return A reference to the lowest layer in the stack of layers. Ownership
   * is not transferred to the caller.
   */
  lowest_layer_type& lowest_layer()
  {
    return *this;
  }

  /// Get a const reference to the lowest layer.
  /**
   * This function returns a const reference to the lowest layer in a stack of
   * layers. Since an overlapped_handle cannot contain any further layers, it
   * simply returns a reference to itself.
   *
   * @return A const reference to the lowest layer in the stack of layers.
   * Ownership is not transferred to the caller.
   */
  const lowest_layer_type& lowest_layer() const
  {
    return *this;
  }

  /// Assign an existing native handle to the handle.
  /*
   * This function opens the handle to hold an existing native handle.
   *
   * @param handle A native handle.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  void assign(const native_handle_type& handle)
  {
    boost::system::error_code ec;
    impl_.get_service().assign(impl_.get_implementation(), handle, ec);
    boost::asio::detail::throw_error(ec, "assign");
  }

  /// Assign an existing native handle to the handle.
  /*
   * This function opens the handle to hold an existing native handle.
   *
   * @param handle A native handle.
   *
   * @param ec Set to indicate what error occurred, if any.
   */
  BOOST_ASIO_SYNC_OP_VOID assign(const native_handle_type& handle,
      boost::system::error_code& ec)
  {
    impl_.get_service().assign(impl_.get_implementation(), handle, ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Determine whether the handle is open.
  bool is_open() const
  {
    return impl_.get_service().is_open(impl_.get_implementation());
  }

  /// Close the handle.
  /**
   * This function is used to close the handle. Any asynchronous read or write
   * operations will be cancelled immediately, and will complete with the
   * boost::asio::error::operation_aborted error.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  void close()
  {
    boost::system::error_code ec;
    impl_.get_service().close(impl_.get_implementation(), ec);
    boost::asio::detail::throw_error(ec, "close");
  }

  /// Close the handle.
  /**
   * This function is used to close the handle. Any asynchronous read or write
   * operations will be cancelled immediately, and will complete with the
   * boost::asio::error::operation_aborted error.
   *
   * @param ec Set to indicate what error occurred, if any.
   */
  BOOST_ASIO_SYNC_OP_VOID close(boost::system::error_code& ec)
  {
    impl_.get_service().close(impl_.get_implementation(), ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Get the native handle representation.
  /**
   * This function may be used to obtain the underlying representation of the
   * handle. This is intended to allow access to native handle functionality
   * that is not otherwise provided.
   */
  native_handle_type native_handle()
  {
    return impl_.get_service().native_handle(impl_.get_implementation());
  }

  /// Cancel all asynchronous operations associated with the handle.
  /**
   * This function causes all outstanding asynchronous read or write operations
   * to finish immediately, and the handlers for cancelled operations will be
   * passed the boost::asio::error::operation_aborted error.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  void cancel()
  {
    boost::system::error_code ec;
    impl_.get_service().cancel(impl_.get_implementation(), ec);
    boost::asio::detail::throw_error(ec, "cancel");
  }

  /// Cancel all asynchronous operations associated with the handle.
  /**
   * This function causes all outstanding asynchronous read or write operations
   * to finish immediately, and the handlers for cancelled operations will be
   * passed the boost::asio::error::operation_aborted error.
   *
   * @param ec Set to indicate what error occurred, if any.
   */
  BOOST_ASIO_SYNC_OP_VOID cancel(boost::system::error_code& ec)
  {
    impl_.get_service().cancel(impl_.get_implementation(), ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

protected:
  /// Protected destructor to prevent deletion through this type.
  /**
   * This function destroys the handle, cancelling any outstanding asynchronous
   * wait operations associated with the handle as if by calling @c cancel.
   */
  ~basic_overlapped_handle()
  {
  }

  boost::asio::detail::io_object_impl<
    boost::asio::detail::win_iocp_handle_service, Executor> impl_;

private:
  // Disallow copying and assignment.
  basic_overlapped_handle(const basic_overlapped_handle&) BOOST_ASIO_DELETED;
  basic_overlapped_handle& operator=(
      const basic_overlapped_handle&) BOOST_ASIO_DELETED;
};

} // namespace windows
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_WINDOWS_RANDOM_ACCESS_HANDLE)
       //   || defined(BOOST_ASIO_HAS_WINDOWS_STREAM_HANDLE)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_WINDOWS_BASIC_OVERLAPPED_HANDLE_HPP

/* basic_overlapped_handle.hpp
kP4BJfXQ3WJiEe+BkmJmLgArwzU3x++f6ziMzvCDZJbe8c5xwJ5uBmEzbs82JR+JOI6BWEi/rTzNjknAp+2QSykvEMamte0Chbz6ODGy5YV2d6PhSU/+cnjvVfmAc1VlE+azcZqTvod5t/3GLWop9vOMiCY+0P15l0W8uthlReCebYtfxAsVlzE/9XPHlWl4YlK0g446Q153tA8StooyNcZb6GIuNZjpSjAD+Z65nqqpct/LtjODPXFAdwSladH3nk5XM8SJ8L3reE+2aPICMVhqm1rpbUTadT9fHK5Bz6V7/zL4adtuPgABivuIzixt51YjRq+P2lrCVapvGv2HDZQGmuHq7k2sU4yXESIn3MD4aV98pXb0L0zz2tPc08x35FVixlVrt0HfoCmxnYCH0C0qSf0qO26nyWnJfmLIMpnWQXhvBW5vaeAKbgIYfsA5f48T0zSEZUCzH/BFRmIdgZ0Yb/RnduWtKVuixywMMLD7W+JBgR4oIF/c7z0jsF7cEjInQx2C0LzuXHyXGDBnXw7FjiTHvxObEPCLcClVa4sQmJ0vTCSAS5gBiLKXDz7Eb+8LoKLfem/qoJ+HQv8lxT1GR2+bemX87OztTju537AI743TjWGlX6/Cvv3bz4Br34zfvvLqP3hJYJehPZjwIVhgvc16uPMsKCe1HfL9uop4W+JdR4p8e5g+3ouE2t6+8Atm8CZTcgE1c4gQL0y295y9Y1pHSX/P5//EM6j97n4LszzH2tK4e92MLd/RGop2xnyLW4ipXaVWvThcXxszprr8ijfmJqZg3ss3mP6ZTxrTutDb9NjOOgyTKdApEAIpUwgrcP8MuP2HqzUd0YdrFols81+Ppg8IAKsBxq4ANOcyZ8cRIsC3kPI26MvorK7UjXvntfcquvH3Ltsv3xyMD3uS9TtWOQYOQxlFkOl2nION13fci5n/C5kEw48dzhEe/2/vzX85NW+5R+Fo4Cv7LTzi981X3OCLwh+2eyVT3hv3NWt33Opw4MUuF1/4Y5+e7GI33caUeUpFE9FtTMVcH0YaJf/WTLz/tfak4BnjMLdAZ1BL+JXT887TzyPfen8YAAIs/dOY33aj0xB3P2QnuRAAIh+QGzLQyJUwY/Be2kroL+ZlcowdeC+Qc1JKZ3LhPTIRtbTRBDYuYfkJxgc7EK0akgAnt3Zra1TLQ84/Y4iNxrqeXZmo20PyT9le6khV18FKpw2cwgHtFReJ7/ffhHoSnNW7F7mOXfhzGZE95nk/YB6sEfe+234NMz1dP8oq8dYX2ewkQEFPVknvWDGydrdO/zSA5qncGUsZyGRTTgc5zbEODLhwwNTA5TMuOu4bCt8kIkGz8Z1r/bPEcAx3d0VVDbdYsSS2B/ENluAMa5c1pLj4IgzdM3hyBc9mv5HHsQwIuc2hhmJZfTVvOW4Cf3vVr1LdhBvKjlcTqIYWf1HeQsx2rhPLxWIyS6gyzWf10rdja15jojU7vOALMQ3oiGrSm7rrvw1sY6aNNmTlXLa14w/NNRPHs7k0XILdO76AMqPZADjTLZWoDe6F9C7GEOYojUntjHB/BZefQn/CyP+3N/0jx4Ycdf8YleINv/qM3ihslm5AD7INxZNhcLqhbWkSA3lkD5h5dxyOIhTiDSxPMfd1o0+lbAuJCSeG5zj1Mbj6TfEW42fc1QeP/ONzrcCJVpyVFtQihkTUYT3WxX+maZg2qNvwL3/ln3g+Ip9bq0hnc3DR4PXntar0wr5EIUQYqGMe5EVX8yExpaxLBPqDA4f4Kge4nGb0AvomEjnEQt6Ws9uoTYOxAYg3jKNLRmHB2JJgh5GDE4/CEXEwVN4vXB7Z4oarM2JgXezPFmhXb6ulN5sd0vFDK112FEuAaG6ZnMCATpBrl8TwdsKl1/koSj3UgvaUVxcnt3I4bIF3MV8ZJG7LlpSSNjJTjx6f0bm5ki30Q7A/Sci5aHbXVqcPWDOwl6sEyPGtR60C2fxALyNd+MJ+7b4JGH94BZkeyQkycxQCB7Il/BFH+NDZZU8F2EuO7+5CeqFm6rqjkG2YX3tS1a0xdHMzQS8qMgIt4zW+EIytC2xz8x7CMPkm3gMXnM9wPjj45qUpERmG16+Dv+I1RD0m2jY/TTAITi+2Fiw0nZkpIdkxL3KtY9I+MihM99lRXzKuHk4wr11v9IOUD0y0ukOIb8EyFtmdiA5VT7gHMLafG0h0+EfjaUNwrv1VeA66T4xKXyGc2i+aNQSkWdetJOz9/M4usHHAWz90WSknTww+0ASEY+IMah6EwPXQ1NkVuAAjX53QqLLHA9gDoSr1w3MP9PrKwsfJ0mv50DsxV+0et4DJkH+xPDbb03HeRKsXHJa4lHWXTh/PofbLd2e0+XAbI+zQazjEXDLkVyeMD/aEhQYP/CryV3sa1AVneP1zyhmE87DDJEFDOexicynjVdVJiIBYTNXtiKVHjBfJ78VThJ+OvnJAz+0aGHMJpCJ4UVLXTb67P9RYBbDXlDAW0af+NFb2w2bIaomw3UVcpFdkmKn2+ChEn7cutW7L86+eLPx/zbdN+ad+d0zC0DaLPHzB2s+FJTKb/kENPtJBzGuJrCgv/4hnmfJsvltI1582GcNZ0nf3WgjLA8Qyc7oRrFafgDZgFs0DcSsbvZ9EBFtlmPBs/13I1X+gHoLaIeU0VxpzLrLJHlDrtp9+GXeIe5x/hkQ8obGyqzJyG3AzFsHB26Dw17trI8dYzma1YD72Y5R2iqU7YRECZVNolsX0UYT3VVMjTa6mHtf6h/J/qsVeh8NHJLW+wwncj19EhlxH7vKB9j34WFOvTCX9MOznpJSvseah58hGDuJ7/mzajYK77fdTeid/WyStqqB74UaU1Zv4bIjJR3UYSfK5j/P9V2pWjDD8pWsb9KZIcPeVhfqEVuiPTE1mDsNf2J4HcCDMgYupaWOVvo2yB3YN5b7OYnaw/QXto/1mcMwAOQtiWwLCS5wv38tYWtAerq+AOrNYYBtWYMEQD8ksDkHhw8/XlArXujgZZrYXC7MdZnvGEmf/rO0b04S+4dVkCodwXg6mHePTe+nJEfboN4fqnfufouhGH/woPtfZGVeEFk8ylI1Q9w1P9Z0M98b5J/KV894H213YT97sdCue22wlXm9nOUcOXGY23Wv2HKLbyfhXJZayhGGlRR6neiL2wU+qwnq6u/qaXt/F/GfG5bOpDMPYA+KFGSlJ+Ffn/jzBRaD1fsNg6Of352kh5mEt+S7P99YH1M88GPxIyz0KYWYks82QNDYFZvqafIj15NPXvaebVMFc/JGCwvnxlJMYn8kbPfN2E3aFg4QNJMp2iozi3dDYq3z/AHV3/zTO8CXPp0Bc93A/eJu8rj4uVtDqJ8VBxBMz//mbDn187klvgvq81ByKkN70vjL9bZABcaCKGL/tYtCM77ne4UBW737ZnT9XCQmZBXFZL/2otBvcg4fYxgNjRU6K31Knjz2pj703KFjOS3dVrT2Y1i5ZDYSLIlKr3SwEUa9JMO6i7OG0L1rYBcLbF+w//RflDy6Ny+1qgRWBVAU90xdZldATbUqa07oWUIyOHnGd6/qYHE5A4/WuFZ6KkKi7Y4/UZcwBJEnE0H9xOYGxyh7yJCXbYTn7u510cc2xGcJNZJ+2ET1an0PzHSZN/4DSd8MTAO3x/N8yTCIa2Jo1GgmD222xQCO6qRfQLcjzIC3q+09W5GNIsCn588AhP3WRsHQheBC5VhH/056zDXo2xFsfYDu0u/KFcHkEIoSdCJSoaR7jiw9RB+FbrA/vXYWV7QFp/q+P2ZtZ173TDYSMYU6PEibEdDYj2DAWd/qRqz2xfGwNa3AOWNG9n9vohZdrdhUURvaxsr9PFlBNz/7eqH8HH74JPlk+3xnVp2YAv9Z6fLUjn/C2SfM9dfA7TcyZMbc5hTjjkfH1YW4Tv1HP5sPf3xeYGr5HuUCDpylbOh8OSPeAyVZbmE8piDbAHskn+EIdmgd0TGBG+maoG5RBifA5WfpZ0OK5DhPC9sR3kOTytqfajphE0rSoGtZTaGPPaSoVLqWYU020OpnxDQbpNKyQVNzkuxvUONY3EZzTtk6hx3f3R9e/iji3FiI/bpn3PVzgDUAA+MohgZnpIvAQEjBbJi+lVyARX8bHrONmbmlOZwJPpL6jorNeewNAbzoEVkqyE3pxRLeSc6bpbiwfh3mA0wwSvsErxRCyQ4C2+gD6QQ0MpOLD1D29KTuQ8lo3vofLacn2IqQRJK6FrOlBXah7RXi2BD97An6djKd4/Z7C92d0SRt9EZl4g/3RoZMOHJeJcmP+xiNBwzC8J9zEfUgsIl+bcqKc6kYJh+JZ0a7dB2G7P2phazaWEG9weRYt/IaJw2Wrl9EnCr+TxV2HV/cRZ6OSiYm3byHTCqtMg8rxkPUuGG7Y/r9dK097PGhv+i777C56j6Yb7s28Rg/Ntbhrak/410LO1mMf7nLsG+rcviXvptvPw84MaS6bkjYpdfQNcH8cuFmA75vc0AAkzpxHA9PFS7n+jb0o65j+5Guur2Kc/IevR23VVGuE/7oJypkKWV3sQbGd1L5ObqW7beakvqrLhpJu8rB9GCfSN4Gkfl3IOsdkGbFAdYpMuIW3zFmnIj8sX/d4IOgfSM86qReAl9yPe/W/0wZk8yQpMJv5t5Y6VqLZbHH/TYrA9egwliiDacFhdH5UioTL3ArlVmvzNhmBFvSqDur/tDPxTEEKMmnSJwjfg/trbFY6aWXFk+NPhj3ts+ayhyDz+CEciIZY9x6kM3rKMurN+Y/kn2fL/J7ul0YczaG929kjMPYg8nwvDrk3bNSxsofl5ohvOLcSmTVR4jXMxH5qLZoEwDr7z/I+LE3lm14eoj2rbQwz1jXD/Vyh1k0xbrxI2hxV56cPrKETbVnS2sonRzruegD/vkHF3N1d5dkS7Jd/bloyGfltGG4k/VpE5znH3kUksHqLX7lYhCsF4o9QvJAWSscWGy/Nka6mv0R9vloc7QUlBKED1pOUBw28FVam6+TndQbHokEESfQJjjwTOwtK3PgMfvaZnsF2f6kmEDPah4xjKr0jW4o57lmrXuDog/I8LIcXNgVx3YVd3fFce3OkPcJRHxUOMlKC8qMPiHHmjGdlpPEXKsD40ixR1woL6uOt0AwyblGpqubMYy/TFC5IjEaUfGoXP9HWBYFoUiCHtjO9+6LKasb40X2iKetJqV0EFGN4PVWBU/acG1ej1GiuS8k0TW96yB0mqYizGfQRYCoUDWdNuo4kdca0pZWpQMmg4Kp7WAvzpCt55tAozC0ywOs3DtU2y4cM1OLIv1FY/LaySCJqLAOJOE5PJkaHDrmw/KKF4I9odarcoc+HD+js59N4/Tc7RT+xZbPNNtGpRSCPiUC++XI9zu1T6fkd4N0ogM5j3lfcJ5C+phO8htpGk47r6Gzpgs0QnG+beeZUUpBwELiGWeO1j8R34icSsbZR+l8+udeeV8wCpdetm8uY4pDzTYYHZ7BGeCJZPur7A/J9tzZbp4WLs0Ca3ImyQH0Cz0Ysykeck+M2EIi2UqSmUSOVTKj7Twcti0By+teFOVwUlIlAPCa+AdMTgjoXRweSEHwnyKM7dJQMVgbf4BPS2rcgkigfLKLxLFNGWXPxLFV7Yro33OB4q43KT+A4nQnpSVBW98itbJ6b8ARw4Toeb9va+/FarrromoqORaq97bu1nmc+MCkcuyW0kzCqDWOIEzk8MAZHV5rLZBiYTlLkMmKFqyqMRv8Uv3LZzfmAe/fpvgu1za6Js97vf1pQTE0TjupntJ5+sWugu9zFlZW0Cu4wGvn/SY6Aex5fxVY/1dLjn93V99tns3dpIAGofaGF5oW0Ng+qeutMriL9CrQ4O3CX4RAy7EKFhqAQpD5w3HRkuhb6StMhhQyR+TNFZesnFVQLV8uqehBD7uVJU97IKfTY1AqwqXPjGkpWf5sVA7+ZebAMisMuqvXjk1a8eerT7gk50a5GwFfaxoxO/YMayHB7JQFmgdFoWyD/uUEmbZCfE1wfH45WORqQMA3wjhuG5A/cegW0N/0NW/jwOWn9Gm1/tnLJ01rQPnOU7sqi853tCdy6eeE5ituHkvIpjXiqd/MlAJ9ZgdJbKyNjgfXYuYPJ7yZVrjiYya3UVsTfyxxvJYhvcKauXTk3n8ONuO+KP1TQPetIs7fHUllhxj1xWIm9V1ttXeXCRV/ksLrsQ3PjE4XNdal9tyc1PdThy3HZ3t93u1U9UMkzsKrcW1BbXkkzxm5sU01Bg+KhC1CcFXcXULKgc3rZs0H9CIfikKOmZ8vNO8zBqd/hnHLh2GWlbAciPT5ZTmFzt6rlSGNZYTmvmoJ1t2q0O7y2Z0nrcfy1Qa3LhVGd1AmDEYVd8GhtYwM7f20m1KN506Brovebnjfp86VLVrwX4k23vWFNdONe6/oauFay/HfxfMXbzQM5oKBiyqmrqmro2hxeB93LoantXapgp6qJ3OjzLGJkY12cf2XIU3FYQRW1+2U5JSG411tRYyil7t3UizMqWFHB/VEStR5qXAwkZO8mri/bU9frvHrwr9OEygvQRqv80rnrvvGBNKCwsXaSznmp8pZnwvqUmszm10g62ZZMNtDotWJ48BAJ97z2w6hPLBz6Z5i35YXVj9ic/dnOVzPZd2SB6yOBgqOko5DNAgpdBXYIoQrOvq6nBLKDZ1Vyd/AmLA/rpyPg+MMErG+wb3BVzN7woKJMa4wOy9umqFJpq4XnmBLi3+pI7aU6sFzPDKSHLFzSq/PVrt8DL5RljK/JZQHX/IviWaz159RK+XWgtB+aVu1vM6+OllA4vw1oVxhaQ5j7TjzS7dYxcrNlZx8AKHoz4cwS15kqizilMfKgCYl/I7c/1Bpl31zTgJgGXoywsC1qxFnG3KGbl1anMzCu5GJ3JFFIumGfb5ugl12Vvze2Gmi3ixFIeZrwRqcxPe6iCnxnpo/sS0qQPJJZYpos0pqkDpVYfZqudDd1GE/aoWQOVRh/miWK3xHdKC7pXgoZRukxutO93DYVmHciK0+UX7SwVfR48H/0Qak/x9SwrCiYJi+p3P9Bh1agOLcxtpjjo7KSMktPoi/uFTeZKaw79MTZwM/AmnnAwzpwv6LwN+T0mghsO44eTqSRGQO357wz7dN1HOh+pi92lPNZEl3lCnrsho82GJIVHVLS+RotfAYdCTt1EcEyOP9M52bRFgq8s7vJz2IGc1Nru0T5+Dw1MQe2PqGQmgF9VXD0D2PWEovKBwUqMQe6pZjZuCAGHMnkcwEB9bOY+bmJXY+vIzgS2Evr4I+AU8x//SwgiwEjOKA9QZlI2zEOrakdSwTgooJisJM9RDqQSMVlVSZSk8lkDXiT3keeKcmQa8R1AnQHIOhF7hiBobhCZhW3ArATxKg7tX2h3Zsufo8zAyBJfGEYivfyMdmMdlFd/ewMyosFsNBnOpLgCkCb5Buck95i3TMc+UzzEqPJEOCogmgAHeAr65N8UQIjgVCTbGMdzVEYljYq2qQk9dTsM4dq1pgyj7iap2chXpmumd/+jII9zMqxDuVPfTFj3Okv+P9CvQ1lIFqY8aT75KFzUg4CzAQvoEMdoWAdoQjgQd6LIEQMzSKz
*/