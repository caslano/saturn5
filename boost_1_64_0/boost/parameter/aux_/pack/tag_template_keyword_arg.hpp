// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_TAG_TEMPLATE_KEYWORD_ARG_HPP
#define BOOST_PARAMETER_AUX_PACK_TAG_TEMPLATE_KEYWORD_ARG_HPP

#include <boost/parameter/template_keyword.hpp>
#include <boost/parameter/config.hpp>

namespace boost { namespace parameter { namespace aux {

    struct tag_template_keyword_arg
    {
        template <typename K, typename T>
        struct apply
        {
            typedef ::boost::parameter::template_keyword<K,T> type;
        };

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        template <typename K, typename T>
        using fn = ::boost::parameter::template_keyword<K,T>;
#endif
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* tag_template_keyword_arg.hpp
v8J0kBHhvqJjaTBy1iRUAhbTgKuqksBoU1mQmJy63b/XjvquQBYF0bzY2IzjVIaTzmPk7BBRr7eNSDuguOUNyGPiKJNZC684orJa6xzzGpnTUQ7Yg0UMm6g8092JTPYn3FLCircwxJy6EFcFS0fyscTMFSRDaXKtzE4x6iODtx9iKIK8rUiZg1+SwVPndbCgUEiWRBZ/aWWyH907XqdlUYBq03IrhKO7o7nucSr0luPU3+3IZ3oK0E7mfDIe4jLnE5CCywpd/IYNjNcqFrN2gTsOnjHnpkWEgExV7zAJ2ZXlaUBLJWOugpSY0MKt97Kj3B01b418CL/jSDDNXim2rGM2rUQXlST7ByyHqecUNM3n+idi+j7cKXjCOYGiRF4Gvbwpd/LeoTsdbpYdGMzX4zBJ/VG0wnQJH/MzLSYTmDnyBjnNQtJtgCJjsKZ6UDSs8KwY+CN9lTE/7kTb4LgGBKGEtdSBnxPN4UJYaf6t158/Y1PgEh6KykkmKXWH2QlJHnX3a3Fz4pj01Iw/1RYvP8sedj1Dv4G/z3C2lry3eV0+bWxiMzoJS9JIJw==
*/