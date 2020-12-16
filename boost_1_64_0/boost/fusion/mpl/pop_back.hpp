/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_POP_BACK_10022005_1801)
#define FUSION_POP_BACK_10022005_1801

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/pop_back.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/algorithm/transformation/pop_back.hpp>
#include <boost/fusion/sequence/convert.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct pop_back_impl;

    template <>
    struct pop_back_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply
        {
            typedef typename
                fusion::result_of::pop_back<Sequence>::type
            result;

            typedef typename
                fusion::result_of::convert<
                    typename fusion::detail::tag_of<Sequence>::type, result>::type
            type;
        };
    };
}}

#endif


/* pop_back.hpp
JIeEanoH0zuI3sH0DqZ3MB2GMqJ3MDBDb3vv3ft29+09AwyYib7v3e3d7d3t7V4ZKm5QtzDePc9woTUowxHNQQfNcZ02xfjk7p7CGpDrRt81y7/7h7TorTG5Z/L5jA8St0184yrLPlQc1dawMWU6uOFbrLVfoHHfJ3LAX6hwWBE4t7MhcVvXA9n3XqS43hPF+62a24y7dNTdqG/TmBwIsJY7Aw6POb4ToV7LkrPWW22jOfn+oZHncHRkAF14xjWB0XnBxTr9d9Fv+oJv5F34PjmwVYff8B+xvW6iGakztrUQD+YM85oBHmZsOT/AR3zbxGUUHbLIybtrr3NVcFpt3f+3GMPYAF/RTYCxu0X4zLaEjD3K2LxSLu2if6a4btCQ+3AtDp8r5ElzBnEasLWvy/I6yC3QcsKfsnv/Aw7n+6trZLlWvYEnYss7YZ5aH0ycDnLUWLBN97URp1opTx8TRl4D4/KuxuWdOHupb/2aoMG+UcbvvlSsiPS5j+9ajlx7NE0ayIf9ZacOgGNvvuQ6G7fDPOkfm+iEOT5PTus08yh2UquV531MQ9wz2LMcLxPfrxRIR93hFEjDy/JA3ImyEnEWqvc8FoVp4z4Y3YVeL1fnfZa89ppo7c93OoS5fX+u0qWa4HqJ1bpkZ8Xgal2yZb6PS8p+X9d3Ftx6zm/6zq3jjsxfAnNunzr2rf8Kv0cbdeV+5InfA6MDWuvqTMDeH4Gd6Ky2cX4W6zRO1w07fWcMuAc8u5Q3+tafwYmv9KSE3LmpROYa59/rrq7yGPJr/n3Q3mh1vejwgbFsgxWq4HWKZSLN3zDWbrdYXvm7l5eOY3bW27k6OL81HJQJ8+TvEg7OaTbQ/n8DFgVSfYFPoVz/iPDpKXV1N+Oj/NU8rq/uRlte1uOYIfh82ORVPSav9Jbvl1zR44z1MCbfKMG6Ol/sr/N48jIt5XtZvBsQY7cUc1n+zv635Ppv4qMMwDitpO1yz4qwMkWiZ9z7EthHXlS/N9K2/eiwxr1tz7bJEY3zTcisq70Ux++yR/0WPuhwtWPA2e8sYwCXe/i3PM67CPT7BbsG13eyjBO8US2Wao3oeIMf4Ot8jjTEcckwZzLA8YM76qJ5k6t7jpunD2KwwbiONGr1uhKF0xgFOMqnpnGIIWUdbyZy3PN2tzjon2KOz6TBptt+nOKcbJNRStXvNMsxG2ifhyieOwJKR+B5rbD5GS9P/Aoun/3k31fpRJxzT9AFHsKX/VmLrwv7If8Rj/trKkguni80ZmTe+j5wOg/a9w8SsMy5z3ncI7jvFN/pe5VGX/a/q2oSZ3e/CjxVjcwZj5njbhro40Vjlrv5A8Xxw6x4i0HjJ5ZXhl0yIdewBtC4k7ELm/uHwPip/2SUFjKMJI+KEC3qZYxV4fgeY1jtVwnusKivtoD9WmLaX7qjMG8h93o+e1GPlufnWD5/nvtNmtM4Hh1BpfL0pJ1peScoHDo4Je61KRiOVxrioN0MR98BvAncPIOPfEaGA4HB2bGcHnVtN6vxeJfBaa8zJ/dby9k4HiUDTj7Mcclw3MRw9F0gTYPjLhD232iOG8nOYK/F7xQ2yNKJkeEdNDrR3EtzwjqxZXhWJ3YMx+rEnuFoncj/3uBGJ2qGY3Vi03CsTmwbjtWJseFYnZj4g+FYnTAcrRM9i0MnMD7/yHPiiW2AOUP+zmPPCdhjfwJOB5tBOIF40F8SvLfciqYc+j8/V7tZXcalen/dn9tYO3niINHgw7/31TP5NFMj3dp99uX5ZHM93n+ZyY/dawdzBxFXudl/4U7lDmK9ejbEJWvlzNQtpA8r99AQz9kCuVug/6FNJWe9S5PXLRBj+FeK4+duUfs=
*/