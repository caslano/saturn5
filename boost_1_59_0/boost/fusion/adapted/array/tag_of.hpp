/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_TAG_OF_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_TAG_OF_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/tag_of_fwd.hpp>
#include <cstddef>

namespace boost
{
    namespace fusion
    {
        struct po_array_tag;
        struct po_array_iterator_tag;
        struct random_access_traversal_tag;
        struct fusion_sequence_tag;

        namespace traits
        {
#ifdef BOOST_NO_PARTIAL_SPECIALIZATION_IMPLICIT_DEFAULT_ARGS
            template<typename T, std::size_t N>
            struct tag_of<T[N], void>
            {
                typedef po_array_tag type;
            };

            template<typename T, std::size_t N>
            struct tag_of<T const[N], void>
            {
                typedef po_array_tag type;
            };
#else
            template<typename T, std::size_t N>
            struct tag_of<T[N], void>
            {
                typedef po_array_tag type;
            };

            template<typename T, std::size_t N>
            struct tag_of<T const[N], void>
            {
                typedef po_array_tag type;
            };
#endif
        }
    }

    namespace mpl
    {
        template<typename>
        struct sequence_tag;

        template<typename T, std::size_t N>
        struct sequence_tag<T[N]>
        {
            typedef fusion::po_array_tag type;
        };

        template<typename T, std::size_t N>
        struct sequence_tag<T const[N] >
        {
            typedef fusion::po_array_tag type;
        };
    }
}

#endif

/* tag_of.hpp
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
*/