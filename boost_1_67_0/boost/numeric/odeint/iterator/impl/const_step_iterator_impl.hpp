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