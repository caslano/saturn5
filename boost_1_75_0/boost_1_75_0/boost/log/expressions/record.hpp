/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   record.hpp
 * \author Andrey Semashev
 * \date   25.07.2012
 *
 * The header contains implementation of a log record placeholder in template expressions.
 */

#ifndef BOOST_LOG_EXPRESSIONS_RECORD_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_RECORD_HPP_INCLUDED_

#include <boost/phoenix/core/argument.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

/*!
 * Log record placeholder type in formatter template expressions.
 */
typedef phoenix::expression::argument< 1 >::type record_type;

/*!
 * Log record placeholder in formatter template expressions.
 */
const record_type record = {};

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXPRESSIONS_RECORD_HPP_INCLUDED_

/* record.hpp
SZcPj4cglO/P9WNTxZ//NLV9i80N0kslHDMRDfcSsLmqfHNikSZeMu0ah4mWu362BxLZG1PF/wpk+69A357BJ3S3b+h9Poa+rtYzTvPHlRPoGDR0LQt8brj7DT5hsNQwdFw6je1XKWRQng0LjYD7tOfdfwB12uE+EhPDfbUP5kk5bT2QBKCTbe6hetPXPb2ZbQm3CW1UdZM8DrIKn7DOiuUUd6yh6C4PI5808Z7bsxIoqfyhRxYtcCYOF7wJHSmKDdEjO/S1OcYKqV+X5zVF0cS3nSnDMZRSNN3bJAN8HB9PlkbRdLcRuGWydBMvo0r4I8WQB91dM10o4dGUJOLAX99Aew3U6YOTJBwZ645djHdAGB+pcCRWF+BxIf03gmJ3Q6OlI7LKdqXWEIkw3vraP89f5ixF3TEfevjShLtXW3uajcQ4c9jo+PXeZoer2v7hSJwjGNGTpPF7/7mIGXQifSGWudEtfuimD8/joG7XSun9DKfNRzCzPgTPYs9JOSkMwWzCXbcj1neUt3qYwc3uLxT/Oo0RZKl1eUjyhtmz7ysSWFkG2j6j8XpEf5CORUhmpDQ81n8GJpglNAA55eRq5Z9r24JZF3nmmvtjRIjM4hBl8MK3R6LdYA7xZqYnrsuLeGZfh/GleJ6+7Sezrt8GlDu409ovO53UjL9czq2PsiKqboBf3wgIRw6Jdixd0o/JswwLc83xato6E/Dq
*/