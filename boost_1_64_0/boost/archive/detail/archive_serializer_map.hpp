#ifndef BOOST_ARCHIVE_SERIALIZER_MAP_HPP
#define BOOST_ARCHIVE_SERIALIZER_MAP_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// archive_serializer_map.hpp: extenstion of type_info required for
// serialization.

// (C) Copyright 2009 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// note: this is nothing more than the thinest of wrappers around
// basic_serializer_map so we can have a one map / archive type.

#include <boost/config.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost {

namespace serialization {
    class extended_type_info;
} // namespace serialization

namespace archive {
namespace detail {

class basic_serializer;

template<class Archive>
class BOOST_SYMBOL_VISIBLE archive_serializer_map {
public:
    static BOOST_ARCHIVE_OR_WARCHIVE_DECL bool insert(const basic_serializer * bs);
    static BOOST_ARCHIVE_OR_WARCHIVE_DECL void erase(const basic_serializer * bs);
    static BOOST_ARCHIVE_OR_WARCHIVE_DECL const basic_serializer * find(
        const boost::serialization::extended_type_info & type_
    );
};

} // namespace detail
} // namespace archive
} // namespace boost

#include <boost/archive/detail/abi_suffix.hpp> // must be the last header

#endif //BOOST_ARCHIVE_SERIALIZER_MAP_HPP

/* archive_serializer_map.hpp
lW/NCuoEthAI6giUlaIQ8+2lldMSqcDNsrlOWq+zbNi9sWWvozrTG5q9LjYClFQe39smdB/gkupV99GtFbwDb3qZOldcT5Mw6buNIFJhrAdYAC8WUHkTUvTtVriuvZz3AWi+exSXFtHILZBkZ0x61b5VDnwiyWylUzsBDzSf6rwZjiljmfe3LS8c7tR+ABzFuAJmrRP5JeKgh0+aBWQzQh257KUvsj10j+nIWReCsXBfnQ7F6a5nqAMHd6GtcEnnXlPPLQZ1T5m1zRzAdiFaqr0TtakrZKqIb8qXaiHmM0enSxQeerRmM74qMagvPrMqYyFNWIkzhlISqowpR8WWrnN9fjdQ05buGHNTRxcglnFoiXlyBvpuCsIUNyNAwmAD06CSx8MpriGCGsG5sPCKApF2M3FdOP3P+9lBzU+qHInQGQ1OnDKkQE1Q3ROpHP/g//pJtEW3xlhND2s6NGPwQkC0BepNlJkPFAnsFTPpfkt5Id/7PoS+p+R6vONp9w8/tdqtwno/3R7gg+lSkkNjPqg0m75NksxBgTDHEeXh1l+f2xTc+GstwGbkoA==
*/