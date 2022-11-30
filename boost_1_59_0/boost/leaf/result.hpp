#ifndef BOOST_LEAF_RESULT_HPP_INCLUDED
#define BOOST_LEAF_RESULT_HPP_INCLUDED

// Copyright 2018-2022 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/leaf/config.hpp>
#include <boost/leaf/error.hpp>

#include <climits>
#include <functional>

namespace boost { namespace leaf {

class bad_result:
    public std::exception,
    public error_id
{
    char const * what() const noexcept final override
    {
        return "boost::leaf::bad_result";
    }

public:

    explicit bad_result( error_id id ) noexcept:
        error_id(id)
    {
        BOOST_LEAF_ASSERT(value());
    }
};

////////////////////////////////////////

namespace leaf_detail
{
    template <class T>
    struct stored
    {
        using type = T;
        using value_type = T;
        using value_type_const = T const;
        using value_cref = T const &;
        using value_ref = T &;
        using value_rv_cref = T const &&;
        using value_rv_ref = T &&;

        static value_type_const * cptr( type const & v ) noexcept
        {
            return &v;
        }

        static value_type * ptr( type & v ) noexcept
        {
            return &v;
        }
    };

    template <class T>
    struct stored<T &>
    {
        using type = std::reference_wrapper<T>;
        using value_type_const = T;
        using value_type = T;
        using value_ref = T &;
        using value_cref = T &;
        using value_rv_ref = T &;
        using value_rv_cref = T &;

        static value_type_const * cptr( type const & v ) noexcept
        {
            return &v.get();
        }

        static value_type * ptr( type const & v ) noexcept
        {
            return &v.get();
        }
    };

    class result_discriminant
    {
        unsigned state_;

    public:

        enum kind_t
        {
            no_error = 0,
            err_id = 1,
            ctx_ptr = 2,
            val = 3
        };

        explicit result_discriminant( error_id id ) noexcept:
            state_(id.value())
        {
            BOOST_LEAF_ASSERT(state_==0 || (state_&3)==1);
        }

        struct kind_val { };
        explicit result_discriminant( kind_val ) noexcept:
            state_(val)
        {
        }

#if BOOST_LEAF_CFG_CAPTURE
        struct kind_ctx_ptr { };
        explicit result_discriminant( kind_ctx_ptr ) noexcept:
            state_(ctx_ptr)
        {
        }
#endif

        kind_t kind() const noexcept
        {
            return kind_t(state_&3);
        }

        error_id get_error_id() const noexcept
        {
            BOOST_LEAF_ASSERT(kind()==no_error || kind()==err_id);
            return make_error_id(state_);
        }
    };
}

////////////////////////////////////////

template <class T>
class result
{
    template <class U>
    friend class result;

    using result_discriminant = leaf_detail::result_discriminant;

    struct error_result
    {
        error_result( error_result && ) = default;
        error_result( error_result const & ) = delete;
        error_result & operator=( error_result const & ) = delete;

        result & r_;

        error_result( result & r ) noexcept:
            r_(r)
        {
        }

        template <class U>
        operator result<U>() noexcept
        {
            switch(r_.what_.kind())
            {
            case result_discriminant::val:
                return result<U>(error_id());
            case result_discriminant::ctx_ptr:
#if BOOST_LEAF_CFG_CAPTURE
                return result<U>(std::move(r_.ctx_));
#else
                BOOST_LEAF_ASSERT(0); // Possible ODR violation.
#endif
            default:
                return result<U>(std::move(r_.what_));
            }
        }

        operator error_id() noexcept
        {
            switch(r_.what_.kind())
            {
            case result_discriminant::val:
                return error_id();
            case result_discriminant::ctx_ptr:
#if BOOST_LEAF_CFG_CAPTURE
                {
                    error_id captured_id = r_.ctx_->propagate_captured_errors();
                    tls::write_uint32<leaf_detail::tls_tag_id_factory_current_id>(captured_id.value());
                    return captured_id;
                }
#else
                BOOST_LEAF_ASSERT(0); // Possible ODR violation.
#endif
            default:
                return r_.what_.get_error_id();
            }
        }
    };

    using stored_type = typename leaf_detail::stored<T>::type;
    using value_type = typename leaf_detail::stored<T>::value_type;
    using value_type_const = typename leaf_detail::stored<T>::value_type_const;
    using value_ref = typename leaf_detail::stored<T>::value_ref;
    using value_cref = typename leaf_detail::stored<T>::value_cref;
    using value_rv_ref = typename leaf_detail::stored<T>::value_rv_ref;
    using value_rv_cref = typename leaf_detail::stored<T>::value_rv_cref;

    union
    {
        stored_type stored_;
#if BOOST_LEAF_CFG_CAPTURE
        context_ptr ctx_;
#endif
    };

    result_discriminant what_;

    void destroy() const noexcept
    {
        switch(this->what_.kind())
        {
        case result_discriminant::val:
            stored_.~stored_type();
            break;
        case result_discriminant::ctx_ptr:
#if BOOST_LEAF_CFG_CAPTURE
            BOOST_LEAF_ASSERT(!ctx_ || ctx_->captured_id_);
            ctx_.~context_ptr();
#else
            BOOST_LEAF_ASSERT(0); // Possible ODR violation.
#endif
        default:
            break;
        }
    }

    template <class U>
    result_discriminant move_from( result<U> && x ) noexcept
    {
        auto x_what = x.what_;
        switch(x_what.kind())
        {
        case result_discriminant::val:
            (void) new(&stored_) stored_type(std::move(x.stored_));
            break;
        case result_discriminant::ctx_ptr:
#if BOOST_LEAF_CFG_CAPTURE
            BOOST_LEAF_ASSERT(!x.ctx_ || x.ctx_->captured_id_);
            (void) new(&ctx_) context_ptr(std::move(x.ctx_));
#else
            BOOST_LEAF_ASSERT(0); // Possible ODR violation.
#endif
        default:
            break;
        }
        return x_what;
    }

    result( result_discriminant && what ) noexcept:
        what_(std::move(what))
    {
        BOOST_LEAF_ASSERT(what_.kind()==result_discriminant::err_id || what_.kind()==result_discriminant::no_error);
    }

    error_id get_error_id() const noexcept
    {
        BOOST_LEAF_ASSERT(what_.kind()!=result_discriminant::val);
#if BOOST_LEAF_CFG_CAPTURE
        return what_.kind()==result_discriminant::ctx_ptr ? ctx_->captured_id_ : what_.get_error_id();
#else
        BOOST_LEAF_ASSERT(what_.kind()!=result_discriminant::ctx_ptr); // Possible ODR violation.
        return what_.get_error_id();
#endif
    }

    stored_type const * get() const noexcept
    {
        return has_value() ? &stored_ : 0;
    }

    stored_type * get() noexcept
    {
        return has_value() ? &stored_ : 0;
    }

protected:

    void enforce_value_state() const
    {
        if( !has_value() )
            ::boost::leaf::throw_exception(bad_result(get_error_id()));
    }

public:

    result( result && x ) noexcept:
        what_(move_from(std::move(x)))
    {
    }

    template <class U, class = typename std::enable_if<std::is_convertible<U, T>::value>::type>
    result( result<U> && x ) noexcept:
        what_(move_from(std::move(x)))
    {
    }

    result():
        stored_(stored_type()),
        what_(result_discriminant::kind_val{})
    {
    }

    result( value_type && v ) noexcept:
        stored_(std::forward<value_type>(v)),
        what_(result_discriminant::kind_val{})
    {
    }

    result( value_type const & v ):
        stored_(v),
        what_(result_discriminant::kind_val{})
    {
    }

    result( error_id err ) noexcept:
        what_(err)
    {
    }

#if defined(BOOST_STRICT_CONFIG) || !defined(__clang__)

    // This should be the default implementation, but std::is_convertible
    // breaks under COMPILER=/usr/bin/clang++ CXXSTD=11 clang 3.3.
    // On the other hand, the workaround exposes a rather severe bug in
    //__GNUC__ under 11: https://github.com/boostorg/leaf/issues/25.

    // SFINAE: T can be initialized with a U, e.g. result<std::string>("literal").
    template <class U, class = typename std::enable_if<std::is_convertible<U, T>::value>::type>
    result( U && u ):
        stored_(std::forward<U>(u)),
        what_(result_discriminant::kind_val{})
    {
    }

#else

private:
    static int init_T_with_U( T && );
public:

    // SFINAE: T can be initialized with a U, e.g. result<std::string>("literal").
    template <class U>
    result( U && u, decltype(init_T_with_U(std::forward<U>(u))) * = 0 ):
        stored_(std::forward<U>(u)),
        what_(result_discriminant::kind_val{})
    {
    }

#endif

#if BOOST_LEAF_CFG_STD_SYSTEM_ERROR
    result( std::error_code const & ec ) noexcept:
        what_(error_id(ec))
    {
    }

    template <class Enum>
    result( Enum e, typename std::enable_if<std::is_error_code_enum<Enum>::value, int>::type * = 0 ) noexcept:
        what_(error_id(e))
    {
    }
#endif

#if BOOST_LEAF_CFG_CAPTURE
    result( context_ptr && ctx ) noexcept:
        ctx_(std::move(ctx)),
        what_(result_discriminant::kind_ctx_ptr{})
    {
    }
#endif

    ~result() noexcept
    {
        destroy();
    }

    result & operator=( result && x ) noexcept
    {
        destroy();
        what_ = move_from(std::move(x));
        return *this;
    }

    template <class U>
    result & operator=( result<U> && x ) noexcept
    {
        destroy();
        what_ = move_from(std::move(x));
        return *this;
    }

    bool has_value() const noexcept
    {
        return what_.kind() == result_discriminant::val;
    }

    bool has_error() const noexcept
    {
        return !has_value();
    }

    explicit operator bool() const noexcept
    {
        return has_value();
    }

#ifdef BOOST_LEAF_NO_CXX11_REF_QUALIFIERS

    value_cref value() const
    {
        enforce_value_state();
        return stored_;
    }

    value_ref value()
    {
        enforce_value_state();
        return stored_;
    }

#else

    value_cref value() const &
    {
        enforce_value_state();
        return stored_;
    }

    value_ref value() &
    {
        enforce_value_state();
        return stored_;
    }

    value_rv_cref value() const &&
    {
        enforce_value_state();
        return std::move(stored_);
    }

    value_rv_ref value() &&
    {
        enforce_value_state();
        return std::move(stored_);
    }

#endif

    value_type_const * operator->() const noexcept
    {
        return has_value() ? leaf_detail::stored<T>::cptr(stored_) : 0;
    }

    value_type * operator->() noexcept
    {
        return has_value() ? leaf_detail::stored<T>::ptr(stored_) : 0;
    }

#ifdef BOOST_LEAF_NO_CXX11_REF_QUALIFIERS

    value_cref operator*() const noexcept
    {
        auto p = get();
        BOOST_LEAF_ASSERT(p != 0);
        return *p;
    }

    value_ref operator*() noexcept
    {
        auto p = get();
        BOOST_LEAF_ASSERT(p != 0);
        return *p;
    }

#else

    value_cref operator*() const & noexcept
    {
        auto p = get();
        BOOST_LEAF_ASSERT(p != 0);
        return *p;
    }

    value_ref operator*() & noexcept
    {
        auto p = get();
        BOOST_LEAF_ASSERT(p != 0);
        return *p;
    }

    value_rv_cref operator*() const && noexcept
    {
        auto p = get();
        BOOST_LEAF_ASSERT(p != 0);
        return std::move(*p);
    }

    value_rv_ref operator*() && noexcept
    {
        auto p = get();
        BOOST_LEAF_ASSERT(p != 0);
        return std::move(*p);
    }

#endif

    error_result error() noexcept
    {
        return error_result{*this};
    }

    template <class... Item>
    error_id load( Item && ... item ) noexcept
    {
        return error_id(error()).load(std::forward<Item>(item)...);
    }
};

////////////////////////////////////////

namespace leaf_detail
{
    struct void_ { };
}

template <>
class result<void>:
    result<leaf_detail::void_>
{
    using result_discriminant = leaf_detail::result_discriminant;
    using void_ = leaf_detail::void_;
    using base = result<void_>;

    template <class U>
    friend class result;

    result( result_discriminant && what ) noexcept:
        base(std::move(what))
    {
    }

public:

    using value_type = void;

    result( result && x ) noexcept:
        base(std::move(x))
    {
    }

    result() noexcept
    {
    }

    result( error_id err ) noexcept:
        base(err)
    {
    }

#if BOOST_LEAF_CFG_STD_SYSTEM_ERROR
    result( std::error_code const & ec ) noexcept:
        base(ec)
    {
    }

    template <class Enum>
    result( Enum e, typename std::enable_if<std::is_error_code_enum<Enum>::value, Enum>::type * = 0 ) noexcept:
        base(e)
    {
    }
#endif

#if BOOST_LEAF_CFG_CAPTURE
    result( context_ptr && ctx ) noexcept:
        base(std::move(ctx))
    {
    }
#endif

    ~result() noexcept
    {
    }

    void value() const
    {
        base::enforce_value_state();
    }

    void const * operator->() const noexcept
    {
        return base::operator->();
    }

    void * operator->() noexcept
    {
        return base::operator->();
    }

    void operator*() const noexcept
    {
        BOOST_LEAF_ASSERT(has_value());
    }

    using base::operator=;
    using base::operator bool;
    using base::get_error_id;
    using base::error;
    using base::load;
};

////////////////////////////////////////

template <class R>
struct is_result_type;

template <class T>
struct is_result_type<result<T>>: std::true_type
{
};

} }

#endif

/* result.hpp
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
*/