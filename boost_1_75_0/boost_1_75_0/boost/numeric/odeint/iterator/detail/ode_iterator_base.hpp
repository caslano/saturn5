
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
2gake8p8CJTFQXvV+y+wzpJGKR44DKU5UFmU7Cjw3azW/B0uhhUX602QWAunHGvQ2tnZBK3KvkkiKf93ZnypNgnwabN7QPwMFjttKJ8HH9aAL0eAFoIiWsZ3p9Yp8UKbkF4hm1t/DTC8chAvPDXDf5n9Hy3wIK9q47V2BhAFibs0/fmsspLXocPrk+0tpdR09difV1+QQ89SWtRP0VWcOgP0VAXkQUdoMt6uUP5DZ8xfQ4W45DvBBy9G6KDZuvlOLr3xn8HhpnV1Ng7axhdtcyF3T/J+2vt7D6d9g97hET6WfC4jGv2PB6lCtrpavHlQGB+Qv7MYvHUnzFKFXHh21s2+4dooKErrFKUfrSrBWXXW2Kxi/D+9XZUTpE7txAZ5cu3Fwu8AaRRNlI2SSIVlLohYbkkhXnuC3zvlL4u+MqWYjPXmDzG8YDEj01j511QSje3iJO85Z+A5Y+cduSS5QmWIc7sMI953J48ycFQOabRAvKjtDGiuqYOVgruV3tizQpxLWRkpYoGEqm2D8FqtOW4WLxmTHyC+nDoStiQDofOmSpgZAZVZziPmz3Crgso/rldF/vtsIHLrQbmWxaPoXrDOkOnwXXrbuZxH7cNmw8Mv9x/QNdB9rbHX8vPD+CtevVvZux2G//wObc+4OGh/+I5xcfOXsNYfXefmED+2yNFa2LLygM9fCK/uQu6M3mLwNiqryh3rI1517h/C
*/