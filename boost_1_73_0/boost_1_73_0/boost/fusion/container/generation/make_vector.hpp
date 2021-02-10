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
liSloGotSUoh1VqSlEKqtSQphXRWFIUyesgstSFL6jwGi6IGnxE/d15aFeY0uyhGFUAwoR3DKObKqRtqJWam+O23/w9aVEqyei0qBVWrRaWQTgpzqDTN9MRUeBEebhoqClhpYnnTUSmgvdAp42p6vlG9xw5v7V1rvRvzqtczr9Eo/g9QSwMECgAAAAgALWdKUkTjgYNmBgAAhhEAACEACQBjdXJsLW1hc3Rlci9pbmNsdWRlL2N1cmwvdXJsYXBpLmhVVAUAAbZIJGCtWG1z2kYQ/s6v2LG/GFcB24mdpMl0qoIcMwGJIhjXncxoztKBrhU6VXcyZpr89+6exIsAx8k0ZED4eO7Z3Wfv9vZyLKZpxKfQmYz6PbcT4MMe9oKbxjGOipTv/9A+/XGvBpzCs6/AvAN84dPMGObyLx7qw+gg+AzlP5z1CZ/PGWnDZsrnoAnPT/kMJ2ZKUFl5T9+D4DlDn8g3+mjTzE8BfcURnEYzOzJb5mIWazjpNOHi7PwNvMDHxZkFXZYKnoCveXrP85kF7yMz8mvMHh9biv9iAdfAklZFNY6FAiWnesFyDvg9ESFPFY+AKYi4CnNxj3+IFHTMYSoSTLM3vOu5HyxYxCKMiWQpC1CxLJIIYvbAIechFw8lR8ZyDXKK05E8
*/