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
gfyN32dzsVTj36Dx7TYX4xBJgPGwLWwBO8KWMB0mwr4wCQ6AbeA0mAqnw7ZwFkyGc2ErWAFbw0V+7+P1GQ7203zY38d3N3L8EaZcjcqNOL4c99a1y2XgqlSuUOXstmqHINcFZsIsOBRq+3Av5dw+k7V9pmj7ZGv74De2A3M1/laNb2wH6vfv7vAcOBCO0vOPhlPgGJhjycM8OAFeByf68scY6Jy/NM1fB81fR80ffhO/6jjxu2j8rhq/m8bHr/WqfSecFlSv+LVeB8DhcCAsDWFjrcZmZy3x0zpba/9uW2tHv6qzt+b9nhF75Ie3ufb/bm8tHFtrywfWM98XKk/jOwFuO24P7jAutmkjVwYuG7cYtx63DVfT9D/rO0Ldr+5X96v71f3qfnW//57fv+j7f2F5uTUB4Pt//3840WXW0Bfpt98WOp/7a1wzyxbLFrv9jsLi0opJhQsWFpZX6MrnDN9aT+T89hPXuD3MO7iN4t/vt/7Ju+61ucsr3828X98g/tddCUY+r6Rkftms4rJyyytyReY8Xcw6+FvE/4nEw1YBf5d5sj6umIi+9fA3i9xfxD/RpNMxOF75ZN7Y+tm5QzbY5k9TecFaVma3I/CAyD1J3PHNtnls47t+TdoxsT3Mu8Se+OfpWnmvXAEB20WustLs0xggswaZRz0yH9rTmqNyaptE7DRMi+V2Psz5A9Ya2OyttjWw+Purfy4HbOuz1V6DfW91s+5M2jaZY1nmmF/7SVg2pK4Js7WRhuUGhGk7+H/TtAqo79qb6nvoBOs781YnvZXtM12NtL3QKdNW70qcWNVfTYNS+dftcd+lj7HvJ076VpntNlt4R2rm5cvvQlySldi9TvkVe0csLcRj0zO36pnmVeNHGjtVkeKfbrejlk8r6ftzlScXcm3Vl3B74+h7ciMn6bRMFbkSWkivmZDhZRXzffmaKOFNQtmK1LjusG2eeepTyh1gv9FTtmS130h5OOZXHmPHsaWkIWWQY519x8i3v27112//KfrtvwUuDtlKx7ZiihQyAde1ruF01hf7OQ838NkdTcTdimvFOat958wrKOgVcGKPXnzp2UPabj9J43Uwfd6fxH9VsB7pNfCihC9TPfHGP91mm6fM2Ipodp+/rYg+4u/s+7ZJ2gWFZVY3IDJWAT+W9FLUj4VAiZOqY4iJg3+o9Bsvi/x10n8OIryS+nnc6vNadLDXM/v8a9+o86VGc2xGbHh2GL192ZeePbF99q5C6FyW6fMkn35tt1i/7T+s3//usmSJX3WfaTsu5vDbjnj+3wLF30PkU/RaI2PGrt7dEr7ONZA85eGW4LQdNa0EiZspueWTnMu39v41CW9PH+oOGssSVOZrkRlDHL7C46w2OUJ7xDc049BNxxuH/kFbZCV6wlY0C/+bZGC79Icpes2WBXyTXOW1Q4YS9IJjYTtkK+83Ng60+nMuKSwrnsW0OMdvq7+WOKu1PbxpnKnh1PSDlv888qTxuV9YkGP7TmnijA+6fkoIq5D4Eep3u7aIf5zRB1Z0UWjf/couSatHpG3eoMy1iNP8Dv2FFT4pYhg7ywXk0WbTo6B4ts+mR0ibWysknSL1+5dzoUvTkKvad10vfkCufWOjI0CHzJyKp6QMGZF2OyFpHrn8CpvNlGdErqOU9ZC3Lsp9+vqKhD8ZMdc90i3Xhylrnk3H55ZTWNOejSSPS90h6kbPIacw80ve/Cd7ZwJfRXEG8PeSEDAESEISwh3uQ9Ag9yGEO5yGGwVJIEEShCQmQbCihkNEBUSBelUFRURBpYiV1lKjeEsVlapVq1i1tVZbilap1dr/fu978/YdmwMCaPve7zf5Z3a+b3eunZ3dmfk=
*/