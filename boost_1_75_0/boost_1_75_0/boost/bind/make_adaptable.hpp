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
uJZ98Aqw+LDn7b0/WFsC3wjw+ip9cHmwnItCcM2MigDNOBK+HA3+j4MK4CwOcSt0RNz3wY1SK4ZRMScEsQ6V0t0MvUxFoYJ43rShw4wtNcbcXSbbQSGuas512b9EZ//ZyrSQDhFiGuq8UdCtUlPuJ1iJKYr1pg3hmko7H9ptLW6NoshMhkluzOsA43RifmVhh6morLgdY6xxZXMt6WNyagLSR+bU6NNtOTWG9PicmsD0uJya4PTr4b9rF5w71RO02QU1AfE6XfrlULAbFOwMBdtDmbAFNX+wMumGnHOtMoIK9bUBA0soMQTDAttmwlaGRDNBL09HvI2WQXeXQZ4rozfsIu0QxfpV/KJT9rjKOVfHnGBTZ9oQSrNnsu2Nv/FUen8c1v0jaZqiOF4cohmKhg/GwwcFFUN+pq8eD1LjCY0+ODKIIeDcvoJpU6Dwse5K7pgyvb5lDiHF73ZvpKjQIEW0Finym/lGjIp8q+2+yEfY7vb+zkN7vT6hwfZIzXf84N/q/T74d47w74ROi390wMVRIa5+jmVRaHZNdPY5hnIvUICgx6yjzphyKTdtFeBYVWMcY8h5aOT/AY5991mzONYQoMGxdE4UvNCra/yNMekWHKpZILj35HD/ScGmdC2pqaWmXw9Q9r5CXCo0bM3O7KLD1n8RxFMZ1zrEEYyDHAT72EF0/B8VxKGCe1Sk9Ep8kO4TCw/CvOm9Bk/2
*/