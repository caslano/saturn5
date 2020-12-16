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
PFIrBbbf2MqlfVPxYdy/rf22e74gg3eqUdMl3yFnrw2ZTqUbOvBDyXMbK7ocH4hdIJRli9rCxwet/Sa4cDuaPqDmR4G9O3DKOsyEo8hA0aue2KuohTjNPZESbjRTbYtPKqUT3a7at6Ci1hrQzO/p9AKHDWfhbaAmdvMU1kdcDrhes+/CkcT8Ikc4S+hPvBq/y5tNeAI8Bfu1LnhMRwUn64LulELla5XfuG8su0x7dRytVJuPGfTq+AAUm1vt5ZfSbsFYGla6y8XIMik6QsfL97riBxxuiSKl/YISDayLk84WwyRRwJlwt4AowkqxmIylM1Vtp6M2bpbjUJvS5PxNDon/yR+hd3q3vOW6hH9neDl+EQsGbzcZYhJ9OPtjI46E3HDbb3txKepYAw3vlTDavNtY2g/lcWCOFaDCWZTV2j8clsDT8pMwH4ehIk5Pf/Hj+b1EfJ3jphJqhZj8t1Zcjb1yyIXecOYKx/HBWLETbURsJ04gZ5YFY31+myI/vFBI7XCqP93M0VZ2LeJ7eZZU0T/nwg1hXgXXFlN2euRtz3CEcfQaix387m0sLnYG0G8ECptVFWD0qCeNFQ71komOdSawwlf8FGvxTZ2D9JilTh1oTxyUUwdwe9jXnQzkmrYQK/4Op5ajOM5Thh5fnumPXeoMxFcUvFGwx3M03ynr1Hifc1b0dyitCIKcmQvAvsWPnvuOSHPCi/A6ykmoasFnzPHccgx+D48NGhCi785ewuQMIxNyov39SDJM0iDtFJXrI1dzgegET1q0BARtOknUQIvXT8Xp8bcZActzy3Jq0CpSwl+NSoazFVXo9KlazfVj6sn3dEBCCzZcXnuYb1Vk32GekvXwfTzzO4HfJyhOyvwbnpe7hGLTnRE7P16l7twtgacTROc/rPwbpCa8JjFKaOFgU0kyz6rHYwr2FGxAxbNeYuK7Y8D/RYcx1G043R+91AvPa3EMYwBeyj2LPsEvQp0MPVzDu3K1MTEK/0rmBZ9ULz0as4pl/5uuFQOgdG/7oy9pfnh3ibXXsD4SLHu6Fct+rrGsUPz4AMuyfy/cW/xV7ceV2+VMw9oRsOLEuG/G+zxT3YpxNZCSFMYRz/wpeFaI37GhvoRzE3qIpY+EoHVqCB5xj7U/n5/Y+coHENvYBVLmpIPPyRecDyQjvX1lcXske6MdkhlFI4FlINnEMhbxXqyx7HdKU0Ench/Rvc31pCR0InsrGi37xGqOfOa1qj0h+Ne2TUiGrj9jQcr5qeflnvYVF8npLLDM8JivmpXvpeNCNUIpd2/GRj1vW4CXpuBPBCMUafRKtYHo0MwAdko4rXlItpOEV1M1DuhbSfQqt311gG+PbgWjpxqRuUQ9I3qVF5dvPgaOBYec4Vn0Hn7wVZZeBsx7XTCvdWz+DQ7rE/HeRoSVZP7tp1djbygvhJzxO/yqyXgY/3XQBm4HRE4oLLzY8w0cgcdKd9rlF4nLYx3QLZYxCyU6HfVMzvtSvCK9eK2mqCCn9IZkxYdc5w1/E3vPW9jdLnikl8N+uoznac5w76T+LulHiCP9NFYOd0Alm6NQ7Be9hH24TpUrrzVgtyguorFHkSybsBfjAimdeX4wdkwaJK1W+vTi0Lb7FZCFnmPSmyTsugckN52NWfWqOVjSsSmPbiofmNmYPqvOhJf7Wc8mgziZ4giJGFfa7gXwSo3bVv8dPwf5Gz/3mhR/4/ZloguttQ+7VHaNDmMS0pYIjCNPPku/bx8u98k3kpp+kz8lHNlvKLezxJcOXKP20eVXf5X4i7shXHd8Hliu6vPLeSDdJFDMi5l19vFdDhV/O9XhaG4a6voW6xLjspzlSaNeB3JM+nLGN3d9q44=
*/