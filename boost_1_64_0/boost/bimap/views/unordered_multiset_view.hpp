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
C6sxCmILCrBEi2qr9AVVJs/2ObnV9WnsKtZLG1W5UuspGm+n6LroGPfZaYmg+Nbc0iXyyjgBLeXKzv8Ulof3cZY17Ns7cVQpHbLd8hMEfwLdCDXUB2x54HGQgQT1xZn4pMuGdkeRK8CeS3VQ0XDXAd1GkkFN2qd/cLLhPZ5vUJRBLAiRFIdcGnHXNn9oXeQdyK0PfXXJR1Cj6UF1Mazt5Cm3DM1cAK8K7tPfRfr3V1cjwLONlKPNmWXz63YVOrRUFr/WAG1K387SaHTb/BhZLXK/WRaVkrPRT6IlKaYUcdL4d80jkcDfLX8sU5WlGm1P4mTDoFVZGmJNT2YCzMeSB+kSNsTY/qx94HkpxwTFxn7KMts6KcTm+GqIfhuRN+tf8rXBn8DKwEHKZb4gnfwgDxxBz5rKM2s8EjZ+xU01cSNsOuH0UjlTggL3OevaELOjsiXlCIj1IQ585xdjTL5QkKZfjNZnOuhibhhhyu0ExOWLirj8cs1umg2YQvDHLa/LglBKaRLbJwUsOuLB3NEg5PDNJxZGRUeF3BEfjiYVTIuIKxhqomcR4GzgZA==
*/