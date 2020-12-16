/*
 *             Copyright Andrey Semashev 2019.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          https://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   sinks/auto_newline_mode.hpp
 * \author Andrey Semashev
 * \date   23.06.2019
 *
 * The header contains definition of auto-newline modes.
 */

#ifndef BOOST_LOG_SINKS_AUTO_NEWLINE_MODE_HPP_INCLUDED_HPP_
#define BOOST_LOG_SINKS_AUTO_NEWLINE_MODE_HPP_INCLUDED_HPP_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sinks {

//! The enum lists automatic trailing newline modes
enum auto_newline_mode
{
    disabled_auto_newline,  //!< Do not insert automatic trailing newline characters
    always_insert,          //!< Always insert automatic trailing newline characters
    insert_if_missing       //!< Insert automatic trailing newline characters, if not present already
};

} // namespace sinks

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SINKS_AUTO_NEWLINE_MODE_HPP_INCLUDED_HPP_

/* auto_newline_mode.hpp
S6TzTvV/cP/+8WFDitaO217cYHgC5nupvi906FP6c+uEY/d/fvZQqpb6lhCPUTvHxKwf/Om7P4UMPDUtfOCj4YcxT0/1HV+7QcS24JVbf5yyY8HbC68MFOJhKs+tO57q9/Gvz/b86pkHVlXaWO8R6FDK5t3p3rwcrAu5Ahkr3xHpHZTCKvF7KD+7CjWwCegDxoC+YCwYBMaB9cEEsCXYEkwE48He7D+C/R3z3EV8vvf4fMZ57p58vr58ngFgdXAg2+8cBDYDB4Ox4DiwBXgXmAAOBduDd4CDwGHg7Rw+FBwBjqO6Yn4avBOcDiaD94Ep4P3gKPAZMBXcxOfZyvk8D44B3wTHgm9z+HEOvyLgNMd7De6/XM+akFKuZzbXM4/rmQ8GgwVgNDgBbKinA5uC93G9J4Px4BSwJzgV7M3xbuV4/cEZXN97wCywEP+P5/A8cBY4B5wNLgLngA+A87ie88EXwQVcz4V6Pfk8xzmf98ClYAm4TK83h3/P4TjGPZvfe8Am3A6ekLYu9l3rgn5gFPd3Pa5/fbAx2MCQXzLn10KRXxDnF8rpwzl9TVA/fw1uv5qcX658dmLMcH6VIWmc30rO7wEe/w+CgeAqMAT8K9uXXcfne4TH/6NgR3ANqJd5LffHOj4v/uZnCcY8n9cb0ofP2xbxLGAHkNavgZFgJ77eOoNxYBewK9iNz9Md3KmhHVtZREfIWMgqyFHIz5CY1hYxArIS8gFEYG42HJILKYSshuyEHIZ8ACmBBGLuNhrSFTIYkgZZAFkF2QW5CKnSDvlA2kL6QEZACiBLIE9BdkEuQq5CAttjXTakLSQZUgjZAtkHKYaUQCI64HyQZEiBzp3IC1wN2QQ5DCmFWDvivJDGkD6QNEgBZA5kJWQdZBfkFKQUYu2EvCExkI6QTEghZBVkF+QU5CqkSmfkC2kM6QgZDEmDLICsguyEHIZ8APHuYp/Tjod0hQyF5EIKIcshayD7IEWQYsimmZgXh1yAeM+qJKIgXSHJs8w5cNOZznSmM53pTGc605nOdKYznen+rfr/pPQ8+wKA36f/rwX7fkOaYM61mhAeQldBYa4/afSE7NSCfGRN4e9gAsl7pDE8D0XLyUYEWj+w1fDbAWM1QS6O2yMWsi4Q8712HXy3gQOTMnNS0pI4J5QlX/hDN+GBeD7IYaavLhXvTXPoHbw1d/P27ufnZ5FeYJZX9JWSh2dlzNw1+0hc/ZpfuJ/nV8/nu5tXv3Hz5Nc7P++Yj6S25j6IcZmPrMvzh/V5Hu9msCYYzfOSjXgeuzG4BIyajbkgiHFurpDn4eS8G8+5LeF5tUCeSzPOmVl5PmyOyxwYz3PJOa40ns+Sc1g8f5U225yLMp3pTGc605nOdKYznelM95/lrJBxf+D3fzb+T5rcqnlsrv7x//u+/fVv9xfZjr9xnXCGxb7mKh1shIUvyZft61P7JQ3FiZPS0vPwu3JJuXkZWen6wlxas+lZnWyoyDWbrf+up5mqJWme6nW6l3ndYlnaWGGwJ7WKwi/xsSa2fUm2ihVrIJV5xRntrj5H4QHKdarGtNMo7dBcYzkOUT2aKeytqNPGCtVvCarjxql/S1DGrSTjpit/z9uY53SKl1qA7pA2RZdReLylksWL0kcY0ke4pK9Zj9KPMtoT+Y7qvkes57XGUYb0US7pC4RceyrtGUyk8EEWHh9wBbJdZ1He3cr1r8OO4VFK+w/tJpk2NwttK21bfkjhn2m7NZswxIlFo0p7zycozjdapbLyybXdt9P5BopAspEFP1kGTzED81G1EOc2DJ6GkEYK2R5pl29RmNhgZzYFvwNLITo34HgdJC1MiGbg7ZAmEc5hcZANTH0=
*/