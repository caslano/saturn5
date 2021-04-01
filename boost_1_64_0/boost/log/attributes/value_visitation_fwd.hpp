/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   value_visitation_fwd.hpp
 * \author Andrey Semashev
 * \date   01.03.2008
 *
 * The header contains forward declaration of convenience tools to apply visitors to an attribute value
 * in the view.
 */

#ifndef BOOST_LOG_ATTRIBUTES_VALUE_VISITATION_FWD_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTES_VALUE_VISITATION_FWD_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/fallback_policy_fwd.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * \brief The class represents attribute value visitation result
 */
class visitation_result;

/*!
 * \brief Generic attribute value visitor invoker
 */
template< typename T, typename FallbackPolicyT = fallback_to_none >
class value_visitor_invoker;

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_ATTRIBUTES_VALUE_VISITATION_FWD_HPP_INCLUDED_

/* value_visitation_fwd.hpp
6AJVQBIKC5YBfpqfBObCeVXj+tbvl13Fr4GYh1a+If5fEar4F11yXc03oVeg2W+B9MIGN9k/FNQhbOqn3jgo4sCHAPDFFeyTC3l+SLF6nTehdE4xv1lN0i1azvh83x22WJOBcm2+/kzRalrFr6QUMLeGLJTHch6nsABhyY6wLIpiB04uKbJv+a4xKlYEA/O/g9NBz5IFldRfVe+mE1ttJR64kTJWwewzpG9JknYr2s6x4hH2+vx1FZ1qZnUJ+HPdZraZfIPQllNPfvjjmpgCy4ulF8we4k1mOQ8t95QYqu112oQ7Zeze1lxRS9ABNIONdF7IT072OYX1HN4tC5/Cxsz3iN4xiCEhje1QHSke+ccyJSDSgc2bKAB03HKWTLW637v04rUu1S0il3jAtFUsTX/G1v52jvI+6e479PQdmriF/YyRTLLtzaW6E64ONw+dbt9ptaJmgqpd1As8e15PkKWGeayfTXnWWhEw3hrR+lzrEapSjuCuj7/Vyu2+SCTzX5aDVXk2osvmS652cCbpzq66rN1kPxRBkg/6GdU30WKhWogAsILyxA2X2Q==
*/