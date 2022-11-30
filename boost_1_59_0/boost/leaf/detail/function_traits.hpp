#ifndef BOOST_LEAF_DETAIL_FUNCTION_TRAITS_HPP_INCLUDED
#define BOOST_LEAF_DETAIL_FUNCTION_TRAITS_HPP_INCLUDED

// Copyright 2018-2022 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/leaf/detail/mp11.hpp>

#include <tuple>

namespace boost { namespace leaf {

namespace leaf_detail
{
    template <class T> struct remove_noexcept { using type = T; };
    template <class R, class... A>  struct remove_noexcept<R(*)(A...) noexcept> { using type = R(*)(A...); };
    template <class C, class R, class... A>  struct remove_noexcept<R(C::*)(A...) noexcept> { using type = R(C::*)(A...); };
    template <class C, class R, class... A>  struct remove_noexcept<R(C::*)(A...) const noexcept> { using type = R(C::*)(A...) const; };

    template<class...>
    struct gcc49_workaround //Thanks Glen Fernandes
    {
        using type = void;
    };

    template<class... T>
    using void_t = typename gcc49_workaround<T...>::type;

    template<class F,class V=void>
    struct function_traits_impl
    {
        constexpr static int arity = -1;
    };

    template<class F>
    struct function_traits_impl<F, void_t<decltype(&F::operator())>>
    {
    private:

        using tr = function_traits_impl<typename remove_noexcept<decltype(&F::operator())>::type>;

    public:

        using return_type = typename tr::return_type;
        static constexpr int arity = tr::arity - 1;

        using mp_args = typename leaf_detail_mp11::mp_rest<typename tr::mp_args>;

        template <int I>
        struct arg:
            tr::template arg<I+1>
        {
        };
    };

    template<class R, class... A>
    struct function_traits_impl<R(A...)>
    {
        using return_type = R;
        static constexpr int arity = sizeof...(A);

        using mp_args = leaf_detail_mp11::mp_list<A...>;

        template <int I>
        struct arg
        {
            static_assert(I < arity, "I out of range");
            using type = typename std::tuple_element<I,std::tuple<A...>>::type;
        };
    };

    template<class F> struct function_traits_impl<F&> : function_traits_impl<F> { };
    template<class F> struct function_traits_impl<F&&> : function_traits_impl<F> { };
    template<class R, class... A> struct function_traits_impl<R(*)(A...)> : function_traits_impl<R(A...)> { };
    template<class R, class... A> struct function_traits_impl<R(* &)(A...)> : function_traits_impl<R(A...)> { };
    template<class R, class... A> struct function_traits_impl<R(* const &)(A...)> : function_traits_impl<R(A...)> { };
    template<class C, class R, class... A> struct function_traits_impl<R(C::*)(A...)> : function_traits_impl<R(C&,A...)> { };
    template<class C, class R, class... A> struct function_traits_impl<R(C::*)(A...) const> : function_traits_impl<R(C const &,A...)> { };
    template<class C, class R> struct function_traits_impl<R(C::*)> : function_traits_impl<R(C&)> { };

    template <class F>
    struct function_traits: function_traits_impl<typename remove_noexcept<F>::type>
    {
    };

    template <class F>
    using fn_return_type = typename function_traits<F>::return_type;

    template <class F, int I>
    using fn_arg_type = typename function_traits<F>::template arg<I>::type;

    template <class F>
    using fn_mp_args = typename function_traits<F>::mp_args;
}

} }

#endif

/* function_traits.hpp
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
*/