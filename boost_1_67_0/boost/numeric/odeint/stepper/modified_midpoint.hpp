/*
 [auto_generated]
 boost/numeric/odeint/stepper/modified_midpoint.hpp

 [begin_description]
 Modified midpoint method for the use in Burlish-Stoer stepper.
 [end_description]

 Copyright 2011-2013 Mario Mulansky
 Copyright 2011-2013 Karsten Ahnert
 Copyright 2012 Christoph Koke

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_MODIFIED_MIDPOINT_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_MODIFIED_MIDPOINT_HPP_INCLUDED

#include <vector>

#include <boost/numeric/odeint/stepper/base/explicit_stepper_base.hpp>
#include <boost/numeric/odeint/util/resizer.hpp>
#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/algebra/range_algebra.hpp>
#include <boost/numeric/odeint/algebra/default_operations.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>
#include <boost/numeric/odeint/algebra/operations_dispatcher.hpp>
#include <boost/numeric/odeint/util/copy.hpp>

namespace boost {
namespace numeric {
namespace odeint {

template<
class State ,
class Value = double ,
class Deriv = State ,
class Time = Value ,
class Algebra = typename algebra_dispatcher< State >::algebra_type ,
class Operations = typename operations_dispatcher< State >::operations_type ,
class Resizer = initially_resizer
>
#ifndef DOXYGEN_SKIP
class modified_midpoint
: public explicit_stepper_base<
  modified_midpoint< State , Value , Deriv , Time , Algebra , Operations , Resizer > ,
  2 , State , Value , Deriv , Time , Algebra , Operations , Resizer >
#else
class modified_midpoint : public explicit_stepper_base
#endif
{

public :

    typedef explicit_stepper_base<
    modified_midpoint< State , Value , Deriv , Time , Algebra , Operations , Resizer > ,
    2 , State , Value , Deriv , Time , Algebra , Operations , Resizer > stepper_base_type;

    typedef typename stepper_base_type::state_type state_type;
    typedef typename stepper_base_type::wrapped_state_type wrapped_state_type;
    typedef typename stepper_base_type::value_type value_type;
    typedef typename stepper_base_type::deriv_type deriv_type;
    typedef typename stepper_base_type::wrapped_deriv_type wrapped_deriv_type;
    typedef typename stepper_base_type::time_type time_type;
    typedef typename stepper_base_type::algebra_type algebra_type;
    typedef typename stepper_base_type::operations_type operations_type;
    typedef typename stepper_base_type::resizer_type resizer_type;
    typedef typename stepper_base_type::stepper_type stepper_type;


    modified_midpoint( unsigned short steps = 2 , const algebra_type &algebra = algebra_type() )
    : stepper_base_type( algebra ) , m_steps( steps )
    { }

    template< class System , class StateIn , class DerivIn , class StateOut >
    void do_step_impl( System system , const StateIn &in , const DerivIn &dxdt , time_type t , StateOut &out , time_type dt )
    {
        static const value_type val1 = static_cast< value_type >( 1 );
        static const value_type val05 = static_cast< value_type >( 1 ) / static_cast< value_type >( 2 );

        m_resizer.adjust_size( in , detail::bind( &stepper_type::template resize_impl< StateIn > , detail::ref( *this ) , detail::_1 ) );

        const time_type h = dt /  static_cast<value_type>( m_steps );
        const time_type h2 = static_cast<value_type>(2) * h;

        typename odeint::unwrap_reference< System >::type &sys = system;

        time_type th = t + h;

        // m_x1 = x + h*dxdt
        stepper_base_type::m_algebra.for_each3( m_x1.m_v , in , dxdt ,
                typename operations_type::template scale_sum2< value_type , time_type >( val1 , h ) );

        sys( m_x1.m_v , m_dxdt.m_v , th );

        boost::numeric::odeint::copy( in , m_x0.m_v );

        unsigned short i = 1;
        while( i != m_steps )
        {
            // general step
            //tmp = m_x1; m_x1 = m_x0 + h2*m_dxdt; m_x0 = tmp
            stepper_base_type::m_algebra.for_each3( m_x1.m_v , m_x0.m_v , m_dxdt.m_v ,
                    typename operations_type::template scale_sum_swap2< value_type , time_type >( val1 , h2 ) );
            th += h;
            sys( m_x1.m_v , m_dxdt.m_v , th);
            i++;
        }

        // last step
        // x = 0.5*( m_x0 + m_x1 + h*m_dxdt )
        stepper_base_type::m_algebra.for_each4( out , m_x0.m_v , m_x1.m_v , m_dxdt.m_v ,
                typename operations_type::template scale_sum3< value_type , value_type , time_type >( val05 , val05 , val05*h ) );
    }


    void set_steps( unsigned short steps )
    {   m_steps = steps; }


    unsigned short steps( void ) const
    {   return m_steps; }


    template< class StateIn >
    void adjust_size( const StateIn &x )
    {
        resize_impl( x );
        stepper_base_type::adjust_size( x );
    }

private:

    template< class StateIn >
    bool resize_impl( const StateIn &x )
    {
        bool resized( false );
        resized |= adjust_size_by_resizeability( m_x0 , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_x1 , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_dxdt , x , typename is_resizeable<deriv_type>::type() );
        return resized;
    }


    unsigned short m_steps;

    resizer_type m_resizer;

    wrapped_state_type m_x0;
    wrapped_state_type m_x1;
    wrapped_deriv_type m_dxdt;

};


/* Modified midpoint which stores derivatives and state at dt/2 in some external storage for later usage in dense output calculation
 * This Stepper is for use in Bulirsch Stoer only. It DOES NOT meet any stepper concept.
 */
template<
class State ,
class Value = double ,
class Deriv = State ,
class Time = Value ,
class Algebra = typename algebra_dispatcher< State >::algebra_type ,
class Operations = typename operations_dispatcher< State >::operations_type ,
class Resizer = initially_resizer
>
class modified_midpoint_dense_out
{

public :

    typedef State state_type;
    typedef Value value_type;
    typedef Deriv deriv_type;
    typedef Time time_type;
    typedef Algebra algebra_type;
    typedef Operations operations_type;
    typedef Resizer resizer_type;
    typedef state_wrapper< state_type > wrapped_state_type;
    typedef state_wrapper< deriv_type > wrapped_deriv_type;

    typedef modified_midpoint_dense_out< State , Value , Deriv , Time , Algebra , Operations , Resizer > stepper_type;
    typedef std::vector< wrapped_deriv_type > deriv_table_type;

    modified_midpoint_dense_out( unsigned short steps = 2 , const algebra_type &algebra = algebra_type() )
    : m_algebra( algebra ) , m_steps( steps )
    { }

    /*
     * performs a modified midpoint step with m_steps intermediate points
     * stores approximation for x(t+dt/2) in x_mp and all evaluated function results in derivs
     *
     */

    template< class System , class StateIn , class DerivIn , class StateOut >
    void do_step( System system , const StateIn &in , const DerivIn &dxdt , time_type t , StateOut &out , time_type dt ,
            state_type &x_mp , deriv_table_type &derivs )
    {

        static const value_type val1 = static_cast< value_type >( 1 );
        static const value_type val05 = static_cast< value_type >( 1 ) / static_cast< value_type >( 2 );

        m_resizer.adjust_size( in , detail::bind( &stepper_type::template resize< StateIn > , detail::ref( *this ) , detail::_1 ) );

        const time_type h = dt / static_cast<value_type>( m_steps );
        const time_type h2 = static_cast<value_type>( 2 ) * h;

        typename odeint::unwrap_reference< System >::type &sys = system;

        time_type th = t + h;

        // m_x1 = x + h*dxdt
        m_algebra.for_each3( m_x1.m_v , in , dxdt ,
                typename operations_type::template scale_sum2< value_type , time_type >( val1 , h ) );

        if( m_steps == 2 )
            // result of first step already gives approximation at the center of the interval
            boost::numeric::odeint::copy( m_x1.m_v , x_mp );

        sys( m_x1.m_v , derivs[0].m_v , th );

        boost::numeric::odeint::copy( in , m_x0.m_v );

        unsigned short i = 1;
        while( i != m_steps )
        {
            // general step
            //tmp = m_x1; m_x1 = m_x0 + h2*m_dxdt; m_x0 = tmp
            m_algebra.for_each3( m_x1.m_v , m_x0.m_v , derivs[i-1].m_v ,
                    typename operations_type::template scale_sum_swap2< value_type , time_type >( val1 , h2 ) );
            if( i == m_steps/2-1 )
                // save approximation at the center of the interval
                boost::numeric::odeint::copy( m_x1.m_v , x_mp );

            th += h;
            sys( m_x1.m_v , derivs[i].m_v , th);
            i++;
        }

        // last step
        // x = 0.5*( m_x0 + m_x1 + h*m_dxdt )
        m_algebra.for_each4( out , m_x0.m_v , m_x1.m_v , derivs[m_steps-1].m_v ,
                typename operations_type::template scale_sum3< value_type , value_type , time_type >( val05 , val05 , val05*h ) );
    }


    void set_steps( unsigned short steps )
    {   m_steps = steps; }


    unsigned short steps( void ) const
    {   return m_steps; }


    template< class StateIn >
    bool resize( const StateIn &x )
    {
        bool resized( false );
        resized |= adjust_size_by_resizeability( m_x0 , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_x1 , x , typename is_resizeable<state_type>::type() );
        return resized;
    }

    template< class StateIn >
    void adjust_size( const StateIn &x )
    {
        resize( x );
    }

private:

    algebra_type m_algebra;

    unsigned short m_steps;

    resizer_type m_resizer;

    wrapped_state_type m_x0;
    wrapped_state_type m_x1;

};



/********** DOXYGEN ***********/

/**
 * \class modified_midpoint
 *
 * Implementation of the modified midpoint method with a configurable 
 * number of intermediate steps. This class is used by the Bulirsch-Stoer
 * algorithm and is not meant for direct usage.
 */


/**
 * \class modified_midpoint_dense_out
 *
 * Implementation of the modified midpoint method with a configurable 
 * number of intermediate steps. This class is used by the dense output
 * Bulirsch-Stoer algorithm and is not meant for direct usage.
 * \note This stepper is for internal use only and does not meet 
 * any stepper concept.
 */


}
}
}

#endif // BOOST_NUMERIC_ODEINT_STEPPER_MODIFIED_MIDPOINT_HPP_INCLUDED

/* modified_midpoint.hpp
zHQ2xane0YhOJe9UCvEMeYFS0B91TRBEhsO0rCyjwzdhba7OZE7RtL3msV9rMjptJH6EnSIehrhiLjJmyqV8ixDLWwQvh5D/PtZQCUsNBkb0/CldPTg4sk/5J/AfaaTSvxnglfnqHyh5hCuGgMKrH2K9r8/zQQPd0ho4gR4PPpOyaVRjTraobUUaXs785ZgLTmuKLc4Tn7F9gAtsoXwrg7Cg7b6UVASUDXnbkp/O1AM/CZVTPpXpJA7GP+gDmXb7VbwkcF7d0w7d07N1J5IFDJxaVZtGyACy7SuabTnp3NADdPVxrfumWz0QItbHXpWxazgU6esikl3agvFtB67pnHIY3b2CYeNvIiHMARmDgVWRbkIxJCVrcxWWIKl2TigDZbgpucP6A/PWIkj605y40VM2162VqWzIhLpHU2miPbEkcwLGKR/0XGpuXTUUgWCKE62fjw+LBi4If5cLZ56j3eoYqgt6P5J6/KBG9AFwsF4WPEW5lDz2oWRUlZxZVXfIxMS5qlzMRm7MJ4PhbQ2m6XA1pICRMLQQo68Lcu2ti4e9tY+dOKPLyWylSOuhvl/31BDM3Rr66zsTeaKjH6IOC/Ql3x4WzwiSelqZBCt4XPjNapa7ao7Er8s1N0sKVMbngC/z4oeG8hSIdLG+bQVP/136DebiOMkN5mb+zOP4tbgczErdnEBdPJD7yYJms2Xh7s/29szjeOn67s2uM83CXYJ34iCpqm73G+wITRyjSk4QpYF9Fy6WkD95BNyvCRU+PElQlqHHkCfDF/+QsmCux87Iu6qQ746hOEHg3tPZsoBT/c6sfg/6G0PqRPNKZzS45SdpAGkyyk9rs9ao4AZzvck22AB46gIdZbFNm6m0ch19sc8ATOwc+BJaPDLbWAW09lziOVA879lwqOtWEjVKKl8eAxL5zQLcnhsnPBK3J0mDUbYNk9zbhMP6lSvI+Vv6PJ2ExZ4Y6p6FVx45t+9gMgr2/otIxjgjHkxb+BbKwFSE+X3e3DYVF+7ycbWxHYce4LGLfL9JMyELufip0Dh6sBte3z48sk7TRqIFFu+p0bEovo73AWobbmtfy0ufbMV8N+P5hwKCH21cD2faUh0mdOkxRNM2zafqLs4IanGHQSuI01B28CoEWoKZdERqG1pCgSHF/KywO2mZ2xD9mptvzQ9AdWryD4H7o/IF0DSyGksADrlOVeQkVv/rdD+aIRZY1Hx6pJVyNwHtoWPBOtlaZ5lSRqT24UARMtqWMytK0Cfywb6DIMEAZWoxMhJ0sfF2X+XnrdjscRRqsVBCS6A3JxXE7sseqbue+mFETRMsteQyw3Eu1g1FLD3ExWSEe5oYvAlihhM6ozbvXFMiMajFLXigW93qLSWbPfNo4GKvNyPTF960I0IZF7qMkuxBvHc7bJETbwrWr/BiyhaoeCT9kkuqTF0C4AUC1b1IAsMlIaI2Y+9I6nhYqt7rNDWB+yHU0ZHedqBWGBnHAyMxXi44tC/az4IN2FcIXN/7hohWABJZdZGHKmcuiANduEfnpsO8EjyPhLoYqX9NcDWPajWbdz0z4D0JNb+AAICYfG10+e6XtBDVRFDER5Jwt5VQPk5cl7J0WBUOEd3NrRO0hlxGBAHIjvtUm40vJOsyKs/yvx1jBSwgGpzolOgJKrcL1y3Cq0wzRYfngQCvW0YvwrT8Y+3pMj1H1C5l2YoQR2sekpJUqlZqQHWW0B3fcAnU5Q53zhBIUhyRfCrvWRI/IHSNFm/4TxV7+Cm75JUwPBkiLzjdARt0ulk1zTgexbCB1UQciP0VJsUTBotXil8K/lVI3ZOQZvfjvFCK26sCSm6QbKA0XAurhxjXoxT1iYbmpTHpYxpnUbaOdESZCOkjifgN43HZvZeZB3tEEzyBwYlmZVLW/avFWfqYDb4G12f5wPhFKLwAxiAmN8BvCMBu2DdGKxK9MNCvWew3ymKf01zA302rX6a7V1uyPT9epjtY1YWLpFvGgGK8cj+taK2gE7xjJ74Wnakt0MXoyAptY6/kndr7cVpMnK6OIYNMsMU3JIY5VrV9VjF73CdbHE3ZFM92JVyb/cV2FPYixrOVGdnwVbxwSa31Dj+K7hdSSN36BD/r4fcSxfV/K8Y1bD4Nd32KG06BgEd36I175skcMsDzmbCscCOMWCMP0byos0TZow0qWJOZhJ/C7ScqPyekjksxkKQzTmu2gQAGDI2V9pVE7lpU/nDMp0CN2xqw/DmRHsxVFJ0A2d6ikBNzbuov+GbPraUQr05wd0WLtYMP8vnp4vxz56+tok3dWceemYiBLBbbbUEdBXZvebUeuK79pOBVCKXKhtdzP+iyMPW6lCzVwMxJEHauOe/8Yug9VxIuJ3Y/EGUFGmoeMHBAjMlkIoEGYL13j0Lq6fyhu3v5jss02WTuo0LzVVO0XUXEKalJ9roPG5wZCYgk66vBqdqMJBNSlj0HXUehOZh0HFuPTV1H/bPvlleB8zpmOmd48SjhpfVWiiL89jI7Hd9yq0fTl/YyrmMNN3WkFOOcZ9ThVeOIx6WamokXGKvG4X5FdigMSW6F0CajZr/X8D2roXfag7mw++epv6cExg8E3n4nBHuKyCa5DJp7yo/6o8niwTLivyR5hN2fiLnORxSP1iT0mSe46DVlMCn4XBYdoW+C4eLnvt6yaMwX0vkHxJYkbzxiZCs6lItijl6E8S1qSqy9ABl2XZHLth04w1Rnj//FSG4gMviy+iFCv24SEYgfh2M6b6UWa7HmJ4q8H6j+xKkk4A01U6j+yDhFoCwG3jhDrc1svESJuqiglOfbJ39dT4x42cPKtTsKVNF1TwRL8gudV9NikQNIlSBROe2vcnPnsTUfkFrmpdYCXYqF90axYtFZF4hNYpaNX/FM2LyaTz/O1EVWMxFW1uDpuSDh9S2vcSZURHA40QSHaz+wG1JLlfHjFd7xO2KbleTFpQiXG6e6RRG5EShIwMmSFNM5Ugq4OvkESX4oFvOcsrssubflipLEUpVUM+fHIsFeZD26q2wGfddo14kEg9lTEYd6z4KIVBYEEVapR92EyCIv4GUCQWp8A9rBi9v5JUnWMFwoCwr7+36jnI912qxFc8snomKQH29dXZiiWTmiAMaOWSe44qUG5BiNCSDTxC4eTf0wbKWy6tkq2n4X8NXp6iaTGmps0BqQcFI/HE3SiarnMjoHq8zpD9tF2qvzjGq36KgHuz6ro6nkJ7v3jRyrmM/6Lez+CyTvjfE42S/j/69iuT5QoVU8eFlglru060lwIBumScLg2JW5wVUuUvodmfc4mIqoy93xaQ6JBxuFpwsRLnm7BZzoV+ppB7/jNYYmxJmb7nEOIX1wJjX5ZfLtVcB0D3MidyX9GM9YIX2Gm67TZJbpjRL+xXdKNL4aC1WxRB/0pyg/zE+0HvZU5kdcavIR2ifYjC/NUPR4SORrBdeWF00RK2d0WBJp4WfD0lBsdo9EEbTEsCLcejqcW7RyTgKCfIjcB60j/dQBvoXkbi0ouG1VkEzCFneWxMMds24xh5Or24HqWnBm1/gkrCilGvVKKnU++lBc9PVLCYNmC6+oX9b9RLrKeWDSrOvzDeM2JUthd9e5seaW7vcXSnxlGp2mP8nyg3fooXps2ZCwIYv+FkbUvIkYPdHvJxeaJPcqYvGq8U4I9qbuDuabN2Xx3atRWrrqPA1v0CnR768GqvwNPD6X/8KqJZthuwkwdk7TcyLLKqizT8ka602frcOni4xrmqgQssnmn3+yU7K4NTeHu6LUlEQm2d9+PCfqqAgVSk1NprWbbkEx5hF42VeNL5It92Qjm65QSXxRk7vnVzydo7ETJ/xMRencpk8H1ZFtM7MCOCzSIkI4zAUQZB2AlrmhktmBQ7Ev0y37mOu4Oy15av/zA1Nshi0sLO5+jt0GrUDVsJQpnHp7lu/+yaOdzVqctu3nuvvUQiLPwX7PGXclOainwAdAfpgrpedpG2vFtPDTywcUG+abb977t6uDgyTRxnsGqQt5F318vNmzM5GFUoEJKfQ6KafYI26X8+gwl3c9GrqTxeEQv1Gs1MaxIKLZTQk9setb39ra65MBR/6szK5rOKpSaad45SqROyDtt4ZmoWSP/Qrcc697ZsilbAX5Hz5ZyRrm6a5lZS7fZItVP/PW1wQPDZRVNBNfya2DRfaNSrUAjCHBG8Cuse+g91VQqg8ElkxtnwXCLgyM/0yVGAZJJGl4gz6qrsgM5VPxnPraxtMCuy6hRtW7KiTzruTIz8+Hmbw9jExtPKNf/1EqMyXTdmmRt1PI8cMOSpv8Tv7u5h0b538fl+//JGfzrSqeZdr4P3kBX91AskH7HeKWg0r+mzoqh20t17l4vkJ6QwVMy1Iebpy/zqLd+ZAtjPxX7tgmdU7wE88jfZQWaNEXPMX8NiIAKi8ZwqDEiBsO0WNsing2Bz1RPy4dGr6DHUU+jyaSiHkjC2pilKSQkOi6TS/+63saHy6+HDlzkskm4pTQWCk4O/qIqSacR8SmVEZeuP2ceq7nDhD+UvWyT6gO8Bk4Y5aeBu/c0yfsNNcOyw7ZjOFcE4rKEHssKGbbNVuEahx0yPBcgNIhc7tFUwmTHcoluhH1ZozKazHKTXm2O5qHQHBHdbMtGX71UIjVpAl1iYLE0D7aVJtWtB0yfRQ6+X4B/biZEM3Umep7O6rXKh0TeXbZOPv0oel5z/CR/HZZEgXb/XssXStXikY2b0f30+EEVNxxH5eKe32weU7jBHyrfQy70w5KkYfu9J/kvjUG7pRijp7AzhaiLq8/xLptTq9kJszUceb6yV0t4j3gpyjPivj7xserrVi+zHqMf3hPEmediXIDwQZelffuPzFa5zMpQJt/+s9V8radcN1NJRqPhqPdx3MYIzyfjNj30h/Xbhpu6r/v0rW/wbrShbs8qY5Vu15q1rdYM08fr28Rjmm+eO1PTepqIzuzgVDD/61y/UAliRq2VjGgFlsNgUsiQRQ/Ck8xfHVpacNC7uWA07QhIHOfD6ld3nUmTSpbxZTdVqN2clMARaiHZBWTfOu1h6Ln6Bi5MwAALP/TGTW0if+sC3T23RI8MobmvTBJpZdfb6p1JLkeCiIwhXaM51c6pUR/Tf1TnHEjqIvx2w3PXL1OTnhWVLx84GqGubwg+e686MmxZT0iSAVlRQJjT5s8gGeNOAXHshOf542Y+RyAoWZ4RfLMHK51ror892JpT+KUbhtbTnekRSFyiBfKNcRHX4z0qnQCQuf0LpfSUJdtd0daNbYaod7grpxUOobB4E8TOFvi1znRO6eCLxKp5q6bLX9PixLAsuhePjWcrbun/7zl5CQwiCF+tyIV92Y6VwviZ7GrsnVB28brQwhhBlnrvggV8Z8gZFfq0BXf5/fa2E/jjvBb99AmkG/tw3BhYFoz2rHp28sjnInxwYg8OuISVu4leR+7YH9D/PdSPn3yoAElijRsw8uM3Mq1p9UmzobyD4Pm5w5rXgsmnn4Txr+CJJtBum4gUvVOy+zsXOuzlgyR5pjxUs6qNPXRjJKfp+3+NHUxYkmL3Lzb4gODUAmEgGXkATls8HhLKJmwQzVDBZQOZJVFAO9QEx87hB/xm2J7HRWY7NpDsLV+6/3jOVqt7j0/gV9daN9kOFW9kqTOvgMePcNvjaw0rFOsIVGSsPZCRG+zegVTdvpPz3qFcPu4s+tALV4hosfWELuTYKl2qAVvtEHDkOLfJKS7gFMgfvmA8dTQ3Wy2WVDv2MY61Z+p7bcoP4eM/k04XMlCHdcXQsh9iNTfC2fFRCjvbkAb3sXQ7yiISfIftEYUJDzl1Vs/HLWPH1BnW0xuNDKzsV7d0bPC5+rV+0QOoYN9wznmq9h8UFNFgw6cfgJUdoiMmQKpare96x176nVeHXpgN1EBtIXeKPLQ9GdZa6hW3mYfzt/LRV/sNiRuIdp9eON5v1EuZugSQhZu/BYDv/b1PRCg/K2AtvjRjGSu2H9uVZOrvDhsK7hStg9ryMsXLsRYFw/T8XKTLuVo+YTW8GhitkSbXhvXd7mcVMWDrxl9jEhIKpTKJxo29qp6SM2h5o8s0PGXxOksQp+W7dwiv47tSVaP2XAbqrmbCpsTYjZW6cxhUxAVJa9e5ki7FYr+ro9XUrnrg7Uqd+vVi3yB8SyFJV7eD99yKzkR279HAbTBjDivixOOIq4BfbdbwtRVvTNFdBkpvSmQUVXxLQ9rpVvfnaj2JmBJpbZHLF4bqOgv4qYCbrtU9Y14ypfs8lisGFPomDxFmjxlKnVFqbLQLMaBFfRHWgM95zWEdeik06Jf+LmyTkS2TdpZjLraqYVHrJeZodwz10ErakowV1Lh0V+IsO4HwdU+/lJavWqGCLskX1DJSNPEbaLlSP6Vr9HeshLtt2WkZ4x57ad1KFv1Cyu8vZCtHZBfZ8MRRSK1Bc9izy5hLGegtgG+1hnBDK5fTRQrCt0JlvKZ6wAIMHmb4vyzIhaqoAtR8izpiJGlIq9YYfrhESfwKhiG1BUzxaIJB3J3gNXCLmypylLve7FdCRXLW/UEegMMqAuG8ZnXfQG/QNhoOkobPP9/rxAPbySTn9+ic4S8OMFMTQ5J/wtVgWrk4uY64rgJYUXySnEEnchgTbmP4KDqAPASnfGY+IqqupvgS9yOjomaGuQ7cmRzjZgUIQpXFWVtMtEiXC1I8MdP7FnixCaRl87d1ctXsQdiplnuVe7RU28/bFVtNY+138m2UeD1jYqa75DYzgtudVN6Up2CUz9PAT1rm0jXFcv9HL4vwOeuZ2KgRCWTDiIcYyfBFD9XkwMobNV42bluZDP8uLvM93NgqZxj8CRq/EU+if+yjqU6kpM9V3mpU0CvNLlyYSbXHCBCws8SGV2GSEDNo11aDyi8PBExDBAw4QDUysJMYaja8wJgRq+wWdHDWtmJd3K8w+4knc7RB8CxkBUfN+/PE9QrbB3bE5armebu/O/fJ+XD6K0PA5xf+tp2ZkYxj1q+zQEOnUL32zwyFgx9PbrGwMSOMf13H5i6UM/4YEAjSHY/hz0ngp+VuYXCyCYMv+PrfkkuwqwLv4xon39D134vzq2JXjH3oUiktfGjTgo+f54YD0BAISZGXp68ufe5alhwFzJkulM03wYkuoM5/WKofobPC4JJnIwO5UwcuFcQCbMRP1qCKWi5QqQummy5D+pslaux5Iw0VjkvZvODfwEaODAlbYdzrrCd1frugA+Xej6VivumHWJgSIE9fGi8sD0svNkQRD9NkUD7t/UXrEfP7VC/SBuOgD64IjYuVDHzZNbrahzjXA9G3aSLxh+cIL9s0IwdVJE21asMyzFbejt9VifoJNv1jODEniOPZcCwny3EN6ctZUgip5krrl3LbAgXzlR3b5+qMq4tLQPd7HWViXzbE82dqooQzEes9dS63NDbKTCdPGDavXUgdjrlLeGCYSrlIsY5aChLIRzVDR21UZOJbOd1nn0MHYlFjsWfZGFWV9hITz+5DK0u0RKNIgnAChRBJaf8saYuXNM0WWByDJ6/jR6ouAxHieYzo3OGHXb2n8cZ0v2sx7rM0dO7sezkGLdOzihCMolg2MiG6HBJYQPFQRMJAt2DX9EahHwAshrmSq7c7Whho2sr6Z64eU/eqzejjZygxg95IJ5P0qxn0Ruu143CusdqqCAy4UwuFCYnsyYo9AXn9nBjIH6TwJ8WrJFGG8xLdJ5JDOY3o6QqMWPTKKdZ09Re47BgFCYYYN/V23o4NOCkd/LXaQehuJM+41J601rCfdALuR8xIZevlDXhEYU9VvOvXB5j3M4ynCXEoH+ya6i2KtdxAy/r1gs00pjoSfzx+8++zvjvBSgMA7cr1l0BOfJQt6MkaynOdDIAsEb2CU3oOBE4Nc7vDoy3D2aU/muZxDbJxwGa5q/xJotIFyl9OSDikEUQ82hY68TLot7by1fJPozb5w36CPM6Y4RNLIDLRBflDatIew9Ce15m9VSohO5/w8SYJTmgjzxwNaRdXkIzFHq9+JQw6WIoKUmwP+IX3pMCf4WwS93PN1acLcpE1y8SfmPdmZXpQ3T+4I2DzxJrD5y1NN5Nspf88hNEegsS/bBPR8Czu77LORfiydm78DjKlKnZuDA+TGyFuR0G4bp4Dx45PYyahbu8ftd/T0Ww5yuoHewB4qA9poJ2EZKvKJroIokp3o+djUqE7gMCJgRP7Inqqj8eSKeYxHVMf62slrPMsLrsnRL1xkhVNHagQBvf4E1lZK5nj8smB8NVNtEjHwzGDw02q2Lhgm/wsYgw9rlC4YSocjTgs7p2Il0xSzUm4ApouBut6ZcKlljZYHC+FQ5lZSFhz8zyOi2WhioiqVzMB/EYVVhYbP/6wAJE4l0e9BJpFlNdSOgB86uXgLNZOVCMoKnh/2pmAw5RrKN3w/85OJj/TQAa19LRik2PTOahn1/meD6N5ylLR/5N7VndY2MFnMh/kJfNslbl6VSkQH071NJfGWlho++P6sjpv6BJDLr2i0LSTGgJPJt4wFk72e4nkQ+r82vPTc6fsBaiNoXcfM9jBMJkYBmk05L3alKh3aUDO4LOx6nx4FFB7L/28E4IN+Asq5wGmAL4B/gH6A/wH5A/oH/A/oD/gfgD+QfqD/QfmD+wf+D+wP9B+IP4B+kP8h+UP6h/0P6g/8H4g/kH6w/2H5w/uH/w/uD/IfhD+IfoD/Efkj+kf8j+kP+h+EP5h+oP9R+aP7R/6P7Q/2H4w/iH6Q/zH5Y/rH/Y/rD/4fjD+YfrD/cfnj+8f/j+8P8R+CP4R+iP8B+RP6J/xP6I/5H4I/lH6o/0H5k/sn/k/sj/Ufij+Efpj/IflT+qf9T+qP/R+KP5R+uP9h+dP7p/9P7o/zH4Y/jH6I/xH5M/pn/M/pj/sfhj+cfqj/Ufmz+2f+z+2P9x+OP4x+mP8x+XP65/3P64//H44/nH64/3H58/vn/8/vj/iSCH1CbHcMkJK5D8cDD3s+FDrnDa8weHHvIO8B/bN/k+FH2OnZQf3+SktqR8CRKTfmm6DRa6/QbNzYNIpbbatMetcLokP8kIPvAlbh3+hwhG1oVYDViH1W1ScN1A5eCoNp+iW5VFiJwda0Fy9UB4N1VNuq0x9AoH89JshdBZLKQQaRXr8SlfF+5dpMwqO/QuXvPesZtXk9ayO3o=
*/