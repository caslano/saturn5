/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_DEQUE_VALUE_AT_IMPL_08122006_0756)
#define BOOST_FUSION_DEQUE_VALUE_AT_IMPL_08122006_0756

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/deque/detail/keyed_element.hpp>

#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/assert.hpp>

namespace boost { namespace fusion
{
    struct deque_tag;

    namespace extension
    {
        template<typename T>
        struct value_at_impl;

        template<>
        struct value_at_impl<deque_tag>
        {
            template<typename Sequence, typename N>
            struct apply
            {
                typedef typename Sequence::next_up next_up;
                typedef typename Sequence::next_down next_down;
                BOOST_MPL_ASSERT_RELATION(next_down::value, !=, next_up::value);

                static int const offset = next_down::value + 1;
                typedef mpl::int_<(N::value + offset)> adjusted_index;
                typedef typename
                    detail::keyed_element_value_at<Sequence, adjusted_index>::type
                type;
            };
        };
    }
}}

#endif

/* value_at_impl.hpp
MogU14cWQg6el3tDGuIBBS7z9cj7C9taKm7X3rnrW7rzWDCbH+PZHS8qd8jAcng/dqfZUrEY7nid3/EF3NHDUrEULpbwi+/Cxbji+iaFN1gq7tA+aCzv8UKwQdFEeI2kbvsSplyJo5QrBbgnw6wJTC6BKlZpyb36Fl4AXoh+f9spdxxwEIw2A+KBC85BF13mwy9CLagzuLdJ4yl/Mtl+Qwn42+Eyf8WeB0b6pqgcegbu4LRF76e8xeJd9BbVjFy2U8CI0aC+kGZclG4f4eO2wHHbvxil/ZigD7bXPq95AaPHF4jVvIAbOFEcnHuDwH9epDPyDAvgQYXlpfkNYYElo0AIm+RFz6VNspWkqrqynwKVb/XQfFKlKXEi1TzGZFMgZvOAi0aoi4VdVosuGGuyIpCTfDVP7LJIHTdsvuo5wQA+UU46OCvPKM7YVe1nDGFdd5lKJLHRCiaJzBYKfwLZH3e9vcp/bNGC/dEOlFaINko6JTVUQBcVDQwXlorAB0ihhkt10VbgzIpTRqbI0eTkCQ772C+5oLPI2IbOznyGfyJMNgJ9uzj6oO6dFn2BKvp2cfQVaww7iL5nQVR5mbM7HQhLV5zTg3BIBaE/DbPOKAZPUlyPPAF2c+OARbsDFqQ1QWUmEy9mXNcXE4idB1k1N+B6A949BeBSvlrDy1HW949o82H5MJWVcokjHRhxgFjmRLzRRCNs/k/bOmZI
*/