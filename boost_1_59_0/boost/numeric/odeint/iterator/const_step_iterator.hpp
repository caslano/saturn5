
/*
 [auto_generated]
 boost/numeric/odeint/iterator/const_step_iterator.hpp

 [begin_description]
 Iterator for iterating through the solution of an ODE with constant step size.
 [end_description]

 Copyright 2012-2013 Karsten Ahnert
 Copyright 2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_ITERATOR_CONST_STEP_ODE_ITERATOR_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ITERATOR_CONST_STEP_ODE_ITERATOR_HPP_INCLUDED


#include <boost/numeric/odeint/util/stepper_traits.hpp>
#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/iterator/detail/ode_iterator_base.hpp>
#include <boost/numeric/odeint/iterator/impl/const_step_iterator_impl.hpp>


namespace boost {
namespace numeric {
namespace odeint {


    /* use the const_step_iterator_impl with the right tags */
    template< class Stepper , class System , class State
#ifndef DOXYGEN_SKIP
    , class StepperTag = typename base_tag< typename traits::stepper_category< Stepper >::type >::type
#endif
    >
    class const_step_iterator : public const_step_iterator_impl<
            const_step_iterator< Stepper , System , State , StepperTag > ,
            Stepper , System , State , detail::ode_state_iterator_tag , StepperTag
        >
    {
        typedef typename traits::time_type< Stepper >::type time_type;
        typedef const_step_iterator< Stepper , System , State , StepperTag > iterator_type;

    public:
        const_step_iterator( Stepper stepper , System sys , State &s , time_type t_start , time_type t_end , time_type dt )
            : const_step_iterator_impl< iterator_type , Stepper , System , State , detail::ode_state_iterator_tag , StepperTag >( stepper , sys , s , t_start , t_end , dt )
        {}

        const_step_iterator( Stepper stepper , System sys , State &s )
            : const_step_iterator_impl< iterator_type , Stepper , System , State , detail::ode_state_iterator_tag , StepperTag >( stepper , sys , s )
        {}
    };

    /* make functions */

    template< class Stepper , class System , class State >
    const_step_iterator< Stepper , System, State > make_const_step_iterator_begin(
        Stepper stepper ,
        System system , 
        State &x ,
        typename traits::time_type< Stepper >::type t_start ,
        typename traits::time_type< Stepper >::type t_end ,
        typename traits::time_type< Stepper >::type dt )
    {
        return const_step_iterator< Stepper , System , State >( stepper , system , x , t_start , t_end , dt );
    }

    template< class Stepper , class System , class State >
    const_step_iterator< Stepper , System , State > make_const_step_iterator_end(
        Stepper stepper ,
        System system , 
        State &x )
    {
        return const_step_iterator< Stepper , System , State >( stepper , system , x );
    }

    template< class Stepper , class System , class State >
    std::pair< const_step_iterator< Stepper , System , State > , const_step_iterator< Stepper , System , State > >
    make_const_step_range(
        Stepper stepper ,
        System system , 
        State &x ,
        typename traits::time_type< Stepper >::type t_start ,
        typename traits::time_type< Stepper >::type t_end ,
        typename traits::time_type< Stepper >::type dt )
    {
        return std::make_pair(
            const_step_iterator< Stepper , System , State >( stepper , system , x , t_start , t_end , dt ) ,
            const_step_iterator< Stepper , System , State >( stepper , system , x )
            );
    }



    /**
     * \class const_step_iterator
     *
     * \brief ODE Iterator with constant step size. The value type of this iterator is the state type of the stepper.
     *
     * Implements an iterator representing the solution of an ODE from t_start
     * to t_end evaluated at steps with constant step size dt.
     * After each iteration the iterator dereferences to the state x at the next
     * time t+dt.
     * This iterator can be used with Steppers and
     * DenseOutputSteppers and it always makes use of the all the given steppers
     * capabilities. A for_each over such an iterator range behaves similar to
     * the integrate_const routine.
     *
     * const_step_iterator is a model of single-pass iterator.
     *
     * The value type of this iterator is the state type of the stepper. Hence one can only access the state and not the current time.
     *
     * \tparam Stepper The stepper type which should be used during the iteration.
     * \tparam System The type of the system function (ODE) which should be solved.
     * \tparam State The state type of the ODE.
     */


    /**
     * \fn make_const_step_iterator_begin(
        Stepper stepper ,
        System system ,
        State &x ,
        typename traits::time_type< Stepper >::type t_start ,
        typename traits::time_type< Stepper >::type t_end ,
        typename traits::time_type< Stepper >::type dt )
     *
     * \brief Factory function for const_step_iterator. Constructs a begin iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. const_step_iterator stores a reference of s and changes its value during the iteration.
     * \param t_start The initial time.
     * \param t_end The end time, at which the iteration should stop.
     * \param dt The initial time step.
     * \returns The const step iterator.
     */


    /**
     * \fn make_const_step_iterator_end( Stepper stepper , System system , State &x )
     * \brief Factory function for const_step_iterator. Constructs a end iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. const_step_iterator stores a reference of s and changes its value during the iteration.
     * \returns The const_step_iterator.
     */


    /**
     * \fn make_const_step_range( Stepper stepper , System system , State &x ,
        typename traits::time_type< Stepper >::type t_start ,
        typename traits::time_type< Stepper >::type t_end ,
        typename traits::time_type< Stepper >::type dt )
     *
     * \brief Factory function to construct a single pass range of const step iterators. A range is here a pair
     * of const_step_iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. const_step_iterator store a reference of s and changes its value during the iteration.
     * \param t_start The initial time.
     * \param t_end The end time, at which the iteration should stop.
     * \param dt The initial time step.
     * \returns The const step range.
     */


} // namespace odeint
} // namespace numeric
} // namespace boost

//#include <boost/numeric/odeint/iterator/impl/const_step_iterator_dense_output_impl.hpp>

#endif // BOOST_NUMERIC_ODEINT_ITERATOR_CONST_STEP_ODE_ITERATOR_HPP_INCLUDED

/* const_step_iterator.hpp
EwXdLsgbVFOBP4qM7o8zCjtyemINeXc+XBprTiwYuUn0SY7zt47ihvO35pZaB8mkCFNhU9On3JcJ7Hqppml2XlBBojFmO73OOMjffdHaX0aMl1X9sq6YJRos5ZRo4mLIr4CP7gY0zGZT2YYwU/Zd6k8f7CXReMoEmd0tQK/MLW+Cnx8XDq/U7Y4ko/pDA1iRdZes8ddbka5BOFEOx7O3BM7rfNFXuZZ/k17RiyG3f8JFSr0RxQvOFCRtPKFVYsAWao6DaOsAD5eaXbeJY3kcetBPX5ZeLj+E9bbj7r/esGQyw/3jvM1xxDHHExwW2mVgLe9KxP0VNKw1oEhr3eMG5Mbo9YcH8soquFZoYvUgyY8ijjMuqiQVbbLidPBgb6Oe0CufMiOyLTN9a5v/yKjtZ/LiIGa38zDK/sgrabHEqw1mzO2O8QzsmhINeZ5wDH08tn5hKTznrt49bAwwG2qS5MPTtg0QMHQHimwmHHLDZCMMmXMJS5x28BRApOlULsf57UQ+PuZwS30uQq49pcpgkNnyMYhBRF9o2HCSG6t1Bvhg/LkKfDRicKD1PNOV+7kkJfKWLJImpgEP6NS4U6hmq4fCKF50gQdrAmhX5aA9cRqhBz1dtMixgSnusGVFb0ub2F5huBYlkxj1P8QoxqstIDcodXlZxhtJ9jN2KggbNcMUcixJNLzOjYtNokLwhn4z89WYkLxif63ynBsO10rBjjAcoh2TKGJVwa5AcYPAmPIn/5AOd0hFCARajVW8Mq3q1rCZL282P+HbD5bKbMwXO/XkXoptitYjnFwViY2S28zCazk/M9hxm0DKMdO4b5WMmdOQalg3UhIvP9B9fP9WASbdBbDnoKnlz5/GjB9RrcpHIv8KfLpFDxoPWXZqRvs5f2GTH+imjYI9yl2+sjF4YzPv95z3RIQHE8X1JzE2CLVhmCK3VrgIDt6HHWcYj0GonB5mERVFR9ddA6D5Fn0Gd5laseWmhCQbN0j51Eko1Lp/yQtFqvu+7nHJdwRc95Z3/OSVfQFsuH/jRk3F+NvATnp67WDxvC7HqR1nc1sCGiynYlHtaPpQr/F1B3DM2eevL4QdJaqM7OM6LcaHJsvqpBrqu+wvwJ3K8a4xdY63186X946d7/E3A1008UbEWSvIdiFljdLX/kxCCOT1iPW9zePO7dxSDutwz41sz/H5Ax6VBi9f7YIf+KwBkB0EQQrb7i2yAAnySnVtbhw3revInm3fgCADVoRMFWr+9fSc0ksRNj+QHLoYHeNMr6D9I/aMyBHamju8fprOSfe1c8dH5tB2xZEI85xM1gO4g5vxc6n6XeAfZP+8dD6nJaxVTOzsY+Dt1NB5DK787F+pyyZFsV3c+A9kYFVLe3SzTXPo3WjHsPlYhpbZxlGwA6HzsrtbhMpkggR/IFxdR1MBfGUzUJWCYPEK2hm2KDz4v4ZuzeXRt7jN1XOz+26sRPrM7bd2VCVTa5Cfk0wQus90MGEbxvEbR7yWia7lPYiNQOCZDAZFNyF9/dGPRkzTx1QOfhvhugQT8pVq78I9J1+7xVjmwWCuN5LSTJeZsMe7Pd1S01UWLE5Rj+S407Ga5c5gBrqqnC/73eVgORWZLkCLW7OWikXR7+SN3hidKVtE8dK0idixujENMkse+hoRlWuRaVVqVFPJNzt40VLB5TskK3TofTdM5XMU+NsxklgySvmgKc/GpHBG4awBPU2SJg0vsBP7BKiak6fe/+oV6DrSBTYhxhJ43EkgVIX0YO4L4MELzBYpIgNuccem6lmgzRRcvdROlRdknHZp7lWgRxp/RreaxcX/kL7JdSQ2zaX9Q82MC/wTOi+AYWKuE+4nVKTYp09uQ35pPtRYWGiMgNgp3g8CgS952u4CPQGWhYmIOyPjZHfXf49ARhJ0TFibZuISSGK1BHNy6BSQzoh9CPGstty9W8i9nR3C22n2I/nuuX3T6XyxUl2h9UQtTk5mU7XtCNkzTaSJKisEfxz5MZAxJdk1vvmcB77dMsZuhmKmWNEK99D8pxdPvsPUkyT1BPncgW9m7ENcvJG7St9qboqmuWGaRdFqrO9WUz/dSNgbtNq6B/RKH11NweQFyMoJ7fBTVLZSeMdbJJWMAWoeHVoTlUbENbMFz3kO5GxJgVbvR3mNBg5nfhM3djtwsY0ZPUUjVJWRB2ojrVC4mbdvBiBzjbZQjcUGz1I0u108vxE3KMBxk0dpVUEYyxnewuhRcrjt3Xtb8C9Ziderzx5N5GMBJCMxFRc+DNYf0K6S5iBL74FFXAqFLVzS1wz5k3O/55jxB/7Yf2YNWDVsfM+lqhh/rdi61qGZtzOF7tjmL5hJ53bsWMQijpepBUPumHyqHP65THmmQ/muj6y/eh4+XpVtkAzaSYYmQF4SUvn0ZsBg8wu4ihn70e0iRceCc1wrhYVa1UVYG41hFMQlopyVMZoP2ijOKoC8+OVzZuDIFOZKvlC2Bw/+qYYtAZrMPYLfg986aAlzJPopE5nkj0DbCwLM/JxHq563tOwrZ9kokBq7CwF8DOs0cHt65CBetXq8NSVuCHHqJ5FwIEkgEVdJmJrv8XlIucoioT+El0PykYsrcrNLuBV3JinPB8uSKjQgUUxjVCcckoUiHKGwFalsuonPRSYCqdRuHNI3b2AXWdocxzKX5+Z45fxYOTmNEj9mHJZzzy/CnJGnP9ooTwc3J2BKDZPGFJ3HBGOVGzbmx5fZj0QCe54D9W+QyzwdFCCLCkBGeeJHgVvYI0h3EJR9jQ27rXsxRVsb6IdqXNuyfmXHcupanzWaf6vqZILlqBgt8Q/TUJixXA0bIPJ35qFGH6yTAWHZHLRcfbDjze3Eby11KTL8Hg8Y9Xc1tq11UYp327BDIfMxCV9YtUqv5ZeD+L5pykovf1068kR7DhYI7OObHi/MChUv8piUwtFC9/wTZ2CrdwxW2B93mU1J79HEDZLUk7g8Qf3ohg3IFVUsbgloqJ8g0nE5cBn9KFBMt/sIWhw5S5H1wmyx6wZzcZ8UYqBiH0QFva9MeauC0ZFB2kBDjT399xQwpJBq61kq3gSyJd2T5zQoDeKQBktFEf/dpPVe2+tb/bJcA1kAxsg0XLmnuFELWPinXSsb0MIL7LYMQWF1YQjEz6j/TBWlV4ZHjpHkgMpquJDu6c+ss1cBy/51zhQejVkmqq5PuhsmhtuDR7zl9bU6Fj98Ypk/mSJTrkhHK2LnGDObF+qARHkshd1Pt55yl6KtM+7nWPCIlWt/bCAI9Bfm2pEro7iv7RVc1+lpukuZV0FCUCblAPDSHgBB7D47iaNbcMDsRB1HGdgaUHaZzg+1LA2XzjcArmen1EHegqsDi4jc6VGoipCR41floEYWXLdOIEsJUfdnpNWetpxX94+iEAIKbLY5cQElmzOl7freUMSob9d7EM7NcDqBD/qmU5vAtiiV4j8KpNn54YpwaZxuhumKQdKdErAkN8znByCIY7+3NYe8LU26OAPQyTJLfavwaHlPMQTse5Dqr6zSU4Ex+7007CRCu3qlP8k2vE0zTwnWF+qHbC6ZbgK+UHROOReXo6VP+mWLegrNP//4s40+9M8FfxSvpdCjFuIvInXux522tHtkOm04bNWhBkejTzlVkRXNhUw2Pu6vBaA8qt1dCQC7/3W9xPtgqBQ15pnCqbpC0WLYzJII+ax3hiMzzlo9bS2pBw6wjhuZEK9ryigNfTlm5YnjBilgsrx3OUWfhnpeEDM+mthkCnY/eRTDxqBHsbdWqHeXVPDNwi61cbguzecWSUX4KN2R4sg+U8HRZerFcP9DkvVxxV5zZL7yXhBH0QFSA1ao83LaAZfOKW5q482MgrhumMBwaDo4XywLqZ4EmeDTrjhl16dFj6KzTYMsPQ2C9K0XtuZtqP4pNJrVXxp0CtLVYXakXM4MjE99njd73+qe06vjlB8L5v6BllbnA+E/mZPf24WKHDcSbCtpdnv5MsxEBHOyH1TGGG8e33KH26mf2br7a9e0kzXxxzkQNN/lGStKaGA8SWZtQoqbJWSRpZPtoEXuWvVfBi7EfI9qbKBkfRu9CD1I4r+1HezKgOBdbctPLSjuI2oOyFiWCXYs+Omn3jQW4Bsq+XVp9k76RvhrX7TFM1hLoBHJ6vuMwcsfUl2wwdXxwngGLaQXi0Dh29rUsjGcbl2EHV6qwLMvYaOZ8/N8E9iAG3aNIm1dmWGgQ+u5c+lOjG1xkl2dMWaq43Ecm1M0mIs+zfDS412+22ZDw3doj6axWN2FsetRVqAvv9627GW+4HE+/9G7v09GHMbXcDLZkDSMhhDVzRDW6rmDZA0W++l70xkvCK7lWysT9HvDVmpFU4l833y7VjCoaxxBnap+pXWpmd0Q4l4rkTCEjYt8rqmfb5+18bsjUuCpRQemaxBqjjA3Hm8kO6LxhEreteEuxB1dTXEVgHzWG8r82rG8wo83eDSL44EmUCI6nGoNUaMD+gQwpAJlZOaxFD9om7vFw61ER6JdTtU0GzYNYcYTyPfb1B3CVIMSHxZqh6+B5vBzl7XHDt2hqlaV/FVEx8IWurJ2j/J22iMUR2qE05LwswgHYfiBUGhHzkFFXzfdpgwYdx7k7rO0JDZytVLk7clw5BC852oedOA3FwqbgKrEQRUhomVYhCjqaDvWaOdYOZ12Cx6ea5Vfmc7UzR0CLwtA2/LQjyb8g5kqsiobvWes1gUMULrisQD6V7TSSgTce6JUauDVHG5fDTUjRJ6AGYmePnerCkNOXVAfDjJrGtnxD9VkC4u0TSanzTjFC00SRSHGyWuciEOt+3cGTx0ntjF/UVjeDcLIL/pIZt9L6kzIdh2Qgd+nml5TMkEtdXPo8Xv9t82ooViho7eRwme38P/NYtH0xkVi5BbS2vIBm+PlCqYeT0XxJWB2ktlzhN6UiXhxmsn2l/yV4Qu23iBcQzlyBYP0p5uxKHgwfR65stOzEwQZNT20T3WxhiUvMNN+dbY2e6eEOvQ0OqdE9U0C1R047vDg/a4WReFIevOXfR3clkHswcXjdmxFJdSePcSvwGNFH0hy4bi7rH7PG1NzR9xC6do5LhirD2BbZydltsRaHGivSEio45eSYsc8+Bc7uo3TzkoYzOJdJODUT5ARDaFYKjOpUbeXHO2mzuE21ff1Zu6WFoQC9LzEmaseQw7ELB1xTN7N5Wl5+QV1RxIROlS3wDAoJdiBU96a12aaOJVDb1a74YOu22jKtCnswfhoBT8uf7qBZyzDP6gF2aj5L5mdLkf2AEsTvQqb1E6IS0NcCFGWwfA24ymCcIS2AW/B732xkuLV9idmlZJhIncIlqfqOCZEIdSO5NEP88B3DKahaPJUYF8W0H1qXvAuPtcrN7K3faiTBUWtL1SJuShSXYS9roe6G94tprvj2xmLT3VUbOp36ka+v+plx4ZYxds4bom+sQwc7eEWN8TArFryAlMLqmWXmGJOPeU5xh8aHesVrabzIHsTl5VaOyhDdDEW3m+YO0XkjnbpTb5cQtgeOcb4MyGR7fhyo73RizEqReEYw0zA10wu5R5C/BTZAeqOP9ne5pslgbLC4fLJJx6q1vJso2ogh53RXQ63uhiLcljKmt+ozLe5uIim+jQfMoDCkvBeNbHDPJW/KsQjP8LgQLi7IosqqjYj8PZfWpTsSZ+x4JJP4+4oUt/G+TSkcAq93sj++bWLB7YvRCHtghpb9e+BDrjSSwOJ1YVSSJFWgpQPtcdZSZvLJ2POR1FRPqs6vVMZt1O9YcOwUNEIesvwfsgwjTD+K1P+u2mNSjfDmKN6inhYEDpH81WgBSz/NbquSHCIlOKrx785Pcmkapp78DQxksukgEsSESZjksx5wFHSy7ODbSstIaB77xTadiO7IT6h/kYT5WS/GYVNXjtAINruRXDEvBB8TreZ1zwh1iWaNEQ1g2SRyjb4I/e53caUeIv6Tr16h4UIktBGYIqjG+VGtaFDmtbj1lPLDR5cz92cpsAenhlxnxxGMW4g/azuWr3Cd9tfB68S5yCmWN2gW06YTuaIJlr+htNN04yQjYZ9riSKV3oQ/2WpZjyn6uYloh1qHRKh4Kjpwk/cFWTqAHIq45RbhqkRq0DVb08izrKJN5OLonAHsSzkDCdqfEf403089Q+eJzjq4ZCIr58ZMy2en7E+uGjpa4gmqZ2zbIrQegcAIn3oIpxW1EyZ5SufYYsbqTQdxploq16bVWQKRSR7gs1uetonp7Yf54ZT7+F4EYnoGWDNwgRyHb8lKOgKgkK3aNE4akwv6DvifwBOgLF/5lzaQXpiGAxKAz9DQY6XOZKjaTVChxww296Gg5f4P9ScXdF15jBdWelOlPi8qfp4fHPcciaDBtxMjT1nMdgGZq352QhzXMySp20pVEygtU7b3a1GTZoFUCZiAJyVit9uvhAWen+s7lK09rT5Pl6nlVmQCdIDI/QB3in6AO9+/SoWRE9UX/q6L+lbMI8aVf4/qaYod+P4f2N+4RS3Akj/p7EiNyRXlnrYgnISmLBE0YJNd6HXhu/MgAoT4IZCL8yvImVnjAzwejQwq0Kr3Gw3bXj0eeazAKYwVh33zMKqLnLeE2dChAh+mb3/WEuEfAZBxTfBsZBpZSNe1wtnJhlSDQaN0x1m3N/6lckQnVsUf2M0/61QEawlZOl0xJtnY4uLnPJbv9a5cW+ekSmCObjrltMD7JxV5Wwrd+o2c5kEhoswi27Qm0VR9hfgqiyuosOPBcxUTLHNV9DqNavJz+5m5jjLI7pAi6jo8pX2KLoE6V2q0W/n0BOWvArZk8GxudLzKto8QxD9QkZH7restBMUwnc1swJWlS51LvTQXOiluYA64bu8NAKYWqGWoBGfVYUMiYepUkWrwTOGSa0cXYtT6vI0lVLSWf2FL9UL2Ft87oD+8mHtOWAUqZmuodryB/XCVdhblI/szsGSBkWJY1Lv7KAYtRweagnsuGUfwQA02vZypJtJYNuQXB2b58gBUjvGe4ZTsc7gEPwtvKcgSIdHh/yMCemcY4i2Hmjo9THWhfrBrEslfrBqqbpe2Ax9NY/AdyZjaQIynry60gQZ7BUs7IuoQMAy/q1Y3tdf3Y9F1mFcXFwrQAZQGvmR0sh40n6zchvJVPLPTgL1dxSoCmXA01llyfhg8CZCzLPp7ilDlZru8heA+LEJcyLeJxZcVr7S6eKfpn3VgBz6RPXPaRidwLPXixKL4H7r6W4lNsFtsYfsfXaEA7mbrcUvr0v2DMv7oI7KEftXJRFKXrP0hdlrrjN5TfY+UZuwqgVPeLQEH3sLCNA0ymRzJleFPEbpkBFvAhbciauu31SEm0Kwsu4kCetGrsxRuDIDmTBNZcjsa2VIHWKIyIfbuEW//l5bdcMZCW6w53WELb/K6lvPq9fNY7W8dN14gR1NR17rIIXTwjDKHg1HKDO/qa3nAcImq0WcMi2AOGYlYkImu7gzbLX/dNulKJ9/1fgkQ1kNGq8cEqTAXIx1BhG9nCWxDVRnsMUpn/nj1yGn/B82XZ3BUwatzuDdos4gPHFAieKYiPkr9eiYT1+HA8qOycefpT1njvFSUwfm0aP0VlFF0FuhVBC8WakgaGE1C4+pt/H6ep5iBadE1Af0fqXU
*/