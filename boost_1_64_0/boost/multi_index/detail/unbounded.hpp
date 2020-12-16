/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_UNBOUNDED_HPP
#define BOOST_MULTI_INDEX_DETAIL_UNBOUNDED_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/detail/workaround.hpp>

namespace boost{

namespace multi_index{

/* dummy type and variable for use in ordered_index::range() */

/* ODR-abiding technique shown at the example attached to
 * http://lists.boost.org/Archives/boost/2006/07/108355.php
 */

namespace detail{class unbounded_helper;}

detail::unbounded_helper unbounded(detail::unbounded_helper);

namespace detail{

class unbounded_helper
{
  unbounded_helper(){}
  unbounded_helper(const unbounded_helper&){}
  friend unbounded_helper multi_index::unbounded(unbounded_helper);
};

typedef unbounded_helper (*unbounded_type)(unbounded_helper);

} /* namespace multi_index::detail */

inline detail::unbounded_helper unbounded(detail::unbounded_helper)
{
  return detail::unbounded_helper();
}

/* tags used in the implementation of range */

namespace detail{

struct none_unbounded_tag{};
struct lower_unbounded_tag{};
struct upper_unbounded_tag{};
struct both_unbounded_tag{};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* unbounded.hpp
E+nIqjB7diWT2md2plN04OVN+3oGMZClYfa1VGJH5ElWjNmTircyYAzOksdGaT7zvzZGP8zSt5nHiOO4ryFmy/kurdzWDluRp8GaTuk1D7GTxTHL+G+w2r98jlM0ZfbH27oz0e9k45mlzRL/FHn+6xShzMqEFFT3dAxW5GHbSMQw1yk687b+FLkEaxZZI2brFn3vjXTznCIbsy0BLvUeGVlJZiNqTZ6E9iRrwOxTwKUT6KN5ah6tTlrPnofNxxicr9bPVfSHFM8cV1DeguRzBmm6/b1Dybxg+nOGMF06/blGuM70+4lH6Uy/n0A0WUqYfo/5WJ3p94qPJ8vHrN/sCeoeWayuPN39LN9YfZ4nPtdVe1aR/cmseO0fWJfiyHw1ZZ8eZHuNPBc5BRUOi3WUWKD2Bad1iVnZL+MaIN0SWntYnr9MvXkcY2mpU6QTyqwLN6OecWQemrIbH5acQ+zLnWKxUPaxanMPzHeykcxqXn61Ff2wQp6DSTt+2wf3kBLI9rPyVvcO2Y/4VjtFemabPy4/gTzXOEVGZjkaxVRBnmvl+YQ03XX/Ot0Y1F/3r3OfLsTEwsj8YIbzLBOLMckzzqSe8SbpEkzKE+vdW9B693mGmqQLX6/O2VcmnUvZfU6hnmSlmJW5U+MV2jrOKVIx616ilDrPilPH1BWGY2oMWUtpy5Ouw4vUG408NyRfj0nTXY8FkRVhtneIS/0WkayJpmxN5fH5kOcmpyjvoWxh5gvbkG677CNpuvdpyQJh+t83xpI1YVZ9dINBKG+H+3ShO9yniyPTZAzL6P+pIwf+R71b6BRXmIUfK6jO3fY4xQehbP83T/Ub/r2qH5Yafyu0V7Vn0v2U+d+ue6L/9jlFd2b9+v6J9SWerAKzZ9GxKRF7vJzT0uKefLGiPfc7RR+hbESPSLUXxgF5PihtTvtWq5GOLIDZzZiPrxEfmRdMfzyKJfOG6Z93xJHtYVZs3x9+SHfQKaKZja85dy7675BTzGCWu50d7/OJw/K5jLSWKZerZ0RklZhtbrUNeUaTfWP25ezCK2jrI7r4dGuIiyw1zHCtRuYHM9x/OereQkwsjGy0tMUa1btPbFXEfozugzHLe+hBI8RH5mNV9n3dyILI85R8DiRtaaHEL2izs04Roykb//zfObBzdL7L8iyb/o76Tf0lOhazPGf+Pgbme9UpGrI87f0KHkNbX5NtLU3X1mSpYYa2NjHf67I9pena2sTCrqvrgEX0hwEPl87E+CTzghnu25B5wwzfodKbft8mspTM7jS7D0sk68fsxoLjKzH/bjhFLmaLGxWdiPLIcjM75D1gM/K8oStP960i35vJ5zaIb9VIH7QZWRqY/ne7YWQx0hZqVLfxa44gz1vUnhZl/hWWlFTvXMprIGktty3GvYTwBKfoz+z1OU3tPXxX9rs03T0PMj+Y4Z4H2UNmTb1OqGe09+h8SVps0j2P+JfjMY/IljAr3HvYB/WOp6yntO63t6n+u6/PM2OtDeFolwd6q5qp4Vm0tcF6nB+pjjlk3sw2TLOrPXPIwphdu+FQ48yQ7lLXLOqcjywlM6+xizEmxEN9OufhdBURA5kXTD8fgsj6MNtxvK76vS9ZM2Y3+tVbgNgfyWeR0s79l6+7jq7i2OMAPvcmgeZ60GBJcIdbQnEJHjy4PCAXdwgaIEiA4hacBmmw4pAipciDUNza4N4G95LgEuD98tjznd/OOdl/msN+OvKbmZ2Vuzv7pdoE9ANZV2aFVhfYh3o+1Kc79DbHT2gzsqXMSjpnyWe+HvmK/cz6XLSfRHyP9emav9jdH21G1prZ8r0t1qC8J75iIjPTmnO1Uc+n+hhqtYqV44wsgFk=
*/