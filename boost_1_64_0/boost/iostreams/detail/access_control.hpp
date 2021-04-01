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
opXxZfAXd+PrBqPLuQ/gcqRmFWEcUWf0vQZ9vf2/SvMvLxyHpxDzSZHOBftf+BkNQNEJNcInSXjTu9chNMivv0rK/xWckKXa/6bUk3yHwnB4fuh01CDOcHIxXBmgSFtd+zXZctqFX3tCJUVlFZE/jlE92SojgY01Xiq2Ye6hGfdE6cPQFClRTDXp9tf/xe8ueVJxLTrdg5ZQgxDHxULAXC2uof/+igDKLHLr+ygatDRHjrOJsBYjYBTtISPn2EeEOyGigi/3s1gOdwt9V82QRRXFiXCD0ISvMEgc1q5K8a/Mz2cLIESM6RxMCQFejR2xecWlxx7xtJ2IZD3DvtQRNLJGBd0dd/I/aSEim3o4M3JM5B5Fd7p49nLMpkUw8+l8hIagC2zFd+KuRA88V4FP6vMGQaIPkuR43iNT8EIFjDbTDMdHKL9mYho3wqIsLTF4yCxv9A+mQ7dT+RNZ3mIP7uDD4rFhJ+bjlrQ9xUHztc0u6o0PA7eqYk1bSG9XlRs5H8zFi5tzomIduaGPBYDBDEK+v0Yp2M1kBOB0qpV8p8BFivwxDa1oeovctA==
*/