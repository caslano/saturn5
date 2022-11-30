#ifndef BOOST_MP11_LIST_HPP_INCLUDED
#define BOOST_MP11_LIST_HPP_INCLUDED

//  Copyright 2015-2017 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/integral.hpp>
#include <boost/mp11/detail/mp_list.hpp>
#include <boost/mp11/detail/mp_is_list.hpp>
#include <boost/mp11/detail/mp_append.hpp>
#include <boost/mp11/detail/mp_front.hpp>
#include <boost/mp11/detail/mp_rename.hpp>
#include <boost/mp11/detail/config.hpp>
#include <type_traits>

namespace boost
{
namespace mp11
{

// mp_list_c<T, I...>
template<class T, T... I> using mp_list_c = mp_list<std::integral_constant<T, I>...>;

// mp_is_list<L>
//   in detail/mp_is_list.hpp

// mp_size<L>
namespace detail
{

template<class L> struct mp_size_impl
{
// An error "no type named 'type'" here means that the argument to mp_size is not a list
};

template<template<class...> class L, class... T> struct mp_size_impl<L<T...>>
{
    using type = mp_size_t<sizeof...(T)>;
};

} // namespace detail

template<class L> using mp_size = typename detail::mp_size_impl<L>::type;

// mp_empty<L>
template<class L> using mp_empty = mp_bool< mp_size<L>::value == 0 >;

// mp_assign<L1, L2>
namespace detail
{

template<class L1, class L2> struct mp_assign_impl;

template<template<class...> class L1, class... T, template<class...> class L2, class... U> struct mp_assign_impl<L1<T...>, L2<U...>>
{
    using type = L1<U...>;
};

} // namespace detail

template<class L1, class L2> using mp_assign = typename detail::mp_assign_impl<L1, L2>::type;

// mp_clear<L>
template<class L> using mp_clear = mp_assign<L, mp_list<>>;

// mp_front<L>
//   in detail/mp_front.hpp

// mp_pop_front<L>
namespace detail
{

template<class L> struct mp_pop_front_impl
{
// An error "no type named 'type'" here means that the argument to mp_pop_front
// is either not a list, or is an empty list
};

template<template<class...> class L, class T1, class... T> struct mp_pop_front_impl<L<T1, T...>>
{
    using type = L<T...>;
};

} // namespace detail

template<class L> using mp_pop_front = typename detail::mp_pop_front_impl<L>::type;

// mp_first<L>
template<class L> using mp_first = mp_front<L>;

// mp_rest<L>
template<class L> using mp_rest = mp_pop_front<L>;

// mp_second<L>
namespace detail
{

template<class L> struct mp_second_impl
{
// An error "no type named 'type'" here means that the argument to mp_second
// is either not a list, or has fewer than two elements
};

template<template<class...> class L, class T1, class T2, class... T> struct mp_second_impl<L<T1, T2, T...>>
{
    using type = T2;
};

} // namespace detail

template<class L> using mp_second = typename detail::mp_second_impl<L>::type;

// mp_third<L>
namespace detail
{

template<class L> struct mp_third_impl
{
// An error "no type named 'type'" here means that the argument to mp_third
// is either not a list, or has fewer than three elements
};

template<template<class...> class L, class T1, class T2, class T3, class... T> struct mp_third_impl<L<T1, T2, T3, T...>>
{
    using type = T3;
};

} // namespace detail

template<class L> using mp_third = typename detail::mp_third_impl<L>::type;

// mp_push_front<L, T...>
namespace detail
{

template<class L, class... T> struct mp_push_front_impl
{
// An error "no type named 'type'" here means that the first argument to mp_push_front is not a list
};

template<template<class...> class L, class... U, class... T> struct mp_push_front_impl<L<U...>, T...>
{
    using type = L<T..., U...>;
};

} // namespace detail

template<class L, class... T> using mp_push_front = typename detail::mp_push_front_impl<L, T...>::type;

// mp_push_back<L, T...>
namespace detail
{

template<class L, class... T> struct mp_push_back_impl
{
// An error "no type named 'type'" here means that the first argument to mp_push_back is not a list
};

template<template<class...> class L, class... U, class... T> struct mp_push_back_impl<L<U...>, T...>
{
    using type = L<U..., T...>;
};

} // namespace detail

template<class L, class... T> using mp_push_back = typename detail::mp_push_back_impl<L, T...>::type;

// mp_rename<L, B>
// mp_apply<F, L>
// mp_apply_q<Q, L>
//   in detail/mp_rename.hpp

// mp_replace_front<L, T>
namespace detail
{

template<class L, class T> struct mp_replace_front_impl
{
// An error "no type named 'type'" here means that the first argument to mp_replace_front
// is either not a list, or is an empty list
};

template<template<class...> class L, class U1, class... U, class T> struct mp_replace_front_impl<L<U1, U...>, T>
{
    using type = L<T, U...>;
};

} // namespace detail

template<class L, class T> using mp_replace_front = typename detail::mp_replace_front_impl<L, T>::type;

// mp_replace_first<L, T>
template<class L, class T> using mp_replace_first = typename detail::mp_replace_front_impl<L, T>::type;

// mp_replace_second<L, T>
namespace detail
{

template<class L, class T> struct mp_replace_second_impl
{
// An error "no type named 'type'" here means that the first argument to mp_replace_second
// is either not a list, or has fewer than two elements
};

template<template<class...> class L, class U1, class U2, class... U, class T> struct mp_replace_second_impl<L<U1, U2, U...>, T>
{
    using type = L<U1, T, U...>;
};

} // namespace detail

template<class L, class T> using mp_replace_second = typename detail::mp_replace_second_impl<L, T>::type;

// mp_replace_third<L, T>
namespace detail
{

template<class L, class T> struct mp_replace_third_impl
{
// An error "no type named 'type'" here means that the first argument to mp_replace_third
// is either not a list, or has fewer than three elements
};

template<template<class...> class L, class U1, class U2, class U3, class... U, class T> struct mp_replace_third_impl<L<U1, U2, U3, U...>, T>
{
    using type = L<U1, U2, T, U...>;
};

} // namespace detail

template<class L, class T> using mp_replace_third = typename detail::mp_replace_third_impl<L, T>::type;

// mp_transform_front<L, F>
namespace detail
{

template<class L, template<class...> class F> struct mp_transform_front_impl
{
// An error "no type named 'type'" here means that the first argument to mp_transform_front
// is either not a list, or is an empty list
};

template<template<class...> class L, class U1, class... U, template<class...> class F> struct mp_transform_front_impl<L<U1, U...>, F>
{
    using type = L<F<U1>, U...>;
};

} // namespace detail

template<class L, template<class...> class F> using mp_transform_front = typename detail::mp_transform_front_impl<L, F>::type;
template<class L, class Q> using mp_transform_front_q = mp_transform_front<L, Q::template fn>;

// mp_transform_first<L, F>
template<class L, template<class...> class F> using mp_transform_first = typename detail::mp_transform_front_impl<L, F>::type;
template<class L, class Q> using mp_transform_first_q = mp_transform_first<L, Q::template fn>;

// mp_transform_second<L, F>
namespace detail
{

template<class L, template<class...> class F> struct mp_transform_second_impl
{
// An error "no type named 'type'" here means that the first argument to mp_transform_second
// is either not a list, or has fewer than two elements
};

template<template<class...> class L, class U1, class U2, class... U, template<class...> class F> struct mp_transform_second_impl<L<U1, U2, U...>, F>
{
    using type = L<U1, F<U2>, U...>;
};

} // namespace detail

template<class L, template<class...> class F> using mp_transform_second = typename detail::mp_transform_second_impl<L, F>::type;
template<class L, class Q> using mp_transform_second_q = mp_transform_second<L, Q::template fn>;

// mp_transform_third<L, F>
namespace detail
{

template<class L, template<class...> class F> struct mp_transform_third_impl
{
// An error "no type named 'type'" here means that the first argument to mp_transform_third
// is either not a list, or has fewer than three elements
};

template<template<class...> class L, class U1, class U2, class U3, class... U, template<class...> class F> struct mp_transform_third_impl<L<U1, U2, U3, U...>, F>
{
    using type = L<U1, U2, F<U3>, U...>;
};

} // namespace detail

template<class L, template<class...> class F> using mp_transform_third = typename detail::mp_transform_third_impl<L, F>::type;
template<class L, class Q> using mp_transform_third_q = mp_transform_third<L, Q::template fn>;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_LIST_HPP_INCLUDED

/* list.hpp
jGCDQQkl18manS8QmsCpyAfUKUItEpbEQN/YO3w6OiL2CEJCAPky5Ns7hPHV4jfgxn/qh/Cyb+G8J8ugYtVxjn1tsCbZLXLE2s2k4Ozt08g5mihk0WLGEXypvay0xLgqxDCixSFSDCKlkjDCALtQkFyT1Mecp2KsrGHD5jukD4JBuroiHxLmYMPDkvfVqdXHU/HhS5/WFA8ifIX9t4JGRMlPsCNI1/qKtbLxLRsMrQBmUW7bvA2jcitai7RiPKs8Oa4N+lyEj7ucxo1y8oSwM4Ex8OMu3iVYp8jdjqiPo6DMuO5Sex73XwiOAwSt/W4uLjj9+7UsiB5emDvWT/xGUruvt0NEkRLTXPQg4LkeAuDSHHxHFR0MENsN9nF8Od6/4Ixy0QMOa5OePQLgjvq0OAOZL5mroTftCOgSYOiKRyLJpr8FZgwxQ9QoaqZYWEFQl5ZIO6gq4KCqjing/fDvpOCUAI5vokkvRN0MWcTXiIl0x8kzg7PSZLpLUNRQPYvjl4R2Iaompe/k4Pdvr+wVrHYvRzGgBOHY7PYNC5jUhQ+UHIOUQRqaFqwdZqcgKeyopHtGOdAJfxE5SC+05Vv2nSVw4PdteJpdNa0G177qrJVkaunlcn2KzRuY25FV26R1mednAuXspNu9aEnfqVh1h2fi5sH5ql1z+hIlO3Ws1F261a797qDoghFMjXGg5oWaD5n69YzvO7Fq3C4o4RAKuNKoua0ABNOim34+YlujDZZS7qgQlTWH1nb4H5fiemPlvCNuWUk6t7EeypNU2xxgOWAwdpldGPUo82Q7etK4bE5kfkm3W17BZmWunLJmY01Cu/jc9SMP0TJUaP2gJAl+nT6MsjpF37RnwYjqGpq9mnp/89zyzKf86IijlYRA1RRa++hNQU4XgmZ1dJ7c4opW8zEsriDRmUeenRF3PL32nYdu3SaxNCxss72MtDiqDSmCw3UejwSbkcT3kJwbnXNTZ/FdMBopN23qTo3b7/IKmFMgeFA2b8ICRsfG6i6KhzCdACQHw4W8T7mL18JJsQtmXSdidZax6rC9Jf/CrR9q8nxoc16YZV/LhJ9S5TJQ4+qV3t5pkOWuQW3L0uQz/yUPcYrxhjfeTeI7/YvnHZ9+UHHt0mOFbJb7ldpyqqPVD4liu2JLuTyu2DWxFs3ViHtZ1z6Bfli+Z8pdWNns6GElWW9pbohkYcWXb8vcgAKD4gYIXvu1pW1vY4jnJiR7x+DhsD7I5zRq43Km7+E523WEKiLhjLmhj9GZ0/U61eU9orrI2H2OYoTWOKza+MIEitnwFfOBHozJcY3h75HoTpPIdcptS90kqWfDdFg7lFDlCad+mO8WOAANcWPVtbFIGIa8XpQzoYA3OJXFFfMzlMd37XHclSQLkSNNaPNhiDHuFD1RiNmYnv3RHSHVmBfNnQpv8DgUu/SASCCD617C9QdfvWD1SUVF2kQ7QKhNQ/0YdiKqxQC3iVI4zng/nGt2e9m8w7vRIEYk/M5uqKBT6mjg5qKega5U9Ad+0p6a1V4x8HwLYHlHnGwPkU3Gjr0kcDGmxHTGNGkADMpNFkQeYMbarhC5OblE8+iJIjQ0eUazSBMc4B3IWbGE41453fwi/lvutTsvSBTX9UcnJDqcY/DwjvMlc2cnqfCOe7Y47dxqi2WiayXFCy+wAmAyGftXrgsjISS+cwN6z8BYUB2+Eo5f1qpD5xajOCfp6aihEc6qm84Kb5im3ZlbwFhbWWdJgmO/Ih/DxIuP7ZeWr8hl9p407LHqdTxhMHjDPbmNr83pvioIchNGajVn0wnJadCiTszlizo1QZWqhkZN+D4oBRv5TjLWaCMwSNHQH16HaNA+KxnbeLBotqx0MOYgc+S10Kc1RjmmMhqiA+Kap6JQviyOp2fOF8dZLtHQqX7bhB0Y9bAkhSMXLjEkXKm3WTXMc4ZhBaO4jx9bNUaiIJNDChR6j9fDjChsh1HzolrW7KDQEp5NCKSuQ75pKJJvuxiBwGhFU1CzavFFi3xRp0ZkNP63sbtKrKKhK+g+JW5G/+am1/E+l2tvrYyM6xEO1Zky0SbPc9U9DKlZJkirhSpgiVCzgpDyNM+39QxDkttLA1MsTaMEqgjJxCXH8vaKCYkeKAYRvcmaNW4vkuzgHFeotXJNpQ/Xk0TVrt1Rt+VhUy/eCQ/XlP6dQ9v5pQBREyn/gmuMKmRRUggmAI1dGTm3eysqffRoIoX1b01F1FvVld3uSsUCn8KPN8b6d9oj79dLXeNtW2v19IilCq5ZbQQenhRXPtHy8MWyzgNwlKZ5EaEALTUhfMAOWUlpeD4rJtJmRcAcxgZij1zj16tJg/j6LXl5vKK8NSH4feP4lbH8G3oDIpA8XdDtXWI2/oHdqpd4U/d0PpBe2xvD9ZpCNyNjnNvjbsJ0YkPmfbyBg2aMGp9IKLR17A8KgbkjD6j4gq9yFdIhB0NMJfjsZvByCi815x5Q8q2kWBfOEv45G/gOJ3Uqx2lOXmVpZrzhUmBpL/bxVlBDQ80FpSTzLkc9Y+XCAKkNMDoeYnz56u1MpgtmMPwvHAAXobOF2BMIuExomctdZu3vVQn1JfNpMmZCs42XeIdf4ap1NtzN1pPR0h6AA67hNkhqec2SHjWPtGTr/BhIOgNPSWkVQ12EYy9dwuvm+AS0HPssQwQBMwQ1d5F5AjeasJXO/le3GFkyAl6FiYoBwUq50q4DIC9cWhckaga87LqgBJAS4tTRbIMBzrK2S1YKHC6otza9rUAi6us7Yj9d6a8qXCJz4tNiOrwSvVK2LPDUL/Fg+/fE8x8Q72cZhWBqWjZEvWqHTMrPvj5hMEBu6UNm9Stl2uslkCJYqUl8CIHtRpovwVg76VDPDQzSTqKUnzjaxzFrrsTR2zPL/LEGJbzYY3Wn0M8PVmOlWaFje7EMgXmhPIpq7hbtAt1Y8LgEh4pVCWNSoCmY6M2wf10TFVVchJawyKU6XzgtdFe8qFxC8kNuAhqLwGUv4VwvIpnvo/Jr2hbWtGzYyQjIzgrf9znF+ZMPT0EDJtCgYJ41mfkUzcCdBrKjrlUelMtSq9PFtwCOHm9/Ll+aLbUPEt5E4YT9a9NXxf2qpyjWsVT34fIOxDjmX9OVm2eFplvTk9GsRSXrr0mFFoXbhIQ/KyLad+9GSrso8nUrA9ZfAepyM+A4+tEChMYQ5KQOWTaw20qcKxaHpLMnvzYCBWSfgVleAUOpToZaAUU0Jigjrpa8YL8taC9SY7b/apygVU6gatAeTU+rqWGkUwBHE/1MCAjI6ATmtBYzAcNaBqd+eqVbT8wqMyytKJIeYv8OcXwEBt9J3munncLLqctCTQox1boJCDN3023V3bKYoeObvXdM0skYaX9LFpEHSZlPShEbXSRUp75yMJiAyi88cU1Q0fP9IsCt1h/kdJmZ9in7wtaZmDd9WQ59JPQkizDVgX3S0Yf/0RNPP3k6X2xX+LkoMEdmJOst/JasZFCnb6zGyWObWDxHY75QYC88U31IHGveESY5zD280IMsxCxRS3/70N/SRXG6KkAclYAiIoAziXhfccSztnbifLKAh2spQ9bOa2ydpn7so/OFUhVbUKh7AQq3a+irUE6VcRb4D4JhgT4vRtUUrdSlvX1yFKsp6ahGehRTIYCLvdxeUIG5qQ+RTsUMZvwB2c8Ot+6LuOLuLWEFTzvb7bVC+0uPF+30Vng3SyYrCbyT018JbN4dz5CY/Wvpr0F68Hu9Y7jcag4sEWgV1OMC1Lf1KhpVEoHSjpYPZt+wVUUwgmC5XTQiIc0/7Xug+nAAsMc7M63FztRFCJiSP36xi7dhCXOKURCsfEAh26MaojfT7PARQKl/73Y9BTNoPF43lP+y8AO7yGeW8Tlb6LW7pNy+EH1CT8DXijPAz32JcjELUQpk9zNJ1sexu6k486gOxymLao/xOpgFF5o3DWh+eNfGgerGKI+ut8YKwjMoX4xgdu7z06c/YtsVhLE0OQ5ABEdb01cZNuHid3gDJJ4T5Q0OSAm0e/CdC27VR5SYc9oA8rekCcfnkUZz+nrPQ847ocvRlD1uKW4Eai9L185Z12XcgehVxd1AwSlKRzrECPI4HbwkvEaMd1xbrBGPeEkMTR+KkvGNyhaxI5uY3qP/rkYvG/3Zv8AQmA6XIgIYYkq/5Of7knk4LxJzkqYVxrIFDjOlrfz01AHsi9ap8MQ6ObnmGcnDlT2nN/dbOjjZpQ1YyPW/3kU9xzpeYoIzY6X5USgjjydi8enquT6zzNSale7WcBmlpXfv8njF23DoUBZ6WFkAXgXBY4xr24lBjSDQdoWKvZ0WSXz2bHpRgMOFxuleQI56fWjQ0Ahv1vWZWtwBsA4cvI6JMzJVnjL25jXUtvDWOLfKYA8Kigs7X2RmE0r3Cbjw2P1AWV1R+7n5ypfeZnmXqN1i6d+3NkYGT3J7/oJPUvUWImZGKstLTCbW6Lhtrje4VqpsGpk6CLdA9vJcA/JjyhL8JCcam6BmISRJJxIUiAz/j0RfUda8WoEqwzHBqMvirrbt0UYgCeZKSKRMHANnugNEoqEVEMXGynuaaF6UnScn/8CrqlAGH3Dntp7s1utpYSEcuO92G9OSze1ZWWtpLHfb/yGJpjw8z5bieDZQacwol/InEKg6r9zueEAq5UyquS7FnFm+R+9hlvDq8sUWQxQ0nB9FUXxc66e0vLpZDDw4293/NE1+aAdQBnkjKWkAvAA+xLCpiJHOijRPuoFwoXCegWjg1rDa6MM6NfzVRxpR3M0/tVODp9E5LPnhsJTh6/kDjvffAV1xurrU2XmxyrEO+3XZZFeCX6QTTBrIL6FltakVrRVBCIN0RBJluETe5PxuLyKtMx4xW7WRWcI4Ni2pbbMepRGUupxoJt8B3FZ+1pMFUGjq1tPh5dBO7XX7U9IYAzGWkO0tvnAfGnuTtGnr3PLiw2H8SkA63XeWJ0giJL582kzBIyDZT2wbi0sTBvnn28bOgjIbT6j1XVEc0IGuLks3tAK6qX3Ozg85k3+JjZZc4e+strW2mGP4yAtx49a/zTUPgLIFnPX8zPzdXIBhDkKa0omVb22lJdOjghGHoY4MJgoOT6coTGWooXGzqFZnoIvrqlj9KvmVbnKFQxS1CpiTvz9dX9c6tZs4wPjTXkAu2Cjho6OjxGtQJdIXSKqcQzq5e5YvflQNODCev+muLu/I8QW46GMu5kuW/DIbRWMTnBGSI1P3HPW42gS3k7p2n5pqInWzlHv1E+MVxPOGOPkJrNkg3ij2Y0phwtm1MvNfCQ5WHTvSZ0quQi2WFRO5BtoL6Pl8sGtu1st6ZYXq6uqw9+PRzByDiQFCqiIRnKGPLJDRgHPw2GERPrBEZiKYXBrUDmwpOioP+sVJCOkbrYfkxBLuV4oLttQsQcmE59N9bi1eOfNXZ16olZzYM5PdHkaOM2k3Pm09/Iw9j9fYDFWEM7pzwILHocVYxooR1FnFyDb8jJKaKBMac0P2f+LVN5GYHyTh4QRY/Om6zIMH9CLMwYC1N3UMD5TXxFejisHds1uIiy3xITsTiE87Bn0E75mFGnTW4AmoQG76qb7AsQFT8BXFdR/hBgaYehfMThO4Bmd0XzKaxRoauPeXT1q+7d6+XCH0xNxFGh6tBOFQOTGoU0PadC2LhR2Ip7dnTL8M62H1AecqsOOYs/7y+CYj9LpE5OqtqvGuYAi1rnqlVG6X/YxE/uhMyduQigZSfOwpHF9ufTJFzVVVWdMLa5qrmCrzv5fsX1h/5qwEEUhBo0uI4BdhFNHN15Q8nyrp0BOo1MvSUkOUnE3Qp9s29GRiND57PDYjFPb5Geg1XGC6NIzMeOkZsgnrpGiTZ9siHL4XtUtOD8hzfp6jHjn+HfkY48/IgCJxCkp+baYbdDQ8TmPYOPKkYvmyOO1L4ZVNdFht+26NVjBC6UnBTsY4cn62T+lSvl7LY+5zuZU/vehz1iYWjnOFB3qhwqGW58M6VjwKVzfjBQW0etvtOlLdh+hmIupxQiI4NBWlxXV2Da3Bz749+hxCtY2WOytdjeNQSNK68tN6oyNzrhqMoxVRaQ7kPAJKxijFJtFpgz6tySSpF6WpMdkjAMi3BI4mIdrqchkiTQX+tHJtZSktip8OamBPDRuq+csQJ4kk767hp2XYt6jJlNjL08VZncLRF1yLx6tWktkXs1gt4ulqHdzhbe3kgAVjuzaYukPLni5xOXZdhFORpnahfM4Z7eZZZi5yKo20KCrLRdc2lwlYB0QxnvwdXYfc5I6BX3Oenl/fUljP6JnmgeI7QEDTVo0BJ9Dg89MGrpUAmLIHRoD8XPzhn41KKrFR6b0WT3kpF8MSilHn/T2ElS6HR835vTZADqKls60/IIr69Jy5K3vXusSl+UY8uPavkqmR6X4Be+T+Wd/y93nhg7uBTyso8wCcvVUtAtiMlEn0kjtIyf/k7zo9LZP4FrMWwdkfOALszNJJRmQ9R+2gx9Xx8P/u6XHqocVPqDTD0oKA5D1/szPhNzF6hGkFLeJIluXs8krXEZPkbdkru9DvmvbJGgZqaPzuX99Y2ymdvpQ9ZQVSBSrD9cL2tWt5CPWOuR7uM3R/M4teDNj1xfdu227AyIfTkT068i+isP4BuOy5e0MXUc2gaiMzDYU+GgyPqLBKsrGxRi+PNzU6W8aUq+F0sLlzwNW6FoZYrjCifMwST1L0myYi1ApNmEN8dN2j7hjCeH30gD4z4Mvf47WwiUaBzt6UU26QJhEW3cqvZtBI/KwaZR953krIAEZOKUM0CL2Q+ePGTA52wvwn+iWBv+ieLwSRxCj7WovJJNRYIMXREn591WXEaxa/jrZHQj8YWyhsRNYcheGP79bJ8BCKb2/v7dOKYevtVsXnbPfC/GLGl3MXsXUt1zhosC+cLUxwCKWZnZCYIdWMgUKoD05MDtjhFN/2HbAUYCjEqHC1dY90a6vDigeQUECyrDDIQ9FQPcbfYMxIUvcQAhPAtYyDPf7RB5N/fydB1ewHGu6NvXIRooWrRXFLTUW+kQBKp+t9HOzUspIyq+QqrsE8tY6R3k/WDCtgjtrdeGAWXb7L8WnNJqje0mVi5CFcq9vonsTUrLi42SVo7qHHaPfSfFa+3w0QHdxVjIzjoKNEkktzyfy9N46MbKy3lmxn0+tnq6I8T9jjvKRDz0qfMkBJMAPDQXkFrn8UKqAl8om7EoFnvt5mNgEkvLnRGwNwy2lvZtJPpnsTnxmsppAGb2WT6X0GIzbM9svyjDo+3lnn9h36mDIvMu1n76UMcDzg1O/iP9RJMtYysLqq4yZrQdgRgAvA1e8605LhLe1N8RMowQmbqQDkQR5KhuidoHADpVOspI3AEk4PT1CaZTTvBoH0utFitDOU1BRNTiOS5M7+Qj14HA/EtDXv+3vZoZf7RTdW8FDbWYsxushJmj9Kmd1/VomrqzmEtupq4ko45oRbGZxn+VVYF6BxtMnebld8ddb/pEnj7OXvhV2RUVhygBTw6azQW6yK2SVPJQhKFfXeRB59kXnQPQxB1nV7S4wnX6e5BuEpRMGforFUseP4/NqdOG8EilZknJXytdVuw6NuWMzJznjcPfVV9cNBQBdDHRN6zJksWZFVnvLZ
*/