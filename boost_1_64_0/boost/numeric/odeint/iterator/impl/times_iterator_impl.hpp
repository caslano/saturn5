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
IgJICK0oPpwoziMZFY7KSEjXWqXttGiKUQymJyZa04MZI/PX5jVHxANb8ckJ2fhG+azrIpLRq3axw+tcRSiPCNP3yYvQau0mm6hK3/taEzMS/RJ4jw5wT/e5lnOhO1hT0zO0sfvE5NR+Dp9fWzAkHQOstoyLSrGL325Pz/l1ZwScdLi1NhXSmBvpIQLCA6WEzXMmG5nngcpneWlxNT306R4YMnYgy4xUHhzAN2itceZ2+VKTlaxR77b5XKBxLkDbQMN8rqVokRGVGhsQHBAfF9MrOCNJV1ZYsv65YpPsQp9eFyg/92l3qfmZYU+vfXqN3iKjHxH25/VWGec72c5ni3un8dG3BCHSNkVJE4LO28viv2dM/hvvyL8CQ4hHzAHt3MBdOtezLtGxx7yutLL81/gmKvOWJfael/gt/87C9Z9NuPuLbN9JsDLJmEtJhqhtztEnMilZ+zdDGz9OM3I143xGEvt4RGn85M/XqabrHFx1vZE2liTzsovNzW+lDCmr8NmP2fIwrd2XmpvXCBrz9NPj47L2xZvK8xVqC27aHvyy/p+azml9/5ZIa1okrhiXGkftqmlMfFSqq771jWst27/m2kIc00nqmB7e3Na4nM/7+lR9xtt83/DX+Ed1OZbzO23L+VG2MRmFOtUVc57/or3RjSs3rbpxffULyM1WTNAgK4G9BW3+luZa678pvDCcxNFbfX1NMr32HJmOkjK9nmuZ5tDT3Aj2mS3OcX1EZJp2SyalDN0BuCvBGtNPf10O53ga4zI6l7pp9MsYl0E2xah43uIcRtHd2iMj1XY/tVC57ui2WR7/YhvaPKs/SVHk25kOn2Z/1r5Pd5/Rp3sO+tRG9um+uU//RjteBE8yNReMTLc533/ZH/wjO+p29NT2Hz7H9ntK23+Ua9vP1ptc2rytVTP/dZn9L2CYNhqY8cdz5JYq5fbkX5Xbi0Cx1OmmF5CfQ4z5n8gxZ3wz26Xi82z5jpHyVX1yK1+Hb30hOT+r5XVFXhOORYaHUqk0bdQake2IVk+QeaCT3v5IWHiszlObSxzKox835lTo499WKhqRSZLvtLc7KPfIk88tpWNeSodgE2e16HvrQntTbbnC3Ao8W46Pvyn3h8tneq+rqBoZwSsC48A5awo1zKpwMyb9+fdjfDfS3UNvxnOuoVXmvTZYhvxCbcxPe+zbWMDUxqrPaaNXLtroZddG8YJtLGhqo7dsY6Fs+rN7vd4mu2Oy9oI9SL5ttKfEC7anqAOZFTO1p9yzZVa/8fNlVr+xncxefsE2lnDQRhdTGys8R6/1n99G9/q08UXaFOrx5zaVNLWp/HPa5JaLNrnlXKcLp/bOWlodJ1jz104WUP50OKumVFraSnHZxzI+xhiMv8SRsqb2O73gO4Kz1b/8Eqw9kvS5wdqx0qZ3meY56N9hNeY5BKRkhMTq2OjEz/KaznOBjd7CyeHeVrHMJcsayePGDlm/fDlpy/ca5XxvdFRsZAwjmfqtT3/IO3V5VvSRObD8e5SpBlrJx5jHpJ1z5X/aHKfKUr5cxz3GOsyq/F3LdH+1HO6vrt9vzBusJedh/flaVdSQ19qfM8+nqqzNp+KFVTiu/fuq3ib2+9N+a8/3kW2S7+JZerv5nwyiiqid03tMXFrKiD7arqvnY77OkMufzxl9Li7b6ibbWv+pjJzM1xtz7LW5RMKFb8Zp9yPnIljVa/ydpVj0r/H7OhyLNPam5dMLyYmRtmlXhHVCdlQCc/PzKXW5blDWzdrzVOHOseQULsFzmwnteRb9ukhb1I/s012f+RoZw3m2iE1OI4WwvbeE0oDr5Gy+uJjAuIRArtHO5dWkJdprtknrqqse8rqG/Fs=
*/