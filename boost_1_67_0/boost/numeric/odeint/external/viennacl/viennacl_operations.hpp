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