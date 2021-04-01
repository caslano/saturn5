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
B2HalRBfqv7aE9oadOwU3yhn8d0S5EEXPnvkefcVAX3FIldq4tGTxTXzAhp7/tzPNaPdko4aWZP65D4PikVWy2c+b7OMZ0avEY2vk94nD+lJrNQ+lR/byK++hEJSNPF2yRwHQn8fx1tyciPNasj+w/CUOmXvhjZr4Eb1zR0+37TGs3UvOZOBeI+vob/pWExqDyUTgR0HdlELwUW5FKgctwXszl6aBaLe9Pce+QKOSufkV/jwBK39LvF/19yZw9ei0/BcsMlHGJQ9xS5AByOohPA1549wGnyPd41FqAJ6BhebZyWp1TVkzBwUCSNKhuyTtBXGSVHTG2ueK/+/Lg5atNhJJidlDICdZIBN8F2hVkPY3amLY2nj2StVNOdYDxEnDuTJCLMwQxykWrDmEar/JtXRBmyljT/Jdn42XTD/VevhIOQqZCNPD5LmiOn4ot3lMF83n11bxT3VljUmXVAnMSyqupG2ndejqGePUivyuvTsunqpKw8yftR/wd6MwlKsh9EbVl2CmPG25grfotHPwBCIJKviZEHaT93CxbP30O9qRx6du/BBYvAPmg==
*/