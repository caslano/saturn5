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