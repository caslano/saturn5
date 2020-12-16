/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/facility.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c facility keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_FACILITY_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_FACILITY_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword is used to pass syslog facility that emits log records
BOOST_PARAMETER_KEYWORD(tag, facility)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_FACILITY_HPP_INCLUDED_

/* facility.hpp
z9SNu7x1A5/u4wRV13U95mR4thxvZfKmUx3W+XfLA+KDG/EJaj9V+nmmk/Z1HbX95AbkQS9f+4koH3LvjXyNYdUNnEOi7SBPjqWaetSZPMhqGvmcxbrUhc6Jlvy6a0DdtC6UBuZDxHWh1L0umPLdIMcbu+WJ8Wv3tYcpn30J3CvYfa3FwsExiSzFH1MvoS/b0bHO+hF2be9btC4516/emhL5/VBd6lN+I/7pOhmJygfxX2nyURZZHlW4aFaRW31qp33bPtHP8CQxqqMSeQN5h9RGe1zXtSZ8069yj6rhzS5cLPe42jcfFZ0YzwOE8DTyPDn6R+hWBpWO8itKlX56sS9+KfCAHE/zNODszyJ7kQPISYQ4SBmTc9xK6/xd3z3AZrkmm3tp7jaJpcwtkHH2cXL8iI6V94VhmbHaPSg/u8lWtMUGLRk1jQivUa6Adv/clbrwC5mzF8m8gkRAeuS83nkGG7zbmeMvGCD7q8x+tuxvM/v9XeuIjgHX+2hTDmYcN+nCnXQFt0H577VdXl9ZTLg59wXUnTGszx223owT3QaehdSX+7l+PoW8gRx1Xw9dw/Y4nm0K7YiZch4pxxt7rub/I8jzyEHkc8St3mh4ph5aQfWwCXxZdPpL2uORZKSjVd/MDe13v9RTjZOpA+aafoP4b0aKEqx2Wq8milu0J4oRoQsI+W6kAnndam3m2raVcJtLvzKfdjqasM+mrkQ3TeiSMD+hY2xcdP2EubH1EpMaWy2pZ/W0nq0jY3ORScjlJDSoTZh+ZqrEoaHu+86XLP1OV8JroPcP3Thnd6QH0hMZRLibZX6W+7U+0bXO4k/CJ1+ok2/e56uTvXpZ6vaa3y3L0rr9Cm7Ouv08+866/Qz7NdXtZGfd1rri7P9yky35bUc8yvn433y/qcPzbEsDc+QhO7Qed9Xy3Cr6D1kd+X82daMfMhQZj6zEba37/amex+O4X4tsnr8vT/s84O8H3r8/MG9+Z/b7yf5es99X9l81+33C3rcP9rV1fTGT6gU69Lnolj4QmE8F+jZiMqv6R3r/QRimDc5oLvW0YJn6T/ZdE0Un0WrgmKuR1e7UronO8t+t6aqvnmKRIrv8g9K1zJGeBTWnR/16Io7bgjBxy9bMPqDx+h2yG92KgLh57/WWhnmOTYFPif4YawD/c9zfOxBmDc85Gs5norNOnnNS2LoO0bU/+Ym6eSbaKbp7eXamN5FrbpTrM1HSFvS4h5xOqG7PRKmwq+hM5d1MfXXjTkPcLiDMYfJMtIdyzGrmfyaqH+EzUUv1m9fM90w0LTEuJjFqAg9Ebs9Dqaq/upk+D8UVJ0bHW6HPRKq3Hb2Pk9BLLF3n8vwuOvvQ+YutU6/0e+b5PUjnODqjU9BpVPqyY+1n5z0i99qn9tzlrHPb0rzK72idext5Bd3KLYF1Tl5yhKlzqbYf0Z9gDeT/UPd3J4QZ5t2JhtFwq318jbw7SWKLa7prHeogeouty7QOPScpkaBMfdwj53qddEZZkzj7T6Hbe5gUOGhrYH2z63ovcbvQStD6NogIbibgTGd9a+avb/XC1Tf1uw+/ibbf6LzEuHqJ0WOoda71TfVPoN/Q1m9wZWJ0gkt9U710MuTbFKlvt7vUN9HJQefrFKlvq13qm+jko3O3t7694qhvtT6T1LW+Fbcw77Xl1xqZh+6+raa+FS5lEvayWXPmF+RHdj3Br9uzgHmWOyjHm5o8rGh76tcR3/VxX0uv8jjEt9bJo+haD5p0LKXdnNL1kTBMei7kbNT1wnzHtbGFHE+mlUW5v8PiuPv11d8+EkVnMPrccSJd9Xx9JHWibtpbd9FNRzfKknc/ei0eRf/zxim+I/Tdp5E=
*/