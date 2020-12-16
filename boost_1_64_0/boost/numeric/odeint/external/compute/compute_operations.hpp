/*
 [auto_generated]
 boost/numeric/odeint/external/compute/compute_operations.hpp

 [begin_description]
 Operations of Boost.Compute zipped iterators. Is the counterpart of the compute_algebra.
 [end_description]

 Copyright 2009-2011 Karsten Ahnert
 Copyright 2009-2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_COMPUTE_COMPUTE_OPERATIONS_HPP_DEFINED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_COMPUTE_COMPUTE_OPERATIONS_HPP_DEFINED

#include <boost/preprocessor/repetition.hpp>
#include <boost/compute.hpp>

namespace boost {
namespace numeric {
namespace odeint {

struct compute_operations {

#define BOOST_ODEINT_COMPUTE_TEMPL_FAC(z, n, unused)                           \
    , class Fac ## n = BOOST_PP_CAT(Fac, BOOST_PP_DEC(n))

#define BOOST_ODEINT_COMPUTE_MEMB_FAC(z, n, unused)                            \
    const Fac ## n m_alpha ## n;

#define BOOST_ODEINT_COMPUTE_PRM_FAC(z, n, unused)                             \
    BOOST_PP_COMMA_IF(n) const Fac ## n alpha ## n

#define BOOST_ODEINT_COMPUTE_INIT_FAC(z, n, unused)                            \
    BOOST_PP_COMMA_IF(n) m_alpha ## n (alpha ## n)

#define BOOST_ODEINT_COMPUTE_PRM_STATE(z, n, unused)                           \
    BOOST_PP_COMMA_IF(n) StateType ## n &s ## n

#define BOOST_ODEINT_COMPUTE_BEGIN_STATE(z, n, unused)                         \
    BOOST_PP_COMMA_IF( BOOST_PP_DEC(n) ) s ## n.begin()

#define BOOST_ODEINT_COMPUTE_END_STATE(z, n, unused)                           \
    BOOST_PP_COMMA_IF( BOOST_PP_DEC(n) ) s ## n.end()

#define BOOST_ODEINT_COMPUTE_LAMBDA(z, n, unused)                              \
    BOOST_PP_EXPR_IF(n, +) m_alpha ## n * bc::lambda::get< n >(bc::_1)

#define BOOST_ODEINT_COMPUTE_OPERATIONS(z, n, unused)                          \
    template<                                                                  \
        class Fac0 = double                                                    \
        BOOST_PP_REPEAT_FROM_TO(1, n, BOOST_ODEINT_COMPUTE_TEMPL_FAC, ~)       \
        >                                                                      \
    struct scale_sum ## n {                                                    \
        BOOST_PP_REPEAT(n, BOOST_ODEINT_COMPUTE_MEMB_FAC, ~)                   \
        scale_sum ## n(                                                        \
                BOOST_PP_REPEAT(n, BOOST_ODEINT_COMPUTE_PRM_FAC, ~)            \
                )                                                              \
            : BOOST_PP_REPEAT(n, BOOST_ODEINT_COMPUTE_INIT_FAC, ~)             \
        { }                                                                    \
        template< BOOST_PP_ENUM_PARAMS(BOOST_PP_INC(n), class StateType) >     \
        void operator()(                                                       \
                BOOST_PP_REPEAT(                                               \
                    BOOST_PP_INC(n),                                           \
                    BOOST_ODEINT_COMPUTE_PRM_STATE, ~)                         \
                ) const                                                        \
        {                                                                      \
            namespace bc = boost::compute;                                     \
            bc::transform(                                                     \
                    bc::make_zip_iterator(                                     \
                        boost::make_tuple(                                     \
                            BOOST_PP_REPEAT_FROM_TO(                           \
                                1, BOOST_PP_INC(n),                            \
                                BOOST_ODEINT_COMPUTE_BEGIN_STATE, ~)           \
                            )                                                  \
                        ),                                                     \
                    bc::make_zip_iterator(                                     \
                        boost::make_tuple(                                     \
                            BOOST_PP_REPEAT_FROM_TO(                           \
                                1, BOOST_PP_INC(n),                            \
                                BOOST_ODEINT_COMPUTE_END_STATE, ~)             \
                            )                                                  \
                        ),                                                     \
                    s0.begin(),                                                \
                    BOOST_PP_REPEAT(n, BOOST_ODEINT_COMPUTE_LAMBDA, ~)         \
                    );                                                         \
        }                                                                      \
    };

BOOST_PP_REPEAT_FROM_TO(2, 8, BOOST_ODEINT_COMPUTE_OPERATIONS, ~)

#undef BOOST_ODEINT_COMPUTE_TEMPL_FAC
#undef BOOST_ODEINT_COMPUTE_MEMB_FAC
#undef BOOST_ODEINT_COMPUTE_PRM_FAC
#undef BOOST_ODEINT_COMPUTE_INIT_FAC
#undef BOOST_ODEINT_COMPUTE_PRM_STATE
#undef BOOST_ODEINT_COMPUTE_BEGIN_STATE
#undef BOOST_ODEINT_COMPUTE_END_STATE
#undef BOOST_ODEINT_COMPUTE_LAMBDA
#undef BOOST_ODEINT_COMPUTE_OPERATIONS

    template<class Fac1 = double, class Fac2 = Fac1>
    struct scale_sum_swap2 {
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;

        scale_sum_swap2(const Fac1 alpha1, const Fac2 alpha2)
            : m_alpha1(alpha1), m_alpha2(alpha2) { }

        template<class State0, class State1, class State2>
        void operator()(State0 &s0, State1 &s1, State2 &s2) const {
            namespace bc = boost::compute;

            bc::command_queue &queue   = bc::system::default_queue();
            const bc::context &context = queue.get_context();

            const char source[] = BOOST_COMPUTE_STRINGIZE_SOURCE(
                    kernel void scale_sum_swap2(
                        F1 a1, F2 a2,
                        global T0 *x0, global T1 *x1, global T2 *x2,
                        )
                    {
                        uint i = get_global_id(0);
                        T0 tmp = x0[i];
                        x0[i]  = a1 * x1[i] + a2 * x2[i];
                        x1[i]  = tmp;
                    }
                    );

            std::stringstream options;
            options
                << " -DT0=" << bc::type_name<typename State0::value_type>()
                << " -DT1=" << bc::type_name<typename State1::value_type>()
                << " -DT2=" << bc::type_name<typename State2::value_type>()
                << " -DF1=" << bc::type_name<Fac1>()
                << " -DF2=" << bc::type_name<Fac2>();

            bc::program program =
                bc::program::build_with_source(source, context, options.str());

            bc::kernel kernel(program, "scale_sum_swap2");
            kernel.set_arg(0, m_alpha1);
            kernel.set_arg(1, m_alpha2);
            kernel.set_arg(2, s0.get_buffer());
            kernel.set_arg(3, s1.get_buffer());
            kernel.set_arg(4, s2.get_buffer());

            queue.enqueue_1d_range_kernel(kernel, 0, s0.size());

        }
    };

    template<class Fac1 = double>
    struct rel_error {
        const Fac1 m_eps_abs, m_eps_rel, m_a_x, m_a_dxdt;

        rel_error(const Fac1 eps_abs, const Fac1 eps_rel, const Fac1 a_x, const Fac1 a_dxdt)
            : m_eps_abs(eps_abs), m_eps_rel(eps_rel), m_a_x(a_x), m_a_dxdt(a_dxdt) { }


        template <class State0, class State1, class State2>
        void operator()(State0 &s0, State1 &s1, State2 &s2) const {
            namespace bc = boost::compute;
            using bc::_1;
            using bc::lambda::get;

            bc::for_each(
                    bc::make_zip_iterator(
                        boost::make_tuple(
                            s0.begin(),
                            s1.begin(),
                            s2.begin()
                            )
                        ),
                    bc::make_zip_iterator(
                        boost::make_tuple(
                            s0.end(),
                            s1.end(),
                            s2.end()
                            )
                        ),
                    get<0>(_1) = abs( get<0>(_1) ) /
                        (m_eps_abs + m_eps_rel * (m_a_x * abs(get<1>(_1) + m_a_dxdt * abs(get<2>(_1)))))
                    );
        }
    };
};

} // odeint
} // numeric
} // boost

#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_COMPUTE_COMPUTE_OPERATIONS_HPP_DEFINED

/* compute_operations.hpp
PgafiaVf8JC4d/TAZiTjQ1M4i8/h7Pw1fEsyPig5Bs+XpP/tsQM7Ykhzri9sJw5sdTa/Es73hxfpp/BWeA/fnY3/OWlgdxtiXX4y6oek/zI7dWBXkvcrOQ3pMy5mUlf9v+L5Qyw8EZ4Kz4TnwotKlL/hdHyliO9EvJ3F4yM4i09EfCbiCxFfifgG/hQbv3O2KL+ewz0WngkvhTdwOr9QeHQu91R4IbyG742/TOlqn7sI7St0/tXAHkZ85Ho+lw9sD9b+UiP9I+U37yrRPg6n5Q/huTh+KeJr4S2ctv+J89vVon1YeCI8g9P0DU7vjzh+LbyFz0XGP2XXDmySId3753k3DOynIdzvX3nTwN4j5Z/mZv77W+EdfBmWv93C41PhGZzOb4DT8esivhHxnYi3W3l8BB+TtN8Wt4n8AU7zB7hPjh81PH1OhRfCa+Ed/HIyPqW5Q+QPwqM7uafCC/iF5k6fs7sGdP8W7270r5L3P7oH/b+k/7S5D+1XZPxm/IBon4DT9F14Caf9f+L8jTh+J9we5B7Baf+XiM+EF8IrOP39Ir4Tbg8N6PzgEh6S8kP/8G/jYzLH+I/qEdF/Aqft13Dafg2n83ceFd8nnKb/cNp/CafPT3gjvBPnt8d4fASn9TfhifAUTte/gdP1b0R8Lc7fiON38GgI9/udPo73gz1fOM0f4fOy/R/gJVsf4Ql+/S18KbZ/15PoPyXewzdh/R9P8d9Xwmn/E5zmv8K9p7knwnM4HX8lvBVuz3CP4Qez9bHhR7D9Y59F+WQIs/xvPtKYKG9D4VY/j/6pId31w/QlkX4Jz+H0+cPp8xfxrYjv4TT9fpl7Ch+P5a9wWv8W3sHp/Eg47f95RfT/CE+F53Da/gWn4xvE8Rvh3a9O2n9eRfpLPIbvzN4f+BX/Kp8sMobZaPgb3OpuYDOT+B7O9u+IXhvYMWT8fAefn7TPxq//Vv5Z2BUPP4+0z/Zv8udnbyF/IePny7dF/R/O9mfo4ZOz9sl3RPsGnPavifhCeCW8Ed7B6fcrrt97V3y/cNa/lor4HN6S9pPm/YGtSfq3kg9E+Ux4BqftG3DavgFflKyPn3w0sO/NbBaHFx+L8hWctj/AO7a/wSfIn1n9sx/Y0UbKh58if2H7v342sAeNzL/4fGC7kvjqSzx/Vj78io+/S79B+y6ZPxN/J+rvcPp+/sLeVQY9TwThw10HDVbcoW9xd3d3SpqkNFAJSYoPrsPg7u4+OAyD8wMZ3IbBdQYG+IEO+uQubfo19G63hB/M8M7bNu1zT06y2dvb27sY+GcZ+HcB19rvhvN/aDi/+FWPl4B/qtnfff3fcH9p/O/HCEt8i+/z4/V38fN3zWDp40eAa+f/DPisM1r6+Dbg2vUxBv72wLXxbYbzn2Xg3wVcOz4w4LPOZOnjOwx4AFxrHwHfQvf8DeBdzfzI47Po2+dD4Nr5wVn18lMCru1/gV+mke9ZZzPID3Ct/ADXrq8Crp2fA67d/9NQvpeB/zjZ6PmH7eewxItCiLtG+J+2n1N//v2Aa/s/4Nr+D7jWPwdca58Yyved4fyzzqU/f9mAb2/AA+ATk49+PnB5Xku7//JVwHebbDS+/XyWuEhjH2+/gL7+AXCtf9mA32U4/8sG/nfAXxI4HhFfLxayxEG6+wN4W4OXSmhfnf8A+C4aXCxsiR01eABcd/4Pgd+pmf9/fBHIr25/JuALanCxqKUfHwLfevLRz2eadQlLO75bH/iquv4LuPb5bAb8LuD7CSFKo8aHS1piH038zl3Al9D5L4Hrnu/6HXBd+cRSlnb/k/2AL6SxL19e2hLb6fqHZSzxlsZ+3X5Z9E8a+SktB/nQ2afAl9U=
*/