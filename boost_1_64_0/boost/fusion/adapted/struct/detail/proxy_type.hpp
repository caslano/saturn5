/*=============================================================================
    Copyright (c) 2009-2010 Hartmut Kaiser
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_DETAIL_STRUCT_PROXY_TYPE_HPP
#define BOOST_FUSION_ADAPTED_DETAIL_STRUCT_PROXY_TYPE_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/struct/detail/namespace.hpp>

#define BOOST_FUSION_PROXY_PREFIX() obj.

#define BOOST_FUSION_ADAPT_STRUCT_DEFINE_PROXY_TYPE_IMPL(                       \
    WRAPPED_TYPE,NAMESPACE_SEQ,NAME)                                            \
                                                                                \
    BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DEFINITION_BEGIN(NAMESPACE_SEQ)         \
                                                                                \
    struct NAME                                                                 \
    {                                                                           \
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED                                \
        NAME(WRAPPED_TYPE& in_obj)                                              \
          : obj(in_obj)                                                         \
        {}                                                                      \
                                                                                \
        WRAPPED_TYPE& obj;                                                      \
                                                                                \
    private:                                                                    \
        NAME& operator= (NAME const&);                                          \
    };                                                                          \
                                                                                \
    BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DEFINITION_END(NAMESPACE_SEQ)

#define BOOST_FUSION_ADAPT_STRUCT_DEFINE_PROXY_TYPE(                            \
    WRAPPED_TYPE, NAMESPACE_SEQ, NAME)                                          \
                                                                                \
    BOOST_FUSION_ADAPT_STRUCT_DEFINE_PROXY_TYPE_IMPL(                           \
        WRAPPED_TYPE, (0)NAMESPACE_SEQ, NAME)

#endif

/* proxy_type.hpp
zDTWr6Zlx+xMhmmODeT/ljlhIlOzcpePiPTIRao9tjZUpxB6q9/mVeAcdHl0pT/462NX6OeJuaGRHhjfN/rll6LdUkDNcA+VXk4EmQLtIVZznLg4zb0IG+WChk7qtsc5C91aLpdr/pK2aoq9rpEM4xno4ikOAeZfG0m+g5Tc7RWubg1++6EV/AT+ogD+Kl8SIVP6QFrQ7aUf/J0XM526n1F5QartCPsZgjS2DT2ezAkG1JiCppOMf0+5e1Fd+GoBw+W5/SA9CgOsubuG1Mq19gB+tc0J3nugrn2fa+BQojwiqiV+43QJ4kHVqQcViF6lReKJb0GEYpSsZUYv8BTORcnO5z4NOGUG0oE0HGs2bOvp3hcdsEw5tefx49H6VuuWITLaurQBsQ9N52JYHXJ/eRwMgNTERXFjdEubfxSSpppLSN/r8bNfUNUSivua5j02BEd8J8L/Ek1HNJfGQDKvqUIku7BCxWErWwRKbNudM19BcE9MwAMOGUDPWjI7Qgv3/jmhVr+wUDw2oBcflICogB3jKNkwPzzl5IlidIGAO/6dYgzHhZ5YjUQNnw==
*/