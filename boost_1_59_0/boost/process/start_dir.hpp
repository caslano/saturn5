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
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
*/