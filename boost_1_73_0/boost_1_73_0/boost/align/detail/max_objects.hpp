/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_MAX_OBJECTS_HPP
#define BOOST_ALIGN_DETAIL_MAX_OBJECTS_HPP

#include <boost/align/detail/integral_constant.hpp>
#include <cstddef>

namespace boost {
namespace alignment {
namespace detail {

template<class T>
struct max_objects
    : integral_constant<std::size_t,
        ~static_cast<std::size_t>(0) / sizeof(T)> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* max_objects.hpp
0HC6T9VCNv4skr/YCbBPFxMTSDS8PGiL9IJgar0mvkQXECP0gbkJhYgtkaOhMZqNdXyNKM07S7imIqFbhvnxYw9KWlWpIl0Neupt2d7EYLaH6PNTk1yOfv1rjctQY0SM24CoE6DeY67M0T+K1rAyhubDKrRRj4UzWLPlKJ6nwTX97rTbjNekNW7baeycMfYZwy5CRyq3d26MnXnBMHOP9zz36peRL1ySGo+zK9eak+e0ndaExGErNdaYn1iW3hxxnAPMa07oyQoELfqh/xG90O6BvjLROXhoZQFwZadnsLGhYP3Rrz9M87b7bVjA57/fvdob/l5ev+DXr+ytXXfjfh936tYORLaEqtwb0NnAgwN9+Z7D84alpB+Whgab4PGl/KRRIBYNiAp7vzFcfdZvUmZ96qJOO2eXmuuvEx7qpe3xIDJokxqbvU5ug75Q41Wn9LLZg/cmUmKHuBeKurHDUj9eTDaZ+LGO3l9cvntzfvzH98cXl7ybcwZzMCeJQWE+ejRb2MooPKivyCrHcW/quw61GJkuDnGGu+RNYJCi2sVx5l4KjVYr6nkepZw3wcB6b7ejqLmXdsNvtZi0dZDSngT2CcwI8QOQfBiJ53SJdNNQJzs2Gox6Pj5/c3rxMgCgs2h/HM1WCBqwuCfK
*/