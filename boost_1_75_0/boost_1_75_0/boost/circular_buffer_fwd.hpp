// Forward declaration of the circular buffer and its adaptor.

// Copyright (c) 2003-2008 Jan Gaspar

// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See www.boost.org/libs/circular_buffer for documentation.

#if !defined(BOOST_CIRCULAR_BUFFER_FWD_HPP)
#define BOOST_CIRCULAR_BUFFER_FWD_HPP

#if defined(_MSC_VER)
    #pragma once
#endif

#include <boost/config.hpp>
#if !defined(BOOST_NO_STD_ALLOCATOR)
    #include <memory>
#else
    #include <vector>
#endif

namespace boost {

#if !defined(BOOST_NO_STD_ALLOCATOR)
    #define BOOST_CB_DEFAULT_ALLOCATOR(T) std::allocator<T>
#else
    #define BOOST_CB_DEFAULT_ALLOCATOR(T) BOOST_DEDUCED_TYPENAME std::vector<T>::allocator_type
#endif

template <class T, class Alloc = BOOST_CB_DEFAULT_ALLOCATOR(T)>
class circular_buffer;

template <class T, class Alloc = BOOST_CB_DEFAULT_ALLOCATOR(T)>
class circular_buffer_space_optimized;

#undef BOOST_CB_DEFAULT_ALLOCATOR

} // namespace boost

#endif // #if !defined(BOOST_CIRCULAR_BUFFER_FWD_HPP)

/* circular_buffer_fwd.hpp
XtuYoaJ9g9nqddcmO6hFuPh+QIeCGSYlgmlAkY9rD7ctN6DbB7NEO2Cx3IR14Tr2+jGdjMBIkjyShn4czY1jWcKHWoOl0th4Mp3Kl1NPeWLMl7SMzAaUXlTN+y54nKIgdfcQXseCZWjOHlZov06wFDm7RJaQojHe42UA/5aRaio3TlMILEZVjB1pFtWzOLPcIFzCYfAaP1eZ4BE4CVoQyXueDQtNq+xudKdcwmjD/dn0nj8sL+y9iuNreWLHSejRtNeedzZWIzjBcmsrnEkNnN3gwfRxc3/2N0B5Usl7pulsmVkAm5gZGnluRvfMT8X0eJ/N9sqK3hkwxOQY/DJGfWYbyvSeX+gmebQyo/Vi18l0GbJI+QW2SfFZ6R7FNGOiwmPkeK/e8ka98mXYJhzgGvAY6AyTJ2EnNlveiHX7lEdMKDJHQmhgIMsTUCJuZdTQhLMa5YZx9dXgiwEd+ssH8+Ig7viMuSX8iMqNwo0aHUY5wDiwE2YygB62HgWy/mop2kCyggohgoIqNMVSmHtXODfr/1CM4oniifqC8oIKh5IVVowKR3Fx48YfdRgPFL/yQbhC2ObcDqJngn4b4fb7hgIk3a47IwbREFKiCteND3j+8WtvlIn8bBH2TlhLXmcj5VR6+C4ubzDhLVQs5FafJZtQJuhWpdocQVOMZRokvajPMm2qQFnEn7OA3ulRnIY/I2u5e1hLJpbDhjIf
*/