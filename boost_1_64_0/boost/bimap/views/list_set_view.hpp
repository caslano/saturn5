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
FBrctTumhmZbUtQnXRgKbLsK1BhHhO+xPsS7WGOqVS5PS6TQBVYWAPbWJ4xh5mEKP7B9xtGUEdcSz2FSSpdZikzNP3+yFg8cik7NCQZe1LwDPdgqYSqRf39GtEGmVeDOjqCJa8luNwC/gE4Rw2F8YIniUvMJu1/RFVhu/6LMpdaKfzQIYY3YeKlZ99TlmCH1LZ0Hi49ONMZe9NR4uxCZNgQ1Fgqd8Or4NWMXCrJSlS+ZlzGPVzxneJIUxV4SV+x554C1BHWvJ48yw+9Hdozx4qRSTZc36FL4Gx1M8KqeYKttNdnPE+g1LUYyqhwNBY7BjGdrDq0lKOAt3Z0AKassumQ3/BSX6rK0Cy3znVu/tgOZa5AjDVtunIDZRmoIE8zTkbosrMsebuqa6qTwEY1dYefyzlDvmBzZ+v6bd5VbJc7m+mXTvoX/YxPj0DnR8HPToKIlEpAyXlsVSwgCQniHshKcVh/zgpXRtCmAjNrnxxiLusKvAsCUhuBmYXjS4IE7hDkNgwRgN7MZXyMzK9cUrgB8HaMrrolmBcNukmsGenwrXxPosfUD7LHzEw==
*/