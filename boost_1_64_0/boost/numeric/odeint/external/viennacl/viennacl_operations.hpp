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
ViX8awWJ9umKT52Kn8H4cdBFvdfm88meLx+PuJm7tDV2uVec0okskf5+94Ayyycrr5W7xI48dPmBDbGFhy5f4DyAHukGjZzYvHcIhpM+qIcKlz+OD3nZ+RPk6MCzeF1ZnW/AHLVll0RPum9rrIfyL+Z8YF8lf8uuK1Y2L1+9emmsvbOPL3Nljw5HkmQNBzkGuPvx/vlWKhs9YHK4365CWLffahUehfCeRfSXz3Rsh0gXtEU9N5nItNCf4/Ue004yaY9G/P4KOwppp7Dt1Rss6MRSJmCnEfsRYvneKbD0dT3Dy9ZjgR9uCMKHV6M9Bm/JzXD1yrjRQVwD4rJ33GZM1vs2W9Jwvjw79PpaOCr/3Z8hpvXHoQMnyzg0c3LYp8hBCKMvxk988tg3vWZNDvqeatVnZe5UzQYNqfguoOt3+Lads31vIfcxPgZc0aB3quavOmply4oYy4Er/H1bk+k5cxpwf4F3s+ZVD+VuVn4+5UZuLeti5nHwB5F1xox53lv0O1sdzGX1PmgBdEfd8425kJ8v2A3HIOp+HmRReGAHxjcBb9+G7ueYyLehmUbehl4wOSwjoE7+hbQV+rK0/PBvED5ksn0HsNBbxLZ0aMDD6D0e0nst9b7E6X3F/KZY09IV85c4nWdD7h6f3tPLj3N76sz3aI6JKDP+Yy150kbx3m+CcWqNi7YNqF73jvbjAM3ELXayptIYRrsZx/fs/ec+2xNbPIkLzqCG4335KoHFrgDuE0vcdMS193Z1IdbFLUfcPK/L6csvwiK+WRnzl5mJ9mz8ykw8rhz5IzdIWZ5rPBisyrfD6123Ds+RxuLxdp33Fi/V361wpxGnMd/02joSyAdA1y/518lXqD7tSpylbbX9EqKG1qcNLa2bE00Or7FWsR+z87PVMqcEJrymOlzmraC5H+o6982sIw1OtwONO0raqvBie8MPNhPuV9cizHl9Xiz4uHn9MVYGltXKEANNdBLtZy2u9YDwAdVhf4kflrdYkY/kZd/bT8icHHYa/PRabL3QIYvIAZyjd6q6gQihPdiNoAXfp+R7VsMQxxyJhwnxnfGeIfXp6GMi7bIfJuis0f/D2aDb1wVPvqXvxtmkGmf7zHyjGkKkjH7S7CP7iaXOiRW9a50fzzRbmOYR6qTX6eSoTtdWGS7ympd0ehKuRHi6CqOvSfRIGDpeo9OjT1nkdLkJfx/nLUrHW2XeutmPG7G+u78r7TBbEW4fsb6D9/yd3B0juvvcuoPhrhFxhGXOlBzh+iyHd+dfR6CPZd+wJxR0gupXtoxY39Zt+wZE2b6hivoAe1+CoDwMF8JXgx+u5TfFE/VcLKKO2TbtuIdw2G/5SayTz7JOovu2ocnv8/mc6dtOydO3fV76BGKi+6UvTPbe3/yJ8rUn1PyJOrH5nYyw3oc4DeHlHzxPXL7oO7ABOfu6+SBlUHPADyRXouf/K9c6vA2e6nCM3pT6lrFA99NnfsB6RFaBAt6SO3s6Hz9f51tc9cunmDHzXAkHNvgBZcL0onMz9SjlF7vSeX0D8U3DyguZxFyfFJvZKmV/Hzz8fk54cH6fNH38BQhXm28tF8qcIHo+HirjSO/b7Eu+Q94Dpb0YGD33v8TPi/1fEIczBeuDbyYPjOV6jGX/rq/jQcvOumpLp0w/MKBcdk1yud8XfPB8Y260oK1EllOvO5nflUMa9yU/21csfj9yo0mnI3S26v/DK6SHxe+nnORpyyrrPFunDLNu9TrvusnekNIF44Ok+770McCYc9jD7lPQGwcdXFvMmUKiPdNO88smZ8dsmbZPDs+HIeObdk2dNm3YrqlvNjwOAI9pw9pfmOcdQRu/1fXLPb2+z0OGkb4=
*/