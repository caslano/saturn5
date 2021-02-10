/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_MAP_DETAIL_VALUE_OF_DATA_IMPL_HPP
#define BOOST_FUSION_CONTAINER_MAP_DETAIL_VALUE_OF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/detail/cpp03/value_of_impl.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_data_impl;

    template <>
    struct value_of_data_impl<map_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                value_of_impl<map_iterator_tag>::
                    template apply<It>::type::second_type
            type;
        };
    };
}}}

#endif

/* value_of_data_impl.hpp
M8/ECW7PtHE1gRc7DyNtblLTdW2HjqqQCsI2iYUfatmvsBrCW3jUc/SvCOpCmGNTb0WgB+Omk4fmTjWqmIxaEDPb8ohRMdL0Qq1BF0IyJYup6bV6GZqEWBPTGRja4jBioNtk3BmLygfR9kJpRDseO7rWyZQYY+umCyFpVmk0MtaEHMpHFXQAUbOz12RKIIfaq6UGZBuv5k4qVBtZJe7M1jVidkfTacMzyfxmNuhCEHdQM1NDqBbUDMNtRUzMiT5dQJcXtRc6EWo/dSIwH7ifJNn5dpfXk+pZQ00nlmO3G7GGtjbubDM8CmrEmVg6Ja+IkzMeyXMlnhEd7GRvTL3ZdOq45OQMYG8COVPTRmnVOkvxXb5jqs6chuVpN2OTjg1tuudlnwi+Dg21aWZeC1WFMIdGxV2teI5OGhOxiaADTNqN5TSMuCbBhMgBAfcZD3cCz/obRwI2R7VmcFVHeCNM0z7isoHAGyUVG40JZGsT07IHzh77vVX6F859HJjDC/kaE8VBjAxig8EjSYnna5EFP/wwzPEY0YW/VMCEpbTb7tVnEPxfdgT1C55Li3qlTX2+F5j8ucdW4g+KLlVJ9thXpD/V2VSkVy1msd5zEFvNJsuB60xqTOVSB9uKeMO4XX6QcwXR5F0R/1yvbTv0
*/