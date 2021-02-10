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
Bjbuej7P8HxPF3NhSXaJwy1I9bunLz8IGT4/PP/zh7PDy9dpytRephEKhDAXcm9SmbD1HXubMwPRTmu5otGV4m840Y8lRXQizXzmTN55D3X3NXFc5JfVnQw6Fs17zCWNMD73uIPkfH62w0O1v3csFhgKBq9OkhKhd9QLzSfKo8f9hKrkbU+VD+Hjbt5Mfb4RYVjO3IcKZucR7HtbmV0BxiGhY56WF0kyjVNxkIKCDOBle3C2HvjkxurAkayeZjp7E1WqoNQ0BSfrUYBO2wPGYNK0fHUwGQIUQ1oJYDY/Ofv0PM4T2qck/bSvQFfiOLHUe6znPqU/e7dn5b4NUqZZ4R3se4FzHco60E1HRpxARil23Yb2YvObD82uhv0KTZEzY75Taw8f/fDDz+49/PKHH36ePBxgBPgM+/ChFCdjoF4FXGK7e/Hx6TBHEpAWO+ifYV8CtAed+F6xQS6fbJUrv29DmqGHJrTranoj9x9VYNKx2+RM3aMS5931PAEjZVFH2KPjEUv6sSPBC9rmW2DxlOff9o8pAgLPEqO8x4s+vXWvdoajrQfm6D4yQgH8rRhqiEebNGPQFBc6TJbgHXppY8+xLBbql3EODvZNcdp/FI1+XqbV56daDduDxwUEBxqbrc3qVdejHVY9QL2B
*/