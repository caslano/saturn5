///////////////////////////////////////////////////////////////////////////////
//  Copyright 2018 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_COMPLEX128_HPP
#define BOOST_MP_COMPLEX128_HPP

#include <boost/multiprecision/float128.hpp>
#include <boost/multiprecision/complex_adaptor.hpp>

namespace boost {
namespace multiprecision {

typedef number<complex_adaptor<float128_backend>, et_off> complex128;

template <>
struct component_type<number<complex_adaptor<float128_backend> > >
{
   typedef float128 type;
};

}
} // namespace boost::multiprecision

#endif

/* complex128.hpp
+hz4LB2/r74+KveZbxdeC9zFjfnFpk7SfAFOFttQQ2jZEJVsZfXi6kYfNvavgG86eADRp/S1modFeCRWGNt2ksEXPbu6MSjPwlVGqTMz2rdYe64+J8g84gIUYUkRO0kbRgXcHip/qwtwHu92+AttuMCa7eZsg2M/uFn5N2PPlmOt5nvqFOXrtDIvKyK/me/5B/I9W/tdPCt/5wKcGMDIAqZOM1/2vRb5hHCiqhI2La2hmqcr83R9K2IpoaPCf2yeC9ZQ3f7LhGdqha3Q953YM/NcWF0vGbeqNmfnkqT8/232V7bfr+2MCF84O8VZksNR0MyXKPkXgVHi1/0o7/9ubMHqGSat1DXzoYsL41OvE3PkHJHbgZ0WIVsq0W6b2wPIuOOgjIbLXgSebm5I55B1lPi/QGztAi41lryI4pp775tDxBex8NPChUPG0WPPHJ+eOXHylDI/P//1UVnWyG1lCdwDoadP4nkbbYOO0v5pp2Ece3lq7p/FJZhm+heENe+5et0+StenrJ04bS9sNfAbbJrGQ5CyPzLPbhI5QysI4WJWeP4D+bpZI1+Ms36MxuqAKZZn7XZk5qtJizqH2ibgfhnviu/lUjzumm7NVHTcYSsbejzXXUY63eQ4DO0Xbmi4PtbG7ArANpVSub3B25/m7/qzc/lZbx6CbZdncox1MUVlu7gm6U3HRhR6dYpE+kCjw+lRtuFW6fwB+YOYowroxrYvrKyCmZAcs+HwVjOWi4QxnL7fhOv1OVvQEMq26NvNeOKX34BRbfJPjam4vhbb42UdQ2J7TO7Q6VANvj1/jdOl74G0N5CG3wJpczuRJr5DbdvBaOUo4XE1y8cJ+J/V9fl1wPPvgHEJdSxfxojeXsXhR0XMSwoG+fRFfRN7FAz9kMjrRQ0HySf7XWKHML5XwVSZHkCbUWbfxliWV5px6zyOzzywFrr3fQxfNXJ1ZQBLZh/H+NFxpJHKoKkDFphkWYwNyG8N2PIuhXOG9P2VJ5CujUUgizH0VhOuj2PhqkTndeCaML2f0UARvr4AkVThyjMP1xmJ9/WSDne5BhlPPynTm2W8jjizjNZTgo511Hp9TltvrIPb/h8w4YSPwvIE0OG+KDeFB81EzD0DRvN5edqE2bgoY/5gwKhxLOYOGjB9SJ8rYX5hwKixLty3MUzzPflVna7F2ZyeBAy+w0BpifZ9mabYWEy8ndG+pI29D/I8K/d+fJDlWZmHmbQGLavWl/J9hu26oENm+xbH+n8ssXCTWlyAPpiv74qjx2ksqsABr33XKRNOQ7wMOeWwFudhv1z22cKOW4ld2BaGCeIFMJ7llIw/5bVcuDLCqfx5iD2WIRzwmDfuOLU39uDeEcagc9QDiKHtsyuXOe60fLhfgR7BzWapviEguHaaJ6BhbVnnzipnzUTGnfTdlgMiOKDpXxe11/J+jvSHW6TQQtcy5ivBNi7JZRI48gVp6hSRnPJE65dN+s1iO/TYec46i4HK4DbnUrvkK8dp3pii7ceF60XS1zpu+OZafLaXjiu5HN088UO3jV/RyIbKcp3wSKzAy5PIa9Hv2swG+/sOGU9JASn84CWmehuSk5kDdAVj5h0n74mZ67UiaAaMD1LCwpgHBB87WZS6cc7GiRl/n8jUyhzHzj2/Hi9oP2JlHD82rcQysdMwAPMUmvPm4Ql86vF6SOZ3HDx+2wk8gAEHkcCnj3nVZWwB/ihZ1E7jXBlHKLODsfWnldj6mR/nReux7Ybw/TAZlvrYAwUiu0dU2bLVN9hvyXVPO7kNF6TUt5hpr/aG+V2CDVxQ6QVeYrEAKIhF/SPpN9/L4d4XwpQKXbpuvCzjnkkBmGZFG76Wonu8KuM=
*/