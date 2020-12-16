//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_BINARY_SEARCH_HPP
#define BOOST_COMPUTE_ALGORITHM_BINARY_SEARCH_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/lower_bound.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns \c true if \p value is in the sorted range [\p first,
/// \p last).
///
/// Space complexity: \Omega(1)
template<class InputIterator, class T>
inline bool binary_search(InputIterator first,
                          InputIterator last,
                          const T &value,
                          command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    InputIterator position = lower_bound(first, last, value, queue);

    return position != last && position.read(queue) == value;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_BINARY_SEARCH_HPP

/* binary_search.hpp
1biMt2ZxF5o602bc7yDddUyc5Wb/pt+I3O34SzZ6/DJJY6rKhMN6S/MZv5ZgKX4aiZ/b8IM9vjw13mWyqV+WxrNXZLZaPsqnvt6LicbvYYkvfM52kZ6z/Xkt9oqM1bsPcOrdZa75EYmLvWgahOx/VvtstX8RY2+f5bT3j7GPjbHPNXanHnWn1nu/pR/Vo+ZlS72nEsWoUb31qOrHL3qWlBrs205ZIOetO92cGhL+jLAzhCHdab4zbao69UyXyjeJ1Z2aujddri+1hvFX26r6aWjq3hNin2y3sxLtiE6VJBiVaqStnZPtrlNdxrUH5NpGe7qd4qoznY7MYpHZa3ejNHbYvijd6zKH7vX57MjZFQ9zHxsnhfU35wYSm6K+aeO9RmWa+qnkBiyQ8y7WX4GitGta+7S2/Buelps2AcVmRtqSpAT+lqSNE9uk4F++J4n2NCdtVFr3tC5BrSjBuLWR+L5S+5ffS9q/RXvHbsp3ld0Qt2spuQF2dnw/qv3mqyJ7jukzqxsH7WPok5p79pn3iExn7Zci8XXFV3/rDfZYquvZd77Y2Nl3viL2tNi+0+RtllyvY/RvH2SbPvOE+W3jmrZZcv0waSeN0X2n0f2/J/J3mX7zKok/VXXwJjzq7ocW4Xv2nb3F38P4wx7lrzE7uPS2m8f1n5ka34cit036z6biFvHbA9e+1gFrsJ0Z0glqvduZYnR9G2uj6xtwkv6kwEXXN8tF1/d6trO/TW7s7C8bx9jHxNhnxdhLY+wXN3bvbzvWcV8LtatJ7ddC7Wry9a2FCqfveB33tUIHmtR+rZD48V4rxPV/7Vqh/zZ97WzR16469sFlX/VtVfTJgMNPBZq0a/Ov19emJ4q+sOBHow7dWdansuveFz748ooOtdfjeuhlPfS4/7v6Wne9bO3fBzyRvrZjlL52gNHXRr4vUB3t8IiOlt9N3jraXqq76w3bwD4wV+34Z2Svv1/0N9IO2AxzUP0PRq4THA77qi72DDgSDoajYD4cDYfDsXAsHKc6vvFwpupkF8OJUNozvAROhZfB6fBqOBNuh2fDe+E58Ak4Gz4F58D9sBAeg/OgbVMusD4sgplwIWwDi2EuLIFdYGlYN23puBb6tdx8oqvko7rOIHsYXaeOHWW8Gq/rbIxcQ9gSNlHdZleYAyfC1nAy7ALPhW3hRtgOXgHb615gbeFdsDN8Ggblfwdz4Uewg9Ht6nNC+/QBJ9ABHziJ3DZ/DXWnDr2pQ2fq0JXuf+PkelIvHanqRdGH1kwXGtGDuuo8Vd8Z/45nwpui71Rdp0PP6anfdOo2nXrNvDcdus04veZ+TESXafSYqsP0ekf05LrKOW+KnlJ1lPH6yUBPzAijk3TRR9ZOFxmlfzTvl255M6h7/Of0jt46R9JI+A1710znqPpGdI1e76Semn6xOd8HYFSfiC4xXo94DL4WJCb2PdaGY42eEB2hQz/o0A0WrGBfO8wWzN2Y5zBHVpzWCZ7+nP6c/pz+nP6c/pz+nP6c/pz+/L9+/m36/9IlxV+X/r9TpmX0f8d0/799mLaYhzBXBt/LPWzLGdH9+oSOKyoMrgTgWj1zZtGyVRVR+pvvi3wTnZcO++9h3s+aIvat1kjVEc7NUH2VhjHB+OlqdFATxf4TjdOce2T0TePk+vViLzD+O0XNhTvfnR8t11eLvdTI5+p1dE5iT3TupRdzThV+zDlV3IIo/eMKE88jItPMNVzywWdBvz5R79IXyvXvmPcYu3B/zld9TFe+d9MzibvDJbXYfy90ppDcJ7P/3twM1ZOrW4GRk7KNOS9Yys+cF2z27tO5/+HhNST6bvcmTEvMSsw11KG8I1KHCkZN0jrE4Vc=
*/