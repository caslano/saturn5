///////////////////////////////////////////////////////////////////////////////
//  Copyright 2015 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_IS_BACKEND_HPP
#define BOOST_MP_IS_BACKEND_HPP

#include <boost/mpl/has_xxx.hpp>
#include <boost/type_traits/conditional.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/multiprecision/detail/number_base.hpp>

namespace boost { namespace multiprecision { namespace detail {

BOOST_MPL_HAS_XXX_TRAIT_DEF(signed_types)
BOOST_MPL_HAS_XXX_TRAIT_DEF(unsigned_types)
BOOST_MPL_HAS_XXX_TRAIT_DEF(float_types)

template <class T>
struct is_backend
{
   static const bool value = has_signed_types<T>::value && has_unsigned_types<T>::value && has_float_types<T>::value;
};

template <class Backend>
struct other_backend
{
   typedef typename boost::conditional<
       boost::is_same<number<Backend>, number<Backend, et_on> >::value,
       number<Backend, et_off>, number<Backend, et_on> >::type type;
};

template <class B, class V>
struct number_from_backend
{
   typedef typename boost::conditional<
       boost::is_convertible<V, number<B> >::value,
       number<B>,
       typename other_backend<B>::type>::type type;
};

template <bool b, class T, class U>
struct is_first_backend_imp
{
   static const bool value = false;
};
template <class T, class U>
struct is_first_backend_imp<true, T, U>
{
   static const bool value = is_convertible<U, number<T, et_on> >::value || is_convertible<U, number<T, et_off> >::value;
};

template <class T, class U>
struct is_first_backend : is_first_backend_imp<is_backend<T>::value, T, U>
{};

template <bool b, class T, class U>
struct is_second_backend_imp
{
   static const bool value = false;
};
template <class T, class U>
struct is_second_backend_imp<true, T, U>
{
   static const bool value = (is_convertible<T, number<U, et_on> >::value || is_convertible<T, number<U, et_off> >::value) && !is_first_backend<T, U>::value;
};

template <class T, class U>
struct is_second_backend : is_second_backend_imp<is_backend<U>::value, T, U>
{};

}
}
} // namespace boost::multiprecision::detail

#endif // BOOST_MP_IS_BACKEND_HPP

/* is_backend.hpp
qwvNVnq9VUgU8cRYOw9Trn/PLrbyOuCk6lNE+7y3tPKQQ3uV3t7OgVK1qqoh6btrq8nFyysmpD9pLpdzaJxE55y3NXH8FMt5KKWjyemDH+r+bQc3DJAvzo43uW2+2LO9jcc572py8GYOVl6O3YNxsLzhRNJ+3U+fa3LU+IA46T0bHDw/y84i7dnR4NB3mtLf5FSFBr2k8Sbv1cprnGm/0s6j+NP50Hu389BZbF6qnUfn2mhv+n1aeWqvBPHKne088wzc0H1bear7RLw3tvPUWIrK5OT92nlydxAwdZ3X27k4CCVetd+3lacGq8Q7tKuddwZ8c/Klg77lD/4rD/rzc8vw10Ga3v6A/8bHGAzauPKBDS5WXIrjz1vwfkv52nhQO88sX2N3tfPM8nW+ldcsXzMPbueZ5euv7TwqX2R3dzvPLF+TD2nnmeXrm6289vL1uj3tXLN8PfGh7TyzfH2zldcsX6+4u423efk69LBWPi9fan4euewu0RXkD+6E2Is4ztWAHJY8bazytIcjJvk4qKcxxEUebl5XSLxjjwAe9qMpqpk3ExZu3SAT79pmPIyOxpt5ZDuv7toT75ub8fAOPI2X7mvnqfFJrvZBsv5iKpI0S60kc++0v6jPOf+J8o/6BjigpTzeN9zG0T/V2jnuJrev9N2tyuwI41R69G9rG17VOuI8f5RxsH9RzxtpZ7fHdA5VM6oTP2jHG/V7bQvywHOyl1anp7OG5/EWYUqRyugtyZPhQKA8g3tQeJ7FQZI6bnjHeaafm/szxZuaQfLN+eE2vEoW+WZE51ATSTogyk2c5pXq87OtHHQP9noH8Z0Z03nUzJKtcEsDp/jSOUjGqZpBuqdkq4lRHlIcjm/TOdTskY594y24kd6LnGM2iVRfLm7/L7xaZ67WUIyy4aZOGAR3PPxjZeMv0vazpdl6kYHszTN7sfBy2wtd+7bvBFcG9Xvc/irt4UX00hrD/lZhcIaLY+WwjkXMJ5NGHFM3dCM/vu1557Y4/l3aKkDIjIeO8Xh84J58vSxy0iRKwtteL6vjQeeTrun67FLkXlykuWPJAzFwpgYWqpdX4ar403J9zKlC8S9T60v99ZUVeWvq4LzMML1fq/srFYlnZVGRuqKUc+DyJSp6l4Pe7dFlMpHbblFkJchAHYY2TRc6Qm8fcDulHTi5WwaiVLvn+8210H8M6sFsH2umVlbdYYZXGyS72hl2A19Y6xM2OcIw+PRr/TsTg4aboqiPC0YZD7unjEi2xhiPrUtcaGIdeX6bxucMx2Ebpf+tTazjhtqZ4q0t+LQ1ODPcgnsOrrJrcyMtnKOajvltTRxXOfS281aDc4DF8xXjDZzFc2h7Ezfj+ZomB+NJ/dLxezRwPPVRL8Z0V5arOXXin2/wO+oivmqrlXEv/NPuyfhsruI8x+pTI7xMUVnZwbhsXuStHFtZhThXWgbnz55/rzZOVSnZvMG923iywpOua5zTnz3T0yNNvEv3YTz1tGBV4fR7FHdynlkOvmngZjlYvC/Hm+UAF/05xywHbzHxZjng9+Dd3+TX94CrtLfjcm6Q9hPs4hxcO9yt0swxlB3UiwcwDBaB4AE1fS8c4tSvlGuiauxLY6KPPRA5iFPcaH79lQ8CDMcMx6b2H+5YMzNHI/tZM56+hEJ90513IVd+R3BDFH3jXmF845LSiQMru+37Gc3xxAVMF6WZ+nKweDr4rqaGTdtN/MgJ73gdQrf5T7KJ/V2ySWcwLvxMnicpE2d6qnNmAlYsEtefwPHCwplT2t2zP78H74/5ZRLEoXP7a7lV3EjfHpbWUPhpnKWOnbTvkYHowBW9+kYZuTum3mf76icO0QjR9mBsldI=
*/