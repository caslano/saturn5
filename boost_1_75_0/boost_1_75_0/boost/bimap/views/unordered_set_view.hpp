// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file views/unordered_set_view.hpp
/// \brief View of a bimap that is signature compatible with tr1::unordered_set.

#ifndef BOOST_BIMAP_VIEWS_UNORDERED_SET_VIEW_HPP
#define BOOST_BIMAP_VIEWS_UNORDERED_SET_VIEW_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/unordered_set_adaptor.hpp>
#include <boost/bimap/detail/set_view_base.hpp>

namespace boost {
namespace bimaps {
namespace views {

/// \brief View of a bimap that is signature compatible with std::unordered_set.
/**

This class uses container_adaptor and iterator_adaptor to wrapped a index of the
multi_index bimap core so it can be used as a std::unordered_set.

See also const_unordered_set_view.
                                                                             **/

template< class CoreIndex >
class unordered_set_view
:
    public BOOST_BIMAP_SET_VIEW_CONTAINER_ADAPTOR(
        unordered_set_adaptor,
        CoreIndex,
        local_iterator,
        const_local_iterator
    ),

    public ::boost::bimaps::detail::
        set_view_base< unordered_set_view< CoreIndex >, CoreIndex >
{
    BOOST_BIMAP_SET_VIEW_BASE_FRIEND(unordered_set_view,CoreIndex)

    typedef BOOST_BIMAP_SET_VIEW_CONTAINER_ADAPTOR(
        unordered_set_adaptor,
        CoreIndex,
        local_iterator,
        const_local_iterator

    ) base_;

    public:

    unordered_set_view(BOOST_DEDUCED_TYPENAME base_::base_type & c)
        : base_(c) {}

    unordered_set_view & operator=(const unordered_set_view & v) 
    {
        this->base() = v.base();
        return *this;
    }
};


} // namespace views
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_VIEWS_UNORDERED_SET_VIEW_HPP


/* unordered_set_view.hpp
Xh1mQhzhyZU4IjyJPo25mp4nBqvQv3EQQf3BwfTcP5j0D+eB+T4RzcB82HVNw3zEQiPM70/RQea12UbIfG8agvGlVzAYr9FnbheUeSZlvrY/Z35an/mXKcbMt01rGua7t/qfhflxC/6LfRC2MHgfvP7k/xbMl1/638O8a2lTMP/q0H8H89Z+54f5/htO/VuYf3CtEeaXW/8NzN/4xP89zHtbEMx7nv0v1jp6fvBaf/S4AeYPHfkXMH92IAH004kM8zMelzDf/ir6dF8iPUOvUmG+ciDBev2V9FSuPDfMs1w/MEyV612+n1y+k06vC2xFj6PWZjM4tcCbrbPAarI4kzm5dzEinmdemi8sFphD+EgamZJwsOOiaO0TUgd5Zsk4FtmxiZR7FPzYSTFmcLeE0+kaqhhvh4zJLBMki431fR/c0g0ypDte2urEuTBsTEtQUiVjg+wPP4rc4WdHgCv8Hvrq8TJ4olzweXtVNfY8gvqPYHWTtnkiUmYfr51g5TCZVlU+W5MqJD7xt1ksdqtiqd9Axt5W+Cmelp4ls1tUKS5XBj9iMO5Z8xiitbgBJJPFK69frdNaRD7CMlk8I7Y8yj6oj8z+pD77Dw8HZb/xMcCDaxgPLgdT38+VaCsgwXqnf8gKOF4APJhEoTJsBb0xdHhAcLOLnL4IOiFYlOKfHgJokE4J6i0UUjw5zddGLgtgJfy4T6eKSPXmnhB/
*/