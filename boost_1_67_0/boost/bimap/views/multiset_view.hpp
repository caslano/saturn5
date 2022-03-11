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