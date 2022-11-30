/*=============================================================================
    Copyright (c) 2016 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef PHOENIX_BIND_BIND_MEMBER_FUNCTION_HPP
#define PHOENIX_BIND_BIND_MEMBER_FUNCTION_HPP

#include <boost/phoenix/core/limits.hpp>

#if defined(BOOST_PHOENIX_NO_VARIADIC_BIND)
# include <boost/phoenix/bind/detail/cpp03/bind_member_function.hpp>
#else

#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/reference.hpp>
#include <boost/phoenix/core/detail/function_eval.hpp>

namespace boost { namespace phoenix
{
    namespace detail
    {
        template <typename RT, typename FP>
        struct member_function_ptr
        {
            typedef RT result_type;

            member_function_ptr(FP fp_)
                : fp(fp_) {}

            template <typename Class, typename... A>
            result_type operator()(Class& obj, A&... a) const
            {
                BOOST_PROTO_USE_GET_POINTER();

                typedef typename proto::detail::class_member_traits<FP>::class_type class_type;
                return (BOOST_PROTO_GET_POINTER(class_type, obj)->*fp)(a...);
            }

            template <typename Class, typename... A>
            result_type operator()(Class* obj, A&... a) const
            {
                return (obj->*fp)(a...);
            }

            bool operator==(member_function_ptr const& rhs) const
            {
                return fp == rhs.fp;
            }

            template <int M, typename RhsRT, typename RhsFP>
            bool operator==(member_function_ptr<RhsRT, RhsFP> const& /*rhs*/) const
            {
                return false;
            }

            FP fp;
        };
    } // namespace boost::phoenix::detail

    template <typename RT, typename ClassT, typename... T, typename ClassA, typename... A>
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<RT, RT(ClassT::*)(T...)>
      , ClassA
      , A...
    >::type const
    bind(RT (ClassT::*f)(T...), ClassA const & obj, A const&... a)
    {
        typedef detail::member_function_ptr<RT, RT (ClassT::*)(T...)> fp_type;
        return detail::expression::function_eval<fp_type, ClassA, A...>::make(fp_type(f), obj, a...);
    }

    template <typename RT, typename ClassT, typename... T, typename ClassA, typename... A>
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<RT, RT (ClassT::*)(T...) const>
      , ClassA
      , A...
    >::type const
    bind(RT (ClassT::*f)(T...) const, ClassA const & obj, A const&... a)
    {
        typedef detail::member_function_ptr<RT, RT(ClassT::*)(T...) const> fp_type;
        return detail::expression::function_eval<fp_type, ClassA, A...>::make(fp_type(f), obj, a...);
    }

    template <typename RT, typename ClassT, typename... T, typename... A>
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<RT, RT(ClassT::*)(T...)>
      , ClassT
      , A...
    >::type const
    bind(RT (ClassT::*f)(T...), ClassT & obj, A const&... a)
    {
        typedef detail::member_function_ptr<RT, RT(ClassT::*)(T...)> fp_type;
        return detail::expression::function_eval<fp_type, ClassT, A...>::make(fp_type(f), obj, a...);
    }

    template <typename RT, typename ClassT, typename... T, typename... A>
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<RT, RT(ClassT::*)(T...) const>
      , ClassT
      , A...
    >::type const
    bind(RT (ClassT::*f)(T...) const, ClassT const& obj, A const&... a)
    {
        typedef detail::member_function_ptr<RT, RT(ClassT::*)(T...) const> fp_type;
        return detail::expression::function_eval<fp_type, ClassT, A...>::make(fp_type(f), obj, a...);
    }
}} // namespace boost::phoenix

#endif
#endif

/* bind_member_function.hpp
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
*/