/*
 [auto_generated]
 boost/numeric/odeint/stepper/generation/generation_runge_kutta_dopri5.hpp

 [begin_description]
 Enable the factory functions for the controller and the dense output of the Runge-Kutta-Dormand-Prince5 method.
 [end_description]

 Copyright 2011 Karsten Ahnert
 Copyright 2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_RUNGE_KUTTA_DOPRI5_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_RUNGE_KUTTA_DOPRI5_HPP_INCLUDED

#include <boost/numeric/odeint/stepper/controlled_runge_kutta.hpp>
#include <boost/numeric/odeint/stepper/dense_output_runge_kutta.hpp>
#include <boost/numeric/odeint/stepper/runge_kutta_dopri5.hpp>
#include <boost/numeric/odeint/stepper/generation/make_controlled.hpp>
#include <boost/numeric/odeint/stepper/generation/make_dense_output.hpp>

namespace boost {
namespace numeric {
namespace odeint {


template< class State , class Value , class Deriv , class Time , class Algebra , class Operations , class Resize >
struct get_controller< runge_kutta_dopri5< State , Value , Deriv , Time , Algebra , Operations , Resize > >
{
    typedef runge_kutta_dopri5< State , Value , Deriv , Time , Algebra , Operations , Resize > stepper_type;
    typedef controlled_runge_kutta< stepper_type > type;
};


template< class State , class Value , class Deriv , class Time , class Algebra , class Operations , class Resize >
struct get_dense_output< runge_kutta_dopri5< State , Value , Deriv , Time , Algebra , Operations , Resize > >
{
    typedef runge_kutta_dopri5< State , Value , Deriv , Time , Algebra , Operations , Resize > stepper_type;
    typedef controlled_runge_kutta< stepper_type > controller_type;
    typedef dense_output_runge_kutta< controller_type > type;
};




} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_RUNGE_KUTTA_DOPRI5_HPP_INCLUDED

/* generation_runge_kutta_dopri5.hpp
/K/kPySOLTduvAwFXI67AncV7mm4Z+Oeh3sR7iW4a3Evxb0c912478a9CnfUcFvc5qWkXFar1XDZUn72rOwcR6/cvGy73Z7yS4X29HN2C+2djserD12u5/6+V9OtYv9TaaZ8XZWy9VVB8xhUSnwfFed8Rsfhn7IKbPjz1H5cffMaSqGuxQL/g70FI8ioTVPlZnubtsYBfQ8Z044WhadOpqwOQ7nMW2idCvTyPjbsNqe/+c1Av34R/CiDFd7yi6lczsJEb22Jueetj7ByIgw8UOMKHMTGuuwQgNhbG/HGi5BcH9S/Kr1jwhuJZ6ifMxOrd9NVLy2mLnAKGuaWqdoKv64iGdylPA1ugcgCtGlswVHBy746htDc2hJvLBUL3wkXgbddrVJl1+pof1LUeHuPGl+sT+rNGtNfbN1LpKrhaw+Bv8bOcAmthjhm9X8kq984Kr3l79vp6rdPSOLaLHYdbHcaGGhKY2BwUP+K9I7Rm+XmqnS0H8W6x4Q+VpSGfprcYeukEEL/jEyL1p2r1ZUjLlet+k15xvnh3Mu4B/mILWnTEZeJCLZehygAF5rG4/1CF0WODwsNoxzetpNaFi4w407VtoOLSFsb/j22PQlG8FDDgPfCuPMjrAEjxO2+mEjgBxjeKCFe3Vd9PQMH4wDCXI5EQWps5TmKP7faAEeNHy/jhI6iVghbcE/QfyCAKyLVOZHUbPNQXrrNVVZxAzfnsemblLTF3BuXiJY/55HuP/OS529cphhIBuaTm4j55CZSgT4518bRAahpJVnw4jvOHyzl2583JxT5B5lF0wF5Xuyr+I9jV88s2Mnbkpt+TIqudHBWoso5uWaEWmtCo06j60KpxP+QI3ViQ4t+QS8kmKHG6plpOnfYYS5VUn3NTFmckTKgx0eYW8jHQsgkKsy0uruXudI9H56cM91GyC6HEYLsV6SyrzSz352Tzl70qfAQ5iprVo5AvLG71tGD1z9y0wj38zhqoYYbM8y0Hb5cqzbr+GAOeYDzHcZ6aVlouLohhexKugbLOv0h26wTMPadHCk0wYD8qTR2E8NT+Qb0L+SILAWK7k+jyMzua2Z2ixZzV35/AUYvZnuAqQ7d4QroM/AqpCHXIpImze76ccCBfKIyxxRcjNHuOSzso6mXtNcODug/EmFuhJ0nun5hQL/AjL5msPrV06HJN6A5FNDfEE47jvBbdA4f7/krLvI/2lRVI6FyUB4OCJ3i/p6k/Cwbzj0HsF4on1z3NmvNLeIDObMB2Fn7U5q8XrYL8krTVpqe7dkG5Tla6+hhOSPNNVUybk1xJn9QQW07eATS0oKyDg7KhnrqPJ9p5Kd/Notzg/4pPg7w6O93jaMAfkEkO+bqYwVqHdwhOR7f93fd/SgCmshvlLRStS3lr1UIL4qccrvWfZnpO0JYHaAcbMWsuHm7gkvD5kTrkW9pL0Tesh35pgY4TiG81qIfRslQJM/Hw7DljiCHAI92hXe/tDfl+mLKqSPlSKU2Yhy2p2JcZcSohYmgmkUrdoTvTYeP6hb+mAzflA7PZZXFlAL/h9L+ZIgAaQUhnat/Nx3wquV0kBBjYTrGFsGtMEv4T0n7f1GmLLa11lpAMktWlxhxRppxQmsQfl0Jd6iLoKD+uWEiKNEnOFe3pKLNE/uNW92R7W6husKbFwldG26WU+XoWo9f/6CI7mCrC9ZmRO0kkx/rVXu5Oc7+RrJW262iX83VYzZ+ITyCf35iD+k5UxvTavQijkuV/5DO9g+4muaQ2MsuzOwffiKY5swLuDF1SSBI3OlRK0fJsiQPxMNYWaruyJiJGuTI85AiMJTiMP1AyIoLiZA5LdtKS7PcG7WIh1Ex/0bFwPo=
*/