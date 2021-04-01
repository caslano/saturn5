/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_IMPL_07172005_0831)
#define FUSION_DEREF_IMPL_07172005_0831

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>

namespace boost { namespace fusion
{
    struct cons_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct deref_impl;

        template <>
        struct deref_impl<cons_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::cons_type cons_type;
                typedef typename cons_type::car_type value_type;

                typedef typename mpl::eval_if<
                    is_const<cons_type>
                  , add_reference<typename add_const<value_type>::type>
                  , add_reference<value_type> >::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return i.cons.car;
                }
            };
        };
    }
}}

#endif



/* deref_impl.hpp
XtvNHe7lLgTGPKo92BUPyAV6xNrZvgngtaIGo4ANEY98kLpmPcpOl0rXlhqvTwhld9oFJFrWT0BlhiRyaYW+MTMML1SWw3SUle58M6zjfKfb4iXvu4f3MrCSWzJt9p8xbUrdMkYYhYp56G/J99dvr1rsvczcqad0Or26poguq/t+i3tCzgJ8RZn5J3H3pBqa+gGR/g5Qi6xCb6kv535n2zC6LbwRd5XNI05Xz1JvZ71MTRvEJJHIAVLX+6DDfXT7HDiKXuvqaKCRUlVByNt1Oes9wm4pYpiDIbwlzfvXjfDuXQsOtbsjFXWZ93Juj5uNvVgLpT34I1LhSYyuw4dGGq8MhJI+005D+IvaOAJ1iCwFx8sa6HkY/bMteRf2qOzlFwjrBkBZgGwVxI3q2IQh1jqNCNW9J3MqdoC6IFv2dR3OiIhGsY41yUK2bNpj48ZloEajyqvDgW0Xhh3mquSYJb5sUWHJg9U9ARKHvMSP5BVwmtWlln17v+Wn3zBW4qRuo8fhek+Gb5VG6NwiFaRdWLW86u2j2K2mg9ZDW1PJA7ddWWqL61c47oehGA==
*/