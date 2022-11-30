#ifndef BOOST_LEAF_HANDLE_ERRORS_HPP_INCLUDED
#define BOOST_LEAF_HANDLE_ERRORS_HPP_INCLUDED

// Copyright 2018-2022 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/leaf/config.hpp>
#include <boost/leaf/context.hpp>
#include <boost/leaf/capture.hpp>
#include <boost/leaf/detail/demangle.hpp>

namespace boost { namespace leaf {

class BOOST_LEAF_SYMBOL_VISIBLE error_info
{
    error_info & operator=( error_info const & ) = delete;

#ifndef BOOST_LEAF_NO_EXCEPTIONS
    static error_id unpack_error_id( std::exception const * ex ) noexcept
    {
#if BOOST_LEAF_CFG_STD_SYSTEM_ERROR
        if( std::system_error const * se = dynamic_cast<std::system_error const *>(ex) )
            if( is_error_id(se->code()) )
                return leaf_detail::make_error_id(se->code().value());
        if( std::error_code const * ec = dynamic_cast<std::error_code const *>(ex) )
            if( is_error_id(*ec) )
                return leaf_detail::make_error_id(ec->value());
#endif
        if( error_id const * err_id = dynamic_cast<error_id const *>(ex) )
            return *err_id;
        return current_error();
    }

    std::exception * const ex_;
#endif

    error_id const err_id_;

protected:

    error_info( error_info const & ) noexcept = default;

    template <class CharT, class Traits>
    void print( std::basic_ostream<CharT, Traits> & os ) const
    {
        os << "Error ID = " << err_id_.value();
#ifndef BOOST_LEAF_NO_EXCEPTIONS
        if( ex_ )
        {
            os <<
                "\nException dynamic type: " << leaf_detail::demangle(typeid(*ex_).name()) <<
                "\nstd::exception::what(): " << ex_->what();
        }
#endif
    }

public:

    BOOST_LEAF_CONSTEXPR explicit error_info( error_id id ) noexcept:
#ifndef BOOST_LEAF_NO_EXCEPTIONS
        ex_(0),
#endif
        err_id_(id)
    {
    }

#ifndef BOOST_LEAF_NO_EXCEPTIONS
    explicit error_info( std::exception * ex ) noexcept:
        ex_(ex),
        err_id_(unpack_error_id(ex_))
    {
    }
#endif

    BOOST_LEAF_CONSTEXPR error_id error() const noexcept
    {
        return err_id_;
    }

    BOOST_LEAF_CONSTEXPR std::exception * exception() const noexcept
    {
#ifdef BOOST_LEAF_NO_EXCEPTIONS
        return nullptr;
#else
        return ex_;
#endif
    }

    template <class CharT, class Traits>
    friend std::basic_ostream<CharT, Traits> & operator<<( std::basic_ostream<CharT, Traits> & os, error_info const & x )
    {
        os << "leaf::error_info: ";
        x.print(os);
        return os << '\n';
    }
};

////////////////////////////////////////

#if BOOST_LEAF_CFG_DIAGNOSTICS

class BOOST_LEAF_SYMBOL_VISIBLE diagnostic_info: public error_info
{
    leaf_detail::e_unexpected_count const * e_uc_;
    void const * tup_;
    void (*print_)( std::ostream &, void const * tup, int key_to_print );

protected:

    diagnostic_info( diagnostic_info const & ) noexcept = default;

    template <class Tup>
    BOOST_LEAF_CONSTEXPR diagnostic_info( error_info const & ei, leaf_detail::e_unexpected_count const * e_uc, Tup const & tup ) noexcept:
        error_info(ei),
        e_uc_(e_uc),
        tup_(&tup),
        print_(&leaf_detail::tuple_for_each<std::tuple_size<Tup>::value, Tup>::print)
    {
    }

public:

    template <class CharT, class Traits>
    friend std::basic_ostream<CharT, Traits> & operator<<( std::basic_ostream<CharT, Traits> & os, diagnostic_info const & x )
    {
        os << "leaf::diagnostic_info for ";
        x.print(os);
        os << ":\n";
        x.print_(os, x.tup_, x.error().value());
        if( x.e_uc_  )
            x.e_uc_->print(os);
        return os;
    }
};

namespace leaf_detail
{
    struct diagnostic_info_: diagnostic_info
    {
        template <class Tup>
        BOOST_LEAF_CONSTEXPR diagnostic_info_( error_info const & ei, leaf_detail::e_unexpected_count const * e_uc, Tup const & tup ) noexcept:
            diagnostic_info(ei, e_uc, tup)
        {
        }
    };

    template <>
    struct handler_argument_traits<diagnostic_info const &>: handler_argument_always_available<e_unexpected_count>
    {
        template <class Tup>
        BOOST_LEAF_CONSTEXPR static diagnostic_info_ get( Tup const & tup, error_info const & ei ) noexcept
        {
            return diagnostic_info_(ei, handler_argument_traits_defaults<e_unexpected_count>::check(tup, ei), tup);
        }
    };
}

#else

class BOOST_LEAF_SYMBOL_VISIBLE diagnostic_info: public error_info
{
protected:

    diagnostic_info( diagnostic_info const & ) noexcept = default;

    BOOST_LEAF_CONSTEXPR diagnostic_info( error_info const & ei ) noexcept:
        error_info(ei)
    {
    }

public:

    template <class CharT, class Traits>
    friend std::basic_ostream<CharT, Traits> & operator<<( std::basic_ostream<CharT, Traits> & os, diagnostic_info const & x )
    {
        os <<
            "leaf::diagnostic_info requires #define BOOST_LEAF_CFG_DIAGNOSTICS 1\n"
            "leaf::error_info: ";
        x.print(os);
        return os << '\n';
    }
};

namespace leaf_detail
{
    struct diagnostic_info_: diagnostic_info
    {
        BOOST_LEAF_CONSTEXPR diagnostic_info_( error_info const & ei ) noexcept:
            diagnostic_info(ei)
        {
        }
    };

    template <>
    struct handler_argument_traits<diagnostic_info const &>: handler_argument_always_available<void>
    {
        template <class Tup>
        BOOST_LEAF_CONSTEXPR static diagnostic_info_ get( Tup const & tup, error_info const & ei ) noexcept
        {
            return diagnostic_info_(ei);
        }
    };
}

#endif

////////////////////////////////////////

#if BOOST_LEAF_CFG_DIAGNOSTICS

class BOOST_LEAF_SYMBOL_VISIBLE verbose_diagnostic_info: public error_info
{
    leaf_detail::e_unexpected_info const * e_ui_;
    void const * tup_;
    void (*print_)( std::ostream &, void const * tup, int key_to_print );

protected:

    verbose_diagnostic_info( verbose_diagnostic_info const & ) noexcept = default;

    template <class Tup>
    BOOST_LEAF_CONSTEXPR verbose_diagnostic_info( error_info const & ei, leaf_detail::e_unexpected_info const * e_ui, Tup const & tup ) noexcept:
        error_info(ei),
        e_ui_(e_ui),
        tup_(&tup),
        print_(&leaf_detail::tuple_for_each<std::tuple_size<Tup>::value, Tup>::print)
    {
    }

public:

    template <class CharT, class Traits>
    friend std::basic_ostream<CharT, Traits> & operator<<( std::basic_ostream<CharT, Traits> & os, verbose_diagnostic_info const & x )
    {
        os << "leaf::verbose_diagnostic_info for ";
        x.print(os);
        os << ":\n";
        x.print_(os, x.tup_, x.error().value());
        if( x.e_ui_ )
            x.e_ui_->print(os);
        return os;
    }
};

namespace leaf_detail
{
    struct verbose_diagnostic_info_: verbose_diagnostic_info
    {
        template <class Tup>
        BOOST_LEAF_CONSTEXPR verbose_diagnostic_info_( error_info const & ei, leaf_detail::e_unexpected_info const * e_ui, Tup const & tup ) noexcept:
            verbose_diagnostic_info(ei, e_ui, tup)
        {
        }
    };

    template <>
    struct handler_argument_traits<verbose_diagnostic_info const &>: handler_argument_always_available<e_unexpected_info>
    {
        template <class Tup>
        BOOST_LEAF_CONSTEXPR static verbose_diagnostic_info_ get( Tup const & tup, error_info const & ei ) noexcept
        {
            return verbose_diagnostic_info_(ei, handler_argument_traits_defaults<e_unexpected_info>::check(tup, ei), tup);
        }
    };
}

#else

class BOOST_LEAF_SYMBOL_VISIBLE verbose_diagnostic_info: public error_info
{
protected:

    verbose_diagnostic_info( verbose_diagnostic_info const & ) noexcept = default;

    BOOST_LEAF_CONSTEXPR verbose_diagnostic_info( error_info const & ei ) noexcept:
        error_info(ei)
    {
    }

public:

    template <class CharT, class Traits>
    friend std::basic_ostream<CharT, Traits> & operator<<( std::basic_ostream<CharT, Traits> & os, verbose_diagnostic_info const & x )
    {
        os <<
            "leaf::verbose_diagnostic_info requires #define BOOST_LEAF_CFG_DIAGNOSTICS 1\n"
            "leaf::error_info: ";
        x.print(os);
        return os << '\n';
    }
};

namespace leaf_detail
{
    struct verbose_diagnostic_info_: verbose_diagnostic_info
    {
        BOOST_LEAF_CONSTEXPR verbose_diagnostic_info_( error_info const & ei ) noexcept:
            verbose_diagnostic_info(ei)
        {
        }
    };


    template <>
    struct handler_argument_traits<verbose_diagnostic_info const &>: handler_argument_always_available<void>
    {
        template <class Tup>
        BOOST_LEAF_CONSTEXPR static verbose_diagnostic_info_ get( Tup const & tup, error_info const & ei ) noexcept
        {
            return verbose_diagnostic_info_(ei);
        }
    };
}

#endif

////////////////////////////////////////

namespace leaf_detail
{
    template <class T, class... List>
    struct type_index;

    template <class T, class... Cdr>
    struct type_index<T, T, Cdr...>
    {
        constexpr static int value = 0;
    };

    template <class T, class Car, class... Cdr>
    struct type_index<T, Car, Cdr...>
    {
        constexpr static int value = 1 + type_index<T,Cdr...>::value;
    };

    template <class T, class Tuple>
    struct tuple_type_index;

    template <class T, class... TupleTypes>
    struct tuple_type_index<T,std::tuple<TupleTypes...>>
    {
        constexpr static int value = type_index<T,TupleTypes...>::value;
    };

#ifndef BOOST_LEAF_NO_EXCEPTIONS

    template <class E, bool = std::is_class<E>::value>
    struct peek_exception;

    template <>
    struct peek_exception<std::exception const, true>
    {
        BOOST_LEAF_CONSTEXPR static std::exception const * peek( error_info const & ei ) noexcept
        {
            return ei.exception();
        }
    };

    template <>
    struct peek_exception<std::exception, true>
    {
        BOOST_LEAF_CONSTEXPR static std::exception * peek( error_info const & ei ) noexcept
        {
            return ei.exception();
        }
    };

#if BOOST_LEAF_CFG_STD_SYSTEM_ERROR
    template <>
    struct peek_exception<std::error_code const, true>
    {
        static std::error_code const * peek( error_info const & ei ) noexcept
        {
            auto const ex = ei.exception();
            if( std::system_error * se = dynamic_cast<std::system_error *>(ex) )
                return &se->code();
            else if( std::error_code * ec = dynamic_cast<std::error_code *>(ex) )
                return ec;
            else
                return 0;
        }
    };

    template <>
    struct peek_exception<std::error_code, true>
    {
        static std::error_code * peek( error_info const & ei ) noexcept
        {
            auto const ex = ei.exception();
            if( std::system_error * se = dynamic_cast<std::system_error *>(ex) )
                return const_cast<std::error_code *>(&se->code());
            else if( std::error_code * ec = dynamic_cast<std::error_code *>(ex) )
                return ec;
            else
                return 0;
        }
    };
#endif

    template <class E>
    struct peek_exception<E, true>
    {
        static E * peek( error_info const & ei ) noexcept
        {
            return dynamic_cast<E *>(ei.exception());
        }
    };

    template <class E>
    struct peek_exception<E, false>
    {
        BOOST_LEAF_CONSTEXPR static E * peek( error_info const & ) noexcept
        {
            return 0;
        }
    };

#endif

    template <class E, bool = does_not_participate_in_context_deduction<E>::value>
    struct peek_tuple;

    template <class E>
    struct peek_tuple<E, true>
    {
        template <class SlotsTuple>
        BOOST_LEAF_CONSTEXPR static E const * peek( SlotsTuple const &, error_id const & ) noexcept
        {
            return 0;
        }
        
        template <class SlotsTuple>
        BOOST_LEAF_CONSTEXPR static E * peek( SlotsTuple &, error_id const & ) noexcept
        {
            return 0;
        }
    };

    template <class E>
    struct peek_tuple<E, false>
    {
        template <class SlotsTuple>
        BOOST_LEAF_CONSTEXPR static E const * peek( SlotsTuple const & tup, error_id const & err ) noexcept
        {
            return std::get<tuple_type_index<slot<E>,SlotsTuple>::value>(tup).has_value(err.value());
        }

        template <class SlotsTuple>
        BOOST_LEAF_CONSTEXPR static E * peek( SlotsTuple & tup, error_id const & err ) noexcept
        {
            return std::get<tuple_type_index<slot<E>,SlotsTuple>::value>(tup).has_value(err.value());
        }
    };

    template <class E, class SlotsTuple>
    BOOST_LEAF_CONSTEXPR inline
    E const *
    peek( SlotsTuple const & tup, error_info const & ei ) noexcept
    {
        if( error_id err = ei.error() )
            if( E const * e = peek_tuple<E>::peek(tup, err) )
                return e;
#ifndef BOOST_LEAF_NO_EXCEPTIONS
            else
                return peek_exception<E const>::peek(ei);
#endif
        return 0;
    }

    template <class E, class SlotsTuple>
    BOOST_LEAF_CONSTEXPR inline
    E *
    peek( SlotsTuple & tup, error_info const & ei ) noexcept
    {
        if( error_id err = ei.error() )
            if( E * e = peek_tuple<E>::peek(tup, err) )
                return e;
#ifndef BOOST_LEAF_NO_EXCEPTIONS
            else
                return peek_exception<E>::peek(ei);
#endif
        return 0;
    }
}

////////////////////////////////////////

namespace leaf_detail
{
    template <class A>
    template <class Tup>
    BOOST_LEAF_CONSTEXPR inline
    typename handler_argument_traits_defaults<A, false>::error_type const *
    handler_argument_traits_defaults<A, false>::
    check( Tup const & tup, error_info const & ei ) noexcept
    {
        return peek<typename std::decay<A>::type>(tup, ei);
    }

    template <class A>
    template <class Tup>
    BOOST_LEAF_CONSTEXPR inline
    typename handler_argument_traits_defaults<A, false>::error_type *
    handler_argument_traits_defaults<A, false>::
    check( Tup & tup, error_info const & ei ) noexcept
    {
        return peek<typename std::decay<A>::type>(tup, ei);
    }

    template <class Tup>
    BOOST_LEAF_CONSTEXPR inline
    std::exception const *
    handler_argument_traits<void>::
    check( Tup const &, error_info const & ei ) noexcept
    {
        return ei.exception();
    }

    template <class Tup, class... List>
    struct check_arguments;

    template <class Tup>
    struct check_arguments<Tup>
    {
        BOOST_LEAF_CONSTEXPR static bool check( Tup const &, error_info const & )
        {
            return true;
        }
    };

    template <class Tup, class Car, class... Cdr>
    struct check_arguments<Tup, Car, Cdr...>
    {
        BOOST_LEAF_CONSTEXPR static bool check( Tup & tup, error_info const & ei ) noexcept
        {
            return handler_argument_traits<Car>::check(tup, ei) && check_arguments<Tup, Cdr...>::check(tup, ei);
        }
    };
}

////////////////////////////////////////

namespace leaf_detail
{
    template <class>
    struct handler_matches_any_error: std::false_type
    {
    };

    template <template<class...> class L>
    struct handler_matches_any_error<L<>>: std::true_type
    {
    };

    template <template<class...> class L, class Car, class... Cdr>
    struct handler_matches_any_error<L<Car, Cdr...>>
    {
        constexpr static bool value = handler_argument_traits<Car>::always_available && handler_matches_any_error<L<Cdr...>>::value;
    };
}

////////////////////////////////////////

namespace leaf_detail
{
    template <class Tup, class... A>
    BOOST_LEAF_CONSTEXPR inline bool check_handler_( Tup & tup, error_info const & ei, leaf_detail_mp11::mp_list<A...> ) noexcept
    {
        return check_arguments<Tup, A...>::check(tup, ei);
    }

    template <class R, class F, bool IsResult = is_result_type<R>::value, class FReturnType = fn_return_type<F>>
    struct handler_caller
    {
        template <class Tup, class... A>
        BOOST_LEAF_CONSTEXPR static R call( Tup & tup, error_info const & ei, F && f, leaf_detail_mp11::mp_list<A...> )
        {
            return std::forward<F>(f)( handler_argument_traits<A>::get(tup, ei)... );
        }
    };

    template <template <class...> class Result, class... E, class F>
    struct handler_caller<Result<void, E...>, F, true, void>
    {
        using R = Result<void, E...>;

        template <class Tup, class... A>
        BOOST_LEAF_CONSTEXPR static R call( Tup & tup, error_info const & ei, F && f, leaf_detail_mp11::mp_list<A...> )
        {
            std::forward<F>(f)( handler_argument_traits<A>::get(tup, ei)... );
            return { };
        }
    };

    template <class T>
    struct is_tuple: std::false_type { };

    template <class... T>
    struct is_tuple<std::tuple<T...>>: std::true_type { };

    template <class... T>
    struct is_tuple<std::tuple<T...> &>: std::true_type { };

    template <class R, class Tup, class H>
    BOOST_LEAF_CONSTEXPR inline
    typename std::enable_if<!is_tuple<typename std::decay<H>::type>::value, R>::type
    handle_error_( Tup & tup, error_info const & ei, H && h )
    {
        static_assert( handler_matches_any_error<fn_mp_args<H>>::value, "The last handler passed to handle_all must match any error." );
        return handler_caller<R, H>::call( tup, ei, std::forward<H>(h), fn_mp_args<H>{ } );
    }

    template <class R, class Tup, class Car, class... Cdr>
    BOOST_LEAF_CONSTEXPR inline
    typename std::enable_if<!is_tuple<typename std::decay<Car>::type>::value, R>::type
    handle_error_( Tup & tup, error_info const & ei, Car && car, Cdr && ... cdr )
    {
        if( handler_matches_any_error<fn_mp_args<Car>>::value || check_handler_( tup, ei, fn_mp_args<Car>{ } ) )
            return handler_caller<R, Car>::call( tup, ei, std::forward<Car>(car), fn_mp_args<Car>{ } );
        else
            return handle_error_<R>( tup, ei, std::forward<Cdr>(cdr)...);
    }

    template <class R, class Tup, class HTup, size_t ... I>
    BOOST_LEAF_CONSTEXPR inline
    R
    handle_error_tuple_( Tup & tup, error_info const & ei, leaf_detail_mp11::index_sequence<I...>, HTup && htup )
    {
        return handle_error_<R>(tup, ei, std::get<I>(std::forward<HTup>(htup))...);
    }

    template <class R, class Tup, class HTup, class... Cdr, size_t ... I>
    BOOST_LEAF_CONSTEXPR inline
    R
    handle_error_tuple_( Tup & tup, error_info const & ei, leaf_detail_mp11::index_sequence<I...>, HTup && htup, Cdr && ... cdr )
    {
        return handle_error_<R>(tup, ei, std::get<I>(std::forward<HTup>(htup))..., std::forward<Cdr>(cdr)...);
    }

    template <class R, class Tup, class H>
    BOOST_LEAF_CONSTEXPR inline
    typename std::enable_if<is_tuple<typename std::decay<H>::type>::value, R>::type
    handle_error_( Tup & tup, error_info const & ei, H && h )
    {
        return handle_error_tuple_<R>(
            tup,
            ei,
            leaf_detail_mp11::make_index_sequence<std::tuple_size<typename std::decay<H>::type>::value>(),
            std::forward<H>(h));
    }

    template <class R, class Tup, class Car, class... Cdr>
    BOOST_LEAF_CONSTEXPR inline
    typename std::enable_if<is_tuple<typename std::decay<Car>::type>::value, R>::type
    handle_error_( Tup & tup, error_info const & ei, Car && car, Cdr && ... cdr )
    {
        return handle_error_tuple_<R>(
            tup,
            ei,
            leaf_detail_mp11::make_index_sequence<std::tuple_size<typename std::decay<Car>::type>::value>(),
            std::forward<Car>(car),
            std::forward<Cdr>(cdr)...);
    }
}

////////////////////////////////////////

template <class... E>
template <class R, class... H>
BOOST_LEAF_CONSTEXPR BOOST_LEAF_ALWAYS_INLINE
R
context<E...>::
handle_error( error_id id, H && ... h ) const
{
    BOOST_LEAF_ASSERT(!is_active());
    return leaf_detail::handle_error_<R>(tup(), error_info(id), std::forward<H>(h)...);
}

template <class... E>
template <class R, class... H>
BOOST_LEAF_CONSTEXPR BOOST_LEAF_ALWAYS_INLINE
R
context<E...>::
handle_error( error_id id, H && ... h )
{
    BOOST_LEAF_ASSERT(!is_active());
    return leaf_detail::handle_error_<R>(tup(), error_info(id), std::forward<H>(h)...);
}

////////////////////////////////////////

#ifdef BOOST_LEAF_NO_EXCEPTIONS

template <class TryBlock, class... H>
BOOST_LEAF_CONSTEXPR inline
typename std::decay<decltype(std::declval<TryBlock>()().value())>::type
try_handle_all( TryBlock && try_block, H && ... h ) noexcept
{
    static_assert(is_result_type<decltype(std::declval<TryBlock>()())>::value, "The return type of the try_block passed to a try_handle_all function must be registered with leaf::is_result_type");
    context_type_from_handlers<H...> ctx;
    auto active_context = activate_context(ctx);
    if( auto r = std::forward<TryBlock>(try_block)() )
        return std::move(r).value();
    else
    {
        error_id id = r.error();
        ctx.deactivate();
        using R = typename std::decay<decltype(std::declval<TryBlock>()().value())>::type;
        return ctx.template handle_error<R>(id, std::forward<H>(h)...);
    }
}

template <class TryBlock, class... H>
BOOST_LEAF_NODISCARD BOOST_LEAF_CONSTEXPR inline
typename std::decay<decltype(std::declval<TryBlock>()())>::type
try_handle_some( TryBlock && try_block, H && ... h ) noexcept
{
    static_assert(is_result_type<decltype(std::declval<TryBlock>()())>::value, "The return type of the try_block passed to a try_handle_some function must be registered with leaf::is_result_type");
    context_type_from_handlers<H...> ctx;
    auto active_context = activate_context(ctx);
    if( auto r = std::forward<TryBlock>(try_block)() )
        return r;
    else
    {
        error_id id = r.error();
        ctx.deactivate();
        using R = typename std::decay<decltype(std::declval<TryBlock>()())>::type;
        auto rr = ctx.template handle_error<R>(id, std::forward<H>(h)..., [&r]()->R { return std::move(r); });
        if( !rr )
            ctx.propagate(id);
        return rr;
    }
}

template <class TryBlock, class... H>
BOOST_LEAF_CONSTEXPR inline
decltype(std::declval<TryBlock>()())
try_catch( TryBlock && try_block, H && ... ) noexcept
{
    static_assert(sizeof(context_type_from_handlers<H...>) > 0,
        "When exceptions are disabled, try_catch can't fail and has no use for the handlers, but this ensures that the supplied H... types are compatible.");
    return std::forward<TryBlock>(try_block)();
}

#else

namespace leaf_detail
{
    template <class Ctx, class TryBlock, class... H>
    decltype(std::declval<TryBlock>()())
    try_catch_( Ctx & ctx, TryBlock && try_block, H && ... h )
    {
        using namespace leaf_detail;
        BOOST_LEAF_ASSERT(ctx.is_active());
        using R = decltype(std::declval<TryBlock>()());
        try
        {
            return std::forward<TryBlock>(try_block)();
        }
        catch( capturing_exception const & cap )
        {
            try
            {
                cap.unload_and_rethrow_original_exception();
            }
            catch( std::exception & ex )
            {
                ctx.deactivate();
                error_info e(&ex);
                return handle_error_<R>(ctx.tup(), e, std::forward<H>(h)...,
                    [&]() -> R
                    {
                        ctx.propagate(e.error());
                        throw;
                    } );
            }
            catch(...)
            {
                ctx.deactivate();
                error_info e(nullptr);
                return handle_error_<R>(ctx.tup(), e, std::forward<H>(h)...,
                    [&]() -> R
                    {
                        ctx.propagate(e.error());
                        throw;
                    } );
            }
        }
        catch( std::exception & ex )
        {
            ctx.deactivate();
            error_info e(&ex);
            return handle_error_<R>(ctx.tup(), e, std::forward<H>(h)...,
                [&]() -> R
                {
                    ctx.propagate(e.error());
                    throw;
                } );
        }
        catch(...)
        {
            ctx.deactivate();
            error_info e(nullptr);
            return handle_error_<R>(ctx.tup(), e, std::forward<H>(h)...,
                [&]() -> R
                {
                    ctx.propagate(e.error());
                    throw;
                } );
        }
    }
}

template <class TryBlock, class... H>
BOOST_LEAF_CONSTEXPR inline
typename std::decay<decltype(std::declval<TryBlock>()().value())>::type
try_handle_all( TryBlock && try_block, H && ... h )
{
    static_assert(is_result_type<decltype(std::declval<TryBlock>()())>::value, "The return type of the try_block passed to a try_handle_all function must be registered with leaf::is_result_type");
    context_type_from_handlers<H...> ctx;
    auto active_context = activate_context(ctx);
    if( auto r = leaf_detail::try_catch_(
            ctx,
            [&]
            {
                return std::forward<TryBlock>(try_block)();
            },
            std::forward<H>(h)...) )
        return std::move(r).value();
    else
    {
        error_id id = r.error();
        if( ctx.is_active() )
            ctx.deactivate();
        using R = typename std::decay<decltype(std::declval<TryBlock>()().value())>::type;
        return ctx.template handle_error<R>(std::move(id), std::forward<H>(h)...);
    }
}

template <class TryBlock, class... H>
BOOST_LEAF_NODISCARD BOOST_LEAF_CONSTEXPR inline
typename std::decay<decltype(std::declval<TryBlock>()())>::type
try_handle_some( TryBlock && try_block, H && ... h )
{
    static_assert(is_result_type<decltype(std::declval<TryBlock>()())>::value, "The return type of the try_block passed to a try_handle_some function must be registered with leaf::is_result_type");
    context_type_from_handlers<H...> ctx;
    auto active_context = activate_context(ctx);
    if( auto r = leaf_detail::try_catch_(
            ctx,
            [&]
            {
                return std::forward<TryBlock>(try_block)();
            },
            std::forward<H>(h)...) )
        return r;
    else
    {
        error_id id = r.error();
        if( ctx.is_active() )
            ctx.deactivate();
        using R = typename std::decay<decltype(std::declval<TryBlock>()())>::type;
        auto rr = ctx.template handle_error<R>(id, std::forward<H>(h)..., [&r]()->R { return std::move(r); });
        if( !rr )
            ctx.propagate(id);
        return rr;
    }
}

template <class TryBlock, class... H>
BOOST_LEAF_CONSTEXPR inline
decltype(std::declval<TryBlock>()())
try_catch( TryBlock && try_block, H && ... h )
{
    context_type_from_handlers<H...> ctx;
    auto active_context = activate_context(ctx);
    return leaf_detail::try_catch_(
        ctx,
        [&]
        {
            return std::forward<TryBlock>(try_block)();
        },
        std::forward<H>(h)...);
}

#endif

} }

// Boost Exception Integration

namespace boost { class exception; }
namespace boost { template <class Tag,class T> class error_info; }
namespace boost { namespace exception_detail { template <class ErrorInfo> struct get_info; } }

namespace boost { namespace leaf {

namespace leaf_detail
{
    template <class T>
    struct match_enum_type;

    template <class Tag, class T>
    struct match_enum_type<boost::error_info<Tag, T>>
    {
        using type = T;
    };

    template <class Ex>
    BOOST_LEAF_CONSTEXPR inline Ex * get_exception( error_info const & ei )
    {
        return dynamic_cast<Ex *>(ei.exception());
    }

    template <class, class T>
    struct dependent_type { using type = T; };

    template <class Dep, class T>
    using dependent_type_t = typename dependent_type<Dep, T>::type;

    template <class Tag, class T>
    struct handler_argument_traits<boost::error_info<Tag, T>>
    {
        using error_type = void;
        constexpr static bool always_available = false;

        template <class Tup>
        BOOST_LEAF_CONSTEXPR static T * check( Tup & tup, error_info const & ei ) noexcept
        {
            using boost_exception = dependent_type_t<T, boost::exception>;
            if( auto * be = get_exception<boost_exception>(ei) )
                return exception_detail::get_info<boost::error_info<Tag, T>>::get(*be);
            else
                return 0;
        }

        template <class Tup>
        BOOST_LEAF_CONSTEXPR static boost::error_info<Tag, T> get( Tup const & tup, error_info const & ei ) noexcept
        {
            return boost::error_info<Tag, T>(*check(tup, ei));
        }
    };

    template <class Tag, class T> struct handler_argument_traits<boost::error_info<Tag, T> const &>: handler_argument_traits_require_by_value<boost::error_info<Tag, T>> { };
    template <class Tag, class T> struct handler_argument_traits<boost::error_info<Tag, T> const *>: handler_argument_traits_require_by_value<boost::error_info<Tag, T>> { };
    template <class Tag, class T> struct handler_argument_traits<boost::error_info<Tag, T> &>: handler_argument_traits_require_by_value<boost::error_info<Tag, T>> { };
    template <class Tag, class T> struct handler_argument_traits<boost::error_info<Tag, T> *>: handler_argument_traits_require_by_value<boost::error_info<Tag, T>> { };
}

} }

#endif

/* handle_errors.hpp
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
*/