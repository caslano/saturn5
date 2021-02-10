/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_AT_IMPL_HPP
#define BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_AT_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct at_impl;

    template <>
    struct at_impl<reverse_view_tag>
    {
        template <typename Seq, typename N>
        struct apply
        {
            typedef mpl::minus<typename Seq::size, mpl::int_<1>, N> real_n;

            typedef typename
                result_of::at<typename Seq::seq_type, real_n>::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return fusion::at<real_n>(seq.seq);
            }
        };
    };
}}}

#endif

/* at_impl.hpp
MzOz6HZv7m4sDsiumCbmVdIkH6o9+XeTcypMSTQqqoxNVUHwqZFzWTeIXntYqI4Y6DrV95Cpv0sru1Kjo8RoxxHdbP99Ja57D/qtqDbd3uG2koJFp3PVSBaYNHcmb0jyqFrkky/pjjk52ARnmJUecXSP61OiDfDgprk00pwSWW/Z97ztwcTbQOPJa6Ka2T9Fz3YCWOFRZ3Bk7ynjOQKgHxprLM2WfbeGtjJX1nFp3W2FLerkdZ2y93NVUspNu4HPP+Vfd7wzuprSpNR7afe2y6RmU3Uf9x9QSwMECgAAAAgALWdKUsDvkRdVBAAAcA0AABYACQBjdXJsLW1hc3Rlci9saWIvaGFzaC5oVVQFAAG2SCRgrVdRT+M4EH7vrxjBSxtl24Wn2wOhq8reFd0JVsBqhZaV5SYu8a1jR7ZD6R7332/GTdrSGgqnDSJO7JlvZr4Zj9N9OdW5mML44/D04yUbfb78i42HV2M27uzjvNQitjRIft7VgQR2Xiz8M7xwDBqfrPlbZD4uzdgjLP5Q6xbHXUYGsFJ5ZD3YrfII3aDCGivH9MzYLkO35BvdBqR5y+gRZ1CNNEemmlt5V3jojnpw8OHDL/AODt8fvk/hlGspFFx5oSfC3qVwnIeZ3wr+8NB34iQF4YGrfgN1
*/