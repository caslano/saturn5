#ifndef BOOST_BIND_MAKE_ADAPTABLE_HPP_INCLUDED
#define BOOST_BIND_MAKE_ADAPTABLE_HPP_INCLUDED

//
//  make_adaptable.hpp
//
//  Copyright (c) 2002 Peter Dimov and Multi Media Ltd.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

namespace boost
{

namespace _bi
{

template<class R, class F> class af0
{
public:

    typedef R result_type;

    explicit af0(F f): f_(f)
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

private:

    F f_;
};

template<class R, class A1, class F> class af1
{
public:

    typedef R result_type;
    typedef A1 argument_type;
    typedef A1 arg1_type;

    explicit af1(F f): f_(f)
    {
    }

    result_type operator()(A1 a1)
    {
        return f_(a1);
    }

    result_type operator()(A1 a1) const
    {
        return f_(a1);
    }

private:

    F f_;
};

template<class R, class A1, class A2, class F> class af2
{
public:

    typedef R result_type;
    typedef A1 first_argument_type;
    typedef A2 second_argument_type;
    typedef A1 arg1_type;
    typedef A2 arg2_type;

    explicit af2(F f): f_(f)
    {
    }

    result_type operator()(A1 a1, A2 a2)
    {
        return f_(a1, a2);
    }

    result_type operator()(A1 a1, A2 a2) const
    {
        return f_(a1, a2);
    }

private:

    F f_;
};

template<class R, class A1, class A2, class A3, class F> class af3
{
public:

    typedef R result_type;
    typedef A1 arg1_type;
    typedef A2 arg2_type;
    typedef A3 arg3_type;

    explicit af3(F f): f_(f)
    {
    }

    result_type operator()(A1 a1, A2 a2, A3 a3)
    {
        return f_(a1, a2, a3);
    }

    result_type operator()(A1 a1, A2 a2, A3 a3) const
    {
        return f_(a1, a2, a3);
    }

private:

    F f_;
};

template<class R, class A1, class A2, class A3, class A4, class F> class af4
{
public:

    typedef R result_type;
    typedef A1 arg1_type;
    typedef A2 arg2_type;
    typedef A3 arg3_type;
    typedef A4 arg4_type;

    explicit af4(F f): f_(f)
    {
    }

    result_type operator()(A1 a1, A2 a2, A3 a3, A4 a4)
    {
        return f_(a1, a2, a3, a4);
    }

    result_type operator()(A1 a1, A2 a2, A3 a3, A4 a4) const
    {
        return f_(a1, a2, a3, a4);
    }

private:

    F f_;
};

} // namespace _bi

template<class R, class F> _bi::af0<R, F> make_adaptable(F f)
{
    return _bi::af0<R, F>(f);
}

template<class R, class A1, class F> _bi::af1<R, A1, F> make_adaptable(F f)
{
    return _bi::af1<R, A1, F>(f);
}

template<class R, class A1, class A2, class F> _bi::af2<R, A1, A2, F> make_adaptable(F f)
{
    return _bi::af2<R, A1, A2, F>(f);
}

template<class R, class A1, class A2, class A3, class F> _bi::af3<R, A1, A2, A3, F> make_adaptable(F f)
{
    return _bi::af3<R, A1, A2, A3, F>(f);
}

template<class R, class A1, class A2, class A3, class A4, class F> _bi::af4<R, A1, A2, A3, A4, F> make_adaptable(F f)
{
    return _bi::af4<R, A1, A2, A3, A4, F>(f);
}

} // namespace boost

#endif // #ifndef BOOST_BIND_MAKE_ADAPTABLE_HPP_INCLUDED

/* make_adaptable.hpp
AG4Hc0x9+oHzdTUmfeaCYfkotpUK37+OBs5jwABUQw+VTYzKX64t6N7VGSA+gxihpEpf35tmsT14T9xUBlxNYhKF9XAxCa7PKSD8ozvhiXPI2WfKIFVSBZtiPj2BoPzW1j2TDVN70/EK9Uyz89DmxvZM1tI7hS7eyvELlb8djaJPu8jiNhukNl0V1n12Yji27dfhuYacrOpHX3Qpmqvm0Jx2SjOxn+V+3x06SAtDhY1xEj4eIFGitMK4VIBpC44RsbHQT5r8XNyyr6LK3CTNrYaucyDPLJjxs84tZp3mXYlMYrGoW2b+mXLMM9ruDXTpnEH1EL9YGz+iW2YkpYbGoCzha/dp4IyEaw9uY7MOmOIqSKB86oEC4gnOxA86J7HyEcJeVQO+Y9mnZNcjLcMgqgXk65TR+6pL7DlB524okuQUeqFO8UD5d323F+dz6tK7H8NkAX85EGGyXKKSazVqBQP+W4cVupWFkcmMugZ8oB4vRRPtGx27c4CC8f8VeN8FXmaHL5Sg0OOCXiSKHtDdso8HzlWJSt1eZwm3RRuWmpBxSJypjANck/8Ozw==
*/