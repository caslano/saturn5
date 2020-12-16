//
// uses_executor.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_USES_EXECUTOR_HPP
#define BOOST_ASIO_USES_EXECUTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// A special type, similar to std::nothrow_t, used to disambiguate
/// constructors that accept executor arguments.
/**
 * The executor_arg_t struct is an empty structure type used as a unique type
 * to disambiguate constructor and function overloading. Specifically, some
 * types have constructors with executor_arg_t as the first argument,
 * immediately followed by an argument of a type that satisfies the Executor
 * type requirements.
 */
struct executor_arg_t
{
  /// Constructor.
  BOOST_ASIO_CONSTEXPR executor_arg_t() BOOST_ASIO_NOEXCEPT
  {
  }
};

/// A special value, similar to std::nothrow, used to disambiguate constructors
/// that accept executor arguments.
/**
 * See boost::asio::executor_arg_t and boost::asio::uses_executor
 * for more information.
 */
#if defined(BOOST_ASIO_HAS_CONSTEXPR) || defined(GENERATING_DOCUMENTATION)
constexpr executor_arg_t executor_arg;
#elif defined(BOOST_ASIO_MSVC)
__declspec(selectany) executor_arg_t executor_arg;
#endif

/// The uses_executor trait detects whether a type T has an associated executor
/// that is convertible from type Executor.
/**
 * Meets the BinaryTypeTrait requirements. The Asio library provides a
 * definition that is derived from false_type. A program may specialize this
 * template to derive from true_type for a user-defined type T that can be
 * constructed with an executor, where the first argument of a constructor has
 * type executor_arg_t and the second argument is convertible from type
 * Executor.
 */
template <typename T, typename Executor>
struct uses_executor : false_type {};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_USES_EXECUTOR_HPP

/* uses_executor.hpp
Ow/K+1uY2MnE8jC+En3nR+sSWEe7u55p2s+Wc64PxsmfpHHsT9O4XngqzBsbV1tjQ9eNvIZ+nsZHSYmv+Pz0utjTfsGxZnBSEKbzx56fxPMnWkzM5UnbO3C1LTPeubyyX9nOswvex906nMYp5ZTc56XEV7sPc9C7D2Ofr9s+bA858gH1V7NpvJl0yKqnxrrZpktunnvPZdB3ZkdZb4b+HP/Ad54QXgoLrpvmxXoN/j6N95BGLF4aiz2OtvD8Js/0t8Ok0w4N2Wb/LY3839O4XcpSmFfvO/QdI90GtGe7O42XkdZ81fYtWcU+RDrD4KQgTPKr9po8fHuN/zmN35PGhZcPazgOrxMbaLN8D7YP6YF8Bu8mdX3NK8tZI6gD7PL20E7aJ0kbTDopAFN8PF+ew8556FyZEv9IYwfpEj4rdWl2sWtI48I3CFP5vfe7Wry/yhqQQIL3QSYXZnD/5gzutsubSLrYbaTU1+3+bXWxH5PWGJwUgKn8xtYiAQSVCSjM299d3TJjvDyKD4CkG3t65J9p3EzaZ9dvotXFXvCvNCZ89U642ItJU1LHQEzyK39SQWWSNBZrX4j2q11NY8VX7+FqvWdaM3hEMoOdN9j+AFpd7Heki4hb9XaxP5KuMDgpAFP5vXqzTASVSRIsWr1HmjL4Oqn3G756u9j5CzLoJ27V28WeTRo0OCkIk/yq3kFlkgSrby8UMA+o2LFt9LOd5DlDK9YVlJ/tMH3YEurmR7lOkO+ScjP19AuxZGbRVNdkR6WuHVCYjK7l3xW0Y6JdiznXGPHZtXRiYG0GbyJd901pF4VV1wTKTt17xdrCXhO61zo6hnygjmGkkWdCZP3D6Vm7V/vTnHw5IMQfRAwdTSZmFNgPTZjZkMFD75fBgW/J+ytM+Yzz7kvMtlX3OaNVXxIjx2XwB9KM8FGYF9Ngc3pGxTTw/OPHOdZTQF8Go6STbxQ+GuteWZvP6F1B3XPoSaCH38wizl8553ujPDvWz/mTNCY8Fea1/W7T9oZfuP0102WtfYWs8Trd2F7u2ch5hpT6ttRhLsbOifis2wYHQ9rgmASO4fqylP2TGW5z7/FUHpDBkpMzeJXwVFg1hkHnfu9N+/zyWvdJ6dPW8Gxn1XCeumnamTxcPLXYd6cDbaPu33biSp4J9VCWX3xCx14jeap8wTZD2zwdlfH3MZry9tZJTJ6RwdmP5Lz7Hcs22fjtCEgPs0EePDWDl5AOfMfqhyCcpLHY+masH23h/qzZfWcXO74ZxxNb3e9iLKuOPezuEB+T2WY1ZwZgej++2/hHMbqWZuokWpgng6R3p6v38exz0hU3WX5PTHwtPgc+B/WcxHZOsY5trKP/HsT44zK4i3T3TVYbatw+Zyq36DspvM+UQSt1w5smLR4Kt3W7tXhf52XwNtKYnU/hgX51zsng0aQDdr5AHAozdTDvk+H7pNG1134f7kcey70/KfVd4SPYPM+0j9av1xZ1z01dGw+F36F/a+cag+bd8ZwMTiKVbvbe/cQMTuQY2zBNnTbn59JEK8dkNQ4Egp4nKUzFPqIu7wUZ3Ei60ORpi6ONayGC0hLNlL2Sbhr4jKTLuXr7HZ7MNhKg5xlOu3a8YyMZHHLoZju2uuMvvYpvfS7XO3mHIGwuDyQ8nz5sC/KBKicsn+477bN/8oIMjn0mv99brFgzw+49Shc/jjTONDnTywXgcReH4hdY3ijTn59B4lBAecSPI+UOqfIE1+VpfnIefRZ9u1D+OEN8PVITIvc4KPOxXXIo7m8ekX6UM6uxIc5JpPFamdBY+B3I+7XS1u1M2ro9Cotjp8NYuznl9DYd4bmlexd+IZoHrbi60879qgXunfg=
*/