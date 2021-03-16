/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_VALUE_OF_PRIOR_IMPL_SEP_24_2009_0158PM)
#define BOOST_FUSION_VALUE_OF_PRIOR_IMPL_SEP_24_2009_0158PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/container/vector.hpp>

namespace boost { namespace fusion
{
    struct nview_iterator_tag;

    template <typename Sequence, typename Pos>
    struct nview_iterator;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        template <>
        struct value_of_impl<nview_iterator_tag>
        {
            template <typename Iterator>
            struct apply 
            {
                typedef typename Iterator::first_type first_type;
                typedef typename Iterator::sequence_type sequence_type;

                typedef typename result_of::deref<first_type>::type index;
                typedef typename result_of::at<
                    typename sequence_type::sequence_type, index>::type type;
            };
        };
    }

}}

#endif

/* value_of_impl.hpp
V+kGNEPnP8cyDWQOMe8swW4Q7HeC7RCMDLgLZiV0kt+WuN/YDXvCPXm6ANdrsgr4JKtRxY1zsnBGLg84KbfTfd++dFQ4xb50RWp4pt3ZCgwOI/Gj3eu/5BOTYYCfqkJ9cIoOhlbptvsh5UK+hzt38ri9s3v9XuNZ2KUHx7IsjqZgw1CH9hdHB3PoQ+R+5lysycI4/gLB1OUEhucVb11FOiAJfy2vqqmaFyqfF162rGpJ6CTTbQNkNxJ3CQ+oXpA=
*/