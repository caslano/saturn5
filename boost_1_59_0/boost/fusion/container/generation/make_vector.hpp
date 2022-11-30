/*=============================================================================
    Copyright (c) 2014-2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_MAKE_VECTOR_11112014_2252
#define FUSION_MAKE_VECTOR_11112014_2252

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/vector.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
# include <boost/fusion/container/generation/detail/pp_make_vector.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 variadic interface
///////////////////////////////////////////////////////////////////////////////

#include <boost/fusion/support/detail/as_fusion_element.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <utility>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename ...T>
        struct make_vector
        {
            typedef vector<
                typename detail::as_fusion_element<
                    typename remove_const<
                        typename remove_reference<T>::type
                    >::type
                >::type...
            > type;
        };
    }

    template <typename ...T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::make_vector<T...>::type
    make_vector(T&&... arg)
    {
        return typename result_of::make_vector<T...>::type(std::forward<T>(arg)...);
    }
 }}


#endif
#endif


/* make_vector.hpp
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
*/