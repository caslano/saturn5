// Boost.Geometry Index
//
// R-tree node children box calculating visitor implementation
//
// Copyright (c) 2011-2015 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019.
// Modifications copyright (c) 2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_CHILDREN_BOX_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_CHILDREN_BOX_HPP

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree { namespace visitors {

template <typename MembersHolder>
class children_box
    : public MembersHolder::visitor_const
{
    typedef typename MembersHolder::parameters_type parameters_type;
    typedef typename MembersHolder::translator_type translator_type;
    typedef typename MembersHolder::box_type box_type;

    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

public:
    inline children_box(box_type & result,
                        parameters_type const& parameters,
                        translator_type const& tr)
        : m_result(result), m_parameters(parameters), m_tr(tr)
    {}

    inline void operator()(internal_node const& n)
    {
        typedef typename rtree::elements_type<internal_node>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        m_result = rtree::elements_box<box_type>(elements.begin(), elements.end(), m_tr,
                                                 index::detail::get_strategy(m_parameters));
    }

    inline void operator()(leaf const& n)
    {
        typedef typename rtree::elements_type<leaf>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        m_result = rtree::values_box<box_type>(elements.begin(), elements.end(), m_tr,
                                               index::detail::get_strategy(m_parameters));
    }

private:
    box_type & m_result;
    parameters_type const& m_parameters;
    translator_type const& m_tr;
};

}}} // namespace detail::rtree::visitors

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_CHILDREN_BOX_HPP

/* children_box.hpp
8+2adLACPIw0Rd5ETjH3lw5KN/N0ys192SPMaRH3qfp7EC9+0P8WPj+0+9P0N6F45X5T2PxpAGOV/RYrv7T/NgHurbvRI32RS7n/M+e9xyk/U7QfvoHKt53HlBt3SH+m7OEqZR+n10+OU3o2qWwfGoZy49OZl0A5ughjMrncwYNU69mPsgoqz8FhyjPTVp7B72FVPqh208pTvrfVs/SRorf2WvpNWre3q2ulTrT2nf0qfUliq8A6Ma1g8vTyKTnh+zdx27ra96ik2dYW5Xe0HD4sfdp9Eo+M8PGgJSrIK4rwPX2c8nOrOqT5et3PSVjcd755EbNlLad5nY7V6r9C+2S9hvh0y2Ef8XAm0oQ2ZQ31xL/OtTxgvFDInVZQGqGNEX99Aup8oRr5ybjVZp8W2sZoe2l/+SvR78rWKbvuNS4v+/tmFR/9vjktuI+RNmeT3AQbEdPdGsTrpV0+xZYvYce37iRbHyN+Wuh3eP2UfjN7STpCngeGavfN9FyFvkq/kTkG0cH72uvx0RnKzbXGAJm3lKnDaWzbT7xPDZ7BSIfuk9L9zwW6vW4Z4ayrLTL5cK/cE7t992brgLwrnFGeP30WXsOvRW+t3G4zzuHfacgGfT/4wvGGbROT4CJlH6PH4U8ovR3l6F+334n7ZlpSzds7s026urV9TfkGdGmj7P11VyugSVKHRiLlyVz7VJ0PMvoO/7w+VLnro9ONPylPWVtg76/EvqU+62uk0nuH7a9S4AXKfoB172n/zXT/PrkGdSW4fyd+P9O/S1t/qr3tv0n0U4PycUB364L9sPTCrrAtPyp1PmbRIk2ZGeH5Uty10ffTHqU3cMQ4rLPLhlv3HyGog1v0++/Xlbs6jlbGQSuPdVinBPqbkYs3/Q1Pu0mT+UjMgVR6E0eCwxUwP6VkapnvTA95T/93y5/DmvMibgLu8eeVfaoj0REXWPdn+uYieuGLyk1rx33Uda/DoccVZW0wl+fddl4VNi/EAp6VlL9oPTb6SemvGu2oC3FmnnO/dEO6Iz0Q2hHFnvJeJ71a/ZA76f42+jkq+N7SZ40MV7ouD9krQ5vr/Bb30g5Jfga1Rd16hD5zfmmuj2nrrzuFWeXTs0pUoFa+qnLNLwyY1yTuPfp9Q67ShxoJ6g51yPea0Pm9lyl3cboM5ym9NeHE6vFXL/KuNxJVjTz0PfuXq7wgjkHPRq3SLcc3IsnIPKQt6d2p08sqoOJienGmz2aV0qtPnxrUBsv8IPFDCOeQm/6zaDj6aKZ/Xw+uIe6u5O1HJ8zkuYl8KONFJ9Y6zw7hzgqfEyVkPJop1wnz3KHf2Xyk7C81EknnBGIqdVr86XNyZM8R9WpVv5dxtsMNpcQpJvYxhaTxDOx98zPTqSuLe/rO+Byo3nH6+ouNScgvaA+9tnU3Ou+UeYZ+ztN5JePp0LayQTt9ZoZt/FbVm39kD576MAV289KmttPlPZnhZ6k59pTTqcoK8qij4dtK8ddUtwMPKt2p5+E5pE2S9lDc99R9znalP+nw6HGKvi91v7ZZuXnRIeUvYZwu5ehb65KlLiRlLW4yDa/MK9+n9DsdfXjrcaGxR5+bGDRnWs9f/0C5v9jR1EhS1/Wi9W1vmtUNqBflOh/KTsNO5kdeiD5I6R2kfstZi1ZW6Ha+qXJzhBjFSTsv7iQL6shc9brKndNh6b54uO1+AvJsFH6+UvFv7LB08UPMG1E/3YbVHr8fIG9LXU0/TntMOLo9DjvvRtdREqHPgg1qc8W8UNdbXX6q7h5Q6aWdk2e6Tu21bntvGSWbqM+R9xsVSG/cZHQIrcslus/V/fDUgPZa/HS0fUfHh36fO0bZTw7TH8qZxcr+HCs=
*/