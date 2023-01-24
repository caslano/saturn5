/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_IMPL_07172005_0824)
#define FUSION_BEGIN_IMPL_07172005_0824

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>

namespace boost { namespace fusion
{
    struct nil_;

    struct cons_tag;

    template <typename Car, typename Cdr>
    struct cons;

    template <typename Cons>
    struct cons_iterator;

    namespace extension
    {
        template <typename Tag>
        struct begin_impl;

        template <>
        struct begin_impl<cons_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef cons_iterator<Sequence> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& t)
                {
                    return type(t);
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
m4S0FX4lwi4EhQOEicA7+C+cGr2F8UjtUqvhOKamcMqkLhNuoPah8cS8G9mT4nrMCskeHxfd6xdk5rNjEKKXaUCL2/QjWoxMme5dDdXieAnGVZ+P8NCAFG4JSsQteOBd5ToPJSTzUMTV/VDWH5GLKEXGpIlNdznOX7WdSu18kEaFbDNm4HsDBQae8KAMvOpBGXjBgzLwNw8mNDBQuofEcquUcluVct8p5T7ywE1OD4I+0Db/HiCUHa+Una2UnaKUHYMSVERIPETmKsuhm0h75FkAxrwSFcFvsiKiJCoiiYoologoGilTHen80xeO5q0G2x0Ip1rpfkU3DLJNshNM9AgqGFtTEMycOC6YO02pYL7qhwXjM4IK4nYyFsydZHp9Mdm5YJKBCnK2FiJhECZhv01nQImqQDwctLXpBuMx40T2JT0iDwwUOe2qmW0QPurVjD8RELXfcqspHFJFDLL5U5iT4gfhPVeyGc61siytrrbt29zKEyUX4iQ+1WwOTg6HDFMgif0cm+7ZfjBAajYVN1WhR3l7NAN2UEfFYTxIoeNBJBoPyEcBfN78SRkP4PT+qBuJ8h+JsgUf9HbREw7D3qOZexYlDPmRiDlafaG3B1x0k0/ZdK/HY4saaEEBgU2utX6H8vWC59n+RdPh1MGP0Y034rUIEVqjfKOqbc9Hsvx6jspWw4WXUb5s050GbZHL3lDNLc7+AymbURN3
*/