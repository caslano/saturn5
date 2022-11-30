/*
 [auto_generated]
 boost/numeric/odeint/external/viennacl_operations.hpp

 [begin_description]
 ViennaCL operations.
 [end_description]

 Copyright 2012 Denis Demidov
 Copyright 2012 Karsten Ahnert
 Copyright 2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_VIENNACL_VIENNACL_OPERATIONS_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_VIENNACL_VIENNACL_OPERATIONS_HPP_INCLUDED

#include <viennacl/vector.hpp>

#ifdef VIENNACL_WITH_OPENCL
#  include <viennacl/generator/custom_operation.hpp>
#endif

namespace boost {
namespace numeric {
namespace odeint {


#ifdef VIENNACL_WITH_OPENCL
struct viennacl_operations
{

    template< class Fac1 = double , class Fac2 = Fac1 >
    struct scale_sum2
    {
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;

        scale_sum2( Fac1 alpha1 , Fac2 alpha2 )
            : m_alpha1( alpha1 ) , m_alpha2( alpha2 )
        { }

        template< class T1 , class T2 , class T3 >
        void operator()( viennacl::vector<T1> &v1 ,
                const viennacl::vector<T2> &v2 ,
                const viennacl::vector<T3> &v3
                ) const
        {
            using namespace viennacl;

            static generator::symbolic_vector    <0, T1>   sym_v1;
            static generator::symbolic_vector    <1, T2>   sym_v2;
            static generator::symbolic_vector    <2, T3>   sym_v3;
            static generator::cpu_symbolic_scalar<3, Fac1> sym_a1;
            static generator::cpu_symbolic_scalar<4, Fac2> sym_a2;

            static generator::custom_operation op(
                    sym_v1 = sym_a1 * sym_v2
                           + sym_a2 * sym_v3,
                    "scale_sum2"
                    );

            ocl::enqueue( op(v1, v2, v3, m_alpha1, m_alpha2) );
        }

        typedef void result_type;
    };


    template< class Fac1 = double , class Fac2 = Fac1 , class Fac3 = Fac2 >
    struct scale_sum3
    {
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;
        const Fac3 m_alpha3;

        scale_sum3( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 )
            : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 )
        { }

        template< class T1 , class T2 , class T3 , class T4 >
        void operator()( viennacl::vector<T1> &v1 ,
                const viennacl::vector<T2> &v2 ,
                const viennacl::vector<T3> &v3 ,
                const viennacl::vector<T4> &v4
                ) const
        {
            using namespace viennacl;

            static generator::symbolic_vector    <0, T1>   sym_v1;
            static generator::symbolic_vector    <1, T2>   sym_v2;
            static generator::symbolic_vector    <2, T3>   sym_v3;
            static generator::symbolic_vector    <3, T4>   sym_v4;
            static generator::cpu_symbolic_scalar<4, Fac1> sym_a1;
            static generator::cpu_symbolic_scalar<5, Fac2> sym_a2;
            static generator::cpu_symbolic_scalar<6, Fac3> sym_a3;

            static generator::custom_operation op(
                    sym_v1 = sym_a1 * sym_v2
                           + sym_a2 * sym_v3
                           + sym_a3 * sym_v4,
                    "scale_sum3"
                    );

            ocl::enqueue( op(v1, v2, v3, v4, m_alpha1, m_alpha2, m_alpha3) );
        }

        typedef void result_type;
    };


    template< class Fac1 = double , class Fac2 = Fac1 , class Fac3 = Fac2 , class Fac4 = Fac3 >
    struct scale_sum4
    {
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;
        const Fac3 m_alpha3;
        const Fac4 m_alpha4;

        scale_sum4( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 , Fac4 alpha4 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) { }

        template< class T1 , class T2 , class T3 , class T4 , class T5 >
        void operator()( viennacl::vector<T1> &v1 ,
                const viennacl::vector<T2> &v2 ,
                const viennacl::vector<T3> &v3 ,
                const viennacl::vector<T4> &v4 ,
                const viennacl::vector<T5> &v5
                ) const
        {
            using namespace viennacl;

            static generator::symbolic_vector    <0, T1>   sym_v1;
            static generator::symbolic_vector    <1, T2>   sym_v2;
            static generator::symbolic_vector    <2, T3>   sym_v3;
            static generator::symbolic_vector    <3, T4>   sym_v4;
            static generator::symbolic_vector    <4, T5>   sym_v5;
            static generator::cpu_symbolic_scalar<5, Fac1> sym_a1;
            static generator::cpu_symbolic_scalar<6, Fac2> sym_a2;
            static generator::cpu_symbolic_scalar<7, Fac3> sym_a3;
            static generator::cpu_symbolic_scalar<8, Fac4> sym_a4;

            static generator::custom_operation op(
                    sym_v1 = sym_a1 * sym_v2
                           + sym_a2 * sym_v3
                           + sym_a3 * sym_v4
                           + sym_a4 * sym_v5,
                    "scale_sum4"
                    );

            ocl::enqueue( op(v1, v2, v3, v4, v5,
                        m_alpha1, m_alpha2, m_alpha3, m_alpha4) );
        }

        typedef void result_type;
    };


    template< class Fac1 = double , class Fac2 = Fac1 , class Fac3 = Fac2 , class Fac4 = Fac3 , class Fac5 = Fac4 >
    struct scale_sum5
    {
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;
        const Fac3 m_alpha3;
        const Fac4 m_alpha4;
        const Fac5 m_alpha5;

        scale_sum5( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 , Fac4 alpha4 , Fac5 alpha5 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) { }

        template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6 >
        void operator()( viennacl::vector<T1> &v1 ,
                const viennacl::vector<T2> &v2 ,
                const viennacl::vector<T3> &v3 ,
                const viennacl::vector<T4> &v4 ,
                const viennacl::vector<T5> &v5 ,
                const viennacl::vector<T6> &v6
                ) const
        {
            using namespace viennacl;

            static generator::symbolic_vector    < 0, T1>   sym_v1;
            static generator::symbolic_vector    < 1, T2>   sym_v2;
            static generator::symbolic_vector    < 2, T3>   sym_v3;
            static generator::symbolic_vector    < 3, T4>   sym_v4;
            static generator::symbolic_vector    < 4, T5>   sym_v5;
            static generator::symbolic_vector    < 5, T6>   sym_v6;
            static generator::cpu_symbolic_scalar< 6, Fac1> sym_a1;
            static generator::cpu_symbolic_scalar< 7, Fac2> sym_a2;
            static generator::cpu_symbolic_scalar< 8, Fac3> sym_a3;
            static generator::cpu_symbolic_scalar< 9, Fac4> sym_a4;
            static generator::cpu_symbolic_scalar<10, Fac5> sym_a5;

            static generator::custom_operation op(
                    sym_v1 = sym_a1 * sym_v2
                           + sym_a2 * sym_v3
                           + sym_a3 * sym_v4
                           + sym_a4 * sym_v5
                           + sym_a5 * sym_v6,
                    "scale_sum5"
                    );

            ocl::enqueue( op(v1, v2, v3, v4, v5, v6,
                        m_alpha1, m_alpha2, m_alpha3, m_alpha4, m_alpha5) );
        }

        typedef void result_type;
    };


};
#else
struct viennacl_operations : public default_operations {};
#endif


} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_VIENNACL_VIENNACL_OPERATIONS_HPP_INCLUDED

/* viennacl_operations.hpp
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
*/