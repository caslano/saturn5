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
UAFK5QtnU/K6AlhFryqg1NP87VP8OZk/H+XPB/jzLv4cMZvOlumRRo+b+cfrKXkVT17On91mC59gMSN1HsS7j9CCPWnBQiX0dSoBVmrLzDpfpxIFC403WAuqDdwV9inACDpzdMr3otl2a/YjiwxzEZHiDBSdhfpMH540a25VEyE6QbKB+O47MpnCvo3F9sKRcSJcmet37wU/3h97zqCLc/D8AbN2CZ6YIQe6X1n9XVx1lNPbG2JvXSJiW0i60SUn7hgSqk9/ctCHRMAdkAvvY66nhZOsgU/zMfKKN4lPI+JHeXX+k2N0/teWZ+idxf0ewin03M1mdJbmbiVvwy/yOdgTo3wqnI/Ls+vCAPGl7iTh78jer2sqagR6uOQ2Tt/scRdRmpG67HH2BC9tdv9tsWCGDl7d/DlM9tyNfv82kwYjsb5rvyAvxV1S9H5C0RUbCCnKgDydXzzy2a1zebr5Vr2fZTWMGMt6wOm7/QDa53/VaH+fC+xvv3r97W2vLTd6Gu51fP1ed/+qub3udZPoNTp6EF6aed8H5TbUd5bftGV4iCi8SX5n0bSlrO9LAZBFm/i8MqMaXz7jpJ6imhR9VorQo/156NFN8DLhgHWlxbqyQ0zCVo8FgnAX7PH8AuZr7xjoQCBWjWMDfJtifpicB808io1vHu0p72Cy0ZrjEeikOZZEpdxXIg1qSN/yuegv1HSnKKlOmEbvjvJm
*/