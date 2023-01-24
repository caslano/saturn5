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
TouWd2yJh+kEJW+KSoabB24ME7Z+HXETZcRNANUO4ibuMhG9v9VEXMQN/BzG6dfic5dyFabvUgbws7dJ5TOKz4RhkbKzYViklJ9hXMXpAL0fC1C+w/w8iOm7lP3wVL4pFzAjUnfx123wZP5DxovVm/V+tEM1SnX5/oQw6AkHXYNeygMCXrALQzxVI6x4gd1xecfvTfPNy7PyYZFjr9jMJRw26g2IlOLbL/DgatX683Gk6uPLKXe5wGlD/g43kYuFx+0yhEs0ZYFFqGstAL4c6oA0X1Wh2A8pSIrGV4q/MozUAqKRxpQkYS9F8qJyZMJ3aUFk4ixsepJRA3CjBr+JpiK+jBrMbmK5poWa/SBmd3L6yTDOfhCzp3MyxaiC7JWYPYLTv5PZKzF7FCfvULMrmD2a0z+U2RXMHsPJb6rZyzB7HKcvldnLMLuUyfxq9sOYPZHTc2X2w5g9mZMfDsOFKaUipVhkNH+7nYqIpS3FMpmcPhybUDHUg9eEN6piImftHVRFFqd3MlYR10QVOZz1WKixijxOPxgqB1qP+Ys4/atQHmg9Zi/m5E9DjdO4mNPXhhqmsYSTXw3KrnD6c8bs9Zw8K9QwntFDGo9nNWe9N2g8pZw+KqjFMk5PNbZYzskDjS3+enXjFis5a7ugFqs5PcRYxctNVAG6K8h6IMRYRRSnV4UYqshsoopozvpmUBUxnL7UWEX3JqqI46yP
*/