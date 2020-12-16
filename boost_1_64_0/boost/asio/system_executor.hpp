//
// system_executor.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SYSTEM_EXECUTOR_HPP
#define BOOST_ASIO_SYSTEM_EXECUTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

class system_context;

/// An executor that uses arbitrary threads.
/**
 * The system executor represents an execution context where functions are
 * permitted to run on arbitrary threads. The post() and defer() functions
 * schedule the function to run on an unspecified system thread pool, and
 * dispatch() invokes the function immediately.
 */
class system_executor
{
public:
  /// Obtain the underlying execution context.
  system_context& context() const BOOST_ASIO_NOEXCEPT;

  /// Inform the executor that it has some outstanding work to do.
  /**
   * For the system executor, this is a no-op.
   */
  void on_work_started() const BOOST_ASIO_NOEXCEPT
  {
  }

  /// Inform the executor that some work is no longer outstanding.
  /**
   * For the system executor, this is a no-op.
   */
  void on_work_finished() const BOOST_ASIO_NOEXCEPT
  {
  }

  /// Request the system executor to invoke the given function object.
  /**
   * This function is used to ask the executor to execute the given function
   * object. The function object will always be executed inside this function.
   *
   * @param f The function object to be called. The executor will make
   * a copy of the handler object as required. The function signature of the
   * function object must be: @code void function(); @endcode
   *
   * @param a An allocator that may be used by the executor to allocate the
   * internal storage needed for function invocation.
   */
  template <typename Function, typename Allocator>
  void dispatch(BOOST_ASIO_MOVE_ARG(Function) f, const Allocator& a) const;

  /// Request the system executor to invoke the given function object.
  /**
   * This function is used to ask the executor to execute the given function
   * object. The function object will never be executed inside this function.
   * Instead, it will be scheduled to run on an unspecified system thread pool.
   *
   * @param f The function object to be called. The executor will make
   * a copy of the handler object as required. The function signature of the
   * function object must be: @code void function(); @endcode
   *
   * @param a An allocator that may be used by the executor to allocate the
   * internal storage needed for function invocation.
   */
  template <typename Function, typename Allocator>
  void post(BOOST_ASIO_MOVE_ARG(Function) f, const Allocator& a) const;

  /// Request the system executor to invoke the given function object.
  /**
   * This function is used to ask the executor to execute the given function
   * object. The function object will never be executed inside this function.
   * Instead, it will be scheduled to run on an unspecified system thread pool.
   *
   * @param f The function object to be called. The executor will make
   * a copy of the handler object as required. The function signature of the
   * function object must be: @code void function(); @endcode
   *
   * @param a An allocator that may be used by the executor to allocate the
   * internal storage needed for function invocation.
   */
  template <typename Function, typename Allocator>
  void defer(BOOST_ASIO_MOVE_ARG(Function) f, const Allocator& a) const;

  /// Compare two executors for equality.
  /**
   * System executors always compare equal.
   */
  friend bool operator==(const system_executor&,
      const system_executor&) BOOST_ASIO_NOEXCEPT
  {
    return true;
  }

  /// Compare two executors for inequality.
  /**
   * System executors always compare equal.
   */
  friend bool operator!=(const system_executor&,
      const system_executor&) BOOST_ASIO_NOEXCEPT
  {
    return false;
  }
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/system_executor.hpp>

#endif // BOOST_ASIO_SYSTEM_EXECUTOR_HPP

/* system_executor.hpp
KAmfZ7pf9Nxc8OT51I03Ei8ADR5nfot897cN/TbPwm8BbZVhIBeM5SHO2ZEHoQxCGYS8pscJynAV9gzzVH4DsVbj/UPLwrSYKMj7asqWtJk6H2Q6BPteom97U4vP77T4fL/dpvBPgzW0wbybBL4OHR51viJKWdC9x+tnbTELW3JmlPZIHOSCsfTS9wF02m7jojlGzeBDzTm84ww/bs3wnWau+A6/gIvhRxTzcQ58gJgjRL2d6m1j4J2vtJnpwFiEfz3kmWB52jZN8y2fI3YLqvAD9uXg8ct1K1XXJhbXtrdPUfOQZRE8qPtWTV8Wpe+Crj9R9Q3Hpu0bUG52Mil8GKdsH8bF2kJV32nV1p1j8Z6p2vf6X69YOZ77m1NjdOok9mo7wN3V3WLtPmcDla6M0saronRjn2oPjqn3PyFX9jbgDol4mxzW1iIv+87UtVE66Z1RmrTTiTvB9Rb2etB+VYYbxtLL8nBnZcg6Fy04+hJ9Ub4uSsvfhXl1ksqDYaLuPm0y9zL5iqVz+B3s0f2kwtb7Q1H6J6ik6sIxc1wKnx5sXEK2Sn8gSqeAFq3V73YnLOx1oDUSB7lgenpf/mroI1j3QNtUHgyTecSRR4zae3ge4NUfjdJNoAmVB8PcxmiNeS8lH5L7FVPHM4V7kpAhWiZMnluHs4da653C4sei9Cho2ckqf47h3jX4Vca28Spad3X7p9v/t1L/jih9GbRVpJN+kEzsJ6CbVRluGEsv+Q54Dtq3oiOG768Wo41CZW2ezQ3CB18nfPvMp+KtGM+fiFJwnV6HeRb2XVCrjk92WVjjJ6PUK3GQC8bSS9s4hKBcQrmEMnjZ2ItXCQ/KcJcwYphLPz8/Ss/POd6K82ev+DqMbYSDd0uJtFuf88Xbcffujiitf56qC8ck//bHj01+OUvf81o+s+IxfvedQmfA68f/5rZevvyns/KU3U4D5no9te8Udjvq/JLy34rSp0H3nqLanGPGjVgvesValtXXMv4NIcx/5f9cvVtdZ73H0oe71peBlj1fG4cIIxamfN1Grbedvw489c0obaikI1eM58HbYybf6bOSS86J0jm5WvB7jOVReTOJnxHFzTMiH2v69Dd4iz/Ftz2Eb1uv6WwduM972ANJGpiU+jLomMHPLH1ZIT27t1VZPPGOkrJbgw6gczJlvU2e3xOl+0DpU7W6c5yfj6m6V3+T0HXcByt/V9Wtp3zoGtzka3MeIc925Nk+JOeRkj379kbpIlDwBZXxyDDmLx12D/PA8+ZB5pw3qvt5SNK2R6P0FKhfy4tjmVVx2MmvUr5XhQQo/Zsq/6yHufhn5W/tOHSk3RU7AdTF9GVY3I91GTQpypZyjYmd+a8oTal6umEsvQ9ey/gK59n8biT3gdYdjNEAaPsLVR0YxvrZh/+t/xXfr/ZGltSFtYVt2VmX1RvC1IB37OM5m992NsboHNCNL9LnYh3DpQ+VeiuMXNMRx+D/ImTf00C96hx+berwrmOM3gJqfLFI34ZxiHv3TZPwN5xLWz68yC0excX9/FornBCXEHd6vIBHemKYPkb4OurvPRXfNoDOPq/uA7qS/gDeQ3GU5eOOix8+x375nRH+y23Bi6ugc16Ndj9N6yNXnBjGy/JxX4d9v5+z6u4lMboAdKtWD45x+03PeswPQk9g2RH7s2PyyIe3YR7vZ34HtKFfa8NZ4P7HpNf7NZC5jJeS9Nmcd/hiOYPya2L0EOhxWQ/TB85UP7VMvhx7oJdZYV3H4PzvpaqN3TCej7EROglmj8n85uV1H3il42K08/gYbZV5Xhem6/Ad5jkmsXCHXm1JCPmvxp5yBU17c24exs6C6ZrIqjo7hy5zvos=
*/