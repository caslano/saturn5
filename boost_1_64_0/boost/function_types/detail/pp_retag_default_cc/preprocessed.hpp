
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

// no include guards, this file is guarded externally

// this file has been generated from the master.hpp file in the same directory
namespace boost { namespace function_types {
namespace detail
{
template<class Tag, class RefTag> struct selector_bits
{
BOOST_STATIC_CONSTANT(bits_t, value = (
(::boost::function_types::detail::bits<Tag> ::value & 0x00008000) 
| (::boost::function_types::detail::bits<RefTag> ::value & 802)
));
};
template<bits_t SelectorBits> struct default_cc_tag; 
template<class Tag, class RefTag> struct retag_default_cc
: detail::compound_tag
< Tag, detail::default_cc_tag< 
::boost::function_types::detail::selector_bits<Tag,RefTag> ::value > >
{ };
template<bits_t SelectorBits> struct default_cc_tag
{
typedef null_tag::bits bits;
typedef null_tag::mask mask;
};
class test_class;
typedef constant<0x00ff8000> cc_mask_constant;
template< > struct default_cc_tag<33282> 
{
typedef void ( *tester)();
typedef mpl::bitand_<components<tester> ::bits,cc_mask_constant> bits;
typedef cc_mask_constant mask;
};
template< > struct default_cc_tag<33026> 
{
typedef void ( *tester)( ... );
typedef mpl::bitand_<components<tester> ::bits,cc_mask_constant> bits;
typedef cc_mask_constant mask;
};
template< > struct default_cc_tag<33312> 
{
typedef void (test_class:: *tester)();
typedef mpl::bitand_<components<tester> ::bits,cc_mask_constant> bits;
typedef cc_mask_constant mask;
};
template< > struct default_cc_tag<33056> 
{
typedef void (test_class:: *tester)( ... );
typedef mpl::bitand_<components<tester> ::bits,cc_mask_constant> bits;
typedef cc_mask_constant mask;
};
} } } 

/* preprocessed.hpp
+h29O9YTHb4hmVhaHkbn1d78Yz0XG7hBTAxEvJLFJX3lHETdq43LthnqEQgZwdMZssvjAiUguN2Etw5qGC20j3SFbh0t1rRYyxq3Un96j5KQ/q6ORNXVndjVN+DEp90bgImBHuMM6pfekb05cwb7nginJhZnGc6Uy1q1HyuLnv3dKlilfbUHvjlzhumanpoo0C7umez/qu8RtLXfSO8XUc+oKOwqLnHeZuk5v16cB8H6iTXrgedZ+rzES+8mzsd1L3/e49GwK68nwb/aIs8zAXOb5Pk4pBcIXp6f3BFfPj1HEO9hEd88/L+xT9t7Efyl7hh0nK65EN0JoXtxiO4kdHwOR16nRH6Ox1e3v5zE+ZT6epj++TtddUGftnNs8UJf+c31hJ6nQbjVld+zQ/K7EeE/hXNZzwnRGdBx+3g+/J8udF3Q/eVqrTsSYq8Xur1RrXvuKnXPW6VOXq0J/3OCjcr9T9TXKOI7jvpqEvWSB99iivNRO0P6g7C7TvAzolwjEZ2eRdiTlwwn7R2GP48vbK91l7Qnw62uvf+/XuqpjZ2eMG3MAdR3qbM8+a77jdEXR8ecOYH//IrzKxQe9wzNQjN8/Ej6q2fmcNv0Xg3o/PF0x3alPOHU6iE9GXHD5eAj7HMO2A2JazcV25kg29pP/zRWEJ+S6YmNDPcqLnWG981MpUw33TO/32YqFOws7tPqdx7PJj56W+9ZpZOq4azSOUXLvrOJr1Cr+o/Y7EnsisVvGFNf8x3TdXVG9orl9Fmlo9xlnlW+bWqRZxMfZ1u2y3KaduXK22iajYMYklfrcK973BxzrAsdvaZE1aU1Te+hDegP+EpeK+WbxgQEXVZHSe9aUadlY1gfRwL0Nv22qjpXlFnq7/hKfa3olIhnNJM8SgzFJXicOIJp9ndTCLeKvlWVpRs+o955rWwb/P1LRfp/F8Q5hSIihmVslfA+jo1Ni/qOhxMMex3Yh3GOsji7QAb9Ul39R6KCeN2QjHLJeZoPBXTTBlW5jh77ND4PKgkjPW5r43C7v6kCGS7mnUoD5fN3fg5L0cHhdOH7N7zkRhKy4vxSpKE3w9TYJQ1CB8WE2mzUEsFTHRreCpDnf3Dux/1lyqD9G9gq0C6haE9o566bii6w3ao8+NxVWufhR3vHstgkl7zVnuWWGcTrwUF1A9wGmdfjtpMWenFOkD/1EyvYn37T2etPJw3VvkvwuIRetqrrYO9Fq5p/HexTujNff67n8A/E95OuAi/XHTdqXp7Xb2YdePl9qtbr/PPRxSTswG0gnLy6blz++1sLN23ypefxIr07HqTD991P87cAt3jd8t8P6FXxrqL86uedGBHfriR4uU5C+cryaxHp/fEWzT9R5GcY4W+63OUVNnP1gP8F+LUiX/vAv2KXvzzKQ9r/lrL8Odwqy0PWj8wPx3cwtcL3Hc8yvtZyy7LfJ+l9oFj/iPZ74iDvd/jTeyq1/PcdDyG9txD8Ee4vpn+9NTe8/HpqHuFuQ3+3X4W9UyvYW0A4+X3L0fzlvv2CO8H/aev9uoPYd+J+dH6IbhHxrBvSugtCdCeh67uD1jWH6E5D9+utWndhiK4Z9WrcoHUXhehaoGvpRvlx3NzOR/z1uANueTWvcr+gug3f+8a4XG//e8X5R4xHLfVwq2v/Zzq+yPb/5P/Q+PIP9q4ELqpqjQ+LioiKW2ouXRcUFXFYVDQ1VgVFQBbFsmCYGWRyYMaZQeFlhWvu4tLLXla4VFZWuFRWZrjviktlZYVLPSsrXCorq/c/936HmTnMKPj233s36ZtzvrN/3/c/yz3n3Oqxru1DTdRM8dw9pSPr1v9l/p3920qh/RYJ8l7P+dz+hPpvvUU=
*/