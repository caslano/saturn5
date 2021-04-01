/*
 *             Copyright Andrey Semashev 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/block_size.hpp
 * \author Andrey Semashev
 * \date   23.02.2016
 *
 * The header contains the \c block_size keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_BLOCK_SIZE_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_BLOCK_SIZE_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass interprocess queue name to the queue constructor
BOOST_PARAMETER_KEYWORD(tag, block_size)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_BLOCK_SIZE_HPP_INCLUDED_

/* block_size.hpp
RxiA3UdmA+gP4taKNCx0x7kEDYGJ63l7Hkwcvplrama1PR4tKsQW8aunmTIy6wkH3jvE8CYXQPeYHOR+mjrTqWT1Sja+FPjn0YWbhAhGq9dEYKgH7BiLdVnOZH04aL6TvNImxoTzSHxjujfqAMe7Zg0orJiEfP0kx8HNWvaE37TjG4hbvuLjdAUksNuUTTerE/gdkeSn+4Y5WaiSQSht8wrbP71jYVTzkeQrsD7CjX+s4VmcaJ9gKC6+5W0Q94bWbVxA/XItokH5oFLXC2Y/GavoUOVLhKKhZg3a/QC3QREBwRc4Ygbs6GAIQk/KOdPDVTtcdyDv8ZOYzwkmSFyA4Eawd9lBu+YcPfWHnL3jGjJs5j/1B4gVxCHVHYojlOmLRsuSMJpNzoNHAcMt/thenJ8LEMaw+Yj7NqD3WS7WLNxVeTCLixo9v11kCU+phipANXF99mcd8+G2qnHRu3tyiPoPyUtiaBj/gEhOIoUovHg3RXryxuHaC2Sq7c+k+Pt93ChU9catzA/enuInUgIwvFZdOWdcSrUT06/XsM8jN8RsniaiSoTcJ3K7dg==
*/