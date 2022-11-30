#ifndef BOOST_LEAF_CAPTURE_HPP_INCLUDED
#define BOOST_LEAF_CAPTURE_HPP_INCLUDED

// Copyright 2018-2022 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/leaf/config.hpp>
#include <boost/leaf/exception.hpp>
#include <boost/leaf/on_error.hpp>

#if BOOST_LEAF_CFG_CAPTURE

namespace boost { namespace leaf {

namespace leaf_detail
{
    template <class R, bool IsResult = is_result_type<R>::value>
    struct is_result_tag;

    template <class R>
    struct is_result_tag<R, false>
    {
    };

    template <class R>
    struct is_result_tag<R, true>
    {
    };
}

#ifdef BOOST_LEAF_NO_EXCEPTIONS

namespace leaf_detail
{
    template <class R, class F, class... A>
    inline
    decltype(std::declval<F>()(std::forward<A>(std::declval<A>())...))
    capture_impl(is_result_tag<R, false>, context_ptr && ctx, F && f, A... a) noexcept
    {
        auto active_context = activate_context(*ctx);
        return std::forward<F>(f)(std::forward<A>(a)...);
    }

    template <class R, class F, class... A>
    inline
    decltype(std::declval<F>()(std::forward<A>(std::declval<A>())...))
    capture_impl(is_result_tag<R, true>, context_ptr && ctx, F && f, A... a) noexcept
    {
        auto active_context = activate_context(*ctx);
        if( auto r = std::forward<F>(f)(std::forward<A>(a)...) )
            return r;
        else
        {
            ctx->captured_id_ = r.error();
            return std::move(ctx);
        }
    }

    template <class R, class Future>
    inline
    decltype(std::declval<Future>().get())
    future_get_impl(is_result_tag<R, false>, Future & fut) noexcept
    {
        return fut.get();
    }

    template <class R, class Future>
    inline
    decltype(std::declval<Future>().get())
    future_get_impl(is_result_tag<R, true>, Future & fut) noexcept
    {
        if( auto r = fut.get() )
            return r;
        else
            return error_id(r.error()); // unloads
    }
}

#else

namespace leaf_detail
{
    class capturing_exception:
        public std::exception
    {
        std::exception_ptr ex_;
        context_ptr ctx_;

    public:

        capturing_exception(std::exception_ptr && ex, context_ptr && ctx) noexcept:
            ex_(std::move(ex)),
            ctx_(std::move(ctx))
        {
            BOOST_LEAF_ASSERT(ex_);
            BOOST_LEAF_ASSERT(ctx_);
            BOOST_LEAF_ASSERT(ctx_->captured_id_);
        }

        [[noreturn]] void unload_and_rethrow_original_exception() const
        {
            BOOST_LEAF_ASSERT(ctx_->captured_id_);
            tls::write_uint32<tls_tag_id_factory_current_id>(ctx_->captured_id_.value());
            ctx_->propagate(ctx_->captured_id_);
            std::rethrow_exception(ex_);
        }

        template <class CharT, class Traits>
        void print( std::basic_ostream<CharT, Traits> & os ) const
        {
            ctx_->print(os);
        }
    };

    template <class R, class F, class... A>
    inline
    decltype(std::declval<F>()(std::forward<A>(std::declval<A>())...))
    capture_impl(is_result_tag<R, false>, context_ptr && ctx, F && f, A... a)
    {
        auto active_context = activate_context(*ctx);
        error_monitor cur_err;
        try
        {
            return std::forward<F>(f)(std::forward<A>(a)...);
        }
        catch( capturing_exception const & )
        {
            throw;
        }
        catch( exception_base const & e )
        {
            ctx->captured_id_ = e.get_error_id();
            throw_exception( capturing_exception(std::current_exception(), std::move(ctx)) );
        }
        catch(...)
        {
            ctx->captured_id_ = cur_err.assigned_error_id();
            throw_exception( capturing_exception(std::current_exception(), std::move(ctx)) );
        }
    }

    template <class R, class F, class... A>
    inline
    decltype(std::declval<F>()(std::forward<A>(std::declval<A>())...))
    capture_impl(is_result_tag<R, true>, context_ptr && ctx, F && f, A... a)
    {
        auto active_context = activate_context(*ctx);
        error_monitor cur_err;
        try
        {
            if( auto && r = std::forward<F>(f)(std::forward<A>(a)...) )
                return std::move(r);
            else
            {
                ctx->captured_id_ = r.error();
                return std::move(ctx);
            }
        }
        catch( capturing_exception const & )
        {
            throw;
        }
        catch( exception_base const & e )
        {
            ctx->captured_id_ = e.get_error_id();
            throw_exception( capturing_exception(std::current_exception(), std::move(ctx)) );
        }
        catch(...)
        {
            ctx->captured_id_ = cur_err.assigned_error_id();
            throw_exception( capturing_exception(std::current_exception(), std::move(ctx)) );
        }
    }

    template <class R, class Future>
    inline
    decltype(std::declval<Future>().get())
    future_get_impl(is_result_tag<R, false>, Future & fut )
    {
        try
        {
            return fut.get();
        }
        catch( capturing_exception const & cap )
        {
            cap.unload_and_rethrow_original_exception();
        }
    }

    template <class R, class Future>
    inline
    decltype(std::declval<Future>().get())
    future_get_impl(is_result_tag<R, true>, Future & fut )
    {
        try
        {
            if( auto r = fut.get() )
                return r;
            else
                return error_id(r.error()); // unloads
        }
        catch( capturing_exception const & cap )
        {
            cap.unload_and_rethrow_original_exception();
        }
    }
}

#endif

template <class F, class... A>
inline
decltype(std::declval<F>()(std::forward<A>(std::declval<A>())...))
capture(context_ptr && ctx, F && f, A... a)
{
    using namespace leaf_detail;
    return capture_impl(is_result_tag<decltype(std::declval<F>()(std::forward<A>(std::declval<A>())...))>(), std::move(ctx), std::forward<F>(f), std::forward<A>(a)...);
}

template <class Future>
inline
decltype(std::declval<Future>().get())
future_get( Future & fut )
{
    using namespace leaf_detail;
    return future_get_impl(is_result_tag<decltype(std::declval<Future>().get())>(), fut);
}

} }

#endif

#endif

/* capture.hpp
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
*/