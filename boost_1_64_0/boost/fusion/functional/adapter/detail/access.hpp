/*=============================================================================
    Copyright (c) 2006-2007 Tobias Schwinger
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#if !defined(BOOST_FUSION_FUNCTIONAL_ADAPTER_DETAIL_ACCESS_HPP_INCLUDED)
#define BOOST_FUSION_FUNCTIONAL_ADAPTER_DETAIL_ACCESS_HPP_INCLUDED

namespace boost { namespace fusion { namespace detail
{
    // const reference deduction for function templates that accept T const &
    template <typename T> struct cref               { typedef T const& type; };
    template <typename T> struct cref<T&>           { typedef T const& type; };
    template <typename T> struct cref<T const>      { typedef T const& type; };

    // mutable reference deduction for function templates that accept T &
    template <typename T> struct mref               { typedef T      & type; };
    template <typename T> struct mref<T&>           { typedef T      & type; };

    // generic reference deduction for function templates that are overloaded
    // to accept both T const & and T &
    template <typename T> struct gref               { typedef T const& type; };
    template <typename T> struct gref<T&>           { typedef T      & type; };
    template <typename T> struct gref<T const>      { typedef T const& type; };

    // appropriately qualified target function in const context
    template <typename T> struct qf_c          { typedef T const  type; };
    template <typename T> struct qf_c<T const> { typedef T const  type; };
    template <typename T> struct qf_c<T &>     { typedef T        type; };

    // appropriately qualified target function in non-const context
    template <typename T> struct qf            { typedef T        type; };
    template <typename T> struct qf<T const>   { typedef T const  type; };
    template <typename T> struct qf<T &>       { typedef T        type; };
}}}

#endif


/* access.hpp
LpB90vA2lRDwrHyeuDJlZdT1Ka7S/bK37pQQyQaj4xXyOl/AYbzfng9YQZClbeKjCPgHhVhTSZ9WFf+fWFz0+bNP+br7X8xvAr2vWl0FF6qBa2j43eNGjRsOCUniR3H/buzFDG11Y0RNMKhHJFyzJ73rMXdKeeaqw9a3deqn51C3GfP71KnPG0CDFQOHn0DVPugKOwEWIgzGBzqTQhOTc1zBIlKejRlluDvkccGlD2OG1vd9yzHe16+6lDEq+xwihyBLI2LH7lof2d582sh6+TwulOu7h6CmgdNX+DQu9ANlUqdSh8th07MjP3xXhEJRHL3YkTu0xZMfRFA5oAaHh+ReA6lp6pN6dkW6tWU9pFV8UTIhuQMDgsHZiw9vG9FfJ6Qha/Rq0wIvtwX+Yhu1Pc9VMzsnmLaw4d7wSdC7LQJhszcBCd5nzINfuKjoxlFigrTHKelPT14Qkw8Hrouehc92ej3fNWqzr1/rb156NAcYngfZlrMEeJXwvFhGTmwwyYvpM7Rl9oDT4DxcPzrEf/7ep7imu0VT4YY+MpVQxHT498yaVmYb4Khk8Q==
*/