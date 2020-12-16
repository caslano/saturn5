
#ifndef BOOST_CONTRACT_DETAIL_DECLSPEC_HPP_
#define BOOST_CONTRACT_DETAIL_DECLSPEC_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// IMPORTANT: Indirectly included by contract_macro.hpp so trivial headers only.
#include <boost/contract/core/config.hpp> // No compile-time overhead.
#include <boost/config.hpp>

/* PUBLIC */

// IMPORTANT: In general, this library should always and only be compiled and
// used as a shared library. Otherwise, lib's state won't be shared among
// different user programs and user libraries. However, this library can be
// safely compiled and used as a static or header-only library only when it is
// being used by a single program unit (e.g., a single program with only
// statically linked libraries that check contracts).

#ifdef BOOST_CONTRACT_DYN_LINK
    #ifdef BOOST_CONTRACT_SOURCE
        #define BOOST_CONTRACT_DETAIL_DECLSPEC BOOST_SYMBOL_EXPORT
    #else
        #define BOOST_CONTRACT_DETAIL_DECLSPEC BOOST_SYMBOL_IMPORT
    #endif
#else
    #define BOOST_CONTRACT_DETAIL_DECLSPEC /* nothing */
#endif

#ifdef BOOST_CONTRACT_HEADER_ONLY
    #define BOOST_CONTRACT_DETAIL_DECLINLINE inline
#else
    #define BOOST_CONTRACT_DETAIL_DECLINLINE /* nothing */

    // Automatically link this lib to correct build variant (for MSVC, etc.).
    #if     !defined(BOOST_ALL_NO_LIB) && \
            !defined(BOOST_CONTRACT_NO_LIB) && \
            !defined(BOOST_CONTRACT_SOURCE)
        #define BOOST_LIB_NAME boost_contract // This lib (static or shared).
        #if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_CONTRACT_DYN_LINK)
            #define BOOST_DYN_LINK // This lib as shared.
        #endif
        #include <boost/config/auto_link.hpp> // Also #undef BOOST_LIB_NAME.
    #endif
#endif

#endif // #include guard


/* declspec.hpp
+hyDv8vcB/PqHtCf6Oe/X/iZMiOX/wcN/wRn/N8JvuML8X+fxQe+abxBXzkatq8eAbgrY+GPAvwtVL7PxK/9k9oMQh9l+DjAJhrYkwCbYGBPA2ySgf0FYIca2K5qkJU92xfgW3ge8OWOwxjiJTXUdtfCxDT5ek7hRVgP/ladPafwklmD9lS7n4lnK338iuDW4X0afpeMLik1SsieDg48ATqH7njF1mv+6vDwsItknYmX9lo13k0R1gNu9gRAuG3rR3jjZQrXzfGIcmJhbC929WxKE6AvxjEWU/pGHcenH6bzElEtEpI4cnKe4B/Aa+lB98F41wcsP+0DnO//1H0E/c/nt0Tm+wRP9DrjeXBmo7/YtVPjDGF88KFIf2ygF+8w/Rv1eg7/be0NEHPL5DP/o58rUvzVtR0d5lEBC4OzIHuNjhu33G/z+OV+m9vG8E0ABK21BkOlD/KW556b8eUdHtoG43Yi4eC5mEKWJ+GEJNad5E3LxqligOaXePTUpeA2yb3L/OUjjZ362vpmEL4B6PqKuv3ppfv7uCYTfZXrq2pvcZ00xnxYwVPwdsxhIoeMrlyO9EgfLBddJTCtr1lsugKAu3r2Gp1RCHDH78lUDvX0NFN+Av0QPp3S2mZXJ/r19spaUiLtGg/f/2ZSHuqzI5ZzWS3HtGdJOTcWtNxRptzR0mYsV0p5gXf53oTecnXOkTp5/Tf1F+bv71t/O+Hg+jGP0gg/BsbAXJAnn0eRtJOHuZfPOnGX6Z8Fy72DmX9OUZj5Z6DS5oXSziYP3huF2HzH89wbIps76al+K4D5qbq+RHR9k+jmRSPOr9bGNY2tML8MQO9oHnCdHRsd18Yl0sazpY1LmTcOd5ZEHU3t5EzOE71T4N4ATYTxfVGWSYkfMy0TIE3zS/mdFcjXc5Ainzo5t1cO8ll0kPEWdZwshTnRL/63SplLC2EuVZmxXB1QbjmM1aVG96wAWLWBnSjpM8Um3yj2n5vjmN4OcMdfGu5w1Rv+GoA/4oX5awQeCM6w42XurAKeJM11eCCDk4x+PdmUaYW5fDLU/yORTxvA3Tz/qZmfHZSn/sOlon+dbDdXopzzvE6gQ/wzDuqMbmibPfN89fTcdp8iuBNzcQuWQLtPo79xH/AeSp/J90SQrwnee0EemkY+EZ/PlkB/HG90W1jXCjmzMlfObSL9iJF/vXxbPN6MBSe/PqNXNwB9grOteLzhP2b4/4Hpr43A/9GGl0FT1s6VOMD7Avpw03L51shjQdc8GA/4zpzSAlyklYa2CtzQoJiVQMPBlhoa22BsCg3LC4/N9xlerA2xHWQ2YOK7fVDqdPm4H44U7+8rfOd0/zfF3A8/B/gszedztYwzoSCXz49IXQsC/FeL3TnOAvMGHfC92PD9cYBBOYadL3rkPRBT6FNGj1xgxs6F0Abiz7WDfyl7lkxlLTQUvkDsuYsULjxb+MU6LgBOMMCheHJiv7s03u24lPKVrylGtl8EeZxrZHWZtJXyTZ/y3p/lt8r06c7lOg4kDXMDyygvODe+ZmSwwPg5vy60CSa0hR9oox1jV41cP/+w/qtVFoxrYsTJ2JgMtu61ZmxcZ8bG9aongQb6Tp6Q9rn/OTYcwfEczovwHuR1MGYiopduhLYtkHmg7bKyvRlklVfg/6ysbjH8uR/K/1YDjxg9+GMzRnWcYh23L7dnRaEefc8DcBRu6fxUZEUwlbWWUXzmD8fiz2V+OJ2Fa+QvKB99ZQRn/F8KviuP+PcAPtL/NY5HwME5+huhea7h4bcG38HZHwgyd3xZf9yDCpf2WvhDAF8QUP5hgJ8bAH8E9NulMmYucHlGjzxq8KaLHq81Z4//RHj4Tsw=
*/