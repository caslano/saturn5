//
// detail/non_const_lvalue.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_NON_CONST_LVALUE_HPP
#define BOOST_ASIO_DETAIL_NON_CONST_LVALUE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename T>
struct non_const_lvalue
{
#if defined(BOOST_ASIO_HAS_MOVE)
  explicit non_const_lvalue(T& t)
    : value(static_cast<typename conditional<
        is_same<T, typename decay<T>::type>::value,
          typename decay<T>::type&, T&&>::type>(t))
  {
  }

  typename conditional<is_same<T, typename decay<T>::type>::value,
      typename decay<T>::type&, typename decay<T>::type>::type value;
#else // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  explicit non_const_lvalue(const typename decay<T>::type& t)
    : value(t)
  {
  }

  typename decay<T>::type value;
#endif // defined(BOOST_ASIO_HAS_MOVE)
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_NON_CONST_LVALUE_HPP

/* non_const_lvalue.hpp
uV8oJnPCEzFNF3kmMl3mBRiqq7wcOV3njSjoJu/CWN3mgQXvCp3xCEzSeZ6IvC7y97DWGOq8Czt0eOD7zbMOn4wBr/XZD5rjCd45tjd4z4eM57V6UpaOP9Va0pXTzB+m69zkLJ2EGbrI38MsHd6OhTo8+MPeITo8uej4Ovwx7NDhK9DW1TOzdAv2DjBmvhf9usmvP8s4Dxz+qn+DHh1+AqN04ewsfQsFXeeBU8yJzvFsDHCc8KPI6fD/ME6zP6vZdenw3dN8RocfxEIdfgZLdfjoc73zdXgKtuvmed6pmOJa2vyuj7rvxlDkGzBooLHxS9huezY9S6ejpMMXoE+HV6Ciw7/DEh2+Fyt1Oj9Lp2G3LvFS7NN1/sjHfN/oCu/HNJ37eJY+jGHGUOKfYZRucEfJPOg8fwG9uso/wyzd4Ms/6f7pNg+8wH3XGX8Rs3WNh800/oPsz/sxz/bwlE957+nwwX3Gr8NvxCYdfjd26BrvQ1uHey6yhhwzvBy9OvwrFHR4G6bo0sVZOuhS3x06vPbTjqmzz5jjzzqvbvBBs41Hl/jNn3e+aL5jjnfdIPt/wZr/ovWvG/zDKzx3OjfPe75inejaVzL/PzvPuC5elaW/zHcuXbg6S99AVdd4HfbqBg9a4D7q8P1YqcP/xCad/5rva/TrV/0j1/664Ww+MU63l2XpqpusK13nScvdi4O9Q/hFzNa5m61ZzNN17l7hfaXzfCoW6yIPusW60QW+Fyt1mw++1btdZ/w2rNcFPg8bdIkvx2Zd4VN/5n5F848w+PXOy7tQ1OFZK41Th+9FRWer3MPbjEdXuefn5mGwc/GfsF2H+7Fbh8+ou0dDzC3Pvt1vhhgzT7/D2Bynwsesdr3mJ3w5ajq8EWt1eAeaOjx8jePrcC+SY4aPQY8On4SROnwqxul0p/X+K9eos3VZehqzHCf/a+PCPJ3W+965y/nien+TpYuwVFf44t+ac13nvejRWSNLq7BVt/ji31mHQ8wPH/l7z5jtBV60wTtZ5+7O0pVo6/CfkcxV+LCN9tfhPEbr8Mf/6FnW4RmBDl+EuTr8HSzS4YM2mUPd4MPu0UMch4tYostcDXSdt2CubvOQe7NU1jkej2m6xFeiqKu8CgXd4IeR120e8ifrROd4PEq6yJdikq7wDRir67wFC3WL96NPZ5vdN6zQef4K6jr8k6bvIx3egt063W+e0a9zfB7GHeIa+RmM0vkHsnQKenWRL0KPLvPXMUxX+RYM1nWubPVbS4dnPWi96vByzNb5bd7bGKBLfAMW6vA5f7VmdPiTWK/rfN12a1i3+C1/swZ0gS/GPl3hh5A6hof9c5+NTYcvwWjdeCRL97SsQ1171LOJ9brFL2KHzh4zh5ik8/zQ4+6dLu40dpR0hYc/4VnWRb4fFZ12+W2APt3kp7BVp3+aA2zQVb4Pq3WL1+w25swa4NFPupY471N+ewbR/8rSr5HZp7bH/Xrad7ou8D0Yqdv8ln+7Zp3nCzBJl/lGFHWdH8c0nXvGeFHS4SWo6PAX2/69Dn8FdR1ehQ06+4/fUdiuS3zBs9aSDh/3nDXQOZx916NXF5/31xFoxRj4xy9Zw7F9f5be+7Ix6PC7U2eap8OzsFgXXtOZfoAVOnzngM60QYefxQ7dOtC2gZ2prcP3DepMg7qGv+oDXteZenWThx/cmcbq8AVDOlNRhxdjlq4e0pme7+pMFZ3r6UzTUNMV3ouGzh3amU7Gdl3k1x9mbLrAe9DSucM701ewqNu88U2o6fBLWKvDnUM7U1OHD8VOXeIHsc9xwr1HdKZke3g6hurwt5DX4Y2YpMMtlHR40JGdaa6u8AakHvPDx7yhMw3T4fc=
*/