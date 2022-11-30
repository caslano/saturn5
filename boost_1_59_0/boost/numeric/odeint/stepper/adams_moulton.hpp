/*
 [auto_generated]
 boost/numeric/odeint/stepper/adams_moulton.hpp

 [begin_description]
 Implementation of the Adams-Moulton method. This is method is not a real stepper, it is more a helper class
 which computes the corrector step in the Adams-Bashforth-Moulton method.
 [end_description]

 Copyright 2011-2012 Karsten Ahnert
 Copyright 2011-2013 Mario Mulansky
 Copyright 2012 Christoph Koke

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_ADAMS_MOULTON_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_ADAMS_MOULTON_HPP_INCLUDED


#include <boost/numeric/odeint/util/bind.hpp>

#include <boost/numeric/odeint/algebra/range_algebra.hpp>
#include <boost/numeric/odeint/algebra/default_operations.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>
#include <boost/numeric/odeint/algebra/operations_dispatcher.hpp>

#include <boost/numeric/odeint/util/state_wrapper.hpp>
#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resizer.hpp>

#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/stepper/runge_kutta4_classic.hpp>

#include <boost/numeric/odeint/stepper/detail/adams_moulton_call_algebra.hpp>
#include <boost/numeric/odeint/stepper/detail/adams_moulton_coefficients.hpp>
#include <boost/numeric/odeint/stepper/detail/rotating_buffer.hpp>




namespace boost {
namespace numeric {
namespace odeint {


/*
 * Static implicit Adams-Moulton multistep-solver without step size control and without dense output.
 */
template<
size_t Steps ,
class State ,
class Value = double ,
class Deriv = State ,
class Time = Value ,
class Algebra = typename algebra_dispatcher< State >::algebra_type ,
class Operations = typename operations_dispatcher< State >::operations_type ,
class Resizer = initially_resizer
>
class adams_moulton
{
private:


public :

    typedef State state_type;
    typedef state_wrapper< state_type > wrapped_state_type;
    typedef Value value_type;
    typedef Deriv deriv_type;
    typedef state_wrapper< deriv_type > wrapped_deriv_type;
    typedef Time time_type;
    typedef Algebra algebra_type;
    typedef Operations operations_type;
    typedef Resizer resizer_type;
    typedef stepper_tag stepper_category;

    typedef adams_moulton< Steps , State , Value , Deriv , Time , Algebra , Operations , Resizer > stepper_type;

    static const size_t steps = Steps;

    typedef unsigned short order_type;
    static const order_type order_value = steps + 1;

    typedef detail::rotating_buffer< wrapped_deriv_type , steps > step_storage_type;

    adams_moulton( )
    : m_coefficients() , m_dxdt() , m_resizer() ,
      m_algebra_instance() , m_algebra( m_algebra_instance )
    { }

    adams_moulton( algebra_type &algebra )
    : m_coefficients() , m_dxdt() , m_resizer() ,
      m_algebra_instance() , m_algebra( algebra )
    { }

    adams_moulton& operator=( const adams_moulton &stepper )
    {
        m_dxdt = stepper.m_dxdt;
        m_resizer = stepper.m_resizer;
        m_algebra = stepper.m_algebra;
        return *this;
    }

    order_type order( void ) const { return order_value; }


    /*
     * Version 1 : do_step( system , x , t , dt , buf );
     *
     * solves the forwarding problem
     */
    template< class System , class StateInOut , class StateIn , class ABBuf >
    void do_step( System system , StateInOut &x , StateIn const & pred , time_type t , time_type dt , const ABBuf &buf )
    {
        do_step( system , x , pred , t , x , dt , buf );
    }

    template< class System , class StateInOut , class StateIn , class ABBuf >
    void do_step( System system , const StateInOut &x , StateIn const & pred , time_type t , time_type dt , const ABBuf &buf )
    {
        do_step( system , x , pred , t , x , dt , buf );
    }



    /*
     * Version 2 : do_step( system , in , t , out , dt , buf );
     *
     * solves the forwarding problem
     */
    template< class System , class StateIn , class PredIn , class StateOut , class ABBuf >
    void do_step( System system , const StateIn &in , const PredIn &pred , time_type t , StateOut &out , time_type dt , const ABBuf &buf )
    {
        do_step_impl( system , in , pred , t , out , dt , buf );
    }

    template< class System , class StateIn , class PredIn , class StateOut , class ABBuf >
    void do_step( System system , const StateIn &in , const PredIn &pred , time_type t , const StateOut &out , time_type dt , const ABBuf &buf )
    {
        do_step_impl( system , in , pred , t , out , dt , buf );
    }



    template< class StateType >
    void adjust_size( const StateType &x )
    {
        resize_impl( x );
    }

    algebra_type& algebra()
    {   return m_algebra; }

    const algebra_type& algebra() const
    {   return m_algebra; }


private:


    template< class System , class StateIn , class PredIn , class StateOut , class ABBuf >
    void do_step_impl( System system , const StateIn &in , const PredIn &pred , time_type t , StateOut &out , time_type dt , const ABBuf &buf )
    {
        typename odeint::unwrap_reference< System >::type &sys = system;
        m_resizer.adjust_size( in , detail::bind( &stepper_type::template resize_impl<StateIn> , detail::ref( *this ) , detail::_1 ) );
        sys( pred , m_dxdt.m_v , t );
        detail::adams_moulton_call_algebra< steps , algebra_type , operations_type >()( m_algebra , in , out , m_dxdt.m_v , buf , m_coefficients , dt );
    }


    template< class StateIn >
    bool resize_impl( const StateIn &x )
    {
        return adjust_size_by_resizeability( m_dxdt , x , typename is_resizeable<deriv_type>::type() );
    }


    const detail::adams_moulton_coefficients< value_type , steps > m_coefficients;
    wrapped_deriv_type m_dxdt;
    resizer_type m_resizer;

protected:

    algebra_type m_algebra_instance;
    algebra_type &m_algebra;
};




} // odeint
} // numeric
} // boost



#endif // BOOST_NUMERIC_ODEINT_STEPPER_ADAMS_MOULTON_HPP_INCLUDED

/* adams_moulton.hpp
lHj04BfQ+q279iii2/hWS5ggPqkyAd8k5iR0ibh1TMlZH79hMDqtgAgoXAJz0AuX9RofZYKGfW2n8JewsYGGRu0jkHhuNidX1Qk6t4ebzuc507CLacgYxm6dpyjkl4LxlHX2TOms1C4tMLPSNGmBhZWm+6UFVqj5gJJ/Drh0TNpN5CGdvhduFdu6kWj213D/4qO6k7cn7cZHs/Rapigwq6fhGVFgaiRpxWvpotQkEAB/VJQmSa9NEQVJAk3xJaLAqCLjh44SzxK/BuBBxfk/AMjodZqbbOCChP4BnrpQSejOMK1sWA5yQd+sTr5ovMjQFJQlTUCW4ATcX+wJQaNKlX0iavN/9LY9XGfb06HLW91GxkANZAy0T00D2qUL/Uyh7hiZ5t/r4fZdPWhg/hR52sK6Z1JGVBHVOehCow8glS20VzDwXX/+LCQxbJE1Mba3+gkSkvSVBVGeh7Genn9zT0IWKPxWOx3cbMpMVyw+IHFUH793hG8GR44O/YUy6MafX8tzZtmqbTgtb4nrLVD+QIDnNwhZKoZN+/E8Xd7CPkqogJ3s37lH81LhmgCM82mG3Qk7gmrx7reQQEeLO2Aeu1g7N7XFxUSvd6meOy6V/g+fBxagJBBNCpSMxOt38X98oGMBuvjRwz3KSCwobsxe/0VYULzC5LsuwoJ+7Xh5wE/FGCXckrATS/sERXy1fiem63aiVbcTDbqdeBrr+wYLa/HDn9bih7N2IHxC87CptqTByU3b4xldr9E2GFDaN9TvGSlAZLqB4u6VHYpb97j62E7c70hfJbFzZbhjA3zCmzE9OaHOFHYY9n+zuoLXxfi24YvG+aYPe/SB+SZBUyN2RtTnH3m1PgxdNMa9WK82Pf7IHYk5cgL6peBbGSWYZ87Vyh9oRZP0T5yasaitejRO63gVvRwQaOGMfkV7dCvaqVvRI/g7LFb0kFFU0qZVAms2Xj2uwoj5G6y0FYaYUc7JD4r2Qxh99MR+aHE25BIljuGaYgQ5vFTJc0oCKsw4Sa/nauDds2EUpQdlXwOa682HMQ12n2DFmeRBIWhyLNPZYgOWI6YNbcoQwakLD5zaMcwCmIKJe129zNlKiU3RVnsBJqalpMZlKNC4cDJjcoRrvjmeCbRBc35r4CfONSo9drIaOwgj2cdbD8T35wH+ZRlXBNaAWZvK1pJY+5m7vk5E9lUUoXrt/K8RkX0ff/g93c7dx38EnYhWht9qIP69SI3pGvwhK8n0xuQFz92kygvYUygYGElqAHvtISs5pUenwhQKmUWJe6QoggfxFN/8k8RX6L+WDLa8jAc3s9VijihNs3qfPi7KIn1cFI9RCHnQzKkEvV/iZk6hmxCXp7+uKd5jpiWsXbO5ueEFsrn5UdMw0yZ3Sc8L5OqD1kgPCWskNFFK0tlH8XPP0+dZTZqJSswQKGaKlAxkHVwgRwXgud2xdhbrtJgl/OPdwvKEl79GuCr6nRMc+6jVgn2tfR5j0pjd5ZOw6RVYI/+t+LC80P0K6u34tfC9UOER8vOSvQZPg7evINFNSj800khCOKEBf8BD9h/83zuwqszFC6MlzG8vt3n5JGiCqmWF9nJKKToG35BVQbG9PA27cXaTIqrGbxxIw36Kb6zqVxPwq7/Dm52oSHgFuRo+MMuhqhw9qiafCnkfvF+UQD/nStHJi7aNLC/SRUGGbXzCVhtI1e2aW1J1u2ZWKtldhSsshuBkfnXvWZxYNs8Cp6AAqIi4+KEpNDou/VD5J+afxgpnsOJcaT3xQP6ZUgQ5JFY4TZKRE2LFMwQTa6tGFSDz55YDg7AJecfCmeh3tdEDHCSwj6rV5tPIwiuuLeX3evm9fwa6NYJcLgtnqAYYvj+TLi0gC3adeBX+YEscrxCLz4g31kJgbgRkskk7lZvpVG5BkaSoxG3lxWhVozXS9yeVlJKJuZ5YIBx92XoamkwjjSylFqT1JBKQK6gEBwqDIsmBV3KukFzV6ric1YxY+CKPKJUi+B2ba45lkw5XpsPhFlmK2nFlWmjkoxA3faczuQ1enWg6wd/rwShHNz92WcdYy1MvGzqS+0f/3sDXLnYYxExR6COYXJzTreGmFPhrogIJGHjndubcYnJuEr7S9Jr8vI/0Z7dSXBfJtc0k04SPl1w7cvbnFbvhGkBjh3XNiGW3apO4jbDsdroNdohbHd3ttmOTxA63ONNxPTCRaAuJLVQOzqBOasN/GjWsTMvA//qXHoVyzgMjKXvMwEPKbqPka5U9SZKzXsQJkN1J4SYzhgoozJXQ7agLfawKZ2I4Ad8xCS+zbhKC3a8KwVoiD6o7VlVOiSL1tjULYViq7Kx3a8Iw6t7PbnCoPUXj7Q/hOKpbjpv+QqKt5HDVVNXPFy6vp8nSIkxWA8XTvMw/Q7sF4GzAfoODEbu8wmhywBhZG/inwbQWz4hdXn7062PFM9XLSzT4p3d6UIRzmN8xSxXyiPe/QqmYuHa1MeHNKwZw1+lGJVw136BGnqGtm00nMZuOqokEFXn+BZVLRWA9ZhIBRuvQdMpTnuyHJW2h80W+oEdZKnNPK+tFZAYXnpBwsLkWmLf0SzV5ikTTHZzEJtJ+Yt5ccT3eJGqi2Gev41YPjqH0WcmscGnUxAqXoCg3Dac0aGHhHUJKGEZLE/SPAA79sNJWboQ5ODHHgVePRLIMNtvCVu+7FEOhtcJfaT32IXxWCQAULOvTWiTaxVErC1OMNNrqYZKVw1QQXhIyGyHO8dUxmhnJuVryrYMe+BeE9yRDDwiNmNoYoT3Jtxr5QzNrx/TlSDWYDkiuNTB7kf3BcSxCc0vYD8oF2iqty27Pf6cqGVqIXjES1DXOOpZalrUCCb/VHrnYEpNTZU3H/VhsgRmGX0IYC5PxIOkoVPHQYd4ym/xUxHp4RYwcgWtwxXJJVi+QC9JzVN3p77xsqAbaNIAvSFrm5gNppzTURkJHIchybRVzlN1cABhEBFOkLwpUB4Qj57L3mggZYtJB17Y8mtjHTYB41ME2F6ifLVA/E5Otfbwnv/XxZNaKQUKoZhOgLCFXc24HLJRPldvW/hZl7n+1rX1ZONU47UE35W2GKXgCDiu73eJh7YqjHVPKCsM/2oukIUa1Kmot+OYCMVk0Pd4ZNFmoxSi4Aalq9cDLvq1uIWoVVXjzCt2hseWpAT43jRSm0W8C/ZKv/naQrBC94t0eLx4a/urdiUm80QFdwnY13srYZy8eP0zc4rKz3c1O8PnjYZ0KzdlOwBYWNo4yPXaTEsoNt4nk40DIow9qsdXrBso+frkEl8fi9Vwdi9eTEYvXM56Fb1PDFIxlYcpBnSxU6xj2a2KeTprQwQJmj19VLrOwCKCMSmDnD+NcQLsmXGjn7/y7UYna1MTdCJjxQwpBCdPtave4/d6AYFX4b8cn0kbTzLX59Knu9fFxU3T8YeZF8kEAJc30xHOVnnh+SHVL4Tn/+CcKh9rZE5hFAPNxAuduMqGWFxbGVv0cTsMLOF0tTiu1cA5loi/grJG2lF+vF77AolBGOPWaF+kW/X41Nr39Rodhxbmlyyawd5o/s6z4cukyK+XiXrrMnHMmmtxIcVvVSe3VJrWXV33eOELg7KFa80F6SPItx/iWvnaK3NCBocN8XfJ8SxI66rB2ydfBr2yMC3hq4lb3zNcurjskBDpiAQmRlOqKR5JN+VvP0GxA3fwkitsSR/m+UD48NRnBTcXK18yHp8YGKWGlWaqJAVQeTAlXpRlC15LnqsacDQtVrTb2LRvSrhhZJPOLvci6h9IjCkzl43CD65zIAm7lKKnrMw0J7RtstXv0pg2v6U0bMEQaRoqeylb0JVGkaNToFgP26hdXKYarzYg0VU2kqUkPICdsanZ7kcUwIL/gyozsh1LKxxwwtaJ7mseN7MZHM7E0S5SiaQrmyEtzZzcTZ7+PSqdopWkBUSKy3P8Plk6Aq7ZERKNeGI/znaHNWSbNWRbN2RRyQbaOaKpFGbk+2a/GVJyScL1ipoQiTRjm8qu6OYac8mPIafpLFcRlDd7Ku3FnBgKUA+IQb71BzT2gJo8me4vMkYzNVLOVefcp8azRqrxJj0+mXJy5Ks3APNWAWA7rEcsePWJ5zUi2fT8PPxY0hB4KVwHVcx+6pHdQcNWnZ1DUkVHwjMRo9DKURgO/ngwYMWpFR51UKELCVS8K/O6WPUpsX/o6kLkUQuXiJV7anEdoLnqWGoV0ljK+iWgts+G2KJJcHBO9HkQRkq+Xf+9NjX2Cjv4k/FiFIfhf6tGfhPwswKISnFveJNLXCH0sCo4rCl0u0lwBHomOYhvIXh5684IIottRgrmdPPAp3/4FfWfA3907gcpnwvKuCANUG4IFRcHv683R8YSNlDYGew3n9IXWHiVapOaySVFT2XzdPDZdekOd2lxd0OaD3LlTlWsCoY7On0K4VDKy5c7N9ya+7CfdPlglgvFMZ0/F+Luw3N8ls8OLOsfzBgo4n2GIHA3hfWBiD5uFXUPO0Txfhm39njne8iS/m81eorQNDp8s2stS4/0GoM1rWKUqJMtllZieASNrVsAuzvB7UfE8ZhtXRJjzIa3ZsTXHRpSFUoOj1QYHx0RPZG+Z8DqmM0LYOZ4D9rtyzf10a4UuEVdW3LpyvnaNxd8ViN1C8RZ/MS1+2zr7gDgh20mVPkl0dd70KVydmrEWhYD/5Q+GeFEmuGHIHzJtsL86K7XGYofeDjg5+CNMI1wvbCfr8cxGxxDllYy23HC2QpNLYO7mLik3lngIxwqf7VO3xagbthBmPBHIYQ0ErqbscEUQc8io8dD9JTiG28p4PLbnZg0c22cp5LJmQVlxoZUiN6C3e/BW7O6QEKPjEphHAruFXKkFz1GxVYsZoQsvGs2SV92vIzvIHKo3tgoa7XeAZ34fZ1p1Nv/y1sH0sB8ubH9m5Gjw9vCsAtoXhXB9YVgknOlwUxLMIIZnMrFbzXC/A9KD+61wSbkZ88xC05cQGW7xBCiK+/vZPcrihYswGQ1Fx7FTXj2nxUOX4S4opbLB+zdTv38zL4L/Q5R+1iK5jtlqb4fR57yfN0moD2aj0H+SUB98H6eVEsrn7w3emfcCqgKCd7JVKO4OH1Ly34bbfzc6TEWTWH8AKeZfX+dAFS1Gi/UdA4bPjLhdpR8peqEgr0NEXge7G5WeM2ixRzWHluXvDT3MijOl0i6ptFsq5VJpL5uEYm2P8o6bN0+FOS/IJGm/asTjz0Q8DSQ9FL+Mxa18cYGmBCgyGQwjR2FyHhP8fQVbdZt+PJv14zk+1RFTbXy9MW3+GFiGq2G9/ImpC48wATx7T2LU+/I8sa8S6JPq7v0/5IvGZBG22if1lFy1Lo/eYxQHM4Wyi9Sp2UXWjZxdhKycswchq5KLIqsNHzWOnENgpFARgRJBzPb8lV/Yv1sdqs9K9FfV9BjpdU1siJkYGz94ubBpvGUQEhbYf8Q7xevHO+X4O7E7JVF7M2Pt5cTau5bNzoSDfBXgABPz4u0TsvtRO+AVV45G4okZqIyRCIlbn/cgjycMx/vQA8gllFLaswK6JWz9EVshCgesi81gK166Su0j06u22v36LdGgJ+7/iCu7EvWueO1KKWpoW785lr5rVEuh5dwn6wzRNJGgBFnuFLaSnBYLLQIckJTkt7YU2tETEzq5IFx/zCAisAiPJH9arN50JmHkAqk4M1wBK/UdOLuzryWK8irm6KYI/eaX6P9CKxtLP4rTmaOLSjBOP+YKWDlaUdTz8VKqTr+w8eL6BSdKJiTXZrQSDW211f7erEeDL5rjaPBpM6JBtKBg9etIJkeC88oteaX24JVnVtUBnjEGSQHeG49YBnQx+WJETVIplXVoIbWD9thHqbtVPwWF1OcaRMicfy44kWpU37U4N6oBAqG+jWjW1kgxvFdT9G7fFvbEOhOF8Wav00lvMQnDO4yRVQsvSHB+5Gz9Uvid3SyVrgj3j65MrhdpRM3CYfXPv0K3fLfk3MS3wk+0/3Nuwxj+sms1f/sPOg39FubbpOoovLSP5WIFTvJhRLKHEMcKoz/UYq7m23bptJir+fNQEUpQQ/Zw5UZDaDSJW3vyTKqnq2pRRmLPz5P4Td+OOx3QSyBqt/E8eCvfakTTLVeTfKuJTBWxSTmQJLla5eKvJOeOIrKEbcOuAW2/nnpUup2MZA9KlSJyG+miQ2Qe66wT2u11qvA/Cd6UCZMzU3lSuUUEY1UD7dZxy1XQBVcddecX30K50DavTFJI/tzviWmA+2Yr3/1yH0zkGli3ccy3mf1ScB2bolcyoUZZ0U/eGJv1YfNRA7KJtQrfPufW8FklNB6VO+OfRXOTTVCOysUk1owTGJxO4mgLe4J8r7IQ+hLRjnglubZGx5VXeOB/fmQjqYfQIpBWKBaSMyYTqTADDU/yexrIKbKg2VZu4BuvRsvCbazIDBPh2+71qLaI0AFb9QSjSNlsq7bSrzVwaJJwWGJJzLmU5UY256DgVTnSn7Ofzf/b9vy2StOcqPEWCX7D847849rzDniu15XXw3ODrrwBnpt05U3wvE9Xvg+eW3XlrfB8UFd+MNxsDp+12NaQqNu5ma2eT5oD3HmwQw9nqZacoW2q3en+LJLdi02gjp1hZMZD/A8C2NziXK0aKJqxjmfeB0LABDUwjDR8iK/CGki8JMzgaH6f+p3gSuM7zYhbayF8G1OPBFXDR1KP4AOf9T4K0KJjMHm4382r3uUJSYnA7Fgc/K/N32juVj6rrXZl/KYIVcRuuZ+F3zxt1i6K4Jjy+928ckPMequX//qqQQLEQhQg2jUBIg0/Ea1Q/l5jomxtF72kP3qfXyyZlkY/jbHo7of+C/krYNo0pLtPom3GTrKxkHYNnFeU0KTwzjUTkVTF/E0lbk8AN0Dnq1zp2Ub2demGUDYbixJtDxKKMf3o7gaKqZ9Glnio0Kd7LfoYS2c3wo4jt0qPsNS4jC0wS3eY2QILK7BKd1ik2VYve6ZCRH85yiLYjXA91RfcKcsYoYAffO+khpknsKfwwpUjBmEJC9/0abpKgq5tOTlcpEk75uofDhNV6/OFWX51MX8ejFCfowR4/iNkvC/XoHO9CFmPmk0DmfZXmMk3b3XpQItBPTBJcg0FiNfBvIk86GpfHMYsvJ30MHhEWwyaeW1N9fDyVFG+04K1uaBH9cNhRmltjJZrmoaXj9HKrXJN6/DysVr5OLmmfXi5TSu3S7UYVk+q3Ux/t9DfBrrgRSwhijfRSJlSGpHekPzLW2pQ6nopPmwgheAG3JAtNWiDlUy/MO0gnknphVb6iyHvpBfQvJKfel3RIukPl2Lv1eWXYyd56EVFOeO0GIOj/LzzCgfpD95eNCx7YWw/bB+4qH8XnCQUjp7gX846qbj5pZO1GN0HyRHrNqPIKYmuirZazPvHdlNSjh+Gd/eKsGuvULivjJjLPCKL702Oe0gLN8TsySQA7tcM52NJ8VCrJmLiZghVF8b3I/kcoibES9z+Mnkn8m84KHzVKfgfWEHi64SXYogwVOvfR9Ja8DcmkfZoZEG/mK/R/3wuNl+eYVNVhvJ0/szlNOuAkWIyTSAjgS5+bACtI3KaYksZb4lWUc0fMVeXr3ZBHLn59QfUj5HdH8iKI2mMOUmeUZs8gspU
*/