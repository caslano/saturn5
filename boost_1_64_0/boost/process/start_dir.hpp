// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_START_IN_DIR_HPP
#define BOOST_PROCESS_START_IN_DIR_HPP

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/handler.hpp>
#include <boost/process/locale.hpp>
#include <boost/process/detail/traits/wchar_t.hpp>

#if defined (BOOST_POSIX_API)
#include <boost/process/detail/posix/start_dir.hpp>
#elif defined (BOOST_WINDOWS_API)
#include <boost/process/detail/windows/start_dir.hpp>
#endif

#include <boost/process/detail/config.hpp>
#include <string>
#include <boost/filesystem/path.hpp>

/** \file boost/process/start_dir.hpp
 *
Header which provides the start_dir property, which allows to set the directory
the process shall be started in.
\xmlonly
<programlisting>
namespace boost {
  namespace process {
    <emphasis>unspecified</emphasis> <globalname alt="boost::process::start_dir">start_dir</globalname>;
  }
}
</programlisting>
\endxmlonly

 */

namespace boost { namespace process { namespace detail {

struct start_dir_
{
    constexpr start_dir_() {};

    template<typename Char>
    api::start_dir_init<Char> operator()(const std::basic_string<Char> & st) const {return {st}; }
    template<typename Char>
    api::start_dir_init<Char> operator()(std::basic_string<Char> && s) const {return {std::move(s)}; }
    template<typename Char>
    api::start_dir_init<Char> operator()(const Char* s)                const {return {s}; }
    api::start_dir_init<typename boost::filesystem::path::value_type>
                              operator()(const boost::filesystem::path & st) const {return {st.native()}; }

    template<typename Char>
    api::start_dir_init<Char> operator= (const std::basic_string<Char> & st) const {return {st}; }
    template<typename Char>
    api::start_dir_init<Char> operator= (std::basic_string<Char> && s) const {return {std::move(s)}; }
    template<typename Char>
    api::start_dir_init<Char> operator= (const Char* s)                const {return {s}; }
    api::start_dir_init<typename boost::filesystem::path::value_type>
                              operator= (const boost::filesystem::path & st) const {return {st.native()}; }

};

template<> struct is_wchar_t<api::start_dir_init<wchar_t>> : std::true_type {};

template<>
struct char_converter<char, api::start_dir_init<wchar_t>>
{
    static api::start_dir_init<char> conv(const api::start_dir_init<wchar_t> & in)
    {
        return api::start_dir_init<char>{::boost::process::detail::convert(in.str())};
    }
};

template<>
struct char_converter<wchar_t, api::start_dir_init<char>>
{
    static api::start_dir_init<wchar_t> conv(const api::start_dir_init<char> & in)
    {
        return api::start_dir_init<wchar_t>{::boost::process::detail::convert(in.str())};
    }
};

}

/**

To set the start dir, the `start_dir` property is provided.

The valid operations are the following:

\code{.cpp}
start_dir=path
start_dir(path)
\endcode

It can be used with `std::string`, `std::wstring` and `boost::filesystem::path`.


 */
constexpr ::boost::process::detail::start_dir_ start_dir;

}}

#endif

/* start_dir.hpp
gvB6mjJEPaI3MYFYTuwkzhBePVh2oiXRl8ghFjv1ZNrU0R5ef0XcI6Ke4ThA9CRGE7OJtcRXxHniHhH5LNOmjlpiAjGZWEzsJA5R94fwDhHak3MGoh7RhUgicojFxA7iBHGNmO3J/vAcdUlcYLwp6NWB59DgXGIncYLw6kWZ40wfy9C/KfYkkogcYjGxhzhB3CBCn2f5iOEMc965jTBMhjPIzXYG+cW4kzhO3CNyj5OnzH6M7s34iSRiNDGHyCX2EOfp/xXeIHy/JV5gGYi2RAoxm1hM7CA0fmO5ihsJFnuyPpzdfahnoi3Rl5hAhDOOt3AjsYc4QdwjImNZH0QCMZlYTmwhviKuEb59mQbzWwH7EtOJjcQe4gRxhQiIo74I50GiHrYlApmn3jiamE6sJfYTx4kLhNaPeSLqET2JDGIusZHYT1wgAuORaVfGpkQXIpuYTqwlDhE3iMAE1gPRhRhOzCW2EPuJ48Q1IiCReSTaEj2JHGIxsZE4TgT0p36JLkQSMZ3IJQ4QF4h7xEZP5nkA641oSyQRUSzndMwlYnjdknreyevzhG8S5YnKRFOiCzGcmEvsII4Tdwjfjjw9lIhMZhxEB153wb5EDjGbyCX2EGcIbSDjJJoSvYkcp99SBg8Q5wnfQewbRFsihejJvOVgLrHHk3nEQ8QdIiCFuiFiiL7EaGIx0ZOb23biCeIG4ZXKNk+UIToQGcRcIoX53YEHiGtEYBrTJpoSfYkMYgKxh5hM2TN4h/BNZ3ujO8NZh8QqYj9xhrhHhFfiPYLoQqQQc4gtxHnCq7KHVpn4++/vv7///v77++/vv7///v77++/vv7///v77++//78+L6Kc5gkBr2aB3ekZiWlb6kMz4RNfLrJQq8ry2KtWrVq8a3b/K0Cyaeq1r9Bter06VrKS4zMSEKpmJKYlxWYl6ibiMjKzeWTSFUTW930DG3cDZinqUpvk4n3ukbY/TDDsmx2emZ6X3z46q0K1iVOcMWlxLHpmcNiCqRXpqBm0YZ2rFabfsrWKMpK6meWrx6jmiZptxEfRfFMxn5A+lf3r6oOREWkGJd7YQUIp+2ZQJtPSTZ2wm82zFkYkJ9JLxL2D8i13jp5U4GXdsSnJWtj7+hfS/IP1Zbv2Zg1lq2vSLqufsF5eiD5ylhltMv8D6zn5JNE1EXQ0y5/lt+s2WftJCnj6g9FtCv54N6Kc/dzwlboDe9lquc148O3d5OrZnbGzrdt26P61pwSp/UeWfavWcUfaSyrVo1Y2S5jgu6/m2zdp1cs6Tyl+x5mOb92jXoaXR76plXK07d+toHd8v5rSll57/VZ/XDs2cs6p5ax2CVnFxv45q1yNQNZbTivAgWhLvM5zG9Wfnz1YTEmKdD1Km5cT0zETVpscpaaeD9WNpNylCype2beNDxsU/9WxmXjFKy7NgvaV/PZv2PcxhLe13GG26+Eq/GM3umU5BWF76+1B/HYNGe8jva7TVLHuAl0eAn3eAo1yAr4fenteyQMJ8RoSU3+JJXTjL+0Q91FaE3r0m5K/bWtHbjXDWW2GpN7PdCOqDnNSHavsmkEFkRcnfZaIAcYnIjdC0Lmq9sIvHOvcGaSJO3y1Ve0MvPrJdJxne2l4Kr4YlJWYmGs/A7iH9f9Q68v8cYhdhs15sxpOZ59nxv0v/aOY93FhfayRX365dInN85rMIszMtz6hLlv6HNA+WsB7/t9YaaqvR3C6Gme2tq21Rfy7+P6T7I/qHM2xtbShb+5OsPz/KrlXt5azD9fKanOF/19bRi+5tHWl0u+pXcgFGTupK1ncNtb67qJFOd5BXzmV9N/3atb55eHJs4nDn8VGz1Hl6BtqtZ4Yz6/M=
*/