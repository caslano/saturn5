// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Contains the definition of the class template access_control, which
// allows the type of inheritance from a provided base class to be specified 
// using a template parameter.


#ifndef BOOST_IOSTREAMS_ACCESS_CONTROL_HPP_INCLUDED
#define BOOST_IOSTREAMS_ACCESS_CONTROL_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/iostreams/detail/select.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace iostreams {

struct protected_ { };  // Represents protected inheritance.
struct public_ { };     // Represents public inheritance.


namespace detail {

    // Implements protected inheritance.
    template<typename U>
    struct prot_ : protected U 
    { 
        prot_() { }
        template<typename V> prot_(V v) : U(v) { }
    };

    // Implements public inheritance.
    template<typename U> struct pub_ : public U { 
        pub_() { }
        template<typename V> pub_(V v) : U(v) { }
    };

//
// Used to deduce the base type for the template access_control.
//
template<typename T, typename Access>
struct access_control_base {
    typedef int                                 bad_access_specifier;
    typedef typename 
            iostreams::select<  // Disambiguation for Tru64
                ::boost::is_same<
                    Access, protected_
                >,                              prot_<T>,
                ::boost::is_same<
                    Access, public_
                >,                              pub_<T>,
                else_,                          bad_access_specifier
            >::type                             type;
};

} // End namespace detail.

//
// Template name: access_control.
// Description: Allows the type of inheritance from a provided base class
//      to be specified using an int template parameter.
// Template parameters:
//      Base - The class from which to inherit (indirectly.)
//      Access - The type of access desired. Must be one of the 
//          values access_base::prot or access_base::pub.
//
template< typename T, typename Access,
          typename Base = // VC6 workaraound (Compiler Error C2516)
              typename detail::access_control_base<T, Access>::type >
struct access_control : public Base { 
    access_control() { }
    template<typename U> explicit access_control(U u) : Base(u) { }
};

//----------------------------------------------------------------------------//

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_ACCESS_CONTROL_HPP_INCLUDED

/* access_control.hpp
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
*/