/*
Copyright 2014-2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNMENT_OF_HPP
#define BOOST_ALIGN_DETAIL_ALIGNMENT_OF_HPP

#include <boost/align/detail/min_size.hpp>

namespace boost {
namespace alignment {
namespace detail {

template<class T>
struct offset_value {
    char value;
    T object;
};

template<class T>
struct alignment_of
    : min_size<sizeof(T), sizeof(offset_value<T>) - sizeof(T)> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* alignment_of.hpp
hzR1a2NVExqc285t8TQbWx0VXga6/6JloVXO2ug9KYLHYgMh7vVr8GQWjyhFVK3Zhr1Ny1F8BxgfsjnSsZJziODxbBiAqX/pelh38W+Wluix0RXjKcSmvwbbtuqyigNdjCC+0oQj7c+St5pCUlYaGYEgH7nDLKLPHheeCChUEMh2kYYo7f5QwB4xjMF6ew/tKQYLyyDb4ABDRR+WaqbwcFuyDoLjFHEiXCwrB2DJYAbtLWaXDYyXsKwmIUfHqqJjD5Ra9pAaskqFDCcb+M3dQljNFY9NFXPFMAaneFojIFdOyy61AGxOwxsUBc/k7J3d/czmRH1+d8saFVZcG9UqBCf8LDEQYiFLl79ZoFODYzIRCNsbqkhJtMoyl/sH9RBKvS1le9wtlttcjFVTKdue703dlfJz1K6QEid48J+Pr+SlsSn7lMfrbihMpSuGH2tRoZuhXOohFLkhbMoE3S1SQSfrkDKPrAivA4KFkWL2vEFwubg5B9v5d8sa+6L+J9o7qbRH453Vk2XEIyqgIipMhSTKn1CLXZ/pF7q3ai8Q+kRZdD3t/7Zt1JbGm5tkF/19kxD4xfjxUFgzzXt2qxsznFkjyxSql28vRtm7xFOea2lLXUmonx/XYWFHuVnnsGxYFHOtMrZZxa1hCH/c
*/