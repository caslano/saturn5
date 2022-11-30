#ifndef BOOST_LEAF_CONTEXT_HPP_INCLUDED
#define BOOST_LEAF_CONTEXT_HPP_INCLUDED

// Copyright 2018-2022 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/leaf/config.hpp>
#include <boost/leaf/error.hpp>

#if !defined(BOOST_LEAF_NO_THREADS) && !defined(NDEBUG)
# include <thread>
#endif

namespace boost { namespace leaf {

class error_info;
class diagnostic_info;
class verbose_diagnostic_info;

template <class>
struct is_predicate: std::false_type
{
};

namespace leaf_detail
{
    template <class T>
    struct is_exception: std::is_base_of<std::exception, typename std::decay<T>::type>
    {
    };

    template <class E>
    struct handler_argument_traits;

    template <class E, bool IsPredicate = is_predicate<E>::value>
    struct handler_argument_traits_defaults;

    template <class E>
    struct handler_argument_traits_defaults<E, false>
    {
        using error_type = typename std::decay<E>::type;
        constexpr static bool always_available = false;

        template <class Tup>
        BOOST_LEAF_CONSTEXPR static error_type const * check( Tup const &, error_info const & ) noexcept;

        template <class Tup>
        BOOST_LEAF_CONSTEXPR static error_type * check( Tup &, error_info const & ) noexcept;

        template <class Tup>
        BOOST_LEAF_CONSTEXPR static E get( Tup & tup, error_info const & ei ) noexcept
        {
            return *check(tup, ei);
        }

        static_assert(!is_predicate<error_type>::value, "Handlers must take predicate arguments by value");
        static_assert(!std::is_same<E, error_info>::value, "Handlers must take leaf::error_info arguments by const &");
        static_assert(!std::is_same<E, diagnostic_info>::value, "Handlers must take leaf::diagnostic_info arguments by const &");
        static_assert(!std::is_same<E, verbose_diagnostic_info>::value, "Handlers must take leaf::verbose_diagnostic_info arguments by const &");
    };

    template <class Pred>
    struct handler_argument_traits_defaults<Pred, true>: handler_argument_traits<typename Pred::error_type>
    {
        using base = handler_argument_traits<typename Pred::error_type>;
        static_assert(!base::always_available, "Predicates can't use types that are always_available");

        template <class Tup>
        BOOST_LEAF_CONSTEXPR static bool check( Tup const & tup, error_info const & ei ) noexcept
        {
            auto e = base::check(tup, ei);
            return e && Pred::evaluate(*e);
        };

        template <class Tup>
        BOOST_LEAF_CONSTEXPR static Pred get( Tup const & tup, error_info const & ei ) noexcept
        {
            return Pred{*base::check(tup, ei)};
        }
    };

    template <class E>
    struct handler_argument_always_available
    {
        using error_type = E;
        constexpr static bool always_available = true;

        template <class Tup>
        BOOST_LEAF_CONSTEXPR static bool check( Tup &, error_info const & ) noexcept
        {
            return true;
        };
    };

    template <class E>
    struct handler_argument_traits: handler_argument_traits_defaults<E>
    {
    };

    template <>
    struct handler_argument_traits<void>
    {
        using error_type = void;
        constexpr static bool always_available = false;

        template <class Tup>
        BOOST_LEAF_CONSTEXPR static std::exception const * check( Tup const &, error_info const & ) noexcept;
    };

    template <class E>
    struct handler_argument_traits<E &&>
    {
        static_assert(sizeof(E) == 0, "Error handlers may not take rvalue ref arguments");
    };

    template <class E>
    struct handler_argument_traits<E *>: handler_argument_always_available<typename std::remove_const<E>::type>
    {
        template <class Tup>
        BOOST_LEAF_CONSTEXPR static E * get( Tup & tup, error_info const & ei) noexcept
        {
            return handler_argument_traits_defaults<E>::check(tup, ei);
        }
    };

    template <>
    struct handler_argument_traits<error_info const &>: handler_argument_always_available<void>
    {
        template <class Tup>
        BOOST_LEAF_CONSTEXPR static error_info const & get( Tup const &, error_info const & ei ) noexcept
        {
            return ei;
        }
    };

    template <class E>
    struct handler_argument_traits_require_by_value
    {
        static_assert(sizeof(E) == 0, "Error handlers must take this type by value");
    };
}

////////////////////////////////////////

namespace leaf_detail
{
    template <int I, class Tuple>
    struct tuple_for_each
    {
        BOOST_LEAF_CONSTEXPR static void activate( Tuple & tup ) noexcept
        {
            static_assert(!std::is_same<error_info, typename std::decay<decltype(std::get<I-1>(tup))>::type>::value, "Bug in LEAF: context type deduction");
            tuple_for_each<I-1,Tuple>::activate(tup);
            std::get<I-1>(tup).activate();
        }

        BOOST_LEAF_CONSTEXPR static void deactivate( Tuple & tup ) noexcept
        {
            static_assert(!std::is_same<error_info, typename std::decay<decltype(std::get<I-1>(tup))>::type>::value, "Bug in LEAF: context type deduction");
            std::get<I-1>(tup).deactivate();
            tuple_for_each<I-1,Tuple>::deactivate(tup);
        }

        BOOST_LEAF_CONSTEXPR static void propagate( Tuple & tup, int err_id ) noexcept
        {
            static_assert(!std::is_same<error_info, typename std::decay<decltype(std::get<I-1>(tup))>::type>::value, "Bug in LEAF: context type deduction");
            auto & sl = std::get<I-1>(tup);
            sl.propagate(err_id);
            tuple_for_each<I-1,Tuple>::propagate(tup, err_id);
        }

        BOOST_LEAF_CONSTEXPR static void propagate_captured( Tuple & tup, int err_id ) noexcept
        {
            static_assert(!std::is_same<error_info, typename std::decay<decltype(std::get<I-1>(tup))>::type>::value, "Bug in LEAF: context type deduction");
            BOOST_LEAF_ASSERT(err_id != 0);
            auto & sl = std::get<I-1>(tup);
            if( sl.has_value(err_id) )
                load_slot(err_id, std::move(sl).value(err_id));
            tuple_for_each<I-1,Tuple>::propagate_captured(tup, err_id);
        }

        template <class CharT, class Traits>
        static void print( std::basic_ostream<CharT, Traits> & os, void const * tup, int key_to_print )
        {
            BOOST_LEAF_ASSERT(tup != 0);
            tuple_for_each<I-1,Tuple>::print(os, tup, key_to_print);
            std::get<I-1>(*static_cast<Tuple const *>(tup)).print(os, key_to_print);
        }
    };

    template <class Tuple>
    struct tuple_for_each<0, Tuple>
    {
        BOOST_LEAF_CONSTEXPR static void activate( Tuple & ) noexcept { }
        BOOST_LEAF_CONSTEXPR static void deactivate( Tuple & ) noexcept { }
        BOOST_LEAF_CONSTEXPR static void propagate( Tuple &, int ) noexcept { }
        BOOST_LEAF_CONSTEXPR static void propagate_captured( Tuple &, int ) noexcept { }
        template <class CharT, class Traits>
        BOOST_LEAF_CONSTEXPR static void print( std::basic_ostream<CharT, Traits> &, void const *, int ) { }
    };
}

////////////////////////////////////////////

#if BOOST_LEAF_CFG_DIAGNOSTICS

namespace leaf_detail
{
    template <class T> struct requires_unexpected { constexpr static bool value = false; };
    template <class T> struct requires_unexpected<T const> { constexpr static bool value = requires_unexpected<T>::value; };
    template <class T> struct requires_unexpected<T const &> { constexpr static bool value = requires_unexpected<T>::value; };
    template <class T> struct requires_unexpected<T const *> { constexpr static bool value = requires_unexpected<T>::value; };
    template <> struct requires_unexpected<e_unexpected_count> { constexpr static bool value = true; };
    template <> struct requires_unexpected<e_unexpected_info> { constexpr static bool value = true; };

    template <class L>
    struct unexpected_requested;

    template <template <class ...> class L>
    struct unexpected_requested<L<>>
    {
        constexpr static bool value = false;
    };

    template <template <class...> class L, template <class> class S, class Car, class... Cdr>
    struct unexpected_requested<L<S<Car>, S<Cdr>...>>
    {
        constexpr static bool value = requires_unexpected<Car>::value || unexpected_requested<L<S<Cdr>...>>::value;
    };
}

#endif

////////////////////////////////////////////

namespace leaf_detail
{
    template <class T> struct does_not_participate_in_context_deduction: std::is_abstract<T> { };
    template <> struct does_not_participate_in_context_deduction<void>: std::true_type { };
    template <> struct does_not_participate_in_context_deduction<error_id>: std::true_type { };

    template <class L>
    struct deduce_e_type_list;

    template <template<class...> class L, class... T>
    struct deduce_e_type_list<L<T...>>
    {
        using type =
            leaf_detail_mp11::mp_remove_if<
                leaf_detail_mp11::mp_unique<
                    leaf_detail_mp11::mp_list<typename handler_argument_traits<T>::error_type...>
                >,
                does_not_participate_in_context_deduction
            >;
    };

    template <class L>
    struct deduce_e_tuple_impl;

    template <template <class...> class L, class... E>
    struct deduce_e_tuple_impl<L<E...>>
    {
        using type = std::tuple<slot<E>...>;
    };

    template <class... E>
    using deduce_e_tuple = typename deduce_e_tuple_impl<typename deduce_e_type_list<leaf_detail_mp11::mp_list<E...>>::type>::type;
}

////////////////////////////////////////////

template <class... E>
class context
{
    context( context const & ) = delete;
    context & operator=( context const & ) = delete;

    using Tup = leaf_detail::deduce_e_tuple<E...>;
    Tup tup_;
    bool is_active_;

#if !defined(BOOST_LEAF_NO_THREADS) && !defined(NDEBUG)
    std::thread::id thread_id_;
#endif

protected:

    BOOST_LEAF_CONSTEXPR error_id propagate_captured_errors( error_id err_id ) noexcept
    {
        leaf_detail::tuple_for_each<std::tuple_size<Tup>::value,Tup>::propagate_captured(tup_, err_id.value());
        return err_id;
    }

public:

    BOOST_LEAF_CONSTEXPR context( context && x ) noexcept:
        tup_(std::move(x.tup_)),
        is_active_(false)
    {
        BOOST_LEAF_ASSERT(!x.is_active());
    }

    BOOST_LEAF_CONSTEXPR context() noexcept:
        is_active_(false)
    {
    }

    ~context() noexcept
    {
        BOOST_LEAF_ASSERT(!is_active());
    }

    BOOST_LEAF_CONSTEXPR Tup const & tup() const noexcept
    {
        return tup_;
    }

    BOOST_LEAF_CONSTEXPR Tup & tup() noexcept
    {
        return tup_;
    }

    BOOST_LEAF_CONSTEXPR void activate() noexcept
    {
        using namespace leaf_detail;
        BOOST_LEAF_ASSERT(!is_active());
        tuple_for_each<std::tuple_size<Tup>::value,Tup>::activate(tup_);
#if BOOST_LEAF_CFG_DIAGNOSTICS
        if( unexpected_requested<Tup>::value )
            tls::uint32_increment<tls_tag_unexpected_enabled_counter>();
#endif
#if !defined(BOOST_LEAF_NO_THREADS) && !defined(NDEBUG)
        thread_id_ = std::this_thread::get_id();
#endif
        is_active_ = true;
    }

    BOOST_LEAF_CONSTEXPR void deactivate() noexcept
    {
        using namespace leaf_detail;
        BOOST_LEAF_ASSERT(is_active());
        is_active_ = false;
#if !defined(BOOST_LEAF_NO_THREADS) && !defined(NDEBUG)
        BOOST_LEAF_ASSERT(std::this_thread::get_id() == thread_id_);
        thread_id_ = std::thread::id();
#endif
#if BOOST_LEAF_CFG_DIAGNOSTICS
        if( unexpected_requested<Tup>::value )
            tls::uint32_decrement<tls_tag_unexpected_enabled_counter>();
#endif
        tuple_for_each<std::tuple_size<Tup>::value,Tup>::deactivate(tup_);
    }

    BOOST_LEAF_CONSTEXPR void propagate(error_id id) noexcept
    {
        BOOST_LEAF_ASSERT(!is_active());
        leaf_detail::tuple_for_each<std::tuple_size<Tup>::value,Tup>::propagate(tup_, id.value());
    }

    BOOST_LEAF_CONSTEXPR bool is_active() const noexcept
    {
        return is_active_;
    }

    template <class CharT, class Traits>
    void print( std::basic_ostream<CharT, Traits> & os ) const
    {
        leaf_detail::tuple_for_each<std::tuple_size<Tup>::value,Tup>::print(os, &tup_, 0);
    }

    template <class R, class... H>
    BOOST_LEAF_CONSTEXPR R handle_error( error_id, H && ... ) const;

    template <class R, class... H>
    BOOST_LEAF_CONSTEXPR R handle_error( error_id, H && ... );
};

////////////////////////////////////////

namespace leaf_detail
{
    template <class TypeList>
    struct deduce_context_impl;

    template <template <class...> class L, class... E>
    struct deduce_context_impl<L<E...>>
    {
        using type = context<E...>;
    };

    template <class TypeList>
    using deduce_context = typename deduce_context_impl<TypeList>::type;

    template <class H>
    struct fn_mp_args_fwd
    {
        using type = fn_mp_args<H>;
    };

    template <class... H>
    struct fn_mp_args_fwd<std::tuple<H...> &>: fn_mp_args_fwd<std::tuple<H...>> { };

    template <class... H>
    struct fn_mp_args_fwd<std::tuple<H...> const &>: fn_mp_args_fwd<std::tuple<H...>> { };

    template <class... H>
    struct fn_mp_args_fwd<std::tuple<H...>>
    {
        using type = leaf_detail_mp11::mp_append<typename fn_mp_args_fwd<H>::type...>;
    };

    template <class... H>
    struct context_type_from_handlers_impl
    {
        using type = deduce_context<leaf_detail_mp11::mp_append<typename fn_mp_args_fwd<H>::type...>>;
    };

    template <class Ctx>
    struct polymorphic_context_impl: polymorphic_context, Ctx
    {
        error_id propagate_captured_errors() noexcept final override { return Ctx::propagate_captured_errors(captured_id_); }
        void activate() noexcept final override { Ctx::activate(); }
        void deactivate() noexcept final override { Ctx::deactivate(); }
        void propagate(error_id id) noexcept final override { Ctx::propagate(id); }
        bool is_active() const noexcept final override { return Ctx::is_active(); }
#if BOOST_LEAF_CFG_DIAGNOSTICS
        void print( std::ostream & os ) const final override { return Ctx::print(os); }
#endif
    };
}

template <class... H>
using context_type_from_handlers = typename leaf_detail::context_type_from_handlers_impl<H...>::type;

////////////////////////////////////////////

template <class...  H>
BOOST_LEAF_CONSTEXPR inline context_type_from_handlers<H...> make_context() noexcept
{
    return { };
}

template <class...  H>
BOOST_LEAF_CONSTEXPR inline context_type_from_handlers<H...> make_context( H && ... ) noexcept
{
    return { };
}

////////////////////////////////////////////

#if BOOST_LEAF_CFG_CAPTURE

template <class...  H>
inline context_ptr make_shared_context() noexcept
{
    return std::make_shared<leaf_detail::polymorphic_context_impl<context_type_from_handlers<H...>>>();
}

template <class...  H>
inline context_ptr make_shared_context( H && ... ) noexcept
{
    return std::make_shared<leaf_detail::polymorphic_context_impl<context_type_from_handlers<H...>>>();
}

#endif

} }

#endif

/* context.hpp
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
*/