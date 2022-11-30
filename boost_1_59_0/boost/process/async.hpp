// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/** \file boost/process/async.hpp

The header which provides the basic asynchrounous features.
It provides the on_exit property, which allows callbacks when the process exits.
It also implements the necessary traits for passing an boost::asio::io_context,
which is needed for asynchronous communication.

It also pulls the [boost::asio::buffer](http://www.boost.org/doc/libs/release/doc/html/boost_asio/reference/buffer.html)
into the boost::process namespace for convenience.

\xmlonly
<programlisting>
namespace boost {
  namespace process {
    <emphasis>unspecified</emphasis> <ulink url="http://www.boost.org/doc/libs/1_61_0/doc/html/boost_asio/reference/buffer.html">buffer</ulink>;
    <emphasis>unspecified</emphasis> <globalname alt="boost::process::on_exit">on_exit</globalname>;
  }
}
</programlisting>

\endxmlonly
  */

#ifndef BOOST_PROCESS_ASYNC_HPP_
#define BOOST_PROCESS_ASYNC_HPP_

#include <boost/process/detail/traits.hpp>
#include <boost/process/detail/on_exit.hpp>

#include <boost/asio/io_context.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/buffer.hpp>
#include <type_traits>
#include <boost/fusion/iterator/deref.hpp>

#if defined(BOOST_POSIX_API)
#include <boost/process/detail/posix/io_context_ref.hpp>
#include <boost/process/detail/posix/async_in.hpp>
#include <boost/process/detail/posix/async_out.hpp>
#include <boost/process/detail/posix/on_exit.hpp>

#elif defined(BOOST_WINDOWS_API)
#include <boost/process/detail/windows/io_context_ref.hpp>
#include <boost/process/detail/windows/async_in.hpp>
#include <boost/process/detail/windows/async_out.hpp>
#include <boost/process/detail/windows/on_exit.hpp>
#endif

namespace boost { namespace process { namespace detail {

struct async_tag;

template<typename T>
struct is_io_context : std::false_type {};
template<>
struct is_io_context<api::io_context_ref> : std::true_type {};

template<typename Tuple>
inline asio::io_context& get_io_context(const Tuple & tup)
{
    auto& ref = *boost::fusion::find_if<is_io_context<boost::mpl::_>>(tup);
    return ref.get();
}

struct async_builder
{
    boost::asio::io_context * ios;

    void operator()(boost::asio::io_context & ios_) {this->ios = &ios_;};

    typedef api::io_context_ref result_type;
    api::io_context_ref get_initializer() {return api::io_context_ref (*ios);};
};


template<>
struct initializer_builder<async_tag>
{
    typedef async_builder type;
};

}

using ::boost::asio::buffer;


#if defined(BOOST_PROCESS_DOXYGEN)
/** When an io_context is passed, the on_exit property can be used, to be notified
    when the child process exits.


The following syntax is valid

\code{.cpp}
on_exit=function;
on_exit(function);
\endcode

with `function` being a callable object with the signature `(int, const std::error_code&)` or an
`std::future<int>`.

\par Example

\code{.cpp}
io_context ios;

child c("ls", ios, on_exit=[](int exit, const std::error_code& ec_in){});

std::future<int> exit_code;
chlid c2("ls", ios, on_exit=exit_code);

\endcode

\note The handler is not invoked when the launch fails.
\warning When used \ref ignore_error it might get invoked on error.
\warning `on_exit` uses `boost::asio::signal_set` to listen for `SIGCHLD` on posix, and so has the
same restrictions as that class (do not register a handler for `SIGCHLD` except by using
`boost::asio::signal_set`).
 */
constexpr static ::boost::process::detail::on_exit_ on_exit{};
#endif

}}



#endif /* INCLUDE_BOOST_PROCESS_DETAIL_ASYNC_HPP_ */

/* async.hpp
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
*/