//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//
// This is a derivative work based on Zlib, copyright below:
/*
    Copyright (C) 1995-2013 Jean-loup Gailly and Mark Adler

    This software is provided 'as-is', without any express or implied
    warranty.  In no event will the authors be held liable for any damages
    arising from the use of this software.

    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it
    freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
       claim that you wrote the original software. If you use this software
       in a product, an acknowledgment in the product documentation would be
       appreciated but is not required.
    2. Altered source versions must be plainly marked as such, and must not be
       misrepresented as being the original software.
    3. This notice may not be removed or altered from any source distribution.

    Jean-loup Gailly        Mark Adler
    jloup@gzip.org          madler@alumni.caltech.edu

    The data format used by the zlib library is described by RFCs (Request for
    Comments) 1950 to 1952 in the files http://tools.ietf.org/html/rfc1950
    (zlib format), rfc1951 (deflate format) and rfc1952 (gzip format).
*/

#ifndef BOOST_BEAST_ZLIB_DETAIL_RANGES_HPP
#define BOOST_BEAST_ZLIB_DETAIL_RANGES_HPP

#include <cstdint>
#include <type_traits>

namespace boost {
namespace beast {
namespace zlib {
namespace detail {

struct ranges
{
    template<bool isConst>
    struct range
    {
        using iter_t =
            typename std::conditional<isConst,
                std::uint8_t const*,
                std::uint8_t*>::type;

        iter_t first;
        iter_t last;
        iter_t next;

        // total bytes in range
        std::size_t
        size() const
        {
            return last - first;
        }

        // bytes consumed
        std::size_t
        used() const
        {
            return next - first;
        }

        // bytes remaining
        std::size_t
        avail() const
        {
            return last - next;
        }
    };

    range<true> in;
    range<false> out;
};

// Clamp u to v where u and v are different types
template<class U, class V>
U clamp(U u, V v)
{
    if(u > v)
        u = static_cast<U>(v);
    return u;
}

} // detail
} // zlib
} // beast
} // boost

#endif

/* ranges.hpp
H1mDbER2I58hCQ9xTh5SglQgW5DXkNhtMYF0JB9Zg2xAHkU+QJo+HBMYiBQi65DNyDtIzCPkK5KDnI6sR7YgLyD7kAbbYwJdkGxkJbIJeROJfhR3SA5SjlyGbEZ2IzGP8SykFLkM2Yq8jBxAOjxec7ZfzVVz1Vw1V81Vc/0/XT/J+X+nBFdSBk8APLrz/5IDDRqXB/ckfyuSKTgKQx7+sz2YFmsanc/R2cKPtCj26JlXwI64bp1AwJwj+HJiwM6XXa8z9dpoLKgFHNGZ5yRovmz2qDxnWifeuPY5W7Ks3O6T5ui3tHvirTDm6IgTtIYnzs6Rxp323Nbcf7ldRz9TB9Zpd7R7p6UmmjUiZt4yvwFde0OWLptjQqP1ttaP9YGR9ECfgVTtUVc0F02jN9GlN4Seo1O5G9TLJr6cH5Y9IlB1jsd3Rm8KY7MN3PO0cR8yT9u4T6ptRqGK5sr9eHQ7mrAP53dtnFl3uQC7c43bb5UWcqO0cOYddzPuJpDHDc0zUrDT3jV2bn67xoc/70vztrU3nMkr7RnpzMe2+aD523ZNpdJW87ft3nuV6cg9E2/SjHtKM+klmWcRJ/mZYp+leGru9icJmqugM4zamDjjZ9j67vRozavR3OiuyBh0dht97eOnPezMbG7lx6jO4XvXyQ0+2T1zqjEnGv/sPnbuPd1jtMk8YbNHG41HN7aNR/jYjCOkIvmGVe5Vhsca+9K5p9i9qq39Ea+7doXf7q051tzD37A9Awt17uN0Z6wMmYJukl+cgst//OMid9ON/YTKuBgXTlywt/u+nlhpPw+FpXih90CoHzlKD7YkM/YTXfbx2E+stDfb0JrJ2q50G230Gpt6Rb6767X8iDB+5Fo/mNRevJzFbFV+zHD5keLyIyXMj0lVflChSord59OdEtRT/c5w+ZFR5cdR5e0Ec8+ks6mHLQKYzT2lrdwnwRxzvzI9W3EvmBYTzb3QNGylupBr7ELTBjsTj0nWzsY5dA1BzMH1ZRpuKvzKFvWEXXB9y1aF0jGuqmzJhZPW6BxFXYkPSU/5HRanNTqbr6M864DMQn+DX5yWFs9f7F9f5K6jsZ+uMoQLxcfamzJ2UpV9HolORjl1xuqZtJnh0uOP6o3V+VFp45S16eZeZRhbqaydZO6Fhite5W2G7BSWkLS8op7GqSth1pnko7/bLy3ZLqd43gq/tJS7liYNZlemgVw45cPqmPQ82a1jQuekp9X7UWnllKPZ5p4Ng02vk+19+9yQ72CpzvI7W2uagm7n4GafV7qw2YC+LbQFbZrY9kVkW9wwIzbRrmty/Imz6WjX1qgt1My4mWG/nR9XY29iwuD57cz2OG+vMPguaOsRp6VH/u007rUmL8/Efy4ubH5jX73zXLzKfJ6Jk/E39MzF4wLmctoUnZF5wXeBZ5wO/+007vDN2Ju4GAeKi7U35XuMsdfr3ZbbUD/GGx3zqtc7INSPScbevvY9v5Po22/cVKtvPwUe38VQN7OsG/uJ8PoO4ubov4OjTD6ZNLPfwTHmnk0n+x0cb+5Xpg26Jt6TzD2bHvYbONXet/G238BZ1s7GL6SMDGx0cLlfQNj3epaRw38DjTt8i7NlRA7sOw6doyjz8SFpKb/D4rQ29uDv+sLg+8kzTof/BuLOtn/nmDgZB4qPtTflqUj29lNjy77VM2mzsEqPP7b8o/Pj2wdOOSOM3DNhtO/0InvPhst+AxfKTmEJXYNu/pr5sPastBKeGUjySsvDfwMr3dU1abDIpIEc2PJhdUx6lrl0TOhselq9H5VWTjlaZOJuw2DTq8zet88NWdf7beODz45bhP+xIelyIv0ikyYx5/CwYXSvwS2M8/Y7ye0=
*/