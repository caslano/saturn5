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
Vee7T7ZTuTR5K2lpuh+/3rPLcvSoI2lqO5VIJmZuyQNzLvOeNcecUCCSykH3lFj19939nMjv1XT/DjfU+d/uMe9xvzawU/C9noXL+T/VbgQ/pOF/tSx5w3W7TpxL7hnG/FtlrrQmvmA0gRcTZ6X1RaiQMUlexJzAE3Mjj/N+weOFWn2XOGabD8C8u5goLmtBNMS+A6blpYsYLy9lnhfrTxliRD6Q3cOYFoGcZk7kOAM0S6cFZETykh9sj0XqMSmWK0lVmoqEsPysr38jqoBtyr4AliS9NV+eEDkp4qDBMcVxxLHmmD2yOFjvfxApJu/pWOGuLGP3p+7xpNxgx8LEFDQi4UUWB2bjLysJ/yIITYqRHMmayz8mXB0k7CGH/PhHY8G0mLT57eSSDOCdMAZJkiPJ9f6V0ZdH755RwTGSLaVpGj7fbfLMRhedPFvuh8I1aMU52MkBhKl4Yv2unKJ/FHVU/ZxoqHrQd5C860M+gd4pfOwBz9DzwTcc8RaLRdCLL2/7IhRWE4LiKF9hAcMwmUKa1GbBguLDzr4Q1NZlwTbLaiR3D9v3owp11Jfzk+lI/LIn8c2/CI4dORbzLPiLL9iS8U5hqqTNbuFFf6WoZLGBtyLuTfT9L30lU8b2JhbxqNUO1dEuxc0ON6argF0M5sY1Vgqf4OI3eIxlcw9xc8heDlsTzqAqlWEoSF3FJXIRp+q2jVSqk48Jibz8TMnKOlO1NQU50uEU7ZggMArGCJQUqWEBwoBoQdhF2Mua7Hcsb5I/w6voLqn6sUbZ5r6CVAUKrnVxOLYhx6hZGvLgFGW9m79D0GtBdMhm3EaW2GcB2NeEIgtH0mmtqC4hZfmU9Nu2t3BBuNab7HchHIv2pV655YjIp9wVWdSoM3f9e/bPGnq7MmXonpC9n2D7iZE3Y9/uXf/qsg9wyXOMA/Z/fwq+9oUWQB5b/bNDYiOEhziI5SECCrt38ITkCwSCipBPCCeKEABNDicMoAAqVEBU8VlWs6ZebVOtSm19tdKuPCxasapR26psqVmlULO1XtEi/cvY2KmHDLnsSfv66fNjn7y+nc7O2ON0Pp3O3tjY+dtrD8BxqLzb1zB0v6rttVgFjWJsl/+TV8HdZ78ZCUjID8TUBAQGbgIOmuyqmTOoXKNmNU6vSGA8bfWh8y31F0idQNoAZWZWRgAqgvkd0sO0IwpJ1QaB0XnBuuRvVl2xVnKwWT7fllE1dDyIPg+WMzDDqqObmKR9LjGz6sdaSOoevz7cvujvWRIdPhvc8nMwDHX7glIF4v/HKC+w4mCRfboW9LfBcXrBTUYl2KZzMCMBwpd0DnsaSB9kFCY6HVK3N9oAwkytK/c5iq+j7xwoOu5K+SjAKUpQdkHrIFPdFgnGLIi2DjhW7cptcJwvGgAs5rmQDjNGkrxFUEbBSIMyBnaV2nMc3jr1I8nvj48AMv4C/ZACHK8c14g6ZZhUJTUwjY58pHEWbHLKQfb89AT7DHv/Ag+oBEimGYCUfXCe0N8gqWSKAjimfxZGfiygn0OkNouLL8+vHnkT0JXyeaiBjD5GNiw+ak2n5239U78nttqek9lSXwTJW5nJysFqKOJzmZ+vMq4Uw5VySEPpzqbllQOZXekCEibjL5gCaHZVsbyGGnURU+HCEpHfyPiQuFEyTandWxG69KhEDuCPIPN3omhMdkn6iWY6cMbTpOO401st5UE31vmD2vBoqMGVQO+QIm4OEI+VEXdtc0wwlLeKmxRu+PfzI//j8IxTj+tjMUmA10qwIcvzLRrcZ8JwtjF3I7MxBwtiSHTPsiiIAfpd7EEDhg39ne/igBMcC3B2/0Z4Zwce5tYdxcCdXcUdtnhyf843+CtamIkcyF8AdHJMFE8W9vq0PwerqKhnCnjPa9b4LXjZFm4ObovRD/JDPUl+obXo+z7PvJ/5gQ7RTfpOIUVABviAOJ40VdZD+K7QwlgH/3s4vzsHsfkV3D4paBU2+ycpoGcBJ5AcPzkOmEMJlKISIsQGnljuB2ZP8sjFjIgv6uXzGkIOgtwwKSGiZ8AYvQofrJ8fdmcGAeD/S8AvObULdONJK/DbCIVTEL8+Een4xwl9XOT1UbVuoCCGE5EXV06ccKYdx5EOxxEO0TU60XCzP4e/fw9cAO+LBnDo9S+HngNenHVK0xS1iJqCfVyYEqJJAVsz37ddpVcnk11MDHRu5Ejh+ZqhxSwB9HtbJrmqqedI0XNJkdOpB4mwphy6xhAa0zqPQQQbzklo9zGxTx/OykPt8+/3N/7nmMNrNH/ir6/wve89+A4U8BZEbHXdHKF0svO8Mxwpe86ytiEPoHDUwWFbXiQTiUzPTCcuGFLsFEGIHujsgHUAJ3uNJ1KGDFiD8bSYO32IbWrPpdYNxAzmFxtaRoFR63pKTHjU4T3+eooqyfxl4Ei4a7H1tFIJrzj+o2ezSupD+H7zFIvauzHMG/yblNWZkyOcuEZn49d8ZIGRsk2shpZbnAdTSMolwhE5wNYPeHAyZ5yYhjNp8KdaUtqDsB6FfEBbsxLIU0RMsTUPlTJ4wUda0STSSktM0JIunfcrI3hRoHr+n8T4BIWy+Rdnoq9ByPhiVFSCeP/JNfpFlosfXTGyzKnW5vxEZ1dBv+s/8ZCk2Vakd1kGf/5L7JIkG9L5DQiCH+AgMFDYTJHShn65GPNKZC2tkbQzc5TyJuaNXRiK4bTK2j46TDWKeHMrEzvF4MoTvsfEXxPY20k0BLsgR2sH5/n59gTl4KP13Zy7YZIYrxFFsu5zvd5tVklND8u+scSIQ8xwvldc9gv5KuESaWKHt4hUWH6RnbVu/rf6z+Kr0FRVjLOD8zx+O0/+RdvRiudyQn0RPzxC6tYay3Hbh0+b2Cc5Vfz4hSad10/dX2cfMHK/qbg9425ZM3FbPIW/j1hWdi4sfwkoXDeXkZJ1cWfg2hTov271RgqfnNZYbr+ZOGjmtbppX8otZ8Gbggo18bg8DKMX2atvbzqklxTUWnvfz3t5V9G/PLzR14pNr3fYvJ1oe9sPS3H/LE9MeP0cU8f7cEdsMd28x/fODbW7F+7GE309nRpOvQZPGZfi1d9wiV+ohdDs0BXlRzNz0ZxMrkKmA+SpqNZHfTkfpmhgFtQ9jj9Gzj9CKyly5lzYOSrfmzvQCnL5yrXcLp47u/O2tqNKX/qk3xCA8nZIhyrHXPALsU6mNRI986QiNXRYPIZ8hqb2cfVYlQH2Jgb8i/Qk0jhrT6B/AOBw6ZJhgxzoehCcCTA2r/ZkVz6WhzIrMmg3AFJF61CoiLfQjwS+bk5nkZKEwQHUBDMGxZzVkeCfkIJU+y2gdfQXjZAUKXm8ltKWcShoEc+gHt2BhHx+YD/h3P58o6y+tpofO5UoTmM72e74fxaXLgY2sIykHL5TIS9s0nactQyxNO+8fbwdQcvfiV3F+g0SahxOX7eCaPHJ3vpbRw4elt6TVjZrZ4cLX7PvtojFVGc8H4ZxykrbrTZdWSeGS9vq6DjcaNlt+XUGlu81U/rkoVwpI93FzYSLrSHHHZNscW36Ch94mkNbEF4+wDtHM3J78Jy7D44KgHdGu1W+OKOYr++7t8Iq+GQ/Qs+f9X8EpfDy3rWfwIFEBZ89v5W/Hs1YwIwgv6b8fszKLBROf4F+2sTGcOmW7NtTCKN120+XbV3dM8ZbUM2uwkfkmdr+s9AvXp2+L5d1/JMU6LJ8iOrqXj9WwxRraXc4j1HvJj8j2aklhsZ3y2E+Bgurd2vVx96rv6HG/9iu9ZojnQUvfKyW39KY57ZWv+R3k1rNFlvXUI+mbe6qf9mMJZY9ypYaRRaiEuV3N3/2RwyJ3dEq7KrbE/2kPgcSQTWrrvld6n71nFddnzL8HU5tKLQ5Ob/ucbVfBu65TkgFdY6iRk/47JNFO499WmR1X2s2TP7ChsMC4PtmefCePvdbW7UBC5v6bK6d+w6K6vYkrTCcQttc46742nZ6x6I2+bCa+oXvy86HbozXIHrTqFS45RR/2sHkgZAiyUc67cYA6bJgL+nvK8PphurIojVxfbgyZKk0cbczbosujfCXx6aifKMvToVxeTXS0pTPVjLYidmHGKgj6F4npu8zbu+yMmqIwpVWCSJgCH4ywVm+6isKBM8DsdKDzG9OfmmO2A4tbsWaNKjPnhz3ZMabYWWxPRQekS+Akr4eriWyLm9r8gJTArjYvSWmnEjR3O03WJg8XkdDfz7+u5fUtutb8bVFdRXZxXx9thjqjE3l/Wn8au7hHGa9fWs/8vfe3SRiOtCSUes/Lh1cmMHLsoHOVJe3cXo577l/2eml4ueY+l2avpS8KdX5YFwjMX6VbdzlKt0fY7t/M12OE82dmK3oa/B0ZGtpMbDN0FiJeASazNUktHiD+xtzSX8ON3SXeN3Obn/Jr/WQtz58llg1XtSvkf0ZPFWcfPtMs4s0zjhnvL193cpvxvXZ9sx6C8jk2evC49ym91h9H3T2sEaXbmOvMvkJewak3W3D003I0pq3nG3I89VsyJB5ro2F+Dl0Xg6PDek6Mx2t+aVX7W6csjRbjawMgePSP0qNYyUBGVQiWTKf+Nibr+jZNX2RY0WLWm+udi+aGi0W2pPbSFpPyqWTmlU5GZq/pY6hmHwyJUEllsAmEcgrpKBUnRg3rjhoLttDcEZM7ucl1EzSp6L3UtBTzqaal58ouEcFPianpHykAhm150cvi6kmE6qbeAFRn0p7KXMd1lLzGpmJOTbwCMCxkxFWAc8g1DuSMAc/EAf/ALmswqfXCx4LjH7O7FXNpYJays20gRQ5Mzs7lZmjMDRR9ZIyuom5+Rk25DFfRGi0XfqtrNpzXKIFDOSPb190XMZkPKZL4Erhd9jxauPBBzXCqLbyMBqb2aERpaZ9Mp84xyb/pa0+34xmuZ7KPdWe+TcXxukcf84as5NXNep/4INk63V+vk1UgdO8/8z4xhdu7cJQ4n4rYfvPrLTgvv6bWPHOpOlbT/WhM+0RfjasWrOCjo+5bHtwHaidkCYpZZWs9JO8+prZznAq/XsjZiv70F0//x06FfcsWPL3E+4slHSTw3KXdB24uEp9UdXn1+L2+Jx5zezIOpPv5X80fejaMibqnYrr+hO7ydK/tfY+6U+9DC7UkTzxzXC63udse/yD+Vm5brxIQcVNrZnh3EtG40vIrCQaR4zV/z4a0UeO6CGHyiHvQNXhyMhumq79bBtwJd85axv9c2F1Vj4dzu8HlQ6b1lDO6n3VeBjqgYX/e1/yDB9K1icOu3uPbSh1DhSZVDji0iRStrJgGqK4Yo2AIQvOBM78uQRjcM44nAZoL5YjIi4ti0J8QFRBajRIrAfhtMeATNFiaaHDqvNGCX2y7ShG0mDfLHdywB7LVenqokRMyx5pPNswIbsYbTxzu4bE7uJwgpj6534ChuVivA1gPctWVLZm08e6dvRbjiydpttufuj4NtakrU9OC6EcNYYOQEEgnIsCI59Tq4xvlRsBCOlu7oguPsXizebnPcxs+U59tsft4G3Z8pO+2OPsXmdnodyu5aN+teGY6d/7OWk/EdzK2twpLT8L/eGz85V2S2L70d9i43Sr2HKcJW1P4ebb+ointrZof0NU8KXY5yWb+nJlbh66mWrZ59vk2f8Twaun50ulVjwej4JqfiOFkeh35v2dzLJk4n66X4Jd+B3ui2f5DyvJSs/ZdbDxPsXeXYaHjctBwOtZHr7+zWjTVvb2vvuXY8PNq8LGorzjufXP7mNhb3O250lzQ3jO+CmN/fh2h/C5737ic+ZmoC3axHspyw4v3fFzXp52Yc//U/Pv62wTr8fVfnA+7b3DOmhyh83/s3arPyb2Cg6VB2d7jp/yLXBj65d6HEsIgua2rnkkJ0B37yD3fbjg9myFfDYWimN15NDv866xPXgCgSoYn6Gwn+Uf8MmnKEAVS6EC6RyF4ll/fIKZOWG0jgZD0zZ9VEw+zO08HVhaJzlFuPyJWfnki6+0J4dqaifOLEBwAi6ZpP8/XmjQtAEu7u8+Z48PauVv7z5Fyyx6Gr59/yedxaGutThPldtG/xbjrasnNV4MDmGvAhM+zZGpis/pquGP5KT8h65tVe1g9tosbV/XmTf3IPEyf77hS7mdDua+N3iuczqojc30j84bsYHTttdvTyp7Ldntj96954/PNHx0OM1qHG3uDkh8byPriuZK/rbDop2UJ76O7/CJAb6FKyf7ZjssLhYc7N+dyyvbNbWZTysiP5inCFjsz1uw+JvDmo8V6azts9xfjuUG3/7LsTV9Ku5Pu8NeTmGk8Xe+PVnoZS5/R/9FKdGbF44txpSkPDutjtLLLmV39pTtHusfg+NY8dfK6N5AOG2t1lFVPw+Dag+NRfpjdW0wup/KzuegnrtT5ZRAvpcYylsAJM/tGn5NEc15HaRpAAAs/9PNF1qLQ2at+enCw9kJunBhLu5nG1tY3xmfnALUJ6bxZ1jlTPIkShMkzoVRFIrX52vAJWd9kgGclOOlKV6eKtO1PpfyrQ6Ti5ihsqqnWdEtz7mWN9Id288FMHezg2ehHy/paEUcGsoELBcfCfrFpg7/Jm9d/lTgGnGV5AzEfWZeCFiWwOoFAUEvniOLfRFYGrbiFDuDg/owjKIne7EP8Xhs1KOjO+TBTH93brp68LhK+qY2vE6fr37exee2CMF4TnvwgAl19iLBwiv5wKw4Ex+0H8Beakft1I+12Kl4HA7K3l5ruSbrFXdiYSNfMz9F1qmCQ7eF1563UT1m9DH+VrkrhT6sIzXuvSHHjpVxXseMWHA2kFxurJLEZS8U5zkb++nJPhbrEXlFMuUa5VF4r382rEVH26V5U+YQwweV2AO1IRfiP3ZhYrWuvRkPnxM9shXyYTm6jU+hhhvAcy0w0Mo03rJenXljE4qPc5k6pSyjoH5cz4cv+3VQ7FP8MDZv715tx2Jbm+HYWp908BTVSyT4DnUKWaTuyc8TMD/bdYctpr5qfQto+p0Oj526U/h3354n/KU4d9j+5WR8T7YZJtvSaL5hpDIaPeveO/WocEEtZL1janZxer8l+rB3uAxY3TMDjk6/kX8lYPXYfQXOis2ev3iLemv3pTr8jN4HqDJO3HUifmYk3CuZ12uS40/AXm0eyY9nioV3Yt3+V2c7iYxX0ySYZUrjjjRIDXvQJhpN1q5vb4sab5VsHCrMvGBQQO2lnCPnO8T1Y+fYznqwcaC6FW45a2ZeLLb71aTiftR/wPpMXRab1u9AS5gdQ8F7/ufJzsaLPzRTzsRzyfq+CE7uXUfxlgPqcJxiOeNd+ml7jD5XH9XwrRMtaUGfIT7Y3R2lzQNWv+jHo6U7mGlz0Y/C+CK5+AzweXwWOxQHGen0QHMttpG9C5t8fb7hM/Pf4PSg3DF6tO/3anHjR9HKqcZBfr1+gy+rXU0yvVGbPrfZkudrwbg8UtN2fQv3WjutXUVL/LUW6x088n7e+624bhWyN5p13Y7vt4ttbSJ6G7TTMdQ5O4qYHmfED5bTXAW26iNf2IunrRGF4qV8Lo/8zr4T24gV6rdaGTV2bm32sH31p+Pp6yu79KS9OEuf84q9W57CsOIiqw7vOTeC7yv78QGCffCq6itb0Bo71fkNKjZQlmOrDIpnn/xwKDJp
*/