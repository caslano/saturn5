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
31cSLF0glVoRTPPmr1tXCpCTKplKdj8hcc1nzKaWYYZcvipIId6mjgxSuOvXyHUix1sB4lp/o14aRJh96izmZgaZOVofwBzZHhMnUASu6IDpcfSxqduD6D2ADkxRIX99SnBWT+PRmhbT32xvE+s62lurrZWx7RE0tubgIpuwCAtmeWFHW8ysOZtmt8XMmtlrn9LMjoX8PUtIfGZNGztLC1tXq/Yy1HmWMEvYYnmtsD86YYHBVAjf2RDxlbnqkrqAzD76ldjjHQS5FeTTkvpr/xGWVPSHMNQotmYB5XeF9fKJ8bvUElimGbmgZDJacQkrVxvgMhlcWtU/imYfeSYdolY/v6hpUz9ikBfPbq1F9KZsVkWL6E2cdZ1S9Dv/ANGHCbFTYrGnEn0mTqNAhq/UnK0MOd/h+ExnuiKrw6So2T7Xbwr0RzbIR69k2H0lqqQ9iTXKBHuhZyQnbaVfIqBS8x7QvF1FqR09cELgJW33O7Lcv6g70hTk+0pJJGjVQbWkmgT0rq7aSrd/nlld/4C2BzyBGynn++c5gWZ16EOICLL+qx06sZmi3EdC5btcFqVC7F0sXyERdl6CBPKayi+1gS+5EnsrOXYT9/78u7gc7Sv4e7qwjvpnVZ9ZF+wosKXoejnYjVylZERb/TsFML/AFevoaS9jH/IpR2FmbeoX/kBw6icG0ZHDuHxeHOu4UEOdoGtB/fCXLajZwWG1VU0X6mo5E3U96/Wwf/b61T96feffvf7y966P/KPXMwiHfEtLJyZ9txi0xtcWv2RH8yCKCoGWd5FS2oAwqHCUUhopfM5wpeRbLUzfcY2iTX4Nzfmd0LfLzz0MX1O0SDj8attIn3OoOJs3Ky5SO0+rRCl13im64LHa+uQjLostb5K/RwqOVYhNQmc391aTe7jkehsH7gIriMg1usCTAIlP50Li32H/Gt+43yC1hte1gx9rBy9pB9/bDr4lCLfkb7WhFBcp1ULCfki4OlL4IOFN3wofJIwdr373c4dQnH/FIBJ6xC3G+2nmtrl62x+kDYkZAxPxU5qIRM1EbLhPmIjgGrU3spM33ZAM8RT3tj/anOJnrVJUtU1RVVt7zKSvqYzKrczQJe7FIm75tuKLcazzceCNQF1WZYVUdqlKpRQtQAFC8p6FH24NlabSennN4w2CkMd0dgtZp3lYV9DHRTwwFXJnnN3ftgyDtDJsvbelDPXCBK3fIYZDcfYQXTDBba0S3Ns6QSG+hKJXFjMFmmdIZVoLYKxMM2xNM0rsrH0SzyifZalyxXqPegvyU3bjyNXFjiyNGwe5+YnGTZjGjXeErmBqfZ5yZSWGCFatPTiG2vzvcKbBQ0uhyut932jqobzhzdEFzi9V6dLKatBQtueIkZ1NfeAHcU4XrXSaOHWUq55YEdjQvCMF0HdByBkLiiHeYl3TAwrvB1ytvi6ijJ6L2I7AiWNKC6tN5zsmadANhMyO6Ro0q1UxUkX6yFy1XHi0LoKUzkpiHZ+O45NL1+J0mtUmTMftRvdJHKz4OQcBsrxG570WHU+OrnY/th5wLMns6eXNOIkB0+E6nOAQZ5/r5MXj8A50gxYMpmMSt7HPIHpTmPK1GEzyOM1lHNb27MvxFk1Mnmi3q0W7PYB2uzpS+NBuf/utFqZPPJDnozkVj+r4ReDkN0R9o6hPwWsp4th83Af1HrTvxMPymiSehXHX6ms/N0Uc8SCufG/xZVgPtOapfQURU9J8ozMsI/mbhV82mcW9gA88pTsCJwUwC30CwohVJtJ4D1PCRqPLSRULHMnbi2IMdX23C8DVdbrYbKFJtr/BayRR9j83t6jrWbOyvbE54AZW7tVa5d54j4GtYAgqGDQ=
*/