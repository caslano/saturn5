/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_AS_FUSION_ELEMENT_05052005_0338)
#define FUSION_AS_FUSION_ELEMENT_05052005_0338

#include <boost/fusion/support/config.hpp>
#include <boost/ref.hpp>

#ifndef BOOST_NO_CXX11_HDR_FUNCTIONAL
#include <functional>
#endif

namespace boost { namespace fusion { namespace detail
{
    template <typename T>
    struct as_fusion_element
    {
        typedef T type;
    };

    template <typename T>
    struct as_fusion_element<reference_wrapper<T> >
    {
        typedef T& type;
    };

#ifndef BOOST_NO_CXX11_HDR_FUNCTIONAL
    template <typename T>
    struct as_fusion_element<std::reference_wrapper<T> >
    {
        typedef T& type;
    };
#endif

    template <typename T, int N>
    struct as_fusion_element<T[N]>
    {
        typedef const T(&type)[N];
    };

    template <typename T, int N>
    struct as_fusion_element<volatile T[N]>
    {
        typedef const volatile T(&type)[N];
    };

    template <typename T, int N>
    struct as_fusion_element<const volatile T[N]>
    {
        typedef const volatile T(&type)[N];
    };

}}}

#endif

/* as_fusion_element.hpp
3tZiMNs+gX5Nftr9otl30iBLcfUn7TqM0surRWs52BCqrqGFUgxqCDHxQp8GCpGRz9GIfVso5l9UFIfb2qqKJDXpkfwbA3w45VeSt6daXmxTlFR/VFecoObIq1yDfq1zssdPlyFe72iyXbkJso1/eWXK2aluoB2183inXc4X4D+lgmVl8X811gtTjIfLqLKojfAkHPZwakG1mRZJentEjpf/wakMh/Mo4JOKBLb74JaMwrhtw6C4/HMNVnS+buZBGgBx1Vt7VMeMBCXI8O//6CF4/PvGiTMlbifwioKwt3pGy7RCx2IRpBVomEgHe4NBGIX5HZYXpj0FcEPNMj0fJWLL4/54TIC7bkTqHcLXKg7a4/5wYERZVp+ACV471NOqekltdpPWBoGS+t99DIJQhvPJ8XWPoWZa3xZQ1wZX9xkjqPaG8SubSq9YGuoTTmqvKlR4jVNF/m6NocoqadjOGJVUa1lRjSWYhcUqooPlcVAieUWXy3ljdcu0L1GeZTTxsjXYXv1LFi9qnh2CZArqV9BchDAEfhPcKUIUTnMoKkfVoa3Kc+Q35uxU3GjT/k3n/nBcF7/Ii6eAK9UPLeua4un2ILb2Av8r/tRGmUd/bjhvzvi2MptVYXIa1ii7Zvh8wltrhfWT50HkeB4n
*/