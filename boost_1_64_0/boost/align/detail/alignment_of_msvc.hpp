/*
Copyright 2014-2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNMENT_OF_MSVC_HPP
#define BOOST_ALIGN_DETAIL_ALIGNMENT_OF_MSVC_HPP

#include <boost/align/detail/min_size.hpp>

namespace boost {
namespace alignment {
namespace detail {

template<class T>
struct offset_value {
    T first;
    char value;
    T second;
};

template<class T>
struct alignment_of
    : min_size<sizeof(T), sizeof(offset_value<T>) - (sizeof(T) << 1)> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* alignment_of_msvc.hpp
fCOACbbKdFTpO19zQt4GxaKENmS5DsZ5rcBx9IO3IdcWndt7gjhILicuUpuv27Pp6DFyz5w92zVUgqPD3/rdViSiKx0tvI5gvuraT9OITgTl0K9EiNq2nkx5JTsK2EiDkw9eCtCYGETzDRR4hIq2ye7th60j11xoxIlGCm7t6z6rNjb/ayE+4dEVLUrkhugIXU2iussZZOaJMXbKVpVwshPJk5o7dJKhVWdgeTlLKosMvvKF8trXbEVugNKlkiVRbqh59oeUvm1dGQV86JDZEJi6u8NYjjgBQg3UHISEWn7n0s6TCai4iQD/wWQAAWwEMOkksp7GOwp9HH/EJovCc+5cFZMlAzR6+/pmszST+7gVptQdJEYZvJpS4nejYaPmXNqDCBcIAsUblmSLouy+cMsiDW3wDsETvmbgB8pwXQJUjXa4+ah3a08rCEk/Tjn13Ji94oLlaVirTQt6Dlfr63/8e9ejaFd7vnkJwVj2n8YGy+oyOKftHpF6B5YtzD7X80Iedza3T9YZi18no0bgQy8eiJbQsRb9FTVwfCfoNpdzlFpIOfsHJ0bBhQ==
*/