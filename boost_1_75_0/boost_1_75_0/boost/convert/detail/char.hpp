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
X3x8iu5ePgdo+1BZAGHzozhvsmrFsy3SVwB9nLPGNTpcI1kJvtrX5z+mv/z0E70D+eL+BG7N9CKbU/sO16S/vMT2MFy79Dlbu75y7iP65dmP2Lo6rqFeOPkO1UWF0UycH4/wfDR94A/n5DMD7ehLDcvoLz/fY+uPuJZ/48uL9O4PN9k6DP5+4MOHv9MHv91n80v3Id5vP8PfX36hd/91m60lXobyXzp9kv5w7Wv6/qv7qTyQ0Fzw4dc8ov7ze3uwcu9cPIv+9uvPUAZur8NP//qB/vvhQ/rdV1fo0b1b6IaZ5XRe/gRakzKMVk8YTKuTBtPZ2TF0tUlF39y5ka0N3rl5A9rgNFs7xvWPaZG9aBbY+y21f36YG80JcaClwwLZuu51Vq8XWBmxTpfrcoE/X5oCsogB+cQ5e1wXwYBruwznS2jZ8BD63st7mBywPRCfn6PFg/zZ2tWj6CN/1RMG0Z9AtnAtGde+X9uyhq1DJfsQtm6F689FA7j1I5xrxPUNeXAbhisaAH2mrxdN7YjrVvb085PvUpyk37e6jqYBX/kggy21P65vTO7uxOb6vr7A3bd+4qU9NNmXW5PORf6CuPW7VCwn8IP9IxvoTk8exubnpkD74bwmzntiPSD9T997i+ZAnEmQVvEY+S/o48nWcebkJTD6OxY/QRPcCSunbmwP+mRWFJ2Xl0g3PW2gbzzfQD/74Di9g79TDM+h
*/