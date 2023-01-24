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
Elsn8T0H57QCT1iZVQm+OYsu8r1Jhu/SXlsRY4hu0yY4XVz+1e5SG03nlTZgxzn5Q5CzuudZ8yFZISZSY+/2vMtER5o01UHpdjfTaWcvHm0h9TWILQuaYq5dTEcHiXZzYKwPhcsKlGVX2TlY2Kta5dmFplSe3Vbis6o2ICJzpPs2yTHKmCNSTMo58JSKj0a5512jLLWBoZLMCyngLIXhbK0OZ4sgE+smC3odUFpZgRHhFJwGgw3r+cOStSNzDOk9xL3wXQeqgpM5DFIhamlBIwQtD+F0rYRo4dJqWg/d1N2GhlBDEwsL2qT7IlLHPk7uJCMs5PxCN8kdaEclg+M1t1mMUmB78T0XBEFz/viOQ/VV2UYUqbyWfpt39RWgzsR4an9d2P8AdT4LU6hDfTnnNDWgzlth1GEpo85aE+qUMuqUKdQh1XZOGMz6vIrAcDnwPDmFwbP0isHTFnal4AmxQhV4bofwem3guHCIdZFjvDLw7DTFJOo3VSK9NK01ZWmmqbBGmxZKZXAuM74rM79ba3y3Vn8HsF1fgbVONhoEnL7JDpkoGAnQ5Mm1PeeHTDZ7zm82drPZPIRdxne7zO8qjO8q9HeVc5CRCxD+pai1UMpTND4aFXHGiHxH3gb11etUnZSj5RQfkuDo5hCJXfZRi84TRpToBLmECfLEiYyutpCLBnmYOILrQLA1Tv/tUX4mAsgatt0ScKaLAeF5
*/