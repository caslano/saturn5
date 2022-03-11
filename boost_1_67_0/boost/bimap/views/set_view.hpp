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