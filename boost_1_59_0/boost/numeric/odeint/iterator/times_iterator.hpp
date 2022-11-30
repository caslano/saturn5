
/*
 [auto_generated]
 boost/numeric/odeint/iterator/times_iterator.hpp

 [begin_description]
 Iterator for iterating through the solution of an ODE with oscillator calls at times from a given sequence.
 [end_description]

 Copyright 2009-2013 Karsten Ahnert
 Copyright 2009-2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_ITERATOR_TIMES_ITERATOR_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ITERATOR_TIMES_ITERATOR_HPP_INCLUDED


#include <boost/numeric/odeint/util/stepper_traits.hpp>
#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/iterator/detail/ode_iterator_base.hpp>
#include <boost/numeric/odeint/iterator/impl/times_iterator_impl.hpp>


namespace boost {
namespace numeric {
namespace odeint {


    /* use the times_iterator_impl with the right tags */
    template< class Stepper , class System , class State , class TimeIterator
#ifndef DOXYGEN_SKIP
        , class StepperTag = typename base_tag< typename traits::stepper_category< Stepper >::type >::type
#endif
    >
    class times_iterator : public times_iterator_impl<
            times_iterator< Stepper , System , State , TimeIterator , StepperTag > ,
            Stepper , System , State , TimeIterator , detail::ode_state_iterator_tag , StepperTag
        >
    {
        typedef typename traits::time_type< Stepper >::type time_type;
        typedef times_iterator< Stepper , System , State , TimeIterator , StepperTag > iterator_type;

    public:
        times_iterator( Stepper stepper , System sys , State &s ,
                        TimeIterator t_start , TimeIterator t_end , time_type dt )
            : times_iterator_impl< iterator_type , Stepper , System , State , TimeIterator, detail::ode_state_iterator_tag , StepperTag >( stepper , sys , s , t_start , t_end , dt )
        {}

        times_iterator( Stepper stepper , System sys , State &s )
            : times_iterator_impl< iterator_type , Stepper , System , State , TimeIterator , detail::ode_state_iterator_tag , StepperTag >( stepper , sys , s )
        {}
    };

    /* make functions */

    template< class Stepper , class System , class State , class TimeIterator >
    times_iterator< Stepper , System, State , TimeIterator > make_times_iterator_begin(
        Stepper stepper ,
        System system , 
        State &x ,
        TimeIterator t_start ,
        TimeIterator t_end ,
        typename traits::time_type< Stepper >::type dt )
    {
        return times_iterator< Stepper , System , State , TimeIterator >( stepper , system , x , t_start , t_end , dt );
    }

    // ToDo: requires to specifically provide the TimeIterator template parameter, can this be improved?
    template< class TimeIterator , class Stepper , class System , class State >
    times_iterator< Stepper , System , State , TimeIterator > make_times_iterator_end(
        Stepper stepper ,
        System system , 
        State &x )
        //TimeIterator t_end )
    {
        return times_iterator< Stepper , System , State , TimeIterator >( stepper , system , x );
    }

    template< class Stepper , class System , class State , class TimeIterator >
    std::pair< times_iterator< Stepper , System , State , TimeIterator > ,
               times_iterator< Stepper , System , State , TimeIterator > >
    make_times_range(
        Stepper stepper ,
        System system , 
        State &x ,
        TimeIterator t_start ,
        TimeIterator t_end ,
        typename traits::time_type< Stepper >::type dt )
    {
        return std::make_pair(
            times_iterator< Stepper , System , State , TimeIterator >( stepper , system , x , t_start , t_end , dt ) ,
            times_iterator< Stepper , System , State , TimeIterator >( stepper , system , x )
            );
    }


    /**
     * \class times_iterator
     *
     * \brief ODE Iterator with given evaluation points. The value type of this iterator is the state type of the stepper.
     *
     * Implements an iterator representing the solution of an ODE from *t_start
     * to *t_end evaluated at time points given by the sequence t_start to t_end.
     * t_start and t_end are iterators representing a sequence of time points
     * where the solution of the ODE should be evaluated.
     * After each iteration the iterator dereferences to the state x at the next
     * time *t_start++ until t_end is reached.
     * This iterator can be used with Steppers, ControlledSteppers and
     * DenseOutputSteppers and it always makes use of the all the given steppers
     * capabilities. A for_each over such an iterator range behaves similar to
     * the integrate_times routine.
     *
     * times_iterator is a model of single-pass iterator.
     *
     * The value type of this iterator is the state type of the stepper. Hence one can only access the state and not the current time.
     *
     * \tparam Stepper The stepper type which should be used during the iteration.
     * \tparam System The type of the system function (ODE) which should be solved.
     * \tparam State The state type of the ODE.
     * \tparam TimeIterator The iterator type for the sequence of time points.
     */



    /**
     * \fn make_times_iterator_begin( Stepper stepper ,
        System system ,
        State &x ,
        TimeIterator t_start ,
        TimeIterator t_end ,
        typename traits::time_type< Stepper >::type dt )
     *
     * \brief Factory function for times_iterator. Constructs a begin iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. const_step_iterator stores a reference of s and changes its value during the iteration.
     * \param t_start Begin iterator of the sequence of evaluation time points.
     * \param t_end End iterator of the sequence of evaluation time points.
     * \param dt The initial time step.
     * \returns The times iterator.
     */


    /**
     * \fn make_times_iterator_end( Stepper stepper , System system , State &x )
     * \brief Factory function for times_iterator. Constructs an end iterator.
     *
     * \tparam TimesIterator The iterator type of the time sequence, must be specifically provided.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. const_step_iterator stores a reference of s and changes its value during the iteration.
     * \returns The times iterator.
     *
     * This function needs the TimeIterator type specifically defined as a
     * template parameter.
     */


    /**
     * \fn make_times_range( Stepper stepper , System system , State &x ,
        TimeIterator t_start ,
        TimeIterator t_end ,
        typename traits::time_type< Stepper >::type dt )
     *
     * \brief Factory function to construct a single pass range of times iterators. A range is here a pair
     * of times_iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. const_step_iterator store a reference of s and changes its value during the iteration.
     * \param t_start Begin iterator of the sequence of evaluation time points.
     * \param t_end End iterator of the sequence of evaluation time points.
     * \param dt The initial time step.
     * \returns The times iterator range.
     */


} // namespace odeint
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_ODEINT_ITERATOR_TIMES_ITERATOR_HPP_INCLUDED

/* times_iterator.hpp
+iXB4ENw2C5tgWzvBM1L2gaZhaS6eLhuga8gNx6FKtjet+2TaBaJtV42+PETZLewLKbMLrv63cruurmqS83jbdFn6Ly0eHnpmgt8NB1lf7VY+yf2V4vE77O/G1VLHbcLwdmA6q47y9Q72j45Bvw50cxdT8FHEyqALv4loMm/YAimLWH3yd+NmnKfnPkPRdb2r6F9cl1gf5EZgmhHJ7hd1oacL3HT5on3sJMu5qYUvlsEBs1ZiGGnT90n1zl4q0qt9yxQO7lZo/Zbjtq6Xn5IgNScjFqriVoRr8EWrb2CPmi2vUzfDU1vuY3xevuUURMxZU5Huq+ocU8nuF2yD0YGbi38MYiEaxiEThDd5qHP72SfHaF17exN0aCL9O3Ep1ttgiUcJ/8m+2DA4mYLIJoJ1aSY9l7DMfJ7Gcc+oZCLwHekCOEFrHOhFwwutFOFPm0VtF3rEKNtuwFhE6p/91mIpn3PaOp/lZvflOiEit4yN1PlZoWBmm5beaNhsFptOEZhVbHdBdw1ntV7Qtu/h7irRO6ygty9BmuVm57nV0ZVQeOZl/V/E447K8+dt33381DgNjXSol3Db8YmQ4dqFm/YrR2q+crKrLTNGv5QzTOx1L/34O73WZN//4fcDBX6CvXG8dDVZuMIMzB4nTVKLDoL/eF1kiaRNm7bX1zPTxbZ+bIfCRx0WHdV847rRhJ7VWppSG3vJo3aG/whg0p2Qp2j9i07U7TXRI3rXdkoUjeW26dScyC1pUFqb/Jtexqp5XDUZEZtn4laTrjpxp8v27iDUmtCB6VmW/iYbZ4+7KPdXdt+0Gny1yadHlANdWIcDJXUaaz/gXOjRY+Y3KgvQ2DQEWL28LgpZr+lUjuI1K4JUjvIZ1paw4cQpFbKqL0VOWZrTrnvOxRU0yLs3NY2aLMtZZRKEAUVG15QcgySOSS2jhs8uh2ose6mchy6m/t8GuuH+RXoV/nODXH+Lj2cRx/iBWXo5Tuge0lj3QvygXhuVnnfbw/fy5+ko4C2TlByybhJyV2qfS4eB/t8uVbj/W3cp3mN3zkp5gbeo2y1riuSkjPNSu5WJRWPkloUpPYOv2W5x9RPbGDUuiN5+qUxk6cfUU1qYAxM6t0ajdpRfqfydezSeE+/ilE7EsnTe8ZMnt6jSrJ1DCRZHKT2n3zb2rAzzuEk+RJbueyJ4Oli45hpIepdVZJrx0CSZ7watWN8297g1/CQ2q2M2rsmavy4fcy0cnVclWQOSrI6SO0E37Z9KMlUTpJH2bny4yZq3FJX5phpqes9LWaiJGcEqb3Pt20/StLJSfJuRu09EzVubezSGdPaWK8qyf4zIMnWX2vUTvJtO8BvwiC1kRsFBm2klnJFJ/LiG6faW6OxYg/bf1Mapn4H7Bbe6Y7wDlgbvNMSCc8b7J3KSHj2sXeKIr1zgL2TFYnWfvZOUgOuFXWokrx2wmYxrF9BWVi2KyLmNAQDXe5FFuiy7Kb1K3Z+j45g2v4YWn3QBbp+Vc17UM2HqjU1f8Bv3L3FB2nEaZ8vMOgIgQ7TH+gD3SmV2jqk9osgtf/iu4SDpkXJZraseCpSoCs5Ywp0Ayq1TKT26QaN2od829r5BXOklsaoDUQKdClnTIHuI5Xa+ChQezxI7WO+bYf57SGk9od5AoOOEOiGRk2BblClth+pRQWpfYIdVCfXQekCXR6jNhgh0HnbczrhlMs12vqBL5NqhK0fxBB3Zhl8ftInto6aOs0/adpFnh57WuPpz3jcoIvnqZjjaf/1AoOe2pa87Qe79DztORSGp2IzT0MqT2nI0ydVGk+fopy6p+JpHuNpKCJPOd0GOR0Ow1OSmafPVJ6GAsDT3wd5+hzl9M5UPNWzE+ifRZbTOwY5dZh5gkii4jx41mZhMafEMNpKCzdQlM/aLKEvinoDwYFi9zkWg341xYi6lI4w26A4sXrAWSePL9SObX8AOrbbKjV5/IVPP32Un0YhzuprBQ46fAzaFTDFoC9VapuR2rH1GjWFTzXbw0+rkNoMRu3LSDGIrTHpYtBplVo5UlsdpPYV37Z3+WkVUmtlR9FPR4hBnFq++Zqf6JSG1HLTWaaW9VOo5cS3qP4RU8/QFgjNyJcEYHTz4lMa66P8COCYaaJz+ofhxu8j+omOeSnkDHVHthdXxE0Gcthm1ggvZu/tk2zZFxZ8K9K87VDk1VIeR3z9UPx9YrJiRtkc9gZ8mjc5K2/dAYsUox7n0FnemLwz5QRkuNAZ1tFYwcSyN3uyYoH3EJItjyXTh6FwcNzIbDLLSQ5YSEzZLYVuJaFnFFZzJYHTzT+M87rJDOnm2a9t3C6MeWHh5v+hLjMOLpMSMIWQr+Vmi91qXFhIiDUvLMSbPeC/Zb/dbjV2sienmXcclBFTp3pW9jmwcK9u469xmnkLp2fE1Eee23gkngKv1HeBq6YJEWbxc8ds2leYl01fYaIkL5yxTf0VZvov+a8w2feXH3m5fFXJ30++qiGlmg7YtHxVw/X6BKxWuV2xBJO3DimlDrV8hIUvH5Eq+8ehwHFlvr48BN58nN4Ujxvw2mR/Dqt6PI6ZbOIdhrxe4l4DhCD7FgtWLTPzkPJRjBFiR72xBEXzEsGqJbcdUnYZIfgUQ1FqiqF6RDKk/P4Ms3KnIcWQohRcsKkfapYbCMbIzWkhgorykxhDst8V9cbqEP6MkBQUJdoIsMgAMI121iEhKMoH0cZ0wgaAWLk5i2ep1QhgMQDEbTyySABLVyk8Hm3KPxwF97MDtimyRQ4pPwzYrjgRm+774rhazr4zvh/77lFazttCxVUC+uIqAbeYgRkUe5QDAabxu0250u45b2OfFadV6dMXCXJ7LhXWKpbvqFdZGqWVK9ESHsUbIOzyzjwKsZxlcOpVkk0Q45V6iCjZ50aVY4qkXuUzuwGCxEFFAXhH8q+gV1FkGKTmIrjnKxa48uXRsm8FMyDGcaMRm5hnoB8j+4oQQuX4PhNEpgHCISPNIMeZRohPoiZiX7UQP/BM5rASLAWFyrpjo5PkdslXgmyXwkPfwF/BOQsR76yBO4K8cx38a18L12ypvRr/baJXuX0z9KPdSZi3uxxhKvFaA9eYoOanqcnIchtYMrLDXzHNBwzJyAaUB9gwM1ZMazCmkUM2VTkOKHmCVuBN00ozPBftDaouSnktxMvYPFVCA0qCCdoP0AShJD80XxzaqmJaw2OaLqNwgpi6bSZMKDw/QIkHt7YaMs+hUFXdDig+I7S42QCRKPvW8vRWmOmhYvwgfrF0qzH1HKolSG+2Gboc1c5wgPLETLXdofJAVy3X4E9ZjfDUPBDKYYKasVzTVYsRSlSe1fM5U95ZHfLSAeVRK1Q+GdYBeauGLeUOIjDrErsNKJJlvB80kHQTqzMJviHvBNsVWxi8NJMrATIryPKoZQoG7GSmNEesNBCfvUrTz16LgSx2IpB/7C82KtvlLxoy2GEiKuboT1rUrGnTgsC1k+U3yP5Gyq/yrIt29a4hfbUXfOJ1zQ1Xs6lXcVCSZPoQDEDzHWLxs8ZkeJD6U80D992kTat0qqfdAYnZZgFt2lnraOOTGHgy6zglIS5WBepxcOlsMPkay033/FQkegDR60ugkqWjUEcCn7TSJ2KagfmrZd+OkLZ7lJ9O2iw61GKyAeIHcnsLdh0o7R4lzggB9bFawTIm6o2mnLJco/PBZSMdVmVOl2Fvb5Q1lGGvYQ479fm2Dqzm48Saeuhe/YuwIg4cx2SFqQhWxpL8pdHUL/37sWpMdxR45wBcm5Oi4XcgCp7CCVCp2Q53mhfD+81wSpEGdLjT3gHv+/rxqsC1fRzxXMLrIoTKhasvD6/F9Bo+EV6Pcuhz25Xko36LH084v5/xxKDiHrVFKtbGklQOKg8PQ69SvkJfimEmBW6zwejRWCdBkP2tuVxlhYuXbGErP3R+ZtMKHgw3sNowlz9nHdgMU124VtqntdnDFRWJgrI1HQ1QtmbDI9oUOZqf3d/BFYY4niRoQGGKcxibEiP7t/NN+ZGhKab6QXTIsCOXK7vy3bcGAGelcSDc3JLL8/dteGE1fmrTcqbuVoV18jPUywa9oNaPqD29Tk5tcZjXMSBuaoCUfSvLwqSk9u3iOX8p0VTfJ9bE1eUhm5Zus1rlKjssV198hVxNN3CVABRcAbG4AeufPGyu47rxyHbMIqRyNd3M1XQTV+LQVEP6QSVvKLLDMX9b4eP8Lf778TdFGTptU2tDH2w0ZlN2jYs7GkEIb4maEGx88Zr7gsm0FcXBjkdZgw3XpbHG7U1d1neKuxJx3yOGyRXk33U/h3s3O/MjhMeNm5m6TO8UdzHiFsQwvudPe4DD7Z6u+V443D0G3DGAOwdxv/JQmDxB/l0PcrjPxasZgsLibhwz5n+nuFMQ911B3LE83yKHezvDPS087hID7jjAfQkNeuxBs5ttPLLrYTRoB05LcxjuuLC4g3arKI2f2Czyz61XmC/1t/8v9pv6ZWh9haXrN1hwchPmf3kgnAWn4oKXKtGlcQYL1qcOv2RwDzo9bYmCMQYb9iivfGMLLt44gos3CXTO1d6KHfKuKJhoGLDYZXy6ShP9vWGxOMgcqRnhjxvgo6jqoqxa5ltFufabqcKMonzx8RWuHDB9fczrKzWsvj4k+UlBbV1F8pO1P4m1G+CcaEU8WerIjk70PyZg3rIyK3lf6YLR3y8cBZKLjo+cM6BMbjIdfhNX6oWBH3TcYLHYLNPnbaJDG5cjiK7mFJCbSVwpZOseO2RpdJNjk32UvERvLXWkR0uuZDhaSoeTWHg3yc2UTAm5CyZnlUARxKp59EF/eRJxJWf3VE1L73wuvevkhDWazJbtsWSZI7uz0kY6JcpxV6L/FTow81alWcpXEU8mcWXQIXEhme0uIMvs3kAS6ZaSyEqHlGsny+ILJLeDeJKk3HhyXHoguXBylpsJHmUkrFJVQKqVKCi3ONl7+k4Y+7lSTqchEaeFmoknGRrjiZfyk0biiSuJ3pBc8ZInieSnEIHUY6stBazVKbS1wZtWvAloJNd4xTSUZrKUP45iIfnxksvJSybeLBlKWfYMFhpl5yZ3ONzqG55BwdOPEkyQPClSfqB8FnE5s3urEtK7qBiJJ+XkhNApRZNoKkihi4nSW5VqoeIsv54kpHdm926IEvIHR5Jvc/VXXZXetbBPcA0mbu+68/ouoUdKQFmvIK5Mkp9B5wZU0AmFZKUqawdFKrntZGW8lEsNx00FxGTtDsraqpd1vSrrvpFbqUBgm2tRAW545TtITAGVwkoqJJNIPMlu8rO19L1eYJ3yvcxBXIH0ntvyUzbEk2jalnTXoBQ9kkg8/Quo+qNHooir3wptzk54+gm1Df9ne7FNYS8j1xDXOGzeLWKbdi4HKGklbZBy79ddk4TOcujPsr+Didsw31ajm2dYOP/OquPyDe6KkL/aNY94Mshqh1QLpWyIK4dcJPlpEuakpV4ryVBji/RInh0L+zZ+arEstmy8CNfExq5OJcY7ZJVWb5ZqiybhOxZIsVhuL1s4YiuzT87a8eQBGiSoNbfQAFbjPpBB55bK5bzApCxDyTDl9G1zLQs7JNel7IFygfzcTvVUjrNF9niQPmaFxBb9IxUgFhwDjiGKs/sHH2IL4tRW06lP5SenU2UXkLvs1PLXMkzwmpLxYyq7JoAntXhQ3q3UUuRkuZ3BiKmW49T9yiwSpo1l6AopJjyCDg8oQpG50sI+coRGMYv1p3ChQpBc9QDQme7aJHkaF/Zlu1pIXRF9JXFHl+TZ7p2wVtxE6nJugOnF/oIyJ21lNcSrCWfFArJlyXxQQUf6lhz647kLVPRJ3gnb0zO8Vdst5fFHXVA9wDISS2/T30xfWbUdFcKkq9V7OJXOcZMT5cv0Nh3/Xk22rYU5ZlMxtGFbOf4upb9HnKRuHfyrxSd1lfgbnhAP9bXk9LoSSlzyDAnbiuazuO8UXihm92gwoKGc1JXSvwtcAbmpHD9cyR9Qag6PwtkVgciIVkWolN1CxeWmwssf0tyboiiyU7egPgGAH/cjoA1+30OREFcr9VKyzXkDfO6QIk6yTkmFTQK3olEvl/52AgasN+eWt8Dr1A1Wbx551FvVCO5NIKQqxOOUXJTvYckTKJ994cMLAwVuKCdFVfgENcj8TQvyA0hySCPpNJAcRpIKkgyYSYJuEmthf5VUOCmDEK5WJ0sVgfSKFkqW5NdQ+kJn+ofLvFU7LMDLakWqGE6s8VIq3kPgKpaKp8puYR5SdjMZUH3F03jhfyv7Hvgmq6v/J03aBgwmaMFUCmRQXTG8W7XoSyzsB8iDoEaT1DT40ajvto/r+vI6dIlWJQikrTxcknUIBZVh3XCfbjJ/3WfMFS00FKTxpYOI3ai2um5vX3+3S9E6/hUtPr9zzn2SprXIts+oee5zn3vPc+6553zPuefe54NpJ2Z7q1mcyb2Re7NAshvsh0CKyJZV6iulN1EGQK9WSmVuxdnFnDvdoGKZd4f+iCsl3OoUS9U+iXgiVwezMRlS0stdzM/18g4gh9EJz2yJQfHvBte3BuWH0Yes0tY+j9G0HzH4m6COw99rjqzHytewDXsMdCZpIjVbv/sd1E+9zAvKh6bE7kppOcwoZ4LRyauKv0sBGmRQcvI8EI5iIBe7cIueXe6InFC8PdD0lqYcKaUEQNMpwU5UinWpji4shI78m0HFwrRj+/GVEYk489Kz2Gdvc9mPoR7wlKcmLk1sfNkSGLb+G+FPMjeyu1DMqJ0YAJiC47nSyIwl5xTnTiXY4PixIXCl48fGwJR2uQENUNKEV7lwRar8KH+85gs1HDsVHprwZLn5jTrjv4cktXDbmVtC0oGHB6H+YhasW4+flNSd/2jaufUfW4CG9Udsn8Gt60Exrv8Ybtmogk1UkEYqZB9Y9xnaC+bKwyO1BQjYKgWuYvJGkDAXHXqfEul5zNsAlmHdnhyCEZWSp5zO4RaTFYcJ0JUnD7/yJyDG7lLjmqu0spgoA0HdjfJqrknihqBgH8hL//9eBI6/WgIcX2RgtMnI5eEr5lGUUhqlhCVN1z6abFPTS7U0YMZ5+eOu0ta4xSrtfImph28OSUfh38fwLxf4Z4J/koH+p8vSj7feZdqYYd9aLm3fwgvv2rxPMoKBA/8D4FJkOdC09toS1bEwADeCFsfC1fhfo+PAIAxr8AYQrJRJB5AGsATUCVr0AncZOwbghA8cmyz1/36iJJX+JZDteMYWxCN6X52IKQV0pjDPBn4poWHHfpR7c/WKiZL2aUy0Y8p+ZJOwYVhWcb+2qCsjMJsHwwnqvSjitIDkrhI2DKvxim/nS5FtFeJgY+qm86Z8CUjiw1ecghm3rrQdEM0iGzSygBoBCOdcJ6wmCq9j30ZA6cEcZT/ZwdtsKD+uzLPY1SnF8KAQNq5A41SpDivVKaGtSmiHEtqpTrGhxMmdzJk433X+fZBDZ51byCFW1mibi49rlVzn38fJrelfpPjpElD6RxVSV/ylG1E8EoC5FFAfzi6XQtpW8fYBLI3Q4dOKkwv0ABqd7186oPKq18+p+CHzDfAw8OsaflI9RQWPQYGy/2Ga7IGJ7YRpCDzeaQMqtwr2mtg2POxZ70UTwUhKS2KIbSQdYhs06zFhIB3E
*/