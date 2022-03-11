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