
/*
 [auto_generated]
 boost/numeric/odeint/iterator/n_step_iterator.hpp

 [begin_description]
 Iterator for iterating through the solution of an ODE with constant step size performing exactly n steps.
 [end_description]

 Copyright 2009-2013 Karsten Ahnert
 Copyright 2009-2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_ITERATOR_N_STEP_ITERATOR_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ITERATOR_N_STEP_ITERATOR_HPP_INCLUDED


#include <boost/numeric/odeint/util/stepper_traits.hpp>
#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/iterator/detail/ode_iterator_base.hpp>
#include <boost/numeric/odeint/iterator/impl/n_step_iterator_impl.hpp>


namespace boost {
namespace numeric {
namespace odeint {


    /* use the n_step_iterator_impl with the right tags */
    template< class Stepper , class System , class State
#ifndef DOXYGEN_SKIP
     , class StepperTag = typename base_tag< typename traits::stepper_category< Stepper >::type >::type
#endif
     >
    class n_step_iterator : public n_step_iterator_impl<
            n_step_iterator< Stepper , System , State , StepperTag > ,
            Stepper , System , State , detail::ode_state_iterator_tag , StepperTag
        >
    {
        typedef typename traits::time_type< Stepper >::type time_type;
        typedef n_step_iterator< Stepper , System , State , StepperTag > iterator_type;

    public:
        n_step_iterator( Stepper stepper , System sys , State &s , time_type t , time_type dt , size_t num_of_steps )
            : n_step_iterator_impl< iterator_type , Stepper , System , State , detail::ode_state_iterator_tag , StepperTag >( stepper , sys , s , t , dt , num_of_steps )
        {}

        n_step_iterator( Stepper stepper , System sys , State &s )
            : n_step_iterator_impl< iterator_type , Stepper , System , State , detail::ode_state_iterator_tag , StepperTag >( stepper , sys , s )
        {}
    };

    /* make functions */

    template< class Stepper , class System , class State >
    n_step_iterator< Stepper , System, State > make_n_step_iterator_begin(
        Stepper stepper ,
        System system , 
        State &x ,
        typename traits::time_type< Stepper >::type t ,
        typename traits::time_type< Stepper >::type dt ,
        size_t num_of_steps )
    {
        return n_step_iterator< Stepper , System , State >( stepper , system , x , t , dt , num_of_steps );
    }

    template< class Stepper , class System , class State >
    n_step_iterator< Stepper , System , State > make_n_step_iterator_end(
        Stepper stepper ,
        System system , 
        State &x )
    {
        return n_step_iterator< Stepper , System , State >( stepper , system , x );
    }

    template< class Stepper , class System , class State >
    std::pair< n_step_iterator< Stepper , System , State > , n_step_iterator< Stepper , System , State > >
    make_n_step_range(
        Stepper stepper ,
        System system , 
        State &x ,
        typename traits::time_type< Stepper >::type t ,
        typename traits::time_type< Stepper >::type dt ,
        size_t num_of_steps )
    {
        return std::make_pair(
            n_step_iterator< Stepper , System , State >( stepper , system , x , t , dt , num_of_steps ) ,
            n_step_iterator< Stepper , System , State >( stepper , system , x )
            );
    }


    /**
     * \class n_step_iterator
     *
     * \brief ODE Iterator with constant step size. The value type of this iterator is the state type of the stepper.
     *
     * Implements an iterator representing the solution of an ODE starting from t
     * with n steps and a constant step size dt.
     * After each iteration the iterator dereferences to the state x at the next
     * time t+dt.
     * This iterator can be used with Steppers and
     * DenseOutputSteppers and it always makes use of the all the given steppers
     * capabilities. A for_each over such an iterator range behaves similar to
     * the integrate_n_steps routine.
     *
     * n_step_iterator is a model of single-pass iterator.
     *
     * The value type of this iterator is the state type of the stepper. Hence one can only access the state and not the current time.
     *
     * \tparam Stepper The stepper type which should be used during the iteration.
     * \tparam System The type of the system function (ODE) which should be solved.
     * \tparam State The state type of the ODE.
     */


    /**
     * \fn make_n_step_iterator_begin( Stepper stepper , System system , State &x , typename traits::time_type< Stepper >::type t , typename traits::time_type< Stepper >::type dt , size_t num_of_steps )
     *
     * \brief Factory function for n_step_iterator. Constructs a begin iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. const_step_iterator stores a reference of s and changes its value during the iteration.
     * \param t The initial time.
     * \param dt The initial time step.
     * \param num_of_steps The number of steps to be executed.
     * \returns The n-step iterator.
     */


    /**
     * \fn make_n_step_iterator_end( Stepper stepper , System system , State &x )
     * \brief Factory function for n_step_iterator. Constructs an end iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. const_step_iterator stores a reference of s and changes its value during the iteration.
     * \returns The const_step_iterator.
     */


    /**
     * \fn make_n_step_range( Stepper stepper , System system , State &x , typename traits::time_type< Stepper >::type t , typename traits::time_type< Stepper >::type dt , , size_t num_of_steps )
     *
     * \brief Factory function to construct a single pass range of n-step iterators. A range is here a pair
     * of n_step_iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. const_step_iterator store a reference of s and changes its value during the iteration.
     * \param t The initial time.
     * \param dt The initial time step.
     * \param num_of_steps The number of steps to be executed.
     * \returns The n-step range.
     */


} // namespace odeint
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_ODEINT_ITERATOR_CONST_N_STEP_ITERATOR_HPP_INCLUDED

/* n_step_iterator.hpp
fPXm2rqx7qdB5eCGCyo+6Dplr5K/LwoTHZdddjGgiIHhGjdQjiva6VE22aRBZQ2fDd0tvc77pnYe3jd2k79Y92jHa/ZciM1BAYcW+Ivsx/xAg+/Q4bc7NfgFBrDfXp7yV5+p8tbWHMKbSOQRUNL/h/7Nrd/5TNVaYoQhdVSc6jYdazyM5hDExYBgoSO7lL3ubjOmSfdaAZXOdStvf1hserCzN7187zjle43l96SXh/b7pM+VfTDXlzmb2T/Rp6x8H4kRq2bIPpM+wPwvG/J/75vys7eSJnVTjpIL9UtoUWWjRax2NKmB70jVKPsDiz3xAYERN1srog+L1Xax2kZ+MuAEq206FfihVA0HkK0ygS5D0S6m5X38V6uchHK1Fe/X1ojVVuWZawjEURGtvLq5SF5diqVle0flGbiAisUHrVWV3Q3DcMisEDfbHhZ9dlbDKnvl1edWStUAPT90CzIF3p3ZZzmH/zyytaPeVKPcDIClszOX2oQue8U5spgaQo0BOFmlVVZLj2w/U3kaKpkiuq2Ur6qyo+FjqobVAb2NBkqhjgPCx7mWEx0Ji5CwNuZG0D5lzL7QBH8350Twj6WzMtGYA52MwaVpk7orOxtzlLcGik2WKP6rUfohDNegBc1GV1uplSj6rCXXKj03v6lCRdCMHssp/OeWCzrrTR7F+3WyEyWsE5tvgQ6M0fo/woXrUX6ElXE2nJlVVpiWVJdS6wFl8q80XYb5vR1yV26wNeTBAVdtrlG+/hquinus+EJtR1czD4vL4tZVafYXh4vQEkF1FRKAd0jVpegEoh5oCpJuEBJFgZukEHlI5+IzQ6UQOPDVFcS3Oiui9CfL+nzzztT6lM+Pvz6RH7LWcD89NAayxngh8lOAo7UDCb178HNVupsaPVO6Gxq9f1SjmdtMSWINb54paQ0XuSigLaFnmYG4B2BIrSJMyPEjpDnhrEer+EH6wJt94c1fqPVmqG0OBITGKBASxNvID81Fy3LlsrcLJ7bhKkxSPgy0yPXm/7qDYWZd9scBtXutBH0KRyF4ruKcxxL1AKInc8dqRFcP3D9dbk8311VGtlf6AbtSC8vRU24cVb3fJg7bMSCOTtFDRLPyx98nWdD1JrXQP5UY6c3KRxAveQ/7PGqhE18kXO0id0QS/MhY21rEni8nAmZyVzkZX+MiZOWF0ZYVpzRMBW+qfMRSYEzwrmpmGArXLkSKiFgzQHAdgercqep8Sul8VfWphSVTD6VorWblTmwYF6kSuUglF83fcWYMzOUXXxVrki5sPVSn1oM7m3SLGIjLS63dNwzB2arM/181KfywtEipZ5/0KHEyTZ6kU1tvjz7+01H8t4wqKt4XV47AQSmujMPuohcmfBSCyLZZQOR0c3EyzK0/19zhA5qExxS3cvPuTlR+0BieVNQ+65BpOzqnG9beNka1a4VxD7H2HVx74Fu0T1w5DI3jL+EFk2qg7Ip3c8OseWWG1xqkLS0bvquWNrXsbjDxfOyQKTaN34Z/7LwCMGI5vB++yMJuy/cPmXyk6uKyu5V7dlGX0JFasj/44AGJrEPUufiYnZPvNc2DOv8R/lfDfxf8H+2vtzunHElHFGDLKYOQ/7sv4R/lw3kojl02q0uVepTOd1GMyp+vFOG3Q+qR7lqwUh3MOH9g/NZ8+cL49gI+p+aWpd756L0VO8yf33wYteWnPWvB2u7ER4j2G3SzzGRH62/TbRFnU6OymjR4PQxeZ4Dg0aNG1ABPyxVhuX5qyNWVmWvd7kOYa4MhV09mrlYGy23I1WvItfU4Hgyk+4OCI3hIBDFGDqEpXKXkbdiLFAGHaRUdMSxhGiYwL1bBQSwVGkD0vRBddYnhQSceSmJwCOMmD/8EzSDGPWJIgW9+dYLa/YZfa9EN0s6+G8iwNQllk0NwMThMRREcq0AKY4wYimN8yIlSdWGkEqRwCYaDCUwNXqJfojNJJuZFrFsMjVB0OUaHkcB4sQfhkpif1CMGicoI1iCcENEaoYcIJtIQNIximIiK8HKIrhFDSHvwzTSwYhhJEOWLZ1LD228YXilYRJB20O/OCSZ9Iexl0/Kaodz5zMnbznLtNeQaMOQi9fdFdwFOa5dCrTQ8+DU/WMXiwkcwLlxFcYu1fJhDDC2muB2cMR9+zQ9uZ3Ehigttp7idWj78EsP4pTWwfA/N5cWnUw0cHNX9CE0XiQaFSSYyTPzeYBn+hpClKxUipQEjjIy9Qpr8MDL5xHA5xfTQikL7k1J4gEGg8CCF51B4iMLzqNQCilFYzylspXlfQmFaGuH1FCZmQXg1hWmFhBdR2ETxiylso3ANhe0UXkbhEgqToFW4lMLrKFxA4YcoXEThRyjcylqIdvvZaAfRPLoYRFPq2hIjo/7hY05aYmQ2PYQm1vmN2kJbBOmK+FRqpIdG7WPlufR9jDFyCC09KsvP4j7GiNQ+poT7IaGe9h7Ps8V2u6EGxVDDi+h67oMc1FaEVqJn8CA6CJQmW+kQQC/jMMgYE+6jMDlxDqObcbi2xFAzfH7gLJVCEUpdTqnoftxdIwbR/ZoYIt+2YXR1qfyhBujcEPm+Ja+nYpC8ngbJXzl5RRWD6yiGFfVTzHr63UigKSbckMoTJI+hDGaI/IaGMQYoFBoAMUz+RYOY4uYfYoMeRG+jSsH61JAMj1reJDFMAqNicP9iExtKkcSGJYpw80s0SM3wpZx+MgUpnuWcILnZEDNIxI5MlKHlq9jU7HgydWReMhyZ+oUQp834uKGOxKg62JJDvjG0mX6R2fxiOR24aJBOCs0zVI3G/vgyVvUUQ9UjhqrTb79MZrp2AY6hrwr384l1BvymJPsNjShOHHH+szqa5Z+e/aJNKgDLrn7llg0WxIL4vq2HocU2hhYhssIXkKSmjXLl/IuFIS021gc+mpZ9Ao9rXyZB537lnaDFJCWMBSqvSgtxU/lntDVARuXTM7DbCrGMR323hsV9DHG0heBWRKuMh9PqsPBlhjqehjpEbshYyfyVQ/4ZUiHmaluNcApx3pTNCBcja7AqTFA2QBS/Iw2+lS8xwJ+aHb5dKiwh0PPgl1+XBiKHLzeM2tmm0aPWtg7r/p/TiBdgPje2h+L+DHH8ojRgN/BYh+y1eRDY82nA+Flp2XN5q6Hu2vTsRWnZbbzd0NvS9OzWtOwTeYehMV9uS8se3zI6+yTeZmjMyfTsPWnZ82TXgFsHvj8tN5zDiE/91ykkjgZwErWYoxDDH0wDZZeDiLTU6D27L73udWkFJsuE19To1RenFZBChARpyA/iN/wCBkIMIhKUBHSjTN9JQH1CWs22tJrz5SChS/ow/ZuQXvNysr5GqFZoNdbc+xyrOfyIsWaHHFxtBORLr3nnc6NrniIHHzEO0m3pBfi0AlPlcBcMuUev4dLzaU0lFFYqjCMqArRdy1O/RCkw0TuYBDENJXvRqDeU1whC5d+fpzNzDr+E6lOSsoQFJJo/6EFzASw/CssojZD/JJdnBqrCsn1lHmScBtGXufgE/2ThsfjXBGIZI+wg1kyx16BSFjtvZZ6/XHINi9TatiW49R7pRmbAMB1DFLECI7jBl7ArfHnaOBTKITybkmt1eOvocSCeMO/QZinosJpTszRdpu/koB/Zmr7OUfhMOXsSERHKSUudIk9iZCFucF7ZrC0BpxH4TXLQScD1/Z8BHA3lKk8TcGcSOEWuOYmn4e5Do3paJIdI1VDv6dQwnIdBVEMcDRZZzsotAIG6zqBS3LSThnfkfuXQ45ZvcfWx+274nw3vkQ0TxnyPRH3g91Limv7ciugnfXlkkVW74eSur1VV+XvATnSWh9wLMYyWxWsObvImjAHcwPySSctf/U8WEtpqnZgqoMEbwPQ/PWmhS0+WE/DpZlLHL069gOafS2WJBwRVsb1ZbJL3Oa6pqkctbCB8kiVc7YLRHtwGkyhfIsj69SYL+PJbw6LdWlXSc3pVLDPtzq7M0lZ5D74Ye+QmjNYb6spWuiWzdI4sbXTist6H0R6tdH620tszS98gCw2ZLf/d5iyl12eWzpX3bMls+Z5spZdllrbJ0rbMlnuzlZ6TWXqiLGzPbPlN2Uo7MktPkvfsyGz5e41ZSieEjNJ5smS1ZLR8bX2W0osvHkovbZeb4vDNnwfANYp3GC1d2PA2k3rk/9h/K14OtGJ9o7t2cJeFlZbjSfAZ1UUzG3ujvI+q2w9JHuVPMb26fKju9aLbktXVjR6L7+2ijbS3KQZfBGacerf8FnPhW1jK2uPcg5vaTPV/o75T/9dSAn7nigIa0xZfT+D99079HIyV5T4oKAojlIJe2JL721Gh1rFkN7/ThBuc2vXYo9oGz8EN3mfc4BsxPWcdDdOUisviq9jgWK58uJQdH5eMx8dUWR42fk8TrpkD0/idNIAsBVmDsYmR5guABH/lz4lsg7Q6bc716t75MWvOh9ZUDVpzWjH92bXUnAJ+PQFuN85Mobzt4iW6yynerRW5uIkV0XPTxD5ExY/hYP22n37PG0FNl/f101JsOsbmkCC9sgmReQbrWBJWk5q/7Q4Y6TWXUTTJclEO9UyBw62853NVkhGKtA9hy004Ct3BnqkmMlWHdPsU7OROXE1V0B73/7F2/fFRFdd+kw0m/JAECZBAgAABIobfEYISk0ICAbOwu/mFFC31YXvho4gYkVdNSwgbsmxmpQgRX3mUIjxjgZJn8jRWTNPPJ8K28jT68tHVF2ueTcuoqaCCRkXy5py5d3bu3Guin0//YnPvPd/vmZkzZ87MnBn8de0gecOHL+uLpmMCIaP4Bw6BPnTbB4a9JUHSQeQ9J12Y/GkfDoHkkGxciZzFGKgoCxVo7Tmmnw/1I6jfAa4fTeT6ef3VPew74qsH/VKhc/mDl0By6weGfskRfnIMqpy+SQ39xir6IekTSahfMv9c1q9e0i9uNPu05+wnTJu4MVybALZHwIeaoj2x2hrGviMHakG/qzuPgcYJIPkGNfQbF+H37YeGpAuEfimKfkj6xRjUbxwh+xX9aiX90pPYp4Vn7ds3PVm0b0YStO8RdE47sX3ngOQ8od94qX13YfvWXTD0m6Doh6RlXL/xhOxS9Dsi6Vcwln168mVz+56rLhjHNfNXF46FMNo9Fqqvh9v5QdDyzE5wofsuGPpNlNp3B7bv53839EtV9EPS50ejfhP557J+B8XfAfQjhDTInbtV7n2TyIEaUOcINCqtEpSTyeJtf7wQGwg5vzYEnwgNxWGnFVu3gM1UueaTCKlRNGiN1JCZu1nmnkJIN3BvhwajsYI7TRS18lxoOFQciJV5aYfP4NRFZc5m+e+Ruhs5us7pmN8n+8xiYy4ijQHLuL+tuhYdX7v3KxwzEnQn+eN1xsjYLotH6S59CXutD5SX5KJNJT4smoatnPE3o2jTIq0YSJqI4/AlPg5jCPjgHieXNpcuSh7AtIKdx1S66TrdHKR7qdugS5foDqZa6GI43fR+6RKtdDfqdA6kWyXoZsilm2yhO+B3cun+6LoqLXQ3kca9KXAWA4MPI7y+UK6PECZ5X195KgnAnSn06gts1rGg1FhX5Q8/ewGPAYkAu3heZC+U496/1n7KgHugT73D90At952x+UPFFmm9LK+f/fFPpNUymDwE4xzy8tgZepUFCrh5qK2rgWnX+cgCGWnZEQVJuPnn8cv3H4T1ohBOjs4b60UhVgV40Qr9spmpm1Mmlpbx4SX2kOD2klbI4c/F4la6WFYrY888AF/1oD6f07G1xYo+TlLXyWfoXB+vKpCmCMSQFjoBs4g5wyT7AkwhwXbQNYsXAC63HZXGy4DPM9hzbZiCPYhU9+B/RFBy3gvYL28VC4LnjQXB8ukkCGd86F+ehzkpfi+j47tX2TutZzevm/wGMA5p2pHf4Da0/xc7hkkkCKeT6aPAUNLgFbWPT7cCdni3WfNYgmeOBe7QrUo1tioCcQQ330RR33nAvqjdUFmfPZesb9aZiorv/sreafUK+mBS3eGQ1Om5S1FnvyIwhJSEtPLdMITkdhneYGjEG1TDf5Ao4IjPyYVcIWln2sBer2APA+wsxO5+T5pwCGy46Fxgv16lTzVssdMU7OGAfbUasGvek2YXAhsuDRfYD3Hs4fbYPdVm7ATAbkfsDIE9QsKmcyXsZI6dYI/drGDfANj7Ebv9Lwb2SAm7d56EPX6XkwvZYi/uPWrCTgTsHYhdLrBHSdjbMyXsP1bpEb8t9hpF79GAnYnYSQJ7jKz3zRL2PRx7tD12koKdBNg9PsA+866BnSzrvVDCHsyxk+yxO3xm7LGA3YDY6wX2OFnvLAn7FK4XMiFb7IMKdgr2HcSOEdjjZb1vkbA9HDvFHrs7+ikT9gSC/+NameEmGu9TOnKbIjCRdacUiW6nKrBXEUitPHsex2adwaMIBGKJq8mf3ywmq5OK4LS2tgFrgX1fzCehU/DwcZMYBNvoFzzymqytUSpsCilp1gecNvp/fM48OULoavYU0Vt+CQm6cVqBIpsmyx63k900iH6zF4XP5cNQw6KDjsUM5Vx+OBr/6szAv7qc+Fd3Kv5FY/CvngT21/zPA8VXOrwy7VSS36zXaRudda8euEyWnfWIQElzIO9Ku9dNKzj/sqprMY82YYDNpMIep+Oj5VrvLnOBphGms1H5HXzGPilSIEZbRGcyPL1okxE6AVuoyRz9MPlyTz+hT/3rIvTh8c77D0rrpXAE2H6L8PvuDrbTb9ZGFk5hyVdaNc2Pc2vFBKqgnY72ctOJjtK/0wG66Zm1PGjXtnymp0qJcKVFw/AJ88K76VObWFOEMb43Nkp9/1ueS4JwnQh98TQrcWxkYx4fPsseEvxfk+mvTpujK3y4jz3UslDFS3LUA/vIZQQvi+mmNxnrbSIfK5Ycht1lLYVL+p2RqKbI0PbKRkWKp3ex8q524uZwnFfb+/hRrJwv3bxyLjvNldNJf32H09F4HbOAtynf3db3tfF/JIp7NyXNTVogdcfjj/VjPg89NRtvPTZK5a9Ok7eBYst4ClonLdnoNCWZGYWRo5YUvgEEBeqkaYpAYEwAPyAtGVAXvbWcry4d7wGTw5N0GeZdTeHtqDXzDtErvpM+q356UPl0KKnOlLErVYH1isAwUjcnGiNgXgluVcCtCFwPWYjw0EMT3zL8/fCIv6+Lc0pwUY84DSFrFp+Wp2DHA3YeYje/aWAnSNhJMRL28Z85DSEb7B2Pm/vOCMDOROx1AvsGCbv3Vgn7Ga73CFtsftyUtGAS0uv+eH3cYi0NCUmRvTthWV//RKlUPm5dkoIWvOZINNufVYG9isAogmlPQt8nVYFEpWpHk5asaOE6Oqn2E5i49MgyVRU9jvI0ElwMnebnJ9B5wKFqEXHjiwdOgAOBywXoWvhmzKYfacz/suH/wJSP+wLZ8G1V2zAuibtl8OmtIHVYg+76Cp3M/kAZ/Rv2aNyJZN0ddNJTt6M7AF8ZU8t95YeF3B2MjVbdwd4S5g7GsGIEgqm478s74CHIhYoXXb7uiNwwSaJh7r5ngC6fTKqPyA0z9x5rl4cPSEt9itzlj6WYuvxYUn1MhvlwwwBdfpzo8n9QPtWz3ngGHBoBaeE5epj/FevHVC/DJCNhmijz5g0DGON4Ut0gK5u9YQBj
*/