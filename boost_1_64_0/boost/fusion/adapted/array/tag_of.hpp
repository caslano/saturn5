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
PLtr6HBnXZ9L+ES1QkEPJJTVBvsKeI943HFTtC+J/p9Y+s41Lh9nNGvxeI6sOfhS70UB4w224ODZi7LOBW4gvj7YuCKPsgQZ9TGC959w7aa9nMEkEirWn17raenEkbBIR9+Og5Bl0K7HrkOGS+PCytcIZJ8r33CdywU5/jeur4f/7j7fJvicWabYDoZRJ+wdA90wddHL8CdkhAwOkWjabWgwrWKnOFG9mtV4rweC3ep5gKrd+g3rxn4FajJrTOZndDPqUkGaMzP2IwKY9N181IP8bFEh98unFTMVbBCaNh6GQN8kVOxCNSdrmO5kjBiKR4Wfk8KTIA0pML53s6C9bxJhlPd5OHhquv7kfD03ZAglSVKvZ9gDiKrzVSMo67BuYf/1nmDI7RXF1yoF/6w1WzGuHW+Tal+wU9hd3pFue7Vc5+NUnGwPYwYnvCkd6eNzC3aFan8xRhHRkdoWFB9A/8TWGWcpoWO2ipWZezLjWPoV16X5MH5EDGNJ5YaYnQ7KDVefiqeQkpSVUPPRK8600KRarvFSf7bSztDQ3rbqrZgIHT8evwZtXchdLA==
*/