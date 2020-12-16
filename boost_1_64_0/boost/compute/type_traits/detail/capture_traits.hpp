//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_TYPE_TRAITS_DETAIL_CAPTURE_TRAITS_HPP
#define BOOST_COMPUTE_TYPE_TRAITS_DETAIL_CAPTURE_TRAITS_HPP

#include <boost/compute/type_traits/type_name.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class T>
struct capture_traits
{
    static std::string type_name()
    {
        return ::boost::compute::type_name<T>();
    }
};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_TYPE_TRAITS_DETAIL_CAPTURE_TRAITS_HPP

/* capture_traits.hpp
B3lc2m/jyCTiuPwGi6MzCduEN3XgVjlfPmBx+hkFnj/e4MHFrnzWb7Xxdj6ffzvnIJ+wD7Pxdj6vPGFykE+0y/F3E/7/x8pz1liZ+U5SBvV9v0Vr31e5ZsZ3qkrrOC1rT63sZoy1zMJUc1Zp8gsRB3HuO6WrzBb40n1khe5e/03WoXo5kCaX6jvTf/viV2/U4YsS6C1phN+RrHCHdWAUoXSKuz/EsQwmDPz5rRInO3mvKsOZjzv5xwIyp4Ud/X/buDajN3zh+Hw8LHzHy8LigR0V4Z69qT+/EGEWOG5W/J9vk/6GY7AV6jv95Htl/jyKT3m/Pr98cWq2N7e83HzH78i2P+kDV9iUZBFOdfOUvmMSlF7lBzQiSTnj+142/Uq2A1c/5gWb4DGON2MU7vVs4zjGH9gdcVx3B9T/tV2E89zZ341zuzmn/U2gjNocfBPAWenkbF4w8zuyF5yLXfp4aR/HbX388yGO2/r46gTHMd429zAfIVz2mEu8HslG7K3SPnmt3w5mLsvXT7RFDbuPWai4peHN5RnJkPHivjRhOhySA/y/W0wcpj6y/fTTve5QuvReNOGD/Iy4g/DF80en5KU1yJwDRm/MDMJvIpzeiJFxNW1F5jFX+Uc6A5trYDwt2BgynMd7aEuDIS8o95cVRuFMLxg7JsYIN9IEZRDH49vBkemCgPvxt3c0OPQK2Wd2AltdNGRxLq30PjNz+cIFcezk6/8iPs4VDbmTs6//S/WRpp6fp/XA+nF1Gqvunrb9DtyWv9O+neDcgGj4vh8l3MTa7e3qVpujfV3D17qNt9vkFSHLKPOqY0ebvN2EH59Ewm807tUlTd7RflSeEU6Cpo+alxQmwxGbxNBvNIbsGXcLBfcDUyVO4ZYP/EnBPaqaxeeJqHZzJ4qDB7qbtXyJooQO1z6sdDU3Rc3fCL+FcPUUE8InP6LDqbka/KsIX+j7wtThd/vhUzMnj5sdDHj9bB+XKmc4fAxJ3ce6XhqS2RZvGHiTiHmPYs8WE1cgsHlgKCewm8BQpsE4tbXBoAe06zWF6bQ6xoqxbYQjvUH7xJvywKk7QO7auA7nQ8zAT+yuBselHOXnST2dfGnQXl/Zo3lor8adzX0a44eZwL8PnIIJVjzgVx7SOBvKjLcnH27wXmce8Y50SfsJpN/zi6QmGQTsBjD5rdJg8072LWAwPCUC8Ls2TrAR90TV4PTEmQLxtvUkMMq/kgN2FfHOzfY2ThCKNCeAkaEwfT94nic5fmrKwmuGS48NwAfz52iUxc/wx0eBs/gxHwHO4kdb/xtw1AWwegthrNzAXgUmdW3naSswVk/Ik43beQKOegJWjxGGemJj1Iga0y6iZZo+JUKSIXsr602TQ6OEUVj7u/6DLcBa36bJD1FalD8+X7qKcD3gGPm7C4zPl+pnEN6aLwXQgzVfAsbTQpkZbs+XGMbnSwqjcGseifkScHOAM+ZKwDvnSr/bAXwwV4KfIWBsgMF+4Af5Gq706rp2Hvwuv/42yckUxYc2auhQz285TnoCdpNjpF9gB5+24z0K7EoLm1bt4NI75TmUipM2j9VwifZxu5HpG9ojLjFtxIVvn57ncUwVDXP6UwZGxTLLzDAqllFmEzumEkSbksCIb/Zpoy2etbFjxve9hfF2vmcrcKZPrPkYzuqR+Ypuc6aBHxkDzuoTa2DgrC0A/3Mbp3pifr6Ao64G8teB8/rCmnU7cFYv2NcCzusUfosUTu2Hz8GfGadwptem04FT77I50+Bg7bmHcVr9+uZehm9eJO0YY8KjDzOcUKS/Z38La+Xx2qMGhw9b4Lz4RoPDhi7+Zi44bPgy3sp7zOSgqIjj+OMGzoYxY7w=
*/