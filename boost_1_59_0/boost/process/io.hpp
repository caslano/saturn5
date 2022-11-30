// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_IO_HPP_
#define BOOST_PROCESS_IO_HPP_

#include <iosfwd>
#include <cstdio>
#include <functional>
#include <utility>
#include <boost/process/detail/config.hpp>
#include <boost/process/pipe.hpp>

#include <future>

#if defined(BOOST_POSIX_API)
#include <boost/process/detail/posix/asio_fwd.hpp>
#include <boost/process/detail/posix/close_in.hpp>
#include <boost/process/detail/posix/close_out.hpp>
#include <boost/process/detail/posix/null_in.hpp>
#include <boost/process/detail/posix/null_out.hpp>
#include <boost/process/detail/posix/file_in.hpp>
#include <boost/process/detail/posix/file_out.hpp>
#include <boost/process/detail/posix/pipe_in.hpp>
#include <boost/process/detail/posix/pipe_out.hpp>
#elif defined(BOOST_WINDOWS_API)
#include <boost/process/detail/windows/asio_fwd.hpp>
#include <boost/process/detail/windows/close_in.hpp>
#include <boost/process/detail/windows/close_out.hpp>
#include <boost/process/detail/windows/null_in.hpp>
#include <boost/process/detail/windows/null_out.hpp>
#include <boost/process/detail/windows/file_in.hpp>
#include <boost/process/detail/windows/file_out.hpp>
#include <boost/process/detail/windows/pipe_in.hpp>
#include <boost/process/detail/windows/pipe_out.hpp>
#endif

/** \file boost/process/io.hpp
 *
 *    Header which provides the io properties. It provides the following properties:
 *
\xmlonly
<programlisting>
namespace boost {
  namespace process {
    <emphasis>unspecified</emphasis> <globalname alt="boost::process::close">close</globalname>;
    <emphasis>unspecified</emphasis> <globalname alt="boost::process::null">null</globalname>;
    <emphasis>unspecified</emphasis> <globalname alt="boost::process::std_in">std_in</globalname>;
    <emphasis>unspecified</emphasis> <globalname alt="boost::process::std_out">std_out</globalname>;
    <emphasis>unspecified</emphasis> <globalname alt="boost::process::std_err">std_err</globalname>;
  }
}
</programlisting>
\endxmlonly

\par File I/O

The library allows full redirection of streams to files as shown below.

\code{.cpp}
boost::filesystem::path log    = "my_log_file.txt";
boost::filesystem::path input  = "input.txt";
boost::filesystem::path output = "output.txt";
system("my_prog", std_out>output, std_in<input, std_err>log);
\endcode

\par Synchronous Pipe I/O

Another way is to communicate through pipes.

\code{.cpp}
pstream str;
child c("my_prog", std_out > str);

int i;
str >> i;
\endcode

Note that the pipe may also be used between several processes, like this:

\code{.cpp}
pipe p;
child c1("nm", "a.out", std_out>p);
child c2("c++filt", std_in<p);
\endcode

\par Asynchronous I/O

Utilizing `boost.asio` asynchronous I/O is provided.

\code
boost::asio::io_context ios;
std::future<std::string> output;
system("ls", std_out > output, ios);

auto res = fut.get();
\endcode

\note `boost/process/async.hpp` must also be included for this to work.

\par Closing

Stream can be closed, so nothing can be read or written.

\code{.cpp}
system("foo", std_in.close());
\endcode

\par Null

Streams can be redirected to null, which means, that written date will be
discarded and read data will only contain `EOF`.

\code{.cpp}
system("b2", std_out > null);
\endcode

 *
 */

namespace boost { namespace process { namespace detail {


template<typename T> using is_streambuf    = typename std::is_same<T, boost::asio::streambuf>::type;
template<typename T> using is_const_buffer =
        std::integral_constant<bool,
            std::is_same<   boost::asio::const_buffer, T>::value |
            std::is_base_of<boost::asio::const_buffer, T>::value
        >;
template<typename T> using is_mutable_buffer =
        std::integral_constant<bool,
            std::is_same<   boost::asio::mutable_buffer, T>::value |
            std::is_base_of<boost::asio::mutable_buffer, T>::value
        >;


struct null_t  {constexpr null_t() = default;};
struct close_t;

template<class>
struct std_in_
{
    constexpr std_in_() = default;

    api::close_in close() const {return api::close_in(); }
    api::close_in operator=(const close_t &) const {return api::close_in();}
    api::close_in operator<(const close_t &) const {return api::close_in();}

    api::null_in null() const {return api::null_in();}
    api::null_in operator=(const null_t &) const {return api::null_in();}
    api::null_in operator<(const null_t &) const {return api::null_in();}

    api::file_in operator=(const boost::filesystem::path &p) const {return p;}
    api::file_in operator=(const std::string & p)            const {return p;}
    api::file_in operator=(const std::wstring &p)            const {return p;}
    api::file_in operator=(const char * p)                   const {return p;}
    api::file_in operator=(const wchar_t * p)                const {return p;}

    api::file_in operator<(const boost::filesystem::path &p) const {return p;}
    api::file_in operator<(const std::string &p)             const {return p;}
    api::file_in operator<(const std::wstring &p)            const {return p;}
    api::file_in operator<(const char*p)                     const {return p;}
    api::file_in operator<(const wchar_t * p)                const {return p;}

    api::file_in operator=(FILE * f)                         const {return f;}
    api::file_in operator<(FILE * f)                         const {return f;}

    template<typename Char, typename Traits> api::pipe_in operator=(basic_pipe<Char, Traits> & p)      const {return p;}
    template<typename Char, typename Traits> api::pipe_in operator<(basic_pipe<Char, Traits> & p)      const {return p;}
    template<typename Char, typename Traits> api::pipe_in operator=(basic_opstream<Char, Traits> & p)  const {return p.pipe();}
    template<typename Char, typename Traits> api::pipe_in operator<(basic_opstream<Char, Traits> & p)  const {return p.pipe();}
    template<typename Char, typename Traits> api::pipe_in operator=(basic_pstream <Char, Traits> & p)  const {return p.pipe();}
    template<typename Char, typename Traits> api::pipe_in operator<(basic_pstream <Char, Traits> & p)  const {return p.pipe();}

    api::async_pipe_in operator=(async_pipe & p) const {return p;}
    api::async_pipe_in operator<(async_pipe & p) const {return p;}

    template<typename T, typename = typename std::enable_if<
            is_const_buffer<T>::value || is_mutable_buffer<T>::value
            >::type>
    api::async_in_buffer<const T> operator=(const T & buf) const {return buf;}
    template<typename T, typename = typename std::enable_if<is_streambuf<T>::value>::type >
    api::async_in_buffer<T>       operator=(T       & buf) const {return buf;}

    template<typename T, typename = typename std::enable_if<
            is_const_buffer<T>::value || is_mutable_buffer<T>::value
            >::type>
    api::async_in_buffer<const T> operator<(const T & buf) const {return buf;}
    template<typename T, typename = typename std::enable_if<is_streambuf<T>::value>::type >
    api::async_in_buffer<T>       operator<(T       & buf) const {return buf;}

};

//-1 == empty.
//1 == stdout
//2 == stderr
template<int p1, int p2 = -1>
struct std_out_
{
    constexpr std_out_() = default;

    api::close_out<p1,p2> close() const {return api::close_out<p1,p2>(); }
    api::close_out<p1,p2> operator=(const close_t &) const {return api::close_out<p1,p2>();}
    api::close_out<p1,p2> operator>(const close_t &) const {return api::close_out<p1,p2>();}

    api::null_out<p1,p2> null() const {return api::null_out<p1,p2>();}
    api::null_out<p1,p2> operator=(const null_t &) const {return api::null_out<p1,p2>();}
    api::null_out<p1,p2> operator>(const null_t &) const {return api::null_out<p1,p2>();}

    api::file_out<p1,p2> operator=(const boost::filesystem::path &p) const {return api::file_out<p1,p2>(p);}
    api::file_out<p1,p2> operator=(const std::string &p)             const {return api::file_out<p1,p2>(p);}
    api::file_out<p1,p2> operator=(const std::wstring &p)            const {return api::file_out<p1,p2>(p);}
    api::file_out<p1,p2> operator=(const char * p)                   const {return api::file_out<p1,p2>(p);}
    api::file_out<p1,p2> operator=(const wchar_t * p)                const {return api::file_out<p1,p2>(p);}

    api::file_out<p1,p2> operator>(const boost::filesystem::path &p) const {return api::file_out<p1,p2>(p);}
    api::file_out<p1,p2> operator>(const std::string &p)             const {return api::file_out<p1,p2>(p);}
    api::file_out<p1,p2> operator>(const std::wstring &p)            const {return api::file_out<p1,p2>(p);}
    api::file_out<p1,p2> operator>(const char * p)                   const {return api::file_out<p1,p2>(p);}
    api::file_out<p1,p2> operator>(const wchar_t * p)                const {return api::file_out<p1,p2>(p);}

    api::file_out<p1,p2> operator=(FILE * f)  const {return f;}
    api::file_out<p1,p2> operator>(FILE * f)  const {return f;}

    template<typename Char, typename Traits> api::pipe_out<p1,p2> operator=(basic_pipe<Char, Traits> & p)      const {return p;}
    template<typename Char, typename Traits> api::pipe_out<p1,p2> operator>(basic_pipe<Char, Traits> & p)      const {return p;}
    template<typename Char, typename Traits> api::pipe_out<p1,p2> operator=(basic_ipstream<Char, Traits> & p)  const {return p.pipe();}
    template<typename Char, typename Traits> api::pipe_out<p1,p2> operator>(basic_ipstream<Char, Traits> & p)  const {return p.pipe();}
    template<typename Char, typename Traits> api::pipe_out<p1,p2> operator=(basic_pstream <Char, Traits> & p)  const {return p.pipe();}
    template<typename Char, typename Traits> api::pipe_out<p1,p2> operator>(basic_pstream <Char, Traits> & p)  const {return p.pipe();}

    api::async_pipe_out<p1, p2> operator=(async_pipe & p) const {return p;}
    api::async_pipe_out<p1, p2> operator>(async_pipe & p) const {return p;}

    api::async_out_buffer<p1, p2, const asio::mutable_buffer>     operator=(const asio::mutable_buffer & buf)     const {return buf;}
    api::async_out_buffer<p1, p2, const asio::mutable_buffers_1> operator=(const asio::mutable_buffers_1 & buf) const {return buf;}
    api::async_out_buffer<p1, p2, asio::streambuf>               operator=(asio::streambuf & os)                   const {return os ;}

    api::async_out_buffer<p1, p2, const asio::mutable_buffer>     operator>(const asio::mutable_buffer & buf)     const {return buf;}
    api::async_out_buffer<p1, p2, const asio::mutable_buffers_1> operator>(const asio::mutable_buffers_1 & buf) const {return buf;}
    api::async_out_buffer<p1, p2, asio::streambuf>               operator>(asio::streambuf & os)                   const {return os ;}

    api::async_out_future<p1,p2, std::string>       operator=(std::future<std::string> & fut)       const { return fut;}
    api::async_out_future<p1,p2, std::string>       operator>(std::future<std::string> & fut)       const { return fut;}
    api::async_out_future<p1,p2, std::vector<char>> operator=(std::future<std::vector<char>> & fut) const { return fut;}
    api::async_out_future<p1,p2, std::vector<char>> operator>(std::future<std::vector<char>> & fut) const { return fut;}

    template<int pin, typename = typename std::enable_if<
            (((p1 == 1) && (pin == 2)) ||
             ((p1 == 2) && (pin == 1)))
             && (p2 == -1)>::type>
    constexpr std_out_<1, 2> operator& (const std_out_<pin>&) const
    {
        return std_out_<1, 2> ();
    }

};

struct close_t
{
    constexpr close_t() = default;
    template<int T, int U>
    api::close_out<T,U> operator()(std_out_<T,U>) {return api::close_out<T,U>();}
};



}
///This constant is a utility to allow syntax like `std_out > close` for closing I/O streams.
constexpr boost::process::detail::close_t close;
///This constant is a utility to redirect streams to the null-device.
constexpr boost::process::detail::null_t  null;

/**
This property allows to set the input stream for the child process.

\section stdin_details Details

\subsection stdin_file File Input

The file I/O simple redirects the stream to a file, for which the possible types are

 - `boost::filesystem::path`
 - `std::basic_string<char_type>`
 - `const char_type*`
 - `FILE*`

with `char_type` being either `char` or `wchar_t`.

FILE* is explicitly added, so the process can easily redirect the output stream
of the child to another output stream of the process. That is:

\code{.cpp}
system("ls", std_in < stdin);
\endcode

\warning If the launching and the child process use the input, this leads to undefined behaviour.

A syntax like `system("ls", std_out > std::cerr)` is not possible, due to the C++
implementation not providing access to the handle.

The valid expressions for this property are

\code{.cpp}
std_in < file;
std_in = file;
\endcode

\subsection stdin_pipe Pipe Input

As explained in the corresponding section, the boost.process library provides a
@ref boost::process::async_pipe "async_pipe" class which can be
used to communicate with child processes.

\note Technically the @ref boost::process::async_pipe "async_pipe"
works synchronous here, since no asio implementation is used by the library here.
The async-operation will then however not end if the process is finished, since
the pipe remains open. You can use the async_close function with on_exit to fix that.

Valid expressions with pipes are these:

\code{.cpp}
std_in < pipe;
std_in = pipe;
\endcode

Where the valid types for `pipe` are the following:

 - `basic_pipe`
 - `async_pipe`
 - `basic_opstream`
 - `basic_pstream`

Note that the pipe may also be used between several processes, like this:

\code{.cpp}
pipe p;
child c1("nm", "a.out", std_out>p);
child c2("c++filt", std_in<p);
\endcode

\subsection stdin_async_pipe Asynchronous Pipe Input

Asynchronous Pipe I/O classifies communication which has automatically handling
of the asynchronous operations by the process library. This means, that a pipe will be
constructed, the async_read/-write will be automatically started, and that the
end of the child process will also close the pipe.

Valid types for pipe I/O are the following:

 - `boost::asio::const_buffer`   \xmlonly <footnote><para> Constructed with <code>boost::asio::buffer</code></para></footnote> \endxmlonly
 - `boost::asio::mutable_buffer` \xmlonly <footnote><para> Constructed with <code>boost::asio::buffer</code></para></footnote> \endxmlonly
 - `boost::asio::streambuf`

Valid expressions with pipes are these:

\code{.cpp}
std_in < buffer;
std_in = buffer;
std_out > buffer;
std_out = buffer;
std_err > buffer;
std_err = buffer;
(std_out & std_err) > buffer;
(std_out & std_err) = buffer;
\endcode

\note  It is also possible to get a future for std_in, by chaining another `std::future<void>` onto it,
so you can wait for the input to be completed. It looks like this:
\code{.cpp}
std::future<void> fut;
boost::asio::io_context ios;
std::string data;
child c("prog", std_in < buffer(data) >  fut, ios);
fut.get();
\endcode


\note `boost::asio::buffer` is also available in the `boost::process` namespace.

\warning This feature requires `boost/process/async.hpp` to be included and a reference to `boost::asio::io_context` to be passed to the launching function.


\subsection stdin_close Close

The input stream can be closed, so it cannot be read from. This will lead to an error when attempted.

This can be achieved by the following syntax.

\code{.cpp}
std_in < close;
std_in = close;
std_in.close();
\endcode

\subsection stdin_null Null

The input stream can be redirected to read from the null-device, which means that only `EOF` is read.

The syntax to achieve that has the following variants:

\code{.cpp}
std_in < null;
std_in = null;
std_in.null();
\endcode

*/

constexpr boost::process::detail::std_in_<void>   std_in;

/**
This property allows to set the output stream for the child process.

\note The Semantic is the same as for \xmlonly <globalname alt="boost::process::std_err">std_err</globalname> \endxmlonly

\note `std_err` and `std_out` can be combined into one stream, with the `operator &`, i.e. `std_out & std_err`.

\section stdout_details Details

\subsection stdout_file File Input

The file I/O simple redirects the stream to a file, for which the possible types are

 - `boost::filesystem::path`
 - `std::basic_string<char_type>`
 - `const char_type*`
 - `FILE*`

with `char_type` being either `char` or `wchar_t`.

FILE* is explicitly added, so the process can easily redirect the output stream
of the child to another output stream of the process. That is:

\code{.cpp}
system("ls", std_out < stdin);
\endcode

\warning If the launching and the child process use the input, this leads to undefined behaviour.

A syntax like `system("ls", std_out > std::cerr)` is not possible, due to the C++
implementation not providing access to the handle.

The valid expressions for this property are

\code{.cpp}
std_out < file;
std_out = file;
\endcode

\subsection stdout_pipe Pipe Output

As explained in the corresponding section, the boost.process library provides a
@ref boost::process::async_pipe "async_pipe" class which can be
used to communicate with child processes.

\note Technically the @ref boost::process::async_pipe "async_pipe"
works like a synchronous pipe here, since no asio implementation is used by the library here.
The asynchronous operation will then however not end if the process is finished, since
the pipe remains open. You can use the async_close function with on_exit to fix that.

Valid expressions with pipes are these:

\code{.cpp}
std_out > pipe;
std_out = pipe;
\endcode

Where the valid types for `pipe` are the following:

 - `basic_pipe`
 - `async_pipe`
 - `basic_ipstream`
 - `basic_pstream`

Note that the pipe may also be used between several processes, like this:

\code{.cpp}
pipe p;
child c1("nm", "a.out", std_out>p);
child c2("c++filt", std_in<p);
\endcode

\subsection stdout_async_pipe Asynchronous Pipe Output

Asynchronous Pipe I/O classifies communication which has automatically handling
of the async operations by the process library. This means, that a pipe will be
constructed, the async_read/-write will be automatically started, and that the
end of the child process will also close the pipe.

Valid types for pipe I/O are the following:

 - `boost::asio::mutable_buffer` \xmlonly <footnote><para> Constructed with <code>boost::asio::buffer</code></para></footnote> \endxmlonly
 - `boost::asio::streambuf`
 - `std::future<std::vector<char>>`
 - `std::future<std::string>`

Valid expressions with pipes are these:

\code{.cpp}
std_out > buffer;
std_out = buffer;
std_err > buffer;
std_err = buffer;
(std_out & std_err) > buffer;
(std_out & std_err) = buffer;
\endcode

\note `boost::asio::buffer` is also available in the `boost::process` namespace.

\warning This feature requires `boost/process/async.hpp` to be included and a reference to `boost::asio::io_context` to be passed to the launching function.


\subsection stdout_close Close

The out stream can be closed, so it cannot be write from.
This will lead to an error when attempted.

This can be achieved by the following syntax.

\code{.cpp}
std_out > close;
std_out = close;
std_out.close();
\endcode

\subsection stdout_null Null

The output stream can be redirected to write to the null-device,
which means that all output is discarded.

The syntax to achieve that has the following variants:

\code{.cpp}
std_out > null;
std_out = null;
std_out.null();
\endcode

*/

constexpr boost::process::detail::std_out_<1> std_out;
/**This property allows setting the `stderr` stream. The semantic and syntax is the same as for
 * \xmlonly <globalname alt="boost::process::std_out">std_out</globalname> \endxmlonly .
 */
constexpr boost::process::detail::std_out_<2> std_err;

}}
#endif /* INCLUDE_BOOST_PROCESS_IO_HPP_ */

/* io.hpp
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
*/