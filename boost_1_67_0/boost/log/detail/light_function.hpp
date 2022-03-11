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
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
*/