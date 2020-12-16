//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_READ_WRITE_SINGLE_VALUE_HPP
#define BOOST_COMPUTE_DETAIL_READ_WRITE_SINGLE_VALUE_HPP

#include <boost/throw_exception.hpp>

#include <boost/compute/buffer.hpp>
#include <boost/compute/event.hpp>
#include <boost/compute/exception.hpp>
#include <boost/compute/command_queue.hpp>

namespace boost {
namespace compute {
namespace detail {

// reads and returns a single value at index in the buffer
template<class T>
inline T read_single_value(const buffer &buffer,
                           size_t index,
                           command_queue &queue)
{
    BOOST_ASSERT(index < buffer.size() / sizeof(T));
    BOOST_ASSERT(buffer.get_context() == queue.get_context());

    T value;
    queue.enqueue_read_buffer(buffer,
                              sizeof(T) * index,
                              sizeof(T),
                              &value);
    return value;
}

// reads and returns a the first value in the buffer
template<class T>
inline T read_single_value(const buffer &buffer, command_queue &queue)
{
    return read_single_value<T>(buffer, 0, queue);
}

// writes a single value at index to the buffer
template<class T>
inline event write_single_value(const T &value,
                                const buffer &buffer,
                                size_t index,
                                command_queue &queue)
{
    BOOST_ASSERT(index < buffer.size() / sizeof(T));
    BOOST_ASSERT(buffer.get_context() == queue.get_context());

    return queue.enqueue_write_buffer(buffer,
                                      index * sizeof(T),
                                      sizeof(T),
                                      &value);
}

// writes value to the first location in buffer
template<class T>
inline void write_single_value(const T &value,
                               const buffer &buffer,
                               command_queue &queue)
{
    write_single_value<T>(value, buffer, 0, queue);
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_READ_WRITE_SINGLE_VALUE_HPP

/* read_write_single_value.hpp
x+gi1xyo3Glk3cEnfkYG1gDyT7O/uBz+oOogKPNX+1IUz2dX97Mn8snfLQbdOilIiJmJDL2//r3taY8y+u+cEgR8M1sylx02R1jA3kpk2OT6ZXTrPb1MfGJQHKYL9pm5Wp/oPGn/1rQ+ZOUXRTlMtl9/DiC3h42T/eLyIP3njTvy38Th5LaKPD1HX/CZX8SP33HvDH6Sp2s6y/3cvc8b0+UZITvP1YstEdn5HlSw53ns5TbjSGyKPbTlF2JE8mmxcUguQkcpv/cNrJoibhhPvtRv1+ePhz1iEjey5bP07z1rDav05yBx9Hr2JG4X2UlhK9fsIP78lY2cYzwZYQxQb8q4FD7B/smxZJ6QXEKut9KXPT0yX7re3zm6zRi7Sk3Ggx6/Qawi30/43QJ1p7XzGDZ/KZ3tP0n9IwPP9rIlue3JdCVm+93Bb/vKeZzMuvnooer/N3k8JP6vY+cnuoa+wi/Y0Ghx7vI4ffOXlLHzEDJNjGHn8iHjcrCfsW6dOvYSNybyxQMneX7EHOcFNvelOciLZHqoGGtvlHQz3yX7Yi87Fs9LN4sxBxt/7EmYO4xeFtlX6T37BG6Ej8w3MvrjezEhtl7NZq6baH2GXGfqy0cVns3kT38lm5PZ5DSyyMfNq8jiC/1pIsupxq9z6ScmR9OWBJvzv8btFS+OivWp20bRmb/f5XNyzPBf2puSi/9ZW18Q345kG3PZWKecq5su/kZvp/PLCuPRHHqawc63VgcKrks+O4adsLeOcdYOyO1F9kYWyQPo2Pidv1EM253ddsh3RpDtAZPpXi6XNLa+GCcb49vQePtsaA9fafina+4WI3bwNzsp0ElxL77GjgtywcIlPvlzhm6zOePqG3T2rhyqij0+QPdjjGvvjxBTJnmnnp+bhwQx61l8N5ViI2+ys4PYezv5ffv9nuPinLli0v81LvRoF9kXyTJ4aGPlhJ65pb+cMd14nz3k+3kje9nVudIYeZFYRR7ltgo+qV3ienQHO3mDT55FjyvUK+ZnP1T2bsaAteZzS7VNm4LJxs+VbET/o1tGe3aATe84yt9yCjJPnem6leJXhzjnfaVogpj7Dlk8It6M9r11SpCW/xc/ob8aMlwiB/hEHLmbLfOVzBnKeUkcPIpMnhirbdo0LB4dwfZON39a7vMXdFusNi6bc2wZBvkBcVJ8jR7Sx+Xk6/7UsLZ+Klb9lW/ux3YvIuuiY5uIF2vFnBVknKNf14chG/2ArcnjE8rJrlT2Hfp4plxxW/aifQ3Wa4JnxcQr6P4rNu//3CbouXS29l/E3z8yZjzIjk9SZpf2nU9fKXq6WH+mTAlSh8qtvOeXO5neW4wFfD5/w/d7tY6Wk7HhrHtD9nq9mJMn29vJSAybc+OUoEgnYacy5QNFn9Hp5Kb9qfscmyof3IWuh/nqJdq+LZsbCs3h5aPmNvldjHUz/b2d9g6r331p891ZLXKPprhcW7sdCy6IBQsfoJt7/J2hr9+Jg/PJ+37ysyd4eVPxw++6YT1Z2O8++4qyH+e7Z4qblxqLzzf23GI/Nvab/9jfzypXfAvbye1edvJ3dlJwbWD+J08K1VO8nF74ddn+m4kCOxHXGtzbYDyKWtnQY9X2/RZrJsXIQ52/coyNB2QXmevFVstJB76vi8/fz54uUIbnYXKuTx0TF/NHus+4/2AVGY2jc2Ok8bx0Gh+aJQdZzVbUFaXIKzLGrpave76/eJsx9gSx82r36L/9HYPSXeJXIJetsS5CP9kUO2Dz6T34bweZKTeL4k2u38K1V4b2PFRup5zE/uQpz7tn0mxuvnLnstVucXUTcfpgsUwdae86lB9iC39leyewVe3JvWVuf35Mvkc=
*/