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