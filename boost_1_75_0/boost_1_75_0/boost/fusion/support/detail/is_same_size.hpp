/*=============================================================================
    Copyright (c) 2014-2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_IS_SAME_SIZE_10082015_1156
#define FUSION_IS_SAME_SIZE_10082015_1156

#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Sequence1, typename Sequence2, bool
            = traits::is_sequence<Sequence1>::value &&
              traits::is_sequence<Sequence2>::value>
    struct is_same_size : mpl::false_ {};

    template <typename Sequence1, typename Sequence2>
    struct is_same_size<Sequence1, Sequence2, true>
        : mpl::bool_<result_of::size<Sequence1>::value == 
                     result_of::size<Sequence2>::value>
    {};
}}}

#endif

/* is_same_size.hpp
7hcUKTaty1X82FV2Wh20TqeeflRMwHIYogMYnQe8oPANzPVyqQCNd6jsIlbJLoVqTa6VhOqFRFQJaD3kyjelyDeRsECzwo5tSL3cYydOSRNkqzlis2Z1fuhWy7D3QmZLrkDppSUpIpItyWmNW+ftLD16rJScg/oGWp+4itBVRIpHpRSRklEDGklosenK4gFwPUBg3UM9JhEVX0TKRRUX6ehhaEHgBxhOEPg1ISjyznSOGlHkBL7L80MXqUqDDWP0m/SCLmxjordKZ/1EyW0ReCmcSrWUGLlIJPXKn/rEWZDALIbLt7qkBYlHM1QbZINBdOLkosM0QlAXy1WgF4Zh68EGW6WnVm9Q7aB1niteAx4ReCOSuiMlFsx7HMFZvMl9lRX96uiuFMtNclGs3hUZ8gOMLIisj7kBIhti7oOcb3QpIJHM0/HFA4VBAush2NNVzpUf0j2NvH79hqv1CUi2/+ujS5aYHikaUPUXWDe7PC1l753ZJdKA0JnBkf0Ns/j/RyjMBlcfDRT0kEWvzsxElar3UmEbRvHA6byigbBAgXVBNW0gFomx/xcYZGFAvKrlVTJNV4qbsK8kzMZngUFvxMj/KZxYtaY4uY9TWC1reI9RwbRv1KCX0+NXq7m38NvlQftnUt6wREStGH3YKtlMKNLiwC3yn5OWeytEdaOZwePVVD+yRMY0txgrZlBY4ruitTXr9CrH5dt/wR64
*/