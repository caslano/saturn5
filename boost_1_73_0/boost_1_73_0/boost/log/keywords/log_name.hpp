/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/log_name.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c log_name keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_LOG_NAME_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_LOG_NAME_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword is used to pass event log name to a sink backend
BOOST_PARAMETER_KEYWORD(tag, log_name)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_LOG_NAME_HPP_INCLUDED_

/* log_name.hpp
SCQO481Aw8Ig5XeYLk0Jd9MA5UCYbkCeYsb4nQzgyex0hidw6LgKmRJijfAEnv08kVRHAAA05RnLDsbrZFww5YaG3Cp7YCoOz/j6/zLdgEaCOft8rxEz+imIhOeAg4xxN9fLTTk1s0SzeVViVBKsYzz4Hxp+lZ0vovaCc5XYTj/K8iAiWnmDdh3jADke+c6oEcuRFWy0jPidAheTU3EjzJuILGgEIKgENJBPGvIXexdb5pXlKVLoGiYyqenggCLRB+gfiCwgqnWBVkq03dCZDh5MECQMkZkjeexe25CTVWA4N4C2pU6G26zwBS0dbcL1FSMLqhxQaSkm1ggRlRdF22Rxkme80RrEgxHpobaetKdiwfDFq+VOGm+Ngzz8DZ139NT0U/sO6VvwDuRBK9V1njGgAQKhewOf3wYF1PI3ZegVviiBXBNNDRUD1Zz7xHznCdLyWBTnJlc/BN6RMpF3aySC5I+Lx68c76zn0I/K1s+fGmn8j9zHGEWkFBNF7OonatTVmcB5rQf+p5AFohGegwr4iWlc2I9V1is+MI69gPIEYqSGmL7AA5PyQC+IED/ELRmG9YBysYwrWMM1h6RHg8Uzww797GAI8a0gqITh/AYtyBuUMcFqXvlh4ThFPmKkeDwtHzO+xUKHYjOJ
*/