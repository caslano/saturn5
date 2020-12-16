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
X2cljMXJcuAH6GRr4vnd09z4vEjWKHu8n36k9yVc3h78jppWEZzux1ZSXrjWEfg1gRnel3k24O7fMxrC+JPVx4Z02V/3ufRupCkfDzsaEn8OYInsc+w5Go4Kbb2nUVmiQthqb0/6M30IIYqCXp4zgznTnqts46z/kTw3RzqV2ZzLuZCZAfU+04YopXsxaqj7mS3ZXLooYzbTkhvrzbp2Xgndq6TupZJ0bzCTHc3kY6B9a1K4gwi5HGJwJOA1jiOX0LTLJqeTk+PMC/VwOQl1Nm109kylsy6vlzrbxz5voA6eqXRwNuTej3QSh9Aj4IquufZPhw5llA5V/p/af/+0SMeaRg7uKsCEBtSx5lyzOyIisGmAdexsKwXI9RnUOfgTGZMRwnGOZmfGmfIQ6GHVDlYczPUr2CIpz0ypt1HySEzyLoz4VDnR2z+SR4qSNz2zNZvrTWeZpdsSVDLPvbmieAyqMkoixK0W3qLrtrrMajbHZPq8xkxby46duf6xbExm0y4MLkRv5EYODufGlPwr4fegX5xzinslcTj6ZtcIXENFB3B/tqkVt6HYPoFXwUbgjsJIpie915ZB/3T7U09sB+Guj3bk8LKvxUf/dOZzULbiwXH1XIj6ncWzZdA3PZnh0SyMqpSRPC0UgU/LtOF2894SB4S7/mpy4TAH87kRCMzQ+/cFz/S6DVGT3mWwiU+hTdw7SZs4hqIyuJgu2UMmGt2/UxyB5x+2LWRl2gwcRv3+rXtv/8TmufRZtHmPci6up80bBLzUdmfzzmZaqpW4rAHPuZ9Pe5edsr17bNq4nfMobk/ioH1xGOpIe1bAI7DZjMyb/hIO1x1GMmNF3KaP1hl6c+6dpH3QnSOoOyNJulMczONQPuiKsgispDAK0GgLJPtxvZPTE0uMQptcHU4XRs1cmFNzocs7h3qRZ1+avET/rUD/rYh/N1OPHF0tFuevjWlYXJ+AL/rkZFEJfdqn9ekxloX65oDHlueciOAKuf3w7mmnkd6fPoh7G/FvjgNJepHeuzcP01VM92YP4VYpzMfEt7f0RBSTrYm+/blGNw4q3XB551E3ns9+MXmJuvEC6sb5ohugS7+KfvwFSGtWrR9/UPlWZ1E3LtS68T+Syb7JfWciWnxmCDo0mS9Ng5vc7yOT63dLUbdy8rWx71/s+172IV6E9GrVxy7/It/HOL9D2VNPgGvwqCeXEM/kUU+YRz25mHpyKf99Kf59HvXlRVpf0COXIW0bqH3xF5nvvtXhueL0QVwtTiHUXsZHhgvlPAO69DKlS1X/Qzk/O5qn+rPZyMZkDmT493T/Ts9QH9PgeWwEqw19QwNDyia17mmN8N0Lk23NLj3g1l+oqy9P0tVheFyHskwGJ0k3nzc53RRKIqtDU6cuvpK6uBn6dTSovwLp2dXxWHarA/nbwvEjTHTP0bzC697RwauM/oJ+Ah7OWxHP5CXq75XU29fw39fi396KUH9fYfT3dUiLMERvgaf11vNf6e8WSrpKx+AgbFYwNjbUr9+iyPaV0qt5B3qkmM9lVZn5gfOsCqh+ZG/8DrTAXSn3KEepzCKVBw2O4Es9HA+aZISHEz2MFFjvah9jcnCov593nAlbibczHFV/DUPdR1jN90U0bC1ww8WV8Kqo08djMIavUmO47jHUxw/JfX0Xws3tFrXI+iRgLW3dIZDj08G6d3Xi6j42wPherIN1te7s6GntBrSttA9V5eA7d+3oadsJUFi+2sHaO7pb27s7ughbFMJ6PN2Orh6Q9fBGX39H86ms50KX3tGEVfbOYJXaw7q6wZ/2R6a/ys8hLwA3rjfH3slxH8ayF1Lp0zVReoZPnxyU1sGrfHptsIw=
*/