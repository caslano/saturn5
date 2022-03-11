
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