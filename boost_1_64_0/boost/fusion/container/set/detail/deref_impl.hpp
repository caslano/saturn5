/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_SET_DETAIL_DEREF_IMPL_HPP
#define BOOST_FUSION_CONTAINER_SET_DETAIL_DEREF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/type_traits/is_const.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_impl;

    template <>
    struct deref_impl<set_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                result_of::at<
                    typename mpl::if_<
                        is_const<typename It::seq_type>
                      , typename It::seq_type::storage_type const
                      , typename It::seq_type::storage_type
                    >::type
                  , typename It::index
                >::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(It const& it)
            {
                return ::boost::fusion::at<typename It::index>(it.seq->get_data());
            }
        };
    };
}}}

#endif

/* deref_impl.hpp
yz3rW7xqWMx3o/kTbKYkWnXYTkXv+FWQpLD4qatK0JAfO59HWVglTjNzXi1WJXSlMd8W2LIXjqZvxQqLaeGTbKpJKsd4EYi3nbMu46qfVT5ngUj9mMmDGdrXHa8lUMsyBMX0Y9cs97oElVfLCxOJjE4IYuOgQyZAqHdZ0RHBGqlELnQeJPgmjpxBF3bbLqBdiPGuOFv92r4sD82OsYN/qy5DvPVZokmBXNI/A2NNfaBk7a1dNV7bNdFsvNqmDLagU0MxvfOjKPdG4M8mjZtF5dzDK+PdsjUVnC+5NBfshZNyV18XA3pOFYbb1TaFlraPH1K8FaB+TeIHRCRIHv5VFec6Fbjn8rrWbmzdOCqHVYeqNaUzP0G0M2aZ37ce6VTTwOEJ8iLJp3O7YC9gPlgt5vwi3yvvixP72osyAdEC/5d+vAwWnKq/4a/TEbi5uYadF51gkZ+8YC8KsOPVMR72gXnwl64iVHyW5/VDFHdXk088EAeE8MPCdTrt/6OE5wBIzVAMu3+gQjAmDJpAxBf/llZZcp+QTz+cT/AcKpK2Rk9m4pZv6sWi4bPTxw==
*/