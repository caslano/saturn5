/*
Copyright 2019 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_NOT_POINTER_HPP
#define BOOST_ALIGN_DETAIL_NOT_POINTER_HPP

namespace boost {
namespace alignment {
namespace detail {

template<class T, class U>
struct not_pointer {
    typedef U type;
};

template<class T, class U>
struct not_pointer<T*, U> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* not_pointer.hpp
e8XmirxqaBocmY0HD2qpBfalBXsN9fZlWs+Lu8mGKwMXy0CoGwwIqg76p9vWh9WrUjRb9XJrS6O8GIaJUFZdJ7oUC97hVrDoB1ylw7gG4+4LuytjtNbPhpSm6SlKdLAAPLCQQOPzMT0ChAlsIvmtMdx+yHu0PqwpqeUVmTbrLtxNn2KPUOlP68OoSmfsc/gbN4gfK8/03HJv2sNH/eCCb+Zcl37HSv/Vv2KsmPD5X009yv/l6dvuXHTiuI+GxM8=
*/