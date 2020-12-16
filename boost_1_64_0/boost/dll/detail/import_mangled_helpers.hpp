// Copyright 2015-2018 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DLL_DETAIL_IMPORT_MANGLED_HELPERS_HPP_
#define BOOST_DLL_DETAIL_IMPORT_MANGLED_HELPERS_HPP_


#include <boost/type_traits/conditional.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_class.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/type_traits/remove_cv.hpp>


#ifdef BOOST_HAS_PRAGMA_ONCE
# pragma once
#endif

namespace boost { namespace dll { namespace experimental { namespace detail {

//the following could be done by fusion, though it's simple enough to just declare it here.
template<class ...Args>
struct sequence {};

template<class Value, class Seq> struct push_front;
template<class Value, class ...Args>
struct push_front<Value, sequence<Args...>>
{
    typedef sequence<Value, Args...> type;
};

template<class Lhs, class Rhs>
struct unqalified_is_same :
        boost::is_same<
            typename boost::remove_cv<Lhs>::type,
            typename boost::remove_cv<Rhs>::type
        >
{
};

/* ********************************** function sequence type traits ******************************/

//determine if it's a sequence of functions.
template<class T> struct is_function_seq;

//type-trait for function overloads
template<class Class, class...Args> struct is_function_seq<sequence<Class, Args...>>
            : boost::conditional<
                boost::is_function<Class>::value,
                is_function_seq<sequence<Args...>>,
                boost::false_type>::type
{};

template<class Class>
struct is_function_seq<sequence<Class>> : boost::is_function<Class>
{
};

template<>
struct is_function_seq<sequence<>> : boost::false_type
{
};

/* ********************************* Function Tuple ***************************  */

//a tuple of plain functions.
template <class ...Ts>
struct function_tuple;

template <class Return, class...Args, class T2, class ...Ts>
struct function_tuple<Return(Args...), T2, Ts...>
    : function_tuple<T2, Ts...>
{
    Return(*f_)(Args...);

    constexpr function_tuple(Return(* t)(Args...), T2* t2, Ts* ... ts)
        : function_tuple<T2, Ts...>(t2, ts...)
        , f_(t)
    {}

    Return operator()(Args...args) const {
        return (*f_)(static_cast<Args>(args)...);
    }
    using function_tuple<T2, Ts...>::operator();
};

template <class Return, class...Args>
struct function_tuple<Return(Args...)> {
    Return(*f_)(Args...);

    constexpr function_tuple(Return(* t)(Args...))
        : f_(t)
    {}

    Return operator()(Args...args) const {
        return (*f_)(static_cast<Args>(args)...);
    }
};


/* ********************************** MemFn sequence type traits ******************************/

template<class Class, class Func>
struct mem_fn_def
{
    typedef Class class_type;
    typedef Func  func_type;
    typedef typename boost::dll::detail::get_mem_fn_type<Class, Func>::mem_fn mem_fn;
};

template<class ...Args>
struct make_mem_fn_seq;

// B: is T1 another version of T0?
template<bool, class T0, class T1, class T2>
struct make_mem_fn_seq_getter;

template<class T0, class T1, class T2>
struct make_mem_fn_seq_getter<true, T0, T1, T2>
{
    typedef mem_fn_def<T1, T2> type;
};

template<class T0, class T1, class T2>
struct make_mem_fn_seq_getter<false, T0, T1, T2>
{
    typedef mem_fn_def<T0, T1> type;
};

template<class Class, class Signature>
struct make_mem_fn_seq<Class, Signature>
{
    typedef mem_fn_def<Class, Signature> mem_fn;
    typedef sequence<mem_fn>   type;
};

template<class Class>
struct make_mem_fn_seq<Class>
{
    typedef sequence<>   type;
};

template<class T0, class T1, class T2, class ... Args>
struct make_mem_fn_seq<T0, T1, T2, Args...>
{
    /* Since we might have ovls, it might be :
     * Class, void(int), void(int, int) //--> just us class for both
     * Class, const Class, void(int)//--> ovl class.
     *
     */
    static_assert(boost::is_object<T0>::value, "");
    typedef typename make_mem_fn_seq_getter<
           unqalified_is_same<T0, T1>::value, T0, T1, T2>::type mem_fn_type;

    typedef typename boost::conditional<
        unqalified_is_same<T0, T1>::value,
        make_mem_fn_seq<T1, Args...>,
        make_mem_fn_seq<T0, T2, Args...>> ::type next;

    typedef typename push_front<mem_fn_type, typename next::type>::type type;
};




/* Ok, this needs to be documented, so here's some pseudo-code:
 *
 * @code
 *
 * bool unqalified_is_same(lhs, rhs)
 * {
 *    return remove_cv(lhs) == remove_cv(rhs);
 * }
 *
 * mem_fn make_mem_fn_seq_getter(b, cl, T2, T3)
 * {
 *    if (b) //b means, that T2 is another version of cl, i.e. qualified
 *       return get_mem_fn_type(T2, T3);
 *    else //means that T2 is a function.
 *       return get_mem_fn_type(cl, T2);
 * }
 *
 * sequence make_mem_fn_seq(type cl, type T2, type T3, types...)
 * {
 *     mem_fn = make_mem_fn_seq_getter(
 *               unqalified_is_same(cl, T2), cl, T2, T3);
 *
 *     next = unqalified_is_same(cl, T2) ?
 *              make_mem_fn_seq(T2, types...) //because: T2 is another version of cl, hence i use this. T3 was already consumed.
 *              :
 *              make_mem_fn_seq(Class, T3, types...) //because: T2 was a function, hence it is consumed and class remains unchanged.
 *              ;
 *     return push_front(mem_fn, next) ;
 * };
 * @endcode
 */



template<class T, class U, class ...Args>
struct is_mem_fn_seq_impl
{
    typedef typename boost::conditional<
                 boost::is_function<U>::value || boost::dll::experimental::detail::unqalified_is_same<T, U>::value,
                 typename is_mem_fn_seq_impl<T, Args...>::type,
                 boost::false_type>::type type;
};

template<class T, class U>
struct is_mem_fn_seq_impl<T, U>
{
    typedef typename boost::conditional<
                 boost::is_function<U>::value && boost::is_object<T>::value,
                 boost::true_type, boost::false_type>::type type;
};

template<class T, class U, class Last>
struct is_mem_fn_seq_impl<T, U, Last>
{
    typedef typename boost::conditional<
                 (boost::is_function<U>::value || boost::dll::experimental::detail::unqalified_is_same<T, U>::value)
                 && boost::is_function<Last>::value,
                 boost::true_type, boost::false_type>::type type;
};

template<class T> struct is_mem_fn_seq : boost::false_type {};

//If only two arguments are provided at all.
template<class T, class U>
struct is_mem_fn_seq<sequence<T, U>> : boost::conditional<
                 boost::is_object<T>::value && boost::is_function<U>::value,
                 boost::true_type, boost::false_type>::type
{
};


template<class T, class Func, class ...Args>
struct is_mem_fn_seq<sequence<T, Func, Args...>> :
        boost::conditional<
            boost::is_class<T>::value && boost::is_function<Func>::value,
            typename is_mem_fn_seq_impl<T, Args...>::type,
            boost::false_type>::type {};


/* ********************************** mem fn sequence tuple ******************************/

/* A tuple of member functions
 * Unlike for plain functions a sequence here might contain classes as well as functions.
 */
template <class ...Ts>
struct mem_fn_tuple;

template <class Class, class Return, class...Args, class T2, class ...Ts>
struct mem_fn_tuple<mem_fn_def<Class, Return(Args...)>, T2, Ts...>
    : mem_fn_tuple<T2, Ts...>
{
    typedef typename boost::dll::detail::get_mem_fn_type<Class, Return(Args...)>::mem_fn mem_fn;
    mem_fn f_;

    constexpr mem_fn_tuple(mem_fn f, typename T2::mem_fn t2, typename Ts::mem_fn ... ts)
        : mem_fn_tuple<T2, Ts...>(t2, ts...)
        , f_(f)
    {}

    Return operator()(Class* const cl, Args...args) const {
        return (cl->*f_)(static_cast<Args>(args)...);
    }
    using mem_fn_tuple<T2, Ts...>::operator();

};

template <class Class, class Return, class...Args>
struct mem_fn_tuple<mem_fn_def<Class, Return(Args...)>> {
    typedef typename boost::dll::detail::get_mem_fn_type<Class, Return(Args...)>::mem_fn mem_fn;
    mem_fn f_;

    constexpr mem_fn_tuple(mem_fn f)
        : f_(f)
    {}

    Return operator()(Class * const cl, Args...args) const {
        return (cl->*f_)(static_cast<Args>(args)...);
    }
};

}}}}
#endif /* BOOST_DLL_DETAIL_IMPORT_MANGLED_HELPERS_HPP_ */

/* import_mangled_helpers.hpp
BGm9YVuppBXVoHI9n296T3riK1Kr+Bpj97g0NP93j8T2VGxspyE2WuaXxcS2QfTw0LkKYaSAxr7herDtan2JwDZiOpoLuFag1VNtmolvFLLGpllAuEOaHonKtf2ffhzkxDxfvXmNdr46upLXty8JnUlO6aU8pbt50vBMvN6pL3EJQ+ZyyxKX2uIHmLJ1XhuHuOOMDAEtw3SYou0axy8bB6sRDNKDluJwxcswtWAFfTCnpEPLGG48g8KLzlvccc7g3YJTsem4pkfI1YoYlsWpSgXHYafWmJy4eIhScnfTWMXvchxGViLzVK+ZLnIqv6Khzl/gXO0UA+M5Q3HFwp0G+L0EwxUqTNn8z2wsAflmAnjzfcHn0H0zFJZdNHhkKj7ThZUPJfzqsZK33w6i76Nf7PMd21eK/q4OO/CucvxrLBK4F7BidHIzE/c5/IhmpvMau+PYbsr9KZiwyaVspQTvkHAgMlqGrLekAHmuP104TFA5m9/8z7E5/DHrTkOzapkkNKuqRaxZPcaalfNZoVkNT1DvrGfBg0iPOyVU7cXFuVucsKShcwoVdfMAJsV4wsjuEMoHOz0OThqn4tH1iROK/SGeVqQQgimaiy0kOrWQQ52P7CaAxObERblAxzELmCHkoVnn/XFKdmjnAwZRv9/8CHJKtWABUBS5jXvB52sEG0/UswumYF1n62h6f6ijaYdoMhvO1XK9nusL6C/YEb38tDt8cDVICBEC0GOhE9M3PsxAnIAySOetWCE3HvB/vTESu2Mvp86S02xPj5DBkaY7owFeflgns08c7i/og+XF1YJN/RtEuVpxgFE7P9BRb8YtwzP2AM1rb+lo7gM0dkiGwSxEXQRnKJsU9v2IztfdLPyn5KkiaZH5yw7Zv4XfHrd4sr8DlB5ua5i7cPjCqNqoc6x8leDYICVvMY2q43obqV1gqvQGPry04l96vRfiyub8xuIsNOPkM0el63Sc57KFWSBkw6muZpKERHDMJar0HVrpm2xKL+IZmQzKlzykl/q+wsvqq8G7c1aKlMXK3qqfOKKWsc6EpAxaKSg1KChFCnZt0M8cUUUMrRybNpIjhzSh4y6pnTmKf4zmcYklxQbLwSNH/3U/7cBwzXLtwPCnL0Y0l/8k6sWkAkPIONDaFP176HJN/x4r0LMy/ctk8pr3dFkk2jXR4eHTB9Dd8I+rZLS6a1oygv3O5FHmx59lxTpPU6xPeTASpU17uvk2qUycqUElm1C2grdzukBe69NllAG5gAd9UPD8lYKMy48nGUXma0X+VN2IIhc/Iy0OVGTQVGSQisTkmY7Rws/LdfHkl2c+Kjn3oJIziZWcDjAm8ejIgdNSY5/fGf+SZi+dX62f3+Ebq7kUe1Wtfmbmu3ulTRKlmH5Z1P7wDWIKlxlPoNcK2dZPGjwVLsyWxbdSYyMNDXocVgd9JF1Nzn0HdIT9aiSNze9DXtT4vRaB2Zqd+fAq1vIxrDeQja8T8QrLeJNJZilUuiekjLThYB8pDCwKChGV75YzeBvXp6m2+OkTZ5voNC6SzM9zYD+Q27vRSmRs5L59wLnY9uPt1ZqBy/OCyd9B36W6v4MbK+2uMjfOs8FRtbpngy1377lnA37P64M7xXteDJdPN8O9p5jhNRVmeKQ1nmF7/APuteSfZYabW/C3m2GGj5ppiZ9mhh+bYomfbsF/txmec5eFPmv83fXj/2CqBf8sS/wUS34LPdWW+pXfbYm31C98j4V/FvioSkt8Zf34R0610DfTUr4l/QAL/ZdY6A8jvobtBbVL1XmDxcvkeQNQYFk3XfdczMMGci3RmxTuksP0bVHcl1ALtRFSlT0rTtN5L3lRyO8uHJC9AQ8=
*/