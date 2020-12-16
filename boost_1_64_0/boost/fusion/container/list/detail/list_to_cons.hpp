/*=============================================================================
    Copyright (c) 2014-2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_LIST_MAIN_10262014_0447
#define FUSION_LIST_MAIN_10262014_0447

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/list/list_fwd.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_LIST)
# include <boost/fusion/container/list/detail/cpp03/list_to_cons.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/list/cons.hpp>
#include <boost/fusion/support/detail/access.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename ...T>
    struct list_to_cons;

    template <>
    struct list_to_cons<>
    {
        typedef nil_ type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type call() { return type(); }
    };

    template <typename Head, typename ...Tail>
    struct list_to_cons<Head, Tail...>
    {
        typedef Head head_type;
        typedef list_to_cons<Tail...> tail_list_to_cons;
        typedef typename tail_list_to_cons::type tail_type;

        typedef cons<head_type, tail_type> type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        call(typename detail::call_param<Head>::type _h,
             typename detail::call_param<Tail>::type ..._t)
        {
            return type(_h, tail_list_to_cons::call(_t...));
        }
    };
}}}

#endif
#endif

/* list_to_cons.hpp
y1aM5SxnOctZznKWs5zlLGc5yx1pd4Ts/03NUM3/Nc3+n2K/b4HOfp9fi9o2teYq+6c+NuxJ0GxbTZ506DXgh7KnVSppRiLHIBHIy36MpZqnqTdv1Ki0Zd+W+xparQxCWtbeQ3a9sj/PRJ/sJpSBcf+YEovR9lW16NGDRLvCLvAG9Kgy6iHlUf89BWb2Ay/vqtlK8Wjv8PUqNV3bjW42gfLE9t5jsu56vdhDi/mktp6yx6vRuprp9dEnso/BTS+72MTbJGPpG5ACrgn81KCXarcrPXGyol899Gp9wjuO8H7pyqEWmq56Gz6e92q06mA8WyIF5hjOlsDfsIdD0Yz8i3+wtifEqbExzz6t5VmSeyZU7hnfPYY8a9v3mmp3sj73zfBq7b4x7Dcra21+35RXm+kqd04T9DXT7bzPtHvH8E6KOtq1N6srMhC5hWuKHNfzFlYtKMrzH5+TlZiRnZaY0yC7kn195LkXv2CTd+Qg2WOwX/RJlzOhU5B+hK9y6KOmjyKH3AvT3rBvnv04hj3zk6TsnLpNJUbZC2ViBzNS1lLz/tL2INhbNnwPQnPtNWjoHgHzvQ+e9gg0fM2/+Z6Cw78X4J9a89/Qtf1Tr1D3VvRs12/Zrveetc0ZHrZ0W83ljVvbH2iTNgqUtS6GOeCrUK81nA3bwznwBxiDJEi4SAnnBSMkXKGYNLwddoCLYHd4BxwMF8NhcAmMgHdCpz7lEm83E31yZC57BvSGMyVcCSK/7/zuO8KdyP+rJdzFMpd9KTwdXgavgBPgVDgRZsF4eCdMgPfCyfABmATXwylwE5wKK2AKfBOmwnfhdNEnDf4C02UNawbsCO2wC7xSv/ZUfocfk/zq155GKuHgWBgEo2AcPAfGw2g4HY6Ds+F5cC48Hy6BMXA5HA+L4QWSjwsl/QKb/K7DTZJ+e5gn6d8tawbugQPgcjgU3gsj4Qo4Dt4Hx8Mi0WslTIT3w0VwFVwMV8NVcC18GBbDDXCd6FNmk99cGCn12El+4xTnJ/V4itRjP6nHAVKPATALDpR6HASL4BDJ/1BJLwg+C4fD1+AIuAMGS72dDhUlQqAPHAn7wFEwEJ4FQ+BoGArDXPXJ77Dn+jxR6rMzDIJdYBz0lnLrLvXZQ+rTR+qzp9RnL6nPkyQ/vlKfvbXnR35r4VCT52e+lN8COBAuhNpaUAmXLuH0a3uul+d3HhwAb4Bh8EZ4ObwJpsACuLilrV5rJepztoV+zYP7eocgJHeUx7UMso7BcP6Fth6hP6JfhyBn1ZucU29cVyDrCbS1BKwdcD+zXlsr4BOorQfwcH69cb5/L5T5feb1XfP5zOU3+Sz7NhH6ufdDz7sHRDrm29Og25n3zKubn3sfOMYxlx4FTebPTefKCxGZH2cu/NBn4st8NnPYrjPxQ+/zsiUhhUgpsh05iPgUMReNJCELiqx5XstZznKWs5zlLGc5y1nOcpaznOX+De4Izf9Paa75/6t727Q55zKZi78N9oa3wLsZ7Kt63TAnJyZ0Gz+PGwcd50VxQrzu3L4+Tj/deVEp2rxpqvjpzjXHj0vVs09KHXtkbUvhmq3o65pLlWvt05VD+PVn3CVtc1yX5zY3GStz70/J3ORGmZus2mZaDurUZFPmUs3mJnPeMMxNanUUdJTsoxY7gzPhOuKrfMOgm5gNbrxOUkcyX+1eR3Ztwlop+7iWXHuUo+xvf7N+ZR9a6bjuGrd5+61HmZd9SaVZ/pp/PUHEW1LubvfEAllPMJu8doUz4F3EV/SWqV5MDasn/DVatzhtrl+JxrO+G94mfTmrSfn86Tvy2e2+Wdza/Nku327UPznj3/dsF7ZSJ/DU++vGHfW7vyLeNX8=
*/