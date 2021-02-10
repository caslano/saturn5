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
wnxa/Zn1/PnV3eXFyDrxWEz3lw8vq8BYY6Mfr8Y1lOygXzEOjZQSSj41piuMJaiCt7MVV6ARkr+sL/3exzISkkGLGoA7sBomn/dYANdzZxMwNsimGHQNQWQUhcwYLUDzLAQQCe4cJUKQzSiMxqVHM39K4++DdN3vG+BwQHb6QL27G9/i6GgtkK3WgcV2Shu7gmxBZsVhKszad4zJvh7c9G+HVyNS1hdYo0IIyqKeZEoRBK484mTiE+CLS9l/A3yh3wxgdmER1eD4NxViga0zLhaZvQ0Uw/MRjuEliJSjVsFwd4ZOgSzuqB67sqY10rNC5Pw5zNJVtzd3AxM5Mu2/B+1YGUs/QlS2EtgRWLcJxZLzpJWYgva4Ne6ZSdfWoK/gin2R9XoCeYMLDDxHDSaLY3Pv7KwhniehMiKMKdKqrcJ0ZzIdsbxV9shtSmaUgL1YUjFOVJ6HlSF43usxfhskfUjBQX4ANQ6unJZABEZeHDZoYg9wps+4MJMoMXz71rvFGIh6rYYj+sRDVWSwZ2dbtNWfzUf1UrVg2rad9Rur9twh1ppwVSZvC1ZfhVBNH4o6ntVbSOy0Zdr8gSKTHW7Ju31If0cwlSaC38WDg4xKcfjX4oaCj5DD2LiWAtFRuUR4aQDgH4YSjQWQajy6
*/