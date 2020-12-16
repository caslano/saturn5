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
UL9x3pmTsB2qjuqjf0Vr4CT7V6gAd5xL/SudMPjYp2wVm/lVKVUlvxXkXzgOdxd6Vv+lgRTtBeUYlIRPadgRpqx4424ohPxlN0prBgjwQw7o4EBun1EdUCd50/rmrIMUQjc0YrJ/3TbINfnVnTi5eoKVg3RFUjBfuSJBrsSbdIAOHQWbjiB7TnhvpujtqRwxHbqmziNTr58lun0qdrvqUup55F15Ap88qIVUv3lifJtDYPl2aeUaq5UzXFo5n5pWRE0renX3d9uh5hnYOCgR1eyZ8tPzFuyS2YslJHK2Mva7LwAUQSh+dTeUj7ai8qUJEBIGCO09NaPAZsLFEQc7S6Ekpy+KBzjJ1VdIfYOq5q6fpWroD+xeop77D2e78M+bmX/++Xydf8aCvFZgsPBMMeiCNOhoreARh5Cws518pnrYHnLI8TYOeRqhsv48nUMeHbRx9qrplsEy8XPGMySNgdww7TRsn/FA9Hd3ssOecpI93PkUe3iJI329I32sHs5PuL+ZWcTyaQHSeFYnmoAF2pTXXtFBHU8Ik+n8BzvdvKefOCYRblCXkprzb4Xs6/0eVnN2mCDcoIZoi9T8XFGqG7+0G0GQYUq8shNwx66xzq6JR7ZvzFYqafsdosefz3Td75VMde731GOd81lpyNdKkXSscslR25Pt5sTBsbjK73HJ73Hk7835HfDn6/YwlD+PMkKpj5b7jUZuNxv8JabXgOmu9Bo1ZS/Qq/egxtHr24FW/hSX/CmO/FsGNnpj3tj9ettpTJ4CQR7nzv18OeDhyF09HPbwn3gDP5E0CKNg90v5pp6M7r0zLmojX4Dd6MP9bC9OD4n0TCs9A9PTShurAEimva7rSfep2n26bYdI/QAb5fIFDakiaKGeekhglYle3yxFQVCz/mavlovZQuPydbxurS2iHReFHiuMxa1Jk1qtrWE3aUkekcTLxgItyYAkvkNfyhoHMk/BPJbSoQD5Yy4OBlRH0E3KLMHDjtUVEQVCEQGXVGt6xPft5ZR67dH+fAbLA2tYHujo0exuVp9GIgFHvB6QUgHHjDm9Lr0jnHrQ6XVJXsCprU63U11txdgtBC/ivLFxbs/IUIhl49xptEPjKv49hESQNZoIQiF29ckiCDv71GIpVPMWiqL8ZOrCHbpx0qWnkjzCEQ8cTkQq5Jgep9UlUhGnejnVIlIxp350al0ihZhIhUykIiZSMe/+VMOdZGoxVW4A2X/rYZJr/P6NHBLre5adrul77p/suNE736Ppe1oPUXdrE+t7wqDv8WhPmen6nsdZ39N3qn6x/1Ggo23JDsvrGfO1Y5gwMRBaxo+F9TEfMTk2ddux8MAOsvbQEtJEKYUgPsR8rIuSaFJuE5REQ1hJ5F+4iJsxdYrukeCzwXuhGaEEzXBql67rvw+1Sw3/6nn/+VTml1XML/t7tHk152RyIMARrYHF2t5OvnaQ5A0c0+wUF97AqebJLryBU5+jVOYNyCEBX3EAGkmOR1iMdI3m2tG850TkEFpLVgxgB5DMSCnEDk+ZZbLLUy2WQjVPC0bKuptvda40tIBcGXDEy4UiYjJHTBxI1CvlmG0FDuo5tSWrCxwEdLqrvKygDg0nKxpOUDSEGuuoW1iMYW4r6eGk5ekTkJZau47Ljf1x1Qyu82ONOP84RcwP4RCEG/9ivvCbLJ6T2gYR9EgqfZOzU1bRFUgVXQHnHQoBfxk+/OfYqSL4jZbuqoiT69PQTSUl1FShoSvSNHSFrKErrKOhKwQNXYRbM5IEohkc8QwwLzWkOHLQxLqDslLP0HZi3UG5XM/w5Yl1BuUMHJT6mAuo1ZuH5vJ6NYHjBVcwF8IZjQs1qyxqRl2oqVQ=
*/