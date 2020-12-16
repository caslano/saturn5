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
ykaLQ+935WUFzL88ovxssE4JaOPm4qu0jev+lBqHI13hbrtrfxNoI3V/uF7Js9rXMfq86Obh/pgaflNdqG8DNcM9Utzfk+f6y1p/mnbSHSvwV2B3u99TzjPeXI9Jej1K2el9Q9Fx8hlYv0PFcG57xCPrAjs1ZtzwqdL6JTJtDFx7Dmrlukb5b03tGr/DRHxl7n1VJn+uwrekQvVlN55qqeNuCXQXMtR+VwjMgwy/hh5/fUP5jzOln7iC21V33EX0Bu6w/bRhbVm4UT+JwzyGK+HPVeEby28s3Nu/+U/0iDFdfeyp4vFdqxLju47elDeW1PM0Sx1TxGZ1pp1Wuw3Y4ZavPSAToCMda7vlayxPwkp5uu2Fc3F3XOZ+5We8lWL34hFTmUo8Mv7p9vHdd7Id6nx//HqtekhD7uMi9GVfQ4Tr+tryZS+vP7oVtzKFbtDP0Dq/R8Xdmf6uT93vzjr3V0LodUyI+qCsgupD7m2tTPT6WNKIf8S2dQ3hOLuvvdGtD/vBxQvcHJZPVm7eirDBc8e5IfvaG4P3QLHCngaknuhx9h/t84PVe3QK72ldoLEfvlHv10g8Hcz9cPEbcuzCuUf+Qrm9r7WxH9QlLPIh8pHUib/c/R0xgPFHlQfSQNv7SsnfTYee176rJW7bS926OG43lrp1sKTdnuG6dVO/m7u/u6jf4e7vTqHn37S9EGX2f6myD9rzoMqx4jGWBk34R+KugeQifZNto1ZKj37S/Cdh3Xrqnaz8djPqkea3hnx7iBRIfWrv9FyLt1B3bKAx928B+r+eZ9QB+/5tEe71Jdn3cLL6SF9YnGWa+ww5Z/qISkN75kyjAr7nd1B0JbIS7ampvuy8J0reY6UeyKPthh99TEzlL3AeSxbhz5N6mYsMsO/vkrlT47xpP7esjfUiYT1Bc3PGesFv8Hj+nJn8Y6ibOSrtTll6VFl2piwjaMfGqTQ8I3Vg348fV+L+c8q0n1Z+UqbavF/wWDHpCx7fOr3sPtEehLc2BpShrNaxAtfrmMuQsJUvQ/wGze3zOafMbPO+qqC4u7vvjoa2UPPr6OonVZjXdtajmMs1aG5f0qzvqequvX8F6Gzzsn2E6TyPU552y5sHs9OUVK6PkPJ0xX2Elk9X3Edw4lHjgIY+Qp+ny/YR3rD1p/nP7yOc97S5j/DWv6iP4Ky/2NJS+tJczAt9/DPT7rMF1kfuxDkTs+QmCL4H+C39HBXmVY+xHxdUth5tjDUZ/l6d/85zGr4NdUP4ivvVm59R8+iUjdd07xCH+V7Tx4I/VX62ekz3k4QPnOfT1p/dp85/70HH0O9xKl/P1FLCGjIIn0fMbuZzH5XvJnpR/rjvHc+Wu95M7m/Zq6rqRe7vsv195R5vuO/1e5yJjRJ4KXdhGnGnPhegU7xm0T5UcoxXheW/4PkFXUfEj6M/5Y5t9VF+b7I6yzfmYtzwY9w4xc00buXqXPrz9vm7KfdrTW0w4Q3vclo63lLnx3piPA3csdWPVJx13fUUfykpN49pfjkB9lPn63k7UlKPePyWYV7EnYv+Wvmd5mlFvr+w6pvWXbjlsUz5fds4L5IMC9T5Nz25nvBy11o8r/yt1eZClGlpPJXOuatv82ljfX8NWksxQ9wdHgqaM3lb1lPwN+MoSBVsFR943rk/yh0/1OdK5P4wjxXGB/T1yruX9PkWKZOg+eV35F4aiITLOsQuduFrfbx5k5jjzOV5Kv0N8553CcN/4s/8DT3NnzyDsAmNGNZdRZYpS33d1UR+6/2GSQFtxKB2Zd8p2uIvvUjPl/QDKvluSli3ff9OrYkmCuXb2PfCf3nvFeb3gJsJ47wHhHr3cPq0BQT41H23+Gk=
*/