/*
 [auto_generated]
 boost/numeric/odeint/stepper/symplectic_rkn_sb3a_mclachlan.hpp
 
 [begin_description]
 Implementation of the symplectic MacLachlan stepper for separable Hamiltonian system.
 [end_description]
 
 Copyright 2011-2013 Karsten Ahnert
 Copyright 2011-2013 Mario Mulansky
 
 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_SYMPLECTIC_RKN_SB3A_MCLACHLAN_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_SYMPLECTIC_RKN_SB3A_MCLACHLAN_HPP_INCLUDED


#include <boost/numeric/odeint/stepper/base/symplectic_rkn_stepper_base.hpp>

#include <boost/numeric/odeint/algebra/range_algebra.hpp>
#include <boost/numeric/odeint/algebra/default_operations.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>
#include <boost/numeric/odeint/algebra/operations_dispatcher.hpp>

#include <boost/numeric/odeint/util/resizer.hpp>

#include <boost/array.hpp>

namespace boost {
namespace numeric {
namespace odeint {


#ifndef DOXYGEN_SKIP
namespace detail {
namespace symplectic_rkn_sb3a_mclachlan {

    /*
      exp( a1 t A ) exp( b1 t B )
      exp( a2 t A ) exp( b2 t B )
      exp( a3 t A ) exp( b3 t B ) exp( a3 t A )
      exp( b2 t B ) exp( a2 t A )
      exp( b1 t B ) exp( a1 t A )
    */

    template< class Value >
    struct coef_a_type : public boost::array< Value , 6 >
    {
        coef_a_type( void )
        {
            (*this)[0] = static_cast< Value >( 0.40518861839525227722 );
            (*this)[1] = static_cast< Value >( -0.28714404081652408900 );
            (*this)[2] = static_cast< Value >( 1 ) / static_cast< Value >( 2 ) - ( (*this)[0] + (*this)[1] );
            (*this)[3] = (*this)[2];
            (*this)[4] = (*this)[1];
            (*this)[5] = (*this)[0];

        }
    };

    template< class Value >
    struct coef_b_type : public boost::array< Value , 6 >
    {
        coef_b_type( void )
        {
            (*this)[0] = static_cast< Value >( -3 ) / static_cast< Value >( 73 );
            (*this)[1] = static_cast< Value >( 17 ) / static_cast< Value >( 59 );
            (*this)[2] = static_cast< Value >( 1 ) - static_cast< Value >( 2 ) * ( (*this)[0] + (*this)[1] );
            (*this)[3] = (*this)[1];
            (*this)[4] = (*this)[0];
            (*this)[5] = static_cast< Value >( 0 );
        }
    };

} // namespace symplectic_rkn_sb3a_mclachlan
} // namespace detail
#endif // DOXYGEN_SKIP



template<
    class Coor ,
    class Momentum = Coor ,
    class Value = double ,
    class CoorDeriv = Coor ,
    class MomentumDeriv = Coor ,
    class Time = Value ,
    class Algebra = typename algebra_dispatcher< Coor >::algebra_type ,
    class Operations = typename operations_dispatcher< Coor >::operations_type ,
    class Resizer = initially_resizer
    >
#ifndef DOXYGEN_SKIP
class symplectic_rkn_sb3a_mclachlan :
        public symplectic_nystroem_stepper_base
<
    6 , 4 ,
    Coor , Momentum , Value , CoorDeriv , MomentumDeriv , Time , Algebra , Operations , Resizer
    >
#else
class symplectic_rkn_sb3a_mclachlan : public symplectic_nystroem_stepper_base
#endif
{
public:
#ifndef DOXYGEN_SKIP
    typedef symplectic_nystroem_stepper_base
    <
    6 , 4 ,
    Coor , Momentum , Value , CoorDeriv , MomentumDeriv , Time , Algebra , Operations , Resizer
    > stepper_base_type;
#endif
    typedef typename stepper_base_type::algebra_type algebra_type;
    typedef typename stepper_base_type::value_type value_type;


    symplectic_rkn_sb3a_mclachlan( const algebra_type &algebra = algebra_type() )
        : stepper_base_type(
            detail::symplectic_rkn_sb3a_mclachlan::coef_a_type< value_type >() ,
            detail::symplectic_rkn_sb3a_mclachlan::coef_b_type< value_type >() ,
            algebra )
    { }
};


/************* DOXYGEN ***********/

/**
 * \class symplectic_rkn_sb3a_mclachlan
 * \brief Implement of the symmetric B3A method of Runge-Kutta-Nystroem method of sixth order.
 *
 * The method is of fourth order and has six stages. It is described HERE. This method cannot be used
 * with multiprecision types since the coefficients are not defined analytically.
 *
 * ToDo Add reference to the paper.
 *
 * \tparam Order The order of the stepper.
 * \tparam Coor The type representing the coordinates q.
 * \tparam Momentum The type representing the coordinates p.
 * \tparam Value The basic value type. Should be something like float, double or a high-precision type.
 * \tparam CoorDeriv The type representing the time derivative of the coordinate dq/dt.
 * \tparam MomemtnumDeriv The type representing the time derivative of the momentum dp/dt.
 * \tparam Time The type representing the time t.
 * \tparam Algebra The algebra.
 * \tparam Operations The operations.
 * \tparam Resizer The resizer policy.
 */

    /**
     * \fn symplectic_rkn_sb3a_mclachlan::symplectic_rkn_sb3a_mclachlan( const algebra_type &algebra )
     * \brief Constructs the symplectic_rkn_sb3a_mclachlan. This constructor can be used as a default
     * constructor if the algebra has a default constructor.
     * \param algebra A copy of algebra is made and stored inside explicit_stepper_base.
     */

} // namespace odeint
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_ODEINT_STEPPER_SYMPLECTIC_RKN_SB3A_MCLACHLAN_HPP_INCLUDED

/* symplectic_rkn_sb3a_mclachlan.hpp
mvwPm7HH54bIa4IPw8c1IO6r9a4mas4jFmVcmsG8pA9zmy/b0JeQ8Q/sfVIocS3nb4H94DGNcjOWlBcRtzAvmXg5NkOs0iKQvIN0sZV7hgxhAn8vfW8Ncytiic3gTfrLXmy4+zTqvIm52VpdxHNPAkgBryzVxG/0+93E029sw5ZqM8Zdi5+YwvjMXKwYv/yToYmlpF0H1oNl4DD4MNCa/0eDW2i/RlnMK9/UxUNjdZFO/BW+lf7ymiaePaSLusfJaxCxwyPY01RDdBjNuPA8NrBTF++dYIzMJf/exEQnie+wl/w2VJh+GEH8MvU18sJuCogdatDHmxD/Pc6PW676mHiLPjfpOWycMvywQhO3HyIOoNy/MbZOglt7P3E7scOGu3kut5Tnch3pF8xn7vsrbfETvjEYXe0zhPn7jg9OY6ynDdqDrqAeqAvqgyagGQgCLUA7EAw6gE4gBsSBWHAJGAcuBRPAZSADZIMsEA3iQSJIAGNAilybuBykgRxwI1gk1yluAUvBfOLtMuady2n7PcTOm2W6+WAJuFmub6wGA9HBijbYH+fPEJcGL6SPNCDua8zch3Hx4iDi3JPME5fqp9c72ptzVvD13fQb/O0GYuM6UcTecv0jFVwOnr3M7Cvk25byybWPxyPxjZMMce01vO+Yqov1jAUjGP/Kid+e3kfc8b4hjuO3XmxPX883xELuWSPv/TmMuP83XRwcwty7NuW/E7uPIe4z11G6YSc70GVtfOQIXbz5Kdxw+ji62PwB9WOcy9xL3FjGelGOIQYjuw9x3jWh+LQgTRzrxnO4g7ro9hFx+xLmm+cRp4Ibb9VFs581cc2XzFNfJ6aA244Ndlupi8f+hi1sxh/jL1MuwC+uIAb7C/6EeW0v5iNhu/ARuyjXR6w/UZ/pidgAaxhN78FfUf8FyFoMKn5lHPmB+mFri/qgZ+z4ris10eo71gjWGGJKPfwV5+tIuwasBx+lauIguts1WMPm6dcTDBFATPAcsXLzZ/AB7zEm1tVEJ9YOvh6sC89grs8n3n4Lf76Lce9TTVxOrJHH+Ne3EWPocl28Thx9L+NxO/pIb+aWQxj/j9IvrujAM3fGxoDFumhK33iCPrKNPrPmUtYoSLcqnfnZL7qYH4WvpF/WOmwQIzBvmoVMuS6VOAvdHCY24dyfcc5zATHNNcQT6PQK1m26wB3FHu5hbWTM5axXbEWnf6GdxhHbMAd7lvEvSa5XJYMPX9DFeZM08Q2+J6EBc51f6a/49M1ce5O1g0/Rw0LO72feUV8Y4nbi8ULizffNe8Ew+vbaMObtH2EjtNHwnlzfiW18RF/Ebz7G3Pe3ZF28sQC/9iHPi1vQb8Ev+MiZSdgmse5XO3lHmbbph888tT6WBW4CN4BFYAG4Ra6BrTSvObjFkl8HNoLd4HXwJtgHDoCPwC6wB7wB3gHvgXotGUPAOuxmRH3mBbTz32YwZ1yuia43EVvkU95aOr6P2LUD60P34K8WE0e1pP7gMJhxBbGdGZcvx++vYR4wDB+3mHk9McQdzdFpY8aon3XR0izDzcjDzj68ivZpxdyZ+LD0E/30etqT2G3jFGIQ/HjQJ9QLud/jey/hWounmAd9h//ifC42F2QwJ2INpPt2xn7aKqeEuPRz+t5wfOD7zGOZsx+hj0x8gvGPtYmRacROrZlrXMC4/yscvnj+FOIT5nePM358HEkfZBxrn4NPZxzN3kOdxlPm14gzyHMB8COv+aOw542ss/2VGIOY9zLWHv42HJ0yFvW4gj4wDf+eTv9+Fb/JPSU5tAuyRt+HjukHn/Jjv9dm0DZc++Bl7ONaYrC3dfEw42kQ63utQQvQDrQFbUAHsIg=
*/