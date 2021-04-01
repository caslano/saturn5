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
Oh5jL6P3pYzkLXknuLkRiebsby3ZAhRX+38IBB9X7Sak0lZ1Fhhp8VHr/+ANAYAKWJdEjZ5fDTpBLBmyPVG2cnRr8gG1Nn/aNjdLEfoSxIhQa9fXaTQ/GVy2AyQ9rPVL+YsKcfTVmck+DNcfvWUOoXgH0rZtq6v3QK8Ev8Dk6ajuIvgFOo9iU6U3zOzWdaTgpBZZucYM+83VGVm1Tiw6P51DpJuoRGDM0ON7AKGlWGUeibHQ1DMN4/X1SPpCJoXXT/9QFzVjFCjVo93r4ACwbaVqowYcmSrlDyvuBsUUZc8ETMtrsAvZgWSOcvPGPeqMulnmWNNNo6L5xmlTDQil8OJoLRH4RpyVrxzv4taZxxyvKKmONTXuyK23nl9KPgfxqYA7Ve1xaHIIJiex4pnMraa46U1NOEDQsdbFbOxrqmm31jXs5araFZ+wgC4Q7ra6otvsZaVgz1WMnPR1+uekmaeNr1pSifREV6b8vOVI5ibvk9wUQfMiu13spTtJ9SrZYhGp7wpKEB9qYZ1T5ixaCSHqEfm1XbK/UP16hfFJIjGTKEhbKq8HnCsa+A==
*/