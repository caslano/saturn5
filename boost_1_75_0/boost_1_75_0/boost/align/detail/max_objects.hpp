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
UnKolHQnx3hCz6UOlYkaYXOkGoXfQRpLJxRCAKqYGubqpECRT6oYWlKOXw8r8u+JJTA5cjsWPkpyECxgcJlKZtBBoC305WeOJJRMLjbUeiR1tKNxYjYcxIyFMD0OItMVEGI2Z/A5KAix7YC+xVE5e8or/WsZ1jjFWiHX+h7I1vLvVBfyV3veD/P4rrbKsf5xWyJwy6e/A8HH4dF4uDJzvFBLaM8Q7yWIpYfhJaucugqPbsEc+wGjx8sE9HI8YfRSrBv3YMSNDkRbG7SczbCS2AIREZygFn0LetuNA6O1t9jF+bnaaiZgrjzNBFfbqTCdjwG5gfJCzvK0rRh9r/Gq3KiHwv6pTxgLw9A1AMWw8SzsAj6Og6YBlnZPnh4OMMOT6tQL7OM31wCKxCwjnpiRVSBWdEMtXnC6OQMvi7jexOmVEhz59fxNIogtvx37uZV+e8NxY+GA4aq+T6dOx1GIlH2LoIhu58jRJrwbtK3G0UVZNzl7tfc6tB2q4e7b/Xo99srn+r/aq0648qA6ot9iohcYEuzXZ7hGHGs6D4I+QT51WAMAizbBPRuSZQx+2kWmFUSg/Muck1mmu4ZjyqvleoX/bfmSsxBP27Iz8eJO+Rv2Qn+ACJhNpeLod5F8qQ2H1bl0cTz2gWR4lUWK5nHk0IHqKvvizRK2PTmgsP5RFI+xrNrB2S83gLPcSbhXPXGnHYQk0jrKcX/lZWCP
*/