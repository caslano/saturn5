/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ERASE_10022005_1835)
#define FUSION_ERASE_10022005_1835

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/erase.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/algorithm/transformation/erase.hpp>
#include <boost/fusion/sequence/convert.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct erase_impl;

    template <>
    struct erase_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename First, typename Last>
        struct apply
        {
            typedef typename
                fusion::result_of::erase<Sequence, First, Last>::type
            result;

            typedef typename
                fusion::result_of::convert<
                    typename fusion::detail::tag_of<Sequence>::type, result>::type
            type;
        };
    };
}}

#endif


/* erase.hpp
AFFGhkmRfaOsdhFJKhIePtKtntowI0KgMA5lZGlB5iTcDpDGXe0hxAJksKRoMc0QmjBhCvbw4CqsUHVnsv8WWXTlTCGjjlYEtjKwthrbIMCt8NKxvoTfjigbMr6gUBcIzEuQ6Ljq4ztXEiZLLKmUIkCbjYMh4oY6sLAFT/EXGlQxmWB9LJuLtx35NlxUhmMVj7eSoorsWxSr9ivYveFJ6eHra1g5HjeJuEn2v6nxwg/rjo0YsyIB49NgvbduPQmwCgdn74IPJx/Ozi+JfoN/PNWcxD5hpaQ1RUhVLwtRi4XS5LC5/MYdJpVKrzbLV8tHCXlxg+Tk0cm1PShkTSenDLbzlDcZikf6SuTeazh0ux0oDJ5UsVLaQV6mjE3lFCMbXzKJcakpJKrUUhw5ZNhsUTDM2DdXPxDZ1O62g4ORZbyX5dskOAXgGLHAzowaYigKksx9ibAJ5NGx+b+Xo33lUd6f2Lc9rgR+Xip9V9rTsyP1HfFubzts6xU6PyoXvCRWx9TmKdExecN82XzuGT9TTHylyQVzmjatlySfk/hVawefPf1rqe66qv/Uilc/5UzpMvnQW234xnnuViyErJzUCGssb3ZCw2IcItVPISTIV2rnrBThj5awQK8RrtG26ozjB7/dDh/S/x5QDban
*/