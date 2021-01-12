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
aD4oNG+8bPz6/sOTXP+8rxn+HWGR6/UW18X9022vddM+43Zvk/PsLs/v60Xu59e4XhVkGh8brftfMC5PcF74PP0C4+RC8/WSw+ZB4/ydu5wHVZ7P/HjU9k173fXYOmzTTfab/T+r1vx09thx4wbXh13GY4l5ZYbr2R73se4b3xnfTzuu6z0u6PA+zTv7P/B5uX9f2vAF889J1ik3R7kvc599o/XbZeZr68UDj/r51gmOc6vz
*/