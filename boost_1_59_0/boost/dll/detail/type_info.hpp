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
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
*/