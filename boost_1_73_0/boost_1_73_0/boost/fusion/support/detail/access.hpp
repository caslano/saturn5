/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ACCESS_04182005_0737)
#define FUSION_ACCESS_04182005_0737

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename T>
    struct ref_result
    {
        typedef typename add_reference<T>::type type;
    };

    template <typename T>
    struct cref_result
    {
        typedef typename
            add_reference<
                typename add_const<T>::type
            >::type
        type;
    };

    template <typename T>
    struct call_param
    {
        typedef T const& type;
    };

    template <typename T>
    struct call_param<T&>
    {
        typedef T& type;
    };

    template <typename T>
    struct call_param<T const>
    {
        typedef T const& type;
    };

    template <typename T>
    struct call_param<T volatile>
    {
        typedef T const& type;
    };

    template <typename T>
    struct call_param<T const volatile>
    {
        typedef T const& type;
    };

}}}

#endif


/* access.hpp
gkvK8UHLuo/uzrMJUzquWM8KmUFQrNsj82bw7hhheF6Cg0FennrWF4uQIeHCbn6zq4fjMQhJl/Zh/e7V1aVMmjSDMY4cbdXeX5z0j19eXvVkUpgHid52T/svP5TSy4qFRMTeIh3EnqhJDW2BqrSX6CkZZbaf4MB9AucnFtWO6B46unPzGajvYpJENsEpQV9rDycyjEklSct8sM1KuazeI94QtgWzOAeGRk41shi5IarDRZPwFB6XSFtdyDhuPH4CNErMjJmaeGbTg3hsVSx4hhWLqKYFoohMyqVFneohFsRC1Nl88Li4ZWOvLnjjFgcKQh5XBZmKsmQOBLsfdN0TJwHplJd4qlBFlGr5NZ1yrq/bzhsQNdTYQZcoKvOi2oN9ubpOHN+tdvT9L6/nOLilTUXpQlPRGZrzR3YykibqpuHdUBI00Cfr3nDvg73itjt2AJXBUs54oRHVjVP7ePOcB7dUDIU8qjFmEZajY0wiF02hWJwp51csKpnOsUnLX1L22CrLFAWvbi3FM1Ck+d1nW4BTrlWFChXHV0UUxJiGAmefSGCchcf72QTxuPphC0MmNnSGUD+7NAFRUKLbv3zf61++EhvVqZ4OZ3etzzwA/pfjJQbHb/DtD0C0+/uTXeOXYH2LOuI+F9TRdLuv
*/