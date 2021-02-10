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
zGt6R3CGUDcT65GNkV5135SJYeD3uA1tRFfkQfNdvkNz0bejU+eNNxug4JxHKq87RDbDZxUlvK2HR/9YbsEM1t5Xz596H/2pnyws/WritHsDrFqGKh1mm2nuJ97q/qJagpryOJ7+13MjPtkJ1cjJ8EW/b5AZLnh53mnqyH237x6axNEkmUcz+OpN5xMrogrfPtIcfJIGF1pRmpId47Ti5TAFujdbZzifXcyCy1kamOmknZDYHffseDIBbxoHOHQ/Rt/sBtgoGIT1m5APBta/UEsDBAoAAAAIAC1nSlLJ7Ho+TQQAAKIJAAA4AAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9UTFNBVVRIX1VTRVJOQU1FLjNVVAUAAbZIJGCtVWFvo0YQ/c6vGLkf6kQEXy4npWnTUzmHXGgcQIAvtWQJrWE5todZyi5xoqb/vTOAlTh3UXLSYdkLy8ybmbdvxtZyBPs/7DIsgoMXr6T7JnjhunUKGvk3T/W3HZLkHvoPOi5xfUWoCTx43Sd78Cqvexh3XskQ65Tuk+QV4ZaUJP1MyHmZ0C3u9J6D/1TWd434XGgYT/fg8OTkFziAt28OT0w4Y5XgJUSaVyvefDbhNOt2/ijY7a2l+HsTuAZW
*/