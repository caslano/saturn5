/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_SEQUENCE_IMPL_09272006_0726)
#define BOOST_FUSION_IS_SEQUENCE_IMPL_09272006_0726

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion 
{
    struct boost_tuple_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_sequence_impl;

        template<>
        struct is_sequence_impl<boost_tuple_tag>
        {
            template<typename Sequence>
            struct apply : mpl::true_ {};
        };
    }
}}

#endif

/* is_sequence_impl.hpp
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
*/