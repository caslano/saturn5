#ifndef BOOST_LEAF_ERROR_HPP_INCLUDED
#define BOOST_LEAF_ERROR_HPP_INCLUDED

// Copyright 2018-2022 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/leaf/config.hpp>
#include <boost/leaf/detail/optional.hpp>
#include <boost/leaf/detail/demangle.hpp>
#include <boost/leaf/detail/function_traits.hpp>
#include <boost/leaf/detail/print.hpp>

#include <type_traits>
#include <iosfwd>

#if BOOST_LEAF_CFG_DIAGNOSTICS
#   include <sstream>
#   include <string>
#   include <set>
#endif

#if BOOST_LEAF_CFG_STD_SYSTEM_ERROR
#   include <system_error>
#endif

#if BOOST_LEAF_CFG_CAPTURE
#   include <memory>
#endif

#define BOOST_LEAF_TOKEN_PASTE(x, y) x ## y
#define BOOST_LEAF_TOKEN_PASTE2(x, y) BOOST_LEAF_TOKEN_PASTE(x, y)
#define BOOST_LEAF_TMP BOOST_LEAF_TOKEN_PASTE2(boost_leaf_tmp_, __LINE__)

#define BOOST_LEAF_ASSIGN(v,r)\
    auto && BOOST_LEAF_TMP = r;\
    static_assert(::boost::leaf::is_result_type<typename std::decay<decltype(BOOST_LEAF_TMP)>::type>::value,\
        "BOOST_LEAF_ASSIGN/BOOST_LEAF_AUTO requires a result object as the second argument (see is_result_type)");\
    if( !BOOST_LEAF_TMP )\
        return BOOST_LEAF_TMP.error();\
    v = std::forward<decltype(BOOST_LEAF_TMP)>(BOOST_LEAF_TMP).value()

#define BOOST_LEAF_AUTO(v, r)\
    BOOST_LEAF_ASSIGN(auto v, r)

#if BOOST_LEAF_CFG_GNUC_STMTEXPR

#define BOOST_LEAF_CHECK(r)\
    ({\
        auto && BOOST_LEAF_TMP = (r);\
        static_assert(::boost::leaf::is_result_type<typename std::decay<decltype(BOOST_LEAF_TMP)>::type>::value,\
            "BOOST_LEAF_CHECK requires a result object (see is_result_type)");\
        if( !BOOST_LEAF_TMP )\
            return BOOST_LEAF_TMP.error();\
        std::move(BOOST_LEAF_TMP);\
    }).value()

#else

#define BOOST_LEAF_CHECK(r)\
    {\
        auto && BOOST_LEAF_TMP = (r);\
        static_assert(::boost::leaf::is_result_type<typename std::decay<decltype(BOOST_LEAF_TMP)>::type>::value,\
            "BOOST_LEAF_CHECK requires a result object (see is_result_type)");\
        if( !BOOST_LEAF_TMP )\
            return BOOST_LEAF_TMP.error();\
    }

#endif

#define BOOST_LEAF_NEW_ERROR ::boost::leaf::leaf_detail::inject_loc{__FILE__,__LINE__,__FUNCTION__}+::boost::leaf::new_error

namespace boost { namespace leaf {

class error_id;

namespace leaf_detail
{
    struct BOOST_LEAF_SYMBOL_VISIBLE tls_tag_unexpected_enabled_counter;
    struct BOOST_LEAF_SYMBOL_VISIBLE tls_tag_id_factory_current_id;

    struct inject_loc
    {
        char const * const file;
        int const line;
        char const * const fn;

        template <class T>
        friend T operator+( inject_loc loc, T && x ) noexcept
        {
            x.load_source_location_(loc.file, loc.line, loc.fn);
            return std::move(x);
        }
    };
}

} }

////////////////////////////////////////

#ifdef BOOST_LEAF_NO_EXCEPTIONS

namespace boost
{
BOOST_LEAF_NORETURN void throw_exception( std::exception const & ); // user defined
}

namespace boost { namespace leaf {

template <class T>
BOOST_LEAF_NORETURN void throw_exception( T const & e )
{
    ::boost::throw_exception(e);
}

} }

#else

namespace boost { namespace leaf {

template <class T>
BOOST_LEAF_NORETURN void throw_exception( T const & e )
{
    throw e;
}

} }

#endif

////////////////////////////////////////

namespace boost { namespace leaf {

#if BOOST_LEAF_CFG_DIAGNOSTICS

namespace leaf_detail
{
    class BOOST_LEAF_SYMBOL_VISIBLE e_unexpected_count
    {
    public:

        char const * (*first_type)();
        int count;

        BOOST_LEAF_CONSTEXPR explicit e_unexpected_count(char const * (*first_type)()) noexcept:
            first_type(first_type),
            count(1)
        {
        }

        template <class CharT, class Traits>
        void print( std::basic_ostream<CharT, Traits> & os ) const
        {
            BOOST_LEAF_ASSERT(first_type != 0);
            BOOST_LEAF_ASSERT(count>0);
            os << "Detected ";
            if( count==1 )
                os << "1 attempt to communicate an unexpected error object";
            else
                os << count << " attempts to communicate unexpected error objects, the first one";
            (os << " of type " << first_type() << '\n').flush();
        }
    };

    template <>
    struct diagnostic<e_unexpected_count, false, false>
    {
        static constexpr bool is_invisible = true;

        template <class CharT, class Traits>
        BOOST_LEAF_CONSTEXPR static void print( std::basic_ostream<CharT, Traits> &, e_unexpected_count const &) noexcept { }
    };

    class BOOST_LEAF_SYMBOL_VISIBLE e_unexpected_info
    {
        std::string s_;
        std::set<char const *(*)()> already_;

    public:

        e_unexpected_info() noexcept
        {
        }

        template <class E>
        void add(E && e)
        {
            if( !diagnostic<E>::is_invisible && already_.insert(&type<E>).second  )
            {
                std::stringstream s;
                diagnostic<E>::print(s,e);
                (s << '\n').flush();
                s_ += s.str();
            }
        }

        template <class CharT, class Traits>
        void print( std::basic_ostream<CharT, Traits> & os ) const
        {
            os << "Unhandled error objects:\n" << s_;
        }
    };

    template <>
    struct diagnostic<e_unexpected_info, false, false>
    {
        static constexpr bool is_invisible = true;

        template <class CharT, class Traits>
        BOOST_LEAF_CONSTEXPR static void print( std::basic_ostream<CharT, Traits> &, e_unexpected_info const &) noexcept { }
    };

}

#endif

} }

////////////////////////////////////////

namespace boost { namespace leaf {

struct BOOST_LEAF_SYMBOL_VISIBLE e_source_location
{
    char const * file;
    int line;
    char const * function;

    template <class CharT, class Traits>
    friend std::basic_ostream<CharT, Traits> & operator<<( std::basic_ostream<CharT, Traits> & os, e_source_location const & x )
    {
        return os << leaf::type<e_source_location>() << ": " << x.file << '(' << x.line << ") in function " << x.function;
    }
};

////////////////////////////////////////

namespace leaf_detail
{
    template <class E>
    class BOOST_LEAF_SYMBOL_VISIBLE slot:
        optional<E>
    {
        slot( slot const & ) = delete;
        slot & operator=( slot const & ) = delete;

        using impl = optional<E>;
        slot<E> * prev_;

    public:

        BOOST_LEAF_CONSTEXPR slot() noexcept:
            prev_(0)
        {
        }

        BOOST_LEAF_CONSTEXPR slot( slot && x ) noexcept:
            optional<E>(std::move(x)),
            prev_(0)
        {
            BOOST_LEAF_ASSERT(x.prev_==0);
        }

        BOOST_LEAF_CONSTEXPR void activate() noexcept
        {
            prev_ = tls::read_ptr<slot<E>>();
            tls::write_ptr<slot<E>>(this);
        }

        BOOST_LEAF_CONSTEXPR void deactivate() noexcept
        {
            tls::write_ptr<slot<E>>(prev_);
        }

        BOOST_LEAF_CONSTEXPR void propagate( int err_id ) noexcept;

        template <class CharT, class Traits>
        void print( std::basic_ostream<CharT, Traits> & os, int key_to_print ) const
        {
#if BOOST_LEAF_CFG_DIAGNOSTICS
            if( !diagnostic<E>::is_invisible )
                if( int k = this->key() )
                {
                    if( key_to_print )
                    {
                        if( key_to_print!=k )
                            return;
                    }
                    else
                        os << '[' << k << ']';
                    diagnostic<E>::print(os, value(k));
                    (os << '\n').flush();
                }
#endif
        }

        using impl::put;
        using impl::has_value;
        using impl::value;
    };

#if BOOST_LEAF_CFG_DIAGNOSTICS

    template <class E>
    BOOST_LEAF_CONSTEXPR inline void load_unexpected_count( int err_id ) noexcept
    {
        if( slot<e_unexpected_count> * sl = tls::read_ptr<slot<e_unexpected_count>>() )
            if( e_unexpected_count * unx = sl->has_value(err_id) )
                ++unx->count;
            else
                sl->put(err_id, e_unexpected_count(&type<E>));
    }

    template <class E>
    BOOST_LEAF_CONSTEXPR inline void load_unexpected_info( int err_id, E && e ) noexcept
    {
        if( slot<e_unexpected_info> * sl = tls::read_ptr<slot<e_unexpected_info>>() )
            if( e_unexpected_info * unx = sl->has_value(err_id) )
                unx->add(std::forward<E>(e));
            else
                sl->put(err_id, e_unexpected_info()).add(std::forward<E>(e));
    }

    template <class E>
    BOOST_LEAF_CONSTEXPR inline void load_unexpected( int err_id, E && e  ) noexcept
    {
        load_unexpected_count<E>(err_id);
        load_unexpected_info(err_id, std::forward<E>(e));
    }

#endif

    template <class E>
    BOOST_LEAF_CONSTEXPR inline void slot<E>::propagate( int err_id ) noexcept
    {
        if( this->key()!=err_id && err_id!=0 )
            return;
        if( impl * p = tls::read_ptr<slot<E>>() )
            *p = std::move(*this);
#if BOOST_LEAF_CFG_DIAGNOSTICS
        else
        {
            int c = tls::read_uint32<tls_tag_unexpected_enabled_counter>();
            BOOST_LEAF_ASSERT(c>=0);
            if( c )
                load_unexpected(err_id, std::move(*this).value(err_id));
        }
#endif
    }

    template <class E>
    BOOST_LEAF_CONSTEXPR inline int load_slot( int err_id, E && e ) noexcept
    {
        static_assert(!std::is_pointer<E>::value, "Error objects of pointer types are not allowed");
        static_assert(!std::is_same<typename std::decay<E>::type, error_id>::value, "Error objects of type error_id are not allowed");
        using T = typename std::decay<E>::type;
        BOOST_LEAF_ASSERT((err_id&3)==1);
        if( slot<T> * p = tls::read_ptr<slot<T>>() )
            (void) p->put(err_id, std::forward<E>(e));
#if BOOST_LEAF_CFG_DIAGNOSTICS
        else
        {
            int c = tls::read_uint32<tls_tag_unexpected_enabled_counter>();
            BOOST_LEAF_ASSERT(c>=0);
            if( c )
                load_unexpected(err_id, std::forward<E>(e));
        }
#endif
        return 0;
    }

    template <class F>
    BOOST_LEAF_CONSTEXPR inline int accumulate_slot( int err_id, F && f ) noexcept
    {
        static_assert(function_traits<F>::arity==1, "Lambdas passed to accumulate must take a single e-type argument by reference");
        using E = typename std::decay<fn_arg_type<F,0>>::type;
        static_assert(!std::is_pointer<E>::value, "Error objects of pointer types are not allowed");
        BOOST_LEAF_ASSERT((err_id&3)==1);
        if( auto sl = tls::read_ptr<slot<E>>() )
            if( auto v = sl->has_value(err_id) )
                (void) std::forward<F>(f)(*v);
            else
                (void) std::forward<F>(f)(sl->put(err_id,E()));
        return 0;
    }
}

////////////////////////////////////////

namespace leaf_detail
{
    template <class=void>
    struct BOOST_LEAF_SYMBOL_VISIBLE id_factory
    {
        static atomic_unsigned_int counter;

        BOOST_LEAF_CONSTEXPR static unsigned generate_next_id() noexcept
        {
            auto id = (counter+=4);
            BOOST_LEAF_ASSERT((id&3)==1);
            return id;
        }
    };

    template <class T>
    atomic_unsigned_int id_factory<T>::counter(-3);

    inline int current_id() noexcept
    {
        auto id = tls::read_uint32<tls_tag_id_factory_current_id>();
        BOOST_LEAF_ASSERT(id==0 || (id&3)==1);
        return id;
    }

    inline int new_id() noexcept
    {
        auto id = id_factory<>::generate_next_id();
        tls::write_uint32<tls_tag_id_factory_current_id>(id);
        return id;
    }
}

////////////////////////////////////////

namespace leaf_detail
{
    template <class T, int Arity = function_traits<T>::arity>
    struct load_item
    {
        static_assert(Arity==0 || Arity==1, "If a functions is passed to new_error or load, it must take zero or one argument");
    };

    template <class E>
    struct load_item<E, -1>
    {
        BOOST_LEAF_CONSTEXPR static int load( int err_id, E && e ) noexcept
        {
            return load_slot(err_id, std::forward<E>(e));
        }
    };

    template <class F>
    struct load_item<F, 0>
    {
        BOOST_LEAF_CONSTEXPR static int load( int err_id, F && f ) noexcept
        {
            return load_slot(err_id, std::forward<F>(f)());
        }
    };

    template <class F>
    struct load_item<F, 1>
    {
        BOOST_LEAF_CONSTEXPR static int load( int err_id, F && f ) noexcept
        {
            return accumulate_slot(err_id, std::forward<F>(f));
        }
    };
}

////////////////////////////////////////

#if BOOST_LEAF_CFG_STD_SYSTEM_ERROR
namespace leaf_detail
{
    class leaf_category final: public std::error_category
    {
        bool equivalent( int,  std::error_condition const & ) const noexcept final override { return false; }
        bool equivalent( std::error_code const &, int ) const noexcept final override { return false; }
        char const * name() const noexcept final override { return "LEAF error"; }
        std::string message( int condition ) const final override { return name(); }
    public:
        ~leaf_category() noexcept final override { }
    };

    template <class=void>
    struct get_error_category
    {
        static leaf_category cat;
    };

    template <class T>
    leaf_category get_error_category<T>::cat;

    inline int import_error_code( std::error_code const & ec ) noexcept
    {
        if( int err_id = ec.value() )
        {
            std::error_category const & cat = get_error_category<>::cat;
            if( &ec.category()==&cat )
            {
                BOOST_LEAF_ASSERT((err_id&3)==1);
                return (err_id&~3)|1;
            }
            else
            {
                err_id = new_id();
                (void) load_slot(err_id, ec);
                return (err_id&~3)|1;
            }
        }
        else
            return 0;
    }
}

inline bool is_error_id( std::error_code const & ec ) noexcept
{
    bool res = (&ec.category() == &leaf_detail::get_error_category<>::cat);
    BOOST_LEAF_ASSERT(!res || !ec.value() || ((ec.value()&3)==1));
    return res;
}
#endif

////////////////////////////////////////

namespace leaf_detail
{
    BOOST_LEAF_CONSTEXPR error_id make_error_id(int) noexcept;
}

class BOOST_LEAF_SYMBOL_VISIBLE error_id
{
    friend error_id BOOST_LEAF_CONSTEXPR leaf_detail::make_error_id(int) noexcept;

    int value_;

    BOOST_LEAF_CONSTEXPR explicit error_id( int value ) noexcept:
        value_(value)
    {
        BOOST_LEAF_ASSERT(value_==0 || ((value_&3)==1));
    }

public:

    BOOST_LEAF_CONSTEXPR error_id() noexcept:
        value_(0)
    {
    }

#if BOOST_LEAF_CFG_STD_SYSTEM_ERROR
    error_id( std::error_code const & ec ) noexcept:
        value_(leaf_detail::import_error_code(ec))
    {
        BOOST_LEAF_ASSERT(!value_ || ((value_&3)==1));
    }

    template <class Enum>
    error_id( Enum e, typename std::enable_if<std::is_error_code_enum<Enum>::value, Enum>::type * = 0 ) noexcept:
        value_(leaf_detail::import_error_code(e))
    {
    }

    std::error_code to_error_code() const noexcept
    {
        return std::error_code(value_, leaf_detail::get_error_category<>::cat);
    }
#endif

    BOOST_LEAF_CONSTEXPR error_id load() const noexcept
    {
        return *this;
    }

    template <class... Item>
    BOOST_LEAF_CONSTEXPR error_id load( Item && ... item ) const noexcept
    {
        if( int err_id = value() )
        {
            int const unused[ ] = { 42, leaf_detail::load_item<Item>::load(err_id, std::forward<Item>(item))... };
            (void) unused;
        }
        return *this;
    }

    BOOST_LEAF_CONSTEXPR int value() const noexcept
    {
        if( int v = value_ )
        {
            BOOST_LEAF_ASSERT((v&3)==1);
            return (v&~3)|1;
        }
        else
            return 0;
    }

    BOOST_LEAF_CONSTEXPR explicit operator bool() const noexcept
    {
        return value_ != 0;
    }

    BOOST_LEAF_CONSTEXPR friend bool operator==( error_id a, error_id b ) noexcept
    {
        return a.value_ == b.value_;
    }

    BOOST_LEAF_CONSTEXPR friend bool operator!=( error_id a, error_id b ) noexcept
    {
        return !(a == b);
    }

    BOOST_LEAF_CONSTEXPR friend bool operator<( error_id a, error_id b ) noexcept
    {
        return a.value_ < b.value_;
    }

    template <class CharT, class Traits>
    friend std::basic_ostream<CharT, Traits> & operator<<( std::basic_ostream<CharT, Traits> & os, error_id x )
    {
        return os << x.value_;
    }

    BOOST_LEAF_CONSTEXPR void load_source_location_( char const * file, int line, char const * function ) const noexcept
    {
        BOOST_LEAF_ASSERT(file&&*file);
        BOOST_LEAF_ASSERT(line>0);
        BOOST_LEAF_ASSERT(function&&*function);
        BOOST_LEAF_ASSERT(value_);
        (void) load(e_source_location {file,line,function});
    }
};

namespace leaf_detail
{
    BOOST_LEAF_CONSTEXPR inline error_id make_error_id( int err_id ) noexcept
    {
        BOOST_LEAF_ASSERT(err_id==0 || (err_id&3)==1);
        return error_id((err_id&~3)|1);
    }
}

inline error_id new_error() noexcept
{
    return leaf_detail::make_error_id(leaf_detail::new_id());
}

template <class... Item>
inline error_id new_error( Item && ... item ) noexcept
{
    return leaf_detail::make_error_id(leaf_detail::new_id()).load(std::forward<Item>(item)...);
}

inline error_id current_error() noexcept
{
    return leaf_detail::make_error_id(leaf_detail::current_id());
}

////////////////////////////////////////////

class polymorphic_context
{
protected:

    polymorphic_context() noexcept = default;
    ~polymorphic_context() noexcept = default;

public:

    virtual error_id propagate_captured_errors() noexcept = 0;
    virtual void activate() noexcept = 0;
    virtual void deactivate() noexcept = 0;
    virtual void propagate( error_id ) noexcept = 0;
    virtual bool is_active() const noexcept = 0;
    inline virtual void print( std::ostream & ) const { };
    error_id captured_id_;
};

#if BOOST_LEAF_CFG_CAPTURE
using context_ptr = std::shared_ptr<polymorphic_context>;
#endif

////////////////////////////////////////////

template <class Ctx>
class context_activator
{
    context_activator( context_activator const & ) = delete;
    context_activator & operator=( context_activator const & ) = delete;

#if !defined(BOOST_LEAF_NO_EXCEPTIONS) && BOOST_LEAF_STD_UNCAUGHT_EXCEPTIONS
    int const uncaught_exceptions_;
#endif
    Ctx * ctx_;

public:

    explicit BOOST_LEAF_CONSTEXPR BOOST_LEAF_ALWAYS_INLINE context_activator(Ctx & ctx) noexcept:
#if !defined(BOOST_LEAF_NO_EXCEPTIONS) && BOOST_LEAF_STD_UNCAUGHT_EXCEPTIONS
        uncaught_exceptions_(std::uncaught_exceptions()),
#endif
        ctx_(ctx.is_active() ? 0 : &ctx)
    {
        if( ctx_ )
            ctx_->activate();
    }

    BOOST_LEAF_CONSTEXPR BOOST_LEAF_ALWAYS_INLINE context_activator( context_activator && x ) noexcept:
#if !defined(BOOST_LEAF_NO_EXCEPTIONS) && BOOST_LEAF_STD_UNCAUGHT_EXCEPTIONS
        uncaught_exceptions_(x.uncaught_exceptions_),
#endif
        ctx_(x.ctx_)
    {
        x.ctx_ = 0;
    }

    BOOST_LEAF_ALWAYS_INLINE ~context_activator() noexcept
    {
        if( ctx_ && ctx_->is_active() )
            ctx_->deactivate();
    }
};

template <class Ctx>
BOOST_LEAF_CONSTEXPR BOOST_LEAF_ALWAYS_INLINE context_activator<Ctx> activate_context(Ctx & ctx) noexcept
{
    return context_activator<Ctx>(ctx);
}

////////////////////////////////////////////

template <class R>
struct is_result_type: std::false_type
{
};

template <class R>
struct is_result_type<R const>: is_result_type<R>
{
};

} }

#endif

/* error.hpp
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
*/