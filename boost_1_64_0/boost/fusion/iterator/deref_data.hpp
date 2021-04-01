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
cKBITujGBAKTYGrqfEUlbunKlsiGna4p6yORSgEMHUVLRHCWftdyjqTi+F+i5cYxkLnj0RQhCF/IMUXS0aqITCB/EGasJDKkPY2Jq7J4LTlfpsbpw3aJSx4wlJj69YCV88yaukyftx1+UQ3rybOmdxKsx7mDw61JFvV1hxAhVVcHJ7Heq6WoLRT2g5R/hODkj1RYrECAetsB96p/3mWl3z2tOaIMQB1J/WSvy4x6XO9baJ5Apro0xLDhiOv10gyCTlPyPN7oIkZ7ozLf4GnYb5xg0ukit+PJKOri6ti1svNEYHpUjKX7cAPhdUhvygEdrk9Y5HMQXXHDX6M680ohJxWzSDi8zTaEB7aurg9cYrV+Xl87sxeDNTN0N/ThjO+VRANjT/UWtQGelu+ZDNGcfjUtmYb5csknii8P5X9qGihj5z8ttxNl0BwsruztQMF8++E7CAd37349lP7pr5qRNnBqWnAP+f+OHCkXshpWppn08yjc8bc6o/FRBTY5jx3mGHMTMa9TCr8HSUc1ke4FafWeJetZfUnduqjARvMBFSRCBmfJNt8f+RIOOQ==
*/