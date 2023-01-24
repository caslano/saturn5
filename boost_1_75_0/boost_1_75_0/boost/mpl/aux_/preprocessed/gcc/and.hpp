
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/and.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< bool C_, typename T1, typename T2, typename T3, typename T4 >
struct and_impl
    : false_
{
};

template< typename T1, typename T2, typename T3, typename T4 >
struct and_impl< true,T1,T2,T3,T4 >
    : and_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4
        , true_
        >
{
};

template<>
struct and_impl<
          true
        , true_, true_, true_, true_
        >
    : true_
{
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    , typename T3 = true_, typename T4 = true_, typename T5 = true_
    >
struct and_

    : aux::and_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4, T5
        >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , and_
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , and_
    )

}}

/* and.hpp
By8aKEzp7Mh7YGf16U/jtfuSdE8TolLejU/kiD49XgbPM89eFzDJU0jL1x74tF+j3HO/+DkO5++aaZZb1LLERNNBqaQuZoWtIoO9Fmcbcd68pgzJC98/iz8NsoCuG/TJT4AJz87z+qnFRgfsBwltxuzvhIT93DodRP7w05478mDiL9coH2pfN20LNR9H3W1RL/l07cNKV+6iz+DzMq4/3sHpaeKwYoDhrJ1WRD2t7ZW2WXhJ64f2KJoVuVXIH/eEbTCUY2ZaRa57Knj29jtKa8DGidYZIv4yIdVXf0MpBerVBtYWX9K67+s5PWIeLDcVR0aS980lH9f62HZczGiiLUPu+mR8YsdPveq2qK/IypesdWCxX3GC/JqiHIwfn2N523sGRsF3c7pJNT09R52EdmgtLuwLb8n3OwpWVYhZxLBfbFNeWmg5QgCYBhGbMX4k1xw75HHRqzAFKGyPYFqC+yA3zAe3ixKmZmPzK7+BvpGZ4IwigieI6GJs+qatY2BUjHGen9x52EFvrVm0XexWbcik5+fKO+iLr/wG3r6YmISfAZh45s/96JjiZwDKvRgAX4dd3K8nzW/WPrYKcwsb7oGbkiM8//05lU3cL1cVnJ1Qc9ajz5YCeSUGfhN4fZ07PgLH51uN4SukTgT09Ow1hEwlD4xSE7lfio1B75XGjG4evYO9GNRv+EP98F/BRzoKLxfjWBUpNHDyz76Z
*/