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
ZpjDMtEpj08QVyXcMphfIWX8h9PqGGiisYsfjT/6lXKkhUp5Jzw0jT9yGiv9vl74O319D/oZiRyUjTDc5OGP89C/wqnhaw1WqeWsol/9jOFpqixU1Vqjk6po8YniLdzkDQPFt3Cx4yNcE802NZuvuqqMdSVeYHOLZ5PAmyW4gWMulfGMUINkwg0cdomybXEl+FVP4BxQNZHhH6NJuOgB/UqzqQiXjICZrZzCdStw5xMuPsAp5yddZoJpuSfaIRBkx2hHrvYjlD1GiGyWm5Mu989GaNzGa7ZoV4JFH/k4LP9zgeSPwhOt2faNIw8zH+t22sXtzpI5Mg8TvbMSUGMI/T/doGNboNx98mYxHT+k/3pA/1V8M0nfwptxEXkLf70RnqryRyve8F5DkS56OHmaK+n1MnoM56FD+HMgf/bhz4o74i3bAvAzuBuWzZ/pEh6GCeJnqKBbWIiLgm9SjnrJfaBme0wGXDOU9itG99f9OcIguTscpf0ZjSjt329EaR9RQdIeEqnxTpL2jZhVhmzy1KD2PV8yRBSXT8Ayt16doAsAIfbpLSN1DQn+oxKI+UNSSavEZ4A2iVs8H5NobJH7GHL7ycHB6Ke4ud0jwcj+mDsgOvPTUf1RxhSDbmle1mINdqJ325xSRQ3ORurSB0g+Fzdfjt5Omp2MzJvg5P88AqYoViuHEl7LUsy6JjuiCvUYpqNfGdV6ptVU4Ckg
*/