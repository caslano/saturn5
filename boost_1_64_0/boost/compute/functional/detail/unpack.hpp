//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_DETAIL_UNPACK_HPP
#define BOOST_COMPUTE_FUNCTIONAL_DETAIL_UNPACK_HPP

#include <boost/compute/functional/get.hpp>
#include <boost/compute/type_traits/is_vector_type.hpp>
#include <boost/compute/type_traits/result_of.hpp>
#include <boost/compute/type_traits/vector_size.hpp>
#include <boost/compute/detail/meta_kernel.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class Function, class Arg, size_t Arity>
struct invoked_unpacked
{
    invoked_unpacked(const Function &f, const Arg &arg)
        : m_function(f),
          m_arg(arg)
    {
    }

    Function m_function;
    Arg m_arg;
};

template<class Function, class Arg, size_t Arity>
inline meta_kernel& operator<<(meta_kernel &k, const invoked_unpacked<Function, Arg, Arity> &expr);

template<class Function, class Arg>
inline meta_kernel& operator<<(meta_kernel &k, const invoked_unpacked<Function, Arg, 1> &expr)
{
    return k << expr.m_function(get<0>()(expr.m_arg));
}

template<class Function, class Arg>
inline meta_kernel& operator<<(meta_kernel &k, const invoked_unpacked<Function, Arg, 2> &expr)
{
    return k << expr.m_function(get<0>()(expr.m_arg), get<1>()(expr.m_arg));
}

template<class Function, class Arg>
inline meta_kernel& operator<<(meta_kernel &k, const invoked_unpacked<Function, Arg, 3> &expr)
{
    return k << expr.m_function(get<0>()(expr.m_arg), get<1>()(expr.m_arg), get<2>()(expr.m_arg));
}

template<class Function>
struct unpacked
{
    template<class T, class Enable = void>
    struct aggregate_length
    {
        BOOST_STATIC_CONSTANT(size_t, value = boost::tuples::length<T>::value);
    };

    template<class T>
    struct aggregate_length<T, typename enable_if<is_vector_type<T> >::type>
    {
        BOOST_STATIC_CONSTANT(size_t, value = vector_size<T>::value);
    };

    template<class TupleArg, size_t TupleSize>
    struct result_impl {};

    template<class TupleArg>
    struct result_impl<TupleArg, 1>
    {
        typedef typename detail::get_result_type<0, TupleArg>::type T1;

        typedef typename boost::compute::result_of<Function(T1)>::type type;
    };

    template<class TupleArg>
    struct result_impl<TupleArg, 2>
    {
        typedef typename detail::get_result_type<0, TupleArg>::type T1;
        typedef typename detail::get_result_type<1, TupleArg>::type T2;

        typedef typename boost::compute::result_of<Function(T1, T2)>::type type;
    };

    template<class TupleArg>
    struct result_impl<TupleArg, 3>
    {
        typedef typename detail::get_result_type<0, TupleArg>::type T1;
        typedef typename detail::get_result_type<1, TupleArg>::type T2;
        typedef typename detail::get_result_type<2, TupleArg>::type T3;

        typedef typename boost::compute::result_of<Function(T1, T2, T3)>::type type;
    };

    template<class Signature>
    struct result {};

    template<class This, class Arg>
    struct result<This(Arg)>
    {
        typedef typename result_impl<Arg, aggregate_length<Arg>::value>::type type;
    };

    unpacked(const Function &f)
        : m_function(f)
    {
    }

    template<class Arg>
    detail::invoked_unpacked<
        Function, Arg, aggregate_length<typename Arg::result_type>::value
    >
    operator()(const Arg &arg) const
    {
        return detail::invoked_unpacked<
                   Function,
                   Arg,
                   aggregate_length<typename Arg::result_type>::value
                >(m_function, arg);
    }

    Function m_function;
};

template<class Function>
inline unpacked<Function> unpack(const Function &f)
{
    return unpacked<Function>(f);
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_DETAIL_UNPACK_HPP

/* unpack.hpp
D0ypv2ke9Nn+ptWPSsz/4G86D2y5v8kboj4Ff9MB6lrubzoCvehv8prow1J/k3dvpJ3pb5oHxhZBlI8yiv6m/MNqDJb7m1aR92x/02E5xrJz91FOub/Juw/ymOlvyosYDDbwgnJm+5uOgZntbzqP/i73Nx2Al9n+pqMSjNkvqy++nKQX/U2r/5Dy6PibzuN70d906o7Kzi/3N+Wgz/Y37QNzsr/pcAbOWjcCU/Q3zd0JtFJ/k+/QzXzHoBX9TQeglfubjkAv9zd5dwZ9pr9pHphyf9Mq6LP9TeeBme1vWoWOK/c3nX+8lC/H33Tq+2q8l/ubctDL/U37D0C+M/1NF1B20d90uA9aqb/p+CzoBX9TnoBW8DftuzTX33Rf0Mv9TQW6rTuOctBn+pu8B7qYor9p/AhgCv6mA9Bm+5tWR8CU+psOdkEv+JuOXJrrb9JtUO5vAr3c33SIPij3Nx3+CrJV8Ded+i1oRX/T/ZBv0d8EWtHfNDenaLt93a10y46p96bXBAbVkhjoo3NOPoK+hnb5s9hrGtE+DqYeouN+BKnLR0yXG3H8F1+qvkPH9yELt7gOp01cH4lp4z3p2uWYrnAbYC3ybOBc3wfWav4tUZ7l+0Aev0Merv9Cy8+m8AVMbR/IEtr6tMjjjOs/Mn2Wl5AYew8pRRm/u1YJvaNl8K+sL0YLA7svsN6bf+XlBN3pi6NX43uhLw6fw3iaEK3Qfp6OkbgOMGXtd+r3yGOm/2fubgxzRmLK22f/MgpT3j4XSukdbd9ctoxOpwLNMXGOtUWWk/bqJN318Z64YmRvbLSj9zRW33B7u02X1BnzzoWns+9dOsH32Mn0sWI9xODH7/W8SyHPNEvzuErDiV+k3d9g9bvc1dM5z7ukV82W2BWDTHHShkCT/bbAZP4qV5/+D/ncgPLJ5xgmHz2+v7tClxi0e2cHO3s7lAfRljhtmXasgiSpBNUWW8UoVw1pHWY03Zlwy3Me1aOZVdTTqSn1FxtcfBW/lCU03JRvbkHiL3kSnurykG6F1u0PjsPlBsq49Ilpwk41p8Fc12Vc7kQ8r0C3lvB9Fu/2lOZBbj3irLQa95DYS56E7SwT/0FCm3ndB2UJaRvW3pe/+lfuTwueNluokY3XiIKQeu8edyd5ItqNKM/JY7uqw6pCoHkAwObecJ2nvylhFICwoF2HaLcFDYl5mq+hzFqcRLJUNk6I9kXQ2GaSdgYR2bsq0W9B/+5O6Ihyd8rzeohRRtLoNoJOo7aSVjntEUTrZNUWO7PJb55m2T4k5/lsEC1feTBx5XnXoN8frbH0RXy7Jv3LD8rmDCXa5DZ2m8gmWR/tjFm1KZ3kcQUJ6ZtVXpe2D0XbD9g3Js5JFKT0Mn19KVvJZT0fR7Q47TJ2+O/jyxK22giWvNK+cbpG5HEzwj6ebqLc7U7LeK8azKPPJownNFqc3kPy/2fKrBGnTIqqkeThDrPyG59j+YGHB2dLoSf79/lznjWCaWspXiJt8aC7Cp5fOMfqKTqG/X4NVm/Wlp7H+XsR0S325PeX0Pckf3AnyEj/JEGeRyFv43nB45nRYAMVVf37UlYW5SFa2UM7n+l1twcTIV/f0/KYdSCqAnuK/mUb1+r3l3HehUzdoITX7oMXWp38rrwdvoV8Mx4TEiQycxp8rD6vFXxX4gydKtpDyqSSx3m7DyoJlYeKyjZ/A8eQTYtmR54YUx0Kz+gui3rcnH4PWafJ9PtSTpEaciDwV2d91CFn+DK1q0xPcDkRCD7vUcInJEWOh3tbugS14Hnel2j86YZtGvmyzw8ZX3zQMEWyTB0j+b8skwVeA9SP/0Zty8p5hqxPh9a2SYRqebcn2vuLckQ=
*/