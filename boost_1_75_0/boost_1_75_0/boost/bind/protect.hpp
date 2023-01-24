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
lj7YyfrUD/pxj13cZe+3Rd7OH6Zs548pqQ3qWhJaygjMcHUj/yYISB8sb+Jvpe7dd/XgR/nID9hdRyVwvRYaMNZujB/owbWKJ5AornuVj8nW0bwPNIFNENRkdw+XHO4wQxUFNgEpmHVAR+b+9uifBhOmywR2xehaU8x+INMDriSbYzRAysTDv8DWGkAG+wglKuq6l72jt3ZLT/2gtXXK/TpR6L9f/Q+r/brzL/v1fO+W9mv5S779+uN7f/1KaqJfeYfUfn2w/6/65Ylqab8Mjfo19XvVxt107uF335c9OXS+yDnB5dxMqUePIabwPX8XGVHOyToWmN4H+BZlRXv6xWazqmpSwWMGD8PYIbgT5yRsJoNcErDP+yjf0oZZtwpwb0fSUcwmOberd7bh2l6MC5bmeAIf2gJpRCCVVYX04YeYyir9etih5jbcwL8gp6Zr6lgpxplqrvd4PB+DDCSdw3HUY75CV7Qm+4XJa+9ZT8E9IvLjQOSbaRKUxPxKaXAVBDejJDk1+owfEsSfBVfWYbt7rtHhnhvrcN8rOfqddFsjhH6lkGnKbY2mX6WCe2KZ0O+o4JpSlOM86rFiYhTWd9tJ9nWruEdwd7Q73W1g/9VR9EU4RB0rJA1e3+DJqfekDxemlQniLfWC2LEMXRQ2PQSetIkRxIR2SPHa2AN3jHQNicYHdtctlXbXrazn8+GmU80FVE1udkzLOmrL
*/