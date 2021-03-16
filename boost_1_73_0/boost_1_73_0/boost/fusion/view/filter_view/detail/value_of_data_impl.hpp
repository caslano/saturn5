/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_FILTER_VIEW_DETAIL_VALUE_OF_DATA_IMPL_HPP
#define BOOST_FUSION_VIEW_FILTER_VIEW_DETAIL_VALUE_OF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of_data.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_data_impl;

    template <>
    struct value_of_data_impl<filter_view_iterator_tag>
    {
        template <typename It>
        struct apply
          : result_of::value_of_data<typename It::first_type>
        {};
    };
}}}

#endif

/* value_of_data_impl.hpp
WyncYeEahIszMWnjnZRc0ayWgkYq1j5QbfZOSLAfH+Qrn4GK9RATSsr/ws1MRgKijMybE51eRDWSTmdhStJNNZl7ZDSZe8TRDaCAszy6gXnVuLMPLOtBrlxQJmGSYdThd48z+dir2T6/T7Ph4B/OJGS51IHlVI6zhSsWrly4kHD3CPcH4R4T7nHh8EfKmeujDZdIC2V/G3cLjTd2j3LVAPeOjPMXlhWruKuVaTIOlTvzlubaJzp0JNY+ZcEt4Bk=
*/