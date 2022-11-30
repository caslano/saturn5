#ifndef BOOST_SERIALIZATION_STATIC_WARNING_HPP
#define BOOST_SERIALIZATION_STATIC_WARNING_HPP

//  (C) Copyright Robert Ramey 2003. Jonathan Turkanis 2004.
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/static_assert for documentation.

/*
 Revision history:
   15 June  2003 - Initial version.
   31 March 2004 - improved diagnostic messages and portability
                   (Jonathan Turkanis)
   03 April 2004 - works on VC6 at class and namespace scope
                 - ported to DigitalMars
                 - static warnings disabled by default; when enabled,
                   uses pragmas to enable required compiler warnings
                   on MSVC, Intel, Metrowerks and Borland 5.x.
                   (Jonathan Turkanis)
   30 May 2004   - tweaked for msvc 7.1 and gcc 3.3
                 - static warnings ENabled by default; when enabled,
                   (Robert Ramey)
*/

#include <boost/config.hpp>

//
// Implementation
// Makes use of the following warnings:
//  1. GCC prior to 3.3: division by zero.
//  2. BCC 6.0 preview: unreferenced local variable.
//  3. DigitalMars: returning address of local automatic variable.
//  4. VC6: class previously seen as struct (as in 'boost/mpl/print.hpp')
//  5. All others: deletion of pointer to incomplete type.
//
// The trick is to find code which produces warnings containing the name of
// a structure or variable. Details, with same numbering as above:
// 1. static_warning_impl<B>::value is zero iff B is false, so diving an int
//    by this value generates a warning iff B is false.
// 2. static_warning_impl<B>::type has a constructor iff B is true, so an
//    unreferenced variable of this type generates a warning iff B is false.
// 3. static_warning_impl<B>::type overloads operator& to return a dynamically
//    allocated int pointer only is B is true, so  returning the address of an
//    automatic variable of this type generates a warning iff B is fasle.
// 4. static_warning_impl<B>::STATIC_WARNING is decalred as a struct iff B is
//    false.
// 5. static_warning_impl<B>::type is incomplete iff B is false, so deleting a
//    pointer to this type generates a warning iff B is false.
//

//------------------Enable selected warnings----------------------------------//

// Enable the warnings relied on by BOOST_STATIC_WARNING, where possible.

// 6. replaced implementation with one which depends solely on
//    mpl::print<>.  The previous one was found to fail for functions
//    under recent versions of gcc and intel compilers - Robert Ramey

#include <boost/mpl/bool.hpp>
#include <boost/mpl/print.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/bool_fwd.hpp>
#include <boost/static_assert.hpp>

namespace boost {
namespace serialization {

template<int L>
struct BOOST_SERIALIZATION_STATIC_WARNING_LINE{};

template<bool B, int L>
struct static_warning_test{
    typename boost::mpl::eval_if_c<
        B,
        boost::mpl::true_,
        typename boost::mpl::identity<
            boost::mpl::print<
                BOOST_SERIALIZATION_STATIC_WARNING_LINE<L>
            >
        >
    >::type type;
};

template<int i>
struct BOOST_SERIALIZATION_SS {};

} // serialization
} // boost

#define BOOST_SERIALIZATION_BSW(B, L) \
    typedef boost::serialization::BOOST_SERIALIZATION_SS< \
        sizeof( boost::serialization::static_warning_test< B, L > ) \
    > BOOST_JOIN(STATIC_WARNING_LINE, L) BOOST_ATTRIBUTE_UNUSED;
#define BOOST_STATIC_WARNING(B) BOOST_SERIALIZATION_BSW(B, __LINE__)

#endif // BOOST_SERIALIZATION_STATIC_WARNING_HPP

/* static_warning.hpp
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
*/