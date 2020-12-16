/*!
@file
Documents the `BOOST_HANA_DEFINE_STRUCT` macro.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_DEFINE_STRUCT_HPP
#define BOOST_HANA_FWD_DEFINE_STRUCT_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    // Note:
    // The weird definition as a variable seems to exploit a glitch in Doxygen
    // which makes the macro appear in the related objects of Struct (as we
    // want it to).

    //! Defines members of a structure, while at the same time
    //! modeling `Struct`.
    //! @ingroup group-Struct
    //!
    //! Using this macro in the body of a user-defined type will define the
    //! given members inside that type, and will also provide a model of the
    //! `Struct` concept for that user-defined type. This macro is often the
    //! easiest way to define a model of the `Struct` concept.
    //!
    //! @note
    //! This macro only works if the tag of the user-defined type `T` is `T`
    //! itself. This is the case unless you specifically asked for something
    //! different; see `tag_of`'s documentation.
    //!
    //!
    //! Example
    //! -------
    //! @include example/define_struct.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    auto BOOST_HANA_DEFINE_STRUCT(...) = ;
    #define BOOST_HANA_DEFINE_STRUCT(Name, ...) see documentation
#else
    // defined in <boost/hana/define_struct.hpp>
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_DEFINE_STRUCT_HPP

/* define_struct.hpp
N8X6f8tAC97y5RcdRFbpes4M33zpVZQNEnGdaO+UhdxertGjjLuaB+ibi8zYPiU4xhI4V55AG66zPLDgg0wXuxtQGwMBfRFZBBccsl+0HdOKzI7OZPjS5RYQWZ9Tg2+FgO+Jn2uXi3eD+pK9Ga9/lUJYQ/bgIB200PHahD4kOk/kRPPiZyGVPREd0en6QdmNkKHQ2YGDmNnOo9fsUbxeMQH8g0iAIk6S+KYxjnmAYTZlRKXuFNlnoXjlLyUU0q2b1RoIqLgk1GOkiXfQL78oe8LqSgI7NnmyZfl7BmI2t5hCky0ovMv+WX+1yp/muhqFFpsUFy5W5bnaiJgOC1Wi+6AH0hxPwcWxibK+cJVqcB48ZLSvrEFUdeXQaGog6fxNlqF8ZHSBGpYWFzYDYfWXDI26GqsPz6i7xNnXfmOjaxctj3Sut97yg8I8mP+MqHIU/gi/86qshcWVPQtLl6WUFOys3BsxyVsJzam04CGTfWUaimOFiPy2P8O1q/oaQx6ke5kBW/U1xrxAcnimKdhqytnc1mS01+aRjLOJ6O5NORtkZedXYcuZVDFOl5zsWyJlhWEVMexKzxSvcu5o7WTW1cQOovVZrmjt/qoxrrZ5mr9D+xqLC17za9UN9ZLLSPFTSjsk83bzzvrUxvcsqZvr4InHVPnqhGCzqeCryibYBvadQWddUKLTXlsr+HlSSeRzVysLsDjTmarWu0kO+QvARKJu3zw6/w8m2nd1pJCnK0dIYTxx3G8Qh2zZNH1/q0f/Rou+CtG0/Rbh8AjGAvIsjR/PoI1lHi33FaGz4USrWPBfHONbKMr6pVZWDoGxKPL0tv+0T+sjVXHrk+bvHcO2Bww6sToHx1poPhCyOzz+k1SvceXKa8WqGyagSIOBJN6yGdP1FHYIRwme0hLALJp619w+aybo4vRmcpRW9amqL8S8dzVE7uz1d/nlg/8w/7npcJK8oUkZbN5weeOpOZsDJ6C4zDAVN1cvLnCRuV0us8ppV7SfCLE8MOqcJsWCH2sdaBK9Bvfa1deB4qylcnosd69Sczvc112nQjNrZgVo43fGgjWk8/nHq1T6kO3aQ/SBqAIZ/hC65rmiwONs0Idc5ZlF8cTgnS6IwX1dEINfdSYG4SlR0AOmBru+lhpcAMfHR1KDsShPnew9eLJ3mugtVU7fgrDlSmkaRsJdRoYtKn/AllY0n2i+81wfC/zJO2K+B5Zr830pLV/HMd8z7bXNKIa6EN05jDtQqSaOkRSjetcRLjEFeI4owEKClCjAZZh6j/t46p3vq0KoNv0p4rcUsYwDudR+FQnzO73Z5xM5fqnlmEs5LufAMuVvszol53Qix2+0HC4feUgh1msLAKYNHmToebNC0wSx4IzfFep9L58j6IFsLqdleQgIwSXUc8QgbRkVowU30kgkTnXazXV7nl8z6oh5vqD783zMqO95ngN9sckn57LjZPccnGhKDiEkug8BruCSbIP/DI93ivL5dar2xhVFw/sJpuZxiChpp3nCJIaReUTfYGllWNtq3i04tuhlGsfWDWBZPu5RCqfr3P8M4v7HCO4/y3eq1KiXf48o/w69fG1bMXypKjw1CP2dFv7FBWr4D+SE8BK3Gh6ZxOHHwetKw65npLEqA4TdWKesDRTf3Cm9svM6rrC5i/JWauVtmd9leRTf3Cm9slwt7+jw6V/lz7yhoTJE/s7xa/T4+Pw2+ipvcT22zvXr8c8dEU9+9I0BIhRWj+9iOU+ZK0Y2lDyrS9GVJK3S2n9ll+2n+OaE9NT+2qO0n+I7t39hXPsoPg7+L2uPaN+HGjwjuoaH4junVz6uORo8HmW5S90gZ/q80rDVbMSwVWDya3M=
*/