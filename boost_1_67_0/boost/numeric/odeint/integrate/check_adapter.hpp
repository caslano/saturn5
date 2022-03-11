/*
 [auto_generated]
 boost/numeric/odeint/integrate/check_adapter.hpp

 [begin_description]
 Adapters to add checking facility to stepper and observer
 [end_description]

 Copyright 2015 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_CHECK_ADAPTER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_CHECK_ADAPTER_HPP_INCLUDED

#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/stepper/controlled_step_result.hpp>


namespace boost {
namespace numeric {
namespace odeint {

template<class Stepper, class Checker,
         class StepperCategory = typename base_tag<typename Stepper::stepper_category>::type>
class checked_stepper;


/**
 * \brief Adapter to combine basic stepper and checker.
 */
template<class Stepper, class Checker>
class checked_stepper<Stepper, Checker, stepper_tag>
{

public:
    typedef Stepper stepper_type;
    typedef Checker checker_type;
    // forward stepper typedefs
    typedef typename stepper_type::state_type state_type;
    typedef typename stepper_type::value_type value_type;
    typedef typename stepper_type::deriv_type deriv_type;
    typedef typename stepper_type::time_type time_type;

private:
    stepper_type &m_stepper;
    checker_type &m_checker;

public:
    /**
     * \brief Construct the checked_stepper.
     */
    checked_stepper(stepper_type &stepper, checker_type &checker)
            : m_stepper(stepper), m_checker(checker) { }

    /**
     * \brief forward of the do_step method
     */
    template<class System, class StateInOut>
    void do_step(System system, StateInOut &state, const time_type t, const time_type dt)
    {
        // do the step
        m_stepper.do_step(system, state, t, dt);
        // call the checker
        m_checker();
    }
};


/**
 * \brief Adapter to combine controlled stepper and checker.
 */
template<class ControlledStepper, class Checker>
class checked_stepper<ControlledStepper, Checker, controlled_stepper_tag>
{

public:
    typedef ControlledStepper stepper_type;
    typedef Checker checker_type;
    // forward stepper typedefs
    typedef typename stepper_type::state_type state_type;
    typedef typename stepper_type::value_type value_type;
    typedef typename stepper_type::deriv_type deriv_type;
    typedef typename stepper_type::time_type time_type;

private:
    stepper_type &m_stepper;
    checker_type &m_checker;

public:
    /**
     * \brief Construct the checked_stepper.
     */
    checked_stepper(stepper_type &stepper, checker_type &checker)
            : m_stepper(stepper), m_checker(checker) { }

    /**
     * \brief forward of the do_step method
     */
    template< class System , class StateInOut >
    controlled_step_result try_step( System system , StateInOut &state , time_type &t , time_type &dt )
    {
        // do the step
        if( m_stepper.try_step(system, state, t, dt) == success )
        {
            // call the checker if step was successful
            m_checker();
            return success;
        } else
        {
            // step failed -> return fail
            return fail;
        }
    }
};


/**
 * \brief Adapter to combine dense out stepper and checker.
 */
template<class DenseOutStepper, class Checker>
class checked_stepper<DenseOutStepper, Checker, dense_output_stepper_tag>
{

public:
    typedef DenseOutStepper stepper_type;
    typedef Checker checker_type;
    // forward stepper typedefs
    typedef typename stepper_type::state_type state_type;
    typedef typename stepper_type::value_type value_type;
    typedef typename stepper_type::deriv_type deriv_type;
    typedef typename stepper_type::time_type time_type;

private:
    stepper_type &m_stepper;
    checker_type &m_checker;

public:
    /**
     * \brief Construct the checked_stepper.
     */
    checked_stepper(stepper_type &stepper, checker_type &checker)
            : m_stepper(stepper), m_checker(checker) { }


    template< class System >
    std::pair< time_type , time_type > do_step( System system )
    {
        m_checker();
        return m_stepper.do_step(system);
    }

    /* provide the remaining dense out stepper interface */
    template< class StateType >
    void initialize( const StateType &x0 , time_type t0 , time_type dt0 )
    { m_stepper.initialize(x0, t0, dt0); }


    template< class StateOut >
    void calc_state( time_type t , StateOut &x ) const
    { m_stepper.calc_state(t, x); }

    template< class StateOut >
    void calc_state( time_type t , const StateOut &x ) const
    { m_stepper.calc_state(t, x); }

    const state_type& current_state( void ) const
    { return m_stepper.current_state(); }

    time_type current_time( void ) const
    { return m_stepper.current_time(); }

    const state_type& previous_state( void ) const
    { return m_stepper.previous_state(); }

    time_type previous_time( void ) const
    { return m_stepper.previous_time(); }

    time_type current_time_step( void ) const
    { return m_stepper.current_time_step(); }

};


/**
 * \brief Adapter to combine observer and checker.
 */
template<class Observer, class Checker>
class checked_observer
{
public:
    typedef Observer observer_type;
    typedef Checker checker_type;

private:
    observer_type &m_observer;
    checker_type &m_checker;

public:
    checked_observer(observer_type &observer, checker_type &checker)
            : m_observer(observer), m_checker(checker)
    {}

    template< class State , class Time >
    void operator()(const State& state, Time t) const
    {
        // call the observer
        m_observer(state, t);
        // reset the checker
        m_checker.reset();
    }
};


} // namespace odeint
} // namespace numeric
} // namespace boost

#endif
/* check_adapter.hpp
tk+QB5jsAJqv7s0L+NGzz5Pbp+J39ZfDh6ON9q8Rd9PCr9zcRvGXUKHJO3LrmDQqKG3OiShJ5glZKQ6G0WE2hokxToaxKU6G0XG2CUlxtonoKM4O38fwk6gPl0JUMa2hL/69yaSqAjQdxYFB3Mfb+Z7fZyoJmmpNeDyQJHuefuc+ILAAkHwEyOG850c2v34JkBZWEIdBL+gWwENIwIh1jgPYrwclv6IusOVJUC5e4m5b0hXc3oaBfXz0yolLqJ6fH9tIByJMoKGaUH/5sEmcg3CMGIrYTojkeOC3R6z8wEaZNGGvk3ePKK4GFPy2Tp6LykA3xRU8F0GUKi5Bv5DRbwTBtKn+9y+sGfBqysatQ1sMAX40P8gcUDH3ycJHRRhz1xPSHNgV7TiVqE3YJB1uzcyzIwuDC6OjRIbyojKKUvmkDRWLalJ/TyBIV9P/gjigotH5JTmnOMf7ZVvRoH/Roe/ILSBraqI2dSfgeWXre+Z8Ab911bT5cWntvQ9R6mlEsKFzKsJABzxu54jGwxpQ3NulsHgX+al8ODBTYlrv5FKQWKpqeTJqWON0szV7sst0VVQ41DD/t6zARBj8kK3KLZmxYjxH6Iz1eLpO49WuLlFAFOPLRCDBpjUr2nZ6dodB4xXj5sVR4xXshv2Saau04Ifwxp2GRa/xmAvDxnpOQRtvQ3/XwEVU2cnq5W+LjSewhk8fzobOV7SGjs6k5z1vp71un9aXI86Sx2HQ1lAz7leqBrLOt3uQDX4Xv+c68A/Iz88L0xPNDGJ9p6f3nEYhhCEoT5n0bVM+jkmz8T7L8s3koJQtPVdOOoDlHZJ02v6Z4R7H4IrDfXZ0yROkbArf4MzM5qRWw934v30Q1TfUVLkFtcXy/f4VpL6HBXNRBQOD82K7jpo34K6hQSEege5xenJ3EJRhRJHYBJsHGpa06oeUuglUY/38v/7+52X9vv3L+fOQGv5nvcZa5xctMYw5WUPURsKZQvne8uTLUBwlKUD49ESPl2g5OXdyBOKi8woxdurTpTPgTLwyVDqUrP+ncNa6+j4INA6BHrO/SKXAYcmbPiORDhTLom/s0UbnYUsEnx4UkK5jFNiyh0ru5N5NAuWLE2kxBRwzC0woIdimAuYZZD2JEDFH9XBACRXwhZpcJ/RoXv5Qta6vwlYb2iYAeiIc/sQZ+W6Yg0DF2jy6XTdsP92/1eRuqNLrY/e3RxKKF/fduDq5xwiqCHf8kGkjn+8G6u3044fHWpmIY48M1B3OuWF1Yo8d1BXuuSlX4PCNKPWQnn5yU8H2CGePHpTYCz6E25gdZLDY9Ym9QmaozC1OBuXG630V6DYPcAxBgJVrYpuzj184ml+bjzoj05qdPr2DcLJ7qNEMd920GaSPqXlwijaf0/1SyYudYLLnGjpYkdkrkKlK3QXlrsIjXsxKWhIbU6li/ud7IH6/41fZG1C6fRFcOtBa8hPdNxDb/q62fKm/hmS8dXhv3Hb/A5Oxr9VvjZkgZIdn1lLXf+kcI9OyGbUvCwepOJryT2bO++uq1WaKcnZEG28tnI3N1A+zlURlOc3m4uz3FhHIokYjTIKNdOVrH51R1mVOMUyB1qfrDr0Mjw1M+7nSZIuawkWL/WH2eEP2xa2GP/srPwhBZpvQyGi3zD7YLxY8d6agBTOF3CiIpclewa9vi9TtDEFOy9HbVzFBpypvyH4M8naSwehEeVduv7KPb0Dq+nAnmgEIXhuGBe+3rs+ESoAnTBrErwSGQzsjur3xU5ToCflIuVgEJuDrbVhNTL1FTEVkyLtUu1harwrtvAuDkNMjYnzFDsY4H1dd0H1ZR+KXWrHYspSWiiVOFYk/MgOEAB3Jp3eH0xfvOCNZ+El97lnTCuSXbbUaj0djskx5Yy90x9NUzax8L888DIR9D4Z2xu2A47LfDDtXaZM7nafWGq01tEGVVn8KoJrvHhhqeZvKNUm57xIYvkeHRS8Ltw4/Dd0XwoaLEM6uxpDnDUK14kfxzfWuB9svM52Ni8RLMwuruIIdNb8HHMuPGhRLTU7VDvecxcZLG8MQNwPFQRO11da2Nh7eqEZcI31GUOqNAcPcr3Nun02dvPMLUQTivxSDVEWQQ9T9A6JirzzL5myz7ZFqqVk4gTmhJY6mUnF3+pE0DHYWz+PX7q2+qnjkf2DT0bDMmKkOZTjxFK0zogqon65bEjvcskJN+gsNViPY3yhHUsgTtmZi8gmbO6D33oQJVA/p7KvaW5eu4hFSg9n5joj21aP4+D3mUm6XMvdRM2nS60YDu1JHyddl3HbdXQ2uw3s6ZbyryviS8UnWL/nSMdONrqN6+KBkW8rucJyJxm8Ez0v9TQNqEDh+co3oUQG7yIawoWZ8fPLHgGtr3TZQZbhaB2e7fKDRyEisbuN6rMAjhElWt6ltAeDXxZEYGbLbxDYLsAdh8OfysB45sAWBgxVnQo8f+ILwycrntwOOkIXiziHh7uDN4be2Htf0bs2c0qM0MtOtCmVL2cRIN/+zedIOKljoupN596vfvk+CJ7qI2bAomYlPnsv0bg9ZC+QId92EWcvBkjljB9LrpaQAO5VYU8vbp/UsSXRKVr+VcepXBjgHY2pdhXlL4g46AqeeG1gfejM35xvGJTHDIU6HDpT7Py28d14Ors4PO9TgIuZ24MCDppgAwsW98xVFzCtfvvMW/E2S6scpgxtiRPPN4RW6Z5pYgu11AzZHyLrA4wiwWaC4yl3ppZWP+ui9WATT3d4WNzPvIU4+t0p5DugIrai/2PnoE8MV7id0JXhO8vO1S4qjr65pt/OCjNmV93El2ntI/up0wbMvVACBhIc1uNir/HxWjG+7x+5kjkuzrM9ZPs9msC0XtvOjzSw3Vy1qf6Y3B3mS9PXXfPGRxrT/gOFJ8u7MQbhk0/ZnsNtKXldUbwvTY0tUM6usy6nmH+lWirWEVSw3cRltAFPkDxWIOWTZEAkB7VRC6ZCl/rmUIqw5c64HdzfHD42BAuIh52anM9ZXog/Y9OZndQbCjVyHY7CVnCnbYDpA2u+mpb6lneUkzjEkb3ABb/S76M721OeBdJcYLKSNV10mSaKPjaGrOdcQwDF23eeF7lDZA2cTd6vlIXrUULlWeSHuBD7vpolctsU4eNoElyn0mP+cs+EiY2VldDQS0uP1kb/grNo7xNXwcmiJzqVLn1UIUs3fwUPI8eiwaLgsTA7zfbmoIL6YuL0aaVh4RKSbG6WvthtWISGqN8oTwgjf0Crd3J6bl7cpdg+CDH6dOUN7x9Ybi0/auEuyy31SLfKSZTKFW3NtaSNCmy3ccBgxPaKyPdPb0y+gWESropzu+gpJTDHQ+vRHyO4kNKJlZcc4ujyyK1RWs0uAlif7zkzhbTKsK9QajpbhdVyPfInPD622Mr5Zn9q3k5efyWuXc9u0wCEE0QivtkBP1zjTlOfzbU+3SwYItbFtJmDXhQCiAOv3hcABfPMSrayyVTwqyTRqwqQ3uU7qEX92+gFM+r6dNY/rsQOfPAQQmfTcwMvutHxr7Ji+60r357bpgU0In41vbM2T11A+5o8gwRHX8sh7ey8nk0+oFZ6uF9id5Uhuv9pkgU9a7aiMaYQTC5t9Xb+jCfqOxEoWeEhEaVkUmlnb/WLCP+yt7BA6n7mi7/xb1hYeXIB8HpO06erNd/rnyIBYPo3mBjff0/ZqavdA1j5jtUA78515bfeSEr5esSBe+BAsxo25rgjG9U6xLFPnpCLsM1HU2/yS9tVyJgHr+k8DxA/QGSqwM0v8RXW86ZrHP6Q2hoiTA94tyfERLZYoLzCz95U6DHytcALawGIn9qKfz07cied9dqd/mp3Ip93t4Qi4lC7f3ORLpLsQOT9xvF6NMiE/aC1gOjIE0mW2XXBhHjB3+fhetYIT5vdm4Gobtm85VDrp7E7KShyyhi6cWpb2qIX3hGSczD+Ff4zd5JaNtR+83gvZO3lJE2AC4v8UWNY7oV16mbCv4yT1lqQlMRVScTl/zNmdHqwEdqEOlDmeeMtnbdI8uXk1M4RYcORPm55tj+Pw+o/NPmj8cFe5fELpICqy/3DKSfxh94aw3uZQptVVuUZyuqBhsZ4o8tC8cd+u1dcZfDYwdTR9c8Gt1Ege8sM3TeihbXuXaX+6qc3xmLFdq5kbmyEnMSAhLkt3rSW28sJHptKxqybJpnNOd+ty67PL/eG3FfxlWlZsZmLh+9du/fDEBCKWFdP94uCgKD/v3I85GmBC2oyC1eEuh1vrTr395CQU+kR6BumaB1huxvaJgMe/jk3o0TkFhbhevmBEBWc3vr/J/zCIiXnlN4R2k/5tE+Pjsw6YBqoOJeuqyEk5BXJMa15lIYWHhk9/R4WH5dPqwYZzQkBTvOgPg1mKLas+6HYuRV9tpsUHR5oPwtYpCpGrkGNQ1A6SXGrhJWKD55WCY8qXlNOFlADn1u5U7UD2dpgzT9TFVzLmbBh6GjD08G6oHmFn4eLbc6zzBchb5v9/ul4LLyKVLcpiesqe/NDK09rzqqyKUX3GSR7y7atZGEY6mwshiNMFuirowi3TttgR35aDehYc/bkv8MvRoiRWlGNyWFbZUevWg3It6PwH7zZJd2C4utTX0JtrYzMMv80KnEBQYV2e3OYDvmgJVJ55dHqgZ8KYsC7TLpT3KEEl4Y6bukH0cfNcULOUt8AdQcTj0id6oAt7Y7ab2KXtwCNg79TeDH4wnF6c3p31paqatQjeN1r5jQlUGFdn7YB44fkgDem5QfdZR75aO1XSMgZ1cZDKKlZqbXXW38aWFXGOeNPaIdiMjDFYvh4EqDQj9FUJM8I3fJVWwVdhRTN66e77Z4l7015jzsgqhNun0eGrHtRfrnDPXz+c7LbgUd52u+d3YsgDbUc0dRYLylx3+nJNmG67i3B0BoaEM53pZNKSt5Szwh4OGmI+QBmH7LiDx24KErjXEKb4EU4XMtzv/IKD6jos86iuWlEuPyy0e+/ZVZsONYsJ16fLDqYgydeWNomVLW3Tah9PX3+T1ciYWvJ4/Ba+Hyibip6Ra6CbQT1Xu4Sidgkx9UTJ6NW9OiKx5A5Vi+pKLQURK+1LbzUXfvB3s939PNMXvqKKzm8ieiyKyYr8e7pAjVqEMcQoQSSObWC0xJglpuDbYHeZZ77oRL8RLJDFGRctzDOTJI/k5ORPuDBFatHb6UzrkAUz2XHikbpO7YCdlJvp/Y4qy1PDFnrKuneyf2r2Cpap/XnmVOpDFv9DdYeHoN3mBKwk5HW2lNLuoiBONwLvccR5xMmgz6u3hTZDi2mpDgBUTbLREaf8w9Sw36OZmVPGy4EyGf9GWe57VqXq2ioRETog1yHLFaIvt3diUVG6+SpDQBROCi25IDyxL4FFNImkcupsHhrTVAb8cOsQ8S1uqutbLvFgBFhX1/X9S44lhyp9XOCKfIgIy+Sem6wwHPf6zoWOmb+6cUu9N/ryyIGFAyVzA9AQkPjeovhJdkxZZ7uPz5rgi3d9alPshN4Lrla8i48cNZOGF1UD67bKbx95C2Wep1kZkS+PhVf4d+cJn3CeDTHhREh2fyKvsDqm+IfjoTPtG7S6EqJz8JDgsSQukaEeh5dEMtTnI3pETrYEjv4gFEp8zOy+7/xbH6ppSyNQICRqj/f41W0AJYT7blSdAMia2VTcXZPONLtuzYM20hGbwFs/+JMESibmJJuJf53ZY1T5K5qpGvA8ocfcB/tcHrHSm9muk3tFQNRjaodwDQY1hLtu7AbeR4rz2ZMQrf00WjylPop2zTVrjfO+VKYO7xsYwZz+e999WTjT3I4w2JE53a/n8zGV3StgB2393exQZFxzc8JQA8xVnwuSWAyJC7JPsFmALvPsKCh8iv93263ogwrrhD0rQfAOI4Lrzuu/6r1lzrqirLPiaFM2A+8+7xle+5N1WZ5ZTc+r40WdhSdNpweEkbIgXUPEyiiaQp74syrzKh/bHzN0pMKY12cO2AU+F2RLVZJ8O8OKwQqIidd475BZd7UFDgXR3ptbsRY7Ww125yrNDy0wyKUpJ4LYvd5msvQzY+Yu98S4SPdQ168etYiEEKOf0KYxWd0pgHTev3+ul7zIJFyu4OWFTYWj8J8W1k0ZWpzwDz9BoG39Zbf8ZL+y7yPqC6Lyq9CLpjlTUJWSUISdcT+VsrAEESPIjpWiqbU92EI/45KkrvaL5lIob5yMlNky1Br8fqgyFkYgF8j3GZrP3z+DX0x+HD3cnQCjNHggrj5hSDvr3IRL9CM2Y1MfUhSQXQZUGLSXa+VK9TnD8Vx64udvzxU/bFe/46vlsiJcZHXP8Kv7lDLnqXXP2ibuAiRVXxJcboNbIybHM1iheWVGR92sMBuhoZgGVer6jMsdAZ/ICB1IMj49m20cUzHJhb+6t+v5+XJF8qnzj6Rp6rAS9vY1gkjg78ropqtB49FRUQ7MNA3j6T/JeUZh9Gld9BWvKlTJL9kMCWPOnid3Y/4cL74So7YTyT9NXSw8DU/UoVLuzg53/bsie8xnpPdICUIGmvcOLRYTyrww7obaOHBFvHIkUy7sDRQoXOkELIPI/MQZDR5aUc+Qc+NM/nGE2nDq5tYCDzZkrzMfctBqI498+5wZxAtM8RKab9s51qtQKsOK1iXzlb1Py5xn2JmE1RMAViGIStog+LC6TW7z9BFGZubJ3HEpeElvJz91W0LJ4o6bPIP0IeNUdtshxVKPKGWKWitgNU9tV39vaavgrVZuTI+/j/27h1+VeLTzjpHraD4j9EHjRB6xBt0+3Qhn4L6bckH06T9jvrQwXh66c/TdxSscWNwg8YXuEM66Yn8nFFV6XFB9Qc2/BbBrjysF1n06j8XpTtHAyrZ5EUL03eD6LHFkqG4DHyliBCf9UkvyIrbNEYgNuDBUZXEx19b4Sr2wjqiW13UvDLHzBFyPR9yFiVPY5b7P/mp9S5gACvzH3omaUEEDp+jj0eMV3XeavjDsfKrVvu4e+m4grFlznyFyAy/aUaWKntCb09UbjU2F5s0D3skbX4xkKB1vD0uvjRQMMGwnW8+w+L1xbNV8fQw7e+UNw/kJhaQVVixB9cqzETdaH+3EX5l36eXJMRNDW0utq6r1kliKvC/VyJoRcRNg+KagbcC8UBgk0anVSeE3mgmTExx064o9RpwhfVSLfvzbBS2hUiYnXHcqr/TgRCFGfAAdN463zFNQIIDVF0S3kkY8pw9SgweKmlG9qMBgxjWKBpOfBIe3Q/2yA2tLtl0jeYlJ50OzSzVtk76CTZRYTLO1ZVnNAwejYaM6qnFRSiXKnbctCn/PyJZTXNkxk98tPT4+Y8MO3rlmdH3E5x9wCqKDCC0qw1PNSql+8wvniJtl0VXDyKjZg3mZySVZ1e2/B+tuVgB/zSzMxIs9cu/viBSFQnAAgxJPrToMFiQNLzBr0aviaRVoo6Zxrr5AruiXii8vnQovarvOVabXOKF7IaC01sH8pi3BdAhfjl76fpUeOtBWi/rpKfxzHfMUz83VhzR6r4iNe2kLxXW7b5sYmBGHTMe/PbKx4BzU558QJxtBdHH25yq4OMUXMQkyCTed44VQnHKKirlto0ikokWhJCViCxx0r2V+zqkqMI4aVoZkoa1sgCVf8+fypN5P4JLBF8Alsa8a+xcXJx+QLo4dYfE7zdb9Xsd/KKALIWmb8RanReehHxXzGmyk6DufRv7rMwYuZVqdMRXSir9wyzumiL59C/fu/7W56f5LxNna+z3r+aVAIrTQfF/fwN8soIaOiUYQsiZ7hnoQJYwpGdpAWEREuCACAzKvPzhXvr+IBI4sHMMc+Cd2UzTcCfUvSbjTU1MRBFQPtWjdoqbusuWFs6kNN/blePrH10XbVAvBG+3VlVAYO3SNAMki/K4HtHzF75ro0xLTRtYdW9FywdAHaFjoLosJDUf2M3S4+EXp0ETu8ibju6GNBsVacW+9y3pUpWyO3I+6CWWPtdQHpBoX0kWdi/Enegb6zk1ZL8Bz60cy4DEvP7N6I8JsK2l+kji1SFwDfla1tEsXewHxY9M3MfT0RlggsCPGymdV9LzBO/8Trq0D8amHwyt9Hj/Ldt2AS6zN6rN+DlMNua5zMvaw7O65wQ9fnHD0CuAD+VJeE5TnByEvPdzsKj9adRUJ9WOwWsVkQjv3R4pn1S9pXFUTcP3zJKzHvgP3KzKTaCMdFHkfHgm2THkge3ujkZchlKV9Tj2HcLMRSampk5m9vLQLOvEam+5P09Biqjad1DassytIC4OLDP2fUCeLjn9tubGXKh5i6ySIT1ReDaK063WICwpfd9/rxW1DeCWcnOPy8hs18ivQ1TSpr/YNrVbUDbGrsWQdY+fVTf8cLaJPQe/OljV5Vqiquja2GL51UqaFfd5+dN6Ci3qVzsu3zjR9eZKLlXkVslmFRsIQMCuIiEiYhwakj7+73L12lrFJ6V9DZ8wOemOGIHzqbZOs1N9o9g1FZbFrCzVKenr2pqunluIpGvPssWjUmZg/pvy0zj03Ui9NjX+JcetgRbl/UfDKBVxpjB3v0UgItD4mRGv8VTHnDxVXjXB2+Xl2Ss32oEuryzDBXvaQb9KEz8CiyhOjly/uiVXtMq74OvXQNbt3X+CIfBhqISjsvEqwFLoX21ypni8ZFLd6MSBrKeREMCR8sw4kaOpffd75PeJFUjDbwsV1+THk/phvXbHd/IfgqVhQQ9P7yNW6gnwEnVrqXH2isZjq17+zw+f1ygpuKPQho12ujzc+zykjNPlN7XmkIRt7hjCzSdTom36WTK7BCPV8aGsrEwZBgqMwQw778UI2+YvACKNo3kWyXJdFQB4i/yJxf40On2pWcWHqd4N07CUyR68ip6BJZ0FZc+rC7hzDd4ohn9FEL8Yj4dV058BnZ+RPav5F7H8UeHdmA6/qvbypZKYfwuUiwlfYj/edEsGBPcJbfSw/z9izlInntDvfzLsqunTK4x9znlZIR/gjDlfiL4ADDwtdS36hr9tnsWYnVFUzN+n8YZWfpwuXzg0T1ODVhvu/mqNUugUWULn4lGEzdaP6a7hLr2dfCTZX8+y9HiHStZmJfHRlA65+K0OcWJI9Q1sHlk8LJs+ACZenh5SJwqPqt6OQWiaSWkWgkkUdkXg8GPSn+gDxz5LINrWQYQ/H7OZ2efOt54RKD55Cm37+ym8=
*/