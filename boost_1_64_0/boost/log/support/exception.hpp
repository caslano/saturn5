/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   support/exception.hpp
 * \author Andrey Semashev
 * \date   18.07.2009
 *
 * This header enables Boost.Exception support for Boost.Log.
 */

#ifndef BOOST_LOG_SUPPORT_EXCEPTION_HPP_INCLUDED_
#define BOOST_LOG_SUPPORT_EXCEPTION_HPP_INCLUDED_

#include <string>
#include <boost/type_index.hpp>
#include <boost/exception/info.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * Attribute name exception information
 */
typedef error_info< struct attribute_name_info_tag, attribute_name > attribute_name_info;

/*!
 * Type info exception information
 */
typedef error_info< struct type_info_info_tag, typeindex::type_index > type_info_info;

/*!
 * Parse position exception information
 */
typedef error_info< struct position_info_tag, unsigned int > position_info;

/*!
 * Current scope exception information
 */
typedef error_info< struct current_scope_info_tag, attributes::named_scope_list > current_scope_info;

/*!
 * The function returns an error information object that contains current stack of scopes.
 * This information can then be attached to an exception and extracted at the catch site.
 * The extracted scope list won't be affected by any scope changes that may happen during
 * the exception propagation.
 *
 * \note See the \c named_scope attribute documentation on how to maintain scope list.
 */
inline current_scope_info current_scope()
{
    return current_scope_info(attributes::named_scope::get_scopes());
}

namespace ipc {

class object_name;

/*!
 * System resource name
 */
typedef error_info< struct object_name_tag, object_name > object_name_info;

} // namespace ipc

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SUPPORT_EXCEPTION_HPP_INCLUDED_

/* exception.hpp
r2+f+61f5pywdMd2TpjVbqHZr/oF4Z4k4aREh86pbCz6i8iPRmZceH9y0KyBmYvfJvo0yxizNW4Zjm0e2R43sStjssQtV+LSKDo0RzlY48bIqBnXbdIkaNbLxC0fPW5Ujm3RB+xnZNaPHFdfgJwzEgn7eAmrf3TVwBuuueNQzGqZscGoRujZRbbZGWnC65Ui53ZLePU84dUz4dnP+HyEMIeL/x2jQ/vjE0WfZfLhLgnvBDNn+8bh+Pg7OVvN2aj1xc4a18czn8dKgzehuDdx66TuOYusMXp27STz8hW6S+xTMVvlq8NXavAZGnmeoZE+Q2h8/yydB5GSrc9xgOeYLvGqZ8pyv4ayz9+cHb5E9Hc7xzH6MZMPiIWoEv7e4NSUdEvxhJkSkW4ndwuW68XT5meQPk4/nkPXrku8r3J4bjV3xdz7jLI+4Rf7WaXx8IUGOjasdaGDpFe8me/KE319R+qKSc/G2PAfHpPH73niR1x06djzDJN/Z0hc5pbunZe8KsA/5CbtVxPPkb5EzaODYmeRv5HjI/1S/cHyuYdwvpJwzouK9g/yzGkXmTmD+cmHy0EMXz/DmCuRc29x96O4W+kZ7w4eTZ9u6tPtIh/vRpbnBK0jfL0cPvzXk26txU0NM/fQW/R9/COduqT6WdbnCz7HPuLTXuyOjP7A3wkzky+5cxblFuTPLJ2nmCzP86AbS9wKXeaf3EZOsubLWSLb6iYwInUjq7Gb8rwj3AFOLU2rv2u4tbTMOo4UWBP/wSk6j6n1brzEaSwtXCPx4wH8WHS4bER7zlgx+TioCTJcJ2sa3ip59qFvpLOdPbVvOm18NZz5vkGm3g0U+0nipoGm8055httc8Ycv+1edbeH3Cmr9vkn8HugOozyM5u4DW70Nz9sMtcP3tzzDKe40WgdpL03+tnfC3ZTOZbwjbsb4qzmDpOztJy3eE7ONUbP9L7qlebaESlkyk2ppysHfJE4jfa7bgD0edcq0Q7JuA/9cefblPo9fc/JnFCzBL5P/b0ub0ZSnro47H2FUMe3wYgnnXfKrn5m7+lnsd6Bu1jRtc6KEeyJuuYeAcF8UO7ezjaQjY2HVfWHtSzpp4GlfosVuFWmfVjCfo3kTdgdKWrLWA43XWNE/SV4tZjxtkdrTeFA3EsL6qHccSrVTS+OWKW4HefJySWGB5mUiOr/IY93JjAaF2oqpYhbju4AR4L3BuyC1jsWK+XxfZF7xiGZe9WdJwyzfHaTiQurWdjfJUkZYT4J/VcS/4jL5hX+m3GyT9IonvaqYee7lUnZPZU9Zb1N3HxV7C5wm5Gk7VCfcjHJqmjbjO3Gz1F/VyfInE/5uwj9H3HxLvsU5dbCbyvvbK77H3PC0Sjf18wuJb7PD65VwX0P0hb67WI/QzpHBds9cl30+7qpkxvVQPyTK/JY513I9ZhuSg3ZgBeQdoJoxD3dkhR1RV6CWe+99oGuryJk0wbUR5J2ujYicL5P3T+8ax8gzRtSs0JjFldrLMGeMGDN9d8OsnjFbIHYaWebbUuBZYlb6/oBd6Z+pg5hLHy9m1LdSs/T/zfNJ7nkl6M+X302dv+y9vJ2+v5557p3XNml87OeT2OcDj33+7VjnJ//d55Yc63zmrzkvt8+n75j6HbcVTvSs7a7tME4MU+HZsDncCFvAa+Fz8F7YCj4MW8PdsA3cC9vCd2E7+AFMg9/DdPgTzNDx+84wDmbCNvA4OBJ2heNhNzgZ9oD58AR4DsyCL8K+sCZxHgRbwGGwHcyGA+AQOAgOh7IPFebBkXAuzIEFcAxcA0+EF8Nx8DY4Ed4LJ8En4UnwgOqrUR9mwKZwDmwFZ8IseArsB+fCHDgPToHz4Sw=
*/