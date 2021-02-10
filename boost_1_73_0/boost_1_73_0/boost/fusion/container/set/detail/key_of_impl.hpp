/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_SET_DETAIL_KEY_OF_IMPL_HPP
#define BOOST_FUSION_CONTAINER_SET_DETAIL_KEY_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/set/detail/value_of_data_impl.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct key_of_impl;

    template <>
    struct key_of_impl<set_iterator_tag>
      : value_of_impl<set_iterator_tag>
    {};
}}}

#endif

/* key_of_impl.hpp
9Rf5i72SRXgh5TP+nfM+QX+gbvjHOZb8g+Nf4SdQDEuOwmgXe4+blL0avWbvPn36jb1hF79c/HLGxk7gCZ9ZqQiWIn48Y59X8if/s3G+f3+biH+eMZEyx39boOyNl7AkXKfPTiwY/N33XBEkYsWchK1E4sbeEr7xApZuBFt7vmAjY36v6ZMz9rzx3A1CdmHGkk2Y+Su2cZ4Ei4UrvKecETlxysI1FAf4yktSAGapFwZvQbZgqYi3CTJQvOMnIXOeHM93liDISdkmTaPkv87P3Sz2QfvzVegm525Z/bebdLuvyT0osXV2LIxSloYsS8QZwyfP2DZceWv8Cg0CP4yype8lm7ODNiAqWJ2HMUuE7yMLynkiydUWzCqa5wwfYxFo7KX4JQmDBEU9b8LtyYPQjkhZZ3EAgqAd4KFVCM18xjIYWrF8WNa8FFG0qWzg1q456LtiYQDKsBeKxTTrBVs6iZecsTvNvjEWNrtTTFPR7XtmXDNFv0fYF00fQ9d7ICxm4nsUiwSEx8zbRr4nVoXMv+/X+U8w+tl//2e/GGDOqwPlBjvBjZ01NoMbBmvvMbfLNVTn9vtdGH9LTkvklL9BF8RMQ9dB88WeAx/oZH7KXIctoWNBh1zUz5l0oLlTVPjVQh9P1R5A5KSb5uJz
*/