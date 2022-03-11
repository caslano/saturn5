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