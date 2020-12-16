/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

template<
    typename ResultT
    BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), typename ArgT)
>
class light_function< ResultT (BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), ArgT)) >
{
    typedef light_function this_type;
    BOOST_COPYABLE_AND_MOVABLE(this_type)

public:
    typedef ResultT result_type;

private:
    struct impl_base
    {
        typedef result_type (*invoke_type)(void* BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), ArgT));
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
        static result_type invoke_impl(void* self BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), ArgT, arg))
        {
            return static_cast< impl* >(static_cast< impl_base* >(self))->m_Function(BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), arg));
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

    result_type operator() (BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PP_ITERATION(), ArgT, arg)) const
    {
        return m_pImpl->invoke(m_pImpl BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), arg));
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

template<
    BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), typename ArgT)
>
class light_function< void (BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), ArgT)) >
{
    typedef light_function this_type;
    BOOST_COPYABLE_AND_MOVABLE(this_type)

public:
    typedef void result_type;

private:
    struct impl_base
    {
        typedef void (*invoke_type)(void* BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), ArgT));
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
        static result_type invoke_impl(void* self BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), ArgT, arg))
        {
            static_cast< impl* >(static_cast< impl_base* >(self))->m_Function(BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), arg));
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

    result_type operator() (BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PP_ITERATION(), ArgT, arg)) const
    {
        m_pImpl->invoke(m_pImpl BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), arg));
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

/* light_function_pp.hpp
tC8a83p4qHX19q9L/+2AL/6Kad+cnnfx+1sT7xt53S+rJ9SEXic3+34JtX7efnuHK8T3y1M/Xvq7h0r7HvvnjoZprw7ad5K14l6++Ma3rh5wV/6ebp/s/oI36S8PPnb2vv0Vwl5A1tuPWfNy/V1XD1ORI4j1LaVEuA7mwjJd3/4MLIPlsAZWwE0avw1W6vpxFfw2rIbfhxvg+3Aj7MD+NsEo+Ak4RtcBZ8ItcBb8JJwNb4ardXuNrjdu0nXG2+A2eBesh1+CO+B+eAc8CD+j67Ut1nwD5mh7+yCHEKfvj4lwBJwGL4XT4RQ4A86Cl8NKOAt+DM6G2+EcWA/nwjt0HXcPzIFfg/PhAbgQHoKL4XG4VPshF6bB5XAcvAaOh/kwG34UToF5cIbGz4KT4GzdVp8Zei+Q+xztdPvMSFNfC/1gLMyA4+EAmA0HwTlwiB73oTAfDoclcIQe/0y4XrcbozynXa/NZHt/ne17wF6/XXqD2/dAKdv1bv8DDA7WDxFrXff4iShPNtus7wb5IsjfHNofwVbSdiEvIJZvgvf4P+ZG/xpwBgxeB4bEW2vBtTe6/RXczfZ+5BByChm/hXyI5cMg7U9Rsm48Ga5me8sWtz+DvWxXkBbo1yDhk7quDPMRp4+DWrbvRAJ9Hewmbht8BgatPRMX6Pcg5aZW3wc7qYO1Jp1PfDashfXIbuQYeZ6Blj+ElJtbfSKM5/+liLV2Xcf/OxFrDfsJ/m+mfGst+72bg/0lvEN64Pp25skoz/it1B/ZRlwdtPwn7Nwa7EOhmbi98Dg8RVzULf718GEwcE0855bwfCrcSb5DyHHE6Vsh4Vb/uvlsaPlYyPfFwfpb2+9roenWtv0tHL3V7HPhFDL6tta19tn8P5N+q4O7kJQl5IOmtfcW4sUPw8mosH0xdNlGG8h/hO1h29heSr+zncP/mfxfDbchlp+GRt82PARN/hpSPkUd4Gj4DHELYS1ylP93Quc6fyPbhxHP1fQZbCIuYzv1YHsadPp0qN7u9uuwl+3sO/DlgGy6I7L2HwmREAmREAmREAmREAkfbjgn6/+8PnW21v8r0J1i+c7X9/H7IRZf9PlDjwt6B7mioLIAh+vFlVW8eOlxvnPneCc2HmaKbgLpHcx+0+MCn3/z7tW6Yp+HfsPzclN+rVN5pfF5ueaX+vUbLO9SYk5vXNsnr/udwPXteD9S3qHStie5fJ/b7Ql4Tm3X215rpX7EUz99D2us1IfyxrnXOdM66XezveQT+o9TTpz9TixjrLqkzHe85EhVGY9PAtwhOtO9Uzxjzf7i23l8ctp5fHLacXzIa3rP0F6zKZb0Su891Lx13WOVvRZzUNJTeA9xrNqX8Ka1xCV7HO9j+9eFtH+ulfS+um3lH22/f7hJtpd5Te8Xypq4pB/n2L/k3MdYK08SvEnyzPPO1Xol2fu5gOeJuaz5ut/rRnj3T4SHe+73ul+INcv9pD+AvBB7+ne/P6wxfS7fJWzvO4Mvf8ZLfPKpxx/rckfhy2VJBT1eeSznaOSdwQ/6zuCH7b9e3u2yrtl6r6p3vtul79z5mAp7wr4wweGXPMOr1xS9htbru2kJ+m5Xtup9BCbCKbAPnAb7w+lwKJwBL4KXw0nwSrgQzoErYQ4sh/PgFrgB3gWvg1+AH4f3wuvh/fAT8BF4A9wPN8NvwIXwcbgIvgiXwCPwavhzmAvfgsv0na5rdM1hBYyGJTANroUXwAo4D1bCElgNPw4/BjfDWsg3dSPvaUXe0zrj97SO8iw25s7I89hIiIRI+N8N5+T3P9a9Z+P3fyo2eMk+u7hUnw2e73Nn1Xwcv6ZsBd9pTScthbQWZ1olNSovU1uv2XE=
*/