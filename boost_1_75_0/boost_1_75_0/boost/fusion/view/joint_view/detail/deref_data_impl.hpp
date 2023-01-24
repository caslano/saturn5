/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_JOINT_VIEW_DETAIL_DEREF_DATA_IMPL_HPP
#define BOOST_FUSION_VIEW_JOINT_VIEW_DETAIL_DEREF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/deref_data.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_data_impl;

    template <>
    struct deref_data_impl<joint_view_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                result_of::deref_data<typename It::first_type>::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(It const& it)
            {
                return fusion::deref_data(it.first);
            }
        };
    };
}}}

#endif

/* deref_data_impl.hpp
ugENrH+RT02sh2prM3671XeHBhS/Una4lUe2sHtfBNcGZsJQ+RINtdW+H8FjiNEYt6sK/FOJ11JZc462tAE/HF1c9qQZ6oV/ssZ+fa4KX/gI3ex960O188UT27dcU1anoX7EgaQPssZHSHfhv5hjZ/o07Bc2jCth2MduU1p6xTeVF0pgyXdlg08kuS/N8/jO2dGRsfzjZnu4Cx8ezH/PLizsn7vydykWeWuPW2PfLzv1e6IvpBFYgCq7XuXRK3iTTwJj/no+g789ZplFnOjMsLo7Zn5PIkXzrn/QY7HDk2GuPJoEMzWyksHFvWpVk50COgldf3JayZyq8dqjB6qWF8Z+tIOP5d2T3uEXgebg5iio9/NbtmW9sOVH7+ug8mBTS4/MisEu/EXr2aEA+8XRuw5cPxONLRfV56MmsBxi3umNlZTlH5qjy0XoPeO0iu76i74E3v2BDg9lL261Hojd+FMMZCX621lr+dAK3/DbTOIdO9QrPptX4UKhx2WFf9mg7g3uvo+HwlneTdlEE2lNH3z/GlwbM+6V/76jLBmgVeOQv9HSC3zsxVeIRbdi+IaMx0wZU60iJVwY/LKsJ1bZaJVHM2WNj2YtNZ69P7RCVjMoPy5aa4GAgkJeGPRRhw/+0VIG/vzNemYGAfquPDC4cOfvL4pg51zkc7Hb4a/xeIZzGh9f46TRx5peqW4hKMXSYUcg0Sz9GC8U/w01
*/