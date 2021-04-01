// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/support/iterator_facade_converters.hpp
/// \brief Converter for Boost.Iterators based iterators.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_ITERATOR_FACADE_CONVERTERS_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_ITERATOR_FACADE_CONVERTERS_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {

/// \brief Utilities to help in the construction of a container adaptor

namespace support {

/// \brief Converter for Boost.Iterators based iterators.
/**
Container adaptor is dessigned to play well with Boost.Iterators. This
converter can be used if this library is used to adapt the iterators.
                                                                            **/
template
<
    class Iterator,
    class ConstIterator
>
struct iterator_facade_to_base
{
    BOOST_DEDUCED_TYPENAME Iterator::base_type operator()(Iterator iter) const
    {
        return iter.base();
    }

    BOOST_DEDUCED_TYPENAME ConstIterator::base_type operator()(ConstIterator iter) const
    {
        return iter.base();
    }
};

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template
<
    class Iterator
>
struct iterator_facade_to_base<Iterator,Iterator>
{
    BOOST_DEDUCED_TYPENAME Iterator::base_type operator()(Iterator iter) const
    {
        return iter.base();
    }
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#undef BOOST_BIMAP_CONTAINER_ADAPTOR_IMPLEMENT_CONVERT_FACADE_FUNCTION


} // namespace support
} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_ITERATOR_FACADE_CONVERTERS_HPP

/* iterator_facade_converters.hpp
AO1Vb34GLvbiL/R8GzPCFWJ74/RlNF5jBCjx5Whf1Y4Dv+x6I7rr6M+HoK2p2fLml2fdpxsxmo1o9c7N5j8tEwKM7+z7QVN5tLVDOIiOAlazhDFkZMsnfgy2oAR4mvUowRnPceIXL8KWN7v+BYBtmz11LYmuNE/k9FLib4i5L9z+5NZL2HB3lVJYbkUWx+knkesDL4bE9N6TE1OhQMlHjPiwlKjwCAfpX1E3N3DaObVmA27qwKIA88UJmC6g5/bYIGe7RZqOr14ZHpI4/R1Q9t0Gi23NulhC0lvHLblQrkHSKhI8mHOqNCi19juXcrVpT9Nppb8KNZQ32FaRwGtft5Q6tRDV/gTKk5MrHgdpELKS86opwx68D3tLypDD/0iMXN68RmG3hLdrKAbP3DHwK1WA2BHA4La6IeqQV3ZYiafcbIMXjSTwOobGBaM/V+sNns96tp7UH/CL48nTw/3P4VTMy0mBx769qMa1whPGmaZG25rqioSKmSpZKqwXWuuq1yZMIOE4IhyzjS/ahC+Wed1g6HN+Waets59/p7cD4JdKmkTVa5mQfYWbNg==
*/