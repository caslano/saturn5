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
4N91PaDbLLli7YWwfrtFVt7ITIwzpm/ucxfYIWsiSMSeykIwRF8kdLaH557QjUBBy31MYCFOfG/CwZoDkUSK1ZOZCAvImUKl5fiovf8PUdlMrkGz8WArGEqRQs4FKUFv195tqbOuVTwrpc+7QgkKJaOiP4KCZ69AmQVhzT69SlpmD6BCBWyvijXr4ptfDo9ePTt8KfEsa1apKM9g7af1zbWt+0VqG22CeITev5Ie8ZZCqDL7FdM+kBrHJ7tjVCkB2dRZcmEG/URUr2HjnYymoIzWlIqGLWRnTIY0TjxU3dQMkZESy2rZr7rSGwN+ViRV19mGDPos/BqAcFXbfgo6akbwV0A2BdYF6Z5VVyPQ64ngHm3jgr6o1jLzviG1dTnrmUmnavZEF1tmiGQ3QuEPD7SjvKdVDXuSG+v1xro+JaxaXKOJLzS1LF75LE16MR9EpyJA8q7Jaj6wKh6T9UxU8JhCBWdwALpAqpVoOb1JZGJXMzNmQUJ7XMLubCqymuhp3d9t6oLYUJWao5ngoEvSpHY8lITpe42+wVwtVbbs3sqPOvgYrUcSY5TpA6mPiSjQrTfFLxTqnqrz7AwKhOjEH11ibPM16JGjEYeu+gCeeAaggj2DoN+hdn4uziOf0hLgmfqu1zdDot6Tr2VT
*/