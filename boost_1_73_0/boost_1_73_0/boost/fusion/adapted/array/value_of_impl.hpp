/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_VALUE_OF_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_VALUE_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/remove_extent.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_impl;

    template <>
    struct value_of_impl<po_array_iterator_tag>
    {
        template <typename It>
        struct apply
          : remove_extent<typename It::seq_type>
        {};
    };
}}}

#endif

/* value_of_impl.hpp
7A0uWqharhhYKbBqYDXA/hvYvcA2AHscGClPxlItg7VildoPMQ1NJvWVCXrE3u6GphV7c8qK5lYl7BPTMKPKdZ29oun3Pmz1+sGzdMvR06W6UE9vsaO2u16p1kOvVOupV6r10CvV7kPj3acIOxnYNGA1wJYAOwjsEDBpBt5lOUxsp3+onS7JVHrT7R8qLZ8zPzqoTiRObGD/YBefFhp/o6JR1GPFg274IUY8WmZi360Dq6/pwCbgPdqCOADaHlA=
*/