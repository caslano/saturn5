/*
 [auto_generated]
 boost/numeric/odeint/stepper/detail/generic_rk_algorithm.hpp

 [begin_description]
 Implementation of the generic Runge-Kutta method.
 [end_description]

 Copyright 2011-2013 Mario Mulansky
 Copyright 2011-2012 Karsten Ahnert
 Copyright 2012 Christoph Koke

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_GENERIC_RK_ALGORITHM_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_GENERIC_RK_ALGORITHM_HPP_INCLUDED

#include <boost/static_assert.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/size_t.hpp>

#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/iterator.hpp>
#include <boost/fusion/mpl.hpp>
#include <boost/fusion/sequence.hpp>

#include <boost/array.hpp>

#include <boost/numeric/odeint/algebra/range_algebra.hpp>
#include <boost/numeric/odeint/algebra/default_operations.hpp>
#include <boost/numeric/odeint/stepper/detail/generic_rk_call_algebra.hpp>
#include <boost/numeric/odeint/stepper/detail/generic_rk_operations.hpp>
#include <boost/numeric/odeint/util/bind.hpp>

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {

template< class T , class Constant >
struct array_wrapper
{
    typedef const typename boost::array< T , Constant::value > type;
};

template< class T , size_t i >
struct stage
{
    T c;
    boost::array< T , i > a;
};


template< class T , class Constant >
struct stage_wrapper
{
    typedef stage< T , Constant::value > type;
};


template<
size_t StageCount,
class Value ,
class Algebra ,
class Operations
>
class generic_rk_algorithm {

public:
    typedef mpl::range_c< size_t , 1 , StageCount > stage_indices;

    typedef typename boost::fusion::result_of::as_vector
            <
            typename boost::mpl::copy
            <
            stage_indices ,
            boost::mpl::inserter
            <
            boost::mpl::vector0< > ,
            boost::mpl::push_back< boost::mpl::_1 , array_wrapper< Value , boost::mpl::_2 > >
    >
    >::type
    >::type coef_a_type;

    typedef boost::array< Value , StageCount > coef_b_type;
    typedef boost::array< Value , StageCount > coef_c_type;

    typedef typename boost::fusion::result_of::as_vector
            <
            typename boost::mpl::push_back
            <
            typename boost::mpl::copy
            <
            stage_indices,
            boost::mpl::inserter
            <
            boost::mpl::vector0<> ,
            boost::mpl::push_back< boost::mpl::_1 , stage_wrapper< Value , boost::mpl::_2 > >
    >
    >::type ,
    stage< Value , StageCount >
    >::type
    >::type stage_vector_base;


    struct stage_vector : public stage_vector_base
    {
        struct do_insertion
        {
            stage_vector_base &m_base;
            const coef_a_type &m_a;
            const coef_c_type &m_c;

            do_insertion( stage_vector_base &base , const coef_a_type &a , const coef_c_type &c )
            : m_base( base ) , m_a( a ) , m_c( c ) { }

            template< class Index >
            void operator()( Index ) const
            {
                //boost::fusion::at< Index >( m_base ) = stage< double , Index::value+1 , intermediate_stage >( m_c[ Index::value ] , boost::fusion::at< Index >( m_a ) );
                boost::fusion::at< Index >( m_base ).c  = m_c[ Index::value ];
                boost::fusion::at< Index >( m_base ).a = boost::fusion::at< Index >( m_a );
            }
        };

        struct print_butcher
        {
            const stage_vector_base &m_base;
            std::ostream &m_os;

            print_butcher( const stage_vector_base &base , std::ostream &os )
            : m_base( base ) , m_os( os )
            { }

            template<class Index>
            void operator()(Index) const {
                m_os << boost::fusion::at<Index>(m_base).c << " | ";
                for( size_t i=0 ; i<Index::value ; ++i )
                    m_os << boost::fusion::at<Index>(m_base).a[i] << " ";
                m_os << std::endl;
            }
        };


        stage_vector( const coef_a_type &a , const coef_b_type &b , const coef_c_type &c )
        {
            typedef boost::mpl::range_c< size_t , 0 , StageCount-1 > indices;
            boost::mpl::for_each< indices >( do_insertion( *this , a , c ) );
            boost::fusion::at_c< StageCount - 1 >( *this ).c = c[ StageCount - 1 ];
            boost::fusion::at_c< StageCount - 1 >( *this ).a = b;
        }

        void print( std::ostream &os ) const
        {
            typedef boost::mpl::range_c< size_t , 0 , StageCount > indices;
            boost::mpl::for_each< indices >( print_butcher( *this , os ) );
        }
    };



    template< class System , class StateIn , class StateTemp , class DerivIn , class Deriv ,
    class StateOut , class Time >
    struct calculate_stage
    {
        Algebra &algebra;
        System &system;
        const StateIn &x;
        StateTemp &x_tmp;
        StateOut &x_out;
        const DerivIn &dxdt;
        Deriv *F;
        Time t;
        Time dt;

        calculate_stage( Algebra &_algebra , System &_system , const StateIn &_x , const DerivIn &_dxdt , StateOut &_out ,
                StateTemp &_x_tmp , Deriv *_F , Time _t , Time _dt )
        : algebra( _algebra ) , system( _system ) , x( _x ) , x_tmp( _x_tmp ) , x_out( _out) , dxdt( _dxdt ) , F( _F ) , t( _t ) , dt( _dt )
        {}


        template< typename T , size_t stage_number >
        void inline operator()( stage< T , stage_number > const &stage ) const
        //typename stage_fusion_wrapper< T , mpl::size_t< stage_number > , intermediate_stage >::type const &stage ) const
        {
            if( stage_number > 1 )
            {
#ifdef BOOST_MSVC
#pragma warning( disable : 4307 34 )
#endif
                system( x_tmp , F[stage_number-2].m_v , t + stage.c * dt );
#ifdef BOOST_MSVC
#pragma warning( default : 4307 34 )
#endif
            }
            //std::cout << stage_number-2 << ", t': " << t + stage.c * dt << std::endl;

            if( stage_number < StageCount )
                detail::template generic_rk_call_algebra< stage_number , Algebra >()( algebra , x_tmp , x , dxdt , F ,
                        detail::generic_rk_scale_sum< stage_number , Operations , Value , Time >( stage.a , dt) );
            //                  algebra_type::template for_eachn<stage_number>( x_tmp , x , dxdt , F ,
            //                          typename operations_type::template scale_sumn< stage_number , time_type >( stage.a , dt ) );
            else
                detail::template generic_rk_call_algebra< stage_number , Algebra >()( algebra , x_out , x , dxdt , F ,
                        detail::generic_rk_scale_sum< stage_number , Operations , Value , Time >( stage.a , dt ) );
            //                algebra_type::template for_eachn<stage_number>( x_out , x , dxdt , F ,
            //                            typename operations_type::template scale_sumn< stage_number , time_type >( stage.a , dt ) );
        }

    };

    generic_rk_algorithm( const coef_a_type &a , const coef_b_type &b , const coef_c_type &c )
    : m_stages( a , b , c )
    { }

    template< class System , class StateIn , class DerivIn , class Time , class StateOut , class StateTemp , class Deriv >
    void inline do_step( Algebra &algebra , System system , const StateIn &in , const DerivIn &dxdt ,
            Time t , StateOut &out , Time dt ,
            StateTemp &x_tmp , Deriv F[StageCount-1] ) const
    {
        typedef typename odeint::unwrap_reference< System >::type unwrapped_system_type;
        unwrapped_system_type &sys = system;
        boost::fusion::for_each( m_stages , calculate_stage<
                unwrapped_system_type , StateIn , StateTemp , DerivIn , Deriv , StateOut , Time >
        ( algebra , sys , in , dxdt , out , x_tmp , F , t , dt ) );
    }

private:
    stage_vector m_stages;
};


}
}
}
}

#endif // BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_GENERIC_RK_ALGORITHM_HPP_INCLUDED

/* generic_rk_algorithm.hpp
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
*/