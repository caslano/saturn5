/*
Copyright 2019 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ADD_REFERENCE_HPP
#define BOOST_ALIGN_DETAIL_ADD_REFERENCE_HPP

#include <boost/config.hpp>

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
#include <type_traits>
#endif

namespace boost {
namespace alignment {
namespace detail {

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
using std::add_lvalue_reference;
#else
template<class T>
struct add_lvalue_reference {
    typedef T& type;
};

template<>
struct add_lvalue_reference<void> {
    typedef void type;
};

template<>
struct add_lvalue_reference<const void> {
    typedef const void type;
};
#endif

} /* detail */
} /* alignment */
} /* boost */

#endif

/* add_reference.hpp
caXaxon2PIXKk8Yfm9FMOmMWLTvepyznq1u4L1XV7jN3FYahm2QHz2EVKKs8ppVnGWuzMeY6+tp8/mgLgXwfOVclZuf7OTZtZkF3NQQSBNKTwimlkxl/RC7LK9LITro0Wm44UZ/T2mQIilldsY5PoqhlolpZR+Zg/H0LYop4FzzKFEHW7YFL2TeFSMeME/qfthHU+gsZ//PDavEzVqnGb1tb3y4YVdnsqo9EAQTlZdc3rOAeNmH71G6Xt+x/AgQfLlHDckUXBLYWRRwDdaeBDbgBNggNojW8n4hAUtKNMDUHWhPOVEd/YwfZ5ngay78fcHvGGcn+bGNsGp0BKvikk6jaltKjKEn2c9DbdMOPL9N5rvyQbuw9VJrmicqGGSty5q77HXmrww+VhnsSsyBYZvke1ZUMiKVZM4sFN6pYSH8VqPFQaYSnB03RfjN4SoEHzNXTcZQoYp+5mHjAs+ABf1OpL4AH/J6LRXoucRuDgIhr41XSazQDUHSELlouRW/hoitRtIEKo6KDuagT17UaVydhErmNGxJZP/2RQ0C6lDPEeobga4rbN5P7iRlNuymSLfBFcLFFvY8JTBYx1EMIkvKHGS1SDPWDB5AO8gZd+44wqj3BczMgTyE1e+eiOzXEfUVBNj+ZIF4FiCPVtc8D4teQDljSzDNY51glsqXEA1YJh2qHEhWTaEAuwYDArUXCgfzAi4L3HOTOSpZFcTr6yYiWRXGM+uY5FL0cI9gDrblRUL0fKNVal8qvXmqseotKNXB9atqAlpeI0tX3GB3h8Mk1kdt7RIeRSeU+5pDiGOfiUMJpARZxc72nyH/VT+9/3rX5K0ypaY/32tIHF9dMH2RLX5pbM72nLT0+RPk4W/qMEOUPvhNI376kZvoWW3rvEOUX2NKfDlF+ri19Xl6I/tvSv30wRP9t6eNeCdF/W3p8oP067Q3hUibbGBeb7HfxheHsvX0JX2npNlqTmv7wn1gjPIh2BPQdJ5wL2IJPfpnX6k9f60/dM/FJZc8jJbz3HH557hnmzZC/iOovasIxuMXNruKcojv0TL1SZuqG7jRTV/NMHY+CYm3JOa0+7RKvLuptvYhdJ1yGzuehcZPP+HIuwOy9yOc+rHY/rZ0lUkpVAssRnvOCOUw8ihLQ4DKqKJCfe3myFwro+w/mm/A5leclaTWYd//5Qm61Afi3Sq93q2nXDzLDF4RJI8m7UGmaHz9cncaxDMq9nWhhP4tPx2VzkJ1kMSU18fUJl2P4iG0OCZCj/hP3TwMbxQHOQer1JyxpwCO3uu9KPkScr/H9bGLryCKZqDvkBNW8sYD9UH5xWsxTy/2l4Mob8X+kf3UFlkr/4c0lFR3yd3k7cvAgjBo3hpZ91w8izp1iNeedJ/5syNeFJRJAZpRqYE+ffBXqvO3Hb5rnnkQgWT/BEkh6Jx+CtF90lx66f+j7DboRoa/A6B1XBfNEZvRNtJnf7Cdb7dLMsIA0M4ykmaV/JdxpL4Fn3EaimIbi8FnbmHKjeGXNvx/jS+8zJ7EUMZXcqn23hCsP3lNLpyab8rQMz+dFVgWpUsHsFFQgwYldk9gDcYvYftL8p9X2Q/hNIB/5HNSubn7D3Ftl/Rpj7q3SeBuDtbuZmgmBCV0evh3bAPpKxJFcqT5tGBmGg9gxD79CU6Xgo06Tw8PwIWpS0yxfz907YsLg3PRlRUO8zO0KuygxqlET2cAYxy/nNUBdetN0MdWbNzU2TPsskWjHTZ21AxUhrth1O2PC2JzM/lHG9VWoIlaNHS+R5OHffg6D5favpI3L9PvDUTYz3Hso5uOoqz6IDBtREF4RQRdxpFOeFdMnU3oa0rMMR/KmOS5ciBA7u0k=
*/