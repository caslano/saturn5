/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_AT_10022005_1616)
#define FUSION_AT_10022005_1616

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/at.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>

namespace boost { 
namespace fusion
{
    struct fusion_sequence_tag;
}

namespace mpl
{
    template <typename Tag>
    struct at_impl;

    template <>
    struct at_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename N>
        struct apply : fusion::result_of::value_at<Sequence, N> {};
    };
}}

#endif


/* at.hpp
ndsczj08ES2DGj0Whr60rDSZuizkamMh4kha8kZVaAhxwEWZRJgjaKqMK7vYRh5MeEwtwPempvM3A1mhMzA8OoeT8yEsmBY6gl9OLn54/eYCfjk6Ozs6vXgLr7+Do9O3pOzHk9NXmHqBxhTwq1pxjcYViFVdCp55m//eJxkMHokqLZuMw5CyN9fcNHVcDHsTz2nC5bZ42RfIpMH/tPiWkhVfSbW2WpKJJVDJtIF2lSWop+KCPwP0o9OAwhlfNEsvTrAMz1AhMvaVNHDOlyteGT2kiUA8I2WpY8FNHku1TIhwicrTw6dffvFI48aCRJ5+Hh/ETwZky2s9Jlcz7qJA6o3GNPp1UwljuDbPYP/w6ef9LOdNZVXBkhsNDKqmLKdEEFExynbNTAGXmDykkbEsdLqRsH82vEq55VvNtHa1SiuIK7Umdq2QZTmwNJUqE9WS2EicU02JHMfVZ98dAwUEPiDSZWPqmMg7FwtUToIM0LRauwIf7Xy1A7tos8nzMbC65shzTEFjAGsF+YaarY+mwKrOFXNQo9yjnpzdPFipOMvWmD5eQdrQ5pEHR86+vXhzdnru37AAWFnK1ELUwS2oPBpToyhhUC1tatKCKZjcyUyKNWzATYoKZcaDjwMALT7wOfpelejEC9KDDyO3
*/