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
b0BFWDKB9v/lrL1EzB642IGFauupFID7r3QnUrPtUM1c9d9rQg41Z/JgGb4gqhs4ro+uGy9W83Sld7qh1pEHGfRTcdbavinGKj0nwD42V+EmUiLHtZylreQ0y6a1NPlIRn89EgsTjxGmurg3evsBsr2NOoeqWDuby4wJvWiD1DyZCXr0fkB5F4dyCQUEhEnBDrn0KMS/05+zBLi8EEg1ttMcSzduxb11q2x/OtBqHWOu/dE0Afqrd2EObvlw9OJi+/70SSNtr1KqWMvDLLQhDEwyslyXT2+CheuvCzr39n4t0VdOIfkfsi1++i79XRqJibuP5NTbpwooby/6InKnN/nReEIqp8hn2gFcU0FtFAY+Ju/RJqu1m8jP3/l0b9ksTnfG3W+4nGaZe0rPIfQCira8A259HmGxe61ti60Q1MJfWIdKe57wp9syfAOB40vc9H3dAmKXjs2kqQgVLcNVRO3U4yqSPTc0xUPi7UK5V/+Rj05G9HJwmkObYIwHvG4/KnGphbdWVz8GTLkiov7aOWjktDEkXsXrAfK1HcYSvtPzTaXW7OhD+lfNvQ==
*/