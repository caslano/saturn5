
/*
 [auto_generated]
 boost/numeric/odeint/iterator/detail/ode_iterator_base.hpp

 [begin_description]
 Base class for const_step_iterator and adaptive_iterator.
 [end_description]

 Copyright 2012-2013 Karsten Ahnert
 Copyright 2012-2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_ITERATOR_DETAIL_ODE_ITERATOR_BASE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ITERATOR_DETAIL_ODE_ITERATOR_BASE_HPP_INCLUDED

#include <boost/iterator/iterator_facade.hpp>

#include <boost/numeric/odeint/util/unwrap_reference.hpp>
#include <boost/numeric/odeint/util/detail/less_with_sign.hpp>

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {

    struct ode_state_iterator_tag {};
    struct ode_state_time_iterator_tag {};

    template< class Iterator , class Stepper , class System , class State , typename Tag >
    class ode_iterator_base;


    /* Specialization for the state iterator that has only state_type as its value_type */
    template< class Iterator , class Stepper , class System , class State >
    class ode_iterator_base< Iterator , Stepper , System , State , ode_state_iterator_tag >
        : public boost::iterator_facade
          <
              Iterator ,
              typename traits::state_type< Stepper >::type const ,
              boost::single_pass_traversal_tag
          >
    {
    private:

        typedef Stepper stepper_type;
        typedef System system_type;
        typedef typename boost::numeric::odeint::unwrap_reference< stepper_type >::type unwrapped_stepper_type;
        typedef State state_type;
        typedef typename unwrapped_stepper_type::time_type time_type;
        typedef typename unwrapped_stepper_type::value_type ode_value_type;

    public:
   
        ode_iterator_base( stepper_type stepper , system_type sys , time_type t , time_type dt )
            : m_stepper( stepper ) , m_system( sys ) ,
              m_t( t ) , m_dt( dt ) , m_at_end( false )
        { }

        ode_iterator_base( stepper_type stepper , system_type sys )
            : m_stepper( stepper ) , m_system( sys ) ,
              m_t() , m_dt() , m_at_end( true )
        { }

        // this function is only for testing
        bool same( const ode_iterator_base &iter ) const
        {
            return (
                //( static_cast<Iterator>(*this).get_state() ==
                //  static_cast<Iterator>(iter).get_state ) &&
                ( m_t == iter.m_t ) && 
                ( m_dt == iter.m_dt ) &&
                ( m_at_end == iter.m_at_end )
                );
        }


    protected:

        friend class boost::iterator_core_access;

        bool equal( ode_iterator_base const& other ) const
        {
            if( m_at_end == other.m_at_end )
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        const state_type& dereference() const
        {
            return static_cast<const Iterator*>(this)->get_state();
        }

    protected:

        stepper_type m_stepper;
        system_type m_system;
        time_type m_t;
        time_type m_dt;
        bool m_at_end;
    };



    /* Specialization for the state-time iterator that has pair<state_type,time_type> as its value_type */

    template< class Iterator , class Stepper , class System , class State >
    class ode_iterator_base< Iterator , Stepper , System , State , ode_state_time_iterator_tag >
        : public boost::iterator_facade
          <
              Iterator ,
              std::pair< const State , const typename traits::time_type< Stepper >::type > ,
              boost::single_pass_traversal_tag ,
              std::pair< const State& , const typename traits::time_type< Stepper >::type& >
          >
    {
    private:

        typedef Stepper stepper_type;
        typedef System system_type;
        typedef typename boost::numeric::odeint::unwrap_reference< stepper_type >::type unwrapped_stepper_type;
        typedef State state_type;
        typedef typename unwrapped_stepper_type::time_type time_type;
        typedef typename unwrapped_stepper_type::value_type ode_value_type;

    public:

        ode_iterator_base( stepper_type stepper , system_type sys ,
                           time_type t , time_type dt )
            : m_stepper( stepper ) , m_system( sys ) ,
              m_t( t ) , m_dt( dt ) , m_at_end( false )
        { }

        ode_iterator_base( stepper_type stepper , system_type sys )
            : m_stepper( stepper ) , m_system( sys ) , m_at_end( true )
        { }

        bool same( ode_iterator_base const& iter )
        {
            return (
                //( static_cast<Iterator>(*this).get_state() ==
                //  static_cast<Iterator>(iter).get_state ) &&
                ( m_t == iter.m_t ) &&
                ( m_dt == iter.m_dt ) &&
                ( m_at_end == iter.m_at_end )
                );
        }


    protected:

        friend class boost::iterator_core_access;

        bool equal( ode_iterator_base const& other ) const
        {
            if( m_at_end == other.m_at_end )
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        std::pair< const state_type& , const time_type& > dereference() const
        {
            return std::pair< const state_type & , const time_type & >(
                    static_cast<const Iterator*>(this)->get_state() , m_t );
        }

        stepper_type m_stepper;
        system_type m_system;
        time_type m_t;
        time_type m_dt;
        bool m_at_end;

    };



} // namespace detail
} // namespace odeint
} // namespace numeric
} // namespace boost



#endif // BOOST_NUMERIC_ODEINT_ITERATOR_DETAIL_ODE_ITERATOR_BASE_HPP_INCLUDED

/* ode_iterator_base.hpp
ndC5QXxqyxd+cZ/6HaovpvPsAvamYntSNym+7gEMOLF4Eu9Cfo2+K8O4MjaWVSXh+3wEWZnj36N1bxJ744c4r7YTkSTDj1JfOgFO+/5e9mFtjHfPteI55NalbwE+Y3X5MVxPf/h92h+e5FkEux/A/qRspX9ule9NwVXr2fZ8ygfN2CJubGx92OAgBhTpyFrjR4GzZRJy5tSlBa0zovHy8ZKsJ6aJMUdaAoho3EYa3B8x8pDfzdRRvT/yyY3mzphZ4yetxD74tFnbA/3YuPysyRdZhvmfF3njvIjsQ+g++aKi8YmNkg98T+PLgDFtYoWTJvHTzP8a8R0txkvxOn+7tdHk5ZvG/n5LfRvfbr5rvsM04HqdBf0j3w93mm+j72v6wPqBtNfTH6027xTF88GneadI8j1tGyv9Z3F5QkZmnVu1bwh5Wla/NGVP32DeIQrLQqelvb/daM5NkyfdZ78Xut6WpA1Pf1Q8ncm8W8jTn03ZfsPT3eQJNk32FQxP95EnrSf3bzSx1RO+Pf5q16NlDyB+XtrMO8RL3Af5O8fjcu65PR/syZ6i3WdI3jN42NRHnMT6HmV91dXyNlJsTjNjOtjE/W3uh/+D+WiTT9+LtD4jUTR7vpWbKFfmJ8XlmWFwpie8r1pFPpDP/Rqp937KSPN9FPBDmVCGjiZ/c4xMHr+J+kZaenwereggL/n9XNKZDVzqB+pkXVKf7B8AT/NuZXYs8kdiMW/wiJx34fVZAMDo7ss3hYflRsIoMJl+/W3h80bThHmeqj3Mf0dE93zmbdLr6qgz5etmPMBdGlD+7sYkyjkdPG5TqINX4N7yxfEYP8Pj2uthtr1jvgJp40AuP5wuRvEi/D00CIN0noT65vo2+7tNEe3rKxzMv/EXlGJLHq/kcGMF2fcfKLo5SKM19JsYGwD1wXUiD7JPHPv2C9tWQ7/pyaquWV52IBBd7lFp1KX3r94yX51Xgt4sBB2d/65j4vknmPzFJj7FEuQnrxFM0H76kE9FWX0WfxnSdqzYfeanAcfHs2JZtT9A/lmuUrcDb9xPwGey7OSsxIpNMi+sZL1OF1dSF3dMY7waHT/anAtbLeO8PJ/o9RqDRxziiT1YS9vWos4w6Dszi6bHY5MdYLqDZ2zW+tjtE/qTrbs7U52ntp4efsjtbO3Z1hEG3J8Qg31bTzlpu9g5T3RpFv4GLzEbtknp2k9WiQwdnt9jQT7TtOfqXrKy1b+e73+kL7qzWWTLPor7k+DJy7YFeJrPBsPnFpO/weRvk7nJ5zfjt0XjQB+2b+I+LHFOwq8GvxX4nYLfk/BbqMtgzt4h/PsyT8Xv6RYP/Lcb2nPwm6doruBP0+40bVph2tRlZL98HveTzBszu4B3qtpHRzp8M1/R37BJ9Q3p71HzaTvzgOfrenaYB52Scfgcr19S5rlIa117ntBDfXEf/EzhxZezetYr87f/Hlk1W3yMZ8028U5ojzbPi5+b+psqN5pQbq/oCPfrrG3FOxsKZ1ElcYwfdDZwdOyD1eosC+pm3BR7Vha3l5UM7vF4Zn9C8klHlUd+3uSj/lj5oso/44TxPuI+ycceAH4m/4Dpz+bZlAX7BH2BM7hxG3ueklejOoeux90LEnDmVZv9Ai2bY8ibWrN5oYxD2hzjB3McvtjIWNaGQjovQX7XxDaYC89dCFaX6mnavKNVDHBidvS9f4map3pnh7pxl7wFT51gzCP+tH5eRvkPK9+ZZdEO0Vn+pF0o+3IlY1f+I8rHH2ZfvVLJ5lL8PWz6/1Vq/O5l3qW0B682ZUdnx23Va2kvLlH24iovDyn3+k2GJ5S7WuiCZ/wMT2/kWLuJYy2APPV30ULzjljSd8s=
*/