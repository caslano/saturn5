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
Gg56lsgQe427wgFlVPVOiBpjRAT572jdJu/QVW19iC+wqf4wXqiDc+d9mvABkC6VaFgOvdYApaHpR39FfysRVi4V/8hWwc2sWaDkY9SmOzhXU/o4V7kpc1UKrbUwlZNF/51Bqfqx2didJ+JXKPnEjFqhr6iydSzaRc/vRhHOum511vmMHTzr0o0dUfxipAtC9ZCM+4ZmA7DhxohObym82o0sL8PHrV6wAF9VhyyQjp4z8DnM
*/