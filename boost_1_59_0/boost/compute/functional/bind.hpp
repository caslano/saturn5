//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_BIND_HPP
#define BOOST_COMPUTE_FUNCTIONAL_BIND_HPP

#include <boost/mpl/int.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/conditional.hpp>

#include <boost/compute/config.hpp>
#include <boost/compute/detail/meta_kernel.hpp>

namespace boost {
namespace compute {
namespace placeholders {

/// \internal_
template<int I>
struct placeholder : boost::integral_constant<int, I>
{
    placeholder() { }
};

placeholder<0> const _1;
placeholder<1> const _2;

} // end placeholders namespace

/// Meta-function returning \c true if \c T is a placeholder type.
template<class T>
struct is_placeholder : boost::false_type
{
};

/// \internal_
template<int I>
struct is_placeholder<placeholders::placeholder<I> > : boost::true_type
{
};

namespace detail {

template<class Function, class BoundArgs, class Args>
struct invoked_bound_function
{
    invoked_bound_function(Function f, BoundArgs bound_args, Args args)
        : m_function(f),
          m_bound_args(bound_args),
          m_args(args)
    {
    }

    // meta-function returning true if the N'th argument is a placeholder
    template<int N>
    struct is_placeholder_arg
    {
        typedef typename boost::tuples::element<N, BoundArgs>::type nth_bound_arg;

        typedef typename is_placeholder<nth_bound_arg>::type type;
        static const bool value = is_placeholder<nth_bound_arg>::value;
    };

    template<class Arg>
    struct get_arg_type
    {
        typedef Arg type;
    };

    template<int I>
    struct get_arg_type<placeholders::placeholder<I> >
    {
        typedef typename boost::tuples::element<I, Args>::type type;
    };

    // meta-function returning the type of the N'th argument when invoked
    template<int N>
    struct get_nth_arg_type
    {
        typedef typename boost::tuples::element<N, BoundArgs>::type nth_bound_arg;

        typedef typename get_arg_type<nth_bound_arg>::type type;
    };

    template<int N>
    typename get_nth_arg_type<N>::type get_nth_arg(
        typename boost::enable_if_c<is_placeholder_arg<N>::value>::type* = 0
    ) const
    {
        typedef typename boost::tuples::element<N, BoundArgs>::type nth_bound_arg;

        return boost::get<nth_bound_arg::value>(m_args);
    }

    template<int N>
    typename get_nth_arg_type<N>::type get_nth_arg(
        typename boost::disable_if_c<is_placeholder_arg<N>::value>::type* = 0
    ) const
    {
        return boost::get<N>(m_bound_args);
    }

    Function m_function;
    BoundArgs m_bound_args;
    Args m_args;
};

template<class Function, class BoundArgs, class Args>
inline meta_kernel& apply_invoked_bound_function(
    meta_kernel &k,
    const invoked_bound_function<Function, BoundArgs, Args> &expr,
    typename boost::enable_if_c<
        boost::tuples::length<BoundArgs>::value == 1
    >::type* = 0
)
{
    return k << expr.m_function(expr.template get_nth_arg<0>());
}

template<class Function, class BoundArgs, class Args>
inline meta_kernel& apply_invoked_bound_function(
    meta_kernel &k,
    const invoked_bound_function<Function, BoundArgs, Args> &expr,
    typename boost::enable_if_c<
        boost::tuples::length<BoundArgs>::value == 2
    >::type* = 0
)
{
    return k << expr.m_function(expr.template get_nth_arg<0>(),
                                expr.template get_nth_arg<1>());
}

template<class Function, class BoundArgs, class Args>
inline meta_kernel& apply_invoked_bound_function(
    meta_kernel &k,
    const invoked_bound_function<Function, BoundArgs, Args> &expr,
    typename boost::enable_if_c<
        boost::tuples::length<BoundArgs>::value == 3
    >::type* = 0
)
{
    return k << expr.m_function(expr.template get_nth_arg<0>(),
                                expr.template get_nth_arg<1>(),
                                expr.template get_nth_arg<2>());
}

template<class Function, class BoundArgs, class Args>
inline meta_kernel& operator<<(
    meta_kernel &k,
    const invoked_bound_function<Function, BoundArgs, Args> &expr
)
{
    return apply_invoked_bound_function(k, expr);
}

template<class Function, class BoundArgs>
struct bound_function
{
    typedef int result_type;

    bound_function(Function f, BoundArgs args)
        : m_function(f),
          m_args(args)
    {
    }

    template<class Arg1>
    detail::invoked_bound_function<
        Function,
        BoundArgs,
        boost::tuple<Arg1>
    >
    operator()(const Arg1 &arg1) const
    {
        return detail::invoked_bound_function<
                   Function,
                   BoundArgs,
                   boost::tuple<Arg1>
               >(m_function, m_args, boost::make_tuple(arg1));
    }

    template<class Arg1, class Arg2>
    detail::invoked_bound_function<
        Function,
        BoundArgs,
        boost::tuple<Arg1, Arg2>
    >
    operator()(const Arg1 &arg1, const Arg2 &arg2) const
    {
        return detail::invoked_bound_function<
                   Function,
                   BoundArgs,
                   boost::tuple<Arg1, Arg2>
               >(m_function, m_args, boost::make_tuple(arg1, arg2));
    }

    Function m_function;
    BoundArgs m_args;
};

} // end detail namespace

#if !defined(BOOST_COMPUTE_NO_VARIADIC_TEMPLATES) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
/// Returns a function wrapper which invokes \p f with \p args when called.
///
/// For example, to generate a unary function object which returns \c true
/// when its argument is less than \c 7:
/// \code
/// using boost::compute::less;
/// using boost::compute::placeholders::_1;
///
/// auto less_than_seven = boost::compute::bind(less<int>(), _1, 7);
/// \endcode
template<class F, class... Args>
inline detail::bound_function<F, boost::tuple<Args...> >
bind(F f, Args... args)
{
    typedef typename boost::tuple<Args...> ArgsTuple;

    return detail::bound_function<F, ArgsTuple>(f, boost::make_tuple(args...));
}
#else
template<class F, class A1>
inline detail::bound_function<F, boost::tuple<A1> >
bind(F f, A1 a1)
{
    typedef typename boost::tuple<A1> Args;

    return detail::bound_function<F, Args>(f, boost::make_tuple(a1));
}

template<class F, class A1, class A2>
inline detail::bound_function<F, boost::tuple<A1, A2> >
bind(F f, A1 a1, A2 a2)
{
    typedef typename boost::tuple<A1, A2> Args;

    return detail::bound_function<F, Args>(f, boost::make_tuple(a1, a2));
}

template<class F, class A1, class A2, class A3>
inline detail::bound_function<F, boost::tuple<A1, A2, A3> >
bind(F f, A1 a1, A2 a2, A3 a3)
{
    typedef typename boost::tuple<A1, A2, A3> Args;

    return detail::bound_function<F, Args>(f, boost::make_tuple(a1, a2, a3));
}
#endif // BOOST_COMPUTE_NO_VARIADIC_TEMPLATES

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_BIND_HPP

/* bind.hpp
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
*/