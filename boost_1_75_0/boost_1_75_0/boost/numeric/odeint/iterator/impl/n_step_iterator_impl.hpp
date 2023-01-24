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
UXBi5w+rcOSuDS3DU3c9+kfpiatnKxeUzaYTTON3WmZeHJBooy1O+nPW/owF33uqc6eEAgaLblbdJfwwLDT0AumHHzU4NaiQ92bkZns/6j5FkZh3bWbkT8pNA6OQ7lyNARtbyKk74/b513qPuEnXWJUx9+MwdtSI0dEHBwbel2PZD+JvWLrTdYzDO3KD3uVO553lvX7x4dQLNP2goq5hp4ZxU0XZl5Iw8Q+jGELH3vKjEOMS8FRmtJ/jQqYjl/zqQOr19AUeWWNEB/bPVNk1A5N5XI8xnqf3oDKp/fSp3GptzLtnMXl63LoHVsO7lf3AO4GeyYMKJq87s5YDAE8Bt9rTBss/ep1+t6N3AOsQ34MsMOyFV/LeRDTV895cKHI4d1X31R61nKlMe8H5G4p3HYfcPpOMkJuOpWVpSf6OySRAf8k5njNJ4yoWY4GaTO+bWqRK9kaXsNvUP/+VV/jHYUie30eAXT7Lm7x8Td3/SBnZBQgKeDVKMTHzuPAgqW73jnAEM6VurBKQRTFEq/PiE1HY68XlVYLlj9nSBf9im+KGMTDp5U2rTGvHs2K/Id0bfwtL5rb1xz9c6Zf3szYDH9Z+tH7bQpjKxqf7jzzDnNPjfxGuZL/o+mKSGPGZp9lf5sK7VJTGS3YyWe7o4R/d7PpaoWJ9orlOZL4PPOP0Z+RQkfnsYfJ9zFei8uGgwCr/7dbGbdgHjVnpn+2S
*/