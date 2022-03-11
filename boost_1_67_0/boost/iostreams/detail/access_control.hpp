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