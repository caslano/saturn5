/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/open_mode.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c open_mode keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_OPEN_MODE_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_OPEN_MODE_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass log file opening parameters to the rotating file stream methods
BOOST_PARAMETER_KEYWORD(tag, open_mode)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_OPEN_MODE_HPP_INCLUDED_

/* open_mode.hpp
ttj2H/bOPD7OIYzj7yZppWmQXkmaRqVRbWlKWtGkFKFx1dGooAg5NmkbzbGSDa0ztCiKoCiKuq+i7qKI81MUdRdFHH8URVD3+d3Js5N3d+fd7lbcOzz95Z33met5Zmbf932emYmFWIiFWIiF/274i+z/VVXK/P/H7f8z9Pn/am8GFdyQC6qErs7nm1WVtl0U1UyrbvIGHP8vdgt15mpdldO+XeSh7Rb7KbtFVZXdhlur7u9O7eOCz/vXNs0piucwS+2CDmVj49hIzvyvFVv9A0OUnUnRm2nr38/UZwdqqjLsE07aAao9QWf0JMh5uiQYAu4MXktdVzrIqKqhbGpNfUWtFeaMwg6VdqTZ3mOTW12KSju9oqZenz/wqbq/rcu4F7Sk7av3SmOL25qpsxzO8YTfsOem6OdHdW+wba/5us7z0WRfz9LqTq2kyhn7S7GRmXSdBg5SvJ+xxvYCfZZi4lSxTZLmiHSVv95Puj9X36vyt3Cp+75MbH1tGWX5fTaGiz3yO5QzsvNviL+pZM6Azv6wVxQ2wsSpke0hj26IU7qRM0llvzgtc8Wr5KL8AbT8+qj6H+HQ39JlQ71+kMpD7IktU839TZsTI7Qnko9pXGp74hnqfqK2J/aO2RMd7YkLlT3x5Bse2K35rvwffy587rbXf3thx5jdUOyGDnbV/6c9sVX/JjJOxG6xKTRHBtIAWQeeDiaCA8GNwW3ATcFMcHNwMLgFmANCyk6WK3yjwSHgDmA2uBO4JbgfOBw8EtwKrBR+vY+C1OtgV+g+CgXwDQHHgSPA8eDW4C7gNmAhOAHcFdwLLAL3AfcAy8G9wePBfcHTwP3AVnB/seMVg7eAB4I/gCVgP7GvpYNTwAzwULAALAN3Bt1S/wI9pzFeRK4JSj4EWYfvw+3AjcA8sC+4PTglZgeK2YFidqCYHShmB+oWO5BnEuunobZJ/x8b0F/0/u/urvf/+uzO/ejWxDk9n/13n9djz+X/T3++obHnvD/8nBd7xlPPeBv0fBfts13suW7Dnuv+jmc6w/Nctz3LRfoc5/AMF/XzWyzEQizEQizEQixEFv6i9/8Kr7d71v97si19ziN7ZaswSNqSAZ3vW4tcodf/N9VMq+fgzoqqqtG+OjQqu+Gx6ry4phon2z/ptY3xTbVmXCU1rg0XXm1vfK5/5PZG6uE7syvgfGDKI06VF2BXZc2JCsMlo2HQWuyV5c5tLaucVbb/3kVWRG0mn6BzyuprjGc2G3nVEZpGG72dN035A1TO8lYbzt825ovFWerQ38bbX3jtcl/xB+WubN/S5r4B9nDVNn3GNm0gTrVBxfXXfKquATpL6BGqswvpn63hdTZpt4mR6Yx8utbWqn7KEHM6AzEKnbVGobPWKHTWGqSz5/+gzmgzcbS5G3XW1jNUZxcVEB9eZ96Z3sh0Rj7ax4XKydxSX1FX7XAmYBR6a4tCb21R6K0tSG8vbKDe/HtR+CozQLf7j+vO7w+2RPamgEf7oFyM7jpCdFfFj5W3uvMXITK9dYTKq8HtMNY6guT16gbKK3BuorygvprTy1Ih0+r6HfwqH/1WBrVXHdmsTq+Oan4hn+D5xfE3QXiJ0/KpaPJ6GprMvlvwG/u1sa8Kr5bn0VH49DjPG6otQb5Pus7S/+x9MvCM6fSk0L62gL5WaJK9dDRfW88NL3PSR97PCoPk8loU/ezcKPpZSW+9FlqFNOhz37OHU1v1o0dkbS6vjOLZI8p+Vh4ko9e7RUb1zn0nSHatyaGyu8znlBJWdgzRCGXXUhn5M0BLlLJrCZLdG39Qdvr3OkLZFW0c6PO4KbTct7+Xs+zcDc31XitC2S0Kat+qDWyf/TcobxM=
*/