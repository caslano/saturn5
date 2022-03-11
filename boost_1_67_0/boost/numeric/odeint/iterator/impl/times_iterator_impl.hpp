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