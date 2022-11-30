/*
 [auto_generated]
  boost/numeric/odeint/iterator/detail/adaptive_iterator_impl.hpp

  [begin_description]
  tba.
  [end_description]

  Copyright 2009-2012 Karsten Ahnert
  Copyright 2009-2012 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_ITERATOR_DETAIL_ADAPTIVE_ITERATOR_IMPL_HPP_DEFINED
#define BOOST_NUMERIC_ODEINT_ITERATOR_DETAIL_ADAPTIVE_ITERATOR_IMPL_HPP_DEFINED

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


    template< class Iterator , class Stepper , class System , class State , typename Tag , typename StepperTag >
    class adaptive_iterator_impl;

    /*
     * Specilization for controlled steppers
     */
    /**
     * \brief ODE Iterator with adaptive step size control. The value type of this iterator is the state type of the stepper.
     *
     * Implements an ODE iterator with adaptive step size control. Uses controlled steppers. adaptive_iterator is a model
     * of single-pass iterator.
     *
     * The value type of this iterator is the state type of the stepper. Hence one can only access the state and not the current time.
     *
     * \tparam Stepper The stepper type which should be used during the iteration.
     * \tparam System The type of the system function (ODE) which should be solved.
     */
    template< class Iterator , class Stepper , class System , class State , typename Tag >
    class adaptive_iterator_impl< Iterator , Stepper , System , State , Tag , controlled_stepper_tag >
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
         * \brief Constructs an adaptive_iterator. This constructor should be used to construct the begin iterator.
         *
         * \param stepper The stepper to use during the iteration.
         * \param sys The system function (ODE) to solve.
         * \param s The initial state. adaptive_iterator stores a reference of s and changes its value during the iteration.
         * \param t The initial time.
         * \param t_end The end time, at which the iteration should stop.
         * \param dt The initial time step.
         */
        adaptive_iterator_impl( stepper_type stepper , system_type sys , state_type &s , time_type t , time_type t_end , time_type dt )
            : base_type( stepper , sys , t , dt ) , m_t_end( t_end ) , m_state( &s )
        {
            if( detail::less_with_sign( this->m_t_end , this->m_t , this->m_dt ) )
                this->m_at_end = true;
        }

        /**
         * \brief Constructs an adaptive_iterator. This constructor should be used to construct the end iterator.
         *
         * \param stepper The stepper to use during the iteration.
         * \param sys The system function (ODE) to solve.
         * \param s The initial state. adaptive_iterator store a reference of s and changes its value during the iteration.
         */
        adaptive_iterator_impl( stepper_type stepper , system_type sys , state_type &s )
            : base_type( stepper , sys ) , m_state( &s ) { }

    protected:

        friend class boost::iterator_core_access;

        void increment()
        {
            if( detail::less_with_sign( this->m_t , this->m_t_end , this->m_dt) )
            {
                if( detail::less_with_sign( this->m_t_end ,
                                            static_cast<time_type>(this->m_t + this->m_dt) ,
                                            this->m_dt ) )
                {
                    this->m_dt = this->m_t_end - this->m_t;
                }
                unwrapped_stepper_type &stepper = this->m_stepper;
                const size_t max_attempts = 1000;
                size_t trials = 0;
                controlled_step_result res = success;
                do
                {
                    res = stepper.try_step( this->m_system , *( this->m_state ) , this->m_t , this->m_dt );
                    ++trials;
                }
                while( ( res == fail ) && ( trials < max_attempts ) );
                if( trials == max_attempts )
                {
                    BOOST_THROW_EXCEPTION( std::overflow_error( "Adaptive iterator : Maximal number of iterations reached. A step size could not be found." ));
                }
            } else {
                this->m_at_end = true;
            }
        }
    public:
        const state_type& get_state() const
        {
            return *this->m_state;
        }

    private:
        time_type m_t_end;
        state_type* m_state;
    };



    /*
     * Specilization for dense outputer steppers
     */
    /**
     * \brief ODE Iterator with adaptive step size control. The value type of this iterator is the state type of the stepper.
     *
     * Implements an ODE iterator with adaptive step size control. Uses dense-output steppers. adaptive_iterator is a model
     * of single-pass iterator.
     *
     * The value type of this iterator is the state type of the stepper. Hence one can only access the state and not the current time.
     *
     * \tparam Stepper The stepper type which should be used during the iteration.
     * \tparam System The type of the system function (ODE) which should be solved.
     */
    template< class Iterator , class Stepper , class System , class State , typename Tag >
    class adaptive_iterator_impl< Iterator , Stepper , System , State , Tag , dense_output_stepper_tag >
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
         * \brief Constructs an adaptive_iterator. This constructor should be used to construct the begin iterator.
         *
         * \param stepper The stepper to use during the iteration.
         * \param sys The system function (ODE) to solve.
         * \param s The initial state.
         * \param t The initial time.
         * \param t_end The end time, at which the iteration should stop.
         * \param dt The initial time step.
         */
        adaptive_iterator_impl( stepper_type stepper , system_type sys , state_type &s , time_type t , time_type t_end , time_type dt )
            : base_type( stepper , sys , t , dt ) , m_t_end( t_end )
        {
            if( detail::less_eq_with_sign( this->m_t , this->m_t_end , this->m_dt ) )
            {
                unwrapped_stepper_type &st = this->m_stepper;
                st.initialize( s , this->m_t , this->m_dt );
            } else {
                this->m_at_end = true;
            }
        }

        /**
         * \brief Constructs an adaptive_iterator. This constructor should be used to construct the end iterator.
         *
         * \param stepper The stepper to use during the iteration.
         * \param sys The system function (ODE) to solve.
         * \param s The initial state.
         */
        adaptive_iterator_impl( stepper_type stepper , system_type sys , state_type& /* s */ )
            : base_type( stepper , sys ) { }

    protected:

        friend class boost::iterator_core_access;

        void increment()
        {
            unwrapped_stepper_type &stepper = this->m_stepper;
            if( detail::less_with_sign( this->m_t ,
                                        this->m_t_end ,
                                        stepper.current_time_step() ) )
            {
                if( detail::less_with_sign( this->m_t_end ,
                                            static_cast<time_type>(this->m_t + stepper.current_time_step()) ,
                                            stepper.current_time_step() ) )
                {
                    // make stpper to end exactly at t_end
                    stepper.initialize( stepper.current_state() , stepper.current_time() ,
                                        static_cast<time_type>(this->m_t_end-this->m_t) );
                }
                stepper.do_step( this->m_system );
                this->m_t = stepper.current_time();
            } else { // we have reached t_end
                this->m_at_end = true;
            }
        }

    public:
        const state_type& get_state() const
        {
            const unwrapped_stepper_type &stepper = this->m_stepper;
            return stepper.current_state();
        }

    private:
        time_type m_t_end;
    };

} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_ITERATOR_DETAIL_ADAPTIVE_ITERATOR_IMPL_HPP_DEFINED

/* adaptive_iterator_impl.hpp
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
*/