
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_DETAIL_APPLY_H
#define BOOST_CONTEXT_DETAIL_APPLY_H

#include <functional>
#include <tuple>
#include <type_traits>
#include <utility>

#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>
#if defined(BOOST_NO_CXX17_STD_INVOKE)
#include <boost/context/detail/invoke.hpp>
#endif
#include <boost/context/detail/index_sequence.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

#if defined(BOOST_MSVC)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif

namespace boost {
namespace context {
namespace detail {

template< typename Fn, typename Tpl, std::size_t ... I >
auto
apply_impl( Fn && fn, Tpl && tpl, index_sequence< I ... >) 
#if defined(BOOST_NO_CXX17_STD_INVOKE)
    -> decltype( boost::context::detail::invoke( std::forward< Fn >( fn), std::get< I >( std::forward< Tpl >( tpl) ) ... ) )
#else
    -> decltype( std::invoke( std::forward< Fn >( fn), std::get< I >( std::forward< Tpl >( tpl) ) ... ) )
#endif
{
#if defined(BOOST_NO_CXX17_STD_INVOKE)
    return boost::context::detail::invoke( std::forward< Fn >( fn), std::get< I >( std::forward< Tpl >( tpl) ) ... );
#else
    return std::invoke( std::forward< Fn >( fn), std::get< I >( std::forward< Tpl >( tpl) ) ... );
#endif
}

template< typename Fn, typename Tpl >
auto
apply( Fn && fn, Tpl && tpl) 
    -> decltype( apply_impl( std::forward< Fn >( fn),
                 std::forward< Tpl >( tpl),
                 make_index_sequence< std::tuple_size< typename std::decay< Tpl >::type >::value >{}) )
{
    return apply_impl( std::forward< Fn >( fn),
                       std::forward< Tpl >( tpl),
                       make_index_sequence< std::tuple_size< typename std::decay< Tpl >::type >::value >{});
}

}}}

#if defined(BOOST_MSVC)
# pragma warning(pop)
#endif

#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_DETAIL_APPLY_H

/* apply.hpp
tSVtWOzIG1hZd9edmx2s1mUiQqzax/p9HsR29z4gx0bub3iyNBsZhXYg2Yhh8X3f8IiU9XCo33AI3X1Y331o3wjE3Ajk3H0Y3QO42AMu0wWggQNcUxGCX4Q3nX1FNoeCeWrOiwOYgsOUgLVP2HkU9BxG3iN82SMG3SN23yPO2F7W2SOO2yOuXGym3yPB3SMR2eNUniBpFIyMBtC/fSHkyLa//WN5vE10qZN+0xOZ32ON3ym12ZPp0hOggBOD2xMt3RNT3lN9vAkyj1Od3VPL2FN73hMrOGvQg2N2BWbp+2PHewQvXma/X3gvWQTmJRofvPOAv1iEvlTGZB7EDEoEjQjp8WUabcUwX0EQdd2LabIR59px/4ELd9uzG0KSAl3vIl6EEl2astrT3N7LHLrLPIHL3Aa2fN6rPLqrGryrctur2txLb6WrDrjrerrr0tqrat7r9tjrLrzrCd3r4drL0d/L2d3r+d/rPtmbtd7rSd/rpdqbndkbpCCUrteOAHfHeG36ICo2D8bb2YDbVqI1bs/blvdbfzaHZ9uLB7FbVqe7WzpHx4HbLoHpEkSXQ4V7Utl7cLv7FTFEzKfAn695F4eetui5kCV28DQ9+TMcgkGKPfUSHHo8PLsHgjwf/DwibPpHMvxZPKZHcnpzXLlHiroHqr+8hyPGJ/q9R5axR9a6J6SeR8q9Jxb8R7q5J1L6J36/J66/JxG9JzG5Z8a5Zyn6Z466Zzn6F167ZwW+8qTS+HuZau29l75MnRSo13HOV+O6yvYAVHEQStM+aSJ3AHDFNLO8SqwETNNm8GmE1Kl/b4qR6LXViZ/L0PonRYnN2d5z8Tgvi8AOEEAOEPka6abBMs3C8iccSP4+76mhRJgC+LgfIn8IohUioqMT4s325SCMH4l+9QojMn7H4lKhUN33+ncxH6GliAXxwBHKwAEWkv790K38mSMb6hUWCL7BmcVx3HIS7lxTWMBIsraSX6msfaAO5KCE6V7FwA6aub//EBj/LESVAAIs/dPPIBKxDskWdIbqgUGgf1xMsX0bgLv0YQ02NMlQP5qGP32Vs9RVysEUwPOWQGQAEMR+f5DF5/UHAiBR6YzX5wmFdHt+H9zVFw5FojH/2R6vLxyJxROKxJJoLB5LJFOq1BpvLJ5IpWPG4SAW3eX1Zv4J/hC/1U326a7/3hi+zqXS8jf/UrrwR+FAhzGBFSpiWevnAQAj+s5jIRvJ1RmMxJJqrV5rNFus1JpsqdqUC6D83WCy2q/N+3Faw25bTQFGlXHhUImc9GvEVsf+/rvgTDIozzG3kWgalzLAbsv4Z3e6vfFkNl8gEuScXe8ca75a/VM1IF14EtxsTA7TbQ/+p6wpU+CouC6830y8JMrmnYlwaX88kUJvtrv98dTSE/pQyOuSHy38h4NiR7Ee8HL3d2msEz7f7FS6FSdktrf74/X+cGJHc4PgKNQBSfobNHp97gJuDHGPXwGyJFsZ0CtkTwBP9G4WYKHpIC4IycgUVwANLiAbhsWQdSeEIITiIIzEF0kY7Ncsfy4IAy9uno71GxFKiIngfclVD7H80BkQmHAS4Neu3j/i5yh53hs7bbRQWBia1SBMUZTsKEmVdxRJPGUtYFJxj4dk3xOQvx/dQDXF8iTNsqT81E2McwwRHoLDwCAQEllE1kEcrnxR++/r+UmOH5inYkbgmaW84PNx8y+xSL42WlpenDjFWVFShDsw/Mm6URwmEIQIntjMmb1RUVHq34uy8tESMqoySHV4WpcwbDOYY7MHi4q204qLWjIRg4GIqJCA+RQduuHLhHhIV0QRdQJjpJp5UYqqIjgsrCs5iYTUBGDPr8EBO/gxDuVciG3LOV4qUk55ESvLtbOm+1EKeifxs0Yj0Xh9jxx2TPM3eWH6IOoasSwf0FKJ179DJ91QbFeMyQwopCUttMGc5n0opUO6opxln3ejeCHWCbVUpl9y6vJInQs6U4ANK479WosJzFhTJGKDBKdVD7PQyh2Y1gaERtWSAg/WT/NisSFnjVY0kMradJBPlzTdeJu/iaPiplVPK3foSSiMFkOccbIA6dNP6+YlsooZPSFtRY2WdxUv286rVvt8S4dZFcqur9cvu6hUWfEl850VSbt+ZDWcCwwwQ6DeWEQ2ZKp+OFuKrRHmtW4etqMmjcdjY1iJCjvM5niyQTY1n5cFCFrP9sidqgKwQgDAYJdtp7LnxYDUVrcOQz1TWSyt7NUf92NgH++1wPDmwcjjojRelVY5Hn8RU80sX69batpxszfl1fHt2ym2vYO9hSNIhmg0nmfv96O9lge/1DQ579bHFUinj683/I5ZiQgcQKL8qu5Cvp8fuQDo5+grKhHoCvXYAORigp7UU655EUiqRnGIdbDHv3IYVflg4unoH14UHKRS+RClytySzkZBjFEE3r2vsStjdyGcTVofjmMDeMwzdnwwhXBR6H2EGHfhUA6ECCljojr3N3gYVoVIJZYUyAp3EZrfihCNY0P0GWEhbE+FaCOSBbgJd1GWxjBfVWkj7J32bKJehVgnkBikC3cx7taTCIVpI/wfdTTWX4X4IOUJNEgPceFYaLt/0sbEuBJIzLyKiUk441iUHhLSdExJWcnFuBwfEgK3DtaEICaUYxjiSqWLMaHKJtRLEKJqo4+xCckmtBXmElqnjVEOyyb0WecSemBL4YXdkJQhHtOIhUgZU9GE1Bkf06iDSJlLx4S0FR4zf38HSFlbxQT0HR8yH4DI2Uc0+Iw1ErLOonIZF8Zmt9kbsu6NspkPxWbPsxpy3nS3EMdTZnxXpaEhwQt5wCuaiEKEzIFkyjaBX/mCuJGtX/aV+vAl5wtE86Hy7eF5qCflC3CbCvGR0cCW+fhGrFiKybJRwBRMMxJKn4vukCilzDyoE7HB8pmnzmrC7SlSLp9KlhkEhSJAlgpyIQo8H8vlUj9LL86DyuWilsWM6xF2yVgq1bIWJZwDmsBNnyqN48nMyKBWGmKGS/CHKCygWaKiM5+rCfcoWtGW4aK0RNVVmiAhyF/gdmT/1roHU6J7sag0MBehMiBpCbsPhgkIllbHREv/zHGvIP6wGHECMND0gBmxxY9LCR05SJoCSYkVxU4QZG+GRWy+xODBDKMDIMpqbETMBfS/4gSKXysIufvrzPuz9RAnQgeRxrUlFoHXMvOrgCFv+YclN4k5V0oGDW+oURy3kCFU9AoAZqXVp7YFzI8A6BK1RD2/4vZYx+BmfcJ1FBaDtnhXiK5MSJzr2Fcqb5Wa93xEvHniVW9Pq2qAOzb497kQ4Dte8U9Gxj2WrlL7NdPYRkEiIDdNdwLKWwiRfPN8StpXrnTGRcAhQvTAAw9CR1VhsHQRBW2ryjxo2mtvfG742QmVl4oDCY5cEviNM8nRUNMS2G8cBLWHD4MxgIcE/0QeY/8edrAu1QhkWsdtLAwRr5g2hjScEcu2tfawuN6wMP/Bp9iZ7Ai8m3bTfxNs4zxSM1Cs120xMAoNlusRfagTHivVJEAKboR1Aw3hiyzPSxNk0125EUu+QhS0bQvrhaA1xFuEZDFOR/xrW+kJb4nr6L8/tiEZBolQGSdAODzdtz6C/ONntK6JMtz+ZDc4DoROx6aK9zm9ADhDEIzJop4n7fogioUNYRW0sYr9vix+8Hksqgi/oH96AvsnPeK/47k4fi0sDeXruBUNqLUCVwPZrwHhl1SNkKsbNCxGsHSC4mOrQE0CINTUmNawrYbM7UYQ6vUQDTyzHXO8tRG/SvenQP5JvT74OirsWBX+862MSgKyKnH7xpf+EwfeXqVvqMgUGdfDJ3rrtPPXPopovGpGkUc0LeeKCHuIrecWrjm5eLJW9gqDtG5oSs6e6u594W24RGBM/k8PAk6c+54s8zXou6khpIN6zz9xm7D+JiygLite3imrx4t1wCTgN732XFUuYiUsSnZ/M+rLm4Bcv3WyJzceUMiHMND11j4O4KTK715wdD1seOh+M6Js/bCa7HvVDk+9OE6+U+vvfebE1jjrOGyju4ALHDzvLRTvx9PK95GDxPcFQ664u/EH3D7Tnnpt9WN41WaIVRvvHO+5YKzgPWUVO/BtaMfnpLaFzrrtr0EzHz/rJo3PHu9bembT8H+/dd38qChrQ3fVQB+h6IZ0odzeqvIDhnR1eUHAAQKFdFkFdoHDk8Tv3yKwELaH7ROCKP5Na+99vmpW5Tzd+chandnuOiqwaUebcdvh97R9iICA29brSsL6tOVMLhO+17NSR7mr+adBK5vBFbDVI6VL/1p2CmpsNtBEBxIyeyWGP2UdNCUqQlDdGwcJSe9XmSpdDF3Fuzm/wrQE8Mki6JqJitnfPO5KtK0JOOGbgkdE7Pp5W4FD6O+TSw//E/Ppk1OphBX+GVxQZk/9BBOr76mZOlej4ZBNSpa1k1QrOqHLXaA046/ZF+Wh39ag0kIA3qFdFISNtwGHEL35u6JvF8YvAsoaImCkPqQgCdg59vxJss3xSWpkq7mjIDe5qDhSDefsvXMe23wgWHsrKFrehxqVYGz1PovH7L+I8509uQHN7LSLuz0U9adn1+jwNMfGMIQoCQflrPN//9AlOERqsK9MZefp35XgmVUUU0RvM9NCrnFVGt7OWvv+5iNNuN2bEn37t9ecMBjNJavC5/n7IgfGPzJHEHwCxG0mUi/wSHH3WU9bwMjbjoO/TeeonprePN31wkFlYK2W0Nqk/F5sPifR4+ZjEY4+TtbAKBsbfxb+VLfntvHJvv1CGBmTrltP6cxQEQsFoB7zAD/ZqAbO/gIxh0wlHFZEgSMEzw6QRwQK8EYCyBkJowSQvfawkh0JkTVqG3FLsmJOCjXS0AC3IeKLNXBLwfpAUGtMiVDJsILtVCguxJpOqeRmDERDlm0ZrVsRLQ9wkF+EYQmXWWDJoX+3rWkSM+cfrNicL9W4IOXarzZWHH70vDFsY22fNGCsZT2jaK+duUOjVrkqHnHvZN3L/cbI2tO6BtMhxKUB4sNRkOztgVrUh4kFtbRueKqZKEnG2Tx2lHZYn4jF91UfRr/C9wHQOiLv2F4sEgjY84PyIpgEOSu58glzNzCCq2i54GF544O8YC15o2QZs+lixwu8eycTjFn1guTEFgYAtgloJ7QMYTMi7rBsNFSm+bVcuLFcsGU58ZakNJy0AXsZo6hkxKaUo3FJ7CUyyRoDw8D/Q62iTROTahoaUf7WxKbEA63k4qX0M7x0ZwWIK4VFK70ELdEcDnl9DudW3JjUejonsQbpI9DObAL/L2RmhOIYiJpNIsdRMcz8eiQ5Was9+cAUuCiJGbQmW1j/WGjnwC3PgQfZwyXCzEkPgTkJGOIsfHYGWc6qwbbdE87bjBrZdCi3iHtdbq0L3u4d4getssuO/7Aqz6ZOQscgT/jklD9/xmEn2jnchfn1YFNHH6OTcOnUAIXc4o8zw+K2kGAzMjpNeIFkUQNg7gzPh8RzLuYyf+mER04UiEFsqbA4A3+shpIZcZnGppTSWG//cGDGMy1hjHWUfCyuJEmiZgtstZ94UQdFKx3rGhVNGTJGm2I8PVEzaKR9joy4Ra5RKunuijXIBWLmHfHCp/i7aqcyLj1gs1Ew5qmOlPSeBwvw2BLx2uHWs0cUQDnpy3pgdER1ScKm9S1k9ea+A+PHFBdFOWS0xrgxfpVECxI0RsQiW5R3djW52yFiwPStXHj/uLrzObF4BKmbwzUmsta07fhX2NS0KF3rE9lb/7SpgzVDG99ODodaJltX3zlXY0iQx75xh8CqP1838ubFZ21qTWZFfxxU03jI0vvWjPbLwjXMbvgMiSJTK5JVW0kKGuMYIRp8Eq8GFsbDtn/w2PGh06B0xxHxMlyWS+DNYcxUK4pDtvkgezLzTpJXLCmLufPT231ZFU0qi0oVWlWche0AJeO7kCUgOVKRGmaBxATjt4aM2MHiGAmuj7DOqDAKVXWg0HeJYPUaE8ZNGRun1VQyk3XWcw3LEpsQ0j9pCdpI3CwhGMIa0IO39/IOHQYeOuwtD1IQVfiRaiMuvRO0XH+q3VuYp+KE3Qa7thxvzqHPOJrcvFqtl3jgLgoa3iIlQTF+9YAYrRhtQ8/Py2RzGoYAKchKacxHOSlCl+iQYX28cUc8WMSLjf8BekSQEBNxlJPnPLsH15+z4rR7fLSbFY+/fZwDPI/64dBfaCeLHlu6j8GwE6vamRN3R0GyqL0wxoUFHRSQ5xNcAVY8ArbIJe+AS7wi8lR4TgIU3+sT7aQiVLP+WqTozPBHgRSxthcN8m46jCqLs/ZIeYFZsa6PBaqKoZttiw4ky29gxyL66nxh0TsTMQILgX1rGA70/dgODzIt5mEM/3Bm9m21dE0dLgSAvYRZV8qnwPkGGjr6vRwgoe7YOP9z0uVRIReb+i2nvwRwv9bBFAWSLwhjteGJUU2PYsp2nGv3frQIrMNSGNNKqWzrs9QIml4UqM0SOk0M/s4fNW8kdN8bWrgTdnidRGKDyLUZcHRd/8QaGWVDfuI5PtY66ctOiW+r9LiBcKO54ENfqKxZpqtDhtyImCU+ZLJ0Mhg97pHmdrtboYxeFgj2ex+JLVJlYEd4DOiDQaf0zXuiM8/SVMHwa0If/EFkDU5uSbbfUe05IweCNqI8OocgLkd4gc7vrFZ5snZ6oPZ5nK7YXM3QWE13QpZzFM7QnP7MnL6ug/xjUTd1VVfVVK4Zsv8Moyy2DqUdpcwAoyzlUTVplRBy/76GrXapFG22rEMKlp97FEtjNClu45fJQKYt1ls+gnkFBGJeLMRFBMtuFFNzVMMOCEdbz6mvOFbAJb9NBFFC/PP2JjzHeZ/kaD+x8eXHc2yEYXZGb9JlaaHwov/nW/9hYEFneOKpf0HqYn5r/qLDLyDvr0ButoD+16D/UUD+zEB82oBhirBhx0B9peDv8SAqaEh+yGdMT8dxxpmDHqq6nvM4u8OQYRKhgXj7IdOBMXM2InVWQkUsPKboPeMnGOUMZbOdZPNIGDFtOb2oeq8hoy+H+V7H0CjWSbfzGIf9qZAjnaFD+GkG5wp43uJQ8hZJlQugYruW8Rjx0roWde6wEufIevYoUm90Ba1DdK8LwxmtrzSGuj7a66cxH7LoauZu/fSkiBuNLYYqDWhmCQ2vjWZKycqtTRYm7RWlze3XFhejbIfJlofD9g5e1osPx+fdfhP96NTdjXPc8TXh2Vr/w1n9mEb+wHr63hriyHr5z3rwwbpxAnZKPuXfYujvP7WliPyRXdaZY7JbcWzs2bUPMiNH4JWQtL3UO/2pPtS1HxveB2/s7Gd3QQt++Q/4jmB7Fl/NOaDTfOPeKW4X8D+06FpGRMDDuBSI4zO+qhENBO5x7J5XdbIWeJs8hO/XG5iimPbyXqCt08v+W+o4cvlRJcmlJ7Kxz9X7jdzkmTiz3Dd6nrvK3r/L71/xrx7OgSfsirMXuzmx1LM+kVy+HD8xuldhdt38JJ1tKh39Yd4/DZeA4A9vv+PAIX7zCzfsMn1Hyscm3I+Xcx4M2+/gD8Mt1GMk4X0RLH+p0SyBaU8JU2cJxSuRDC+JT52YV6PeRvQx+WETpwh54QAXx4gIAckzoncpGQgxG9CAxyaLdWntYCjGjxq1o/R8ub+Va3C775Sq85qqjqqqaJ86
*/