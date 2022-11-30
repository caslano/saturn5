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
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
*/