/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ADT_ADAPT_ASSOC_ADT_NAMED_HPP
#define BOOST_FUSION_ADAPTED_ADT_ADAPT_ASSOC_ADT_NAMED_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/adt/adapt_assoc_adt.hpp>
#include <boost/fusion/adapted/struct/detail/proxy_type.hpp>

#define BOOST_FUSION_ADAPT_ASSOC_ADT_NAMED_NS(                                  \
    WRAPPED_TYPE, NAMESPACE_SEQ, NAME, ATTRIBUTES)                              \
                                                                                \
    BOOST_FUSION_ADAPT_STRUCT_DEFINE_PROXY_TYPE_IMPL(                           \
        WRAPPED_TYPE,(0)NAMESPACE_SEQ,NAME)                                     \
                                                                                \
    BOOST_FUSION_ADAPT_ASSOC_ADT_AS_VIEW(                                       \
        BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION((0)NAMESPACE_SEQ)NAME,  \
        ATTRIBUTES)

#define BOOST_FUSION_ADAPT_ASSOC_ADT_NAMED(WRAPPED_TYPE, NAME, ATTRIBUTES)      \
    BOOST_FUSION_ADAPT_ASSOC_ADT_NAMED_NS(                                      \
        WRAPPED_TYPE,(boost)(fusion)(adapted),NAME,ATTRIBUTES)

#endif

/* adapt_assoc_adt_named.hpp
nCu8Kk7ZQi8HjQkFPeRuv+6B9CraGEoPpBxwJanIMYaN6QhhyjbmkHFhTsDZzk8OSBA1Rqch4RmsQ8/0rUJ9o2CXYpm2Xkuz6PiVjBjz/kLDLDIEIc9WU8jWSsXLqqdhCs+im0/A+e9YNY/jY43JTx1+3fOjzBQILht8P5rkBCU/3anZeB6i1aHjHdKw4AdeeST/eakps9FuMf8aj79zFzfIijiV67ULyS0kryoFxtcGh5Q6Ho0tMjrQVoq7GAznzlBy5ggfT64seaKtf11xqA8sJqTJheukBz096HAENxRDMiq/7csEsx8oWUo4X3hHGjskjVZq0ncmN0ULbThN4IIJv9Fakfi93nQPKdSuXSCvmdI4qZbzdCHfNe/3kT/y8+QE1/U6GdVo93y2di1hKMwyWrtmaafmG/zgOo1R2vDbxhj9dnr5dCiMx2h5MuQaRN7XHhlg8ty5B7ThXQao3LVzxhEYQiCbyhNOHlnrBeBzE68oKFDfF5uRA5ugbc4JeAHcZHBgg1jHMtVXhuQ1/c7u4+UarypWa3zb2+Y1ht91rfGieVe8xn94aY2bW/WVBOZtk9chw0nBIIY8bcp5X+JlnlPmiZ7G1bMNxzxwAGO8xAGUGMgF1H+O6+cEcQwPec0cg2RXI8Q+eh1mf/MyprVbu18iSHLIfyWVrZlB1PVDprZT4Kk1vI284kbjrzD4pV1IhrJy7dnZUHYi
*/