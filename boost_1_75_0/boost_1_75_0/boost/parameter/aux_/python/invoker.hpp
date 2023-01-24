// Copyright Daniel Wallin 2005. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_INVOKER_051210_HPP
# define BOOST_PARAMETER_INVOKER_051210_HPP

# include <boost/mpl/begin.hpp>
# include <boost/mpl/next.hpp>
# include <boost/mpl/deref.hpp>
# include <boost/mpl/size.hpp>
# include <boost/parameter/keyword.hpp>
# include <boost/preprocessor/iteration/iterate.hpp>

namespace boost { namespace parameter { namespace python { namespace aux {

template <long Arity, class M, class R, class Args>
struct invoker;

template <class M, class R>
struct make_invoker
{
    template <class Args>
    struct apply
    {
        typedef invoker<
            mpl::size<Args>::value, M, R, Args
        > type;
    };
};

template <long Arity, class M, class R, class T, class Args>
struct member_invoker;

template <class M, class R, class T>
struct make_member_invoker
{
    template <class Args>
    struct apply
    {
        typedef member_invoker<
            mpl::size<Args>::value, M, R, T, Args
        > type;
    };
};

template <long Arity, class T, class R, class Args>
struct call_invoker;

template <class T, class R>
struct make_call_invoker
{
    template <class Args>
    struct apply
    {
        typedef call_invoker<
            mpl::size<Args>::value, T, R, Args
        > type;
    };
};

template <long Arity, class T, class Args>
struct init_invoker;

template <class T>
struct make_init_invoker
{
    template <class Args>
    struct apply
    {
        typedef init_invoker<
            mpl::size<Args>::value, T, Args
        > type;
    };
};

template <class M, class R, class Args>
struct invoker<0, M, R, Args>
{
    static R execute()
    {
        return M()(boost::type<R>());
    }
};

template <class M, class R, class T, class Args>
struct member_invoker<0, M, R, T, Args>
{
    static R execute(T& self)
    {
        return M()(boost::type<R>(), self);
    }
};

template <class T, class R, class Args>
struct call_invoker<0, T, R, Args>
{
    static R execute(T& self)
    {
        return self();
    }
};

template <class T, class Args>
struct init_invoker<0, T, Args>
{
    static T* execute(T& self)
    {
        return new T;
    }
};

# define BOOST_PP_ITERATION_PARAMS_1 (4, \
    (1, BOOST_PARAMETER_MAX_ARITY, <boost/parameter/aux_/python/invoker_iterate.hpp>, 1))
# include BOOST_PP_ITERATE()

# define BOOST_PP_ITERATION_PARAMS_1 (4, \
    (1, BOOST_PARAMETER_MAX_ARITY, <boost/parameter/aux_/python/invoker_iterate.hpp>, 2))
# include BOOST_PP_ITERATE()

# define BOOST_PP_ITERATION_PARAMS_1 (4, \
    (1, BOOST_PARAMETER_MAX_ARITY, <boost/parameter/aux_/python/invoker_iterate.hpp>, 3))
# include BOOST_PP_ITERATE()

# define BOOST_PP_ITERATION_PARAMS_1 (4, \
    (1, BOOST_PARAMETER_MAX_ARITY, <boost/parameter/aux_/python/invoker_iterate.hpp>, 4))
# include BOOST_PP_ITERATE()

}}}} // namespace boost::parameter::python::aux

#endif // BOOST_PARAMETER_INVOKER_051210_HPP


/* invoker.hpp
bynLwdGX23eRt4c/pjKBV7iDVg8mu7jUHK/sQQh9Ls2sOq5pbNzqU23EbhxuqgA/avtuTsuZPztcIxIqKF1FdLWB7YB9cxs8FZxRu3nBAt/4AJEnc78cK1nrpvzO5O8ou1FwzvR8iB1diNdCeP+wXRtKOgyBiZitbhVms5gj7ZXQ0sIa4wmWI7STX1zTvnJTLZD0ztxzdfRvxDBgMj6MlJRPlDPtAsNZu6L8NdXOaE5bVnY7BrwFapzKzx/qRu/c33qCNx8XY/rigO6ffl4+NBotuosjtkDQttE9oj2vK4UbUtbxq47xXoo17zQRnMfwiMsus9eurBC0Le7XmFtHvPhbj84kvc3rHwj3vqXKZBF0YMghG2Wz2ALJe9O3QF9FDB5RexeN9rznvQOveIE4J3fENa+so0ffegkVD86gZ483/YgeRxuINjZV5cLikjaHHI6YKztX+94IPbwwPEf3C1u1OK0Vt5mQ/oUnA7magNy6RrUMBI4iIgMGERmWyeFSSePjUwlJjFJY7BGz36XKsQI8TDlq9+s+GY/sY0s7uTah0mX70vJrWwmltjtwbJaJJpEW09dkHX3+XVeXMwP9EbvsLbd2/Ndi5A9/sBCm+XJUhBK/6vGHmuWAP1wUVW0DA7b9H8SBt8T0oleSG1j695pRWx4VymZ5tVbYVAUcHA+61grC7mkJQmtgWnND/mpdf+JpNZZyDnThzhQ+
*/