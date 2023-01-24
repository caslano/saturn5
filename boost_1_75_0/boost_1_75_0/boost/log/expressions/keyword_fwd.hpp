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
3ud+33PO9zvv8nuf73vOOe95P+f8Tnfx5R9sY3zLjFrYy/3u9LM1qp9clie8eaG0w27PdbC74/LUqYEInb6acF0YkHia7oPoe+u5/HAoSZ8USBFf1npF8rx34GC/Id4xLevLs8D1CJUgTRnO85qWuWNleIHLUcz24cGLKbEFO7z4RDFicBJ/iphE6K2u1+rcwWZUdyFSQDfUYqu1/ywjvZAJ3t8uOvk3oPtUAimyZ32+bZ4g10zY3QBOujpZ9F5DTFdmSy1JVJEr6HgvlsbokIhsxYC0nOStyUOj2lKKbT9kPRf5TRHbQJ3U7NyZ7zCqCPcru+zSX3ixzIPN/qTf7ZHtG2VhAC+lKZjWz1Xo1ZsM8jvAz3UYiicPPH57OKXq8MIyYggdDftw1IpIPdqC1B2o3u7St1xsuuuvYxWBWHJD/cGFRkGUpnQk1jNc+rSGo8mqXe8Yr98C3yZBtmSXsl5uA7F4ffetE7Bkd5qaSAMhcdOxB1lQcedTgIfNeKWkDzKV22PtsP/hJOJEEJIfzehEZ5BhsqbAbAd2ugCppC4wdct2OG9bAHN0illv/fSTuLNeZ73uLpAftVl4ttd2X49qE4Y4O/Kqor+UjiuzPqo1GzBfyYLeHc130fcE/LB/qXonfgqP/A693XRazl+OR6Wl9j6nfV/t9WrQSO3dDjnxesWO3m2V3SczCVnya29A9Y4dyjOHXwJC4pUg
*/