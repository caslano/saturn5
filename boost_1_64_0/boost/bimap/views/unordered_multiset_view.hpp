// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file views/unordered_multiset_view.hpp
/// \brief View of a bimap that is signature compatible with tr1::unordered_multiset.

#ifndef BOOST_BIMAP_VIEWS_UNORDERED_MULTISET_VIEW_HPP
#define BOOST_BIMAP_VIEWS_UNORDERED_MULTISET_VIEW_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/unordered_multiset_adaptor.hpp>
#include <boost/bimap/detail/non_unique_views_helper.hpp>
#include <boost/bimap/detail/set_view_base.hpp>

namespace boost {
namespace bimaps {
namespace views {

/// \brief View of a bimap that is signature compatible with std::unordered_multiset.
/**

This class uses container_adaptor and iterator_adaptor to wrapped a index of the
multi_index bimap core so it can be used as a std::unordered_multiset.

See also const_unordered_multiset_view.
                                                                                    **/

template< class CoreIndex >
class unordered_multiset_view
:
    public BOOST_BIMAP_SET_VIEW_CONTAINER_ADAPTOR(
        unordered_multiset_adaptor,
        CoreIndex,
        local_iterator,
        const_local_iterator

    ),

    public ::boost::bimaps::detail::
                set_view_base< unordered_multiset_view< CoreIndex >, CoreIndex >
{
    BOOST_BIMAP_SET_VIEW_BASE_FRIEND(unordered_multiset_view,CoreIndex)

    typedef BOOST_BIMAP_SET_VIEW_CONTAINER_ADAPTOR(
        unordered_multiset_adaptor,
        CoreIndex,
        local_iterator,
        const_local_iterator

    ) base_;

    public:

    unordered_multiset_view(BOOST_DEDUCED_TYPENAME base_::base_type & c)
        : base_(c) {}

    BOOST_BIMAP_NON_UNIQUE_VIEW_INSERT_FUNCTIONS

    unordered_multiset_view & operator=(const unordered_multiset_view & v)
    {
        this->base() = v.base();
        return *this;
    }
};


} // namespace views
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_VIEWS_UNORDERED_MULTISET_VIEW_HPP



/* unordered_multiset_view.hpp
0+Dv9T5xOfwtvAJeA6+E18Kr4Bp4NXwIck7a0XKo7Vy/5aJtubTzTuRTF5in7aErHAwPg9PgcK3vBfBU2B3WwR7wItgTXqvut8FDtV/qCx+CA+AuDednDSeeOPSCuXA47AULYB84AC5T9z+q+wo4EN4ER0DNX/3GhjVPl/zdrenaA4fDH+FJ8CdYAn3cf+ZCPzwXxsGlMB7eARvBNbAJvBc2hetgc/gETNH715rgdxvwSM3fFnb/qfG4zxe43z0I+8GH4JHwUTgfPgGXwSfhCrge3gifgWvgs/BB+Bx8Tt1fgy/Av8MX4cfwZRjLtTfBxvA12B2+CQ+Fb8F+8G3dQ327pe/WwyUa7zYcb9F4v4dcB7gV9oafwlHwM3gM3AGr4dfwTLgLXgm/h3fAH+DdcA98Bf4I/wYt8v9dG9qfxGs/0gjuhkmwEXFJhm1hGuwEW8GesDUcCNvAwbAtHAmz4XTYTvuTLFgOt3HdxfBzqOMV3rf2Hq+M0PHKSNgdjtLxymgtb+7H+j6tvBct/k+wyFfc7V8i18mDzWB/2BwOgSlwGEyF42AaPBFmwjK1nw9bwiUwHV4DW8HrYAa8XeXvgllaL7LhI2pfp/bnYA78BHaA38LOMIa45sIk2AV2hHmwG+wKe0DkJF85lnztCWfAQ+BcmA8vhb3h9bA//BMcAO+CA+EDcBB8Gg6G78Ih8FM4FPpjAu4pcBRsBUfDXDgG5sOx8FC191f7cDgeHqXyJ8Gp8DR4HDwfToN/hMfDG+AJ8HF4InwangxfhjPgB7Ac2vP3CtgPzoKT4QJ4LPw9LIeXw+WwCt4O58C7YC1cD0+Hf4VnwDfU/054JvwOngMbx/JsBvaD58Mh8AJYCC+EJ8DFsELdfw0vhRfB38Jb4UXwfng5fAwug+vhFXADvBK+CK+Cr8Or4fdwOYyJ4/4IG8HrYHN4A8yGN8Le8GbYF/5J28t4834QeajtxakX81bkWsDVsCO8HY6Ad8AxcA0shHdqeNMwGzW8IzW8BDhJwztK9WwWwlQ4GbaDx8AO8FjYBR4Nx8EpcIK4h+53Bb2873c5en/vqP5zdb6TBy+DXeFfYDd4DzwEvgzz4btwMNyp7vSz4t4U9oZtYR/YB/aD/eEwOBQOh/JODayAI+BsOAaeC8fDK+EEeB08HN4AJ0GZdwbfoYBlLvPONM23dM23VrA1zIIYsXeEGTAPZsLBsDUshO3gNJU/Se3FYg/Na7br9Tdb0fOaMTGB8CfAvvBwOAhOhCPhJHgMPBIWwaNgmdrL1X6ayv0aToMXw+PhCjhZxxdH67xhCnwKToWb4LE6LnjW0mfAgPw28/uHNZ7cK6U/3wr7wE/hALgNDoWf6zjsC1gCt+v8+Ct4Kdyh9eNrnRd/A9dB+liJzy64EX4HX4ffw7fhD3AL3APjidNPMAda2g/HwDwYC/NhI9Ne9JklPCWyvahe/Ex4gpbvSVq/T4b9YREcBEvgeFiq5TtDyzXb0meBMD1Qz+U4zbSXkFxBA+WK65Hr4JCra6DcCm85zofk1jVQ7t2QHPfzcLn3Q3I0Ym+5Emf+NVCuYC9ysXSs6KHZq66aSUzOlm1rbN2D2YjZjcn4HB3yQ9FrggnqsdmO3FDcg/psYg/DMKHLw3TieO2dAR0305GphQvh6yxQrIBXI7OmOqT7Zj1und6LtTZXc338VkbowtldHa0PJ2kYtM1pxANTiumLe8Ew/HF8M2Y6x2uhl86ct08L6c1JZvK5EW7AvhPTF/skTCVmKWYrcdwIt2EGDidtmKnEeSd+FsCF2NvWBHTuLOE4D47GvopzTv07se+QXriac4tx2wx3Y7YMRxZ7bAFxYQLcozako6c=
*/