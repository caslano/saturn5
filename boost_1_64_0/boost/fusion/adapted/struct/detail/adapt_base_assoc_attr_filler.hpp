/*=============================================================================
    Copyright (c) 2013-2014 Damien Buhl

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_ADAPT_BASE_ASSOC_ATTR_FILLER_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_ADAPT_BASE_ASSOC_ATTR_FILLER_HPP

#include <boost/config.hpp>

#include <boost/fusion/adapted/struct/detail/adapt_auto.hpp>
#include <boost/fusion/adapted/struct/detail/adapt_base_attr_filler.hpp>

#include <boost/mpl/aux_/preprocessor/token_equal.hpp>

#include <boost/preprocessor/config/config.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/variadic/size.hpp>
#include <boost/preprocessor/variadic/elem.hpp>

#if BOOST_PP_VARIADICS

#define BOOST_FUSION_ADAPT_ASSOC_STRUCT_FILLER_0(...)                           \
    BOOST_FUSION_ADAPT_ASSOC_STRUCT_WRAP_ATTR(__VA_ARGS__)                      \
    BOOST_FUSION_ADAPT_ASSOC_STRUCT_FILLER_1

#define BOOST_FUSION_ADAPT_ASSOC_STRUCT_FILLER_1(...)                           \
    BOOST_FUSION_ADAPT_ASSOC_STRUCT_WRAP_ATTR(__VA_ARGS__)                      \
    BOOST_FUSION_ADAPT_ASSOC_STRUCT_FILLER_0

#define BOOST_FUSION_ADAPT_ASSOC_STRUCT_WRAP_ATTR(...)                          \
  BOOST_PP_IIF(                                                                 \
      BOOST_MPL_PP_TOKEN_EQUAL(auto, BOOST_PP_VARIADIC_ELEM(0, __VA_ARGS__)),   \
      ((2,                                                                      \
          (BOOST_PP_VARIADIC_ELEM(1, __VA_ARGS__),                              \
           BOOST_PP_VARIADIC_ELEM(2, __VA_ARGS__)))),                           \
      ((BOOST_PP_VARIADIC_SIZE(__VA_ARGS__),                                    \
          (__VA_ARGS__)))                                                       \
    )

#else // BOOST_PP_VARIADICS


#define BOOST_FUSION_ADAPT_ASSOC_STRUCT_FILLER_0(X, Y, Z)                       \
    BOOST_FUSION_ADAPT_ASSOC_STRUCT_WRAP_ATTR(X, Y, Z)                          \
    BOOST_FUSION_ADAPT_ASSOC_STRUCT_FILLER_1

#define BOOST_FUSION_ADAPT_ASSOC_STRUCT_FILLER_1(X, Y, Z)                       \
    BOOST_FUSION_ADAPT_ASSOC_STRUCT_WRAP_ATTR(X, Y, Z)                          \
    BOOST_FUSION_ADAPT_ASSOC_STRUCT_FILLER_0

#define BOOST_FUSION_ADAPT_ASSOC_STRUCT_WRAP_ATTR(X, Y, Z)                      \
    BOOST_PP_IIF(BOOST_MPL_PP_TOKEN_EQUAL(auto, X),                             \
      ((2, (Y,Z))),                                                             \
      ((3, (X,Y,Z)))                                                            \
    )

#endif // BOOST_PP_VARIADICS

#define BOOST_FUSION_ADAPT_ASSOC_STRUCT_FILLER_0_END
#define BOOST_FUSION_ADAPT_ASSOC_STRUCT_FILLER_1_END


#define BOOST_FUSION_ADAPT_ASSOC_STRUCT_WRAPPEDATTR_GET_KEY(ATTRIBUTE)          \
    BOOST_PP_TUPLE_ELEM(                                                        \
        BOOST_FUSION_ADAPT_STRUCT_WRAPPEDATTR_SIZE(ATTRIBUTE),                  \
        BOOST_PP_DEC(BOOST_FUSION_ADAPT_STRUCT_WRAPPEDATTR_SIZE(ATTRIBUTE)),    \
        BOOST_FUSION_ADAPT_STRUCT_WRAPPEDATTR(ATTRIBUTE))

#endif

/* adapt_base_assoc_attr_filler.hpp
rkx3ofcgW9Qfl+J+g+Vki30bl+FMOVG2V8Cd0+BOKz4LT/6iOAPuDJzBNzckw1dP9nFyLeYS4Wec7IlyncQS4eYi/8w67INAn6rUOrNuMdz/Mdw/B+FdQv9Ef+jCkIz/Uri3SvgF99ZmcPpx33El3OtARzOIOq0j2WLYehjZg0RdmynvdeicKdPxCLJ/JOZZyBZrxI4jW+TrfmTXkd2f7HlkDyR7IdnZmfJsv0FkX0b2ELKvz6D0Jns12cPJFnsyTshUZ+thf0SoBt9ZP1tvbHN5pt54skeJMXVzec/EBHzfbJFuWIffHe834/ZC/k4kOe4zki2mKkfhvWuEm3gvA+nTlvOB/HVrEVoi2r0eZLM+nmzu47aQZyr2JnuOmOoiOy73nSxZINqrFvJ+i35k3yLiQfYjZA8g+0myjyf7LRFussWc6WCyvxb5mOxvRb5sgXybif0CvH9Ahi9f8DhiomuGTJejMmT4js6Q369Hhvxux2TI/NuL7KgIL9nnifCSfYkIL9m3ifCSfbcIL9kfiHBmyDMeB5L9vShnZIvzJQeTfQTZw4Q/4juSTSZ0ItmFGZS+ZBeTPSZD5o+xZDeSPY7sSzMoPhkyH+SQfS/ZE8i+n+xcsl8kO4/s18meSPZ2sslNPtvxJLK/IXsy2YdS3IvIFuvMppDdi+xisk/M5PKypITsk0W8ya4gu4rsqWQvzOS2e8mPyZ5O9rVkn0L2TZncti+5h+wZZD9L9mlkP0/26cJ/sqvI/oTsarJ3kR0mW2SwCNldyK4luzvZUZEuZJ8h0oXserInkB0jexLZ88ieSnYj2fPITpB9FtlJss8he774LmQvEOlF9pkiXGSfJdKL7LPJfozsc8h+nOyfkP17ss8j+12yLyT7Y7IvIvtTsi/OkPlI5FHsJwg9hvIhtgHM8DonLWU9kNtS5qM8skWZyid7mNBl4WzMSf9g71zgrBzzOP6ey4w2SemKaKRUdJluDN0vU9NFjZoyiJlpZmqm5nKaOVOTQirEtuSyZIlBahAGUSqaJYSWQRKSkBWyZgntCvv7P89vzns572nOpLWXz5zP5+nbeec5z+19nv9z///BGWASeDU4EpR5/yhwHTga1HZkeJ+A9wwWO+zIxMOffO8BdpZ6H6vrbe9YXW/7xOr2fRZ1cCaAudKOwRJpx+CVIhfBP4D9weUiJ8B7wYFMRyUc7xoYW9i+W8j9CqZjHPM3nvFOiNVybiKYBqYy/AvAP4MXgp9KuYFyvvMSKS8wHewKZoC9wUxwEJgNXghOBTPAaeBlYI6kH5weq9vDDHAVmBer20U++BRYwHxI2fP8vlHM8jyK821D7Snq/qBE4gdnxWr5PRucAJaC06WfAQvAS0H2ZzxLj7JguNb+rNqj68XfwZPVOQj9vvZ7dLl9B0rf+gOYCB4AR4H/YL2L9/AMPc/WI3y1NtaeZ6K2+VBu4DvgmeBOcBK4C5wG7gavAD8GrwE/Ae8D94APgp+B8i73glXg5+A74FfgL+DfwBMR19dgHFgNdgT3g8PB78Ap4PcSH/iDT/dnP4JB8CB4P/gT+GfwZ/BF8BfwVbX4i3hBD7gHjJX+Sd4NmChl6dfy6HfSX4FHg9nSB4NB8DjwCrAZuAhszn5JrQk05rid78U6Dmjl1+/leL/ut0/w6/ZzIsc/bcCR0i8wPAloKcPbw3ZwkrxHhncW+ps20q7Yz/UFe0m7AkdIuwLHSbsCs6VfAueBg8HLRX6AN4iciNHtcAS4VvIBbgJHxuj3Mwp8X+QEuE/qWYxuR+eCJ4Fjwf7guBjdj5wHXgCOj9HjixSJF5wELgXPl/4VTJX+FbwoRr+fyeDb4MXgh9JO2Z8uheM=
*/