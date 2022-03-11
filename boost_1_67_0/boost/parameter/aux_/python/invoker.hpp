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