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
+xutlsXOepfDWTC6RFb4YDIdz8an42EUMKnYI18iS7tHfuQhrzl3K9dR85RThaMtC1vG9wbru0zmSSjgnYDZj1G205rYT86xXowL4BWJwvS7Y5j/FUXYPIyIbzUHheMK6EVFgxft9Xmb2LTUhjuK+QsgYQ5ZMOfIZZMxRHasWezy0KmDxU7D2W5e1IhLgnkOjoLgRSKXHFzUnxB1rq9NB/soEiEWCAALleBSuwoAEJpYxs2CfD33xj5iunR81kJAumOX2gM69/6yEFkLnbPeMOp3/Np7QINtd/nm2rl71NlZkQ9oIkARP9QUyZiZYvv8+KF0/75S9ZoLJqsSg8qofFMyOqaPH6HBNcBWxbIsOzsqRg9DWYi683779IvIGvuYcbTNDfC0yb7Kc5AvMgoI3CnxxJy2NXk03fngyam+tYPB7fDLI1ZbkLY9pDYNGpp7z2qe5TeeNYVRGdktF3hBWoDXLesiBk9IzKqnW72mNWdJy+7jLfUHLVix+3LheLxYLAgruU0Q06C+VVVlGZv1wNxCYrhqGbQLWSqYF2rM//XW6R0dUK7MS41AC62wI/D7AK9zd7ITtBOrR/z/pkHsQF3wC0SVidj1BuYRsRHHO8LvxM8tCfNPFzvjNtmd/fcWG545PDjaBHLkWINd
*/