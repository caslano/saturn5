// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_POSIX_ASYNC_HANDLER_HPP_
#define BOOST_PROCESS_POSIX_ASYNC_HANDLER_HPP_

#include <boost/process/detail/posix/handler.hpp>
#include <type_traits>

namespace boost { namespace process { namespace detail { namespace posix {

struct require_io_context {};

struct async_handler : handler_base_ext, require_io_context
{
};

template<typename T>
struct is_async_handler :  std::is_base_of<async_handler, T> {};
template<typename T>
struct is_async_handler<T&> :  std::is_base_of<async_handler, T> {};
template<typename T>
struct is_async_handler<const T&> :  std::is_base_of<async_handler, T> {};

template<typename T>
struct does_require_io_context : std::is_base_of<require_io_context, T> {};

template<typename T>
struct does_require_io_context<T&> : std::is_base_of<require_io_context, T> {};

template<typename T>
struct does_require_io_context<const T&> : std::is_base_of<require_io_context, T> {};


}}}}

#endif /* BOOST_PROCESS_WINDOWS_ASYNC_HANDLER_HPP_ */

/* async_handler.hpp
FWvkWn969nmjDx+reXeVjLl74ih2k3NU45td3jF2nzZ/AUDEQxv2P+tTsH8AhwIDPS19SZjm3Png4dgin+niZeETCgsNqilyRO5ST0adu8sFwTPk1EMOTwDpmu6ztr1eC7wMIwmVVdrYiYuEkuC6bPxjjDfXVbjzklgHozEVM0LpulP+BmiSlp8pLdD/AcBgwL0zIU2zpPoceTdI/r4C12DvFUVYD7c0v4y1qUm+JES5X5EIgjk1AqUdbe0LMjPJ0LVayUgHvN1mszZdx/oGPXpHBj0uV0V2YMINgktmGw+9cB5m3zRIe6VEUrbprGSvZtsEkdp4qAW5eptZ3AleDIn2TQcQgaMQ//1Bf94JcuhpXLMronkrwg0z2ICm6mTo4codbmasEN0b25my4PYGNuw7McdBVwr7H3+AzjNzwgDLa6s3qMQeF9maKZCHx4eka82rQTpLWQnfWbPWnmollXmfUauS4gt4yLblGWCK90zwRJEWz49JTzoydpik/QLVTHnf7gnQTwA6NmU6HRdL2+6qZh6TyJDhIH7sij7icoBBLJYTGhoJju7EsQ==
*/