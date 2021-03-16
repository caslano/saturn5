/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_IS_ALIGNMENT_HPP
#define BOOST_ALIGN_DETAIL_IS_ALIGNMENT_HPP

#include <boost/config.hpp>
#include <cstddef>

namespace boost {
namespace alignment {
namespace detail {

BOOST_CONSTEXPR inline bool
is_alignment(std::size_t value) BOOST_NOEXCEPT
{
    return (value > 0) && ((value & (value - 1)) == 0);
}

} /* detail */
} /* alignment */
} /* boost */

#endif

/* is_alignment.hpp
JxR7VDtLuT5DitnSyUGCp2qEimkuzEQckF+Z9pBhDiE9bu59wtGCDR6EGnNZbVUFDbIqgB4wQ/lEhblcG2SxHJmjPE0JPbS/0geFqzWpraenq1vsNtfhHog6FxuDui6Cb6/nxg/1PlaGrEOszFEaV3IfUu/NtAwkJTpojjp0vVyhMtDstxndz/Feso2O6Cbk9q5hdGu6LyrlkQxJ7PGdblNA28O/a1e2ghvKz4U2U9nQZLuqqZLa60y0cUR70As=
*/