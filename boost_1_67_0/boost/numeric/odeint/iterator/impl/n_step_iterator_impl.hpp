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