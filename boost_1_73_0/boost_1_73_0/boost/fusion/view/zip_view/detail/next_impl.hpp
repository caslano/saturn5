/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NEXT_IMPL_20060124_2006)
#define FUSION_NEXT_IMPL_20060124_2006

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/zip_view/zip_view_iterator_fwd.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/support/unused.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion {

    struct zip_view_iterator_tag;
    
    namespace detail
    {
        struct poly_next
        {
            template<typename Sig>
            struct result;

            template<typename It>
            struct result<poly_next(It)>
            {
                typedef typename remove_const<
                    typename remove_reference<It>::type>::type it;

                typedef typename mpl::eval_if<is_same<it, unused_type>,
                    mpl::identity<unused_type>,
                    result_of::next<it> >::type type;
            };

            template<typename It>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            typename result<poly_next(It)>::type
            operator()(const It& it) const
            {
                return fusion::next(it);
            }

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            unused_type operator()(unused_type const&) const
            {
                return unused_type();
            }
        };
    }

    namespace extension
    {
        template<typename Tag>
        struct next_impl;

        template<>
        struct next_impl<zip_view_iterator_tag>
        {
            template<typename Iterator>
            struct apply
            {
                typedef fusion::zip_view_iterator<
                    typename result_of::transform<typename Iterator::iterators, detail::poly_next>::type,
                    typename Iterator::category> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& it)
                {
                    return type(
                        fusion::transform(it.iterators_, detail::poly_next()));
                }
            };
        };
    }
}}

#endif

/* next_impl.hpp
Gp/i6BWMlSTvilJqGC9JpUWiZFjb/HmfXqv1RGVBUoWSdvj0fC1NVRzEO61W7yfZ4LgmWXJPEQIZXdwc7suMCyekRaWSUP+sgHoIJQplRIPL6dl0OPNHFx8PWw3xff/j0B8P5yN8/dHYf78K/GUmjcK3p7KD+KT1RGYoxG250zfbIuHiG9z96UXft3bWJURZiB6beSjl+x/PZ2ustR9r9xtSG8YuppPBcDbbMFWUeYDC2RRpThmHHAoj+IhXRA22aJMU59qoYosmdLwlGKPqt0imlGWZl5tURoYNAgflFwYIs0EO8izDJGBir2uxJxHa0K+0ZOHm0w2QLaQDPcVtwj1ry2CjootSZWYrOPsglWle3m8+AC2Ui+qq7gAL48yripvD27y81u0OcNMAMjTNp5dDUpGtaWCSTB3MgIv7tNda5HmyLY3kVJhzliqFvqcuH0an9Z8WQVXb3hDfYIp1LeZkAtYkI1CKEyF9r41MGWdMDOR1tg14ADy51NmeASymFirpKm/VgyqskIQrEoTSuCpFuscTJELZgxNgfgv93KF4ioS6EVLCmH3OmkDKwNWos+OD2VQW5XQtgeXc3BGfVCn3AeocP3OeDt9cvuvPZsPp3AV3/Ch5/yStEqPqpy7BtPZg/4RT6NscMs9X
*/