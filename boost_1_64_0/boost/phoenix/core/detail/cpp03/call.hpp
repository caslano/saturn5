
#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
#ifndef BOOST_PHOENIX_CORE_DETAIL_CALL_HPP
#define BOOST_PHOENIX_CORE_DETAIL_CALL_HPP

#include <boost/phoenix/core/detail/cpp03/preprocessed/call.hpp>

#endif
#else

#if !BOOST_PHOENIX_IS_ITERATING

#ifndef BOOST_PHOENIX_CORE_DETAIL_CALL_HPP
#define BOOST_PHOENIX_CORE_DETAIL_CALL_HPP

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/call_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif

/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/phoenix/support/iterate.hpp>

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

#define M0(Z, N ,D) \
            typedef \
                typename proto::result_of::child_c<Expr, N>::type \
                BOOST_PP_CAT(A, N); \
/**/
#define M1(Z, N ,D) \
    BOOST_PP_COMMA_IF(N) proto::child_c<N>(e)
/**/
    

#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
    (3, (1, BOOST_PHOENIX_LIMIT,                                                \
    <boost/phoenix/core/detail/cpp03/call.hpp>))
#include BOOST_PHOENIX_ITERATE()

#undef M0
#undef M1

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, BOOST_PHOENIX_ITERATION>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;

            BOOST_PP_REPEAT(BOOST_PHOENIX_ITERATION, M0, _)

            typedef
                typename boost::result_of<
                    Fun(BOOST_PHOENIX_A, context_type)
                >::type
                result_type;

            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        BOOST_PP_REPEAT(BOOST_PHOENIX_ITERATION, M1, _)
                      , boost::phoenix::context(s, d)
                    );
            }
        };

#endif

#endif // BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES

/* call.hpp
j4j03x1yf+Cy/oer/DsEV/mXxG8U478X4leL8d9n41eJ8d/594SUn/hD4vvirXsZH6biL+/X3xd1eBcRv7UD39N1Gz+6Vl+fcjxd/nfKdP/gq8X6jyvw6/izvePnFAXv10r8auNLJwWpSa4jfSL+eiHeDM82PvYGfH10Vx9dHOx/A15pfFlx8DQVPET7iGrfwtP9N/FM1wfvFxXr1+J9XLfvxw0ROT+P97Cun+bip4vxqW3wYjH+vS1eqNZfxy9w7g+7/6X4eY7b/V+Bl7tu61ePRPT62bg6/3L8aDU+Hz9SlB+1uHq+vUdDvr9w+f2Lrxbjn4fiN4v5hYfhN4j+j0K81PiDRUFuFuFJ490mOfEpj+n0x3H1/ZaPd1Tlo7N9+0zXDx8jnr+LcdX/XIv3Uc/H4zr+IB8/QJzfcfhe4v1fgXdW7Qf4nsJrQ9x7Ql+f3BCP4y2EJ/Ch4v0yCB8i4oMn414k+/peU/BvvcDt+hfVG3X/WA2eX//3LPGn8Sf5/lHtj3hPFX+Ky/HPIV6Bd1HXH89z3a7fhqv5M7yn9Pnl4ur8CnC5vhmu0l8Z4jW4jO8O8Tpctn89ra9/Ad5GnV+IV+Dq+f8Nrp7/Wnxf1b6zifgeVT7im9X8xPhG49sHOvM34Y86bvvPluEVjtv+s9vweY7b/rPkMyHv3xCvwNX1rcRzhVeHbF8T4rV4a+HeZt5PwuP4seL+q8DXZrh+fVN+H15fP/qb4+8XBkd7BT/N+IAiJz6/hu8/Vb/BVflRjbdX+YPL5xOfkCPqt/h4x+374dAtEa+p47b/NPlCxLtb9B8uxG/iz/aOn1PkfN9s1fdPOb5O9U/iq8X+ky+S/6p9IsTrcJW+3D9HvNcz1K9zU94ZT81f5vu6lsH3VRf8ceNf4jmp/O2OP+y4nd8gjv/BcTu/QeIlfX/k46r99xBctf8W4qp9qxw/ROx/EX6wqh/icn6YbXp8WRw/Ts0Pi4+NZB9/0Ac/Wqwffig+0HG7fslr+ByTvidxP/76Zb7/RPmwBS9W6z/+RfcvjMVV/8KJuOpfqMVfFM/fdvwFx+36om/hNSI+6H38SREfNPoVynexfngdLvs3Xo14U1T7PK7yfxWu8j9eG/HKRP73wOeI/O+DzxD5X4VHVPsG3lp4rXYuIPV3VT/FT1Lxs/gJKn4W31c9/7jqf6jG26vzw+X5vab7Z3Jx2f6Jy/4HXPY/hHgFrs6vKiT91bi8/vha1218Gn6/6zY+Db9XtL/XvK7zpy7Ec98I6f/A1fmX4xNE+/EifLzxv+LNU+e3GB+XIb68WerXkvr0ifjya/FRjtvyyXtT319xXF3/fLyryp+Q7StwdX9U4ZvE+Iq78KfE+Ip78Wpxf1S9RXyTmN9vHX59hvZnv33mbfp31PcDvl717+MPifLlFXy1ur/f0fEXtbhsf3w3pP0Xf1S8Xzvj94r6be579fF/Ij4IP0L1v+C1GbbfM/X7F/hGZ/ywnX+zHH/c+AQ8/fwswh81vgZvmjqbi/F1jtv5Ayre5/kT57cUP1qc3+34PiK+tg7/idj/DvwYsf9mH9A+pOJ38esbXl//fIvwla7b+anxK42v2tMZX4ovNV6H++NL8cvF/CaJD4lfVO3D+OkiPvwQvFjEhx+GnyLWXz4cHyfqf9X4JrU+BP6UmB/vT/j9Yn685/B7A7frY3MytF8bHz/BGd+Hj1Lpw0eq/uOPiG9Rzy9+vNi+HN9NrE+xCG/kuB2f8Xv8SS9wO3/K3fgTjtv5c/6Ab3Dc3l81dbQfx4LvY1u+bcM/wpuk3M5P0mJHxHvQcbt+6q/xb6KB2/VTN+NPG//xZCd9n+rx77X1ruo3Idt7n+k=
*/