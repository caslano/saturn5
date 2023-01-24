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
ls9iVQZAD36VcP4voVyAN1ArhnCxVeKehr36FXKwyqK2YiP9C1jXkziAeA3Yv51hNZGA0AmodkgDUW1UKs7YCgRUryIQBGd1MlHeEngqS8wQzHh3wP78DBkpsu+1lKEnPx/jAu35vRU8lXFmkrdv469/X6PS/A1DiMb/dA09v8NPGN9y+RCjDBxE70uI3ndvLel9DxKGU94Hlf86pcGhkfvwhONej5jiTuD/A5XnjhOEHg4o1Q4V25xQEnKImT7AC7AqD3FTTCLy8geUl/WZrUGZn6DMCZdz5qn6zN8+ZszszgOx+G1m00+wWPy50tYGOEQI9rnrEJ31AmAZlBVhKwQbFfErRkZtQNnXhVQmRaPt41Jn/+ooOGgrrCHozFCH6w4//6YJF9MkCjXIQurWeXE60gn05vs+sgA20bG6hWKzH9HEcIpSLpFPBML5D07v2M0cPtxW8COy14JyYGZBQOzH4g245xCdleWPPyRxT6TAPYewEkgk1LOKBucsaQr1POwiMC4mtHBAwzwzzYx5HAfgvCVeh3imqognm08dEOlc0AeQzlwV6WQcYJwzkio/BDjnEAxPuWs94JyRgHMOAc6Z35Jwzj5YLf9IPc4p1rCL4yni0g8QcgHscUDiliAnwhyCvaUTsQpF48R7pLmRJNLd/9x/sdatFwWv9bu5VlPK7K2ilh6AJvb9RWgCGewZW0uC0AQB65+DCLSn
*/