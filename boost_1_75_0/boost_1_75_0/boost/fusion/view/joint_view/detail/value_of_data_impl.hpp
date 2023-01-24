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
L1bTK2gK6sT2oN3E/pSvU8m+mVcoI1CsZNkWA+XKOW1K8HBfv6GKkDULkJCureowq/eY84Bk1i0E1EZf4U3fbWe81d6p4VA+5Joz1c381ahbln2Oamht/DMTgauMYRYd5TG7ThZ2jRTRI9X5bFCAoHubDkCRSWVhyLT3EArLpE9rFHeR9AE79Bwl3jsA1TLuXVTSG44XvfbmS85NHbonBU3ogu0qxviVe4vEINPIowPD6QuVSmRxG1tV6T9dvpmhbIo3v20+EWi3bcptUb1+uUBKJ+J/UTkm6WaPSiBf8kFQV2jv3giqvqrBkpka3FTp2bd/dMhKf57mRrafOSgh0ksROVXbnsoSsegpPn5wqYjcqyDmIlA874gXy7EBvDKyMqWHON97R6aYqlnXmgSR0jlStdO1X/iPz3NDKE3IJZXLq63f/lEbzbexfOSpL8LL5HaaiPr6CKH8bqqaft5MdBX5Lxbrs13BGFtCVegKlcDVpccEn49Ci5OzVoKzOrgM7VR29XTD2jkATbSqXzIi1ZNd+cg2t3CxiHnynlUoYceDfDIViBdM3Zknm4kjIWp/etEVPy41k5JklMtT+X+HswcA9NNcm7Ds1Sdlc5RrQ5vluSQm/HuREmzG/CuhR5XRAP5LH22hY17YsUTU5RmV1UAh7B16zebUnjEpoeLZhUTocSmDLOK1yESRwKr0lAK+w1sLOgk2xTdo9/ip
*/