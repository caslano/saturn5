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
LhzTcn36K2uTN+ZTGy/vUg0nHlJWMyNS6vTX9v+SHOM2px1rr3dF+6Ej0LFoETodPYLYg7Wt3yDxXXcjUuSjY9CpnMk6dA56BnoF+jLhG0ka1xkoaU5JGsx6F+OovZiT5j7pdnI+cTOd5KQu5D0pI5W8l2DQJenUtbanx9FH0Qgab2ePoPFrqIubsF5+sN8Fjpgmbaz0SGn/Znu0bmc67TJOEhudXqPHDN7c0bC9GsOGxsP6
*/