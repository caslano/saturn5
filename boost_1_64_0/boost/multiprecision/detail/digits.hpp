///////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MP_DIGITS_HPP
#define BOOST_MP_DIGITS_HPP

namespace boost { namespace multiprecision { namespace detail {

inline unsigned long digits10_2_2(unsigned long d10)
{
   return (d10 * 1000uL) / 301uL + ((d10 * 1000uL) % 301 ? 2u : 1u);
}

inline unsigned long digits2_2_10(unsigned long d2)
{
   return (d2 * 301uL) / 1000uL;
}

}}} // namespace boost::multiprecision::detail

#endif

/* digits.hpp
Lo1N/j8HR7co3YcJndBVaKPRTAZJ6T5C6WzQi9j4WweFfD+a013ufOSd5J5Z3qH/6xX0/SC0FfetrNJNwcb+BtJijASiC8q5TsvoxxHsAW9BGwClDynBl2eSkgM9+n+QtkTdiYYLzfZu7Q1qNtpRfkr1THW8sZ2smIeG31rYeej8/z3Vs9DA2Im2gfkIB9udRL/RX4iN92Fn/0QwuhW2brRnagUGfXRzzAtg7F1UsWKHy5zIVE5PIrRC266pW8NiTouxGXLaq77SzjS2guUL7pHHY13mw0volWzb6IRg6yU92hBy+ufL1vjOhMDm+3uHb7lU+Gc5QtvIJtTOBLYOvZ3QXs9pLzeqbjtuLIhpZ3dik3lNTutZckUBaslmKe8cjCBuVZmMdilGKBVTsg2mVmDQtk7GJjkqtrFt2dYmPjygunYXoa9j1za1rIE+UPphnr43p7/UetPABm6YFIU99f05XcWhw7zVLTcMPhQhsGJKJHewj5p8Zm0Y0w+T8XettTUPqkf1dm1cCwit0VLrBsZf5rRDu9mVM3mODFvVOhqGbiGj3Z+0u2GVlJ2RkoM2JuP8jBrbIShgJoNqmOtFHZ4H0Gej2fpQxxXe19Gn05rK8e9/IuuLgBnttGWbu/AYKvvI3UG/lD+Tc40xlZKGs+RTuIZOmUA/7P8PA3riOySDbrvYJm9L+BxPzohqeeODF3S4r13MsZ5VLbdtrRwc4Ra3t7ffNh7EDwZ9YISfYFbZyrYVjOvJQtHS9x9ffM1RebyC4BwLXttQORjLJW5pKj/a66Nz5lXMMc7kn4vvDqW16TR+By4ut5JE5nQNe3eOu2y572LlAsu+4M7s4/dU2b/GeVEZyQ4P4Gr+bQIOo3BzuIMmevxeJ7iWyc5XrvYshZh7CySGiQkO+zetgMYU+0bBO+0WTRc9WxrqswGiZ8CfEpwCmQihtTDInAtQT2rsR/3MsY6BgkpeixYO0pDui78Fl0CMVfoX6o8tVas7oUZe3QHNFLaoIx3p6V53+S+FX54HjRANg0tZcHB+xdqL156PfnIDRlKM4aGtTdSMd+v2xVcAc3mKuZ5jPHO1S7fvabNbuMvkIYiPMVcY6WPDDIynb0XH0jXDBkx8WLKPd9Id8lsPaBXjN/K7/kLPfypUrfXL7/LZ5tLQg1aRbP6/n/ZRgxytrsyyvc9duzTcGQz0d4oxCSZ2dadG+kuU/uOUvja1CqbRI33hR/Y1Sg/EJiXQXNJfet5a2Z7vF/Vr3UrXtUhftudnRfu9qnjbOKQv2/NnSt80WtkuxJ7+yvOH9qA/0F+L/Ss96g3Rs6U/8tpbd5LD37rhpV9rjntBFVvexqZl8GkzBmjDO3fCQzIjlaqFq5jf2Tw6mB/chNVt+amJUFyD2V/pGiw6GIBQMa7W4VHjpavw+ElUS8wefq9TjA9dtG3yBZrNe8xs80aBedj37k5jbdV1pZTL+IhKFJg3UD5R1p0N3mZ8Nm9sFphDijGuFVLUIeMTdNmfd1JMa9oGJmmX8Tm4WfbnPRSTPghs19V5fyZ8PkgxoTOxMlrn/Znw+QjFuErZ2phuyQfmyyr5fI5iYDrK2MWQ+PSYqXxeQeVjfWxr2Rnks0o+36R8NI8pS6dCPqvk82OK6awMSkeBfFbJ59cUo6TuoqmQTSaeEXPmbwTTiGBjq9q8PxM+D6IYFYKsuW+Q0Sr5PIliahlrZaNf8oH1YJV8LlKMizFZ6GLi02Om8vkAlY8OSimva+SzSj6M8rFCpbVZI59V8okU01pet0Yim0w82TylmK62LvLIkc+q+XNYjDXX0DLv8v5M52khU6+TLdnm/UE+w9r4nr8V94Stii5dUG+Df4E=
*/