/*
  [auto_generated]
  boost/numeric/odeint/iterator/detail/n_step_iterator_impl.hpp

  [begin_description]
  tba.
  [end_description]

  Copyright 2009-2013 Karsten Ahnert
  Copyright 2009-2013 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_ITERATOR_DETAIL_N_STEP_ITERATOR_IMPL_HPP_DEFINED
#define BOOST_NUMERIC_ODEINT_ITERATOR_DETAIL_N_STEP_ITERATOR_IMPL_HPP_DEFINED

#include <boost/numeric/odeint/iterator/detail/ode_iterator_base.hpp>
#include <boost/numeric/odeint/util/unit_helper.hpp>



namespace boost {
namespace numeric {
namespace odeint {


    template< class Iterator , class Stepper , class System , class State , typename Tag , class StepperTag >
    class n_step_iterator_impl;


    /*
     * Specilization for steppers and error steppers
     */
    /**
     * \brief ODE Iterator performing exactly n steps with constant step size. The value type of this iterator is the state type of the stepper.
     *
     * Implements an ODE iterator solving the ODE with constant step size. Uses steppers fulfilling the Stepper concept.
     * n_step_iterator is a model of single-pass iterator.
     *
     * The value type of this iterator is the state type of the stepper. Hence one can only access the state and not the current time.
     *
     * \tparam Stepper The stepper type which should be used during the iteration.
     * \tparam System The type of the system function (ODE) which should be solved.
     */
    template< class Iterator , class Stepper , class System , class State , typename Tag >
    class n_step_iterator_impl< Iterator , Stepper , System , State , Tag , stepper_tag >
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
         * \brief Constructs a n_step_iterator. This constructor should be used to construct the begin iterator.
         *
         * \param stepper The stepper to use during the iteration.
         * \param sys The system function (ODE) to solve.
         * \param s The initial state. const_step_iterator stores a reference of s and changes its value during the iteration.
         * \param t The initial time.
         * \param dt The initial time step.
         * \param num_of_steps the number of steps to be executed.
         */
        n_step_iterator_impl( stepper_type stepper , system_type sys , state_type &s ,
                              time_type t , time_type dt , size_t num_of_steps )
            : base_type( stepper , sys , t , dt ) , m_t_start( t ) , m_state( &s ) ,
              m_steps(num_of_steps) , m_step( 0 )
        { }

        /**
         * \brief Constructs a const_step_iterator. This constructor should be used to construct the end iterator.
         *
         * \param stepper The stepper to use during the iteration.
         * \param sys The system function (ODE) to solve.
         * \param s The initial state. const_step_iterator stores a reference of s and changes its value during the iteration.
         */
        n_step_iterator_impl( stepper_type stepper , system_type sys , state_type &s )
            : base_type( stepper , sys ) , m_state( &s ) { }

    protected:

        friend class boost::iterator_core_access;

        void increment()
        {
            if( this->m_step < this->m_steps )
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
        size_t m_steps;
        size_t m_step;

    };




    /*
     * Specilization for dense output stepper
     */
    /**
     * \brief ODE Iterator with step-size control and dense output.
     *
     * Implements an ODE iterator solving the ODE with constant steps. Uses dense-output steppers.
     * n_step_iterator is a model of single-pass iterator.
     *
     * The value type of this iterator is the state type of the stepper. Hence one can only access the state and not the current time.
     *
     * \tparam Stepper The stepper type which should be used during the iteration.
     * \tparam System The type of the system function (ODE) which should be solved.
     */
    template< class Iterator , class Stepper , class System , class State , typename Tag >
    class n_step_iterator_impl< Iterator , Stepper , System , State , Tag , dense_output_stepper_tag >
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
         * \param dt The initial time step.
         * \param num_of_steps the number of steps to be executed.
         */
        n_step_iterator_impl( stepper_type stepper , system_type sys , state_type &s ,
                              time_type t , time_type dt , size_t num_of_steps )
            : base_type( stepper , sys , t , dt ) , m_t_start( t ) , m_state( &s ) ,
              m_steps( num_of_steps ) , m_step( 0 )
        {
            unwrapped_stepper_type &st = this->m_stepper;
            st.initialize( * ( this->m_state ) , this->m_t , this->m_dt );
        }

        /**
         * \brief Constructs a const_step_iterator. This constructor should be used to construct the end iterator.
         *
         * \param stepper The stepper to use during the iteration.
         * \param sys The system function (ODE) to solve.
         * \param s The initial state. const_step_iterator stores a reference of s and changes its value during the iteration.
         */
        n_step_iterator_impl( stepper_type stepper , system_type sys , state_type &s )
            : base_type( stepper , sys ) , m_state( &s )
        {
        }



    protected:

        friend class boost::iterator_core_access;

        void increment( void )
        {
            if( this->m_step < this->m_steps )
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
        size_t m_steps;
        size_t m_step;
    };

} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_ITERATOR_DETAIL_N_STEP_ITERATOR_IMPL_HPP_DEFINED

/* n_step_iterator_impl.hpp
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
*/