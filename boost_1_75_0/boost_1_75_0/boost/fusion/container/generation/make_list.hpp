/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_MAKE_LIST_10262014_0647
#define FUSION_MAKE_LIST_10262014_0647

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/list/list.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_LIST)
# include <boost/fusion/container/generation/detail/pp_make_list.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 variadic interface
///////////////////////////////////////////////////////////////////////////////

#include <boost/fusion/support/detail/as_fusion_element.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename ...T>
        struct make_list
        {
            typedef list<typename detail::as_fusion_element<T>::type...> type;
        };
    }

    template <typename ...T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::make_list<T...>::type
    make_list(T const&... arg)
    {
        return typename result_of::make_list<T...>::type(arg...);
    }
 }}


#endif
#endif


/* make_list.hpp
Gy8ayTTW7ygqaWEVqwRV53Ve2q3pBWtxZ4x2NJWTmf9d0DuV53YVvfW6KDd8iFYrMdj4y8f4zno6BR7RUX2e4AwXD851eURBDcuj49LItIf78XrGH29kjD9jtWo+Bc/8mJh2KmB6jNDrOPjd9dtqM8WDV6IHc5qQc+7U/rHty7cW92t6CpFb8XcdoxSulCDn329TJZvZtIxDPqKjGJaG7vXdhah/m7pB2QT8HnmiVMiXGz+idsTzo9M67geH51rvppMkMMCxszqwaTCcd/KdIx08sOnDdxHV+fcqZ9Kv6/GkK38UX96RZADhNhtWiaaAIlA0xTSzE+NhRh3gOYu+C/lBh2Kl9Ke36u6n9Zre9/EX/dR5cE5Gsrkf/eGoTzEnUOzNNHgkCHcWkHAOk13+g1lSAV9Y6gpco8FYNTohGyP5J7gqR4Kttl9usWoMbkHcDTcOhGZN2g8Uuq6YnldVCX3edOtPsfGy3MtHX9oHTfopiUj24Ck+0usn+wRHX89ILXiglWlPqmclNUJJJ0/bRlL6lf6WI7+txl2ytSh31tQCWlhBsJZBm+mQqtaQKqyAOMKqIXo/Sc2hE5DhuJh4WslZ9ukcBjn5zpsxbRgKZrJeMLUdEv1tuiNesxgD+RV3pc92tTvxF5Jz9X7qO+zDzLikA3LoO0zgHP/nu9zaa6zEmpHlXh+7VIS6LsZjSG+FgbvKYIUleHJ/0YpA
*/