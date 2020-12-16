/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_MAP_DETAIL_DEREF_DATA_IMPL_HPP
#define BOOST_FUSION_CONTAINER_MAP_DETAIL_DEREF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_data_impl;

    template <>
    struct deref_data_impl<map_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename result_of::value_of<It>::type::second_type data;

            typedef typename
                mpl::if_<
                    is_const<typename It::seq_type>
                  , typename detail::cref_result<data>::type
                  , typename detail::ref_result<data>::type
                >::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(It const& it)
            {
                return fusion::deref(it).second;
            }
        };
    };
}}}

#endif

/* deref_data_impl.hpp
66OaSHslHhWO/Vd3eF669po+U68jy+vzSIxf7bc09s3Sxl6Gtk/OgJzTWlNMp8EiFtxkEQvux/5l4f1cOxKqDvXPMPldKJcmTfpxWtCuMn9pQcAbkdNS4PF4PeHzUBvMSfCZ339Jl/j5S+tQL3wWzufYnDMj+7LSW+otDMSSQ9G1V9pZwX4MVJzs81YH9L59+Sy1b/1q30qehXUu0dPGXCIl9kYY0B/sE7dFn6hx0RJfSaDCWxnqK6Vf1DG2VPolH9kMmYjUcWzN2eZ+MUY9o8c3ra7FFKWNcm3KvaeP3Mwny/3gOOQSyrrO0e0o8QVCtwHCoMGrM6oNKUrb/bq+7UVfk+g7QNrtRhZq7W7X54lFh7RT7nHavbH9XDYYrmstpnlfsG7uC2qMcbhM6X0SYyxBLuWY1nZb5EZYzPd2o9+TZP2RUN/LdRQaG4UVXm3IGMZXYzCWqw115Zw8JXadKX00A1nEsf5zQ3YpL8tMjmVtFOU6lf5KEfus8wN8ik1jJD6/rdg0CLmcujJmBWPlxaF4bO7Bow+IOk4MMVm1H8LncLG+T69H+abKT2LHLvIsyUGWcmy+vR2yJ/YYsZU9V8h1LPtknZnQM0XNZVjWI9LGqynfHNXG4J6RR+w7enQcMXQre6+0sJfrQuxVx1u6RWz/msHaQLayl9yTOOLtBtuU9XGWbhg5nq7j2BxLnSW+Sm9FIJ68AqNeuf/J2PcobR/aM9KOmzjOb2mHz3tSHDZcr+srLjLm7t0Q/NuEfWp/LLew42ZtzFjawXOqosQ7LcHzIP0h906Pck8ctlFk3sWtHNd2ninvwsPDOuCNWb8xByZFzbtQzsc9G0X2w3L058y21J/nD1QkZIP63KcWU/6JOyXSji/4n99sh5b8GceYiMeG5pTI6/KTQeyPsIFLMkEbjH2fujH/k/ZuJDo/5dhWsz4uA/J8Sktj0KnMcza27lPXHFP9/qrK4hjqTqRP+6Za5xW55/w9eUXPrWuXP2SXb2SXV7T25Q9Z5znZ5Q85eUJR3v20ycfqvDwhu/ytVD1/KOOpw/OWPLF6/YqJ20y/afD3l0dft0v3A8H1ze/+SZ6Hxu1gN7i98V3DGfbvdO7IcV3gTjAF7mwo1yrl+luUGyH5HHvBfnDvcDnxq8CNLMrtJvk8w2FPuLsh7yJDypVJOWPeRbPkXdwMB8Jb4BB4K3TD5TAX3gYnwTtgMVxhyBNplvrHSf3GPJEh65AvBLeFg+BQmAO3g8Ph9vBIuAP8BhavI/4K8WM0Idvw70naDsnjyoTj4I5wPNwLHgsPhRPg0XAiLIGToA8eB6tgHpwJ8+EyWABvh5Phi7AQroIe+Cv0wvXQXQS7wymwDyyGW8MSuDM8Ae4Dp8JxsBROhD5YDMthDayAl8BpsBmeBG+DJ8MH4CnwSXgqfAtOhy7t3gvXhTX8lwLPgAPhTLgDPBPuCc+GR8Bz4Bh4LpwEz4PFcDYshXNCeUvriE9DfB1afw/m3yOlvx+Q/LkH4RbwIZgNV8Ic+AjcEz4J94NPw4PgM3IeXoSF8CVYDF+GfvgKnA1fhfPha7Aevg5vg+/Ah+Aq+Bh8V87Pe/Bd+D78CH4EN8bWj+Fm8HOYDr+Cu8E2eBD8Bh4Bv5Xz8z0MwB9hDfwJ1sKf4SLIOa9pgl3hlXBDeAPsCe+Em8KHYT/4BOwPn4XolutCfCIw3+K6WKTZCxfDrWAT3BleDo+AV8CJcEn4OhbfBphscR1fJdfx1bAfXAbT4TVwG3gt3BVeBw+E18Pj4A3Gb+dL/QdY3F8y18FeuCV0w61C1yvSKuV8Uq4HnCTl9pXxMxJmwgNgNjwQ7gAPknaPgkfDg+Ex8BDogYc=
*/