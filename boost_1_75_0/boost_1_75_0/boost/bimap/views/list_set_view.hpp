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
7TUTKPjLyguZl7+B/dIk6nn53Jo03zyVkXfUaFx8dIiOi3fXEAsvmBbI0xz/vhUaTLiI+PcjzL8Pq+AV4vOsc8drhpUVhX6ThZpj1me8Dcz677aCvxEgKapzXMB+v0ivi4Gd7wRruhiX7+M031fQr74difNrYyadiJMR3e7s9hweXXW6JAOuU6h15pfOgV8LSv4JBGYLfO+rghg8gh3bBewYunNEvFr3lkQAFyzo09EMIuVqrZUyqZL4r9mfoItgwXt905N4Lzz8n7EViI2e90qefcCpRbN+9C2rSYYZd6pcp1PH8RBOvx0shLVh1Q6HC8yzD9RVCGLX7yHgSnY8QCSwB751foje1nLqW/w0P6TS0gfuB+JbfykRX+VBopw1D1LGvfye/YBaYND9/8pW7YOrjLZqNS7Qgvv+cXozkslWzeE7mwocXPIHZghUMLEJa7Uq6YhaM1FL6IKmaTWs6PAvrDGppml3dtFIbKbYgFmg+QnYE94kVpXLqOy5I5PN0cB82Fb4Ipir5O8SyI6UO5nKixOJ1E4kEnDr/brXLGXin0R5RQvb3yDKOxq7mIVq17VFaheLTKoRxcwucPXKk+NClY8jh8mrO4+sJ4pYBosNN5vEl1FCIobrk0V3g2XnIE+OrWC0BQAU9XblnZl2r0NDm01ghkc6vCLxlkc6vDydDu/Z5wQNXzaaaPgTnZvS4eUF6/BGoC2c5UAe
*/