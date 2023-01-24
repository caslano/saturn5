//
//  Copyright (c) 2012 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_NOWIDE_CSTDLIB_HPP_INCLUDED
#define BOOST_NOWIDE_CSTDLIB_HPP_INCLUDED

#include <boost/nowide/config.hpp>
#if !defined(BOOST_WINDOWS)
#include <cstdlib>
#endif

namespace boost {
namespace nowide {
#if !defined(BOOST_WINDOWS) && !defined(BOOST_NOWIDE_DOXYGEN)
    using std::getenv;
    using std::system;
#else
    ///
    /// \brief UTF-8 aware getenv. Returns 0 if the variable is not set.
    ///
    /// This function is not thread safe or reenterable as defined by the standard library
    ///
    BOOST_NOWIDE_DECL char* getenv(const char* key);

    ///
    /// Same as std::system but cmd is UTF-8.
    ///
    BOOST_NOWIDE_DECL int system(const char* cmd);

#endif
    ///
    /// \brief Set environment variable \a key to \a value
    ///
    /// if overwrite is not 0, that the old value is always overwritten, otherwise,
    /// if the variable exists it remains unchanged
    ///
    /// \a key and \a value are UTF-8 on Windows
    /// \return zero on success, else nonzero
    ///
    BOOST_NOWIDE_DECL int setenv(const char* key, const char* value, int overwrite);

    ///
    /// \brief Remove environment variable \a key
    ///
    /// \a key is UTF-8 on Windows
    /// \return zero on success, else nonzero
    ///
    BOOST_NOWIDE_DECL int unsetenv(const char* key);

    ///
    /// \brief Adds or changes an environment variable, \a string must be in format KEY=VALUE
    ///
    /// \a string MAY become part of the environment, hence changes to the value MAY change
    /// the environment. For portability it is hence recommended NOT to change it.
    /// \a string is UTF-8 on Windows
    /// \return zero on success, else nonzero
    ///
    BOOST_NOWIDE_DECL int putenv(char* string);

} // namespace nowide
} // namespace boost

#endif

/* cstdlib.hpp
NB/bAY16m+WfOso/NV+wZf5B90iBoRSMcI7X0PeOrer71d/qtjxFAkTZUoPm02AH3S/U4cwc+SgGDD0msVAZ5jWd8p4+IjaZjR+koSfIrwuEjxHQ/9m+oLnoEvwnAVVQgyX5Jc0/KFFJm46++1nyUwhNwWi4EMq2NX0jRJXCj+GJwyMPxITie6/Rikd+zMNOZJeLzyazaXSyCBJIfbM+YtF8IvZMNRk9AdKbNn7uvoMnplg3ft68ucoSGcKzBhyE8xPrMRqREQ5S2RJTm55HJ7GdeHoor0u6snutSVNmJUsUQAzdVzj2FcZapViTFBoKY0Bh3wIO85MWOl+xWgJsq7t0o/hRZEO0U81NlTJuLHJj3L/XxfRny09x1DLHZ1drE5f4EX68nfBAAa7TugSerUDaCVoW0/XhFLbrDLO6P6lP7KJCnNjwJBzkBp1pnNwGbtCrt/FGnsUbWZvfJvwwv7yl5fwTvQubypmo4/YsSX52oThxO7C/rFZC+lF/O/kMNvPLw38T7JQ2i21bE4fR5iZj351zt9zviQ+32O90wJ/o5e07ZSaK1muRK/1R3NfrWtXXUTXc19zwlF5GX155t/zEXLI9KMqQ5GmArJ+tJunmbEoM76xGw9Fhtgwzru1Gt7PGezQY70lZo3y7D9r2Ua36FkgaWZ4lntjDEwuiKjZBedSBJHpctwXn1BUJKJwJ3PwrPfgatt5co2EW
*/