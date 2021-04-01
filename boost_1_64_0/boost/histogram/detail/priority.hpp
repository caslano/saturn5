// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_PRIORITY_HPP
#define BOOST_HISTOGRAM_DETAIL_PRIORITY_HPP

#include <cstdint>

namespace boost {
namespace histogram {
namespace detail {

// priority is used to priorise ambiguous overloads

template <std::size_t N>
struct priority : priority<(N - 1)> {};

template <>
struct priority<0> {};

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* priority.hpp
aJeEYpVit9zlKvbJ2WxVGuHaFT+24pDV+dKYytwatjDyKYP59LiKKsvTOmhAu7/Hg8Sb/wdUGAKSdhNQs5yhX3n3b4nyzZxXhCOpxsH50OomqH5yHQwwht3C7fLUcPTQLPQE5d0p5OSzPFyCZAQemtxfIjTD5Da2lbIwIz019rIkDX7qwuc34f/vLu3FoEICzu6CevDWhj1MQnnqQhHXixoGEprk0ptZFFfLnu8gw3fTR9H65y/01A72/9H0BIAqgWD38FBM1WR6U6/uPyvaHfZ1UJzxmznvQvEHQw3tO5MU52mwLV92hm4Cz+6A/9v9kwJzkrmdMO39J4xsbn/Q8zTvkrgYb+NdgsEj5RguzkaoncEtnuCTGVR1VVkLuFV0vvZ7VQrUjJy6yVJtjhwZybIkNS3cVVVthrqQliFx0alzpJnkE0DGVY+2KxuJVHCp1zlCAuURuMUDmJybOmzQ3gWvFXHqqPBfiSpJqI0A0akCvWljL5swu9nRFsJH2a1hDCWW+ztgxQf1agW6WCSFFSrcp3bUXWwJdjOKuBGjJe45Uhg41kL4UIUmeA==
*/