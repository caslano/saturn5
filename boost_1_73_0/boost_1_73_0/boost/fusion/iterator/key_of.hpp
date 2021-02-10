/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ITERATOR_KEY_OF_HPP
#define BOOST_FUSION_ITERATOR_KEY_OF_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    struct iterator_facade_tag;

    namespace extension
    {
        template <typename>
        struct key_of_impl;

        template <>
        struct key_of_impl<iterator_facade_tag>
        {
            template <typename It>
            struct apply
              : It::template key_of<It>
            {};
        };
    }

    namespace result_of
    {
        template <typename It>
        struct key_of
          : extension::key_of_impl<typename traits::tag_of<It>::type>::
                template apply<It>
        {};
    }
}}

#endif

/* key_of.hpp
vonSA11W1kjT8HnIfmwMS1Re+JlEeUUZdCjejE1CZodm3IJl9KZWd85rbxrn/Pz7Vr6rIAz25GSagEs8jUIPPUHfwE/nrJSxTMpZ4oI97k3vS2xzKbKaEXIVfCZ2T3KzwkbMXDHg5w5uXVTiU/SMSDX10fYPxvdAU+QC9oJRZSpcs7NHkFEiwZgRHhj4iiUUt+VFAsvueWNFgC/B8tlwaY96pxhFrIiCrgRZ2jFoyXtQ8+Lo+fOXGHdg70Z8OtzfBwv56fOruSWeIy1Iy+cCnABl9b5+/aJcJgxngGEkXpCYof7WgqPAlI9TLgvv5uAUr0+7R/KL8l3aXiO1AOdxT2zjIm2C4xQFMtnW4BWjEiPsCbRstdkKas0fooniwgzPIoFCC9w3ZamkBizZORVY38AYWitC8QgU+pjjKspsR0U5hGHGxnEezgKSgDwAWyMqvE6yWsVypdgxQwdKe3gsYLbQr7mL/EQ6Xl95NrchqhTlNMYVLYrwzXwJYLX0K6oqMEg0ZWdQPQatPya340R5H9wAEQL5MvNgNVD0QOxAMc56rrRMILXCPMUgADzCQElQghYVkWKnu8p6lAfUVn3RVWj4MFUe2B9A6mEUTgQFUPY9kMFSURlIhfZkEOMkWMYRUl3Rzg8ScggHsHI1
*/