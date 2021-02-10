/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_FOLD_UNTIL_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_FOLD_UNTIL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/fusion/support/detail/segmented_fold_until_impl.hpp>

namespace boost { namespace fusion
{
    //auto segmented_fold_until(seq, state, fun)
    //{
    //  return first(segmented_fold_until_impl(seq, state, nil_, fun));
    //}

    namespace result_of
    {
        template <typename Sequence, typename State, typename Fun>
        struct segmented_fold_until
        {
            typedef
                detail::segmented_fold_until_impl<
                    Sequence
                  , State
                  , fusion::nil_
                  , Fun
                >
            filter;

            typedef
                typename filter::type
            type;
        };
    }

    template <typename Sequence, typename State, typename Fun>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_disable_if<
            is_const<Sequence>
          , result_of::segmented_fold_until<Sequence, State, Fun>
        >::type
    segmented_fold_until(Sequence& seq, State const& state, Fun const& fun)
    {
        typedef
            typename result_of::segmented_fold_until<Sequence, State, Fun>::filter
        filter;

        return filter::call(seq, state, fusion::nil_(), fun);
    }

    template <typename Sequence, typename State, typename Fun>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::segmented_fold_until<Sequence const, State, Fun>::type
    segmented_fold_until(Sequence const& seq, State const& state, Fun const& fun)
    {
        typedef
            typename result_of::segmented_fold_until<Sequence const, State, Fun>::filter
        filter;

        return filter::call(seq, state, fusion::nil_(), fun);
    }
}}

#endif

/* segmented_fold_until.hpp
087G6tXx+XW31B01NIxn83zLm8sgvZljkBQ6kpc8SJKIUfSZzGcM7YhHgZ3B1dLk6CBGq43GZ0udxsJLMPIRIN2nXgjdCccmW6dt160t9yU1yk9kSqlD777o7Q3iPElmQHWazG8mOAzeT5BAgGupc/B4YTpvcWKAz+RPwqSSCcOxpXqWpLkbGjmyLV+KK2KMuyW7kTHM0lpioA0JOdz2DJCnm1ROhE7kDD16RLuFzG7FCPqNZl98PgMLjPNvJJ6EE1/wclPIqFlMuRHviLLHz51+FJJXiL7Zs7dNU7NXFRvT7PvvSTWC0ccgHmp2nIFzFNaB+UkFYhiS50oD6xi3GxQNS8cc5yeyefgFDFUvt/YlOqhhbPfTvNO1/4oIlqeruOQQ0McEtENsJfoNp6qcA8UCnWqxjeyUDE77aOV4C3oHKH1Hhkj6kcFWYDhp+YzBoz/nQdFqdeiQCI60JR9B3kZJvAvyN5+hHDt7RQKCew6xqEkeL7PT3ppph+rx1khGlU819rft5s7ETzI3hvJko+107UWgcBXN1ro7YShYX8iDBQV7NKNWF+j54/5bp/ndfvH+oGZKzNnkIR45jzRvP/qnl91r9N3/1b26Bv/rWoge4M693rCtv9VV1xucG14FonCAbINJAyOGbo0j
*/