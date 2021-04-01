/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BEGIN_IMPL_27122005_1117)
#define BOOST_FUSION_BEGIN_IMPL_27122005_1117

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/boost_array/array_iterator.hpp>

namespace boost { namespace fusion {

    struct boost_array_tag;

    namespace extension
    {
        template<typename T>
        struct begin_impl;

        template <>
        struct begin_impl<boost_array_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef array_iterator<Sequence, 0> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& v)
                {
                    return type(v);
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
RF78hx72+/pXRzE4M56n+QGN0Uev/XSpL1TBM6Sv4hTVnYojTb5quKJJ3T1M/ns1eZZ5nAP0+DYAw05FNOIkh7k3AsaKeMcTO8dm0nh0MdaepYcoZ+4vO0oZf89lIpthQYhsfzqsJAF/ZHxXV0x0WcDII3xIrsp4Fb5xQx6MpIjaL4RUKZZiJxA/mYuEAA/hmswXlsoSRskAhUAaHTX8EgicrsCWra7R0g+84p/QJF3avPdbQXMlbWUnOhhEWHy5W2S3RjVP18LQVY7b9zKLMgVOj7YbAHuFTw+EblWAG3d8pliXi2lQSzu8ArGWM/b9m25Op/6r3jxaaBELqePkMHRQPR29LyfGpOcx577QSEUYuCnfUzwPRiC1rV/6qerVqtwZeGPJ346WGwJS3t9ghUK1bJn6Mc7rbHn1XoXqLQ8U/R1YR6Dust0GYeGxo3AKlbho4GR+QxlVRnwzhW8GL7//sKYKUrzHPxc4VFGTqcYspy5pC7jyqqbYPUKGNS51+4bYM/S30KTUXwOsI4jatrKpN2lO5yRLmyzw62QzI+7iRZFTUvWJ4BZ3OA==
*/