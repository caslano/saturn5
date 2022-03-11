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