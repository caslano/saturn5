#ifndef BOOST_BIND_PROTECT_HPP_INCLUDED
#define BOOST_BIND_PROTECT_HPP_INCLUDED

//
// protect.hpp
//
// Copyright 2002, 2020 Peter Dimov
// Copyright 2009 Steven Watanabe
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/config.hpp>
#include <boost/config/workaround.hpp>
#include <utility>

namespace boost
{

namespace _bi
{

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) && !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_DECLTYPE) && !(defined(BOOST_GCC) && BOOST_GCC < 40600)

template<class T> struct protect_make_void
{
    typedef void type;
};

template<class F, class E = void> struct protect_result_type
{
};

template<class F> struct protect_result_type< F, typename protect_make_void<typename F::result_type>::type >
{
    typedef typename F::result_type result_type;
};

template<class F> class protected_bind_t: public protect_result_type<F>
{
private:

    F f_;

public:

    explicit protected_bind_t( F f ): f_( f )
    {
    }

    template<class... A> auto operator()( A&&... a ) -> decltype( f_( std::forward<A>(a)... ) )
    {
        return f_( std::forward<A>(a)... );
    }

    template<class... A> auto operator()( A&&... a ) const -> decltype( f_( std::forward<A>(a)... ) )
    {
        return f_( std::forward<A>(a)... );
    }
};

#else

template<class F> class protected_bind_t
{
private:

    F f_;

public:

    typedef typename F::result_type result_type;

    explicit protected_bind_t(F f): f_(f)
    {
    }

    result_type operator()()
    {
        return f_();
    }

    result_type operator()() const
    {
        return f_();
    }

    template<class A1> result_type operator()(A1 & a1)
    {
        return f_(a1);
    }

    template<class A1> result_type operator()(A1 & a1) const
    {
        return f_(a1);
    }


#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING) \
 && !BOOST_WORKAROUND(__EDG_VERSION__, <= 238)

    template<class A1> result_type operator()(const A1 & a1)
    {
        return f_(a1);
    }

    template<class A1> result_type operator()(const A1 & a1) const
    {
        return f_(a1);
    }

#endif

    template<class A1, class A2> result_type operator()(A1 & a1, A2 & a2)
    {
        return f_(a1, a2);
    }

    template<class A1, class A2> result_type operator()(A1 & a1, A2 & a2) const
    {
        return f_(a1, a2);
    }

#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING) \
 && !BOOST_WORKAROUND(__EDG_VERSION__, <= 238)

    template<class A1, class A2> result_type operator()(A1 const & a1, A2 & a2)
    {
        return f_(a1, a2);
    }

    template<class A1, class A2> result_type operator()(A1 const & a1, A2 & a2) const
    {
        return f_(a1, a2);
    }

    template<class A1, class A2> result_type operator()(A1 & a1, A2 const & a2)
    {
        return f_(a1, a2);
    }

    template<class A1, class A2> result_type operator()(A1 & a1, A2 const & a2) const
    {
        return f_(a1, a2);
    }

    template<class A1, class A2> result_type operator()(A1 const & a1, A2 const & a2)
    {
        return f_(a1, a2);
    }

    template<class A1, class A2> result_type operator()(A1 const & a1, A2 const & a2) const
    {
        return f_(a1, a2);
    }

#endif

    template<class A1, class A2, class A3> result_type operator()(A1 & a1, A2 & a2, A3 & a3)
    {
        return f_(a1, a2, a3);
    }

    template<class A1, class A2, class A3> result_type operator()(A1 & a1, A2 & a2, A3 & a3) const
    {
        return f_(a1, a2, a3);
    }
    
#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING) \
 && !BOOST_WORKAROUND(__EDG_VERSION__, <= 238)

    template<class A1, class A2, class A3> result_type operator()(A1 const & a1, A2 const & a2, A3 const & a3)
    {
        return f_(a1, a2, a3);
    }

    template<class A1, class A2, class A3> result_type operator()(A1 const & a1, A2 const & a2, A3 const & a3) const
    {
        return f_(a1, a2, a3);
    }
    
#endif

    template<class A1, class A2, class A3, class A4> result_type operator()(A1 & a1, A2 & a2, A3 & a3, A4 & a4)
    {
        return f_(a1, a2, a3, a4);
    }

    template<class A1, class A2, class A3, class A4> result_type operator()(A1 & a1, A2 & a2, A3 & a3, A4 & a4) const
    {
        return f_(a1, a2, a3, a4);
    }
    
#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING) \
 && !BOOST_WORKAROUND(__EDG_VERSION__, <= 238)

    template<class A1, class A2, class A3, class A4> result_type operator()(A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4)
    {
        return f_(a1, a2, a3, a4);
    }

    template<class A1, class A2, class A3, class A4> result_type operator()(A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4) const
    {
        return f_(a1, a2, a3, a4);
    }

#endif

    template<class A1, class A2, class A3, class A4, class A5> result_type operator()(A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5)
    {
        return f_(a1, a2, a3, a4, a5);
    }

    template<class A1, class A2, class A3, class A4, class A5> result_type operator()(A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5) const
    {
        return f_(a1, a2, a3, a4, a5);
    }
    
#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING) \
 && !BOOST_WORKAROUND(__EDG_VERSION__, <= 238)

    template<class A1, class A2, class A3, class A4, class A5> result_type operator()(A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5)
    {
        return f_(a1, a2, a3, a4, a5);
    }

    template<class A1, class A2, class A3, class A4, class A5> result_type operator()(A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5) const
    {
        return f_(a1, a2, a3, a4, a5);
    }

#endif

    template<class A1, class A2, class A3, class A4, class A5, class A6> result_type operator()(A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6)
    {
        return f_(a1, a2, a3, a4, a5, a6);
    }

    template<class A1, class A2, class A3, class A4, class A5, class A6> result_type operator()(A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6) const
    {
        return f_(a1, a2, a3, a4, a5, a6);
    }
    
#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING) \
 && !BOOST_WORKAROUND(__EDG_VERSION__, <= 238)

    template<class A1, class A2, class A3, class A4, class A5, class A6> result_type operator()(A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6)
    {
        return f_(a1, a2, a3, a4, a5, a6);
    }

    template<class A1, class A2, class A3, class A4, class A5, class A6> result_type operator()(A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6) const
    {
        return f_(a1, a2, a3, a4, a5, a6);
    }

#endif

    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7> result_type operator()(A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6, A7 & a7)
    {
        return f_(a1, a2, a3, a4, a5, a6, a7);
    }

    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7> result_type operator()(A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6, A7 & a7) const
    {
        return f_(a1, a2, a3, a4, a5, a6, a7);
    }
    
#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING) \
 && !BOOST_WORKAROUND(__EDG_VERSION__, <= 238)

    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7> result_type operator()(A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6, A7 const & a7)
    {
        return f_(a1, a2, a3, a4, a5, a6, a7);
    }

    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7> result_type operator()(A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6, A7 const & a7) const
    {
        return f_(a1, a2, a3, a4, a5, a6, a7);
    }

#endif

    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> result_type operator()(A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6, A7 & a7, A8 & a8)
    {
        return f_(a1, a2, a3, a4, a5, a6, a7, a8);
    }

    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> result_type operator()(A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6, A7 & a7, A8 & a8) const
    {
        return f_(a1, a2, a3, a4, a5, a6, a7, a8);
    }
    
#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING) \
 && !BOOST_WORKAROUND(__EDG_VERSION__, <= 238)

    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> result_type operator()(A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6, A7 const & a7, A8 const & a8)
    {
        return f_(a1, a2, a3, a4, a5, a6, a7, a8);
    }

    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> result_type operator()(A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6, A7 const & a7, A8 const & a8) const
    {
        return f_(a1, a2, a3, a4, a5, a6, a7, a8);
    }

#endif

    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9> result_type operator()(A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6, A7 & a7, A8 & a8, A9 & a9)
    {
        return f_(a1, a2, a3, a4, a5, a6, a7, a8, a9);
    }

    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9> result_type operator()(A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6, A7 & a7, A8 & a8, A9 & a9) const
    {
        return f_(a1, a2, a3, a4, a5, a6, a7, a8, a9);
    }
    
#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING) \
 && !BOOST_WORKAROUND(__EDG_VERSION__, <= 238)

    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9> result_type operator()(A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6, A7 const & a7, A8 const & a8, A9 const & a9)
    {
        return f_(a1, a2, a3, a4, a5, a6, a7, a8, a9);
    }

    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9> result_type operator()(A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6, A7 const & a7, A8 const & a8, A9 const & a9) const
    {
        return f_(a1, a2, a3, a4, a5, a6, a7, a8, a9);
    }

#endif
};

#endif

} // namespace _bi

template<class F> _bi::protected_bind_t<F> protect(F f)
{
    return _bi::protected_bind_t<F>(f);
}

} // namespace boost

#endif // #ifndef BOOST_BIND_PROTECT_HPP_INCLUDED

/* protect.hpp
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
*/