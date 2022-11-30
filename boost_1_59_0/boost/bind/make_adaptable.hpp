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
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
*/