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
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
*/