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