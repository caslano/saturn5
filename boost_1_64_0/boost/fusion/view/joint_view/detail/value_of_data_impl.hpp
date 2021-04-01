/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_JOINT_VIEW_DETAIL_VALUE_OF_DATA_IMPL_HPP
#define BOOST_FUSION_VIEW_JOINT_VIEW_DETAIL_VALUE_OF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of_data.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_data_impl;

    template <>
    struct value_of_data_impl<joint_view_iterator_tag>
    {
        template <typename It>
        struct apply
          : result_of::value_of_data<typename It::first_type>
        {};
    };
}}}

#endif

/* value_of_data_impl.hpp
1RERVYe6cG5DreRLupq7Cp6rnwRBWbPpeqdwUrhFp5PO0X9HHivOgpRkBKnvgRW2fMw6QznSQHrde6AeSKZodxz+eV+UjLYeHAAnjaASNPSRzRAM6KeeflqyNroH91HNxdEOXIMKILp0F02StKS23lY6x+NdWejsO1CGpbW8IvBbau7iJe4G6Krns6kBEzl2l6Q4oL1qHZQgccNop3OgKyASuPhhBElAL7kZUj1N4ElOkSlXpwDngLDL3U8q3yvv05N09J8/xxMAkU+iia49D4iwccJp21umftaEj4o0QeVWp3tqwMPbEc0Enl3/fsX5lg4fI9+vfpgriaLtGTHX6ZrBcBIPL0LV+X6wjDttgU3veIM76zI/eTuq4hGzoWCh0fC5O4wl19NmKxMq73wNNK94dvgLM4DXc5z+8kHuekMgyGw12LlBpzipWXrOlgiljXpI/vj/rYNo9iEvp+Pq6pEe/wXjjlomDN8gnig26BMFD307fNQ8mUq2wtqpxB1qC+eEP4/+M2o9lWyvgrs5DwPFtbaPW8KGLaIUHdzkSPhPQSbuZH+JUV0U1w==
*/