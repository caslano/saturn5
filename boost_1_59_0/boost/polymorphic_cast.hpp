//  boost polymorphic_cast.hpp header file  ----------------------------------------------//

//  (C) Copyright Kevlin Henney and Dave Abrahams 1999.
//  (C) Copyright Boris Rasin 2014.
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/conversion for Documentation.

//  Revision History
//  10 Nov 14  polymorphic_pointer_downcast moved to a separate header,
//             minor improvements to stisfy latest Boost coding style
//  08 Nov 14  Add polymorphic_pointer_downcast (Boris Rasin)
//  09 Jun 14  "cast.hpp" was renamed to "polymorphic_cast.hpp" and
//             inclusion of numeric_cast was removed (Antony Polukhin)
//  23 Jun 05  numeric_cast removed and redirected to the new verion (Fernando Cacciola)
//  02 Apr 01  Removed BOOST_NO_LIMITS workarounds and included
//             <boost/limits.hpp> instead (the workaround did not
//             actually compile when BOOST_NO_LIMITS was defined in
//             any case, so we loose nothing). (John Maddock)
//  21 Jan 01  Undid a bug I introduced yesterday. numeric_cast<> never
//             worked with stock GCC; trying to get it to do that broke
//             vc-stlport.
//  20 Jan 01  Moved BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS to config.hpp.
//             Removed unused BOOST_EXPLICIT_TARGET macro. Moved
//             boost::detail::type to boost/type.hpp. Made it compile with
//             stock gcc again (Dave Abrahams)
//  29 Nov 00  Remove nested namespace cast, cleanup spacing before Formal
//             Review (Beman Dawes)
//  19 Oct 00  Fix numeric_cast for floating-point types (Dave Abrahams)
//  15 Jul 00  Suppress numeric_cast warnings for GCC, Borland and MSVC
//             (Dave Abrahams)
//  30 Jun 00  More MSVC6 wordarounds.  See comments below.  (Dave Abrahams)
//  28 Jun 00  Removed implicit_cast<>.  See comment below. (Beman Dawes)
//  27 Jun 00  More MSVC6 workarounds
//  15 Jun 00  Add workarounds for MSVC6
//   2 Feb 00  Remove bad_numeric_cast ";" syntax error (Doncho Angelov)
//  26 Jan 00  Add missing throw() to bad_numeric_cast::what(0 (Adam Levar)
//  29 Dec 99  Change using declarations so usages in other namespaces work
//             correctly (Dave Abrahams)
//  23 Sep 99  Change polymorphic_downcast assert to also detect M.I. errors
//             as suggested Darin Adler and improved by Valentin Bonnard.
//   2 Sep 99  Remove controversial asserts, simplify, rename.
//  30 Aug 99  Move to cast.hpp, replace value_cast with numeric_cast,
//             place in nested namespace.
//   3 Aug 99  Initial version

#ifndef BOOST_POLYMORPHIC_CAST_HPP
#define BOOST_POLYMORPHIC_CAST_HPP

# include <boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#   pragma once
#endif

# include <boost/assert.hpp>
# include <boost/core/addressof.hpp>
# include <boost/core/enable_if.hpp>
# include <boost/throw_exception.hpp>
# include <boost/type_traits/is_reference.hpp> 
# include <boost/type_traits/remove_reference.hpp>

# include <typeinfo>

namespace boost
{
//  See the documentation for descriptions of how to choose between
//  static_cast<>, dynamic_cast<>, polymorphic_cast<> and polymorphic_downcast<>

//  polymorphic_cast  --------------------------------------------------------//

    //  Runtime checked polymorphic downcasts and crosscasts.
    //  Suggested in The C++ Programming Language, 3rd Ed, Bjarne Stroustrup,
    //  section 15.8 exercise 1, page 425.

    template <class Target, class Source>
    inline Target polymorphic_cast(Source* x)
    {
        Target tmp = dynamic_cast<Target>(x);
        if ( tmp == 0 ) boost::throw_exception( std::bad_cast() );
        return tmp;
    }

//  polymorphic_downcast  ----------------------------------------------------//

    //  BOOST_ASSERT() checked raw pointer polymorphic downcast.  Crosscasts prohibited.

    //  WARNING: Because this cast uses BOOST_ASSERT(), it violates
    //  the One Definition Rule if used in multiple translation units
    //  where BOOST_DISABLE_ASSERTS, BOOST_ENABLE_ASSERT_HANDLER
    //  NDEBUG are defined inconsistently.

    //  Contributed by Dave Abrahams

    template <class Target, class Source>
    inline Target polymorphic_downcast(Source* x)
    {
        BOOST_ASSERT( dynamic_cast<Target>(x) == x );  // detect logic error
        return static_cast<Target>(x);
    }

    //  BOOST_ASSERT() checked reference polymorphic downcast.  Crosscasts prohibited.

    //  WARNING: Because this cast uses BOOST_ASSERT(), it violates
    //  the One Definition Rule if used in multiple translation units
    //  where BOOST_DISABLE_ASSERTS, BOOST_ENABLE_ASSERT_HANDLER
    //  NDEBUG are defined inconsistently.

    //  Contributed by Julien Delacroix

    template <class Target, class Source>
    inline typename boost::enable_if_c<
        boost::is_reference<Target>::value, Target
    >::type polymorphic_downcast(Source& x)
    {
        typedef typename boost::remove_reference<Target>::type* target_pointer_type;
        return *boost::polymorphic_downcast<target_pointer_type>(
            boost::addressof(x)
        );
    }

} // namespace boost

#endif  // BOOST_POLYMORPHIC_CAST_HPP

/* polymorphic_cast.hpp
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
*/