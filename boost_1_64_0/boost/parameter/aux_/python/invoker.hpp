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
rOBNseEX0LFlJQDKNj1bvS7D/Dps6ZQWjz83Sn5t1VHNfy9XDvABFSjBkDGdtWlADcBdu6G82sfwyUCy9C7TXO7rCTmkOi+kr0KSi0VuFwjBY/Eu8DvDNNj55H0B+96CHiBUeUeIRtLMcDBDCOwseaEuKO+ye+f62YsK0kZyS6CpyoW+Uh0bfXI0rYGvrED0BGZvkEuRYBhqhFTsR15tEl1+kg+ynuL7JtYdyqbwoVMb/IK2hWLuaR2/1Uimcp0JTBkMsAGB1MQOIwMxrFBRJMKAhl7Ehm4WMfHiRc6r54hMewpMd4xGtijSGmFILkKhJQl5XUiEH6gbLJGeilSXb8/YbByRWx9ehpC81+5nAz8ikq2Ob6tnmQvW8EfIIxmvcl1YUXZ4wWQFd9KRPST1h2pn4P/lg006Sfflnoo4fkaC5aVD98ZxERDsBNmLKBQF05LR3+PVcFGCP5W/VO8nk67rKLTZhoVheiEnbE4wJvEAW0bsj6aMf05bnPIc/KSdab9Gqsu0bJ8rZDQApe6Qv5MNfMwmmgr+hMIZPO4rI6NewPdx8t9FS5SZPA==
*/