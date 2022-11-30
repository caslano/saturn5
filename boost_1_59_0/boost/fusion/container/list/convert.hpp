/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_09232005_1215)
#define FUSION_CONVERT_09232005_1215

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/list/cons.hpp>
#include <boost/fusion/container/list/detail/build_cons.hpp>
#include <boost/fusion/container/list/detail/convert_impl.hpp>
#include <boost/fusion/sequence/intrinsic/empty.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct as_list
        {
            typedef typename
                detail::build_cons<
                    typename result_of::begin<Sequence>::type
                  , typename result_of::end<Sequence>::type
                >
            build_cons;

            typedef typename build_cons::type type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Sequence& seq)
            {
                return build_cons::call(fusion::begin(seq), fusion::end(seq));
            }
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_list<Sequence>::type
    as_list(Sequence& seq)
    {
        return result_of::as_list<Sequence>::call(seq);
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_list<Sequence const>::type
    as_list(Sequence const& seq)
    {
        return result_of::as_list<Sequence const>::call(seq);
    }
}}

#endif

/* convert.hpp
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
*/