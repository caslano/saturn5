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
7VltEC4mBgsXEw3Cxbct9MLFRDxwD/AZmtFCq2npYlekUbr46d3/SLoYX9wUbva8d37posUSli7KLShdGGWKuud1MoW/WGLapXgcv4s+Qmrt7L8gVBZBinbYnmdS7QUebIHIVzFmUEwqvb6OMpSrAkS5FCCQ1Helz/Xq5/pG8kU9OrlbW2lsotKkHvhXQAYfN4GwmbAPpYqXIxiXL0G7oIXkY1RQjtkRdPsGjG/rxrKRsVHM6KaJGUPS2cR4zp1kYowbE8WLFdcS6H4aagRdo1SxslQPuv2HY3V7lUfHGsHwi3kEhnsZDB2LUULYC/r/NA7/OCSozDIuU81l2lKZauxvdqaUKlbrpIoH5hmkigOLmgbWly8Okiqq9VJFdZBUcdqKY2t3A0oV1Qiam5ZKqeLyEFWqkIYxQqoYv4ilimqdVEHA+9lIAt65LZoXKtzABFUofcPNyHsy/V5pbYL7zCJ+M50eTno0Z396O55w+uUldjvtt3SNBY22yoJOWRAJTmcrcQzQ8bYnTcR/OvL4WomTrHqVqseJgP9sCWI+syTzmZun4zzxIPNti57z7Pfc+W1PpY8AAexnF6rGw071Rgt8+GWhepuFDaBkXQbzJ5XzPGv2tKUVQvsnAUOpswMGtjP07f9LtnOJVkHdVN4tqmQ1kPpbTWQ7Qi9ZRejJx8QwlKyIfEQw+UgNN+nNTGwFbnRH8uMCq6ysNilA
*/