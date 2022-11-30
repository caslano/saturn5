// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file views/list_set_view.hpp
/// \brief View of a side of a bimap that is signature compatible with std::list.

#ifndef BOOST_BIMAP_VIEWS_LIST_SET_VIEW_HPP
#define BOOST_BIMAP_VIEWS_LIST_SET_VIEW_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/list_adaptor.hpp>
#include <boost/bimap/detail/set_view_base.hpp>
#include <boost/bimap/detail/map_view_base.hpp>

namespace boost {
namespace bimaps {
namespace views {

/// \brief View of a bimap that is signature compatible with std::list.
/**

This class uses container_adaptor and iterator_adaptor to wrapped a index of the
multi_index bimap core so it can be used as a std::list.

See also const_list_set_view.
                                                                                    **/

template< class CoreIndex >
class list_set_view
:
    public BOOST_BIMAP_SEQUENCED_SET_VIEW_CONTAINER_ADAPTOR(
        list_adaptor,
        CoreIndex,
        reverse_iterator, const_reverse_iterator
    ),

    public ::boost::bimaps::detail::
        set_view_base< list_set_view< CoreIndex >, CoreIndex >
{
    BOOST_BIMAP_SET_VIEW_BASE_FRIEND(list_set_view,CoreIndex)

    typedef BOOST_BIMAP_SEQUENCED_SET_VIEW_CONTAINER_ADAPTOR(
        list_adaptor,
        CoreIndex,
        reverse_iterator, const_reverse_iterator

    ) base_;

    public:

    list_set_view(BOOST_DEDUCED_TYPENAME base_::base_type & c) :
        base_(c) {}

    list_set_view & operator=(const list_set_view & v) 
    {
        this->base() = v.base();
        return *this;
    }

    BOOST_BIMAP_VIEW_ASSIGN_IMPLEMENTATION(base_)

    BOOST_BIMAP_VIEW_FRONT_BACK_IMPLEMENTATION(base_)

    // Rearrange Operations

    void relocate(BOOST_DEDUCED_TYPENAME base_::iterator position, 
                  BOOST_DEDUCED_TYPENAME base_::iterator i)
    {
        this->base().relocate(
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(position),
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(i)
        );
    }

    void relocate(BOOST_DEDUCED_TYPENAME base_::iterator position,
                  BOOST_DEDUCED_TYPENAME base_::iterator first,
                  BOOST_DEDUCED_TYPENAME base_::iterator last)
    {
        this->base().relocate(
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(position),
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(first),
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(last)
        );
    }
};


} // namespace views
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_VIEWS_LIST_SET_VIEW_HPP


/* list_set_view.hpp
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
*/