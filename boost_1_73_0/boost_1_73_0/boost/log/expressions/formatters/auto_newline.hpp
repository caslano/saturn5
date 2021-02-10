/*
 *             Copyright Andrey Semashev 2019.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          https://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   expressions/formatters/auto_newline.hpp
 * \author Andrey Semashev
 * \date   23.06.2019
 *
 * The header contains implementation of formatter for inserting a newline, unless there is already one inserted.
 */

#ifndef BOOST_LOG_EXPRESSIONS_FORMATTERS_AUTO_NEWLINE_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_FORMATTERS_AUTO_NEWLINE_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/utility/manipulators/auto_newline.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

/*!
 * Formatter for inserting a newline character, unless the last character
 * inserted into the stream is already a newline.
 */
using boost::log::auto_newline;

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXPRESSIONS_FORMATTERS_AUTO_NEWLINE_HPP_INCLUDED_

/* auto_newline.hpp
r4PRSI2G70/4N2VedXVngK5KjQfTj/3rgXrfn3xQ+01OZ2ZUmzT2px/+HdD+/NNo7riz59806PGPEHaj7dWNv0xlKl2Bj7m0WSGwdjW3ujXfvNPmLf8PUEsDBAoAAAAIAC1nSlKQn4nyqAIAABwGAAAbAAkAY3VybC1tYXN0ZXIvc3JjL3Rvb2xfbWFpbi5oVVQFAAG2SCRgrVRfT9swEH/vpzjRF0BZE5iYxgTTojaMallbpUGsEpLlJlfiKbUj2ykg8eF3TkNbpKK+zFVq5/z7cz7H7oqFzHEBt1E4iBLWv0tilo7HMfsdDkfsttOlSSHxw3n/9P+1DpzCwcaah1GjvmFMtPqLmd2PZuwV1j9iPVB/yMSHLeWVncBhyiscNxTWuly5MWOHjB5cbu7Pd8wH5oYUIZpj9lX1osVjYeG4fwJnl5df4ROcB+eBBwMuBZYwtSjnqB89uMqbyI+CPz/3DH73AC3wstdKpYUwYNTCPnGNQONSZCgN5sAN5GgyLeb0IiTYAmEhSoT+eDIbjn568FSIrHAiL6oGU6i6zKHgKwSNGYrVWqPi2oJaEJ3Ec2EsCdZWKNkjbwSLemmchrPnpVHAV1yUfE5G3EJhbWW++X5W65Ky93OVGT97W36vsMvNSmaUxJK/gKos
*/