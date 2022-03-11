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