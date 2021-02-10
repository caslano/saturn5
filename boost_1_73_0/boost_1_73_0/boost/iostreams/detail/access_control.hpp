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
bC1tYXN0ZXIvcHJvamVjdHMvV2luZG93cy9WQzkvc3JjLy5naXRpZ25vcmVVVAUAAbZIJGDT19LLS07i0tfSKy7NB1GlxalFILosuaAoP4sLAFBLAwQKAAAACAAtZ0pSV7yyumMEAAAaPgAALQAJAGN1cmwtbWFzdGVyL3Byb2plY3RzL1dpbmRvd3MvVkM5L3NyYy9jdXJsLnNsblVUBQABtkgkYMWbX2+aUBjGr2vidyDupkuKAaadvdiFiq5NXGdGsl1bxYaFiUHtlnT97sNVa5Xz53kPL+Vqwg7v8zvv8wQ4QL9E0zRZJfO19T1abSaxFaw3syixgiTerKNkYQ2jOLywhkn6a5KNCdPVdqfrNB2nXnt3cpDnOJ16bZwmP8Pp+rzx2On1r/qDXsfu9Fpd23V9x+74rms7TtfpX7nZ/7a8p8Z765PVmG7SuHHx/G/zYbrMamw3H9ue1xlkReyu517aLc8b2t324NJuZ3vbA8/3P7r+U6NeGyxmO9167XOc3E3ieu3s+UeQ7cygz/dT6ieLeXS/SSfbjXE8Wc+zya22FMs03A/Kjj7zRyPLD+8295ZtbX9/XYaLIBjttkbRXRBce39/RIsPXnYwYTRe/M9lCy6djVUU1nFqydQsMvWs6iz5vbKCYHxz
*/