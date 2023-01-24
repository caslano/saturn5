/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/use_impl.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c use_impl keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_USE_IMPL_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_USE_IMPL_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword is used to pass the type of backend implementation to use
BOOST_PARAMETER_KEYWORD(tag, use_impl)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_USE_IMPL_HPP_INCLUDED_

/* use_impl.hpp
sJtWZ4O2ONIhLVJhslXLecMBB3nT3I9dH77joWObTDTcKNMkM47DhmwRhjceXgdTzM5Qx1EPSCK5tpwTt+W18fxVLRp+YWyDBSlZcKbc5w2zIfrEADXnqc5632gnIXEnE8/G3OaZdZfS0W8vByu7ASvPhCCB2BKOWguOD+gpw7m0rTnnPoR3H5qnp1wbq2E2+61jNjoqAIiqe6PZe0onJ9jWQ97qgWgNTKM2vC/w9KI8TXWkfrgNqYywcY4f4fMEt7JQlI4z+eAdomBexKDLFEl0sYbyyKShhTZhRc9qjRE4L7VNMAor1XKNq1BcY+FyosxOb/Z8wqYns2LQusamAprlE1LRAZC+fccgQO7NtmZJxoR7rjNT+MB70DF3LZB9Q62Cg3w0G40xd8GTTT1nuUFVz5hCDEhioNnBC0Rly4o9i9JKuGRSkqYYTnufGqNeqHGbk+44jKOo/Vx8bvAzW4cPOavs/Jtj8UbSVYu/xfrdri3J+KShG/+Zx2ePS6X0bpGm16RIHcEQ++voRv0Cwt7PC7IRCgNaX5FU9Z5+C1eqGmn2KsOicgzKWJ9/T/aGZzDlx4f9Eac3kDlfoxugI6c53pVxX5XUW4JlKk7ib/fWwCRWw15frNxSfXNnd13ZieqGRMXzU4vVgudjqx0qyQLDzgNWwFZDLVmwtDvkyqF/17anNrFnllL9deen1apPwPw0svOkdPwgcEPm
*/