/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   current_process_name.hpp
 * \author Andrey Semashev
 * \date   29.07.2012
 *
 * The header contains implementation of a current process name attribute
 */

#ifndef BOOST_LOG_ATTRIBUTES_CURRENT_PROCESS_NAME_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTES_CURRENT_PROCESS_NAME_HPP_INCLUDED_

#include <string>
#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/constant.hpp>
#include <boost/log/attributes/attribute_cast.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! The function returns the current process name
BOOST_LOG_API std::string get_process_name();

} // namespace aux

namespace attributes {

/*!
 * \brief A class of an attribute that holds the current process name
 */
class current_process_name :
    public constant< std::string >
{
    typedef constant< std::string > base_type;

public:
    /*!
     * Constructor. Initializes the attribute with the current process name.
     */
    current_process_name() : base_type(boost::log::aux::get_process_name()) {}
    /*!
     * Constructor for casting support
     */
    explicit current_process_name(cast_source const& source) :
        base_type(source)
    {
    }
};

} // namespace attributes

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_ATTRIBUTES_CURRENT_PROCESS_NAME_HPP_INCLUDED_

/* current_process_name.hpp
l3kUgVT+ek6wGpoQRgtaC3rLn1owvP88QiLmCsNaJVjFCHi9iL+qDGj5fotBhEaETvQnw+CoEIXgGimiyZcAPEeM5hU3MVfJFyfoElgnL+iw8xnWV17lod8udko80vWI2y1Q9P7cEMGmedf7CLDr7XnZ89eOSwg9hgm6yYuEyUSdIICDSo7sgF7fSaJqMZMNg+MnixRZd/5SSXJFVQUMGwsAXb5ipOXUums3wnLq+wfdF1sNlPz5uf6bWxHnn9zYrSLZypK7hq0AgHSl7O+MV34/oALJFa0iftwS5gO9U4qmwt/69iPjP+NNl9laqPNn05zGq5WWqiepcD9chxsShG/v+fCRg6kD53OpPyRrfmCkTJRLrSi6nTnQf4eflUT5uNQ04wuEhS0waJhoPf6ZXtt+rd6QGo+NuXSmlodGjSUvKth37rPcqgKEmFaI2UvIOIyk1wbwp3HbuAOrkUwBaDiJoulJu5tLiLI4mHDxbtiO0wTwOmxzuDzVfz0TZzCgwoqPnCCchJ/Y8ksCZbtYZm5sZuBA63D4r3NlgE1DazHidwL6ot9HQFYM9Qm+occ3ziR8Nk0VEfqc09j+MoIltiH8N4q9ZyU076CbOpGbfeGXulsu/qZRLXWj/o6NP6Ezost7cLwEr6YmOmqCZlqC5rsHMYMOhGiqZeoU4EOlFy4vfxKV2o825mctJsqc20qh72t0iWUOLWVzM9aa
*/