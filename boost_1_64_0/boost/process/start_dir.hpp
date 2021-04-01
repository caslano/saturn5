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
7ypqkDes9AK9W/B957Hf6zqHJzr29faKeXSHDo2jgWsYTSJqjkvtDOGDVwP6KwIHSjF90ppxo/BNnkzN5tiJGS/toW0GR9+4s0TzT8eyyHUjoIBw9DoQqp4kVsqDZlWZJxyBRO3p1ioqtZ88+934LZMCFXZwj5C69hmSEqriL9TCvMEYkTjQq9g+5OXPK3kKIWxfd7vl3mL+wZR63+vXNx1skMLHWxBOYrSIKsPme33vFBxIKbqIXHoO+V4cZqlbvenkAQiUA05UlsYGWNBoO0OzphTgmi9lwdJOhHYNR0d6bahsDe779LlGDdyXcr5M8/hU+/TuACZGSKI6M+hHlOPFNnXKr0C2sHTqtYNRgnW/smzqa3QDYg4aKerR0p6weQNZQc3GD+ptLz9KQP69kffBGsv4MirhiRoO348MEwGZ7mz521WX4hFv4HZM9JHUOoAZgnkf9wxsaBruD6syZ8ObLscNbAUdAysKruAqY7WULTddNTmXS9uoV678s4Gkd+cvmADhLszB/775BXlAetqZa1ETGTOxtaiHHGyva+TqifDdIckEtpfnVw==
*/