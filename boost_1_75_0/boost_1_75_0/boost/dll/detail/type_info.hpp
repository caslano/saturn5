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
BPlAD3c2lG2m4kDRmHouUHhirgTlsD+6QLv+JnY+ukAvIXECGxz5nEjM7a1gKTUPKD4dvDEO0Eo2HnEQ3J8LiFFx38wBwP35wCb4RfdnH4zi+RyRTLk/8Rst9rDg4ZVA3oZVfIYd8xiBtafJJ4otD+12I4iSNBAlMYhU9uLlLQmOyazxJVnYCrekXb/lOa0ix//w0LiSLVTa4rCsIwqVcGlGtETbf/E11gdesn1ABuQkK8ypVsODSf91hjArycKsH/FWUWIJoxKRv+zEEvODzYauL/f9w4NzzsN3MSMxZuem6836Dn0nFpb1B/hsAbwSrxvlS3l3VvPuLEVE/eV33p15+u6kZ6t/t+/O+JDdGW/fnf1itWbsTmGQlja+O5vH0u4kUq5Gr3ZnfOjujA/dnYdodxZASSXgBmp3zuDdWWCO38QgpYmZv9HuFLwFduevzQirUh1cl0nMjf7eYkU3uGhyqXI4i5tZGeJ6cYa4OeKea2mToPu2Pz2qNTx4gHsAXpqxLJZ3EkVIvC62AmTGIGk4ZSMcBIzMF7vKky/kiE6updtQQg66/zoCTA5CGOnDKccDXZppC7yEF7iGF3gJzrWZmGs16rlO4gzwyMmqqle2I71VGmQwqkDaCagwBzuqILRAGSRAjxX0Z1u2f63c/XsRF1OOA8gyWhhG2nvYl6s8B6NeH0K7HHQIAQYgu6BpDkaMAQZk/3RvX0bW
*/