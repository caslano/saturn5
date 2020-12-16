// -- control_structures.hpp -- Boost Lambda Library --------------------------
// Copyright (C) 1999, 2000 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org

#ifndef BOOST_LAMBDA_CONTROL_STRUCTURES_HPP
#define BOOST_LAMBDA_CONTROL_STRUCTURES_HPP


#include "boost/lambda/core.hpp"

// Arithmetic type promotion needed for if_then_else_return
#include "boost/lambda/detail/operator_actions.hpp"
#include "boost/lambda/detail/operator_return_type_traits.hpp"

#include "boost/lambda/if.hpp"
#include "boost/lambda/loops.hpp"

#endif

/* control_structures.hpp
8oxHraXdPmiMs/0GS6XUndP5oRFnLnIkG4mUxV7hvbXZHmHdSON5kKcvnim8f2PE0KZkn/D1dejNjvEujz77GcJHvby+tbWRgy67PCpUn+ordTjP7Ij23INlcUmcQyhLMyMb48g0cP0TjJW34++tRiT6zt+MXixbUk/aJmDUHIQwUxGmFvW4AX8/ZGTgDGGvEe3YpuYJsyW/jupbcps890X+X6hyDpUy1Dr1Ngr6fpFN//u9/PU2Cs+I3BLDGtgosD9fJTx1CtHYJIjcF0s9jHfpbBJ26vlTNglb9P7KJmG7v/j036/3VzYJz+n9lU3CNu24MUKNv3Uy/rbl+HshZhTjVT+4Xcq9HiNshPFrfE8yzRrjbrPCiHfUqX5wQNK+DWFCMYe53pztaGEksq10lbRfN1rC73zQ/SDPHOAJqfMBaDkOoxfbxg6pp5ZhG9BPv0C/e80x2VyMnvs3jPZtQpLNeeiDj4d2Mjz2Cm9JeDNsjmO+K4Zjg6esc10zDJ0Ng4wpEgbjicaGYa8tDWsOMOWUzgFOow2DnMO9uKXHN2PdL6+/sfSxa+b1nbHsf8eGYVf3H7cNQ0baqbVhqEs7ORuGDWn/vzYMB0zONTmnzgNa/O0x9TYMWcC2tGVIoS1DJx9bhum0YSih7cJv+fs5YbRZ6E+bhZG0WZgFHAe8lbYKLwEnAh20TehPm4RK2iQsAhYAHwMWAvcDi2ibMBOY4uTv4tBG4afAOcDbgOXAjcB5wKeAFcBDwPlAB20UEmijMJQ2ChNom7CKtgm/ArqBfwYuAL4HXEjbhYuBbdEvFwEzaKswA7gEeBNtFR6grcKvaavwF2Ad/v8AuBT4PfBKoEmbhW60WRhNW4VC2ijcRhuFXwB/StuF1VY6wOuAIbRN6Aa84QfYDjT1HD1yYZjRGTQENB3kXhg8Vw+6oAu6oAu6oAu6oAu6oAu6H5c7zef/FXOKa+fU/3tq9P8jkgx1LjaF59LVPJeuAv0dGxP5neRc7Jz8URMmTx5fOD6vsBTMucs8egD7OsrZ5Rw8qn3GqRJnLvb+Tdnfg1yYTpI6o+I7zbmY/nzYHtYpZ401ZW7bb4SvEv9M8R/aU85D1e+Px1ihxT/Fpg9gydFQ/M0T/6ninyvxa1T81sD54t9F6QhEQnbrwXMLzblluB8dAUtWcZRVw33L4+Es/uLIn/18fgjP59swcblHKg37mQ3rqKq4osK3fjRnk4xLubaSOpi1oLJEXwcMq87oWwZwRt9Y2a384pif/Yx2jou6KGovDzJJxz+dteUsLK6ZHVBZJT7L+nFa42VlWNXeTMPKxdCdxSPsqZWLxRvlovayLR7iyIO9TbhCvNtcmPU3ZJXSQFZlNTVVNQHJqT6ueVJlsPOWF2qIK+aYUgQ6hLAZDXibVVNW1mA8UWfr/ST8BXq9FyV71e/V7/WPEb/uaEchfGcaI+TdEPCZbjsbL1fjyBDxn6wdR9oAJ4t/PMc6pofTlGi849iAcYHUBP0hXxnmUIYHQxvWbyzqd3MDGc4uc6M/XFxZWFFVXCr8x6Q3Xs+bm1jPSI88evfXrWTuOtbzatAHKM+2BjyWV9aW1bh1345Ezx2nEucaowv+LQJdrr4hnvSGet976tNP+Q1R596fsu1kYjc/H6Tp60hD+21R7ahPF8u/Pb6uDr/flwQJk+73+3JM8pjk+31R95B9L/4TjC7I40yQpy21Sqr/1tx6km2JYwrGj8C/M+gY4laxPq8FfY4067r41mdl2cXUlUqUb8ccdf77mYRN0LQ7psM+u0bilah4fxS/NG09MR7bjq2e2HauF/9LoOFkKvndHWWR9MUAdONCon8taRgYLPvI81PqOUM=
*/