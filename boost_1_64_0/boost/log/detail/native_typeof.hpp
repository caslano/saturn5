/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   native_typeof.hpp
 * \author Andrey Semashev
 * \date   08.03.2009
 *
 * This header is the Boost.Log library implementation, see the library documentation
 * at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_NATIVE_TYPEOF_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_NATIVE_TYPEOF_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if !defined(BOOST_NO_CXX11_DECLTYPE)

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

template< typename T >
T get_root_type(T const&);

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#define BOOST_LOG_TYPEOF(x) decltype(::boost::log::aux::get_root_type(x))

#elif defined(__COMO__) && defined(__GNUG__)

#define BOOST_LOG_TYPEOF(x) typeof(x)

#elif defined(__GNUC__) || defined(__MWERKS__)

#define BOOST_LOG_TYPEOF(x) __typeof__(x)

#endif


#if !defined(BOOST_NO_CXX11_AUTO_DECLARATIONS)
#define BOOST_LOG_AUTO(var, expr) auto var = (expr)
#endif

#if !defined(BOOST_LOG_AUTO) && defined(BOOST_LOG_TYPEOF)
#define BOOST_LOG_AUTO(var, expr) BOOST_LOG_TYPEOF((expr)) var = (expr)
#endif

#endif // BOOST_LOG_DETAIL_NATIVE_TYPEOF_HPP_INCLUDED_

/* native_typeof.hpp
9+n+tvGTMqtt9Oy7bV1ulIVyc6ve/fcpj/77qyr032cq6b9JN8/+e7IuQjmlY+OTSHciW/KJsz5o9y1xtcvzgkraX9yevf++Wa6/baR799+2e6/3yu55Ul7NOd6TbBF3zzDvFV7p+94E2F7GhkP03DQeFHc9DK86lgh/KNevJv16iZtE202q+724FmyxA+PkPhPLu5Fn+rJWzCu2sZ7pZ0V18I8I6LTLjQkq7fM/EL9ipOY7y7P2+dq3u98jFsTirmHV+vonPqlYnrXsLqhaXy955ipr+9p59/WD7b5e2wfp6qs2dzC4Gn394Gr29YOr0dcP/g/q6630zm/vzt961nyoPa9VmD1ncUFO0TJZRFWlNVS4dcXzpmrE0xEn15jkQCf+yHuOQD5thj39ehbCAu+B8lgO51kmHHW/V7jfbj2fzxfhGW78Kr/+z67f++XaLb5cX6TqdbXs97T9UDPP8uN8j9RdwtHAV8dn2usihtf0mzX1LGP4WW4+RvsAredPy/Wr2fNaQ96bxNhuWhqNSUW7DFYMH0fgw8/OdqOmhG+8rwYbN2Nt3afyjEa+BMcEB8WvydK+iBlnXcVtR1+cEeZL0LC8LvbW+shPtC+nGOqnqz1M0PmDP4ndXGzWMeJ1jU4DO33i7LQ/LfYWyToVbsKxwE6TBM6aSjiSTXYlBsw4+7SG32wh+65rOfRK59ht/gC5/oin/UuNqRK+mfGBNYEPc889DT1F7DxVX4TfAbu/r6/X9Lwkpmr6X4m3trFVW0N6rnbAMYZwraE80dm93rQN0jeNMNWy9EpUfb0pbsrVo1lebS32PHV/eNYBtVuu7/vn1plqmrn0oES79XW45/67GnKkqW6vHkh/TgZr2oi+jYzZizLm5C+zxj/o+uVaVqFTV/EssR/r3UdZ8bP1IhcWzHHUyaFyPdGI4p9nv2WnudYtx/PYJXKtJfbC7PT7kPDt8CiDEZWknz8+8RqfWKfOYQmnu63eo+lVVz2qg0wiIEc/rulIr7kF2dlGleajcefqT1pXoz/Bb881ubelahjNQJzrwB7kaakjT/U9hbwRxYqO/ez3oLZ++x3i5l3uU8O4gDR+HfHUt+LIY8qe/Y40SfNpg1z/wmiH6wlGOD5Ge+U1/lToYwozivv0SNUwxcEfip0Iswd/M5AziEe9sv1qwXjzafKtuBtjb9I3bExUK4ab4VFROfImKSzKKF92Ki2rR8TPJPKrrr2e6PNAeFzlM0Hb3ffk2kNcC0fHqs8ec+8V8zAZu1rhS0zV8CVb4Vsg4asZUfXwbRd/k7keY4dv/1nCt1uu9aMXiGSmL9orfJxPJb8lbIiMrVkPcO423r3Pwf0OmzKi77ArjO80v931rnd377Fc5mlnvSvMuSK7au14Zrlx3Lhq1Lvy47hTBkfYt6fj5806fvP+n7drO/70itXbR0xNPFHrxqsr1/0zQuwXJa397JpL7pp6XYdJP47pEXmsMt0z1dcJ1F90Ar148+GRU35Vljxhedjrd+4ta1a5TqA75/nND1+bddP9DT99+Hj87Lf2rXqyQ/V1BcVKvFY9cPcr7zyTknLNM+OKc9bff+K71yF0S2/xJ/2eYccfzO1R2unA8x99vb7tf55uoS93+c1HDf31sIxef18Tv6nTFe8U9VuMLvK6fvO9L03+4Ce5jY9/c8vGoa+1/NVJ9JvV85vveHvKeXdmPlj7uqj9ZsLpBx79dnUR6SOuzEMdgk2QNfq7JXKz/l6GHydhpr3fSvZvybVIZLz6s5HKbcJNUJ6NYDTcCpvD+2E7+ADsCB+EneBPYFc9Pyl+694mGK/3CUOs9byvY8/PwzAOHlF3vZHB6q6tugtH5JE=
*/