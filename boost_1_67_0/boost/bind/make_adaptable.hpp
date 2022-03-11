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