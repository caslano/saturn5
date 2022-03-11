#ifndef BOOST_BIND_PROTECT_HPP_INCLUDED
#define BOOST_BIND_PROTECT_HPP_INCLUDED

//
//  protect.hpp
//
//  Copyright (c) 2002 Peter Dimov and Multi Media Ltd.
//  Copyright (c) 2009 Steven Watanabe
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

namespace boost
{

namespace _bi
{

template<class F> class protected_bind_t
{
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

private:

    F f_;
};

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