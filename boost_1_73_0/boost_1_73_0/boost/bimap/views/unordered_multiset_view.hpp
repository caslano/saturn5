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
ziozLrTVvN3490u68qTaFChRm3R7K7atVdos3aoNTUjkdft6KYZa16PkvQjYbFfhKPDd1Sb6OvygH/ZpJ+vRZp8mPIXocuT/doAcUao5/0f88buTbisUF2aedx7NvBDBb3iuOaWcIDQfU17edJ5FlXhUfKm7/cnE89e5fab5VeiqStM4l5o7aac5AzTYpgCC843DgJUQRVSrI62Figce1Alq6K223eOB23jcsAqq+9NWEaGMqBMUTJQOnWGqMn1a9RhTm0oMD+J4rFaHC6b1J37H8OzId2NZdEkmXaqNkhW83XtE0rwgmo1JjzvOqjM0K3CTyznLq33btsrTcXDcH0f98VrOK+jWfZ6K6kmne7iYVYQuNI51HveCqrqT5qy41NQSiAHeakjxtwpP1rm/xV8F+NvG6XS2lOnDtr1Sw2akzZSNZr5Hvfs/UEsDBAoAAAAIAC1nSlKeRBidHgQAAA0KAAAzAAkAY3VybC1tYXN0ZXIvZG9jcy9leGFtcGxlcy9zaGFyZWQtY29ubmVjdGlvbi1jYWNoZS5jVVQFAAG2SCRgrVVtb9s2EP7uX3H1MMByFSvrvqy1G8xw0iVIZge2gyJAAIGWqIirTKokZcdo+t93R0p+WbIlGKogpkTdPc/dw7tT1P1xVwu6
*/