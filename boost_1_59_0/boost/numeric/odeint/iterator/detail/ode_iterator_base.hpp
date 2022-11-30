
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
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
*/