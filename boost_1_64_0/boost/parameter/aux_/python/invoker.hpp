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
2VhYKSryoquMB0XedYw6wyf8mt4WeeOpUJsZbjYtd7xfL/L5jBraQ8kTCjc3wxUp6ea9UeRdlccFxpvKfeYFUTaaMgChL/gO8Xk9al/Tqw1Z74eGXmm9VMIxCdsLy4vYrhwHBxUZAhN53TUgvYvyPzjjIJrE+EuZcfs7IrbAvuKizSG17krXB0w92xPT4VdRz1hI9KWNjR8yxkZ/Ni/5K3ubl4q8la7N/3Tu3QPei6Xtzsywnbof/F7aSlw68v2ZyL+xkHlMY2pKp2XBVk3mnKyuRXnviw01BDZljk2Qzka9k/9S7wnhCL7lLVySzp5p+8t8rmt/INWGzmqJzoHhAHlNNIk6asQ9/UHovxVkfWrf0wuD4p4t94kvrTQGHF+2zjtT52rGH1ifGcZR58NVnV0/ynAL7tdqZOKIwe+ZjqGwIdJntk7B0sx7mtCxHOf81PFzpC+y2I+t6noedS1hhmLqerunrnPMloRlZior7fRllrJl7OSRjCEAcQK1lP2Ip2z7/1SbhaEtIwnJtndD7ldIXw9SftfwjO8byl86gHxGjnH745sVkL2kuPe95QbI/kXIPjZDtjk/Yor3LmMQxzBcBvZf/eWvwfmv/vLX4PxXkd8rbgXOKHorMkozyozEcY2rU0/7xO81pdzIjHLVLLd3bVo5EU9bLVedUW60/E3Aa+XbLPorFz63OC/aCtukWaYG56tZR2br8ZnQF23MbKHw4a1ersTkUMZUW4kbW0JgTcYi32y513jujKdfxowtRvt8h/Q90g9Z2Em9n3xGHYoNMnUIZ6GDhX8xCXP76UfI/ilL+dtQ/u0jDIHJvK42R7oYdjpkuXpdpUlNGRy/p9ljkfNBEaXdUK8p1qFcU7SXuO/+jPQL0rIs9JXjCvJUaWl9GRN/YTukQpvZjnv7akci3jNzTfbTHv6me1nUc5axnTFdaSPrF5GmdoCO8vgGo8aZHwHOnKoZssUvHuX3zFpGAHnXE+0Qv31xNFOcG4ryu5bdjb75Fpb5Vcyb9gj6hwZL5ZzqdJzvLpVzqrY+51R1or4NeCzrLxHfhXZSx/BvTK3sk6DRgyK1TxirKCzqKmW8q17nJhkD9F0j+y5YYQicynvlCUjXIP/pRkDtu2QonogfakXlw4ZQxPmJ5PyG5D14j3LbBilMa8xURjwy1qeMR84hxC/ZEMso85DnaKsa9/c+f+rzB6Oa9y2Rd5Tbj6sUOP1Yi77qQIYU9PodsvylhcP8JcOnFQaDJWhr2u+mP2j36oxYU8syYk0tZqypEtg7ADlqXDK/e9wwWfbJdwbPMeZcSdq5Se7cE7aj5dJ/Uz5d0fv5wULYY1KB2j+WGcO9PfM3ZbkSK47RypQ+YR1Kn7i/IQdxX8iMhabe3xaPNATqqbuI1YD8s1XdM++rqexj3M1O019tb4uVaBeP0dz8RRn5g8p37J9Z3gsHig0X5GeudNpD7vdpqjQEtqQ9JiN9jvxnOvbgbdFpx+6jRTs645zfqu1G/sxrifc73ljFtLrnXnetyF+J/vXh765l76Bf3kFlf9n3r1J/0Ffh3NfacG7xKPmcrbLP52xXiPqKej+D4X3vavH5asYIw+fe66StxcWDMtk8f7vAkTNgv8ixCJspFuNzEvkMEzJtNND2GyE9tBrm2I7t0569GhxLi8f03QdvZNkHsi3dIn+1sPO+lRgLVbR/uV+cs+dNs6qk7Sv6tP1S1NPfM84vxOc1vexeUJW93d8fpN1hp0y7u2M+xRvqKNq9gnYf6aPdbWNlYW/k97xX+aoGvm699fxv7yl7RuwpmxN4YJubfr90YkPTsod9z3Zdqf3xcu2P97Phxt0Sz1Oqwbs3Otfh7Rg=
*/