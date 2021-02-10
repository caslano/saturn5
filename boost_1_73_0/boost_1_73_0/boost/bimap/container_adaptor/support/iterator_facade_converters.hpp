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
mWFR65VOdwjhR0aJqyKDIPgBRJGGm3tUZZEsLLG1vBFR+9Q6+LuhafWNSGdQhg7Gc5rMD2ghjDI9upvc/Da9vaG78Ww2vrr5RNMPNL76xGC/T67OEHoFYQXJh7yQBsILUmmeKBnVMv+6z6DTGRzSydn5/PQ9y7+eXr+BXAFxErFR2dLanVZJqZBdcEYsQsmUJ4OGCRg/qixMqkjSiSkjpf3V+52jAji7Z5woLltwzCpYL+KvIKOs8EYJJOya1cCD41NIoEkkb4r0qzVM1IKhXhurvk0MkYuFSlSJ9PBpUtKiUklkOBxsTq7zN31G8sONHI69TJEqZSGQabU4pCfjtRL2PNEkwZUGT7lCKdgCakAL+Z9KIYYNAP3dPxr6Q46oWOh7y87ui2SsMkmXtxc3k+D6fPZhOrsMfhtffQxuJpfnnCt/G0LKaDgcdjqmFKUKCYpW6JilSuW9SKi8z/S6e69V5HW+dGj/NV4ed3AMV/NR12NPIvGNdQgoKmmTHO+4ixgZ6gwOg39DaUlkrsMVa0uM5Zf3AWjoHXUTnS09i3l1e3HhHbcElaMYWsFOnNPj28YIZobqKPy4u6+xXMuit2+HTlCYzsIasWsJG4X6jqL+6dVOo5873K5b0mqPtrLEA0ts9UOEOcWyLY+e
*/