#ifndef BOOST_LEAF_ON_ERROR_HPP_INCLUDED
#define BOOST_LEAF_ON_ERROR_HPP_INCLUDED

// Copyright 2018-2022 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/leaf/config.hpp>
#include <boost/leaf/error.hpp>

namespace boost { namespace leaf {

class error_monitor
{
#if !defined(BOOST_LEAF_NO_EXCEPTIONS) && BOOST_LEAF_STD_UNCAUGHT_EXCEPTIONS
    int const uncaught_exceptions_;
#endif
    int const err_id_;

public:

    error_monitor() noexcept:
#if !defined(BOOST_LEAF_NO_EXCEPTIONS) && BOOST_LEAF_STD_UNCAUGHT_EXCEPTIONS
        uncaught_exceptions_(std::uncaught_exceptions()),
#endif
        err_id_(leaf_detail::current_id())
    {
    }

    int check_id() const noexcept
    {
        int err_id = leaf_detail::current_id();
        if( err_id != err_id_ )
            return err_id;
        else
        {
#ifndef BOOST_LEAF_NO_EXCEPTIONS
#   if BOOST_LEAF_STD_UNCAUGHT_EXCEPTIONS
            if( std::uncaught_exceptions() > uncaught_exceptions_ )
#   else
            if( std::uncaught_exception() )
#   endif
                return leaf_detail::new_id();
#endif
            return 0;
        }
    }

    int get_id() const noexcept
    {
        int err_id = leaf_detail::current_id();
        if( err_id != err_id_ )
            return err_id;
        else
            return leaf_detail::new_id();
    }

    error_id check() const noexcept
    {
        return leaf_detail::make_error_id(check_id());
    }

    error_id assigned_error_id() const noexcept
    {
        return leaf_detail::make_error_id(get_id());
    }
};

////////////////////////////////////////////

namespace leaf_detail
{
    template <int I, class Tuple>
    struct tuple_for_each_preload
    {
        BOOST_LEAF_CONSTEXPR static void trigger( Tuple & tup, int err_id ) noexcept
        {
            BOOST_LEAF_ASSERT((err_id&3)==1);
            tuple_for_each_preload<I-1,Tuple>::trigger(tup,err_id);
            std::get<I-1>(tup).trigger(err_id);
        }
    };

    template <class Tuple>
    struct tuple_for_each_preload<0, Tuple>
    {
        BOOST_LEAF_CONSTEXPR static void trigger( Tuple const &, int ) noexcept { }
    };

    template <class E>
    class preloaded_item
    {
        using decay_E = typename std::decay<E>::type;
        slot<decay_E> * s_;
        decay_E e_;

    public:

        BOOST_LEAF_CONSTEXPR preloaded_item( E && e ):
            s_(tls::read_ptr<slot<decay_E>>()),
            e_(std::forward<E>(e))
        {
        }

        BOOST_LEAF_CONSTEXPR void trigger( int err_id ) noexcept
        {
            BOOST_LEAF_ASSERT((err_id&3)==1);
            if( s_ )
            {
                if( !s_->has_value(err_id) )
                    s_->put(err_id, std::move(e_));
            }
#if BOOST_LEAF_CFG_DIAGNOSTICS
            else
            {
                int c = tls::read_uint32<tls_tag_unexpected_enabled_counter>();
                BOOST_LEAF_ASSERT(c>=0);
                if( c )
                    load_unexpected(err_id, std::move(e_));
            }
#endif
        }
    };

    template <class F>
    class deferred_item
    {
        using E = decltype(std::declval<F>()());
        slot<E> * s_;
        F f_;

    public:

        BOOST_LEAF_CONSTEXPR deferred_item( F && f ) noexcept:
            s_(tls::read_ptr<slot<E>>()),
            f_(std::forward<F>(f))
        {
        }

        BOOST_LEAF_CONSTEXPR void trigger( int err_id ) noexcept
        {
            BOOST_LEAF_ASSERT((err_id&3)==1);
            if( s_ )
            {
                if( !s_->has_value(err_id) )
                    s_->put(err_id, f_());
            }
#if BOOST_LEAF_CFG_DIAGNOSTICS
            else
            {
                int c = tls::read_uint32<tls_tag_unexpected_enabled_counter>();
                BOOST_LEAF_ASSERT(c>=0);
                if( c )
                    load_unexpected(err_id, std::forward<E>(f_()));
            }
#endif
        }
    };

    template <class F, class A0 = fn_arg_type<F,0>, int arity = function_traits<F>::arity>
    class accumulating_item;

    template <class F, class A0>
    class accumulating_item<F, A0 &, 1>
    {
        using E = A0;
        slot<E> * s_;
        F f_;

    public:

        BOOST_LEAF_CONSTEXPR accumulating_item( F && f ) noexcept:
            s_(tls::read_ptr<slot<E>>()),
            f_(std::forward<F>(f))
        {
        }

        BOOST_LEAF_CONSTEXPR void trigger( int err_id ) noexcept
        {
            BOOST_LEAF_ASSERT((err_id&3)==1);
            if( s_ )
                if( E * e = s_->has_value(err_id) )
                    (void) f_(*e);
                else
                    (void) f_(s_->put(err_id, E()));
        }
    };

    template <class... Item>
    class preloaded
    {
        preloaded & operator=( preloaded const & ) = delete;

        std::tuple<Item...> p_;
        bool moved_;
        error_monitor id_;

    public:

        BOOST_LEAF_CONSTEXPR explicit preloaded( Item && ... i ):
            p_(std::forward<Item>(i)...),
            moved_(false)
        {
        }

        BOOST_LEAF_CONSTEXPR preloaded( preloaded && x ) noexcept:
            p_(std::move(x.p_)),
            moved_(false),
            id_(std::move(x.id_))
        {
            x.moved_ = true;
        }

        ~preloaded() noexcept
        {
            if( moved_ )
                return;
            if( auto id = id_.check_id() )
                tuple_for_each_preload<sizeof...(Item),decltype(p_)>::trigger(p_,id);
        }
    };

    template <class T, int arity = function_traits<T>::arity>
    struct deduce_item_type;

    template <class T>
    struct deduce_item_type<T, -1>
    {
        using type = preloaded_item<T>;
    };

    template <class F>
    struct deduce_item_type<F, 0>
    {
        using type = deferred_item<F>;
    };

    template <class F>
    struct deduce_item_type<F, 1>
    {
        using type = accumulating_item<F>;
    };
}

template <class... Item>
BOOST_LEAF_NODISCARD BOOST_LEAF_CONSTEXPR inline
leaf_detail::preloaded<typename leaf_detail::deduce_item_type<Item>::type...>
on_error( Item && ... i )
{
    return leaf_detail::preloaded<typename leaf_detail::deduce_item_type<Item>::type...>(std::forward<Item>(i)...);
}

} }

#endif

/* on_error.hpp
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
*/