/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keyword_fwd.hpp
 * \author Andrey Semashev
 * \date   29.01.2012
 *
 * The header contains attribute keyword forward declaration.
 */

#ifndef BOOST_LOG_EXPRESSIONS_KEYWORD_FWD_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_KEYWORD_FWD_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

#ifndef BOOST_LOG_DOXYGEN_PASS

namespace phoenix {

template< typename >
struct actor;

} // namespace phoenix

#endif // BOOST_LOG_DOXYGEN_PASS

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

/*!
 * \brief This class implements an expression template keyword
 */
template< typename DescriptorT, template< typename > class ActorT = phoenix::actor >
struct attribute_keyword;

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_EXPRESSIONS_KEYWORD_FWD_HPP_INCLUDED_

/* keyword_fwd.hpp
keWgPGUZ/obJXBIOZu8R6hDw9n20cmgsQgvo+rZWFVw2Z6NW+v0uCTxxrHIX2r31vbzBQ829PzdqydXwarBHxKH2vd/ffEGY/6TJ9HQ4VmfD0WB82d74Rg89SKMFCnUD8oeQP94U+I52rXzVBVCgn5EYXF/vljh6zsjRs0aOHhtpyvPAb6RByntp0ls6bJaTMs350OPet0WXhbRyYAkPdNGt+D1+bSAHTroH2GfBnIkJORYB0Esh4dUCai+JKKIoaYtkMZkkvgtF3I+VkKIQ31AIEE0Cxyd56exmr/79iL+XfPOwYhyu1KeD9zfnm0CQoqOqeqMCZOIKD9CJCkUtHd+xAZvJrEddDC5EF+cpmLRt64HkS14VslUNi9BcOXPNEJ7zd1k9dAJS0gKoObg+vmvsb6jel00hDnjUpD/FaWWDwalnyRwJIbkeo15YveWafR753SqcqtHl+dm4fzFQ72/OJsP/Dr70qiCjhQx1bG28O6anJlTxh9yTSjsMJnr9+fC11Q7VbnrfkJW0eWbTjvOelQ/KaGyNebO5qmqtnVY+PWhZ/y51gAqUm8IH6kqWNMySt7qmtUnwJ7kAIHOPMFmFOBGae7O1Gam3ScVqj0InsETcgECre2+FV7OwPCPV131hvf/wCCaj4cVw
*/