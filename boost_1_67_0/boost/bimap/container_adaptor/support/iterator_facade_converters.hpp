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
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
*/