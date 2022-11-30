/*
 [auto_generated]
  boost/numeric/odeint/iterator/detail/times_iterator_impl.hpp

  [begin_description]
  tba.
  [end_description]

  Copyright 2009-2013 Karsten Ahnert
  Copyright 2009-2013 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_ITERATOR_DETAIL_TIMES_ITERATOR_IMPL_HPP_DEFINED
#define BOOST_NUMERIC_ODEINT_ITERATOR_DETAIL_TIMES_ITERATOR_IMPL_HPP_DEFINED

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/throw_exception.hpp>

#include <boost/numeric/odeint/util/unit_helper.hpp>
#include <boost/numeric/odeint/util/copy.hpp>
#include <boost/numeric/odeint/stepper/controlled_step_result.hpp>
#include <boost/numeric/odeint/iterator/detail/ode_iterator_base.hpp>


namespace boost {
namespace numeric {
namespace odeint {


    template< class Iterator , class Stepper , class System , class State , class TimeIterator ,
              typename Tag , typename StepperTag >
    class times_iterator_impl;

    /*
     * Specilization for basic steppers
     */
    /**
     * \brief ODE Iterator with constant step size.
     *
     * Implements an ODE iterator with observer calls at predefined times.
     * Uses controlled steppers. times_iterator is a model of single-pass iterator.
     *
     * The value type of this iterator is the state type of the stepper. Hence one can only access the state and not the current time.
     *
     * \tparam Stepper The stepper type which should be used during the iteration.
     * \tparam System The type of the system function (ODE) which should be solved.
     */
    template< class Iterator , class Stepper , class System , class State , class TimeIterator , typename Tag >
    class times_iterator_impl< Iterator , Stepper , System , State , TimeIterator , Tag , stepper_tag >
        : public detail::ode_iterator_base< Iterator , Stepper , System , State , Tag >
    {
    private:


        typedef Stepper stepper_type;
        typedef System system_type;
        typedef typename boost::numeric::odeint::unwrap_reference< stepper_type >::type unwrapped_stepper_type;
        typedef State state_type;
        typedef TimeIterator time_iterator_type;
        typedef typename traits::time_type< stepper_type >::type time_type;
        typedef typename traits::value_type< stepper_type >::type ode_value_type;
        #ifndef DOXYGEN_SKIP
        typedef detail::ode_iterator_base< Iterator , Stepper , System , State , Tag > base_type;
        #endif

    public:

        /**
         * \brief Constructs a times_iterator. This constructor should be used to construct the begin iterator.
         *
         * \param stepper The stepper to use during the iteration.
         * \param sys The system function (ODE) to solve.
         * \param s The initial state. adaptive_iterator stores a reference of s and changes its value during the iteration.
         * \param t_start Iterator to the begin of a sequence of time values.
         * \param t_end Iterator to the begin of a sequence of time values.
         * \param dt The (initial) time step.
         */
        times_iterator_impl( stepper_type stepper , system_type sys , state_type &s ,
                             time_iterator_type t_start , time_iterator_type t_end , time_type dt )
            : base_type( stepper , sys , *t_start , dt ) ,
              m_t_start( t_start ) , m_t_end( t_end ) , m_state( &s )
        {
            if( t_start == t_end )
                this->m_at_end = true;
        }

        /**
         * \brief Constructs an adaptive_iterator. This constructor should be used to construct the end iterator.
         *
         * \param stepper The stepper to use during the iteration.
         * \param sys The system function (ODE) to solve.
         * \param s The initial state. adaptive_iterator store a reference of s and changes its value during the iteration.
         */
        times_iterator_impl( stepper_type stepper , system_type sys , state_type &s )
            : base_type( stepper , sys ) , m_state( &s ) { }

    protected:

        friend class boost::iterator_core_access;

        void increment()
        {
            unwrapped_stepper_type &stepper = this->m_stepper;
            if( ++m_t_start != m_t_end )
            {
                while( detail::less_with_sign( this->m_t , static_cast<time_type>(*m_t_start) , this->m_dt ) )
                {
                    const time_type current_dt = detail::min_abs( this->m_dt , static_cast<time_type>(*m_t_start) - this->m_t );
                    stepper.do_step( this->m_system , *( this->m_state ) , this->m_t , current_dt );
                    this->m_t += current_dt;
                }

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
        time_iterator_type m_t_start;
        time_iterator_type m_t_end;
        state_type* m_state;
    };



    /*
     * Specilization for controlled steppers
     */
    /**
     * \brief ODE Iterator with adaptive step size control. The value type of this iterator is the state type of the stepper.
     *
     * Implements an ODE iterator with observer calls at predefined times.
     * Uses controlled steppers. times_iterator is a model of single-pass iterator.
     *
     * The value type of this iterator is the state type of the stepper. Hence one can only access the state and not the current time.
     *
     * \tparam Stepper The stepper type which should be used during the iteration.
     * \tparam System The type of the system function (ODE) which should be solved.
     */
    template< class Iterator , class Stepper , class System , class State , class TimeIterator , typename Tag >
    class times_iterator_impl< Iterator , Stepper , System , State , TimeIterator , Tag , controlled_stepper_tag >
        : public detail::ode_iterator_base< Iterator , Stepper , System , State , Tag >
    {
    private:


        typedef Stepper stepper_type;
        typedef System system_type;
        typedef typename boost::numeric::odeint::unwrap_reference< stepper_type >::type unwrapped_stepper_type;
        typedef State state_type;
        typedef TimeIterator time_iterator_type;
        typedef typename traits::time_type< stepper_type >::type time_type;
        typedef typename traits::value_type< stepper_type >::type ode_value_type;
        #ifndef DOXYGEN_SKIP
        typedef detail::ode_iterator_base< Iterator , Stepper , System , State , Tag > base_type;
        #endif

    public:

        /**
         * \brief Constructs a times_iterator. This constructor should be used to construct the begin iterator.
         *
         * \param stepper The stepper to use during the iteration.
         * \param sys The system function (ODE) to solve.
         * \param s The initial state. adaptive_iterator stores a reference of s and changes its value during the iteration.
         * \param t_start Iterator to the begin of a sequence of time values.
         * \param t_end Iterator to the begin of a sequence of time values.
         * \param dt The (initial) time step.
         */
        times_iterator_impl( stepper_type stepper , system_type sys , state_type &s ,
                             time_iterator_type t_start , time_iterator_type t_end , time_type dt )
            : base_type( stepper , sys , *t_start , dt ) ,
              m_t_start( t_start ) , m_t_end( t_end ) , m_state( &s )
        {
            if( t_start == t_end )
                this->m_at_end = true;
        }

        /**
         * \brief Constructs an adaptive_iterator. This constructor should be used to construct the end iterator.
         *
         * \param stepper The stepper to use during the iteration.
         * \param sys The system function (ODE) to solve.
         * \param s The initial state. adaptive_iterator store a reference of s and changes its value during the iteration.
         */
        times_iterator_impl( stepper_type stepper , system_type sys , state_type &s )
            : base_type( stepper , sys ) , m_state( &s ) { }

    protected:

        friend class boost::iterator_core_access;

        void increment()
        {
            if( ++m_t_start != m_t_end )
            {
                while( detail::less_with_sign( this->m_t , static_cast<time_type>(*m_t_start) , this->m_dt ) )
                {
                    if( detail::less_with_sign( static_cast<time_type>(*m_t_start) - this->m_t , this->m_dt , this->m_dt ) )
                    {
                        // we want to end exactly at the time point
                        time_type current_dt = static_cast<time_type>(*m_t_start) - this->m_t;
                        step_loop( current_dt );
                    } else {
                        step_loop( this->m_dt );
                    }
                }

            } else {
                this->m_at_end = true;
            }
        }

    private:
        void step_loop( time_type &dt )
        {
            unwrapped_stepper_type &stepper = this->m_stepper;
            const size_t max_attempts = 1000;
            size_t trials = 0;
            controlled_step_result res = success;
            do
            {
                res = stepper.try_step( this->m_system , *( this->m_state ) , this->m_t , dt );
                ++trials;
            }
            while( ( res == fail ) && ( trials < max_attempts ) );
            if( trials == max_attempts )
            {
                BOOST_THROW_EXCEPTION( std::overflow_error( "Adaptive iterator : Maximal number of iterations reached. A step size could not be found." ) );
            }
        }

    public:
        const state_type& get_state() const
        {
            return *m_state;
        }


    private:
        time_iterator_type m_t_start;
        time_iterator_type m_t_end;
        state_type* m_state;
    };


    /*
     * Specilization for dense outputer steppers
     */
    /**
     * \brief ODE Iterator with step size control and dense output.
     * Implements an ODE iterator with adaptive step size control. Uses dense-output steppers.
     * times_iterator is a model of single-pass iterator.
     *
     * \tparam Stepper The stepper type which should be used during the iteration.
     * \tparam System The type of the system function (ODE) which should be solved.
     */
    template< class Iterator , class Stepper , class System , class State , class TimeIterator , typename Tag >
    class times_iterator_impl< Iterator , Stepper , System , State , TimeIterator , Tag , dense_output_stepper_tag >
        : public detail::ode_iterator_base< Iterator , Stepper , System , State , Tag >
    {
    private:


        typedef Stepper stepper_type;
        typedef System system_type;
        typedef typename boost::numeric::odeint::unwrap_reference< stepper_type >::type unwrapped_stepper_type;
        typedef State state_type;
        typedef TimeIterator time_iterator_type;
        typedef typename traits::time_type< stepper_type >::type time_type;
        typedef typename traits::value_type< stepper_type >::type ode_value_type;
        #ifndef DOXYGEN_SKIP
        typedef detail::ode_iterator_base< Iterator , Stepper , System , State , Tag > base_type;
        #endif


   public:


        /**
         * \brief Constructs a times_iterator. This constructor should be used to construct the begin iterator.
         *
         * \param stepper The stepper to use during the iteration.
         * \param sys The system function (ODE) to solve.
         * \param s The initial state.
         * \param t_start Iterator to the begin of a sequence of time values.
         * \param t_end Iterator to the begin of a sequence of time values.
         * \param dt The (initial) time step.
         */
        times_iterator_impl( stepper_type stepper , system_type sys , state_type &s ,
                             time_iterator_type t_start , time_iterator_type t_end , time_type dt )
            : base_type( stepper , sys , *t_start , dt ) ,
              m_t_start( t_start ) , m_t_end( t_end ) , m_final_time( *(t_end-1) ) ,
              m_state( &s )
        {
            if( t_start != t_end )
            {
                unwrapped_stepper_type &st = this->m_stepper;
                st.initialize( *( this->m_state ) , this->m_t , this->m_dt );
            } else {
                this->m_at_end = true;
            }
        }

        /**
         * \brief Constructs a times_iterator. This constructor should be used to construct the end iterator.
         *
         * \param stepper The stepper to use during the iteration.
         * \param sys The system function (ODE) to solve.
         * \param s The initial state.
         */
        times_iterator_impl( stepper_type stepper , system_type sys , state_type &s )
            : base_type( stepper , sys ) , m_state( &s ) { }

    protected:

        friend class boost::iterator_core_access;

        void increment()
        {
            unwrapped_stepper_type &st = this->m_stepper;
            if( ++m_t_start != m_t_end )
            {
                this->m_t = static_cast<time_type>(*m_t_start);
                while( detail::less_with_sign( st.current_time() , this->m_t , this->m_dt ) )
                {
                    // make sure we don't go beyond the last point
                    if( detail::less_with_sign( m_final_time-st.current_time() , st.current_time_step() , st.current_time_step() ) )
                    {
                        st.initialize( st.current_state() , st.current_time() , m_final_time-st.current_time() );
                    }
                    st.do_step( this->m_system );
                }
                st.calc_state( this->m_t , *( this->m_state ) );
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
        time_iterator_type m_t_start;
        time_iterator_type m_t_end;
        time_type m_final_time;
        state_type* m_state;
    };

} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_ITERATOR_DETAIL_TIMES_ITERATOR_IMPL_HPP_DEFINED

/* times_iterator_impl.hpp
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
*/