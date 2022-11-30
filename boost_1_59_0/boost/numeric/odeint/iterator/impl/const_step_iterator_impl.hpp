/*
  [auto_generated]
  boost/numeric/odeint/iterator/detail/const_step_iterator_impl.hpp

  [begin_description]
  tba.
  [end_description]

  Copyright 2013 Karsten Ahnert
  Copyright 2013 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_ITERATOR_DETAIL_CONST_STEP_ITERATOR_IMPL_HPP_DEFINED
#define BOOST_NUMERIC_ODEINT_ITERATOR_DETAIL_CONST_STEP_ITERATOR_IMPL_HPP_DEFINED

#include <boost/numeric/odeint/iterator/detail/ode_iterator_base.hpp>
#include <boost/numeric/odeint/util/unit_helper.hpp>



namespace boost {
namespace numeric {
namespace odeint {


    template< class Iterator , class Stepper , class System , class State , typename Tag , class StepperTag >
    class const_step_iterator_impl;


    /*
     * Specilization for steppers and error steppers
     */
    template< class Iterator , class Stepper , class System , class State , typename Tag >
    class const_step_iterator_impl< Iterator , Stepper , System , State , Tag , stepper_tag >
        : public detail::ode_iterator_base< Iterator , Stepper , System , State , Tag >
    {
    private:

        typedef Stepper stepper_type;
        typedef System system_type;
        typedef typename boost::numeric::odeint::unwrap_reference< stepper_type >::type unwrapped_stepper_type;
        typedef State state_type;
        typedef typename traits::time_type< stepper_type >::type time_type;
        typedef typename traits::value_type< stepper_type >::type ode_value_type;
        #ifndef DOXYGEN_SKIP
        typedef detail::ode_iterator_base< Iterator , Stepper , System , State , Tag > base_type;
        #endif

    public:
   
        /**
         * \brief Constructs a const_step_iterator. This constructor should be used to construct the begin iterator.
         *
         * \param stepper The stepper to use during the iteration.
         * \param sys The system function (ODE) to solve.
         * \param s The initial state. const_step_iterator stores a reference of s and changes its value during the iteration.
         * \param t The initial time.
         * \param t_end The end time, at which the iteration should stop.
         * \param dt The initial time step.
         */
        const_step_iterator_impl( stepper_type stepper , system_type sys , state_type &s , time_type t , time_type t_end , time_type dt )
            : base_type( stepper , sys , t , dt ) , m_t_start( t ) , m_t_end( t_end ) , m_state( &s ) , m_step( 0 )
        {
            if( detail::less_with_sign( this->m_t_end , this->m_t , this->m_dt ) )
                this->m_at_end = true;
        }

        /**
         * \brief Constructs a const_step_iterator. This constructor should be used to construct the end iterator.
         *
         * \param stepper The stepper to use during the iteration.
         * \param sys The system function (ODE) to solve.
         * \param s The initial state. const_step_iterator stores a reference of s and changes its value during the iteration.
         */
        const_step_iterator_impl( stepper_type stepper , system_type sys , state_type& /* s */ )
            : base_type( stepper , sys ) { }

    protected:

        friend class boost::iterator_core_access;

        void increment()
        {
            if( detail::less_eq_with_sign( static_cast<time_type>(this->m_t+this->m_dt) ,
                                           this->m_t_end , this->m_dt ) )
            {
                unwrapped_stepper_type &stepper = this->m_stepper;
                stepper.do_step( this->m_system , *this->m_state , this->m_t , this->m_dt );
                // use integer to compute current time to reduce roundoff errors
                this->m_step++;
                this->m_t = this->m_t_start + static_cast< typename unit_value_type<time_type>::type >(this->m_step)*this->m_dt;
            } else {
                this->m_at_end = true;
            }
        }

    public:
        const state_type& get_state() const
        {
            return *m_state;
        }

    private:
        time_type m_t_start;
        time_type m_t_end;
        state_type* m_state;
        size_t m_step;

    };



    /*
     * Specilization for dense output stepper
     */
    /**
     * \brief ODE Iterator with constant step size. The value type of this iterator is the state type of the stepper.
     *
     * Implements an ODE iterator solving the ODE with constant steps. Uses dense-output steppers.
     * const_step_iterator is a model of single-pass iterator.
     *
     * The value type of this iterator is the state type of the stepper. Hence one can only access the state and not the current time.
     *
     * \tparam Stepper The stepper type which should be used during the iteration.
     * \tparam System The type of the system function (ODE) which should be solved.
     */
    template< class Iterator , class Stepper , class System , class State , typename Tag >
    class const_step_iterator_impl< Iterator , Stepper , System , State , Tag , dense_output_stepper_tag >
        : public detail::ode_iterator_base< Iterator , Stepper , System , State , Tag >
    {
    private:

        typedef Stepper stepper_type;
        typedef System system_type;
        typedef typename boost::numeric::odeint::unwrap_reference< stepper_type >::type unwrapped_stepper_type;
        typedef State state_type;
        typedef typename traits::time_type< stepper_type >::type time_type;
        typedef typename traits::value_type< stepper_type >::type ode_value_type;
        #ifndef DOXYGEN_SKIP
        typedef detail::ode_iterator_base< Iterator , Stepper , System , State , Tag > base_type;
        #endif

    public:

        /**
         * \brief Constructs a const_step_iterator. This constructor should be used to construct the begin iterator.
         *
         * \param stepper The stepper to use during the iteration.
         * \param sys The system function (ODE) to solve.
         * \param s The initial state. const_step_iterator stores a reference of s and changes its value during the iteration.
         * \param t The initial time.
         * \param t_end The end time, at which the iteration should stop.
         * \param dt The initial time step.
         */
        const_step_iterator_impl( stepper_type stepper , system_type sys , state_type &s , time_type t , time_type t_end , time_type dt )
            : base_type( stepper , sys , t , dt ) , m_t_start( t ) , m_t_end( t_end ) , m_state( &s ) , m_step( 0 )
        {
            if( detail::less_eq_with_sign( this->m_t , this->m_t_end , this->m_dt ) )
            {
                unwrapped_stepper_type &st = this->m_stepper;
                st.initialize( * ( this->m_state ) , this->m_t , this->m_dt );
            } else {
                this->m_at_end = true;
            }
        }

        /**
         * \brief Constructs a const_step_iterator. This constructor should be used to construct the end iterator.
         *
         * \param stepper The stepper to use during the iteration.
         * \param sys The system function (ODE) to solve.
         * \param s The initial state. const_step_iterator stores a reference of s and changes its value during the iteration.
         */
        const_step_iterator_impl( stepper_type stepper , system_type sys , state_type &s )
            : base_type( stepper , sys ) , m_state( &s )
        {
        }



    protected:

        friend class boost::iterator_core_access;

        void increment( void )
        {
            if( detail::less_eq_with_sign( static_cast<time_type>(this->m_t+this->m_dt) ,
                                           this->m_t_end , this->m_dt ) )
            {
                unwrapped_stepper_type &stepper = this->m_stepper;
                // use integer to compute current time to reduce roundoff errors
                this->m_step++;
                this->m_t = this->m_t_start + static_cast< typename unit_value_type<time_type>::type >(this->m_step)*this->m_dt;
                while( detail::less_with_sign( stepper.current_time() , this->m_t ,
                       stepper.current_time_step() ) )
                {
                    stepper.do_step( this->m_system );
                }
                stepper.calc_state( this->m_t , *( this->m_state ) );
            } else {
                this->m_at_end = true;
            }
        }

    public:
        const state_type& get_state() const
        {
            return *m_state;
        }

    private:
        time_type m_t_start;
        time_type m_t_end;
        state_type* m_state;
        size_t m_step;
    };

} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_ITERATOR_DETAIL_CONST_STEP_ITERATOR_IMPL_HPP_DEFINED

/* const_step_iterator_impl.hpp
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
*/