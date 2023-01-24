// Copyright 2014 Renato Tegon Forti, Antony Polukhin.
// Copyright 2015-2019 Antony Polukhin.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DLL_SYSTEM_ERROR_HPP
#define BOOST_DLL_SYSTEM_ERROR_HPP

#include <boost/dll/config.hpp>
#include <boost/predef/os.h>
#include <boost/throw_exception.hpp>

#if !BOOST_OS_WINDOWS
#   include <dlfcn.h>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#   pragma once
#endif

namespace boost { namespace dll { namespace detail {

    inline void reset_dlerror() BOOST_NOEXCEPT {
#if !BOOST_OS_WINDOWS
        const char* const error_txt = dlerror();
        (void)error_txt;
#endif
    }

    inline void report_error(const boost::dll::fs::error_code& ec, const char* message) {
#if !BOOST_OS_WINDOWS
        const char* const error_txt = dlerror();
        if (error_txt) {
            boost::throw_exception(
                boost::dll::fs::system_error(
                    ec,
                    message + std::string(" (dlerror system message: ") + error_txt + std::string(")")
                )
            );
        }
#endif

        boost::throw_exception(
            boost::dll::fs::system_error(
                ec, message
            )
        );
    }

}}} // boost::dll::detail

#endif // BOOST_DLL_SYSTEM_ERROR_HPP


/* system_error.hpp
f4fZF4C4fXuHWoBvw+yvszmCGJxtDeC4kvnQ3jhD3IRBlwXCXeXPG/CHw1UOzctOOlwVXZBEqlUK/E6rlNPwKuWgH5NXyf1n6CrlmN/sp1UaEBaySjlmv21xst7H9NXLeKlypH3EfHaXWKrATMM2nBvONZwO1nAePV5/OCN4OEA0Q4bz5lZtOBv04QBvN5vtMmTZ5v8c0DFnVdBjwxzNZrxSsxlnBD+BELvAe5w0c7veTGGb2tNOiGLIYxlOkgpBcdPi/g+4wRbtI3VNIWiiIJNi7myW2++FVAbpIVqi/eDH40g5yh9DNMYAOJQDhPAy52MSXkBSaDD/Adlbl7chwePG8+h3eHvyf/LtQefhZd/2dJnCv92pVRK/lECt2sKleWFCQz7Tg6Rvnz9FCSx7Ubx9nONtauAWmgEriSxwfFAORnJikBpJzSnHUQbNbwOeU7GFbmtjoFRJQlqU3P4QTz2mvUFxHwbJy4Pb0PoYDktrP9WaXqfKh7jV4U/deRrfBkZzGGSwPGgKkVOQZ0lpcQUO0uJKmK8WoBzi/9ND6jp+Wqrr9GyceJY+89OAxBgOzFLqOkWSKXV9QWutGanrG9h7Ct9rRF2f1BrU9aEVvwCybFUzUIoGd0rqupyYpq7Dmy58B6q9Q6V3pa9j2lyMLXVsY32dJgb7e4kD9wkwwMOxBF2vQ5aMn8N/b1X+022tBO6mfkD89jcEyHxs
*/