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
9CImxB203zAT/k3SPJOv8gTzXT5CZLwCl7PkW2NnO1njp2n7K2nT2SX+NEQXbODxreH1jegVv+TFLYOdkessPlNlwA1ls9W67md2B64pabtNOt0zk51O94VX1bfP/WWRwa1WJqVS4iVc0CId+p61Es7BLNN3sEPpUsyibQ5A0kQ5k3jkHpk9p0dH95x2yojs6Ty8dxdL3U4+y+zz3DPitifq1sM6zGdz5Lt4unwXa5un7Xvr
*/