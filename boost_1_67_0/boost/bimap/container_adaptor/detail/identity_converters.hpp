// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/detail/identity_converters.hpp
/// \brief Value and iterators identity converters.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_IDENTITY_CONVERTERS_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_IDENTITY_CONVERTERS_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {

/// \brief Details of the container adaptor toolbox

namespace detail {

/// \brief Iterator identity converter used by default in container adaptors.
/**
If Iterator and ConstIterator are of the same type one of the convert function is not
included.
                                                                                    **/

template
<
    class BaseIterator              , class Iterator,
    class BaseConstIterator         , class ConstIterator
>
struct iterator_to_base_identity
{
    BaseIterator operator()(Iterator iter) const
    {
        return BaseIterator(iter);
    }

    BaseConstIterator operator()(ConstIterator iter) const
    {
        return BaseConstIterator(iter);
    }
};

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template< class BaseIterator, class Iterator >
struct iterator_to_base_identity<BaseIterator,Iterator,BaseIterator,Iterator>
{
    BaseIterator operator()(Iterator iter) const
    {
        return BaseIterator(iter);
    }
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

/// \brief Iterator from base identity converter used by default in container adaptors.
/**
If Iterator and ConstIterator are of the same type one of the convert function is not
included.
                                                                                    **/

template
<
    class BaseIterator              , class Iterator,
    class BaseConstIterator         , class ConstIterator
>
struct iterator_from_base_identity
{
    Iterator operator()(BaseIterator iter) const
    {
        return Iterator(iter);
    }
    ConstIterator operator()(BaseConstIterator iter) const
    {
        return ConstIterator(iter);
    }
};

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template< class BaseIterator, class Iterator, class ConstIterator >
struct iterator_from_base_identity<BaseIterator,Iterator,BaseIterator,ConstIterator>
{
    Iterator operator()(BaseIterator iter) const
    {
        return Iterator(iter);
    }
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

/// \brief Value to base identity converter used by default in container adaptors.

template< class BaseValue, class Value >
struct value_to_base_identity
{
    BaseValue operator()(const Value & val) const
    {
        return BaseValue(val);
    }
};

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template< class Value >
struct value_to_base_identity< Value, Value >
{
    const Value & operator()(const Value & val) const
    {
        return val;
    }
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

/// \brief Value from base identity converter used by default in container adaptors.

template< class BaseValue, class Value >
struct value_from_base_identity
{
    Value operator()(const BaseValue & val) const
    {
        return Value(val);
    }
};

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template< class Value >
struct value_from_base_identity<Value,Value>
{
    Value & operator()(Value & val) const
    {
        return val;
    }

    const Value & operator()(const Value & val) const
    {
        return val;
    }
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

/// \brief Key to base identity converter used by default in container adaptors.

template< class BaseKey, class Key >
struct key_to_base_identity
{
    BaseKey operator()(const Key & k) const
    {
        return BaseKey(k);
    }
};

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template< class Key >
struct key_to_base_identity< Key, Key >
{
    // As default accept any type as key in order to allow container
    // adaptors to work with compatible key types

    template< class CompatibleKey >
    const CompatibleKey & operator()(const CompatibleKey & k) const
    {
        return k;
    }
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

} // namespace detail
} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_IDENTITY_CONVERTERS_HPP



/* identity_converters.hpp
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
*/