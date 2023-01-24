/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/time_based_rotation.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c time_based_rotation keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_TIME_BASED_ROTATION_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_TIME_BASED_ROTATION_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass time-based file rotation predicate to the file sink backend
BOOST_PARAMETER_KEYWORD(tag, time_based_rotation)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_TIME_BASED_ROTATION_HPP_INCLUDED_

/* time_based_rotation.hpp
EzSRNoW5xf2yes3ZZ7M2Gp90VTY48yrpcVDQy3XEkfUOe7jcJCGLaA5dQ+27Il1u5Wtwz+9uFPmwRhAduroqueHFcNThdSg8JJyq2FHVJ235aP0yWcXU5fWT3dUhn5kj4QvnSjByNv9yS6Hn67vjlzCnVws2oSqmXF5TNbrMGy2GtffdsrX6Tu2C3f0lTpYNNYnKioWezJXWDjpUfEYiGLKlSksOC0IUGlSt7n68R1zmMkMLRgZ8M2+JCTmk1kR5vLLnzCXGdvT+8yRq0goHTq9QPa7YqckfFzHYKfNt6Knj5Wu4K/2of6INv6jKMCXIJik6DYkT+R0lOItexVAagwfErSs6esKWLJatOo/2M/vgHt5el+P5es6tTe4uzLU2ZrvuDlW7VCnEemvIaBn+8sdRDzZLK0+iZ8bhDsQ0HiXSDJOUEpLTVQMPfh6uoni9yzon0lHThbrPlWQ62MyT4+J8nIy6z+XkD8EpuWbuDQ7K9taqNMS/c7PXuEa0FdxxKZ0UsdfMizPCV3e1xwJS1IYickK8L35l7Jut0ipxFU+wzLMcGxQVTHXjmHt/u3sf6cSyRD76m4yR2bbNqr60CG27ZH07P7WpTvzDo/uqDk1dUzbC0uqqF6C3xdsfQ2E4e0kLKC64x6WU9SOVV0/t7dtiCrQem3/zqerbVPZgw5Xn0P0Udb/6J127n1luOIVk+dnAKhutdAJ8m6IH
*/