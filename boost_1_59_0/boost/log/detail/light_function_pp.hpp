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
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
*/