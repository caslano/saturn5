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
A5jVBmP+tWTiBtiIMljHn9k61gQhbmd6I9gwLkqhty6xaRai9hE2zj3rM86I9b1VYn1LOnOuIzq/kPlusGYwy9ZbvbB2T4FiCh94WcfmU6z0ILpVjf19pCAAffv6l8n6GGx9Ln8Zrc9JsD6b7qStnUra2ik0t3ZMm3NyHmn5tAV0ffkrsDmtepHNeZbvPrWAdOvbeXT9hq+L5p1T10bH1NG1o35H5hS5vwO6NniSpWtfk64lXIe6Fo7RlY5l/takaxt9UtdCp0hdO5CPezvV0kkd5BB17QmJW4+6Joa43n96G9W1L9YH6Fq7F+W+Tmfc1xF1/fIo6VpCIGI96doNIxmwvqAa8epVXcter+ja6KV1de2lqaxrE6pZ16pY1+6cKnVtwmG3tVFBmzYf2Gitbz4wWAmnqeL8C4tzWrA4g3OohV//o5RpOWnYdrWlUfD+ryzTv9Ur0/Kt3Gvr0aijzEI6sWDU1aj9wbXfcXWgRjVSu2G99ds1pkbJGU3bKeaMRipZ2BSeb0Cvzng0QKOMctKoataoXeWWRo0fdC6NmvMx6cxNPJr3+Rw0qjKZNCqJ7yZ+SRrk+ZiueXzN/VjGmpm4iO4cwhkqGp4jt4N9tyapuIczJpu4h4Th9mvr/xHDLbQOhptE+v2ohYmck8XnOsl+h89nhq2+UaoguPXVKL/mNai9l/0HauvQ/pMwujEvmAhufX0mglv82ICw
*/