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
a8tvMjsXXf/n83fFcdVE4Lk5xpuM86V9a3IeEMcNyhnh4Qt23WTe6ir+qMtP7I9qAq/8/G83mbSjnrF/cl0i0idw75v7bzILzu2Z8+tqd5E+gWt/OQz8T1pjkRc8INJ3QXjLjjM3mSzf7RHXukV7UBP4+9Slm4zm+4J/5lIS/wS+a+bvN5nd+eNe8fpdhJsIPOu+nptMwkGL7eEz0vggR/ihf8o7mNkvM+O//KfIp5rAtX7jOpgdM3JNpT+Icqsg8NqCqR2MvuHKSfXPYr8zEbi6YHYH89no2DFtt8RxkiJ+724//w7mzSubz1zf96hIn8AXHg3uYLr+MfZwxVnJPgk86yFtByNfkRJ8JErsFyYCr1i5poPxn36CMr4i8T8c4c0RmR3MhL//vOORVsn+CXzH+Cc7mAP1L0z68TdpXCJweu+mDsb3F+77eaEivonAw+9/poOpf/rduxdLHxHpj0D49tU1HcxPd0xF13vth8Bbn3ilg/mhvf6FU6mSfAg8PmZ3B1M8w+ePV/WS/RB4j/LDDmZDXdSs7LXS/KJAeOPbn3Uw9999IPzbF4JE+gS+f0xdB/PyyTL3n++Ei/QJ3BR/pIMJz3+revtnon9iEuDFp0GPZ+4/Ufuy5J+MJPoqutDBzA9ZGnw/I8LVBO637EoHs/3l9w6uK5LoE3j6H791MKPH7awtUYr+oYnAeaO1g1n8xgNfevuLfFKj
*/