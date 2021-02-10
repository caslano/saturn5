///////////////////////////////////////////////////////////////////////////////
//  Copyright Vicente J. Botet Escriba 2009-2011
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_RESTRICTED_CONVERSION_HPP
#define BOOST_MP_RESTRICTED_CONVERSION_HPP

#include <boost/multiprecision/traits/explicit_conversion.hpp>
#include <boost/mpl/if.hpp>
#include <boost/multiprecision/detail/number_base.hpp>

namespace boost { namespace multiprecision { namespace detail {

template <class From, class To>
struct is_lossy_conversion
{
   typedef typename mpl::if_c<
       ((number_category<From>::value == number_kind_floating_point) && (number_category<To>::value == number_kind_integer))
           /* || ((number_category<From>::value == number_kind_floating_point) && (number_category<To>::value == number_kind_rational))*/
           || ((number_category<From>::value == number_kind_rational) && (number_category<To>::value == number_kind_integer)) || ((number_category<From>::value == number_kind_fixed_point) && (number_category<To>::value == number_kind_integer)) || (number_category<From>::value == number_kind_unknown) || (number_category<To>::value == number_kind_unknown),
       mpl::true_,
       mpl::false_>::type type;
   static const bool      value = type::value;
};

template <typename From, typename To>
struct is_restricted_conversion
{
   typedef typename mpl::if_c<
       ((is_explicitly_convertible<From, To>::value && !is_convertible<From, To>::value) || is_lossy_conversion<From, To>::value),
       mpl::true_,
       mpl::false_>::type type;
   static const bool      value = type::value;
};

}}} // namespace boost::multiprecision::detail

#endif // BOOST_MP_RESTRICTED_CONVERSION_HPP

/* is_restricted_conversion.hpp
HFSefpydj4IzUN3JqQAeceJEsaZ0FO/Put1i5qXUes5K243vlnvClYpQFS15/037s/0GE5pK0hr1KeXyFBQrh0zPNNUr4YmUU9qQHgZXKNT8BA86snkqWEoe+/7C/Uh5osCMfY+K9LSKall4wfkTDRSl96d8fl5Eu0QYqxfU9dZ22gcH24e76sks3aTpJUkhj+slxC53OyGrcqDLltgYkboKc63mZMbQ8nCkX5oJJ5Lxlx8z1cWNTgLc60ZHvUpytSQd7Kl4l0vDm5uC18DUwJDQU3ZtWc0dmVS8wOc4DpmUJ5w9QaItyVD2g2ACAhZ7I7VuEclN9VRbSFSRqaUsmF3oEFi8GvCOuPDHoeNRvOjO0f6regoTWjm+B/0Tnj6mC90NCgP77hzsbqafwcLNpLmy1QvolbOk7G0dbHdQHgbecOjSPfC0tYgh9h4uxfD8T4gHUyNKHkchQNrSLc22Wsfxag5G4TPyX77LlroFGD4zKmV9h0Sh/njgDXATlfzKMc+YYKrSbCVOs0ycjnwHtNvSD5vj58ZGrXTUI7r4RyPH4AX8CKdC0reTR3YvBugdQVJvQAddnBGy87XIFOxm5Vv2pfCokN+ZQmGBzozwNGVBmnEFOvZ15kTus6fpfhriZu0fxkvxKMHTR1uf
*/