/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DISTANCE_IMPL_14122005_2104)
#define FUSION_DISTANCE_IMPL_14122005_2104

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/distance.hpp>

namespace boost { namespace fusion {

    struct reverse_view_iterator_tag;

    template <typename Iterator>
    struct reverse_view_iterator;

    namespace extension
    {
        template<typename Tag>
        struct distance_impl;

        template<>
        struct distance_impl<reverse_view_iterator_tag>
        {
            template<typename First, typename Last>
            struct apply
            {
                typedef typename First::first_type first_type;
                typedef typename Last::first_type last_type;
                typedef typename result_of::distance<last_type, first_type>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(First const& first, Last const& last)
                {
                    return boost::fusion::distance(last.first, first.first);
                }
            };
        };
    }
}}

#endif

/* distance_impl.hpp
QH5mxbYs7kX1tbHAZVbf9uLtvVRfRwtUYXFvzq5fJMybZIGOLG6jd0NaYbZuFohhcTdmVTxGcd3x2qGV9nRA05LUFqcFGjFzrr9VXhj0tUALZuve9T1E/dnPArPSSHvd6WkZastwC1QGaZGG/f9Qn6G5WDvHp/s+r7BElwVyMeuwukIxGtuRFngC0krqe/1EbRllgYXMZl6LGSzMNxqvcdLYNQ7LVLGAigVVDH5J3QwqZlUxm4rZVcyhYokq5lQxl4q5VcyjYl4V86mYX8UCKhZUMRijMn4qZlUxm4rZVcyhYokq5lQxl4q5VcyjYl4V86mYX8UCKhZUMRirMn4qZkV7EiatR6+9J6nMSRZoEy7txdJs46k/3RZIAmkVEjsXo7jpFghTrCLalNy7X1FbUrW+YGVWSVMEuNlStX5gR2uiWGVNUbAXLFpJmBctq0aarv7fscIMv1qgJ7OoX6Y1FRaYaYFXIG1qk+W1KG42nidYnOPz8PbCPHOUvlZM9jW2RcV8KuZP1YpCAE28T7yKpgT8N7/oSWHueXhdYZaz8dHrwmABjjtIW70tZo4w60K8rjDLNP+PWGFBtC3MVuTsfUyYf1Hq5l2snHsU67HldYIw5xLl3KNYdPUpF6m+pUruivHcYVnqZlAxq4rZVMyuYg4VS1Qxp4q5VMytYh4V86qYT8X8KhZQsaCKwXKV8VMxq4rZUrUSYEdrophd01PuE2hetKwaMrlPoBlW4j7BjPYJtMAquU+gsX0C49bIfQJN7hNonrVKOxXj7fSqmE/F/KlacQigXVTaEqfpC5/qDlsjzLbBAp4waTNt/3qF+TZbYDeLa3+zQ6Kw4FYL3E8rTddjyjVh/n0WqA/S6qwoUEOYfb8FmrG4S1dXFBDmPK7koBjPwZWqtQI3WjfFquL14aWlUZgw6wkLdGBmfjZ9iDAP2itmNH5o/pNy/NDk+KElnrZAb2ZTG+ZaIcx21gIjmD0ZNaGZMMN5vB/TSmtS4nR9Yc6LFqjG4pK7zviJ4i4ruSvGc7eqmE3F7CrmULHEVM0JTrSrilXTlIZ01wcvE+a6YoHnzNJof0wjzHvVAo+YBUrl+FOY/5oFtjGbXj/5ijDfdXyepZE263rru1TfTQuU1kor+zLuoTDHHQvcY3HrCpbrQm25Z4FkFvcs/+pT1JYHFpjEbMFPa58Kgz8sUIBZw8JpG1OZT5U+U4z3mU/F/CoWULGgisGz1M2gYlYVs6mYXcUcKpaoYk4Vc6FN0UpLnHDbT+PwwgJjNdKi59RTnrEUAc9LfI6iWHVNHwh/0rqQMAha4AZIe1r/u6rCDK/ltQNNXjvQnG9wD2FGewgavMPrCjO6rqD5/5b5ocn80AIqFlQxeJ+6GdCyK1YD7e0PTzoIs6H9xOzRu413hLllmWi8zNLgQcuiWE1NR6DvjaL5VCygYvAhdbOqmF3FElXMpWIeFfOpWACtt2K10AoUKbxcmPOjBZzMLLobHsr9H7xuaqT9dHB8N2HeT3hdAWlzD8b3FOb+1wJWFjf+cvmOVOaX//F1F0BOXV0AgM/bRRYPEkeCtSwLS3CHYMUhwOIWnKLBHUJxT3FvsOIQKF4kFJdCcIeg/bES/KfQ9j//kHvuyc68N8yUGb6ee8+59z7Ny0s26M+sbcbl24QF/8kGb0Ha9nwDdlIc6MGhsBruTgpQf4oe4oAsek1omF/DAhoW1LCQhoXR+jIrVKj+fJr3GD104rWHip6j7ShWT+eRtdDoPBLNjVaPmW/UsiPCgmhx0qK3aVXrD2G0fRGrrXSDnKV+2C4slEIPn2Kkte7+frUwX5wec5V2tkCagsJc6WV/aKy/buBGqxqxukobmP8=
*/