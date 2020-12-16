/*!
@file
Defines `boost::hana::default_` and `boost::hana::is_default`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CORE_DEFAULT_HPP
#define BOOST_HANA_CORE_DEFAULT_HPP

#include <boost/hana/fwd/core/default.hpp>

#include <boost/hana/config.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename Method, typename>
    struct is_default : std::false_type { };

    template <typename Method>
    struct is_default<Method, decltype((void)
        static_cast<default_>(*(Method*)0)
    )>
        : std::true_type
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CORE_DEFAULT_HPP

/* default.hpp
+eYLghUhixsfG6MsHOZA9iltdZT0AWYgCx79RmYwFuZMVtnm6HrpA8yOzDTmheSXAnMh+2Haaa3MmWafPv6+p8zpJfpCtq1z2yvK/GBeZOebnegrMwiz4efM31meMxRmT1bgzHZLmU8Y59Bkf/JkZTEwR7JDIQfkjIyHeZD1nPBbzqxkysE76343MtKVpcNKsC38N0CZwyv5fbBsS/45/KnUBWZPcdUflIlQVlKLK1ukU7rUDJZX4mBf7ifLPsDMKW7C5b87yD7AvChuWJd7l5T11+LOmNz5KnMGM1Dc6CLHVsuuwPKTfdjx1EvmDFaObP2dDIOy69r9Oge8l1lKg3Gtn55p2V3mDOZEtq/8nTnKDK8x12QZo+xjpGYwvma7ObbrpC6wPGTnLnSR+wXDuNbRE3LIN3Tof+m477CqriwK4GAFBHk0QYoCgqCCYEclih0VFZUoduzYUSxoLNixzWBs2BLsZGzYsQaNhSQo2LFjx44d+yydOdv1znwz/8yX/L5z7917r33fg8TAHMj8K/fcLRmElSNLvf+xQNlaWKH//vvl3l+/8z0r5K8sBaay+9Uu7P9R+pIOK0V2r1XYMtlNmB1Z8MTil5Tlw2zJrhyfO1uZ2VPj+5n1OdJMmTvMQDa9lX9d6SfMiiz0feUmkkGYJVk1m4y5ysJh3mROpnWKSc5gnmS5Db0HSZZgHmSze/g8UpYBK01WLizhqOymZlfch7+U2p8Z29uOgSWU+cK4Z2FBRZykPs2i2jTJlbzAXMkuD3zqJ/XBHMjOrn7XU1niM63X/u/spXaYNdmQya8ku6kwc7LqPfrL/dI1y+pzUGrPhvH84m3jfpH902xeKZPxkiVYCbLDQwI8/mtA4+e8Ujt6iOwmjHNWau8WqcEXxnk5l58zSVkQzIysRd5RsRDNto0qc0B2WrP8xkXlfuGaVXP0/YfMD8Y92+cTVV/2XauvapTdApktrCTZ3iU/nlSWALMnu/h2UqDMFsZzH3zNykpmC+Odblv6hzTJvNbP10NGz5X5wRzJxk7/65qyAu2arXr2D5QZPTe+5vkPL5/JjGC8Ky9HVJwtvYZxrtt4tJZ3ZJRmVx5WOSg902xZ2JxOsg8wfs4Ztg6yYykwzkto4y8blaXBeEa5vToUkZ7BeEbXmk9tpyxHO5e832qnsjwYz+/pjtZ3JPMvjN8Fhq65t5Q5wXgOn9q+uqosEMZzv9BizzLJNcyaZ/vLxI+SXe1+ZYa+aiX51O73y7gfeyiLhzlz5j3+NUAyCONeB0buCZJ+wjzIaqzY8kpyBnMly6hZfq305aXxZ1X8rCRH6ctLbUbtaw+SnMF4Rjvt3LKUBWlm8eR5pmQQxlmac7aDrWQQxvX5b+k6WTKoXbN1H49Y2VsYz/3gk2PS62Ttfk1NN/hJz2A8ozsrix9Tlq1dc1PSxDjJmWbdqjwtIv18ZfzeHRyR11n2FsZ722Cs7Y/ST5g979HzmKmSMxj3Zc/G4puURcIseQ4jyjpLzrRrxpxPdJCcwTiD3pkbyipLghnIHo3dMEx2GmbNcygzMF/6qdnj7ssuyk7DrMhKnzwm98vRrP7U2yOl15q1eF47UlkBzIIsu+HROcrMXhvXUGvm7xck1zCew5fX9fco83st3+e/2fHidS2VBcI4S5MHTXeSXMPMyZbciJklM4Lxc/ZLnHdKZgTjnr38vYq/ZB7Gc+/eOkrulwgrQ9a81Ch5J6fCLHnuB6J6K0uH8R4NCj8bLJnX+vLi9/ClMgeYD9ms9z9vkVy/Mc5SraY9f5Jcw/iamVsiv38v0CysZI1fpGcwnnusXeFD0jPNTr/NdZOewXinJ3Q/sl16plmtY7uzJNc=
*/