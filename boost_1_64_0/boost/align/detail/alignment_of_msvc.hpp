/*
Copyright 2014-2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNMENT_OF_MSVC_HPP
#define BOOST_ALIGN_DETAIL_ALIGNMENT_OF_MSVC_HPP

#include <boost/align/detail/min_size.hpp>

namespace boost {
namespace alignment {
namespace detail {

template<class T>
struct offset_value {
    T first;
    char value;
    T second;
};

template<class T>
struct alignment_of
    : min_size<sizeof(T), sizeof(offset_value<T>) - (sizeof(T) << 1)> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* alignment_of_msvc.hpp
L1vym3krKhrX1zMo/YMv6vw/zr+KRR8qSL/ie64aylBjq9Bm59wNlJC/z2TuYAvD2HEsUrbxEsgiGEmf08zd8I8CzN0lRUeht5xztKMNAvzE0gxz5wEmpMmCMaKdZTsSpiaWDgmRyHwg1nRwvHB2vah2x5yjv7Ah8JdD8JoWHlbwZtPcpYNDVM3hUuLZOLI5q/fUf3r+j/KgCj2qDnH+t6QvWRbi/G9JT8JaOYF9fuzRwPyJBJZE8oNU7/eZRNCkDf8En6TYcIsjRWJs5KbKeqgqaPbueV/kbEPp0DFSnb3WLButy3YPKgslNgrCmDpc5UrhgvZNDf1JklfDkcyBcErzJZ0n4f+O6BWxRQ2r1PCuVJdA/snK3ABv5l5ss8INMiZwH1MPopTKWWMW7SRFC5Yer4hfXU1FSlZopdCPYP7Ev8Vtj8aEVVrCy4PCDz/WONwhKFwcFF78CMJB8q96Hh2j5Z4+eDjrlRoZlU4g9B8jAho0O+w0yJ6zP4cOwnTspC/t6frTmP5J/XATiRJpNXWorTH+Szr2zzT14XKwystNfZC0EEz/6gP0LY1xvnd9EP0LSj93ZeP0yKD0sBWN07881Dh99/LG6UuD0p+HZK2R/UNQ+oTKxuXnBaVfB8WddbyuPRQYj2QesLcw4I3635Cunlx28vFKNNtL5vaO0gRY5/9g4/TWQePxUVD6umWN098ISi8LSn8wKP2O2Mbj5QtKTw3aP8cEpafXNB6vAQcD45HP42V827h8YkO6Kqg++Xh9+V2gvXxub2XQ+C8NSv8sqL9PBaX/qTpo/oPS7wlKvzYo/fyYxuOVHZQeFrz/B6XHqMbjFRlIdzuIhsElWZ6H7I2iafRy/J8xOUyrPO56Xvptk/KZp1J+XtPyac0sL/1vXB72Vpmp9NGy6DZ7mC9a3tzcoTn9EO1HNirvk7eY0SDgSLHCwUROQDm+/UPBMC1ff/mbhlqNLQQPNHp57KInwg/XySnCO1/4JzFWnYlJbaZ8fcw3jeCN5H6h7iSqW3f3s2ZRZOv5xQ+5t+m/9SDb57/xRAzk6u+amu0z8GY4OjPCIQE4Olmn/bh2EgPeuVTgdUewH1ejstknnpDnvwOh+5t86v3F/Jwf0H8Eat1ixBTVwBUUeaxqy6rDy3BuqY3hz+582fUpsa9+6nGZqw3RzZirQHuxRenhgBnAV8IyJmR6xPHSYUYTav6hIRD7T17O0bCRb4TPAyTdXbpAwN6LLb/Es1n53padvBdEUVsfE9X6QrJ6+b2oXdxQrzPTphdcNaJNhD+hv7rKfQGIMJyQQrHj0QZ9krHOdEs3P/xEbukantLXSHm9VCxCDnXNUpwD91HVbGg52eQX5WBAMoll4CZvbWdsDEqtiUe7rMFU971DMosZd5B8WGQl34axDhlO8Nr7rinaHV7QFs7SfMkQezjYbWpqJdChpRnca2dB0WAjmthep8QDVaZSttYkUh5oxl22kk+7PUVckshNFxbr1RHcAzI/+GrVz/nT9P9r4ecSqG+d0LeCWL1arJZYaxYhVyAw7lBofXEQQrJ/NdNfzjt79WTtZyUyFlAxux+47EPEk6dcL92cW1rGbaMllduOxHZGPXbfYjKtNzF2CJjSEvhbrlwsIg1tptnzkSCkFQ90bnURaaGP1kYUJ6GdQLN3E1mfB9ktDDcbml2jZoezGBl1tlXO7QFDj/yAYxZ1FCIgSzWPfXAc6BcmhoUR7Ld1seRu/W2TCr0kfmHrNEHgyagH5fbM7H8fChqbuLIpfBl0Cjn7VduwH+fI1dk7VjP+9PNX+qszPilca2np2W8oF14uQu1i5GVt1JJxFjJStePQBG04+ENVD/qcIK0=
*/