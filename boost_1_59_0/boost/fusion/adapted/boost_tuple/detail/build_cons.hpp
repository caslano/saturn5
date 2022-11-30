/*=============================================================================
    Copyright (c) 2012-2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BUILD_CONS_10172012_0130)
#define BOOST_FUSION_BUILD_CONS_10172012_0130

#include <boost/tuple/tuple.hpp>
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
    struct build_tuple_cons;

    template <typename First, typename Last>
    struct build_tuple_cons<First, Last, true>
    {
        typedef boost::tuples::null_type type;

        BOOST_FUSION_GPU_ENABLED
        static type
        call(First const&, Last const&)
        {
            return type();
        }
    };

    template <typename First, typename Last>
    struct build_tuple_cons<First, Last, false>
    {
        typedef
            build_tuple_cons<typename result_of::next<First>::type, Last>
        next_build_tuple_cons;

        typedef boost::tuples::cons<
            typename result_of::value_of<First>::type
          , typename next_build_tuple_cons::type>
        type;

        BOOST_FUSION_GPU_ENABLED
        static type
        call(First const& f, Last const& l)
        {
            typename result_of::value_of<First>::type v = *f;
            return type(v, next_build_tuple_cons::call(fusion::next(f), l));
        }
    };
}}}

#endif

/* build_cons.hpp
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
*/