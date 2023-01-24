// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_INSERT_TAGGED_HPP
#define BOOST_PARAMETER_AUX_PACK_INSERT_TAGGED_HPP

#include <boost/parameter/aux_/set.hpp>

namespace boost { namespace parameter { namespace aux {

    // Inserts Tagged::key_type into the UserArgs set.
    // Extra indirection to lazily evaluate Tagged::key_type.
    template <typename UsedArgs, typename Tagged>
    struct insert_tagged
      : ::boost::parameter::aux::insert_<UsedArgs,typename Tagged::key_type>
    {
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* insert_tagged.hpp
NivhXNQb2CMITu+TRSgjpBCKiEOho37c3JYfLMv23TRBNFFLagsAqVW3oehRF4HgCSqesSAHIDkw23hU0MnWY3ynMckZk9k79od/AZcxRJxy1IM8PbE5Yc9TrFzI1P5GlugXiQwKexOx2E/27Cb6xQ+jf6K0HWXWX1FaWjzHXn5ybSeyc4yVm0Ro6+1dJ7+PpAuTQNxRfI4wtepRE5OTcM5k+F5k3mU7Y35ak88f4vqsiynTNsU8JRR7LXGhcx5LAgQzSzYMIWzp8+tJUTxyslqlQkndRUYcwQz5iqyBiUZ/UvLY3Yob2FwqeZPMshJrjg7r7I1vUTK6aGIz9SZ3WnIXUQMYSpDZ+zeV9twMzPmnShuE/6nSK48uxteJZN9O5tH/qtIfHH81/FWl+SU8/EV8rf21/8AyojtUmvQwPJnifgdHe7RODyYK1v9JPvMga77I5cAoP8avxz9l0zkqkHovYc9sVCZ7QGbLUH6rSDPtRT0a+WwEffCzXi9y9iYpSEr56IUp5jFHBQlP/OtVV+nLCrdyd+1U2jLqpgacUyS2xBpaly1JhmCSqPr7agmsgIa8Pgc06uLNPevnQ4EoGMIKeJbTwQKJc4HHvYIYBRWFZWPHGMLxPDucdKHiaqSfuJ+8Ya+Z1j3BGjAXGNkzjW6zRFFmo+7z+95w4pM0MCl4Vd9dPIL4gFWfte+jm/lHvzR4fJ80MJ+XZPvh
*/