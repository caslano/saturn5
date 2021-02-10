/*
Copyright 2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGN_UP_HPP
#define BOOST_ALIGN_DETAIL_ALIGN_UP_HPP

#include <boost/align/detail/is_alignment.hpp>
#include <boost/assert.hpp>

namespace boost {
namespace alignment {

inline void*
align_up(void* ptr, std::size_t alignment) BOOST_NOEXCEPT
{
    BOOST_ASSERT(detail::is_alignment(alignment));
    return reinterpret_cast<void*>(~(alignment - 1) &
        (reinterpret_cast<std::size_t>(ptr) + alignment - 1));
}

} /* alignment */
} /* boost */

#endif

/* align_up.hpp
WVq7O5+xSwEVMyoe3thHu/5p+xsc051c8TJWi97UfXHmILEPxzHfa7ii5eICCdk4PMvFNOR+KLz66HDHZchO/sBAHTsVnbg6m/rlMEoMtU3CWc2/lnWpZjHBLdEy8WpBUMuBb+mqd6kYGWjt8maQYXO7pKF50STWbAqwpRihoqEWSrPo21iXuduMptVkQBebQ0EWTwYTwXQrs7qQpkFZMwNOqAUtzZdjTvoy5mZt3CWeCx3DXpiedYO4fdYsHqUGKwaLV7O889q7WvRSBtkm6VyIjp53PYRvtylJG2cyTO/WS6tgoHslKtn+2uAytxYw1MsO94TmomsC+aMG9wPBXuzFgomHJ4d2b4OPAtvDC+wpCuKdxmcjPppccEOFJgFlG/mY9yYitozFqgIMbaq9WHGt/cs9JZfXnSEwvSZ1KBZ5mk/aCHU0GEyqXm6SCcL+oFfrv23ncxmCXgj5HQOMNXEuVoXXUlWVz8lgdpSEdwo/8KZd2rmEFWm37leYuR/ibixB87NLSyUdnqfeLtzZG4YCX12RHyTZh1+Mnj0ZPXIotasiaSaDDqkzSJLzGnfQqyd7XVevqwZJxjqRW3F1ExyTXmt59vzpcFIqI/kg6/jQWZ3GV1oc0PJF9fVWu5KU1mIr1sU22b5lHK4K
*/