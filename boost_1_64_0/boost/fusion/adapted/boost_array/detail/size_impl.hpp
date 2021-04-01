/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SIZE_IMPL_27122005_1251)
#define BOOST_FUSION_SIZE_IMPL_27122005_1251

namespace boost { namespace fusion {

    struct boost_array_tag;

    namespace extension
    {
        template<typename T>
        struct size_impl;

        template<>
        struct size_impl<boost_array_tag>
        {
            template<typename Sequence>
            struct apply : mpl::int_<Sequence::static_size> {};
        };
    }
}}

#endif

/* size_impl.hpp
6x9ahxJEC1Lbyp4lLXY5v7m0V02vbP146kR0DoofgqlRmMGKuzYyUjylY43mL3TCeXPLbpjRx4jfr4tQDrqMGbcN3Z4vAN+dZj9EWEZAV0wHdC2lvPmyOHXwYXtzwD0r3JPW7IpqwP2DFVOE/Bfr9wWVupX4E+Nah3bLT4b3B+5RFlMpbk0NFJ4DzClDk2ERLLXRMZecVCoxYAydt96+L6S2qoGl2Byri4n4ofXHquEKce/20aidcebHmDBjjzhgmPOY0zkTBL4JBoLEZMRHKO/qgGPi2YVPKwIaEwDKkgoPKwBKX5xxNwJNZ/a8p2zr8opUlFmhBCPCxJnzx7QybX4knTmBdrA6AW+qvBbkLJsqqfmIXfYnmi2o3LRJ5BqXKrVdWmdYqPfBRaaGfbfiwd85zFBsDy0alAkt5PBH4iX2joRwIRymRX+Dw1xbIHQiie8A4VOYHE+5u7Pxxz3pRz9/BDT+GLqFMd48DgQzU/5XpiHaxBA1kQkXtThya2PX2rqiHrg3SYoBN6ymlloB4WTtNBV9mlbNp/957Y3Mvg6pRIkPmWAAdpuYSA==
*/