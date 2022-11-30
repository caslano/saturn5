/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   light_function.hpp
 * \author Andrey Semashev
 * \date   20.06.2010
 *
 * \brief  This header is the Boost.Log library impl, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 *
 * The file contains a lightweight alternative of Boost.Function. It does not provide all
 * features of Boost.Function but doesn't introduce dependency on Boost.Bind.
 */

#ifndef BOOST_LOG_DETAIL_LIGHT_FUNCTION_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_LIGHT_FUNCTION_HPP_INCLUDED_

#include <cstddef>
#include <boost/move/core.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/core/explicit_operator_bool.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/type_traits/remove_cv.hpp>
#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#endif
#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#include <boost/log/detail/sfinae_tools.hpp>
#else
#include <boost/type_traits/remove_reference.hpp>
#endif
#if defined(BOOST_NO_CXX11_NULLPTR)
#include <boost/assert.hpp>
#endif
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#ifndef BOOST_LOG_LIGHT_FUNCTION_LIMIT
#define BOOST_LOG_LIGHT_FUNCTION_LIMIT 2
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

template< typename T, typename ThisT >
struct is_cv_same { enum _ { value = false }; };
template< typename T >
struct is_cv_same< T, T > { enum _ { value = true }; };
template< typename T >
struct is_cv_same< T, const T > { enum _ { value = true }; };
template< typename T >
struct is_cv_same< T, volatile T > { enum _ { value = true }; };
template< typename T >
struct is_cv_same< T, const volatile T > { enum _ { value = true }; };

template< typename T, typename ThisT >
struct is_rv_or_same { enum _ { value = false }; };
template< typename T >
struct is_rv_or_same< T, T > { enum _ { value = true }; };
template< typename T, typename ThisT >
struct is_rv_or_same< boost::rv< T >, ThisT > { enum _ { value = true }; };

#endif

template< typename SignatureT >
class light_function;

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

template< typename ResultT, typename... ArgsT >
class light_function< ResultT (ArgsT...) >
{
    typedef light_function this_type;
    BOOST_COPYABLE_AND_MOVABLE(this_type)

public:
    typedef ResultT result_type;

private:
    struct impl_base
    {
        typedef result_type (*invoke_type)(void*, ArgsT...);
        const invoke_type invoke;

        typedef impl_base* (*clone_type)(const void*);
        const clone_type clone;

        typedef void (*destroy_type)(void*);
        const destroy_type destroy;

        impl_base(invoke_type inv, clone_type cl, destroy_type dstr) : invoke(inv), clone(cl), destroy(dstr)
        {
        }

        BOOST_DELETED_FUNCTION(impl_base(impl_base const&))
        BOOST_DELETED_FUNCTION(impl_base& operator= (impl_base const&))
    };

#if !defined(BOOST_LOG_NO_MEMBER_TEMPLATE_FRIENDS)
    template< typename FunT >
    class impl;
    template< typename FunT >
    friend class impl;
#endif

    template< typename FunT >
    class impl :
        public impl_base
    {
        typedef impl< FunT > this_type;

        FunT m_Function;

    public:
        explicit impl(FunT const& fun) :
            impl_base(&this_type::invoke_impl, &this_type::clone_impl, &this_type::destroy_impl),
            m_Function(fun)
        {
        }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        explicit impl(FunT&& fun) :
            impl_base(&this_type::invoke_impl, &this_type::clone_impl, &this_type::destroy_impl),
            m_Function(boost::move(fun))
        {
        }
#endif // !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

        static void destroy_impl(void* self)
        {
            delete static_cast< impl* >(static_cast< impl_base* >(self));
        }
        static impl_base* clone_impl(const void* self)
        {
            return new impl(static_cast< const impl* >(static_cast< const impl_base* >(self))->m_Function);
        }
        static result_type invoke_impl(void* self, ArgsT... args)
        {
            return static_cast< impl* >(static_cast< impl_base* >(self))->m_Function(args...);
        }

        BOOST_DELETED_FUNCTION(impl(impl const&))
        BOOST_DELETED_FUNCTION(impl& operator= (impl const&))
    };

private:
    impl_base* m_pImpl;

public:
    BOOST_CONSTEXPR light_function() BOOST_NOEXCEPT : m_pImpl(NULL)
    {
    }
    light_function(this_type const& that)
    {
        if (that.m_pImpl)
            m_pImpl = that.m_pImpl->clone(that.m_pImpl);
        else
            m_pImpl = NULL;
    }

    light_function(BOOST_RV_REF(this_type) that) BOOST_NOEXCEPT
    {
        m_pImpl = that.m_pImpl;
        that.m_pImpl = NULL;
    }

    light_function(BOOST_RV_REF(const this_type) that) BOOST_NOEXCEPT
    {
        m_pImpl = that.m_pImpl;
        ((this_type&)that).m_pImpl = NULL;
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template< typename FunT >
    light_function(FunT&& fun) :
        m_pImpl(new impl< typename remove_cv< typename remove_reference< FunT >::type >::type >(boost::forward< FunT >(fun)))
    {
    }
#else
    template< typename FunT >
    light_function(FunT const& fun, typename boost::disable_if_c< is_rv_or_same< FunT, this_type >::value, boost::log::aux::sfinae_dummy >::type = boost::log::aux::sfinae_dummy()) :
        m_pImpl(new impl< FunT >(fun))
    {
    }
    template< typename FunT >
    light_function(BOOST_RV_REF(FunT) fun, typename boost::disable_if_c< is_cv_same< FunT, this_type >::value, boost::log::aux::sfinae_dummy >::type = boost::log::aux::sfinae_dummy()) :
        m_pImpl(new impl< typename remove_cv< FunT >::type >(fun))
    {
    }
#endif

    //! Constructor from NULL
#if !defined(BOOST_NO_CXX11_NULLPTR)
    BOOST_CONSTEXPR light_function(std::nullptr_t) BOOST_NOEXCEPT
#else
    BOOST_CONSTEXPR light_function(int p) BOOST_NOEXCEPT
#endif
        : m_pImpl(NULL)
    {
#if defined(BOOST_NO_CXX11_NULLPTR)
        BOOST_ASSERT(p == 0);
#endif
    }
    ~light_function()
    {
        clear();
    }

    light_function& operator= (BOOST_RV_REF(this_type) that) BOOST_NOEXCEPT
    {
        this->swap(that);
        return *this;
    }
    light_function& operator= (BOOST_COPY_ASSIGN_REF(this_type) that)
    {
        light_function tmp = static_cast< this_type const& >(that);
        this->swap(tmp);
        return *this;
    }
    //! Assignment of NULL
#if !defined(BOOST_NO_CXX11_NULLPTR)
    light_function& operator= (std::nullptr_t)
#else
    light_function& operator= (int p)
#endif
    {
#if defined(BOOST_NO_CXX11_NULLPTR)
        BOOST_ASSERT(p == 0);
#endif
        clear();
        return *this;
    }
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template< typename FunT >
    light_function& operator= (FunT&& fun)
    {
        light_function tmp(boost::forward< FunT >(fun));
        this->swap(tmp);
        return *this;
    }
#else
    template< typename FunT >
    typename boost::disable_if_c< is_rv_or_same< FunT, this_type >::value, this_type& >::type
    operator= (FunT const& fun)
    {
        light_function tmp(fun);
        this->swap(tmp);
        return *this;
    }
#endif

    result_type operator() (ArgsT... args) const
    {
        return m_pImpl->invoke(m_pImpl, args...);
    }

    BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT()
    bool operator! () const BOOST_NOEXCEPT { return (m_pImpl == NULL); }
    bool empty() const BOOST_NOEXCEPT { return (m_pImpl == NULL); }
    void clear() BOOST_NOEXCEPT
    {
        if (m_pImpl)
        {
            m_pImpl->destroy(m_pImpl);
            m_pImpl = NULL;
        }
    }

    void swap(this_type& that) BOOST_NOEXCEPT
    {
        impl_base* p = m_pImpl;
        m_pImpl = that.m_pImpl;
        that.m_pImpl = p;
    }
};

template< typename... ArgsT >
class light_function< void (ArgsT...) >
{
    typedef light_function this_type;
    BOOST_COPYABLE_AND_MOVABLE(this_type)

public:
    typedef void result_type;

private:
    struct impl_base
    {
        typedef void (*invoke_type)(void*, ArgsT...);
        const invoke_type invoke;

        typedef impl_base* (*clone_type)(const void*);
        const clone_type clone;

        typedef void (*destroy_type)(void*);
        const destroy_type destroy;

        impl_base(invoke_type inv, clone_type cl, destroy_type dstr) : invoke(inv), clone(cl), destroy(dstr)
        {
        }

        BOOST_DELETED_FUNCTION(impl_base(impl_base const&))
        BOOST_DELETED_FUNCTION(impl_base& operator= (impl_base const&))
    };

#if !defined(BOOST_LOG_NO_MEMBER_TEMPLATE_FRIENDS)
    template< typename FunT >
    class impl;
    template< typename FunT >
    friend class impl;
#endif

    template< typename FunT >
    class impl :
        public impl_base
    {
        typedef impl< FunT > this_type;

        FunT m_Function;

    public:
        explicit impl(FunT const& fun) :
            impl_base(&this_type::invoke_impl, &this_type::clone_impl, &this_type::destroy_impl),
            m_Function(fun)
        {
        }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        explicit impl(FunT&& fun) :
            impl_base(&this_type::invoke_impl, &this_type::clone_impl, &this_type::destroy_impl),
            m_Function(boost::move(fun))
        {
        }
#endif // !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

        static void destroy_impl(void* self)
        {
            delete static_cast< impl* >(static_cast< impl_base* >(self));
        }
        static impl_base* clone_impl(const void* self)
        {
            return new impl(static_cast< const impl* >(static_cast< const impl_base* >(self))->m_Function);
        }
        static result_type invoke_impl(void* self, ArgsT... args)
        {
            static_cast< impl* >(static_cast< impl_base* >(self))->m_Function(args...);
        }

        BOOST_DELETED_FUNCTION(impl(impl const&))
        BOOST_DELETED_FUNCTION(impl& operator= (impl const&))
    };

private:
    impl_base* m_pImpl;

public:
    BOOST_CONSTEXPR light_function() BOOST_NOEXCEPT : m_pImpl(NULL)
    {
    }
    light_function(this_type const& that)
    {
        if (that.m_pImpl)
            m_pImpl = that.m_pImpl->clone(that.m_pImpl);
        else
            m_pImpl = NULL;
    }
    light_function(BOOST_RV_REF(this_type) that) BOOST_NOEXCEPT
    {
        m_pImpl = that.m_pImpl;
        that.m_pImpl = NULL;
    }

    light_function(BOOST_RV_REF(const this_type) that) BOOST_NOEXCEPT
    {
        m_pImpl = that.m_pImpl;
        ((this_type&)that).m_pImpl = NULL;
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template< typename FunT >
    light_function(FunT&& fun) :
        m_pImpl(new impl< typename remove_cv< typename remove_reference< FunT >::type >::type >(boost::forward< FunT >(fun)))
    {
    }
#else
    template< typename FunT >
    light_function(FunT const& fun, typename boost::disable_if_c< is_rv_or_same< FunT, this_type >::value, boost::log::aux::sfinae_dummy >::type = boost::log::aux::sfinae_dummy()) :
        m_pImpl(new impl< FunT >(fun))
    {
    }
    template< typename FunT >
    light_function(BOOST_RV_REF(FunT) fun, typename boost::disable_if_c< is_cv_same< FunT, this_type >::value, boost::log::aux::sfinae_dummy >::type = boost::log::aux::sfinae_dummy()) :
        m_pImpl(new impl< typename remove_cv< FunT >::type >(fun))
    {
    }
#endif

    //! Constructor from NULL
#if !defined(BOOST_NO_CXX11_NULLPTR)
    BOOST_CONSTEXPR light_function(std::nullptr_t) BOOST_NOEXCEPT
#else
    BOOST_CONSTEXPR light_function(int p) BOOST_NOEXCEPT
#endif
        : m_pImpl(NULL)
    {
#if defined(BOOST_NO_CXX11_NULLPTR)
        BOOST_ASSERT(p == 0);
#endif
    }
    ~light_function()
    {
        clear();
    }

    light_function& operator= (BOOST_RV_REF(this_type) that) BOOST_NOEXCEPT
    {
        this->swap(that);
        return *this;
    }
    light_function& operator= (BOOST_COPY_ASSIGN_REF(this_type) that)
    {
        light_function tmp = static_cast< this_type const& >(that);
        this->swap(tmp);
        return *this;
    }
    //! Assignment of NULL
#if !defined(BOOST_NO_CXX11_NULLPTR)
    light_function& operator= (std::nullptr_t)
#else
    light_function& operator= (int p)
#endif
    {
#if defined(BOOST_NO_CXX11_NULLPTR)
        BOOST_ASSERT(p == 0);
#endif
        clear();
        return *this;
    }
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template< typename FunT >
    light_function& operator= (FunT&& fun)
    {
        light_function tmp(boost::forward< FunT >(fun));
        this->swap(tmp);
        return *this;
    }
#else
    template< typename FunT >
    typename boost::disable_if_c< is_rv_or_same< FunT, this_type >::value, this_type& >::type
    operator= (FunT const& fun)
    {
        light_function tmp(fun);
        this->swap(tmp);
        return *this;
    }
#endif

    result_type operator() (ArgsT... args) const
    {
        m_pImpl->invoke(m_pImpl, args...);
    }

    BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT()
    bool operator! () const BOOST_NOEXCEPT { return (m_pImpl == NULL); }
    bool empty() const BOOST_NOEXCEPT { return (m_pImpl == NULL); }
    void clear() BOOST_NOEXCEPT
    {
        if (m_pImpl)
        {
            m_pImpl->destroy(m_pImpl);
            m_pImpl = NULL;
        }
    }

    void swap(this_type& that) BOOST_NOEXCEPT
    {
        impl_base* p = m_pImpl;
        m_pImpl = that.m_pImpl;
        that.m_pImpl = p;
    }
};

#else // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

#define BOOST_PP_FILENAME_1 <boost/log/detail/light_function_pp.hpp>
#define BOOST_PP_ITERATION_LIMITS (0, BOOST_LOG_LIGHT_FUNCTION_LIMIT)
#include BOOST_PP_ITERATE()

#endif // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

template< typename SignatureT >
inline void swap(light_function< SignatureT >& left, light_function< SignatureT >& right)
{
    left.swap(right);
}

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_LIGHT_FUNCTION_HPP_INCLUDED_

/* light_function.hpp
+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
*/