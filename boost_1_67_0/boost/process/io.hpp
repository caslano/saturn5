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


struct null_t  {constexpr null_t() {}};
struct close_t;

template<class>
struct std_in_
{
    constexpr std_in_() {}

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
    constexpr std_out_() {}

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
    constexpr close_t() {}
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
1+kGH5KtzpWkKAkp8n/8yifhfqVxL9dXbDPXOdySZIZYKy9j5H35uCSrHxYiWc+npfuKGLux9pTkmBfG6z42qdV41sJ8ttfvWQXyuws0z7rsCKcecLygc0jrOl58nKdfVHaeZwt01s5z6Db9gpxDeypP+v/wnEPrsfP4n0NrtfMI5IXOoQ0apwc8h/ZBh+yHn6Eemxd467Eme93ndaxH8uOS5Li46jGQva6w0LceL5QfF6rH6SU6a6+z+nGZebt+Vj8uRfnOvEKnw/BJSnbkv3axs+vP30Q9eNbfXrVLUQi0/tY+3kuPBy2eofcErSdDTwAtwULn5pEd+TI8/Tzp0nrj3mY89POk60/3pOtP96RrpVN+POfBWvNJP+s5sb9DXXDzsVcin9y67t+Bt3H7Be7O96w3q/6jeujdzc6um+mLeufs/NeAzvmpKXfz5Zrh0vn9ssU6a+fPxHf7fYZBPz2OL4+OyA+3LnuIQ9L912UPMXkK9zsMPvPmHRg3r5Dj3KMP6sZ6vRm4/3KhLsixnUWlvzLbkesePm6cZ31jxvCs7Ky07IzMtFGD0m6UWy6ljzGj4Se7HblyQJsXaxeFXXhb0UYz7bKluqGXt+gs7xeY9/nm/dhXZN68awczHUXFk4yFNX9FmD5LdJH1qi4eqdRr1JOW7a8dvzyC+Dg9qdMb+kWvJ10I++aUd3Uh3cmV0u5Fo9xjSn0qm7abGnbvhd0D6/U5K3RjX5r1R/Njia/rIo7RC848r4sEhj4T9dOeoSsVuohm6F+tBh9h7OqPfK5X22/cOr6FKHqxOj0K9MSV1enRoLter07vDHrOuur0WNB7fFKdvj2hhVA2BO6vPqWtWNcZpw8fBQE2O7mf5wgsJbhLhBhyEPpP/2J3kbl3MDrOLtYq3n6Y1KxZVVopWSWFzrIyh9uUQYfG+dr5rH2W6rg8jrdvZ6LPcfw1/yTP56ae4Plch+PeceLqXRI0rhw95R1XPHQaV9ZY6BmgZZj0Jqe98XjoFM9Ik07hR4A2ggnvoXvCc/sgjiKfLZjxqdPJwPVY+/Xd5GItr9jtkAu8TT9RE4ukWKGkkNOoMkcR/X/4Kq/OQL85Lb11uxltYfEZXTwHbD0j+ePbe3j+qH9dz4c/rtvD80cKL+cHnK4y0xmc5+zcFPOemh0ZjR+Ot4uhjWTe+gSHiCWR3ryV41lFA2++41Z45/ijukaIOCWkVufl3oZ4a8PXa2P/6qWY6yUusnVVv56Xe+7rqn6u83Ipv7+el3vxn5dLfGMG+EZX9OGp9UKM/rPiRGA7yLtq3fnGnh91seRwIx95sB/GoUtBHjwX/ZnjG3SNOtFIDPi+UdU7VEZ03Ydy3g0MCA0Xf8a1V4Nwo01HYExsERlu1APdP2deX8LYmniokZjdMFy80TRcbEad0Pnnlb2lHMnZl8k/Ayc3pCvSps/9yM8zLc54tG24SLqWXztWgnGE0+uWIE+cPLu2foh3f+6XoH0p5YgF9QLno5q/R9BWIz+zzPH7KT3Ex38c+QtTZttFbLcIsU0LEZ/osl3XZBcin4B1bdeXyrkLHzQIOa92Hcgu9KoI8bELdQgJOe91XHMbyHWqgfw++voUhLx9nbc9jKUwFjtvUjd5/sbvm8l2kBQe8uv5G+eh7wZqB/7r+b4JPf92QPX3MOrva9R9T3H2fkx9/3Kvv/9WPw5ucv7159+P/f1BUn9b2Ffybm4coXGrgNEXH0e8nH04G9/A2ROngM6NXyfDQthxMRXxO5l0OzYOYc9ROdDIMq5ZzsH4qqmk0896DsZNDb3hredgWMNbz8Gg8L6pen+114+LCx3OkqpTaozzuOgd73HeinGvyDE3xVXmtrj4UmKT7SK4vlf3tPJY+i1DP/2sDeTIDmfnsws61L2fDmgbckn00/8Wn3213fn30xGI4wUgqZ3sk3Epdlaui0TZc+de3hLF98cdUTXIdf1ySx10JB/+n4v0FHP8pp/VfqbHRohFaC9/SoQODb24JrvGS4l1b1d1WddzIe0agfSTV3pL/n8h7BqruoeIVsg/2TUorNWuYS3r2tg1HukS4mPX6IJ4rXYNT16sdo2Zj3ntGpRfsml47Bq9+0i6R2/ynGNstWusQf2/fEOIj13DE85q16C2Q//Ts3f/oopYvEt2DbLVxvWX4xFnr+3Rg9drKD6uv3yNPHDnhS7uWr2/0DjyZq+QgOfE+A9gRP8Lyrjcl2zQ++NbE6soXvo2hOfsr5kJNfRTpVhxKWWKG9dCJUPJxZ3coa0og0pHOUud5jmYpZ4OLT1/+dzjuefOGF/S+6dk/oe9K4GPolj6SwjEnd5NSthETg1IOATkhsiZZLOEQEJiEsADiSEEEgkJJsEAInIfATnFhwIPlIhRUG4BAZFLQUARRVFBfT7g8eAT8UA5RL5/T+9kZze9uQnoY/Or9Ex1z0xPT3dVdVV1V8rAgelpYvGt49yaMDwrBWjh2bc4zLHnxHQbvuNuxzxvJvJM5KAZEcmOvDmgGRetRjqG9J5QI70MWIK+5od7NGjuRztxvNUm+FRgJTPNfcBM7chMYTiuE2am1cxMw3A+7V4zvYL+vALwRjdH/+bjw4p7vI1jH/ShDgC/EPT7yehTbXAdnh3c10h5SMcgb0uAWG8m+p+Zfmwi1pUpHmZqW9lMvoDLHcyUgfIPWs30XmVRnvvmaOPuJ+D+xcdGd5H3S1sz/aeTmc7gHoPbmekCcJfxHr8hbRNhpv24F68HL7vAPt4MeEZ7lLchXQoYjeNgi5mO4978WTWrmtWyc4FfDtgI+AAwyWSmHD+0SSMzre9qplMmEc83LNBMSwBbjOJ9+LP4WDt1h6hjb6uAnWjH42jvTxuY88csh+1ob40+TbHfg0NDT3F/ja4ogHs53QIc6mKmRLSnxiMvNjRTK9QrAXnJgJHNhQ3UhOfyPY722M+b28919tgYmzU4whoR/HBUnzidfUhsvx8fEx4Sws90sVMcZbRMRzAZR16P8LAeEYA4rVREeGxcfHicLdL5HiG27lExNjUwjFaSF4oXUWDyh0SmfnyIzVD5qNnW00IHdf3/cJguLjfKcwc/1b7QIyl1uMRjlu73oz0DwKvGGou0FxyZXH589cMBt6a9oH3ajeOrN9JewPNvtL3gjWwj9R/tzFeLshdsiDe6tRe0xf0ACyz00/4K9oIkvMNEwOEUY7HtBY89ZSTPbPEN3NkLeJ5mL+DtdfwJ8W1c7QXNxopvpNkLnhpuVO0FlzKMRdoLfke9xw5BP0gRdSnMXjA2wehkL4jIEOVd7QWVxkNOGCPqlAX68S7GcvQ4Iy0CaP6vT+K4vPxf+bUabakI/1d3fuD3jRM69h7Rcj3495OM0nUWtfENZH7jZ7OM0v2CtuP7yvbfiHlSLkc+/6xR6n++M8O9PJfPF3TboXM8PWih/nZZK2qekRZbHfyE//bhex8DH+g+w0jPzit8Htbl+fLjF/9L87DYKUa387Dj0x1jQWvr4vCL4szDHpty8+dh8XON+fOwjbPRx1CnXEC1qUZKBRyaY6S0BRir04w0BTAK7XEd6W6kvwHCc4wUhXwr+l7nWUZVF3ApVq7H4PEy/F3wvNywGfJxnAe8bL3U4ZlG6TqPs8DL5o93zXY/f5wgKb9pqlw/uW6qXJ95Hm0oW6cVMMs9PeBxemJTBRXwbyFk5bilYm6krvlIGKguGGzbx0KejQV9eHK7kZ5/xpk+pOLaGp6eBOpb5Pqr9IaexaIPT9TwLEAf5gJXUvpQmP4v/g7PMun/3NGH+rU8pfq/lPjSrw+04NpJaOO7AQf9Pen1KuDXmzBv2ww5x+JJdet40hTg6/p6Ule8Vwhgn/2bWl81qj6ilpZ+NALf92V8w58SWeHr23+sWDp+I/W01/YbqQnA9TstX1nQnlJWOr7hZdCuPNCoZaBZgLuCGdXdADoF3HHA6J1G6hjHaHNbRu8i9RnIyKsdo7XtGZ3pwGhWY0YfAi7y2GBNGLW4j9FkwLR4RjseZuTdlFEoIL0Zo1zAPhzPB+T2ZvRaK0bfA2q0ZhQL+AH59ZvjvCujpTFMfZfDqN/TqAePPfYY8mZ9DFr6CuqKZ5/D+ZaNRvo4iNEC3KcyylkAAYC+r4O2t2G0MpRRCM6Xvwl6+yijA3jORkBz5A3PBf8BVA0RPg5HrIy6ofwspM3vZ9QG98jCtcFIOwJ6AJbgPB4QhePBSLseMtL0NqKtv79TyIP8eGsjRgNxjx4tGQVEMxrG6/aZkfa+Z6RJywRfGYA+++tWvB/6+P3AjcaxGqs+YaBqK56ANqRHLFK6anlDTrcXfy/3c3jpIzm/2LVdTp8TT8jpf5uVcrnvYdRHtq/+0zuMUv7l/5acT5k/kPOpk6vl/OKPdUbpPsGj18vl0HP75HJuDvqZbD9Iv1fldrpofCtZPKMZ29zzr0pon4YNnfQvsdaYqAge1dWOC7PFhcYEh4VE9ekdypes6cpyvDUqMlrE+3XgNe/gyKg+sTbuMKzXDwX3ttoiUMIFr/oVB4c4bqf6nA7lIWbsdo5VLZ3jhfC6/AHcrp+MlLPYTB+3UQqlxw26KBVKj2+GXL2nrlLucrVeD6OXqzddEnqYwJ+Nqh6G42R6mPFXjRRzpfhy9dZ6inqvZ34uKFcf+8VZD9PEV+gpNLlar4cJRZ3XA96qqahy9Q+o76VLznJ1RiuFotFmrnI1f29+j9N7zPlyNdfDPNDd6NZvk1/vTg/D48lqepjKl4202dOhh0lGncLwLq56mK/RZhfvUGg32q9KntAPcODv+YaHouphpvwp6slB08N436+Qz0WjqoeJrqLQ8mtoa8ABtGfdn8V73ldZoU5XxPEk4M5B8jx4j0KRTRUKsSjU9y6MpZYKzUDeiEYKvYg01ahQHtK3AHsADVCvL6qItra2U+ilGgpNaq1QDMbhlLYKrTAp1NgbEm1jhcbnKtTjcYt0X86t143SfTkpUJHue1YJdZfxme9+lfOTS/UVKf2eX1WR0vsD9yrSfXvfrq5I46U8d0nOr65dk/Ol2U0UKf88hb64zAXPy1+urUj5zLxLcj1IDlPIU/LcgXhfGf8Zjn4g83vMvSLnS+MwPk35GPHjdrC8Top0XVhQB0Uep55/Fzc/B1+IjrHFxsZbI6JibfEhfeLiovgj9OvpVZWMppl/qJUf9QGdTw3BuOnp2L8wtyvktgSFFkUq9FyI0Jk+300p9v6FHL/HZtd57fSia/7CxtIzSKH+uPc94eI5XK8WHi7GhLZ/YXawQq8GF71/YbdosX/hMlzP9WqfdwdNCFXoiV6gEV3Fs/W6SA0WIq857m8bmZQ4IivJYOW7ceF/nCFdtTqGGBIMGcAlGdIMI3A2wpCFP26XFP4HPCYSlx/6hfcOjeoX38MWEa22L7c5aussLiRaKNdDfFNlsEJ6eyH/5aHdTyUp1BF5RfkZJAz++/PhG6HfkvFhji9Pe0hJ/Qxc7SEyPjzbnmr6rangBfVXKAXsIcX1Myhq/URx+bDMHiLjw/x9irKHcF+7ouwhnAdy32od7cqnW9swfj7FtbJ9V3tkKU77ri5PLj7d0uwBGt3SxpbrvquaPUBPt0q77yp/t4HauwUMN0RnJGWqfgt2OT402UFLbOinel35YbSD/ySFRswsmo7w9rxNR24NOlIcPXl50JHPcV6edKQ85PnS0BG9PC+jI3p53pWOcN38wqH2/fIlct4LM+Vy7TPPyeXgvbinTE6tgf4h06sHTVOk8uL+6XI5tRbeXRaHesYSuRw8Y5FSIG4SX7c97Z/u5cXolLT8teKRMX36pQzKSubH4ZndU9MTeJxgLUZGTHp2eNqgpJHaueqlG5yaMiRNW+vKdwwUeVwBkTTIGafezxCQqffVcvhpcV2ZLpSqQfPZOgm61jujErXdoKjju02me7pWY2fF0rUbqTfW07UzGA8aXcvJKP2+AROfquRE1xaD5nC6Mxz33fk0nj+mEuUhbTqqEn2zQYy3WtsxbjPEMwZnV6JjaWL8aP7izwQJ4PuDfPCuku9HPjZIAMf3fseBHxMkgOOXvOXAjwoSwPF9NjjwTwcJ4PihOvzoIAEc/6wOPzdIAMcvXufAzwsSwPEn1snnwXevdz9OOrcW9ox+6GNqHHH7+S6c/xvAZZPQjPThoenZaU583CDmXFqeOmpccNpcgf8+w31n74ZcACjKP+rHz8qvv58IFL4ZN4uP315PXXL/KHfrqRfsdtbL/Z3XU/++SyE/vG9R/lG32nrqXYcc8wielnU9tfjVCeL+QiOzLFJ5peNHcvkmca97uhfYxo82on0Djgr+W9g6uO5HS0+P/spxCbaifYpLjzgUZ33NF+8rZV5fo8UlOHpMUWNGzHlK7keWe1iR2hm93pfzyRjg67ngC4trN3mfIrU/VtuvSOO5Je933x+fR3/8Bu09hve1Lx3z/ezPFXoO183bg3kN8g4cVGjdEYXWfl78+X67Q856yjScZx27MfP9a59CZuBiMiRsVdaFeM3fr85IC/UwOPyr9bEw+e8k3v/IVxiLF8V45PX69znwiFOg+d8oFAx85HGFdv2m0PYrCk39P0Wtx/pv8Y2/U+ilqozaI/8kjo/hPlcA7S4Jmjx4nplanlUo+0eF9p2w1y82RZ0cbEO9Otv99M7fyQr46bVs60ePMUZ3V2NF6h8+qMVKTSe43LLDxEokp99IueVm6B/0fnqa3MLTqz4i1pjW1sWRW8qqf5D56Y0kxz4THFcWPz3+bJ53qSbL1z80Rv/raGa05m5G3dDfPkR/MNXBM4E7BOjlzagmYA364+zqjHyA2462aeLHyPcuRuuBr406+tZHefRFrhdY87T79VfcPubOn09G15bhObJ5/jE8U6YXiAdeRjeP4j1d0Pk/Pl/mw9OuGtTbdWJHZWYlDXOy7hgM0zA+2+J9F94rvolGN5cAtwO4Q0hLYt/p2cARC8vjXvG9K9K+cwH1bRjAVPvOqQBHXfSg2XfybTJ2n8JJz1hUO59s3edxtNOLpypRl/k++f6Exd2Ha+wMHykdC8nxoaENGR0FnMbxY40YbcPxdZRPbSfmkdXj8D6PM9qM843IT4hnRfrJcZ+istDRW1XfoaejT3VjpdZ3uKOjK3eTChOiGHUdwFQ/uWmtmSpnnQbwvJvpJ6fVT/OT48fTkWp+cvw9iuMnx69z9ZM7fz+j6BbMrZ+cbBxx4H5yfI7I/eRS0V6anxwHjdbL/OTU+CfjLVL/Ao/uTGpvr9aZSecpuWFMvk6hC5POd6J6Mqle9WKEnN6OQt1l8vEuvK/MLy0LbSDzMztrY1J7vq2Pe3p+0E4Hzicwtf/r1vzZegdH2rhrGC+Xj7cvFwy2xoX3tec6+4S54tQLwnuHOV2iyw+zxXFcvH2TdYN9/V+S0Extm2ChNTqaqbdj63hPpnVEZlb6sJTRSaEpCanpQwwncd2yO3R7HpJjX8Ea7cU7+w1l1H+jNw2yn78zhKn7yJ4+6009JrqPb7tzMMaQC577XUzF9TJ/k38muW//NXj2VOQHZoj2L0zP/K8hN5bunjjuXWF09zLaUEZ3q6AOrnT3TrRNWejumye96fr33tQkmVHSGW+alS5oh2a30fRB4cMYPYxnbfvKNz9uC9+zZBXOA3XnqUOqU8RkC/G082TRT3p0EPz7wcniO5aEf981kUm/YzbwKw/60G7Aox/70DE840vg1gL2Aq7gWX9OYfQLjhtNQjqV0ZvTwBdwbAX0AjweKOr1+fSS12ulm3rx9uZwfDxT233M1775/rla+6ROwbjFs4fngC4D+gNyAPtmgEdlJAwJTUpNGIXy2WrMp0wDx0WmpIWmZKomHUPgA6LeM2eWvN4hOfJ6/4E2aIO8XIDUHynTIbj6T7VQlkHQj72zwCd3OPYe5b9pqN8A4H+e5SzXvobzmrMZRcwW/ZLXsbj2fw2v6VEqyv7PG8CaPmxYQtogdb2cGmbVYI+7qtFVe9Mcw3svmsOo8QLm5K8VvgxjEfjwBQ55vvV8VqL3/mmeGJf8uKLkec1fa8cL4tmaTkYvg2jy/Pz5vN8kDeueom4BYXhouoV4nFaNx7w33iHPN+voR31zIZfliv477mXwlnEe9AkgdbwHjRvtQaYJHpQ3HcfLGX39CuR0lPkYEIDjUYDRywWMWC7qFo50MqA7yjwEWIp7pyGdArDGJmVxq2lmbFZ6Bmp3AXXzt9dt9UrMYV30OWNQv+9w/fGVon7Km7gn4OoKyGxvYIzg+MirmAugTNs8RvGvMeoAqAw4Ddwnr0MmRf7jSMci/xruMxDpCeBio7rH9QuOsfXHc/Z1FON41Jqix/GyNc78rbB5zeDVjA6vFvOaerhu02oxr+G0gPvs6N9V/7NqG0HhuE4nP1qBa9PWMVq9kVEVpKM3oC3XMlq1RvDs5E6i/gGbSl5/d3Tog7fxPQHdcc+XXuS//3YT6RY17ld+mGPNOIffNtTjHZS/+iEr0j6XdqL85IRbNY78/7J9rrRx5Ctiv+NKn7IS2ee09yxv+1xx9y8oThz5wuxzvE+4iyO/6l1Wojjynbdino18Hkde6xdaHPnxXzBpHPkXUb40ceQ5eeGxNTU5zO4D48/1eqn9Q5Myh2alcxmA2/Wi51ik/v5q/3TB8/UB/JvJ5rl7djKp/3viLvm8+4WPmHT+/v4h+by722H5PHrucSbdf+raZpbvp2EJEcD9NJ7Y4sBXDxHA8bu3yPUAR/e7n9859rJRW1YNXi/BqZR+8VwLBdr3wue/fXscMuc05PHgMlqePt49/x0Gfxh4kkFmNRXJH1Z4m/72/KHRNaG/u80fis8fZp5iTvzhkIeQhTX+0F4xlZk/tKtqus0fSskf5p11zx/+qGQqE3/wvAw5/7J4l6b/ZfT7j5AhL2DecFrQtsDOfmT7D6MhlcV+B3sivNzSlxZVS09fbkV/jNqZXgX8MaIyCsabXdvTq9j0hUNx/DH2PehVbv4YwYmVqSagOeDtSC9aiu95GXTytXgv8jjDyBuwDbjIFC96boYXfTnHi/b+Q+xVpM3TjyN/0BKBm4oywxfa51oSf+FhKKu48MsOgF5/yvn6lT/l+vGAM+75K5/rXOB1kNxv7Tm5XEHn5c/fcV4uP3zyi7xeAzA2ZPbZS7/K5Zy+v8ntszWvMPKVrHtfelUubyw=
*/