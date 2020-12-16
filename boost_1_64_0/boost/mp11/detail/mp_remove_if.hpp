#ifndef BOOST_MP11_DETAIL_MP_REMOVE_IF_HPP_INCLUDED
#define BOOST_MP11_DETAIL_MP_REMOVE_IF_HPP_INCLUDED

//  Copyright 2015-2019 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/utility.hpp>
#include <boost/mp11/detail/mp_list.hpp>
#include <boost/mp11/detail/mp_append.hpp>
#include <boost/mp11/detail/config.hpp>

namespace boost
{
namespace mp11
{

// mp_remove_if<L, P>
namespace detail
{

template<class L, template<class...> class P> struct mp_remove_if_impl
{
};

template<template<class...> class L, class... T, template<class...> class P> struct mp_remove_if_impl<L<T...>, P>
{
#if BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, < 1920 )
    template<class U> struct _f { using type = mp_if<P<U>, mp_list<>, mp_list<U>>; };
    using type = mp_append<L<>, typename _f<T>::type...>;
#else
    template<class U> using _f = mp_if<P<U>, mp_list<>, mp_list<U>>;
    using type = mp_append<L<>, _f<T>...>;
#endif
};

} // namespace detail

template<class L, template<class...> class P> using mp_remove_if = typename detail::mp_remove_if_impl<L, P>::type;
template<class L, class Q> using mp_remove_if_q = mp_remove_if<L, Q::template fn>;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_DETAIL_MP_REMOVE_IF_HPP_INCLUDED

/* mp_remove_if.hpp
1ML++Zn8HO7JY8f8d/1U/M9lKv4nCuXNZzqLbw6sHFaQLZJvi3FBkkfqWvlW9/mc6Lit96qJxphtTqjbh29U+6oME0ThfcTFCh9T/GoKzRWkNWYkjyefaGzxQq2CNxhcrjl9kVOB+OEbUQ60VmUkviwQFzkQT3eAKtHqvNWjAfXNi3YG1BFOd1++Qa3IUxgiA/hc7WuFo5tO3A9cHJG2vcVZnF1tm2nIVPAn34cI+PQRf7geDqP4X0tBn2tjevY+kjje4dINHjZfpj6+vUiLn0TCSxd/Qem8n784MLW4MxPpIbY5c9tKsR+Dgp/NoRjP86sQgaflNUWZvyuvfZT5XnntpcxRfhVadDO/Ks+bqiEOAYl9AQlIjx2bCzEBEZAhSEAIm5xVKwQE6cIsfoM5Zvy08laNgBQQJ8JEYYGW8BYm6MyIuLdkuJLPzxECsi9j5IwyPj1wkcLIdxdQSBskESShfmahsyPftImXtedN9O04D+zrkttfgM9UzVOfdTb0Y17Na8xiCCZdKtDO0YLqpIABanR0LTyTKcbBX6lWGxw1hTBUlGj9vE71+21ISN6PTg6NsBYs1alT7lGl2wIucDIQX+aSgcBJV1uzXeDAlNB3vwbO1QROmun4FA2cM/uBk+FAHM/erUofjqVlYp4/XSbmWG4qxRTmLvrOBbwc50oZeB+pJcb90OQxMDAEJpG7s7Tk5yFZeE3q+HunqcRHUCdzPOrffXY2q2+OM4voTU0L7VM38BZKUeOl/FaZqp9a6yWqfe+lagQifibp3PNeCIR8p2rvaGyvymtX+8vr9Wrb+A1UBJWpkiV+r4DdXW1VnKZZ1ZG1fTeP6lJJaABQyOVrmAbKi5Q1S1nRAcZq+YoC5TFITNzvocpUjsu1HDGneDe7k/19vkq8ihL7GAyvA8ZetT7K+uVLFBgnojvYlFo/Zreu1BIO9FEfqWX0yLPeuUM1MAxLTaK9qkaT4VjxecV0vc1OAxTQKksHW72AzqiptxfIQt5Praw4RFFV3SDTCuLCAG6cSataRWSR/D+arUC+AfN/lXAz5V/j5B8DNUiJvy5QLYTR2+tyyEyeItOdPD9bpGrdN+dymj44kQv4ONcc5ntZee1BtzrxsuDBjwMTO19z7WNHMizLiSeeqyD5CScSAk/RKXacvFO7kJ/sSmzPIs3s8jTsLd5ctO3PXqFo5gLaQLd9SWMm04qZpK3391MVM0mD3gO+XE2KSE/Vmck0eYZZ31ugmMm9kiNsKhgp3eAj/e0QqCQahvhsHYqBxGJFTYqwLaoSp608jy0/+f2X/pz4mO80YvxiusGHAqgGGobDKiT9ggGrOymBZ/FbmsMPMoe0eo5u9xEbxFghTcHJAw0ToCgHd0OelA7JF1WEnoSa6AOel2/MKZixC5ZSQcmnTte74BODE60OEED/aNiNhggq/jfUWsuiRuZ86vGANhkYcPbYFTvqxtsBmAPLmLN+/Ur91p7C5C/yjPDq3NdV1ZDrX99LLO2QFhCd2Q6U6TCgI5BiSQnVO6RxXM3dGNKoByXJ2ppmliS/d43EJd+7JRJXipiTr5EaYvB/Utruc8uuKm0R3ol0/88CWE/aLVPNxxZ56kvt08ynz9MChZ7vJ7enyqpg3XmwyOxbDyCQ2On6wjrGrxaWurmdFmy2ciasDyzqsyPq0voIPIHxVLrgE9cKcSIpGVZx7u1X9zVvGed/ri1TgF2XEMRiYtNbctsFxGFkcZWhfY7Fz83HNnnqi1Vg5U7+vCHQZEc+EHfzPgK1L0bx0bBUyeK7ckI8mjFIrQdIvOWBu/mK+qbNHLr0lOaNvdPBKuVZil4aSXFwSw1g3FflKDRYQIVe3Qo=
*/