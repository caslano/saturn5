/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/ident.hpp
 * \author Andrey Semashev
 * \date   22.10.2012
 *
 * The header contains the \c ident keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_IDENT_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_IDENT_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword for passing process identification string to the \c openlog call
BOOST_PARAMETER_KEYWORD(tag, ident)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_IDENT_HPP_INCLUDED_

/* ident.hpp
VozBKwhOdklXiRxcXbZTpy/9YWqRk+C84Pcvsm1Jb3yMH3LA15+4bq6gizJo8qk59BZSBtt827G2GbTyEpy+YMB6D4TMInIk2SUnXZlR03wgVN6TJ0LdxVO5QR57PNvrQY4/KhGineAjDSn4enIzZT8RluSUb4dK9g4frIxMTc7iUX4/6sX9L0eYNq2HUwz9doOkr7/wlefmT3ChDEfb0dsxTO8PvtcrYyKmeRjRkICD+JM15lQDsC64VyhCHKnK8u9EyR6eBFlLwjzanOgs46CWbb5Rox9qSHKsFS9/LgLjpNBb7XCV+B9UY4FHz/p1NYNZUsnYa08za3c7TNfpkhVJuoWS/cQFLqrh3MPlKHAk1STNmokjWdzcr/SoTFMsnL8vsBqr0ajMVx3tZ83g+OrJUcpW66w5XwfXO8rsPZseg5p/QHYsTdh//YVWvWxi7PonEigi4FvBcIKUM2lPi2tHROhjpLE3FVuFbia6zEkMkpKdXvs13CGwSxWZV9bg9OysRh+pUtkL92FAn3feQGf/u8MOxvPXuKgvzShi+cOWfR0NH2veZOFQBg==
*/