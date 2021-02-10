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
xnWlfyiaSdHU8sbF2dvjb97Z47y2kxxUVV8Y0LKg1LCuP/IXaCy/dj1FVxrVDDn2gdmJHPpqPFOrmxkqOtF2izmVdNmkiG/FZ/1Nyk26Ka9v5mvaKSGREl8p26iipKgrR815caEEaSuZqJG7wrHkInbYkCy5rKbzFYWii1qExlIFZeEiAhzBJP7yTkgNf3mZNyKZCUTOhu+/U3CdnJ98N8gO8eOyWT1/OoDYtbobiBZa3kHelqffn8u7QQ4/XAgtlkEvxo8H2YviHfAkn3KwdxeZjPN+3jWljPDHt9/p3H96Azw5uTjK8PBbUTdF2jVxXhaFDy/Wi0mZVxj2lS7ssJo1dSnH9EbkVBnt5MWb7PLsVQDraDS6B1jcnUEqcMtrZ5+egzUs5QAJazNoZU05vRmIjj+fc5Ro8cAEV3nbcfj0ZqZ6qlCxWnmiCDi8dbDLCUXHryqKK0cgGVyLcnNny72QEzMLEVmzLX+Q9a9A4CS3uPOqaQp1xhrqSk+uEgWpUuOJmQHJ8KOkX7Sc89uEZJqpmubAyjWA7GPWQtkeZScie96sF65IqLo+L4VaX5e0+ihhEgFbKJwAnGyhvYER79vDP9ntUDoM1n+gWzar9Hi8EP00HwkiN2W+GN4WE5H9G/gzxpx/ur8/no6x
*/