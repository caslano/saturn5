// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file views/multiset_view.hpp
/// \brief View of a bimap that is signature compatible with std::multiset.

#ifndef BOOST_BIMAP_VIEWS_MULTISET_VIEW_HPP
#define BOOST_BIMAP_VIEWS_MULTISET_VIEW_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/multiset_adaptor.hpp>
#include <boost/bimap/container_adaptor/detail/comparison_adaptor.hpp>
#include <boost/bimap/detail/non_unique_views_helper.hpp>
#include <boost/bimap/detail/set_view_base.hpp>

namespace boost {
namespace bimaps {
namespace views {

/// \brief View of a bimap that is signature compatible with std::multiset.
/**

This class uses container_adaptor and iterator_adaptor to wrapped a index of the
multi_index bimap core so it can be used as a std::multiset.

See also const_multiset_view.
                                                                                    **/

template< class CoreIndex >
class multiset_view
:
    public BOOST_BIMAP_SET_VIEW_CONTAINER_ADAPTOR(
        multiset_adaptor,
        CoreIndex,
        reverse_iterator,
        const_reverse_iterator
    ),

    public ::boost::bimaps::detail::
                set_view_base< multiset_view< CoreIndex >, CoreIndex >
{
    BOOST_BIMAP_SET_VIEW_BASE_FRIEND(multiset_view, CoreIndex)

    typedef BOOST_BIMAP_SET_VIEW_CONTAINER_ADAPTOR(
        multiset_adaptor,
        CoreIndex,
        reverse_iterator,
        const_reverse_iterator

    ) base_;

    public:

    multiset_view(BOOST_DEDUCED_TYPENAME base_::base_type & c) : base_(c) {}

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

    multiset_view & operator=(const multiset_view & v) 
    {
        this->base() = v.base(); return *this;
    }

    BOOST_BIMAP_NON_UNIQUE_VIEW_INSERT_FUNCTIONS
};


} // namespace views
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_VIEWS_MULTISET_VIEW_HPP


/* multiset_view.hpp
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
*/