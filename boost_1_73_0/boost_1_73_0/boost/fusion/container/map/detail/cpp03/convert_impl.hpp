/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_IMPL_09232005_1340)
#define FUSION_CONVERT_IMPL_09232005_1340

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/detail/cpp03/as_map.hpp>
#include <boost/fusion/container/map/detail/cpp03/map.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template <typename T>
        struct convert_impl;

        template <>
        struct convert_impl<map_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename
                    detail::as_map<
                        result_of::size<Sequence>::value
                      , is_base_of<
                            associative_tag
                          , typename traits::category_of<Sequence>::type>::value
                    >
                gen;
                typedef typename gen::
                    template apply<typename result_of::begin<Sequence>::type>::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& seq)
                {
                    return gen::call(fusion::begin(seq));
                }
            };
        };
    }
}}

#endif

/* convert_impl.hpp
h44CzpmJKnhh7GJ9Wyzfh/FBqjuXq4GZNzj5F5ltW8vl1+SEz+yf1TDt7eLx3eIVllXi/OZzppOStzT0BJ7DHRimkLajtyEKdySluRpn6a+ErFYxS7rYiKp4mtWBWhcXds3s3pNmc2sHRbKULl57USPuBhYi/CjPF0oudSnXZNIKZFrFbnFQmK/wCG463jqmfF3h4kccy4gKacJ9RgYwNuTFTr18XUJgsUieoQ1u6BXz6OxSWTazqWPFVPRQ0iVqiUcM72GD0OI9ac+1qQ0MH4RUCT9Q4KHzO51hzXwMvqL5DujbN8l98ClF7F0/En81QC9aHmHtRQWWeOMHd8CvaywBwcfgTTeQVdwHaLY+BYQr0UJnp3gr2FOg4fTB1kV/3cC2MC44nvlOiBWdg6G4fwhYHYD9zy0H54Kic14Q3OBfMKDeCjT6kwlUKzIG9XGT/WWFD4AoXmMkP4Y7bpy9ugvCG8cNG7quwVNEN8ZmsrJnkiIGesmHMZLN9ppTKWUfJinC4/YJaBt00rKD4Y3cvEb4xwFEiqtvoe6LOR7nUDFRevegTD0dTcsZQ042FGDo0JFoULEXeVeRUQpggh3G0YBYEm4sMhdhJWHxpzqmAYjMgwLORIwwX4vmAq/DIiwMzeLVVaD+Py1/hqHa
*/