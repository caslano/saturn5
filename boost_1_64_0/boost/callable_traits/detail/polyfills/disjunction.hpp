/*
Copyright Barrett Adair 2015-2017

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_DETAIL_POLYFILLS_DISJUNCTION_HPP
#define BOOST_CLBL_TRTS_DETAIL_POLYFILLS_DISJUNCTION_HPP

#undef BOOST_CLBL_TRTS_DISJUNCTION
#define BOOST_CLBL_TRTS_DISJUNCTION(...) \
    ::boost::callable_traits::detail::disjunction<__VA_ARGS__>

namespace boost { namespace callable_traits { namespace detail {

//polyfill for C++17 std::disjunction
template<typename...>
struct disjunction : std::false_type {};

template<typename T>
struct disjunction<T> : T {};

template<typename T, typename... Ts>
struct disjunction<T, Ts...>
    : std::conditional<T::value != false, T, disjunction<Ts...>>::type {};

}}} // namespace boost::callable_traits::detail

#endif // #ifndef BOOST_CLBL_TRTS_DETAIL_POLYFILLS_DISJUNCTION_HPP

/* disjunction.hpp
SJv3T5j/798bPsW/5zgvql5r/NhxWYtyCVLmBfzeMS+ggdeS36s6Br4Hc1sT3oPr2usChg5Jm5eVw0mgbuc0qF5bM049VeTbdb/SoLMbjH5XdQvcL3WSuP3Waqrj6ZmqH3wOUYx+z7lO3AawJrm22Y+6ROzGYpPCfNm6Zt/T/rHkWaXmrDu/hxQHnT+dE7znpBkLNx8++C3StMzFZJMHGfUC07K4OK1ofsFSuaezcfdYRZqetm6iSc+zRZ4o4/7B305GGv3G5nvCGSKPZxwwwtz7cUbc/1CFeydO3FuR3rv7Wcsbw8w4jczHWK7l5nDgvc6bH1xuNK9rRYc7z1dSf+3dygxugWtPIsXvHIdukZl7ES5u8Vp+1K9zzYfj7M5omCj6vcy3/TNEbiT6uXI+Ldkl9WaQpI39reUd0vNdjL1PaaZ7ug7kGsSzp3xbOd3jkTTNDipfs4LKV5GRi8x3buKCLHEJPCdKv9te4iVucB2cge7W6OB8yMKzax1W3WZWrM6H2VuWvt4GFOjeGJc8UT9NzPnpe8quJydXZmCcZTtW8/xh0Sn2NuH/QRjNIw0r3jFvY9ky/jP7666P8bvfa/b8XlIfmZHBWHHnqjEie8IYdfwOe3vf72zR20WcNrnuZX+f+POJLGvMRY405+w8Lv5rVjjnLJa/RsToXBL9FueJCZ5vk0e2kScadm0J60xyLtPs/fus+BmsMvvoihznDKOLc37VhRKG17FX8TJTJ3qL38/L5iWZvcAXF8wvnGnqxkfiP9GUYdoF2sXKfy/MDCq3U4LKbbaj7XCW0a41y8+uS8FcjnmJtuJAgwplNG/2Oa5lVHU7mzlbP5f5dZTNpaZsomvq9GTkWg39cpFDd4mWPVu3h5ljFSm6iyu0LWNwCxe3uSKPNX67Ba9bM23cT+I+i/QeHH06chvL9uOR9oR67touNYJ15FpnO9Z9LZldeA7u2s43Ffcplu6fbNZ2/RFzGLOqUnkaHj25oZl3dJI8Xqp5bMtLtO0KbKuKgtZvOedJZNbSvXm0HKzBzPJ/b2/oVg5CtlfoB5aFPyKLe3lZWGr2uFZ9Z3n4RORch/6SJWZ/a9V3lomPRZ6pbVpgmTgqbmeZMoHfE5aJd8R9mrNM4CeoTJg8nzE7vyDP5PnfRG9EyDLzmbhnVigTb2Heq0KZaBsbukzEBJYJSeeYgHKhaallg/QKWTacbURBHUt+x7RsvKltxOrYCmWDPaZdy4XqtjPlYrvIT7v1X6rb3ZSJB0V+oML61Uyjm27Kw/0iP+LaRuwQt9u1PNh+OwaXB2f+o3PyNqEB3C16N4t7HZlFwbQ0x1luL4n7lWX+I8yzi+kj3hH3C61EygfO9lxF7NlbxJ6vWKl918Oje8ZVtt3ICWo3cqvcbhyra8nPfw9JsCeUdiPOrWxUbDfMfB3Rv01OwzBtSZzO19Ez1d9sJM8ikhfE2a3sqJ/OEu5Ef/sjcoInyYp0Kz+q30H0J/vzQeR4TzOrdoU2ZazRby36k5DfFDnZk4J2UDkybUOGxHtbYLsSV16uVruUq1h9lvmT6DX2JDN7ZzRG047fYlN2pkj4F7ue5bRU3M5SuTwNe1LO6uj82OOYI7rm2G6XeH6WMnhU1xh/6HevQjvFdewyWMXn6lyRlwS1T6tP0D7VI05CGtamMBx25Y/M+AplkH7atX1S3STJj63uZUt12pp0XypyhCdW54mvT/DLf/Clk0+DrRm+4DYo04TR2rSD54j8UVioPukOcR+k5c/238K0dwtFbirxZj8iZ/kwZfqg6MwJG+UpVTvutLHfrpRRixsIa4C0Ea+K3uVh5WFMtxL1Xp9LwI17asUsysnW8+zF1ds=
*/