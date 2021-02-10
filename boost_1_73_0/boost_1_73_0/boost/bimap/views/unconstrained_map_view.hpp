// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file views/unconstrained_map_view.hpp
/// \brief Unconstrained view of a side of a bimap.

#ifndef BOOST_BIMAP_VIEWS_UNCONSTRAINED_MAP_VIEW_HPP
#define BOOST_BIMAP_VIEWS_UNCONSTRAINED_MAP_VIEW_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

namespace boost {
namespace bimaps {
namespace views {

/// \brief Unconstrained view of a side of a bimap.

template< class Tag, class BimapType>
class unconstrained_map_view
{
    public:
    template< class T >
    unconstrained_map_view(const T &) {}

    typedef void iterator;
    typedef void const_iterator;
    typedef void reference;
    typedef void const_reference;
    typedef void info_type;
};

} // namespace views
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_VIEWS_UNCONSTRAINED_MAP_VIEW_HPP


/* unconstrained_map_view.hpp
KcgsSoWGDrssRI59Wh+NJ0PokAGKvN946LMx5RQRS39jaCHfhInLpnWrZAydZZUkqIPtY77sbooc82XQeEkvvQMfqt1gUM9wdlRl4RO0ni+3t/AAZNJ6Q7sOj2s3LjfS/A5JCtankhA5DJmpITb4+SMTCpDw3pZb21IRQHO9bLb7bvfzIHVGGi2JBRy+73M85rtivYkEH8s+PIsNE+ZjPzR2hjWPjxkMas4eAyQQD41GQ1IT5EIWjndP1wn1IXS4qfr1XaRiLhTT/57MxJYOzqeaoiYNAO2kaymLZsApcOKuF63SuJ8dNBAktWIVRaQ/SZVtSZxeTiacEdUI1ROhCFeZWooslIW0LYYTnk1mnweT8HQ4GlxOFu3dTkLhDFCYjd/erk+Tl/en6Jn2c2KJluSXsiszEXl4nD/pBsmGUxLBvaS/mTe1mYe5D2TQ0qBxIQJH1+x8EdLlhRJtGuKM5hhpkf7Da0GPpga6hZ6jzt7ZbZEQf6de0ojXfZ/XKsP3NAHWKbqhrPEtjQZhBT9foisQmv4/CPnqYrwYji6nJ4vxbBrsW3KPZO6ErVRUNDy5lMNUFwTdlcI40WUOd0j/R+zTwWIQwK91SfGxHsjkBTGuEV051ZS3rHGk6uBUvQsjpXcjgM/OvZYUiPH2
*/