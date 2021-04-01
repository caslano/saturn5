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
DlXj8yuj3piVmWSgHyOTglV66yDx/MR/8B5Cnqff3jcW47WxmHZlHPommHX/iOr6tLgjGUke/MW66yef6rHQT/i2vNoB/qhUOim80XyoBpxEoUKGXo86a4rzyLC/b2RaE7DOvEj55gATs3G2DE6P1OHdMQE8W/UOyCCMTmGXG2tc1FZ0Kgo4uTnv38ESgeXGzTPHEtwAfjabd24HgBRglLtSpWQJNK9dWN1oxYRZLe7NCpcTBuqXFUnYOPM7amg43e60Ti61KAdDBqUBVy2RGk8KsouTD5bMq62oRm0V2ZE9jkEoy5/0fLZz5NwoRWzG3jFsHh+RMYYvFJYzm9XwlJG02D4cNBHYZuVxueMZu1pCpgXo3OmJfTZq68jjMVXgVcwixqxyq65NBvBu3nEc/z68yknYYVNg9L4awulD/64gL5iI+HDSTiOjfK3/TQBaF0gcSwWeQB82N3U0PhwSrGqeTeYYVcFKisWLZ9/c8J5tZ8OiTT9iVJB1chp3RXa/kgkGVMR52pykYPI/frT8qf0vLh82nnrCi2gTsVQGWHPFcDSmmdg2ItYnPw==
*/