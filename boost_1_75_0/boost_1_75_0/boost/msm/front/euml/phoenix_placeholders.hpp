// Copyright 2011 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_FRONT_EUML_PHOENIX_PLACEHOLDERS_H
#define BOOST_MSM_FRONT_EUML_PHOENIX_PLACEHOLDERS_H

#include <boost/phoenix/core/argument.hpp>
// provide some meaningful placeholders (instead of arg1...arg4)
namespace boost { namespace msm { namespace front { namespace euml
{
    boost::phoenix::expression::argument<1>::type const _event = {};
    boost::phoenix::expression::argument<2>::type const _fsm = {};
    boost::phoenix::expression::argument<3>::type const _source = {};
    boost::phoenix::expression::argument<4>::type const _target = {};
    // this is for state actions
    boost::phoenix::expression::argument<3>::type const _state = {};
}}}}

#endif //BOOST_MSM_FRONT_EUML_PHOENIX_PLACEHOLDERS_H

/* phoenix_placeholders.hpp
tpzVaWDVtFcU+1HBflib041FcKMrv7EAftxhFvvlYl6TlZjZvA3JC7DGYljT+0gk4NeyD8EoTaKWrjvHXs7gLcXCD5iSL7pFQh0yDwy+hpB3PdUxyZVJcYTqQ+xGjuslzDnOhns3k/kdbmQyv0kbcKnmZ1TZ3G63xFGCD0chcuqbdGSZ8MpUbNTHb5LQkPIdouERjp8HN8kyXK7/sTwY7w87GJj3CxTe73owFN7P+f+Y+xL4KIol7s2xsAHCLsdCkMMoQaJ4RIPPYESzksCsJBBEJCpHFIV4R9iVAKLEJZhlWEABRUVBed6+Jyo3qIFgEu6IgOGQW5hlUYPwIIBkvqrqnmMPkg3q9338fmR6Zme6u7r6X11dVd2dFgJxb6ynHhIilmGArmZsG3x//WdffVXDk7zwzQX7wqnd2rtCxDRQFU9XaDJcbbevl9fVbl0uXbmXCnijxYRVrW53hWi0RyoUPmrnH/nXp8wmRATU6dWf66+T8+dw6vTGnSFGmS3lQXWasayuNoqouz49y/oIxL6De8OpU1SoOt1OdVJ9UYPHNjJ4P5ygnBvOzHOux01ozRXHmZw3YdbXoR+pq/5g+Go59r2rAJU1jQwGvjZ3o3S4JzcTaxsniTaTXOK2mUq18eOFhLhBgnhCsf8u5e2RUS24syTBM0ji/kTB9ZiE/sQbsJzPb+LOxOGCCG8pvsRdexRfYh+aF2UdgK8O
*/