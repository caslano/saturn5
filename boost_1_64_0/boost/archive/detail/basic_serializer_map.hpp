#ifndef  BOOST_SERIALIZER_MAP_HPP
#define BOOST_SERIALIZER_MAP_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_serializer_map.hpp: extenstion of type_info required for serialization.

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <set>

#include <boost/config.hpp>
#include <boost/noncopyable.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>

#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost {
namespace serialization {
    class extended_type_info;
}

namespace archive {
namespace detail {

class basic_serializer;

class BOOST_SYMBOL_VISIBLE
basic_serializer_map : public
    boost::noncopyable
{
    struct type_info_pointer_compare
    {
        bool operator()(
            const basic_serializer * lhs, const basic_serializer * rhs
        ) const ;
    };
    typedef std::set<
        const basic_serializer *,
        type_info_pointer_compare
    > map_type;
    map_type m_map;
public:
    BOOST_ARCHIVE_DECL bool insert(const basic_serializer * bs);
    BOOST_ARCHIVE_DECL void erase(const basic_serializer * bs);
    BOOST_ARCHIVE_DECL const basic_serializer * find(
        const boost::serialization::extended_type_info & type_
    ) const;
private:
    // cw 8.3 requires this
    basic_serializer_map& operator=(basic_serializer_map const&);
};

} // namespace detail
} // namespace archive
} // namespace boost

#include <boost/archive/detail/abi_suffix.hpp> // must be the last header

#endif // BOOST_SERIALIZER_MAP_HPP

/* basic_serializer_map.hpp
fOCSyrzQ7V3n7IqGn3LCYOz78TDwxMclLcPZiHpY1/sHk3N2ggBvKl8DuH8hH+tqWxa5oNxhU/YGflMAzwi6w1b24epFfMTuoPekrKptSdHGlsM0skThiQINcWNlx3/6sQ9u97+xtCmJdrmpAum+wLzADK05XHspEN8mX2GLtRLNx/rnUbbDBNnr9YZVaHrBl/yaXSIUJGk/HI+WzCEXquY4H5vX2U3I18XEgkl+JboVPgCpPn5W2Ibb8B3be8PXtKZJ0VsuQX+5RFCxqUpfsSGn+xaDuW9Zo9q+3EmdpHvIXE2lYIYSQAjkvvDBCOTTOAVKvJc7rlnmVVmFedd4k96ye8sl+xvA29TBw2eqjyDy+DbMubmVTU0+WibOsuJ91bG+PvsBkhrdHRu0xVDfy1uGsUaF+sWkcsXH0EYiOm8Zf6fqmj9QhLIzEUtMNAlQLs2y3TXXIjaQFhETfBAmp8RSpMs7wCKLxRsa8JFFrUOzC0rq+OJMbrBbihdg7/XlBySAD676qhYnfXN9KO9AlIVN7I+xt6DBJW8uO1i9NIBmLQYycO0tdyqx8g==
*/