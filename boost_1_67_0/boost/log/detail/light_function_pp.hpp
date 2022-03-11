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