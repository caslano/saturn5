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