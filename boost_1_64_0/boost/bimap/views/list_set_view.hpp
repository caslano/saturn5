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
OB8Gwx1tJtxMDTdLw802ep703RPQHUOZQuRBntNwz8N4+AJsC1+EXeBLsBt8WePbhynU+HjHRPLRWfTByMFVMBDfWpgLL4ID4KVwJFwHx8CtcCxshDPgRrgEXglvhVfBu+Am+HV4Nfw7/AK0E98M/fBa2B1+EebAJtgbfhnmwUY4FK6Dw+FWo09K32sAKzAlYfqkFqo+uFJYAM+Cg+HZcAw8B86BS2AJLIPnqB2D3dHHJu8RwCm2PUwf28Wq/+cS2B1equl8Fg6Hjao/6XI4XuxOvHUab36UeK/Qdtyo8V8JO8FNMAteBXPg52EfOe/or6rTfjZA43Xrr0J8R+JdB3PhhTAProdBvUEHtV4Hani33qAa7W+1MAHWaX+9ECbDNbA9bIB5cB0coO5Gb1Mz8S/T+Cs0/kqNf6XGv1zjr9b4z9f4V5pxps+eYfso4+wSymnzUtgOflbLvckOp+2xX8O59QBeo/X9JTgUboEj4VY4Cd4Al8Ft8Dz4FbgC7oQX6fnNev6Lev5muAPuhl+F9+v59+Eunz6LlGepOgfZ/jlvH7drv94DZ8P7YBn8Nvws3As3wAfgLvgg/Cb8LnwKfg8egg/Dw/AH8C34Q/h7+Aj8CD4K/wYfg23s9QxMhU/CQvgLOBv+Es6FT8NFar8EHoJXwl/B6+Cz8Fb4HNwNX4QPw8PwMfgqfAq+Dl+Av4cvwyPwMHwHvgGPQfsG9wPYCX4Ic+GfYV/4MRwA/w5Hwn/AamgvTNfBeHgZTIQbYAK8Uu13wyS4B7aB78EUmEPdp8K+MA2OgG3hBNgZLoBd4GdhV3gNzIJbYDa8D3aHD8De8CewD3wangKfgfnwbTgAZvoZI7AnLIR5cDBcBIfASjgUrobDYB08DV4Gh8OroOjLg6PhN+F4uAcWwXfgRPg+nAT/CqfB/gy80+EYOAPWwFlwA5wNr4Vz4A1wLrwXLoKPwKXwCVgOX4HL4O9gBXwbVkI/F7AqmA2Xwz7wPJgPq2EhPB+eBlfCmXAVLIer4TpYC9fDOrgTLoC3w4XwEWj3z9fgAZiSFND3lQEXw35wCRwM0+E8mAEXwUVwHZwMb4BT4E44Bu6CY+HXYQH8MTwV6ryj+9L0nSjzTqPOO5+DiXAD1OuA7gXLHBhxHVip8/Uq2AmuhsNgHRwFa+FktZ+udqOHs0T1Q0a5Po7U/IyGPeAYeBocC0fA8XAcLIJFcCKcBCfAqXCSpoOb7pFSF5qOW3/bYE1nCOwGh8L+cBgsgKdpPLmYfRpPpsYTBztpPGvUXx3msLtcYXpoz9T0SqEfng2T4DmwMzxXy7sY9oVLYH91PxVWaPmrtJzVpj51jw0WR6nPqZruNE13OuwNZ8B+cJbW72w4Ei7Q9psn7YZd09kZj9F02E8jHfzwm/dd5dhmzwPwK/A0+FVohx9E+PlwJ/aN8Fa4B94JH4F3w5/CXfAV+DX4W/gN7b/3wM728zTYH34LFsD74DC4F46B34FT4P1wFnwALoQPwlL4MLwI/hBeA/fBL8IfwRvho3AnfAx+Az4OvwV/Dh+F++FP1f4ifAK+qvb21MFTsAv8BcyFz8LPwOfgMPgKHAWfh+PgC3Cyni+GL8GZ8DVYCX8Da+Dr8CL4Frwcvg3vgEfgPfAdeB88Cr8P34MPw/fh4/BD+FMYTzs8C33wJeiHr8ME+BZMhHI9gf3s6wkcBtvDqbAjLIGd4ErYB34engK3wjy4Hf7R1vcJk7B/DybDH8IC+BN4KnwRDoJvwHSYTH9Kg/mwLRwAk+BUmAxnwL5wLuwH62E+XA/7wyY4ABbb5TqMbjzMFEzl4TbH1Yf436IL8eNW6EP03x1dJ+ICTGUUnYiVs5I=
*/