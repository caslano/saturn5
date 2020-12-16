/*
Copyright 2014-2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_ALIGNED_DELETE_HPP
#define BOOST_ALIGN_ALIGNED_DELETE_HPP

#include <boost/align/aligned_alloc.hpp>
#include <boost/align/aligned_delete_forward.hpp>

namespace boost {
namespace alignment {

struct aligned_delete {
    template<class T>
    void operator()(T* ptr) const
        BOOST_NOEXCEPT_IF(BOOST_NOEXCEPT_EXPR(ptr->~T())) {
        if (ptr) {
            ptr->~T();
            boost::alignment::aligned_free(ptr);
        }
    }
};

} /* alignment */
} /* boost */

#endif

/* aligned_delete.hpp
cJNgVD0dWbSrYcH8+fPVwb07wuesCp+zTjWdsynhjAuf00gnmGzFkufEftUHhlYHavdn1hTgJffhUNMrMrf5cBltL8J09UF8R/SH8wIZH0x/vwPVVtEnr5ysMNTWBwWCZHxl1s8y6zKhr1btcwaqrMPXTHz0QR3HZ+UljlLz+QJ0fvhqzPNZDHCQldd0NJgXUkF2GLHpCRaKzk4V2VP7lo0ipaL/5o2invTKUVl2bZOx9ZJkkuNhPy8jEn8U8Yc0uyXzn/dqQQVPbIjPPOsMdgm1UzIiqe1Ly/LFc9LAfSG8p629ZwW857572Xs+60zbmfKe1R+wCgKDCoZm4HJRoGCoHXgFqZnFrxQMrSiOLBqE+LO233d79m99DIeXLn4BMDgdrjODR8JzeF35VTdaqylBEH0xXA1q1qGmU3dhala1Io0Y6ZJtvk7aNHeKedvZ6mB6fWUmOJqfQ+OEgJWEklRB/XwFhOxpyRa7ttU/1bx1I/tgwCB+zz0EeHwmZsJoxF0Ee5RRX34/wctKrrdrd2beso18dhLdGEzwt6v/ub/U9yRrS92xDjC55K51S+eEVKY1tWvZrKhCeLmoCe/0NIEh5BOnWPGK5NSu6jEI2uCtYnA5iWeNZFN0UXtVvLA9OaLl+mEZyTysDoJ+6WPInxzLmMc7/tg5QR8CPNhMAjHVCgO47WRCB+fTaH8bmRKoLoLrq230W1MTt+4a0MOBx+chd9nZmCC14hejY5rWDjLapzYR6m1WclVsUYJRxxQq3oAvXJcckZdC/e/rHlP8NCekdB+YL/Nr4qHxZ6FU2Ih183tY4/c5s1/enppwrSwIGFbDuTKC+rPKzYD2FwSqRPkLApWi+7xMl3jOcAJoqZfaakbQdELrAdIbD9+jiwyYCa/agVJn4l2+jJRgjkUgRz7/8bTUePRpjpl6MULylp8r5e75kI+65aRdluZRgdSS+bMDn/4LeVcCHlWRhJNMAkM4Eo5ARIQooBFQIhENxiMDiUwwkaCgIKuiKKIi5wyghkNChPgcRVdYdb12vVbFWzBkFRIihPuUez1X1w4xXAoEUGb/qur35mUyCQHZ69v5lLz3+qqurq6urqquxrTFNlsrr/an0sa5hdabcdpq9bfUE26cA0uBJqI3O3MjWBDYceAI2yW2I8UI1wLKarygZVBR1vAVLMplpq6cdBPuKmrkTt0xvoe70C+/Du7U7ZM6sgTma/UF85dFj3LAxKgrAKEqr5L9eBtNhMR2U1ixL2RE4wQberx7eEzq/im98w9NvjILlSFOddd1aO1gGMsYJSBWGql+vlaNQawr/XGTR7UAgFS2m8Pf0GhY1pe3lxXP6o8r7B/zuVXZmKWdNPme8Cc7dgyiw3DFltY9f7t3MmVmEEIWNBYYylYFQNToAIPv5SocLbR+dDZPhg9Uzt7A3rqtu+DBBGKmuKyWebzdPuaVgiWzhToW97I0XfXvt5b/OzKkyStlB7EvsIMgaT8Sck+pEV5qo3/Jr51QWMFiNM/fNPUn/yquwQ8DYa36JVHCsw+e9jFoINUx7YFKyQtvf68zpl7ETmvGMZZb9frj1uuPXi/8pbzitM/9QTulXUtIfhcGeD2P3kixzaM/zBLF7lP4aFFo2kn5qOn+n6M5czh395UYq7sEVyesHgmpzae0w6rhBrdGNMllBHt2AcLKGS5nphEZXpuCwm2wPirBDR7dUOtwSkPdf3y2bb3yWvzVCIfa4QDxEXOpylPQd8BH1O0b4GRWH3f+3cTh68kDqT9X6DZvlTbz7o8lpu49O8vITMhGOiZ0c1C4omb9cX/GAgIFUHg9LlMO7H+l5gyhpfKBzarhsxXwGQt8NiHkuYc=
*/