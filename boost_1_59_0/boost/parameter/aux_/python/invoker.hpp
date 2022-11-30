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
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
*/