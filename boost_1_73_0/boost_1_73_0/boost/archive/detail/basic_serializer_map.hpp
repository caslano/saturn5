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
YWqgqaqE6PaoF3I0mAzf+5QJ/FFMTk8+DkeXZ2I6+vWUq++2JUo6YnI6Z/vaFxsLG9Vw7pOuHKioDm1jevwHHUx7TZQCYWq5pZCuk7V29LWhNE9j5dRptVzIkNPk78w9l7lrKuvckbAZ6jafwLfBHNakphqlS3WGW4D13AUj3lIa/2G05iKRS/3wZvi7QRQHT6E9N6GT+fbMNa5UUU6+ol6pOK1TnuBfuTsGJsXQNCgmTrOnZN2Pvsx6UOypTZ/7WU6G3WW/FkmVN6kv1+xnvLT7Z2yIcbSLlXebqwm7fDfh2KTj43A3CIKuZ2kSS44klHsGliS9TASdErvbO5rcF2SSHC5V7UU1nwfODPJOaZAOSbHOcefIrFGTXJlbk/Q516VJ9bmU7MyeRm7bXNpmdMPwpNiUbXlkXuy0V9iAvMkNur6KxsvxbjLjrZUbVRSbNG4adxu7TIUk7dB3hq+D/XhydX01vDp3SLPCsUhU60LxNe+Pk3N9f03WK1jV46RwI4CsCEwMY7nSydwjvGnLIrYNsUUNwDQ8LftTb2cVxdAfTE6n4uRy6kDsb0EIEbfHjwN5f309FnbMvansffuyrlbd6WYKv1uWsljBiaUhphmKqLINJy5uXz22/mh8+2p7PBgEKvWpbXNA71Mv
*/