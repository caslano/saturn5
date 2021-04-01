// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/symmetrical_base.hpp
/// \brief Base class for symmetrical types

#ifndef BOOST_BIMAP_RELATION_SYMMETRICAL_BASE_HPP
#define BOOST_BIMAP_RELATION_SYMMETRICAL_BASE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/mpl/if.hpp>
#include <boost/type_traits/remove_const.hpp>

// Boost.Bimap
#include <boost/bimap/tags/tagged.hpp>
#include <boost/bimap/tags/support/default_tagged.hpp>

#include <boost/bimap/relation/member_at.hpp>


namespace boost {
namespace bimaps {
namespace relation {

/// \brief Base of symetrical tagged types.
/**

                                                           **/

template< class TA, class TB, bool force_mutable = false >
class symmetrical_base
{

    public:

    typedef BOOST_DEDUCED_TYPENAME tags::support::default_tagged
    <
        TA,
        member_at::left

    >::type tagged_left_type;

    typedef BOOST_DEDUCED_TYPENAME tags::support::default_tagged
    <
        TB,
        member_at::right

    >::type tagged_right_type;

    public:

    //@{
        /// The type stored in the relation

        typedef BOOST_DEDUCED_TYPENAME ::boost::mpl::if_c< force_mutable,

            BOOST_DEDUCED_TYPENAME ::boost::remove_const<
                BOOST_DEDUCED_TYPENAME tagged_left_type::value_type >::type,
            BOOST_DEDUCED_TYPENAME tagged_left_type::value_type

        >::type left_value_type;

        typedef BOOST_DEDUCED_TYPENAME ::boost::mpl::if_c< force_mutable,

            BOOST_DEDUCED_TYPENAME ::boost::remove_const<
                BOOST_DEDUCED_TYPENAME tagged_right_type::value_type >::type,
            BOOST_DEDUCED_TYPENAME tagged_right_type::value_type

        >::type right_value_type;
    //@}

    //@{
        /// The tag of the member. By default it is \c member_at::{side}
        typedef BOOST_DEDUCED_TYPENAME tagged_left_type ::tag  left_tag;
        typedef BOOST_DEDUCED_TYPENAME tagged_right_type::tag right_tag;
    //@}
};



} // namespace relation
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_RELATION_SYMMETRICAL_BASE_HPP


/* symmetrical_base.hpp
y0oIMv+zCHMZxNogbMr7To1O8wPrRQ7Fi20pIasd++iTlzZEPScLWf97AYu+/+63WSXnR7z6JZodi5NCjknEyloTKKCRCy5WvWAy4DkYpvL53EIkzCIu7G/Y4SE7eUYajKTvkRFR4mysGdtIfLHKhz/vr/N/ZcsWMA5DkMi8y7/XGsGHfMEjt0APR+Bi2zkHdFSInbR1ctcwl4RxcGcR+qtuz976vsCGDqgDsiv2gojVSU+rGK4UdmxnCO+ZtUAX5GF4KmVCuKXXRQTctyHCKI1w67SrFPyNoExTWlVXEE7R1IIJzxUuvriKJyuQ99BWXnaswcDgamu1YbvkdglmkWAQcdZBYkMbaY7Or4zn7u8QgX1k9O8vJoJn6bdTbI1X/pB4YuSI33/ZhESeXFvAxqvXg2/1CfMNkdGr7UpFd+5uxbQo7LVhsMOIU65PpyGWsEzFQXd2w7++SGxjaVkvSB2a+aYYNC5B6lYj2f093HYRuR8DsizcBFWA0ufRnnNkycrvRdjD6G1EuXeUC3P+R3+DZn+vTrzNqWCbCmfe6OqWGWo/xonVljK8Lg==
*/