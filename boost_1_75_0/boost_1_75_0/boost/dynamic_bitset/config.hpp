// -----------------------------------------------------------
//
//   Copyright (c) 2001-2002 Chuck Allison and Jeremy Siek
//        Copyright (c) 2003-2006, 2008 Gennaro Prota
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// -----------------------------------------------------------

#ifndef BOOST_DYNAMIC_BITSET_CONFIG_HPP_GP_20040424
#define BOOST_DYNAMIC_BITSET_CONFIG_HPP_GP_20040424

#include "boost/config.hpp"
#include "boost/detail/workaround.hpp"

// support for pre 3.0 libstdc++ - thanks Phil Edwards!
#if defined (__STL_CONFIG_H) && !defined (__STL_USE_NEW_IOSTREAMS)
# define BOOST_OLD_IOSTREAMS
#endif

// no-op function to workaround gcc bug c++/8419
//
namespace boost { namespace detail {
    template <typename T> T make_non_const(T t) { return t; }
}}

#if defined(__GNUC__)
# define BOOST_DYNAMIC_BITSET_WRAP_CONSTANT(expr) \
         (boost::detail::make_non_const(expr))
#else
# define BOOST_DYNAMIC_BITSET_WRAP_CONSTANT(expr) (expr)
#endif

//
#if (defined __BORLANDC__ && BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564)))  \
                             || (defined BOOST_NO_MEMBER_TEMPLATE_FRIENDS)
#define BOOST_DYNAMIC_BITSET_DONT_USE_FRIENDS
#endif

// if we can't use friends then we simply expose private members
//
#if defined(BOOST_DYNAMIC_BITSET_DONT_USE_FRIENDS)
#define BOOST_DYNAMIC_BITSET_PRIVATE public
#else
#define BOOST_DYNAMIC_BITSET_PRIVATE private
#endif

// A couple of macros to cope with libraries without locale
// support. The first macro must be used to declare a reference
// to a ctype facet. The second one to widen a char by using
// that ctype object. If facets and locales aren't available
// the first macro is a no-op and the second one just expands
// to its parameter c.
//
#if defined (BOOST_USE_FACET)

#define BOOST_DYNAMIC_BITSET_CTYPE_FACET(ch, name, loc)     \
            const std::ctype<ch> & name =                   \
            BOOST_USE_FACET(std::ctype<ch>, loc)         /**/

#define BOOST_DYNAMIC_BITSET_WIDEN_CHAR(fac, c)             \
           (fac.widen(c))
#else

#define BOOST_DYNAMIC_BITSET_CTYPE_FACET(ch, name, loc) /**/
#define BOOST_DYNAMIC_BITSET_WIDEN_CHAR(fac, c)          c

#endif

#endif // include guard

/* config.hpp
Ar3UgZfc1tKyvANeeFzv/yLVfxvqv63ovxn2f3wN9l8UjUXh6iIqjhdlppcHi/qLYZRtCuLWLEnBijak88u7yswHZnRf1bA8ECiguMNOQcvqwogF5+lbXOF0FE0GjGZqQnkNTyjPITNb7GXaCVvdXgZO0aeQmm00eVf5FRie0HyV4Dvdz1AaqhLVvERrjiKArfRoHkl6kkFNLT8L5Vi8XyLzgv2EvVd9y3zqW8TilIOk+9FVJ37Yli7jDrahnEsNZsxNSLNlzIUIHwBmdqX061JEA+aw4OFyBl1f5cCFKOc6yNoFhCjluP8MYv/WKDZSbMNMuGxfVLF3lAbSiv+ZoxKOov7x+9O0Gy7ml8nNofLAywNfWvQrrOPdUXYLzIUKN9myDraNvATAzRtq2PzxVqRmOKbNLA+ryri56z7yQK44FQFKmeapS0g6BSZBuO90VaRHkrJJYdpi7/cAk2FGWm9XeddIdR4ulx3bJTC1hQwXzL8dBqb0IBJvyEmUDy9+B8mJlgol4ofVGCcT5S1bH1b8C/DwEpmfWyqqYGnpUeVG2FWF04fn8XPSUfHM3mbzuq5t8CGZjrgREGfSPcyr50KoiyAeHpmqQOUXCf9RiH7xYFnJlrlFINvs1mB1ocMebVK+AKUdWoOMtH7pEBLrKidDY+TS90jGhBRIazu150NWGR+4yTyKenf3Pd7P/sLMNy1XgpvFRJ+6UKYh
*/