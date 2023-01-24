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
zM57MsivMKD1lzS9K/86jDJ4Ngg5G1aZdQGXEiHgEk5LmNi56xGh7gi2FZks+eYDQpS1bD+fVBuSa0uMazPAiWu3Q6qDC8f+jERoIWeExDh2mYivhK2nrDI3I9SQ4+pQsUce8yCHe+EJlab0fT89qH7fTwf1fXOJWcRV2oLuoymuEvtB9AEMvWw2MD9jEhNS5lGPcbCd2jyLT2eDnc4A7+wUPXbKWyBWBHR6FPWLDfo61nMh2w8q0WT7xvvuvCpU3//lpj26J2Tf/xrYdN+3rGxO3/v+w76nNtL3ISub2/f0vqH6PmUK9v01t6bPjw2KYfGnPYCf6B1q6+L/rOBbOi4HnUu+l8lBO1i/kxeBMOOOLMSny7eCRIxKpdTJJJt1QrJZVE+y+WojIE2TbPRY00k2sUN1c0RINhL6Hr/biXPEr5sjHVeYmxGfp0cfEgcKSRwIDpJxy2SK0TZFH5NC/laSnXjCdCkKMCQYDIsn6cQ7Jp7roBjTxTgVDe2fC1I1dLs03/Lq5nn0F6EwvbgepiXfPGQxoySjoTH8XSrwB9ELEXnjEHl3AfK2BCDvu+XNQd6PVzawgUbchU1C3CVMVmOmqBEL5AF6RUkwb31oubmhuG2zog2e1LI53XF+Qdy75c1hhP05nAFBC8ZM1O3vo8HnP9u8x6q6HOWWABADvf5v+rzeXiDaWgAx5AoXd0faX5nNaf+rwSDVxwqp
*/