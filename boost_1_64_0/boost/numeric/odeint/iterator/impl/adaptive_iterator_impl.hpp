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
W7RsqkO9sGP6OoVzw9xknLeZ7wE7vm4QHfX1vHW2tR+MPSJ4qKs83k20c9d6OXJ+MWcyTuB38Ls22T0xxB2RelBWcOyYuTmyvfRjDE2to7cApteljhLbR/zkPcNbRb7EG99PHxQ+iGNlI3x8GPmmXo9j2/ZRmZc5r5i5hfditNw+jjL0cRLLNBof5zb2UyvnI9bH+UjPScn13bHJnL1bJml+y6vvbtoBI7vPgoY9t2N9rRW0FZ/fxLS9T2TK2T78kurDI8xdjBW0MV9RY2Rrwl2Jr20y6zfE0235xqYku5esB9+S/k3AFXur5f0dI+8UEH3sCvN9o2ndmTAWvk86jr5dYznGjDO/RmjqvenJkjbzO8rKW+nuX79GqPKXJNC/y/gHSwITW1zl4ywncOJz469lTIH/8uc4f6v6cInC0334e7Z1TN4oZhmRjdXhPxm6STh/ERzxtQzOPQZnSQLOfYJDWQsO/vY4DwgO5WXmXeD8bZMZO5SHfX/+IYW3hHgyfkS2/xA8LX+OI6H3sPFTk9r4aIw3obfIxDr6t9DyNmuYMTM1rYoGjRPOWzYm33SFcw/pWJwjDE4SnZkN4Rxz7hPDMbwUc4yue+3TWEbFTn9cg/YfbT5ilzfo74TQBo9yrrLxNp6gcO8h7vQyuNUNIuNryNswY3NI/ZXBnAQ813aLN7dBpSkvpikb3pM9dvybCfORp8f7cVrWZeaN47XcqN+axpMVjZPKnPVZaHCSYu6fQL5vMO+nLQEcfIl+Gvu+tMHG/wpxPrAyOV7YMupOyb+udrrDdb8TG+RuCNal/LsqTwdMxR7JFFL+7DM36VVaziZbPvALYdDX2Pf9MybmnfjC+0rgJ66XHYIv/75vg9rfl/pQl62nMlhDGV18HGPoq/Gly+lvuLWqj9lW9F28j2uRtjKyfWVlVOf4riidS0ql2rqbUk27m9p2uC+r1J662ij2uc3r7m6tYVztpLy1NTyfZPLw1x7SrLR5uCezBV92W5l/RFJZ1hmMz+vaiSDmyby2t3a0k9fEPFe4dm3wQHjG6UiecaqHbBRu2462ntMZtNtAwzNOyffVsGKI6Orh2auWVpyBb+vs6Qh3wBOzZA98Y4N8zzaq8eTXPkz6GJX+EMdbgx9bw2tq6lIDJ0NuDla3PIKNocUe9qt1EWyojuvvz2wQ2JraEC/9FIGV6DUqPNDj2/9SR4neSxWsRG/mUwXm6C0OZjjZL2tqCOPiuRwfXjn808tlJPa+YCf2LPRdW39lIkrPCroyPuJlP88PelgPtkIk/fgIZ00gb/2WYDXBdp4xbNZ26jD79EWxuIFt/dG9YW/pS6HKBTY9aB5M4+WzrIJV8n1lpjFGOkb7EKku/uZxT7pwtrwbXxWcmjm4P5fHnlb0Nm1rUntsUyy0XIy+KZT3cbVRN9cx8besV7Ql6HuV1nemPxTTgeHatU6VKaNTGwhzKk9YYT1hTr0ppx0RHtSbeNeBIGFhWcZuJCyq451Lo3ojegPVESyi99DyCObpPYX6vbMhjAeJHKo3/uK+i2NhOvf9Hloqb7W/IYhsdFdPc6p526ndPaeKbfaw3V09eAGyu9u/YMa8aczr6Ora1dnjznM2nxq9dxDm7Wpva29zJZubdqR2dbcGtM2qHF4yaNrhEALaZZfXtmNH69amHYG3mTNoM5/VQA5b8/lcvn1suDeTD22mhYY2c1XUrhFca9qXAYxt6ssNR20YTo+k9/p92jzqwi63r6vb1ZXa15dKF4t5PFGC91/q6zE6cPy6gDe++zJNhOPNULcBmuJbbeHfjYmYjYZgo3+vtsRjYTQDLjx/fIfvXPAzjfzsmgI/uVG8ZQoKJZ6YnhI=
*/