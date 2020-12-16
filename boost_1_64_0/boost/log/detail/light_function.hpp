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
PeBLqp/j1fub3jt3w6H+75VK+Ijmn6r7vxymwCtgPzhLj+McmAXnwgnwKh1f8+AMuAjOgYvhQrgELoeIHNdr4CaYB2+CK+BWWATr4UrYAEv0+K2BT8BS+CO4Dr4Jq+AxWAOPw2vhn+EGGEebroPp8CY4Hm6FE+EtcAa8FV4Jb4ML4TaYDz8FV8LtcA28HlbCG2AN3Axr4Y2wtAP9/OnwbFja43eqLVuVIxPCs09x+qUKtENJg9mI2p6Y7U5cNidmW5M6GMK+RH1bme1J6m0bkrbtR6oRsRkx+MF6B3HYiLRpH6K2IWoX4rAF+QB2IKHsPo6YfWmpjUewbUeT+thqhi3IMcZR1A7GEjITWY1sQRqQA0jzjohNRiREQiREQiREQiREQiR8eOHcrP8XrTwb6/++df61jnX+ik76m9rLu07wIHzV9z2S3tYa5JXTZuQtvSQva6xjHa+8plqf9TbwPLZI8jZ6rfXIgt6h1yMp117nq/FoWbzy7nGsuf1a8gzwmtZn0LfXU34nvn1ypR77qUe1pDXY9Vgt27Gm9Ru7nJ52PXKlFoY1HFeds+J0HTOvvKRI+2A3+94iears59C1sj2BZ0yxhvUe1/61HTVr5Tsj2gd1kr6K50TxlBJrWAcy9SVlaF8a1oJc+1yRLOtGRR5tw17asFXSt3mT9Ll2hWx/ybfW4ZmN+MrMcJSZYehHD2VSBfvZ/muSfp7jWX2JvZ4fl+BLa7bX89+U7WHWOCMUFVdqW3ZRP42XtYZKhz+3KapnHYt3ZZ/9ZL31mhSpE4sTrc/1vy7p872dPHHBtgOU0UgZ9ZJnizde0rUuNMzKc4A870ueJP9+km2fB1LfJ0i31mmH0lm30+BSOmw4/49Q6Z/EtvJR9QM1MtH/DD/fo8H9DH8qY4uxf6msgyRKv3eKo99CrNlybjnWbGuQROf5pmt4jD/ic0U31sqn50OSruMx7omzx72u56muPXZZz7P1dSxq3gy4Ipl4xofGyTH115O+1bjdVhzHWOOkL6/x69K/+s0dXeuq1Z/6OV76Bc6Gcaxh1Cda62/+a2tJ2cpyPEGuKC/yf+Pzb3LOVbDjVjuYoUk+nVtM1y0tz+vUpYJG2wTyhrxemK5F5G/7mtgbPiJ5bjZdn9A3Xkvsa9HPJX0azz+TDNciw/6dx07PsS9Kninez/F0OYnxn2Lp0fMHPJs82ZwF9rUpoMyL/XcaCs0rX1HdWq9u0t+ZlNdB8qVLPs2mfXVCz3vqQJBekfgXiPfpLIrX60FeQfWGimJJayatm32tqLDP+0bZ3xDa3MXTU9swU+J26P61LMf+W3T/ybKfAvv8Pky84dpgr59eLOV+kWejnTmfc+OiibujP1eIDLfU6xo0t1wNof1t/U3ONRmzEtelNY5Kq6+t4HNV4mMDz38tN8FwDqcYzmHi5VikS9nWMZIy9FgQr8eHvHIMODbE2ceGvDFxP2fRZavYHuo1XPfnP+crRLfF3g95WvcjfZ4sZcpxcK15t6hPuho9J9YjvbkOTPaveVetLanIK6gqG0O08xymlNb7wlWSt5ArYZT6DLH0U91zGMfad3yUlEO7W4/9QknP5R3tzqbrg62v44f/MGSpLljlCXF90PyOexWZHfZfdZKeJrrv0Ecu3yeap0bydPdv89/Dst3RnkfRY/b99NNantUHubK9zKovoXZFaUFVlVXfU3ou6Dm6TnpD094jzbK3KFPbk5jwx7oeH/WP5B8jOsYctkXaf5pX+kDi7X6iTHucrxfdU3Yeuy0S/549lu12uHy8mNe3Q/skMa9vh16nNa+7hl7H/rKse0c/XrUjet8bLw+I/tWy5cWvJoRab2//urR5nTw=
*/