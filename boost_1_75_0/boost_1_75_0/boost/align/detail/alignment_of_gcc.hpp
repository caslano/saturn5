/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNMENT_OF_GCC_HPP
#define BOOST_ALIGN_DETAIL_ALIGNMENT_OF_GCC_HPP

#include <boost/align/detail/integral_constant.hpp>
#include <cstddef>

namespace boost {
namespace alignment {
namespace detail {

template<class T>
struct alignment_of
    : integral_constant<std::size_t, __alignof__(T)> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* alignment_of_gcc.hpp
hRgWvwKIIbdB1dCVpYSTyMrXJmxAQHFQ55fki89F3FECnUEdEMRVvZN5Ga5hPpR/69iHvdW1HSRziUGS2h8rXQi6BV5Dih1pncfaBP1r/oN2GIFX0rk8L1Ngh4c5AJ6Mr6bOQrDV1W0GY2URI3jiGSlVKlRisoWM39pKGsGHasGB7w+ge09vjBFoVI0dziEjWjUMZVTxxjFLgy7WMJqYjDn9yKf32rEYpbDKLgC4tLxm7vNjiA+sKkMOqflNrIhZ1yO8vpA952PcgkUp9t/aQu3d5EVj2OYDYUmKiaIaBzx3F1jw/XXxM2gqxOG6gqF1ZnRKcsQP+td91IZCRvb6Q1PcGZZpODll5SuNEyT6uQ8bhIWKlvsYphpNZXRRJdEhHTW95xxryv0m6ti3TCddA4aEjsEahaYpytRUT2wVHQNiUM0sQY+sKVLmbqtdsAT35p9DQljZ63mqhQNLsxMVJoXY7VShRF4o7Idut/AhYbLk1m8kzT7HLJGDx1CIsBWeRn+LM+wLKLrPm9+ROU7hVmy1eaczcxLAV57fYJdh3bYlqclXaHZfCJOlV9m9z/EkBDCxFCtClMOY+CeTiY++E1HIVQpNQOZpnlK7BOG97/9CUU7gyHs0p48vYS1O+9fvwRKMMq1+JMzZHApap3gVMT/FYNQMy21XO1IhVt5i5sCvncdvPaRyqslwr5WUIcMlHKwmuOUO32XgxWu+
*/