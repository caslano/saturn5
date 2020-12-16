/*=============================================================================
    Copyright (c) 2013 Mateusz Loskot

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_ARRAY_SIZE_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_ARRAY_SIZE_01062013_1700

#include <cstddef>
#include <boost/type_traits/integral_constant.hpp>

namespace boost { namespace fusion
{
    namespace extension
    {
        template<class T>
        struct std_array_size;

        template<template<typename, std::size_t> class Array, typename T, std::size_t N>
        struct std_array_size<Array<T, N> > : boost::integral_constant<std::size_t, N> {};
    }
}}

#endif

/* array_size.hpp
JQcukasTOyG8fV7XsyRXJyK16min1tA+vcMK19NOHQ+Ovh5uHNFXS08IP13t1Ne2rnFucORR3ZKJFs4tospT8lF2owcqvqqdeoPKp3LITTzsQRkaQJZ2ukI6qIGna2RIxxrpKpmRt0LXSQOT6LnlEldnFSPXVfKAaji6Tvq4uVBXylj6Pl0rd2g6io6eQy+KF+h6GUFwoitmgbYcdM1Eya36QTL+JtZVM4fmna6bDv7d05UzRN0jXTszlKjQ1dPMHevkcTyi6pb87Oy+DjBXtUoQqJeHP+jLdP3cWZLKFdQTknQNjYQkXUULOJLu3FVfj3LAkCgHei0EoR5CkANB9K7CDvoBO+hHgY7DjfOe+QpuDLwEwgv1JrwklpeNOlfhpWp5Kfd1WsKL7uzYnk33dsoVmd0ddfsd3d9JoWajOzzHfmVQ1T2ehrCjuzw9oUf3efbQU9GdnrrlJ7T8dC0/meWndFhG+FGPFQg/6rIS4Ud91kH4UaflQ1CoXiuGojsfwNoDRaicUKR+KxKK1HEVQpF6LlcoUtfVForUd+VCkTovZ+qp8wqFIvVemVCk7ssIReq/AqFIHVgiFKkHO0DRqb/w4ShUHxYLS+rEdrBkFqUX84QndWOR8KR+rBCe1JG5wpN6srbwpK4sh6ed+jIHpjx1ZqFQpd4ss1xtLVfGclXDZ7MyWbo6lq4EulBL+JIVCrbc90z7VZ5ok3SR4hkC9dxd1B3WWLmEtZ3uksAa3ttX781KBmu6P6D7iNb96U5iQ1jTvcSesKa7iXthTfcT68Ka7ih2hTXdU9wKa7qrWLOsBbDGSmJZSyxrG8vaQVhTP+8La+roY2FNPf3Osla6ek9YU18fCWvq7AuhTb29K7Spu28Lbervc6FNHb4jtKnHD4U2dfmZ0KY+30Cbq04/EN7U6yfCm7r9g/Cmft8X3tTxx8Kbev6d5a10/Z7wpr4/Et7U+RfCm3p/V3hT998W3tT/58KbdgCO8KY9QCi8aReQwdtpb8IIb9oJBMKb9gKJ8KbdwMHyVrW8+Za3luUthjfckOVtV/LmvWdar/JMyl0Lz/LWtLxFwpt2uUWyO3flruWtIbzprnXP8pbDm3YbunNdF95077orvOnu9dbyZuDttKMRwFtPd683QpruX1ctab4lrWVJiy1pa0vazpJWdo6ekKa9YySkafdYCGnaP7pCmnaQbSFNe8hcSNMu0hHStI8MhTTtJDMhTXtJI6RpNxlA2mlHKxHStKM8CGnaU/pCmnaVsZCmfeXOklZ2lt55VyISzrS3LIQz7S5d4Uz7y7Zwph1mPi/UxztCmfaYoVCmXWYmlGmfaYQy7TQDoUx7zUQo027zIJRpv+kLZdpxxkKZ9pw7S1nFUuZZypqWMhyX7myy02spOwpnfsmZUOZayhqWsrZQpnspuaVsbynDc+kuWVPPRrpCmZ6ObIUyPR+pCWV6QtIRyvSMZCOU6SlJVSjTcxLxX109KVkLa3pWUrGseZa1pmUtsqyllrVCWNNdCldY032KtrCmOxW59ovCmiOs6W5FKKzpfkUmrOmOhdFOWlgLhDXdtUiENd23OAhrunPhC2u6dxELa7p7sbOslfsXnrCmOxiRsKZ7GIWwprsYru4zCW1toU13MnBj530wR2jT3YxQaNP9jExoO+2ICW+6pxFY3vBlkIYj+/u8fcD6+Qd7ezg7u3s4E692z+HDmZ7G4dUe+fz4kdOvDP94ry+cBcKZ7ovh1f4Sz9/8g1y/cBbofk73kfeHM/Frv9v/Q5vuo+HXHnUB6Uv6AE/82qNuINfdUWgzJnzPNNWv2V3s39Qb0Bk80RfQFcBZCmWF7QfoBuCrAV1t2OpBVv4=
*/