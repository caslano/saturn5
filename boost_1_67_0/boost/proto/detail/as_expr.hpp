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