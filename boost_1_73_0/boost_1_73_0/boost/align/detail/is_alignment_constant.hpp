/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_IS_ALIGNMENT_CONSTANT_HPP
#define BOOST_ALIGN_DETAIL_IS_ALIGNMENT_CONSTANT_HPP

#include <boost/align/detail/integral_constant.hpp>
#include <cstddef>

namespace boost {
namespace alignment {
namespace detail {

template<std::size_t N>
struct is_alignment_constant
    : integral_constant<bool, (N > 0) && ((N & (N - 1)) == 0)> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* is_alignment_constant.hpp
u5elPj8RpyvfivF6whZSHr9LpDw057CuhISXz7RWz5Et5y4yyjTeJZOxSXDzNFLOBheZUsWhirfvZTR3t15Vc7UxPNVqqOj9htK+Vgu1fDNDlNT6Jy5qXbQDNUGNtFRxZqIdMlerA3m6VNE4b0cKax30KuZeJWsCGpiAW2gWllvTEE0O8suZ+yJrNSBlOFOfEbTDhYHkbWVyJyW001AB4jVt9/bxDnc6yY09/4eObjAcnU+Sv0/sOFEobuCaVX4=
*/