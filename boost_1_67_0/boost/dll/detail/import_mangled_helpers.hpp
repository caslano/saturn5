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
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
*/