///////////////////////////////////////////////////////////////////////////////
/// \file as_expr.hpp
/// Contains definition of the as_expr\<\> and as_child\<\> helper class
/// templates used to implement proto::domain's as_expr\<\> and as_child\<\>
/// member templates.
//
//  Copyright 2010 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_DETAIL_AS_EXPR_HPP_EAN_06_09_2010
#define BOOST_PROTO_DETAIL_AS_EXPR_HPP_EAN_06_09_2010

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/args.hpp>

#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 4714) // function 'xxx' marked as __forceinline not inlined
#endif

namespace boost { namespace proto { namespace detail
{

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename Generator>
    struct base_generator
    {
        typedef Generator type;
    };

    template<typename Generator>
    struct base_generator<use_basic_expr<Generator> >
    {
        typedef Generator type;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, typename Generator, bool WantsBasicExpr>
    struct as_expr;

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, typename Generator>
    struct as_expr<T, Generator, false>
    {
        typedef typename term_traits<T &>::value_type value_type;
        typedef proto::expr<proto::tag::terminal, term<value_type>, 0> expr_type;
        typedef typename Generator::template result<Generator(expr_type)>::type result_type;

        BOOST_FORCEINLINE
        result_type operator()(T &t) const
        {
            return Generator()(expr_type::make(t));
        }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, typename Generator>
    struct as_expr<T, Generator, true>
    {
        typedef typename term_traits<T &>::value_type value_type;
        typedef proto::basic_expr<proto::tag::terminal, term<value_type>, 0> expr_type;
        typedef typename Generator::template result<Generator(expr_type)>::type result_type;

        BOOST_FORCEINLINE
        result_type operator()(T &t) const
        {
            return Generator()(expr_type::make(t));
        }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    struct as_expr<T, proto::default_generator, false>
    {
        typedef typename term_traits<T &>::value_type value_type;
        typedef proto::expr<proto::tag::terminal, term<value_type>, 0> result_type;

        BOOST_FORCEINLINE
        result_type operator()(T &t) const
        {
            return result_type::make(t);
        }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    struct as_expr<T, proto::default_generator, true>
    {
        typedef typename term_traits<T &>::value_type value_type;
        typedef proto::basic_expr<proto::tag::terminal, term<value_type>, 0> result_type;

        BOOST_FORCEINLINE
        result_type operator()(T &t) const
        {
            return result_type::make(t);
        }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, typename Generator, bool WantsBasicExpr>
    struct as_child;

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, typename Generator>
    struct as_child<T, Generator, false>
    {
    #if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
        typedef typename term_traits<T &>::reference reference;
    #else
        typedef T &reference;
    #endif
        typedef proto::expr<proto::tag::terminal, term<reference>, 0> expr_type;
        typedef typename Generator::template result<Generator(expr_type)>::type result_type;

        BOOST_FORCEINLINE
        result_type operator()(T &t) const
        {
            return Generator()(expr_type::make(t));
        }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, typename Generator>
    struct as_child<T, Generator, true>
    {
    #if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
        typedef typename term_traits<T &>::reference reference;
    #else
        typedef T &reference;
    #endif
        typedef proto::basic_expr<proto::tag::terminal, term<reference>, 0> expr_type;
        typedef typename Generator::template result<Generator(expr_type)>::type result_type;

        BOOST_FORCEINLINE
        result_type operator()(T &t) const
        {
            return Generator()(expr_type::make(t));
        }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    struct as_child<T, proto::default_generator, false>
    {
    #if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
        typedef typename term_traits<T &>::reference reference;
    #else
        typedef T &reference;
    #endif
        typedef proto::expr<proto::tag::terminal, term<reference>, 0> result_type;

        BOOST_FORCEINLINE
        result_type operator()(T &t) const
        {
            return result_type::make(t);
        }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    struct as_child<T, proto::default_generator, true>
    {
    #if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
        typedef typename term_traits<T &>::reference reference;
    #else
        typedef T &reference;
    #endif
        typedef proto::basic_expr<proto::tag::terminal, term<reference>, 0> result_type;

        BOOST_FORCEINLINE
        result_type operator()(T &t) const
        {
            return result_type::make(t);
        }
    };

}}}

#if defined(_MSC_VER)
# pragma warning(pop)
#endif

#endif

/* as_expr.hpp
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
*/