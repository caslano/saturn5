// Copyright Kevlin Henney, 2000-2005.
// Copyright Alexander Nasonov, 2006-2010.
// Copyright Antony Polukhin, 2011-2020.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// what:  lexical_cast custom keyword cast
// who:   contributed by Kevlin Henney,
//        enhanced with contributions from Terje Slettebo,
//        with additional fixes and suggestions from Gennaro Prota,
//        Beman Dawes, Dave Abrahams, Daryle Walker, Peter Dimov,
//        Alexander Nasonov, Antony Polukhin, Justin Viiret, Michael Hofmann,
//        Cheng Yang, Matthew Bradbury, David W. Birdsall, Pavel Korzh and other Boosters
// when:  November 2000, March 2003, June 2005, June 2006, March 2011 - 2014

#ifndef BOOST_LEXICAL_CAST_DETAIL_WIDEST_CHAR_HPP
#define BOOST_LEXICAL_CAST_DETAIL_WIDEST_CHAR_HPP

#include <boost/config.hpp>
#ifdef BOOST_HAS_PRAGMA_ONCE
#   pragma once
#endif


#include <boost/type_traits/conditional.hpp>

namespace boost { namespace detail {

    template <typename TargetChar, typename SourceChar>
    struct widest_char {
        typedef BOOST_DEDUCED_TYPENAME boost::conditional<
            (sizeof(TargetChar) > sizeof(SourceChar))
            , TargetChar
            , SourceChar
        >::type type;
    };

}} // namespace boost::detail

#endif // BOOST_LEXICAL_CAST_DETAIL_WIDEST_CHAR_HPP


/* widest_char.hpp
BWTr6qYztC5v+v/pDIa4LxzWFFCHc+Zw3PXM48hhQhA0EIghY27arW0pgTDG/nyq8JAh/YEKurR5iJVW+uBjj85ioXCuFDcEm9u4X0Om4we4HPSu6c880Dw+MrX5VljUU4E2Z2q6wqKuz6B3p9FmuGs+Td38GFnDs0V1jb20cB/nkKuW5+2l+XitNKOkGZtRu/w6Lc+Ip/v4PqQ/RNGxSTq01hKDWidbsPgBQ0rFfRwlE18fQKVmobC0KTPIzBqlKFOGOYf6+QUMaUOgKeoF8NQxRh4O6rgCMrwba0cSps7gVIyP13Y+Gy1kA9Kjh1yQqpK6lP9SbXXgrR4+Loa1UzZdt8mv1BaUAJ5Fku69X1Ha9MigW7GdbsA32rqnKuiWtIK+62IiOYHdg31RTjAGUpq65qnEn+9wMTR7ow+Dm7v3H7TDynGOkaGE2xTj2DCrw0TkFEdu4ugWH3OvM4VEZN4uYnlD8/V29FlQ5EZ8rlSuc6ClPT9/rc/IGJydw4A5ix9X4SkGL2uwUbXXWSDBn2HzpDGe4qOS7p+KNyi3TJshlgE/j7QCA4//t4eV+vCvlGHTa0cBO5dLx1pL7mL1wKy5OsxPSLbsYdvDy27XzOIOg9zPGh6frXLjY4fk2CF4XMIswlYLuxWB22iW
*/