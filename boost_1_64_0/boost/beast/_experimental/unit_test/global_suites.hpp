//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_UNIT_TEST_GLOBAL_SUITES_HPP
#define BOOST_BEAST_UNIT_TEST_GLOBAL_SUITES_HPP

#include <boost/beast/_experimental/unit_test/suite_list.hpp>

namespace boost {
namespace beast {
namespace unit_test {

namespace detail {

/// Holds test suites registered during static initialization.
inline
suite_list&
global_suites()
{
    static suite_list s;
    return s;
}

template<class Suite>
struct insert_suite
{
    insert_suite(char const* name, char const* module,
        char const* library, bool manual)
    {
        global_suites().insert<Suite>(
            name, module, library, manual);
    }
};

} // detail

/// Holds test suites registered during static initialization.
inline
suite_list const&
global_suites()
{
    return detail::global_suites();
}

} // unit_test
} // beast
} // boost

#endif

/* global_suites.hpp
Nh8pL59TvyF6OxwzSdMmJMzYgGK+RWrt3+MK26rf99FvAv0qYe/37LO2d+GCRL+x2osz+ub9v5u4WCTRhz+GDXX+GV5NO2DW/RRlQbmWlUWE9gfSzzFNv+qm2tuc173Xvkb8J88vuX5BnntKHRzY6lkHORMrrQPVj1H7XsQj7htdUZzLsl1Tsl3eF/ZZzjqPt8//OSVunZNlS9gGUp4l+AZsw81TYLd+sNwISdUa/fRX8NdzD8SdI+5Qp7hNWs4lLVb9TZ2cyXSRAjJzn18lD58FNHEEaF+y0qXvL2pfulnSMsQRwz/il/G5qcR/jrknzBB3mtpGsc5fQ/Utd7jqW+7f6XlN+sy1J584p0meujnFbcLE2dpksTs/UmabcAVJOg8G2MYFqlfjVDsld7ws9mHUbcpJ5y7GPpop10skzmRjR6aOhH/bdbOjuavcptq14ydoHafB8vOPzx6rVlisPHWW8H298yRh9odZYSaQ4vK6PiZhmkn8jLne/d3YqasraR0WUE/L/QpbOdvukadYcYeb/He1pZnsU/12Oy2zpR4SnOK2tXPPfFLM+k77GltdiM2bsvGjAAXJA31b+4ipd27Ly8t8isR/vrrtdaTvzlKvpNLoXy/nutVnHdUp729y7lR+rWaMaqdjVBPS8DEMDC+bS+ykDtKV9RFrfvFgpKcURkF4EGmKfzTyEb/DG9KvCNcIfq3hW+MXgPt62Erj6qLx1OG8v4R6nisTHg0rGycLq3jvfsN2TzswK3yMmwl+xs0Sc/8tY5Ec22TG0mIdK+zjLu1c4+wGaa8c0/aqx9eYeYK2Cdt4HiVxSDtQm5nm/B73RSfVTr6LjDWAp5FmcZTJDs8xm88VpnOWsrsjW79war/QsVvDhZvrZ41XZS3MUZf/DyBWO3bSrjTVZuxzim4s73wG6b2Hxmf7Dk6Q6Lg8+8OEbI1Hrqeq8wWx2OctYwrGZo4pLphcPtaeJ3rJxBZS6ZiwTvTaGptwn/hIg5a/ifsc0WlJzOjpdduWLmO/887y9k5s7L0Ud/Wv29QBdWrNRahn0yZM+er13DpuystL39L2XIOJVZvj7nJoCjvDla1oo69VbB+FOTmTafL+2oaGaWHs1WWKu7XTusY4Pec9qv87Hb/w95pLDUJndFmcTp1baZhm+JtrLCNs+TUpcKfbf4S5Jo0W9zmiXzNExs4pmfnlc4gw27XKnT+HzcbDVDmX02b3JLNsDU6v20vFP47e0MCsPc6RY7XsdkbNtcbX+N1O02CNxZoG+3cmTfrsbfZlOU+YujWfXt+cLLR9u+h9LTdrXD8p7tsd9SirXrTVBg4Zt+V+MCJGxnLm77puY7Pt+SiyCmnMsS9px5FwdVh17g0DQ8fs9LazZW/feq9ln3/qOFjoZ8xNgNQpx6VOdW3Uau9SV7qeZmyAik47z/FTzhFrbKyYOvC0z6c20o85OQ/8HK6mnxzYWbGflD0VS8+bOLbAX1/RcDFmvvGzuN9yXuUI8DlvHmDCNDJzzhPi3uDIJqX1dc39odf1+u7dP3TcyhH/Dma8XS7uera5dDaZL7enE7zL7f+KZ3vWvuNrztYNhlnzbOY/48m1/ZtYjxAfZ1W3df4kP3Mq9df50euhVpx5hbmk0hojdkucb+n8XHWk+ZS3/7tFJ8npdQ9m+m2o+L/o9Dd3C4XtJC3Njf3MfuK+Ut0mL2bdhfmM9KdGeq8WRJl8VHaMs/CbAes47qNwKmSeY5/PyLwlsxrPF9x966HXq9e3bPMZLxtBWu/ar+z9pZvnnEX7mf/7xO6xup9dn8/+FWnttqX7hvaV8Tm6Sp2k4yllXlP6SKEcMPeKGsb2jbap4t4l7eWG0LI=
*/