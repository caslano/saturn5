/*=============================================================================
    Copyright (c) 2014 Christoph Weiss

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_HASH_23072014_1017)
#define FUSION_HASH_23072014_1017

#include <boost/functional/hash.hpp>
#include <boost/fusion/algorithm/iteration/fold.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace hashing
    {
        struct hash_combine_fold
        {
            typedef std::size_t result_type;
            template<typename T>
            inline std::size_t operator()(std::size_t seed, T const& v)
            {
                boost::hash_combine(seed, v);
                return seed;
            }
        };

        template <typename Seq>
        inline typename
        boost::enable_if<traits::is_sequence<Seq>, std::size_t>::type
        hash_value(Seq const& seq)
        {
            return fold(seq, 0, hash_combine_fold());
        }
    }

    using hashing::hash_value;
}}

#endif

/* hash.hpp
3A1yf1ZhdHZPYDpfkomxHY05ee6G9vjE5Qij0H60xclH9wfxe2fYO3ddN2Z2ppbDsQaMaTu753me8d2zH+3L4ATjPZsvPx9w9pUzPvo2vlfxINTfR64S4ccRsxE+uo8CS9sCkG8LnHDcpebropVRFyjHK67jeeG4yw5wG3eR6eReGeIN2L4gv6XHM+Mu+ZeAkxl3aYKTHXcZgROMu9QRNw7ykGcdcr0UvMy4SxOccNxlBNzGXTZfeT5gobjLWH8bjruMwMmMuzQzOD4plHcEXnbcZQxOOO6SfxnwzLhL/icot4m7NPE9x13QvsCCcZU6ZAQvHFfJvxx4ZlylCY6Kq1gd2TxP8qgrujGqvbwm1vEF9BHEXgbwUaK/hmMvvEcRaWTGXsZv9Jx94irNbySc/eMqY4qreF5mXGXrceDsG1fZfAp4Jq6yozFUn4z15/4JmW3sBf7sS3uOjb30gNnYywjtnB17GYMTjr0UIF849rJpcBt72b30hOeEYy+5lWuncLtOKxiOXadNTCCfYOwl/yakEYy9bCKP7NjLjuLYdVENMtjYyxYwG3tpvvUyHrOxlzGw7NjL7tvACcde3g48GHvJtXy59om9FAzHxl7GqGMbe9nE9+HYy47FVftuXdmPJ+nYC+bja3pcx154LgaeGXtpgpMdexlfEnLsG3vZhbzh2MvEVUI4j4u7t/R9a5/Yy8StDMfEXmqGY2MvW4ZjYy876Ov7x17GYz9vZMde2OdBcRXNtbGXHXDCsZcRxn0bexmTjz7GsmMv+WeDE4y9NA1uYy8jcMKxlzHwcOwl/xzgwdhLE3g49jICnh17GYMTjr3knws8GHtpatzGXoBnx17G4GTHXvLPAycz9tIEJzv2UkP/srGX5u8SHbWxl82fADOxlxG+C8deJr52FY/b2EsNWDj2sgU8O/ayC0527KVGsRXm2NjLFnAbeylMA1Oxl039u429AA/HXnIzBjexl4Lh2NjLpubY2Iucq1NcGqlnXXtAphLwzNhMAZxwbGbT4DY2s2M44dhMrn1tyVP2z96rVBrSmqzBFsf3iN80UG/AUnEZZ/e61OT9vftxvZ8P+48efZUw19vCmDMNT5kPPcj5mCweHfRMyZl/7H5cLefev9BvbWxI5N88gbJbXir/0X5cnz/sIs3VcbeTwEy8aeu0H8P2iTeNMf+F4035bwLPjDc12z6f/yHeNAI3HG8avRnlMfGmJsoajjeNgNt4U+87aMNgvGmMb7PjTflTliPt963vIg8Tb8rvXM1j4XhTE2lnx5tGhmPXMU3kE443jZFGdrwp3zEcdDbIgnyy401jcLLjTZNvQV7BeFMTsmTHm0bM0esq2O6X9LiNNzXf4fUxFW8a4XcbbxrBzg/Hm8bA94k3vdRwgvGmZgZPlm8Ejo03jYGF4035kcZluk1gNt40AhaON42B63gT+8OAZ8abmuCE400jg9t409hwbLypiTEuHG9qvt/rVyrelNtO1hbheFMBeDje1FxDupnxphHytvGmvU8CC8abdj6gcSo6Y5vATLwp9whgwXjTGP0tHG/K39/gauzYejzwzHjTLnNsvAlxX3BMvGnHYDbetIexJxxvyr8DuIk3NQ2m66iJOgjHm0bAw/GmAtogHG8afQq6ZeJNu58FZuJNY+Rr403508BMvCl3mwTrt9Gs7pYd0Wa9k3lwUCzPgW59MJ0O4fLunPfEvqYu+XEw9RCO/QF+LO+6sVzs42++wv/OY3wbPowfxmP5wMZI+JzyRTM4jThsAN29Cngq9qH2yf0IHBX7wNj3OuAmfgH9eFUcCxjqGMgC2mM7HrPO2PgRr7tOe472IbF/9t4hvM46/D7XFt0=
*/