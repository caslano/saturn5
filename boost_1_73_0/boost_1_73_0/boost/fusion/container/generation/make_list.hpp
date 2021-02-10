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
ghSrSc6sot1j8MAvv3UiZTPtYpc/ofR8y/caUDY7FDOhCQWdV1b2L7/JaId15nMOnExdI6LYcjLCs8OyosqDPoKq8PlIvv3ogKeVBSxA2jhJLCmdsR5Ay3HBoQdBeHMYB3EgELBrq5gLm0cnYdksboRXqU2ndI2hs2Xxi5E8CuUoemkvYK4eGUlc5IaHZK09d+UGPLQgGLvVKY42FnmyPNua2dPtGVKCcSx2MqOyK0xUrKItsjMli+aeFPHCusqFrYK3rf0cxCp4UDlCe6whby5sLXlzECvxh1YrkLiGvLmwteTNQawUfgocTg15c2FrySvrzcLYmOx0iPsa0p6jiquIOZDywuHBLf7GDqzobIXtzrP45P9kSsn8L88bMT1lg15OeKYZuFnP+vpf+cKnTu2X9p7/2ZQrPKu4iZSLH/qmYEwtlle1yXZqJfoCFxnyTAueeiWe/FcMUQX5Fj8asGrKkURC3kEJL+gSOo+giQdKlnhhJ2ZJU9HYRqE4SEzQyQIyzsyey6s81uwOE+xWhmrdn+asV9Ub8IORyjtQ2GuGmghzIctPTPGpzuyp6OibWdy3SZfzwgIf8vmp0Buw622hD7DBK3N9UHTwTCHzTJzgyi9Njb5IDAAt7BnUkrhdxGRa+LRMB0spqiCo
*/