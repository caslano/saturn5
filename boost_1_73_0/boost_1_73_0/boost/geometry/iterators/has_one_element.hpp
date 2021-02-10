// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_HAS_ONE_ELEMENT_HPP
#define BOOST_GEOMETRY_ITERATORS_HAS_ONE_ELEMENT_HPP


namespace boost { namespace geometry
{


// free function to test if an iterator range has a single element
template <typename Iterator>
inline bool has_one_element(Iterator first, Iterator beyond)
{
    return first != beyond && ++first == beyond;
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ITERATORS_HAS_ONE_ELEMENT_HPP

/* has_one_element.hpp
UiEKSSGiNZQIkJOjI0Ia6Af5FwqgjT7HH4yCrgr9EYKJz/DPSOgCgIoy9b2iyFBYtH5MJJgTVwH8pLQxht590q6ZltCIjxNyaQRaPhsvY1tVM4HmoVZFp3fSuypeFRRYxWPENfvA7YPk2lgHh3yQ6I8sLZK/ZPyPMrS1tXjspRa2ZtZNvTnej/78oo6miz5r2v1V2JpyevCgWMEDGmtuQqPg7Fly3nIKio3VKOkbQ1DjaH5jHDiEQmG/LWN0l8pEkd8WmcVuvl44jJiN7YKB2ImJVDMnPM/10k2uPR5Cs+NGjoPFbcBJ95ku01yPm5CN8k+Ba2vVrIHJYC2snMKEWDdHEFSvaMKiifgm147hWCSoQna9JHzx2lE3R07P+yfDs/Z7ZNbrX+FjklaJhvIKgklQX1kD0IUR1XOY7On1yz/A1lyiMGBKV3hX6XHo24HrSyJdTg8q5bMytlgqYXxUJQMpI8hWDoJkhWAao9lsn9rFDzV6ljS2fqw2PiHd5xvPceippurztDmTQYPzihI0TMM5jjLEy3U+3sbkDiZw4k+sdkNIiVKBU3ZZwO8xXceUKPnhloXnwliRZ76LoQLexggd5ynhmkGnE79M3CSVDOZ4VXisbmDEH1xfIM7cDimJxHsfdHMDEKSf8vW6
*/