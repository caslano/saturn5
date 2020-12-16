/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ERASE_KEY_10022005_1851)
#define FUSION_ERASE_KEY_10022005_1851

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/query/find.hpp>
#include <boost/fusion/algorithm/transformation/erase.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename Key>
        struct erase_key
          : erase<Sequence, typename find<Sequence, Key>::type>
        {};
    }

    template <typename Key, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::erase_key<Sequence const, Key>::type
    erase_key(Sequence const& seq)
    {
        return erase(seq, find<Key>(seq));
    }
}}

#endif


/* erase_key.hpp
31bOq9N5w1o5rynC8/T9Km5oK+fl6LyxSI7tvG/GtZxXr/P6tnJek85LbuW8wxGml5qm/LZyXn6E5/GtwCyXOsR63iTLec2W9NzPQ4YrH62clxPhebXDI7O7N8Lz4ka0nl/fc03njXC4D3qpnTsLDoW9rXEvwuj1lV4/6fW3xq+Q3kgHvYG67wbBNDjYUl81xhl3bphxjiYkR+ctVDtmpLdP5y2RX0thD7gM9oHnw2Hw83A8zIUz4Eq4CF6o9u4iuBrmwSqYD7fAAngTXAXvhYXwe7AIvgA98A1YDD+Gq+HJ+FcCz4Cl8By4Bk6Ga+FcWAYzTvLHi0h7MD4u68H4VuNGPMZ6+D0V/rgF2Q3+9fEZX44PiiWRw79fhSu9wTElvF7SQpxiS3SkI9ULCcSYyLzYOc5EEb9vIn23eBPX8vft/L0BNiGKP8FLJOcjG/j/A2C4WBRZlS3xKDZVBsekqOffe5CXkE+QyVXkA7HHqthSFRyvorEqNGbFYfxMqeZcfsuERYg1hsUm/r0Nscey2F1NucID0B7T4lC1c1yLXjWhsS2KahTfgjLYVEMZIJ/w790wZRrpQ3/MC2Q9ZX1VvBn7YvL6lvgXK9e3xMDY/G/27gWuiioP4DiID1JUNF+pKSq+X6j4RkURn6ioqGiUPBUU4QqooFSkllqui0r5TElNKa0orShxQ/OVUlG5ZuYapZWaJqWl7Zrtb+78GefOnctD2/189vNZPp+/X7nMmXPmzJkzjztzZi71TxSPhdGLNEFE3lybcTE4aC99bIygHcxnHhKXvZg3Fo+TsXHenbEy0nbox8sgPX9z68I8sQ2fuyZT75ShDZ91SDYfQyMo2XYcjT07Sh9LYy1pThEZzLsI9WNrNEhRx9cIRP0YG3uYNjKFMg0mHZ7nd7MxN24+5VLmcTcOpjgee6PxEhdt/I0LKWUbg8N7/p1xOAL5v0cW5cMsYhif5aHZuBypfV2czs8v+/gcbgvUMTo6oHWcDgzCZEwnisfs2MP/c/EUGsfuaJyqjt/hrcjvwZhK1BlGWgxg+fVjeuzhs1A+8+3O9pCqje3BSeKd8T2S+cyT34P5fBjqx/pIftR2vI9sfo+k31xMZBNnCNfdLk7eRAixmMgmCgn3PS5OPkQ0kUEcJIqIBm9SHsJCZBC5xAWizltMT0QTGcRB4jrh8Tbv2yJSiV3EKaJiDu/0IkKJZGIjcZA4Q1R8h7ZPBBJJxFriIHGZaPAueRDRRDqRS5wn3PayDEQosZTYQ+QT54lbhGfu/8chsf/57z3/Py3lz3n+/2sOSNyvKc//z4qJC49JSix+xpy/VXfn2Mn6t9ETRk0dOCFo2NQA/4n+AeOd1DEAlrR30sYvjq0g18SogGa4G28x76JlHsrxkjb4amTMtGnF31sno8mPfA9bqVbiCtJShFlRs6ISEtTvZtNkTFb98/9Ltc+484TlUj5L57Ns9dlABg9Qp1urXIusbb3PVHt+ORN195zL9+W2z2MM08ZCZRTeRLkPwTA2bD0nl1pF6Ek9eGPIXyi75BGKHa35Mmiyk/WeBW36aKaPwaO66QPvjBk9N04+89V9xh27yjxsnm27LvX/u9yXcJP4nfov/KtW/9xJNWac/1S/oODiW6zL8X14RQ/rsiaxzqz311ZLV8vr1sN2LN5oF8Nz71IOj5Um5Sj1XlDHZdAve6HJuwNuk2eaWZ7qg94RUQlJZb7/3pjvIMk3RJ7xry351iL+IN/MEvKNDouJK8+YA8a8h0jeZ+zy5ke5R6SEvOckJERx7zYN9u7zHyH5h1Yy5C91Xlh6/srQ8mUaP7u0+j9j8oy/cy/lASNHZVDvBfkz6j+ksv3yVyA=
*/