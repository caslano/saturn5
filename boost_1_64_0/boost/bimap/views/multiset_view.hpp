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
Zf7siqvgCulQ8kMWJaVUYyCLs5IS6rUs1Vc9Ha4HM0zPpJa4NRR6uQdygFJ4nPD+NST5CmUSqqiq/1AwTk5kqT0iKqnkr3Pd2lbYFC9rUaQhmYgBM7jKxuPRtNXz+9C7UrWsNG55JY/5cljEQ/UiENPX2LvNZ0rQElaKxc40NwnuxxiO++djzA1i0oknXs9pBRHww5kkJEtoe7Nh0uW3IojHzSkrGMvxl/0Clr0Iqab8cfUs2yXxc+YYfgONkBQLz8781MXKaO4F5iHkBve1JGNoQf1U2fOnWbg5INxmiXIY1v/DXfaiBhPUwNyaEEdbNw1YaXr63qg1vnEpmyAeBCleTrs0DAPYDZ0YG81K5oraMA1ni9KWnLI1gyslqpVCHQArwnwLU8cHNgqj9Q78pDkqU5HBEJO+BoHAtHu/yod/j/ERILR4LgmUi44Jo1acBR5k0IDsKKdt3wPWLO4ahJLVX2kRa1BTB6y6hVtBDJgDqCjtErh5xjP4qqRv8qwDPQu6MSgUFjfSotTmrBhX+9qk1r7MCTXiOLP6Nrna5A9qfraSG4Lmc3mnUg==
*/