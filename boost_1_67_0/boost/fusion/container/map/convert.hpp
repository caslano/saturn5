/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_MAIN_09232005_1340)
#define FUSION_CONVERT_MAIN_09232005_1340

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/map.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename It, bool is_assoc>
    struct pair_from
    {
        typedef typename result_of::value_of<It>::type type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static inline type call(It const& it)
        {
            return *it;
        }
    };

    template <typename It>
    struct pair_from<It, true>
    {
        typedef typename result_of::key_of<It>::type key_type;
        typedef typename result_of::value_of_data<It>::type data_type;
        typedef typename fusion::pair<key_type, data_type> type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static inline type call(It const& it)
        {
            return type(deref_data(it));
        }
    };
}}}

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_MAP)
# include <boost/fusion/container/map/detail/cpp03/convert.hpp>

#else
///////////////////////////////////////////////////////////////////////////////
// C++11 variadic implementation
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/map/detail/build_map.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct as_map :
            detail::build_map<
                typename result_of::begin<Sequence>::type
              , typename result_of::end<Sequence>::type
              , is_base_of<
                    associative_tag
                  , typename traits::category_of<Sequence>::type>::value
            >
        {
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_map<Sequence>::type
    as_map(Sequence& seq)
    {
        typedef result_of::as_map<Sequence> gen;
        return gen::call(fusion::begin(seq), fusion::end(seq));
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_map<Sequence const>::type
    as_map(Sequence const& seq)
    {
        typedef result_of::as_map<Sequence const> gen;
        return gen::call(fusion::begin(seq), fusion::end(seq));
    }

    namespace extension
    {
        template <typename T>
        struct convert_impl;

        template <>
        struct convert_impl<map_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename
                    result_of::as_map<Sequence>::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& seq)
                {
                    typedef result_of::as_map<Sequence> gen;
                    return gen::call(fusion::begin(seq), fusion::end(seq));
                }
            };
        };
    }
}}

#endif
#endif


/* convert.hpp
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
*/