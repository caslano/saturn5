#ifndef BOOST_LEAF_EXCEPTION_HPP_INCLUDED
#define BOOST_LEAF_EXCEPTION_HPP_INCLUDED

// Copyright 2018-2022 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/leaf/config.hpp>
#include <boost/leaf/error.hpp>

#ifndef BOOST_LEAF_NO_EXCEPTIONS

#include <exception>

#define BOOST_LEAF_EXCEPTION ::boost::leaf::leaf_detail::inject_loc{__FILE__,__LINE__,__FUNCTION__}+::boost::leaf::exception
#define BOOST_LEAF_THROW_EXCEPTION ::boost::leaf::leaf_detail::throw_with_loc{__FILE__,__LINE__,__FUNCTION__}+::boost::leaf::exception

////////////////////////////////////////

namespace boost { namespace leaf {

namespace leaf_detail
{
    struct throw_with_loc
    {
        char const * const file;
        int const line;
        char const * const fn;

        template <class Ex>
        [[noreturn]] friend void operator+( throw_with_loc loc, Ex const & ex )
        {
            ex.load_source_location_(loc.file, loc.line, loc.fn);
            ::boost::leaf::throw_exception(ex);
        }
    };
}

} }

////////////////////////////////////////

namespace boost { namespace leaf {

namespace leaf_detail
{
    inline void enforce_std_exception( std::exception const & ) noexcept { }

    class BOOST_LEAF_SYMBOL_VISIBLE exception_base
    {
        std::shared_ptr<void const> auto_id_bump_;
    public:

        virtual error_id get_error_id() const noexcept = 0;

    protected:

        exception_base():
            auto_id_bump_(0, [](void const *) { (void) new_id(); })
        {
        }

        ~exception_base() noexcept { }
    };

    template <class Ex>
    class BOOST_LEAF_SYMBOL_VISIBLE exception:
        public Ex,
        public exception_base,
        public error_id
    {
        error_id get_error_id() const noexcept final override
        {
            return *this;
        }

    public:

        exception( exception const & ) = default;
        exception( exception && ) = default;

        BOOST_LEAF_CONSTEXPR exception( error_id id, Ex const & ex ) noexcept:
            Ex(ex),
            error_id(id)
        {
            enforce_std_exception(*this);
        }

        BOOST_LEAF_CONSTEXPR exception( error_id id, Ex && ex ) noexcept:
            Ex(std::move(ex)),
            error_id(id)
        {
            enforce_std_exception(*this);
        }

        explicit BOOST_LEAF_CONSTEXPR exception( error_id id ) noexcept:
            error_id(id)
        {
            enforce_std_exception(*this);
        }
    };

    template <class... T>
    struct at_least_one_derives_from_std_exception;

    template <>
    struct at_least_one_derives_from_std_exception<>: std::false_type { };

    template <class T, class... Rest>
    struct at_least_one_derives_from_std_exception<T, Rest...>
    {
        constexpr static const bool value = std::is_base_of<std::exception,typename std::remove_reference<T>::type>::value || at_least_one_derives_from_std_exception<Rest...>::value;
    };
}

template <class Ex, class... E>
inline
typename std::enable_if<std::is_base_of<std::exception,typename std::remove_reference<Ex>::type>::value, leaf_detail::exception<typename std::remove_reference<Ex>::type>>::type
exception( error_id err, Ex && ex, E && ... e ) noexcept
{
    static_assert(!leaf_detail::at_least_one_derives_from_std_exception<E...>::value, "Error objects passed to leaf::exception may not derive from std::exception");
    return leaf_detail::exception<typename std::remove_reference<Ex>::type>( err.load(std::forward<E>(e)...), std::forward<Ex>(ex) );
}

template <class E1, class... E>
inline
typename std::enable_if<!std::is_base_of<std::exception,typename std::remove_reference<E1>::type>::value, leaf_detail::exception<std::exception>>::type
exception( error_id err, E1 && car, E && ... cdr ) noexcept
{
    static_assert(!leaf_detail::at_least_one_derives_from_std_exception<E...>::value, "Error objects passed to leaf::exception may not derive from std::exception");
    return leaf_detail::exception<std::exception>( err.load(std::forward<E1>(car), std::forward<E>(cdr)...) );
}

inline leaf_detail::exception<std::exception> exception( error_id err ) noexcept
{
    return leaf_detail::exception<std::exception>(err);
}

template <class Ex, class... E>
inline
typename std::enable_if<std::is_base_of<std::exception,typename std::remove_reference<Ex>::type>::value, leaf_detail::exception<typename std::remove_reference<Ex>::type>>::type
exception( Ex && ex, E && ... e ) noexcept
{
    static_assert(!leaf_detail::at_least_one_derives_from_std_exception<E...>::value, "Error objects passed to leaf::exception may not derive from std::exception");
    return leaf_detail::exception<typename std::remove_reference<Ex>::type>( new_error().load(std::forward<E>(e)...), std::forward<Ex>(ex) );
}

template <class E1, class... E>
inline
typename std::enable_if<!std::is_base_of<std::exception,typename std::remove_reference<E1>::type>::value, leaf_detail::exception<std::exception>>::type
exception( E1 && car, E && ... cdr ) noexcept
{
    static_assert(!leaf_detail::at_least_one_derives_from_std_exception<E...>::value, "Error objects passed to leaf::exception may not derive from std::exception");
    return leaf_detail::exception<std::exception>( new_error().load(std::forward<E1>(car), std::forward<E>(cdr)...) );
}

inline leaf_detail::exception<std::exception> exception() noexcept
{
    return leaf_detail::exception<std::exception>(leaf::new_error());
}

////////////////////////////////////////

#ifndef BOOST_LEAF_NO_EXCEPTIONS

template <class T>
class result;

namespace leaf_detail
{
    inline error_id catch_exceptions_helper( std::exception const & ex, leaf_detail_mp11::mp_list<> )
    {
        return leaf::new_error(std::current_exception());
    }

    template <class Ex1, class... Ex>
    inline error_id catch_exceptions_helper( std::exception const & ex, leaf_detail_mp11::mp_list<Ex1,Ex...> )
    {
        if( Ex1 const * p = dynamic_cast<Ex1 const *>(&ex) )
            return catch_exceptions_helper(ex, leaf_detail_mp11::mp_list<Ex...>{ }).load(*p);
        else
            return catch_exceptions_helper(ex, leaf_detail_mp11::mp_list<Ex...>{ });
    }

    template <class T>
    struct deduce_exception_to_result_return_type_impl
    {
        using type = result<T>;
    };

    template <class T>
    struct deduce_exception_to_result_return_type_impl<result<T>>
    {
        using type = result<T>;
    };

    template <class T>
    using deduce_exception_to_result_return_type = typename deduce_exception_to_result_return_type_impl<T>::type;
}

template <class... Ex, class F>
inline
leaf_detail::deduce_exception_to_result_return_type<leaf_detail::fn_return_type<F>>
exception_to_result( F && f ) noexcept
{
    try
    {
        return std::forward<F>(f)();
    }
    catch( std::exception const & ex )
    {
        return leaf_detail::catch_exceptions_helper(ex, leaf_detail_mp11::mp_list<Ex...>());
    }
    catch(...)
    {
        return leaf::new_error(std::current_exception());
    }
}

#endif

} }

#endif

#endif

/* exception.hpp
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
*/