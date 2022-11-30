/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BUILD_CONS_09232005_1222)
#define FUSION_BUILD_CONS_09232005_1222

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/list/cons.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/deref.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <
        typename First
      , typename Last
      , bool is_empty = result_of::equal_to<First, Last>::value>
    struct build_cons;

    template <typename First, typename Last>
    struct build_cons<First, Last, true>
    {
        typedef nil_ type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static nil_
        call(First const&, Last const&)
        {
            return nil_();
        }
    };

    template <typename First, typename Last>
    struct build_cons<First, Last, false>
    {
        typedef
            build_cons<typename result_of::next<First>::type, Last>
        next_build_cons;

        typedef cons<
            typename result_of::value_of<First>::type
          , typename next_build_cons::type> 
        type;

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        call(First const& f, Last const& l)
        {
            typename result_of::value_of<First>::type v = *f;
            return type(v, next_build_cons::call(fusion::next(f), l));
        }
    };

}}}

#endif

/* build_cons.hpp
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
*/