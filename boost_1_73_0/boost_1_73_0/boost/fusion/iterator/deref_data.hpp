/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ITERATOR_DEREF_DATA_HPP
#define BOOST_FUSION_ITERATOR_DEREF_DATA_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    struct iterator_facade_tag;

    namespace extension
    {
        template <typename>
        struct deref_data_impl;

        template <>
        struct deref_data_impl<iterator_facade_tag>
        {
            template <typename It>
            struct apply
              : It::template deref_data<It>
            {};
       };
    }

    namespace result_of
    {
        template <typename It>
        struct deref_data
          : extension::deref_data_impl<typename traits::tag_of<It>::type>::
                template apply<It>
        {};
    }

    template <typename It>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::deref_data<It>::type
    deref_data(It const& it)
    {
        return result_of::deref_data<It>::call(it);
    }
}}

#endif

/* deref_data.hpp
CmqLUCUky01usCfXjmwHisTH7zqEsUlMfcFRch3nnnvOPVY80LWtqMbZ6WhyOhfjq/m5mEzHS3GWDXhdW3rtU3HwdiPDAXYO0d2CB8cOcendLyrj69lCPOLpYtQNx10kBV4gj2IfuyGP2Osgomc5SXMhdhHdJG3pUSTkjUhTXmFYQo5d8+D1rYrYG+/jw/HxR7zH0eHRYY6JtJoMFpHsmvxtjpOqW/mq5HY7DPQlB0VIM+xLLZUOCK6O99ITeG50STZQBRlQUSi9XvOLtoiKUGtDGF9crqazHznulS5VKvLgWgTlWlNByTuCp5L03VONRvoIVzOci1c6RC7YRu3skLkJkfwmpBqJXprgIO+kNnLNRDJCxdiET0VRtt6w+qJyZSjK5/aHKm7+dLJiERv5ANdERIc2UI6UmWPjKl2nyIbwYtOujQ4qf1HDVLYqnEcgY1ItxmkKT7IJi96ePKWhYcU6phCcDYnqXrnNP4nsY6pSt94yEfvASZVjm3O0/Bv5Lrnr/Jmi97Qz+L9b86K3grMsBu9GC0wX77CWQYcc19Pl2cXVEtej+Xw0W65w8R2j2SoV+zmdTXjrNZN50LbxFJjcQ28ao6nqOd9uFFk26M+M/kRYjL6dn3YnQ0Zbbt6yyzZEcE8t/6Bj3mGh
*/