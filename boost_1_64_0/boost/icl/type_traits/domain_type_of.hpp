/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_DOMAIN_TYPE_OF_HPP_JOFA_100902
#define BOOST_ICL_TYPE_TRAITS_DOMAIN_TYPE_OF_HPP_JOFA_100902

#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/icl/type_traits/no_type.hpp>

namespace boost{ namespace icl
{
    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(domain_type)
    }

    template <class Type>
    struct has_domain_type 
      : mpl::bool_<detail::has_domain_type<Type>::value>
    {};


    template <class Type, bool has_domain_type> 
    struct get_domain_type;

    template <class Type>
    struct get_domain_type<Type, false>
    {
        typedef no_type type;
    };

    template <class Type>
    struct get_domain_type<Type, true>
    {
        typedef typename Type::domain_type type;
    };

    template <class Type>
    struct domain_type_of
    {
        typedef typename 
            get_domain_type<Type, has_domain_type<Type>::value>::type type;
    };

}} // namespace boost icl

#endif



/* domain_type_of.hpp
I6JviOgiEX1NRJ8R0VkiukBEXxLReSL6lIi+IKLPiegEEX3I3qN7n4g+IKJviejvRHSaiM6wufgf2DuxPxHRj0T0HRF9T0SXiWg3Ef1MRK8S0VEieo+IjhDRO+y7Qy2l63goUQts3yWiw+z7RK8T0TX244w/iOg3IvqdiK4S0S4i2ktEbxDRAfZ9o/3sO0j7iOhNItpDRL8S0S9EdDgUPgOngTPAu8Ap4BzwKfAB8BXwNXAe+Bz4EjgLfAF8ApwETgBHgc+AY8DHwHHg6RCiQwaiC9iKRDRL2oL/MBG1Af8q9tti2w4YSkSXQIcAFwxEu7B9BdgJ/I2Isghlgf8J8ATBZ2wPAheB94APofcR0B4YC7xIRHFENMVA9DPwK/AL8BUwW/KFiGYS0RwiepaI/kLgh2ALnDEQbSKix7A/DvuLgX5ElEHKe3rdiGgQEfUlooFE1J2I+hNROhHNJaIBRLQetucNRCcAuxRTbAsBNxH9gO1Z4AhggmwbttuBF4G/A/uBl4CdwA5gH7DLoLwTFwGEENHLRNSYiF5hv3uIJKJGRHQbEd1KRA2JqAERLSWizkS0yAB/YHh/KNF9wBLsPwvkY98GRAN/MxAtAx4DHgeWS7EGngSeAqYB2URUCN2lsL1qIHoBaAq8BewBciFbiK0D21Js3wFuIKKHoF/M1gP7VMqfiFpi2wJoJeVPRCMlG+jtBvYArwN7gTeAN4F9wH7gLeAA8DZwEHiMiI4biA5h/zDwDnAEeBc4CrwHvA98AHwIfAQcAz4GjgMngE+Ak8ApwCDFGJhuIHLCpznY1gB9AxAGhAI2IppGRF4D0bgQ8IAbgMnAJGAiMAWYBkwHpgI1AAMQAoQBJsAN2IHxgAvwAYVAAeAAHgCKgGJgAuAFPIATGAvkAfnAGMAGWAAzMBrIAUQgF7ACtwNJQDegAVAH6P4P9u4/vqq6juP4/XH2kwEXGGz8GEwZijB0IAIaKCIKKtpUri3FnDJkKD8mTEVBnYpIiUlKiUqJiYmJhYVJibkUDZNsFhUl6lJMTLKpqKRovT73vj/3Xm/0ux71x+6j1z3fPXd3du+555577/fiotFUQqUUo6OpjLpQXxpHx1A/GkM9qYYOpmo6hE6hT9HpNJ6OpXLaj/an42gCTaT+VEED6HjqRV3pSDqKelMVjaBD6TSaTMPpMIrTCXQiHUAH0kCaRCfRyXQQDaLB9EkaSZ1oKBVSHhVQPlXSEOpAxVREHWkUHU7dqDudSsPoM/RpOoOm0Jl0Fg23Y2yY4xhdQ8vtumJhO+aF+Xl7nmD8FuM36TLG59NNjGtZnkvn0NN8PYCuDfF92ot93fYRbD2dh83HRoa4PdRgx258DsuLWH6Ny95DL9KrtJNeo1b6Db1EL9MOeoV+SxX8bB29Z4/3UCi0ii7Qe5QGvU+x5+YH/L2Iv+bfx+vza0KcguR7gc50hV4nLwqlX/c26rXvEL0+PETPMafRqXqNOzTr+cZf7/rzSyUNo8xjf9U+Xg+envFcNWgfr28viyTfZx8QTj8ffUfvuf21yHX0+VDyuWQRXUl30nUZzyGLE++3/bmEQowjeo+d9RwyIeN55GQ6POt55CS6Xu/F5/Kzc+hCmk3zyN+fZ76/zg+4XqHk6zB/vXRVOHmsZhFi4e9teV+b3Ef9WMc3Od7t+1hXQG3R5L57YyixL7NPcnkdA68NJfdNf09cFEru07+LJN/Dfirjfd0NofT7waV0RYgxX++yY0co+fx/mp57bw6nn7cmh9KPpVND9l7N32/v+73292km8Vj92JxZ077nzXgf8Nfnzq7Z9/wZ7xX2PYe2eN/zaLyX+Phc2vyPvef/+3Nrc6N/bX4=
*/