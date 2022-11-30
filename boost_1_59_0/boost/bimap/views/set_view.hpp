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
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
*/