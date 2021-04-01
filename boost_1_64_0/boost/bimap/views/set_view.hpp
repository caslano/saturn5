// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file views/set_view.hpp
/// \brief View of a bimap that is signature compatible with std::set.

#ifndef BOOST_BIMAP_VIEWS_SET_VIEW_HPP
#define BOOST_BIMAP_VIEWS_SET_VIEW_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/set_adaptor.hpp>
#include <boost/bimap/detail/set_view_base.hpp>

namespace boost {
namespace bimaps {
namespace views {

/// \brief View of a bimap that is signature compatible with std::set.
/**

This class uses container_adaptor and iterator_adaptor to wrapped a index of the
multi_index bimap core so it can be used as a std::set.

See also const_set_view.
                                                                                    **/

template< class CoreIndex >
class set_view
:
    public BOOST_BIMAP_SET_VIEW_CONTAINER_ADAPTOR(
        set_adaptor,
        CoreIndex,
        reverse_iterator, const_reverse_iterator
    ),

    public ::boost::bimaps::detail::
                set_view_base< set_view< CoreIndex >, CoreIndex >
{
    typedef BOOST_BIMAP_SET_VIEW_CONTAINER_ADAPTOR(
        set_adaptor,
        CoreIndex,
        reverse_iterator, const_reverse_iterator

    ) base_;

    BOOST_BIMAP_SET_VIEW_BASE_FRIEND(set_view,CoreIndex)

    public:

    set_view(BOOST_DEDUCED_TYPENAME base_::base_type & c) : base_(c) {}

    /*
    template< class LowerBounder, class UpperBounder >
    std::pair<BOOST_DEDUCED_TYPENAME base_::const_iterator,
              BOOST_DEDUCED_TYPENAME base_::const_iterator>
        range(LowerBounder lower,UpperBounder upper) const
    {
        return this->base().range(

            ::boost::bimaps::container_adaptor::detail::unary_check_adaptor
            <
                LowerBounder,
                BOOST_DEDUCED_TYPENAME base_::base_type::value_type,
                BOOST_DEDUCED_TYPENAME base_::value_from_base

            >( lower, this->template functor<
                            BOOST_DEDUCED_TYPENAME base_::value_from_base>() ),

            ::boost::bimaps::container_adaptor::detail::unary_check_adaptor
            <
                UpperBounder,
                BOOST_DEDUCED_TYPENAME base_::base_type::value_type,
                BOOST_DEDUCED_TYPENAME base_::value_from_base

            >( upper, this->template functor<
                            BOOST_DEDUCED_TYPENAME base_::value_from_base>() )

        );
    }
    */

    set_view & operator=(const set_view & v) 
    {
        this->base() = v.base();
        return *this;
    }
};


} // namespace views
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_VIEWS_SET_VIEW_HPP



/* set_view.hpp
DQfGj76AKHNvUrFuN3zW719dlxmnMxcem4NBAk05G8rVwpye7BUO3cr1juO9uch/DxXqVzeY4yLl/sKjq/dCrXbUm44Ag5a54eXRadarssIhi6qYhMERPnxlBodJ+sAFcMNWNZ8Ndtp6jTpQNULE6pLP5JiIZ5BEfF53cIg3KJhH/VeuKNgsBH2Y2CnRqhSuZH2GyKSL6x0Q8LsZ+uMCGboAh2srFfgIntsHFfkNB8ph3sZOIeGIS+b3S2ttmg5aLUqfJlLeIWnjg77Zg4O1mOI4mHgnD7BwHp/nMxrUb8yBV1iAcULccR5dL7d26M2tamvv/WTIdiinPD7kUwNwX9+yXbbhe/21sCjVHaVqOrlwZZRqjF/6dW/td/BZW95C+8o/CjvE1OC/NLfRZLTlfIQ+Fw13UpWepj+4rgXh/A4T2n8Ot17EYRP7pc4JT+aRu4SMtTFSkmT64fsC4sjeBOoRAyJB87dvVVb3vblDjNwvNFzII9UOEyzxItepznzdiwNm5rBsTz3+Jx6mQhTTZXMriJRaqlZlHs0XD1zjbqIWIPrTZeNNS9UvDQ==
*/