/*
 boost/numeric/odeint/stepper/detail/pid_step_adjuster_coefficients.hpp

 [begin_description]
 Coefficients for the PID stepsize controller.
 [end_description]

 Copyright 2017 Valentin Noah Hartmann

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_PID_STEP_ADJUSTER_COEFFICIENTS_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_PID_STEP_ADJUSTER_COEFFICIENTS_HPP_INCLUDED

#include <boost/array.hpp>

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {

enum adjuster_type{
    BASIC,
    H0211,
    H211b,
    H211PI,
    H0312,
    H312b,
    H312PID,
    H0321,
    H321
};

template<int Type>
class pid_step_adjuster_coefficients;

template<>
class pid_step_adjuster_coefficients<BASIC> : public boost::array<double, 5>
{
public:
    pid_step_adjuster_coefficients()
    : boost::array<double, 5>()
    {
        (*this)[0] = 1.0;
        (*this)[1] = 0.0;
        (*this)[2] = 0.0;
        (*this)[3] = 0.0;
        (*this)[4] = 0.0;
    }
};

template<>
class pid_step_adjuster_coefficients<H0211> : public boost::array<double, 5>
{
public:
    pid_step_adjuster_coefficients()
    : boost::array<double, 5>()
    {
        (*this)[0] = 1.0 / 2.0;
        (*this)[1] = 1.0 / 2.0;
        (*this)[2] = 0.0;
        (*this)[3] = 1.0 / 2.0;
        (*this)[4] = 0.0;
    }
};

template<>
class pid_step_adjuster_coefficients<H211b> : public boost::array<double, 5>
{
public:
    pid_step_adjuster_coefficients()
    : boost::array<double, 5>()
    {
        (*this)[0] = 1.0 / 5.0;
        (*this)[1] = 2.0 / 5.0;
        (*this)[2] = 0.0;
        (*this)[3] = 1.0 / 5.0;
        (*this)[4] = 0.0;
    }
};

template<>
class pid_step_adjuster_coefficients<H211PI> : public boost::array<double, 5>
{
public:
    pid_step_adjuster_coefficients()
    : boost::array<double, 5>()
    {
        (*this)[0] = 1.0 / 6.0;
        (*this)[1] = 2.0 / 6.0;
        (*this)[2] = 0.0;
        (*this)[3] = 0.0;
        (*this)[4] = 0.0;
    }
};

template<>
class pid_step_adjuster_coefficients<H0312> : public boost::array<double, 5>
{
public:
    pid_step_adjuster_coefficients()
    : boost::array<double, 5>()
    {
        (*this)[0] = 1.0 / 4.0;
        (*this)[1] = 2.0 / 2.0;
        (*this)[2] = 1.0 / 4.0;
        (*this)[3] = 3.0 / 4.0;
        (*this)[4] = 1.0 / 4.0;
    }
};

template<>
class pid_step_adjuster_coefficients<H312b> : public boost::array<double, 5>
{
public:
    pid_step_adjuster_coefficients()
    : boost::array<double, 5>()
    {
        (*this)[0] = 1.0 / 6.0;
        (*this)[1] = 2.0 / 6.0;
        (*this)[2] = 1.0 / 6.0;
        (*this)[3] = 3.0 / 6.0;
        (*this)[4] = 1.0 / 6.0;
    }
};

template<>
class pid_step_adjuster_coefficients<H312PID> : public boost::array<double, 5>
{
public:
    pid_step_adjuster_coefficients()
    : boost::array<double, 5>()
    {
        (*this)[0] = 1.0 / 18.0;
        (*this)[1] = 2.0 / 9.0;
        (*this)[2] = 1.0 / 18.0;
        (*this)[3] = 0.0;
        (*this)[4] = 0.0;
    }
};

template<>
class pid_step_adjuster_coefficients<H0321> : public boost::array<double, 5>
{
public:
    pid_step_adjuster_coefficients()
    : boost::array<double, 5>()
    {
        (*this)[0] =  5.0 / 4.0;
        (*this)[1] =  1.0 / 2.0;
        (*this)[2] = -3.0 / 4.0;
        (*this)[3] = -1.0 / 4.0;
        (*this)[4] = -3.0 / 4.0;
    }
};

template<>
class pid_step_adjuster_coefficients<H321> : public boost::array<double, 5>
{
public:
    pid_step_adjuster_coefficients()
    : boost::array<double, 5>()
    {
        (*this)[0] =  1.0 / 3.0;
        (*this)[1] =  1.0 / 18.0;
        (*this)[2] = -5.0 / 18.0;
        (*this)[3] = -5.0 / 16.0;
        (*this)[4] = -1.0 / 6.0;
    }
};

} // detail
} // odeint
} // numeric
} // boost

#endif
/* pid_step_adjuster_coefficients.hpp
TegbcZju8XJccapYrWcfbBY3YGKz1bVVfj90BTMvrFDtNtGOii0PJ4YYs6uEhp2lwmjnd59HNvUBWNsv8OEdy2VnHe7gRGhjI28p2fEgRWN/ZHba/RTct1pHTL28oqb+1PvZOWZskncvrW3gCCUJi+ip7tqE5Lqib5Lr+P2y+nb4SWlx8r2g1Xw+OhJTKwjpem2I5y62SPMI31omYMpNE9gxbcqWX/8j5Q80yhLKs/5H4ve3j2/7vQfPRmoAv/1K9gIK4uoKrqqCfbLLUICWnxHpnRBpY5PwCPXJUeMq/P4z/Pihdj+fE2+L11jiXlgaJzm1++3imMFpzyt7Ki3NZ7Q71j/74CvJrzPGreqcXeGA6oNo1vXVzwv3WeGupnuW6ZcLt0y4Trqn4S9L6GDH+zFhXP/wtv4eXXSY+B5dPF6J2/BB7WfjhtC7lxMa6K0wuFblpbh+CLVhKpPrPmEqmqCsiEthwi3u/Udk2y7Zto3nKWSLsapQPrlTtoyssrhrTfA3JDcUqXhvl+NrC+W5u0WYbBF+I/2FcvGribsS/cmvzU1RtvStxVZOUax3lF95VuRgmOyVDAu9RpwFBKU/IzQVoUAOV8o0hJhKr7GnASOmVL2YjF3OqtygLTY7z8/l2Mn/kkC1qmnCaFoaOT/+sZ00HeKTniPBuZHYYbaqJyuC6whlH3Nut1d5MG4kSLoisNkWlljT+IYk7IcgNzy4ZfaTwAbZwJnBLbNLAyGxM7mFFQlXHOzwwCCXb7sjtrFcG5JB9iSQJPa90PA5j/udyFcuf0abUSSt3CnmShuJt3IHs7vZvSFuUBhHxNO5E8StLex5RXP4GO/A55dXKqJr4oYRjym6j+QVD7Jv4qj3JRuH3g47RrAme3CMrCwVWoExIfdY3kfi0s1UIM4DeBXKV0IOtNO5uDkgtm4MFVP0gU+dxTflYinsEuU+hqwLo8nDl+v2h/FKIlG9xnCBdWWiv/wAau0hsT/Y3Ts1MoD8g4Y89ojA3BCfmXyi6ENlWY2W4XDUGba6DqcO0jkH5qh7b6ZA37i5zZ6g9iH2wL7gJsQpKg3cCe4LHhBbH96yuH66lk9UOUBjUbkBVaBt1lmSyoS+yRWcsHo3iK91FeIweJk2tn5QyNsbWS6gcZHxVmx+xleeh8/OFxzC2WdtD9MzLbKfumJRYMvG7Jrk3qiKA/GjcV8cRhZfXRRxwyQDAgfh61llGszJanHcVoOu6VLuMJq8dn3jKOAmHmjZZGxsTEQItkkNqJM4nFr3TtF7I/t6etIZaY73lJlXAzfQWjzTzPGKWcfz0wZ++hCbhsEt0YnfYt/HeZk380usm3VZFNxAibOfbxAaEtgPbXwXSy452ZPUnDLto5FmnsfO4I6HEdwnYsyB/qQfakfb28z81lBv2JINsq13NuXKB0CGa6a6zG89vTwFRuiAQXfrtwiyuH0JqRR+ckD4i1ecFN+q8EIhIbeADXDo8lD/Oa32OuWlGSCauJff1a6lCmFnUdQa1xlIsJlN5wCNzT7NbI58sJ8hDFweacvldz8EuAxTlj5IOfI8UqUOJ5RQrzh1jEUiT5mICOyGumuOWx0h7XdDy4SeeDJ/gMBqQtwbaDs483Pl8eT5CFRFLArtwYnnSA8Ckt+XF2f7Rc7RGC7HKEtF+uxJOVZPhdgVvU/sii77gf4KsStauFgzbRngmEvQ9mkG/l138l8mBNDYD/4d557/oIf9deKu0urAKrl2r82qPJ+iZ2eMuUaPkP1GDsh/6OnqYrCkuWsSkl8vOqTUnWZiUd1P3H8tb72/Ec+jB9w4TuXoagiuOMRomxts+SPZSQZPaLg647vClcEVj6FIl4J3uPs=
*/