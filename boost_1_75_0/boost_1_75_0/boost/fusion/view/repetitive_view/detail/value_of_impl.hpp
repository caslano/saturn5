/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_REPETITIVE_VIEW_VALUE_OF_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_REPETITIVE_VIEW_VALUE_OF_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of.hpp>

namespace boost { namespace fusion
{
    struct repetitive_view_iterator_tag;

    namespace extension
    {
        template<typename Tag>
        struct value_of_impl;

        template<>
        struct value_of_impl<repetitive_view_iterator_tag>
        {
            template<typename Iterator>
            struct apply
                : result_of::value_of<typename Iterator::pos_type>
            { };
        };
    }
}}

#endif


/* value_of_impl.hpp
B1RnwybP6WvvP+RwX/xVkxDqqHXbfg8LM7q2gZg9rAc0bOiGZnud/fLhUs2DVHk9m5OVay1z1oaTJyoDgzbeA5iSRkJt7I3gsOsdWeoJ0vRM6d++yZ0Hf0gQfgY8SK3nOMW9TopX53KebshHyWqJRlTWuxrk4O3/2TGo5VQX7rStchd9LltJ/db2H5XGlQCv813LB0IOlF/1oohNjNcDodpLZ5W4wR+1Ry1fx8eZN+PboQGdVJ2x8NQE29vhgVfMtP96pAX2NCbcQL06hlz5+R9+Le4c7lLEYprazn6LvMulmTNc2ciRY3Ko7HcBlUJr6kQbx7SZkMVobDluczp/Kg8JcNF45dugZSjxQrFhzW29s1371wt3eyndCLHZ4bfPgZeCpQ/46WCcXQanNMZvV+kduBKSiOEpGbkux1lTEkJ02nszhyQwlfV7qs0ASvhJNRmTZSeFiLCn+IvnVDAqUVL36ne22nfkZw0cr37vPki+m+xBYUQLLr7r/zJ7OJStbHJ9z/rW3J66ZHq82cqciAsNNk0RtGZMWdXnajJXnhrBDiWvm/f2hppupfazcx+HSd0wxO4hOk83tS4G2tSvj7XIHBM8PCSh0FZu7fOAVJoywP6LOTyk622gTMKuDzC/SQa2y058nQqZSu17irgDxgBRwlrhzSdnRQaTcuI/TVyv0T45ey8378asYkngSRPRSxAB0OjZXjwPqtjU
*/