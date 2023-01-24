/*
 *             Copyright Andrey Semashev 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   sfinae_tools.hpp
 * \author Andrey Semashev
 * \date   23.02.2016
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_SFINAE_TOOLS_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_SFINAE_TOOLS_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! A distinct type that can be used as a fake argument type in constructors filtered by SFINAE
struct sfinae_dummy {};

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_SFINAE_TOOLS_HPP_INCLUDED_

/* sfinae_tools.hpp
/Zkf9uduky21r7obc9Lf/Vqf+DBGnCv7saZ44m/9OJJlhJXnkK+f+Uk/DCsKqac0dFlv7XtHDr4kzrHU3nAe/cT71Lv7tu4ZFHLGN3N+v2dpYZ/Cgn/6AOxS3noF54/7D6B42w9odZXjvMo+cP6iIKGIc6Yd+f2Trdg/FVLfh+stzm/fzxScEFXO87wOX85bF3lETh3dfkAyiPBmyBVvaYbDtxw+3v+2Wjt17sGe7IuP+nWgT36sfb0RzGPe8JdIxescOGL88nbuRX5++vsKqCJr0cn1lGX7xI8Xcu/a151V3fI9pr/fyvH0gx3SXnezaOPujMlPPi9u7ThuOWS213RSpZn39+16uA+vX1l4d/uRXN9htksEvyTfrf6+z5o2UAtEhJ3bi/b52nNcJxtzORz1bz+gzvoQnjqI8LFfVXlRext69YY0azowvr7wy8p3u+I5ux/94PSv44ytv6DqaaCX71a+wXlmbCaDt2V7oTu3/OZvsP7Y0bcXuBzvkf/tBkc/RZbl4R0u61akcfGLhX1qDCPe9YNoo4OdVgzGn+/Gunn7Zy08Dz7eZ9mJ/A/kCmk16EHf/Rbqf/wNi377AbEjvEnhBegaLcehy6U7trzEa2rY2zX0Qk5+fD7WGK91KTkJ/CjGS9POhYTcndmy7alnMwrfAhnS9JMaz/5xgU9sxL3IzF7gaZJlXBp6ZVPlIqGFa1zOS7oX8vEz
*/