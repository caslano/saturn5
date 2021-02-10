// Copyright 2016 Klemens Morgenstern, Antony Polukhin
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org

#ifndef BOOST_DLL_DETAIL_TYPE_INFO_HPP_
#define BOOST_DLL_DETAIL_TYPE_INFO_HPP_

#include <typeinfo>
#include <cstring>
#include <boost/dll/config.hpp>
#if defined(_MSC_VER) // MSVC, Clang-cl, and ICC on Windows
#include <boost/winapi/basic_types.hpp>
#endif

namespace boost { namespace dll { namespace detail {

#if defined(_MSC_VER) // MSVC, Clang-cl, and ICC on Windows

#if defined ( _WIN64 )

template<typename Class, typename Lib, typename Storage>
const std::type_info& load_type_info(Lib & lib, Storage & storage)
{
    struct RTTICompleteObjectLocator
    {
        boost::winapi::DWORD_ signature; //always zero ?
        boost::winapi::DWORD_ offset;    //offset of this vtable in the complete class
        boost::winapi::DWORD_ cdOffset;  //constructor displacement offset
        boost::winapi::DWORD_ pTypeDescriptorOffset; //TypeDescriptor of the complete class
        boost::winapi::DWORD_ pClassDescriptorOffset; //describes inheritance hierarchy (ignored)
    };

    RTTICompleteObjectLocator** vtable_p = &lib.template get<RTTICompleteObjectLocator*>(storage.template get_vtable<Class>());

    vtable_p--;
    auto vtable = *vtable_p;

    auto nat = reinterpret_cast<const char*>(lib.native());

    nat += vtable->pTypeDescriptorOffset;

    return *reinterpret_cast<const std::type_info*>(nat);

}

#else

template<typename Class, typename Lib, typename Storage>
const std::type_info& load_type_info(Lib & lib, Storage & storage)
{
    struct RTTICompleteObjectLocator
    {
        boost::winapi::DWORD_ signature; //always zero ?
        boost::winapi::DWORD_ offset;    //offset of this vtable in the complete class
        boost::winapi::DWORD_ cdOffset;  //constructor displacement offset
        const std::type_info* pTypeDescriptor; //TypeDescriptor of the complete class
        void* pClassDescriptor; //describes inheritance hierarchy (ignored)
    };

    RTTICompleteObjectLocator** vtable_p = &lib.template get<RTTICompleteObjectLocator*>(storage.template get_vtable<Class>());

    vtable_p--;
    auto vtable = *vtable_p;
    return *vtable->pTypeDescriptor;

}

#endif //_WIN64

#else

template<typename Class, typename Lib, typename Storage>
const std::type_info& load_type_info(Lib & lib, Storage & storage)
{
    return lib.template get<const std::type_info>(storage.template get_type_info<Class>());

}

#endif


}}}
#endif /* BOOST_DLL_DETAIL_TYPE_INFO_HPP_ */

/* type_info.hpp
SS0qW6/p+2LxDeauyUn6r03C1wv6iielZCXf09k2lzeJhZPeKXRfvfoZWvBjp/uqCedcSZHC1Aq1FPlNE17H7uS3hN/fe0a8aYKwwFPvSGGYSANGr+yG5wLweyojoYyIgRuIhYlyucQ/pAKbCFjJVEAvGM8Ho3dN2CQySio9W12ASXSRxpDwOwG5iIS8K9VkPLegV6gB9cfSWNRZWKmVh+YFWJGvTaWGnOCp0cDvuEz5Es1xC4m1mTlrt6MiTzGSdqwj045qKLzErh9ENUdv1nwLOrNgNRRGNIHuN2GtY7miJ0KEh1mxTKVJmnu30KCK2zoHI9K0UoeiUpgyBAHTCq0m3YQMvZeWHkYrQ9Y2iV4fXURYK0WrIldoDmHBe7FG4JtQqFjk7r4DorZSoewgfyJle99j0Aq9goY/hcG0AUtupGnC1SC8DGYhXPmTiT8K5xBcgD+aV/reD0bnyA2JVnMQ91kuDHqRg1xnqRTxkfHvWunMCy+hN5sMg3G4GAfTEJ5Do/sSfi8UcfqnBjRSuaSkw0vv+Uuvgwf010Jws10YYSm9+ItMMqhsegkj/0OfHWm8biEV/y6EsYTLZRiOgc7d7el8FIyngyn7QaooLWIBr0l9SbPkDXOaIo3nD62e0Bt4liABUuTBocUm
*/