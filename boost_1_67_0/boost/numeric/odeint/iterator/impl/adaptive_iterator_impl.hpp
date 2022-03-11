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