// Copyright (c) 2009-2016 Vladimir Batov.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#ifndef BOOST_CONVERT_DETAIL_IS_CHAR_HPP
#define BOOST_CONVERT_DETAIL_IS_CHAR_HPP

#include <boost/convert/detail/config.hpp>
#include <type_traits>
#include <cctype>
#include <cwctype>

namespace boost { namespace cnv
{
    using  char_type = char;
    using uchar_type = unsigned char;
    using wchar_type = wchar_t;

    namespace detail
    {
        template<typename> struct is_char             : std::false_type {};
        template<>         struct is_char< char_type> : std:: true_type {};
        template<>         struct is_char<wchar_type> : std:: true_type {};
    }
    template <typename T> struct is_char : detail::is_char<typename boost::remove_const<T>::type> {};

    template<typename char_type> inline bool      is_space(char_type);
    template<typename char_type> inline char_type to_upper(char_type);

    template<> inline bool       is_space ( char_type c) { return bool(std::isspace(static_cast<uchar_type>(c))); }
    template<> inline bool       is_space (uchar_type c) { return bool(std::isspace(c)); }
    template<> inline bool       is_space (wchar_type c) { return bool(std::iswspace(c)); }
    template<> inline  char_type to_upper ( char_type c) { return std::toupper(static_cast<uchar_type>(c)); }
    template<> inline uchar_type to_upper (uchar_type c) { return std::toupper(c); }
    template<> inline wchar_type to_upper (wchar_type c) { return std::towupper(c); }
}}

#endif // BOOST_CONVERT_DETAIL_IS_CHAR_HPP


/* char.hpp
hXOO5T1Pa7CRszsDZjVdix79CT5wtnM3sbf34S1VwY3l5Lv2I7MKfJ77NXJi4NipRehnHTj5vfCsb2mPvb/7PX0y1c8n9yG2zyFXWp2YeRv62TQGmwvA/tj33vO0AyPa0XdGFu8jZjJHCD6FHMZH6eQaqpBvehD9Go8OIpeN3/I7tp8ILhYTt685CC/5Gj0KgINni+9b5p4Ajns4TnyvArZWSryOHi6dhb6Tj2qB/G2N8Cur/LEl7kyI0aZgF13Rh2fyyLG3QrbBrAX/1x1ZzTtG/A8X/4HYfPkRYpiu+K6n8dXk5Bzgd7VK4Ar8II3fU4lZDqQjl3jWto6YE2xdDGZPygNfwdBq5J9Wgm12OPIH4EFj4uAPxxInETNMxiZm1YAHgznjHWDrJuJlcD1/Dn6YfETkVvIqnZEvPL4He8vxh68PAuPB0La7wB9imVal4B5+8dn2YE8wvtuPGIc1DdgHbypin+JeysV58XMCHRyGKPr2BxvA/2k5YBnyeCER/vMNMTv+/fVvib3xleXAnSe/Qna78Gt/sZeJIlfGGV1k3gbItj7+B7t/9VH2tR7/jW5nB6DH+MkB6G//f2KrzdBdctsZR8APxjh9nlzHBHTbTax/gjGZ9+gj2HsTclgx6Etd7LQ3eQJwqeFtYCLxzcQoMBo/c+gCseIncNzBXPfP4szE984+jl+bgz2Sc//qZ3TkU3gQOngA3X/3G7jHUfSiB5gzF+6A31gINnb6HBmBfXuT0fk92PGd7AE5vg62/xoOL/iZftWwf+zQAeZPoe3c1XAq4qaYuzk79rERTNwzXryfJFYjD9jnZXjv7/CMFM7qJ2JQ7Gh7e7AeOWfP5IyWcu7ELvs+UO+i5yYQ0wYS8yFH2yh8KXJaBqbfzpl9zp6exx/XR98PkfOu3xcfcx85CjC9cSR87mcwBJy6vg6/T14jbxq+jnuJkZzHhF7kw/zAnafQe7j4yyfBtPsCwDNsxg4O4mvnpoEdcJ6ag9HXSmA3ZSe6kXM+hS4kEiNF4svB4eTNYHZF1sy+16fCN+DYx8sTl7wLJuDn1qUQE08OQJnARGyv1xJ8fF/OycVYrLNxR+JlsHyTPzb8CjZNfByzHb2E0y3CBx/Jgw/BL54D6y+M5y6WeL3yEjg83Pvt+ficAOoaE6suhGMjT+dpdOwe9BN/EAUvOFkBPwm3jePcHh2LLuzEd3DuY4gfj2YQyxBDP7mc+Ji72A6s5zC+N6QOdg4PjkDPfkRfm1WHCz4Ox8vBb7jgPpx1hhu/gzyL9/E26zScg/N78RhcvQY+B391sh6cjnxcR+KNQuLO2QuI4+qQp62ALnbm3IL9yCWTUwtCL9rhK4fjizLBpW3wKXDDXQtcWU0O5SQxBHm30lZgdiiyGQ2HJrYZVg88/Bb7n4Cto/8HsKWD3HPfTSyAi7OdInZ4Bz807x1y0fiAPgHEd0/i32/DxvArm0RuGLl9QX5udjMw4U94dC/8O2t+EMwby73AYrhUYB57Qg4Td2ALgfiGruhjPlgN189bCf8ej+71AY/J6U/ZznmRX918AdsLA3c3gAvd4CLkm54hPhef0Xl/LLq0jXGd5J3J80+GI8cRl0ZMBKuxxa+TkPkLYDjreYt4ZAC++vhz2D58aucw7gw593DO7khd8nW58An8+xu/ItPX8PfgcpE//hB7sZPHGryD3Gsa2D+Q+VuRZziMfYzAhxADB7OmVLjPh6Hsi7u1Obx/SkO3Cw+jH+j1p3/ZaI+f/ZN4ibh1HLgaDJf/qiL6tgHs/REfHoDe4tcf2BOArwEfRmJD+8GfmvCjpvCU+sjoCHKMASe5ayk5zJni94r5u++f2Aq4sQ1+uL0=
*/