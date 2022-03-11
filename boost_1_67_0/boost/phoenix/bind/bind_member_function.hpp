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