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