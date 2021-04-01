/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_09232005_1341)
#define FUSION_CONVERT_09232005_1341

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/set/detail/as_set.hpp>
#include <boost/fusion/container/set/detail/convert_impl.hpp>
#include <boost/fusion/container/set/set.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct as_set
        {
            typedef typename detail::as_set<result_of::size<Sequence>::value> gen;
            typedef typename gen::
                template apply<typename result_of::begin<Sequence>::type>::type
            type;
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_set<Sequence>::type
    as_set(Sequence& seq)
    {
        typedef typename result_of::as_set<Sequence>::gen gen;
        return gen::call(fusion::begin(seq));
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_set<Sequence const>::type
    as_set(Sequence const& seq)
    {
        typedef typename result_of::as_set<Sequence const>::gen gen;
        return gen::call(fusion::begin(seq));
    }
}}

#endif

/* convert.hpp
4VsUwuzi4+5IycsxXZWJMHial1fT4HzBV4tyDnDSOn6bMfPRiXC8jUlk/jEtWHjpyFRiaawaob73LCL3GkpwG9NePNWuhybQgaKkKPRnv3S+YgnE60d11OUwKpFioc6B0koVAYLuW9D/oJEkQ9odXYy9vO6TmmfrwjliherwANpRv84j25y4gOobCK+FDLfcUe5r4qoE8X209yyW+IzDLffJf1IIS5BdXDAIdrLr5oHFeNg4AioXLKE9Htiowi/JTO4xDObO5qmNjcGm4ADJ2czdB5mwqG1ZF5tB9F9CHuFP6TG6iWzEzC2slB1fCdWDKdFEUrye34+7jY0r7pGdyLhcCoX4KdY97XA4U9p9l9NXZI3xev1psDJaGHYvoU+7xPGyC7JXfQaOHFeGLZCIsHgXcMjFGdk7YokrNOFWhyF1F22d4KW6xUnFMZPxKkHNVALSBMDqK/uzD7JBeShKlM61hxk+nHc4cvTM9v6U6J8N4rXEvpsGX+KUsVdwKyQcglwAg6LMxyQbj+OeMcuLG+mR9di+EH0kyTib8D5lhxUKUfH0QB2pYqxOeA==
*/