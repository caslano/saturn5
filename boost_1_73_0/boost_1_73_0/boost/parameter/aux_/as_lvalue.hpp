// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_AS_LVALUE_HPP
#define BOOST_PARAMETER_AUX_AS_LVALUE_HPP

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    T const& as_lvalue(T const& value)
    {
        return value;
    }

    template <typename T>
    T& as_lvalue(T& value)
    {
        return value;
    }
}}} // namespace boost::parameter::aux

#endif  // include guard


/* as_lvalue.hpp
Sm7L5h/bn9vS6y5a32c6ab2hwNl8wz4qfJ2g10HIc2cmHzfDY+OW82a9MiZnbteG3hayekfISs5Rt3fma8c+ENZCyOzdbLstf/+QQhtE2/eStD0hNXnbD0TbD0VbOa/u19Xul+GyNZbUiUqH89+BPhJ0Ps62bDS1PsteB2xKQp/x1hL6nwn6/7Ho66nhHvZ1PMu+nq48j/Rw2ikbz1tCXzxP0mmLol8Gd+v3m2w795HtVR45nTb0rYLHxpUM7zs=
*/