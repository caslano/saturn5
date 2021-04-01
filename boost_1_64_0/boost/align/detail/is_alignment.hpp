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
qLuHSp3e2kqtzx0FnnriqttZX1+9NZi5BzN+rugrxP4atLpDsOywBwLvZDklMPV/bXNHmkauXfHarlVJv9FZSfQA8zV+3GU26cALUN9Y0bxA8Qe0nLCz13/BjbLewwkkkWUwZJ9nLlmI/ZoDLsXzVk/YoDJFu17STywirB0PXAzo2UKNpje6vqBByTmlUz0OeVV17R5AIw5Yi0Dxc2bBYyy7lo85CidKGVrL4lqfELWEsVNO+8Yh7BKfuy9xBadPYI7gplI7t1nGvokqHEsDgmGtn6IxiJA//WoTo8eF1fy5YTBegcjxNDSkwyLzU7SGV8w20X/36hOEWSJ+0ADrBOghz8JjmvMYLCdhqYdNN3OEZLGeIEBWzCjsZ2NoluDJNrGhJBvliRplLac/GxknqaTFLLE5FRvMBMJiSyUfbDMo9ZZ+yhPbgdbM5xuR0BXiCgzuE73wdHtu8ggBBfi4yWdTySHrg0f7W5CiJemE+Ay7MbLTi8c7NCHZmgmMn3I3uz/xnPPBWwWF0DKg1Erw0iRlaZ81hoaeVwss0g324y7iIHZk9aLd+AoISg==
*/