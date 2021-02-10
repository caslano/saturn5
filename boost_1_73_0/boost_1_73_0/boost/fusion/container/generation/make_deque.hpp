/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MAKE_DEQUE_01272013_1401)
#define FUSION_MAKE_DEQUE_01272013_1401

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/deque/deque.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
# include <boost/fusion/container/generation/detail/pp_make_deque.hpp>
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
        struct make_deque
        {
            typedef deque<typename detail::as_fusion_element<T>::type...> type;
        };
    }

    template <typename ...T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<typename detail::as_fusion_element<T>::type...>
    make_deque(T const&... arg)
    {
        return deque<typename detail::as_fusion_element<T>::type...>(arg...);
    }
 }}

#endif
#endif


/* make_deque.hpp
eJE0qrQcrfCJ9wnjYOMubKBYb2NTzCsTr9VsV5Eru9mhRMC8c1UkJBVKaAx0JuXYmAglZGX4ZFclEeN9EmWDKaljVTgjuSrXJga+qWRH0c6JEkNKnIEi2wDCJY7FDYAvkpdkPO8MgFx2E4ea5HCbZpNxsOUyOrgiOnOMLOgSL08hL18S/sXzgrJrSR7tJ+qQeN8EWVg+8ei/NvyqC0QI4wWe+xFK4fM9E1PL4VdjLFKpdOAdp85S4dc/4N5FSMOR6LMND6UOvmAljohOLW+6YFtR4oPDkAXfxCsurMBG/7VGoPBynKteDx52NvxynfDGDvgBCHCq5PYOugTwPdHuu4M7CAr4s+3Fp5B8x+7E2dYEv0YmceRHQjc4xMXvvYhETm2vC6XAO2QQY0WtaINMpC12l4e1XsO/LD7b/0MxMjuzxKlr23tDQMsO3pqBrQQ08gxAvkufqHe03ZDy8ePHn6JbgKKIkQwYyDveYhPbX66hWc5XdrIfFs8/gb7FWQ1LAEPhZ77ftGj3R8TC8G4wQOoR1yvc4+O4Qcw3luwQ3+XbkLiZwhssY02BWSyTyz5CC3gv855FZtZKnITH0DvJs/GQaFtGcNaE8FokBwRmH7A2I3XkdEXDiuiwwkq7XnJVUmn+UlEvLMc8zNKq
*/