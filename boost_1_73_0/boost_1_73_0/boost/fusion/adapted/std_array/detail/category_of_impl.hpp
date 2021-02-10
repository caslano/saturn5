/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_CATEGORY_OF_IMPL_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_CATEGORY_OF_IMPL_01062013_1700

#include <boost/config/no_tr1/utility.hpp>

namespace boost { namespace fusion { 

    struct std_array_tag;
    struct random_access_traversal_tag;

    namespace extension
    {
        template<typename T>
        struct category_of_impl;

        template<>
        struct category_of_impl<std_array_tag>
        {
            template<typename T>
            struct apply
            {
                typedef random_access_traversal_tag type;
            };
        };
    }
}}

#endif

/* category_of_impl.hpp
B9BtTJDm38g4b1Jzixbn2ftPRLuTbFtpGE6OYPzy5Qt4AsdPxy98OCWc0RoSTXlG5daHV4W1/FGR6+tA0dc+UA2kDu4AriqmQIlSXxFJAe9rllOuaAFEQUFVLlmGXxgHXVEoWU1hEi8uovkbH64qllc9zk50oCrR1QVU5BMFSXPKPjmYlkgNokQExC+Y0ojZaSZ4gPQUNJWN6mFMEKRWAsgnwmqSIR3RUGndql9Ho7yTNWYyKkSuRvm+FEGlm3tZXWA0DdmBaDVoAZ2iPpjzPjSiYKW5YonQ2HZZzVTl34aFhLwYCQmK1nUPh66MKpcChaSvlm9OQovRM20uSnBl2K4q0dw5iGXtgcpOcqTDsuC5QmDhfeh4QaU9bwuxZ+mrbEv+nZbdxl6A4BgVDMIEomQAGVFM+fAhWp3H6xV8CJfLcL66gPgMwvlFj/c2mp/ibDBklUCvW0kVRiGBNW3NaHGH/Icq3QtW5zBZL2fxYpWuF7M4PE1P1mdn02US/TWFZzAYv4Cw29oBH8CgZpmZAPgleH4cPEWD+ZZSonapotr0Gv9wrBQiJ+cwD99NvW/Db55gi7FxkpZUSixd19aCFJB1JRpAsX+ohUku5vEiiRLvJ8bzuisovDK8bhir156lyAXa74czNE/gcYVj
*/