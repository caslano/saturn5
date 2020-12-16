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

child c("ls", on_exit=[](int exit, const std::error_code& ec_in){});

std::future<int> exit_code;
chlid c2("ls", on_exit=exit_code);

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
sq8z2qZOI6xMbNTNvTjbblOcN8Gnl6LXAr26koeynJesa4yOJbQY9J4Uuvb5XmQXlKZpKTrRxiNtrP5lRj9pq3pNNWbtSOnvA1+ZBN7+l2R8ft6vF9ZH5qTGmdbJpydvl/ZcxjGuEhsfNxnVOPz80zJwy/9lsT0+UOq7EJt2+TdLvZtzpVvyE2IzBZvNpRxG5jxBOWRpHiKfz9FTuvn4o/STKW4/+ZdRXj85A3sBSeMvsz+IGKNZQ3rXVjfiyh1gtTVR/OPN0eYMsVeNvQliLzP7Es1zSj2pz/JxpeXueHYvbaeG1Pv5ue9lh/2WqKyYSk9aVcwgR895bLYTm/2yH8Rm1HfQqe4Wp02K7unZK9HNtso8eLe8uKCYF/9NYipLmcbZhv21EmdHk1Mb22WqfTo3nUsmh/+2OVgUPoapU+yNYbY4/YnY29jkRDu9Oja0z9klYW11anlZafnEgqnlpTMKvL5iLzoHpazm53we1vZlfaSea958mq2SthZxZ/lf8mWG9VG5qat986Tflb4KuzX6Sh3kvIddbw6jd93K0LmqD4veY9mttM25dRW8jJYWV2r5aBqSZWy0lPj28ZvVW+3bkeHY3I3NU6WMemav1TKa6tZpRWlFMSVR7M1xahrxu6/zaK8NN8DWH8TW403aYivVGotT3KLTA510KcPJua/S3iLe3yc6O2k7x4rOObmPh/dn+vs22Hf0w5Z9Lms3JTaaEVZLyqoqZ28T+3zSWQwlpePs5+JrRfdh7Uecfdocf76/NdfNDeaEiOv7B34dz0v93cCxPpf4l2cf1DI82DC8Lwj1d+eG94m6VjM4S9toPe8m/6ukHJ9v0q2xPT7VPtRKdxdp7030Pic9gPgvxJ9lhpmAKcU5Nrtw3OlSpjVzp2WHXw/tMcid6C0Xvb05/dGzy9e+bp6IXnvJc9+cByjfaPNx1+k43moDbQyfllrGOgbh99jtNYYl3m/q1+xiCmvu8Z2RfLt5L7kdY5KmgV7pwXazGltb5XgPZbcIG/O4g2f3vOsnZTcqNUXHznWtsfMa3746YfdLrB/LqRp/27lS93/znJ1P/q+T47zXZIi29RfSdIxk3bPtLrYu/NH9Be/5ctF4Y+lfJ2PKY3w/NU6z47fR+A1guvQ5HUxTx++211FJcWan/y3/i/4d8fVNUo0Uc3+N5QF5p+JxxnQ6w5jlpD2l1pVTQnOOb8GvdUr8iupKq80Vyj27JO+9jNiY5dkYdSg2+kaxsRwbtzo24q/MC9m4Db+ts+UM/HXQSbpqiX0cW2cfOgFHJ/6qS2LZSTnTmHvSYM2FW0M6ayJ0WqHTJh2d9AWbQjp3R+gM8XTuiaUzA51THJ3UBZdE6rwQGJn+Gf440vsMOvHwVFgDht5TeVMMtx6XUCe6n+/Y0+/qptuM4u4Lhf2DbqveX78R1k0PuoC6yDz0QpaoaVan8cL1a6KThMtE9nQaTo81ET/Eee/m3ByRnmTiqQuTP3QIeYl0Kdg4g2PWglqWYW4jbgsulfAf4ELcH3GnpYf7a9cJujTcGyL3mC5xvXiPwb5apqvwO8xAZy6yOtBxi50yg/VwhGMn/Nl1picXXom8PrIGuIY49MJcFrJGuKV8bwyb4LJxOXostcMxbfux7UbaycUdhWuq8Rqonu0/2oqvZaMyCJvhjnGorrnjNP6xsIWV5+P4fjzuBNyJuJD/JLHnsSU8WeMdB1vhWuPa4NpaDI/npbkd/va4rLB5WGFr+N0+cETw/ttPzmsOPTPfLX35ft43/pw/gzjMKdA4wT0mmqvd7+QakhOXYTqZc0x/xikTTGtWKt3ge9Es9F/s+1Fcq18eLMeoJ8+vhvj+1vOrFAc=
*/