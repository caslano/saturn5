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
JsyTem3Jl7ewdZbcTlvY/NkWtlV+DmkLm1W6/0o4KBIsc9vqkfWEzeksFBGz/LT+yCkiiSmh+UNJQcmS4hEWtUYcY+upC4hO2TCL0+w3SW0sL8z6jOmMn45/UoSPg/ZKsQcKP37KohPdNuG7T2XF0Y4R6xtnxfHRg3+kaDIecMVx5Hg9xZF3QUPFsUmoCbnivFOJfSYoADdo2oTch9K4GYCaOhOju1VJa8MKjRMm7srR+YJVmKzI9SZFbvRvoiJ3ZYreFt4Es1a4niGG020mpa82EIqcalGcxhz9NEfn0vzB7Ar/zy3SFf59iNWvfhVZbT5Frz4SiyG1VvcxHF/YUbWmrtzScmBVznCemuEhjOEvGMOhxHB1ieG3XtNjmN9hbuY4T25vk22IbHzz0ywq3awfWvoA3W9RRdn5t+4L7/6jWpmNGWfqa13y9VhGtjg/91nQP3FhN2u3PtmrmBbVCLO22jijmOWvqoQ54iap13qYIcTzQ80CiuR1d6NmAUXyGjKmUN6i8UVjQbtzUZz/9ZTXvm3CUn9+j8u7O+TJ3zCakA8fpUz+Vn3JlP6MLzHrea4Hm/zZhLPbMfkL7clnP00aswlBoMo8n/+s3slxm1nlu73dUBhIvcjxx8Z8l+nugWB5gnMyULnh8yrl8Y0oZYJjxwTn490srxd2486aVt359Z7jg/ldNS+9gAmOXWNlCPmYjRhvjZHPVuSx
*/