/*=============================================================================
    Copyright (c) 2001-2009 Joel de Guzman
    Copyright (c) 2009-2010 Hartmut Kaiser
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ADT_ADAPT_ADT_NAMED_HPP
#define BOOST_FUSION_ADAPTED_ADT_ADAPT_ADT_NAMED_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/adt/adapt_adt.hpp>
#include <boost/fusion/adapted/struct/detail/proxy_type.hpp>

#define BOOST_FUSION_ADAPT_ADT_NAMED_NS(                                        \
    WRAPPED_TYPE, NAMESPACE_SEQ, NAME, ATTRIBUTES)                              \
                                                                                \
    BOOST_FUSION_ADAPT_STRUCT_DEFINE_PROXY_TYPE_IMPL(                           \
        WRAPPED_TYPE,(0)NAMESPACE_SEQ,NAME)                                     \
                                                                                \
    BOOST_FUSION_ADAPT_ADT_AS_VIEW(                                             \
        BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION((0)NAMESPACE_SEQ)NAME,  \
        ATTRIBUTES)

#define BOOST_FUSION_ADAPT_ADT_NAMED(WRAPPED_TYPE, NAME, ATTRIBUTES)            \
   BOOST_FUSION_ADAPT_ADT_NAMED_NS(                                             \
        WRAPPED_TYPE,(boost)(fusion)(adapted),NAME,ATTRIBUTES)

#endif

/* adapt_adt_named.hpp
CaiA5dYTwCjjEqRYqjWrEOg55wkWElNgElKUScUX9MILUBnCkucI42Ayd/0/TFhnPMk6nI2oQWaizlPI2B1ChQnyuxamZJUCsSQEwk+5VIRZKy4Ki+gRFFYr2cHoIlguBbA7xnO2IDqmIFOqlO+Gw6SuclrJMBWJHCZbKaxMrZ6tak7VrNgGRKlACaglmqDnm7ASKV/qkSSiYFkvci4zc1cWERbpUFQgMc87OErlKNslIISdWqaeCSVVz5UepCikZltnYvVkIsnaAS3rqiA6koXmpYKEN6EuUqya+Y0QW5ZO5UbyV1q2qz0FUVBV0LNDcMMeLJjk0oRrN7oIZhFc29Op7UdzCD6B7c87vEvXPydvcGKtAO/LCiVVUQFflTnH9An5D93phhVdwHg29YJJFEfjSXzpOBPXj648OILewSl8rgsy98HPPejlfKG7DyfW0Yk1ooB+i5HJTSxR6T7TTZaShBpegG9/cYyXoW/2qbUKKAh/I5b7LCefksFJ/TuWN9nh3A8moRsaP/EiyesU4UzTtf7LPhgNciIo/ryKvv4Cexk5IyeDvFiBCbkobr8xDt43nOdOOJ66k8gNfGPCqAOsmWZBiEo2jtgmmHo3SkxEkVJvVUYbRH8WZEGmOCHLjVS4gjUnA68ZmXOB
*/