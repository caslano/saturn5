//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_TYPE_TRAITS_TYPE_DEFINITION_HPP
#define BOOST_COMPUTE_TYPE_TRAITS_TYPE_DEFINITION_HPP

#include <string>

namespace boost {
namespace compute {
namespace detail {

template<class T>
struct type_definition_trait
{
    static std::string value() { return std::string(); }
};

} // end detail namespace

/// Returns the OpenCL type definition for \c T.
///
/// \return a string containing the type definition for \c T
///
/// \see type_name<T>()
template<class T>
inline std::string type_definition()
{
    return detail::type_definition_trait<T>::value();
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_TYPE_TRAITS_TYPE_DEFINITION_HPP

/* type_definition.hpp
Ds3BHPCm4vQzqaNR7wzAbmWngV+YJwx5/P4uwqy7a9qm40/7ZR08T20BT2ZKcYkZ/sFmVN6A4z7k4VHCFmmtg7CxLRRG60/D5kWFwfZpcHb8PB8HvcKrQzd84O8CjRU79bhT+DTm8HH7syr/vtLrYAVp7A2MtTlqlQYOnTtzjrHyJQ7O2docismwY91JnPlV2kHASp36g66L258indBD+aoaED75aR0u32iVCMKvIPzESTP8VhN+bJrxDz6vw+XLsiq82euSdfkZlXdK23h3A+H9tEfMt4iA9dPXGPbogMk8sHc+gPXzYd6xva0wmqGoMKy1PqPbGXxjD8JUynjHYzvCKWbE8dIOCke7RH31w1TBEH4T4TJqhNPbdE24LJA5hiFcJmnOh3ZRONo9wr+7exAuU0C4tLFEOMX0WFPHqk2sL6/J5wCOnpxk/fMWzd+ULoGjzLJOJYb+ifXw85YeXqYwI59oKypdsi+hJPmY8GlKkwYago36OzRKGE/zrgpDmrBB/nRHmjc/SWmSTzfd/o00P6XTnDPq9eAohfP0/kthVnpXt1AY0oNuz+n0Tqh2z8v5a/n7kyrNBh9huv2k1U5f2kphPC/fH6Mw5AU2aZ/sKPsI8kLZ4GU/2+RjhJf9rF12FdYu+9mO9K6f7ad3vCO9T+j0jlvpfcJOT4W10/tEx3h/7qy1Rx3meZH5Dzwnb/aKzpjxnfBzGZ/rO+LMJ+uAJrZ4z8+cU3xMz+G909NTtVoVGnv5W4BLZEqRzG9AvtXE6YN/VN4i69vSPok5RTdn5vwLM2XigyftOYfyKjcF7/CO4Tx6jQ3fuXHG0xebiSnLh/eVGIcmG4qAM/VdNs6yDt7abpvHss78OHfx5lY3L24Y7eIgaxeZqF2nriLvgfdAqV2ffa+MUNkArZ1fUNdu+n39kzK8/hilc35zeWVj+eKMxPX9j+clZixCoNM7yk8tEDXpSgZ7/pi/gkPpURWZ7+OMd+D9JTbimN9tcHACbtwHMHF9mIi95X0GRiqmvBlrkjPsjFSWecq4l/Iw4Zh7Q+5nKlxtM0rVkpDcMlgx3uh7hHCKS++J6vB8P8K7jkkhv/So5hHN2Kvw30DhfEWoiwvOgTe2Ofa56c0OTpdN5/U3tXm2TefGgTbHPi999Qxvv1HtFl4ZPfB5x3ONLTeLLxRF6WWxW7nda7MVeym/ukg3W+aePWXekzn4MR5n6NRRnNXefdyTseNk/sRPj/LVvnbtSTLY26xHu3ibi/LSmXIhy+ycOrjNsgtvBWxpc7Q/X9x1gZ/prW1us2MkN1gR512bZ1vJGfu+3xzr5up8NvTB20zb2ny5jkYeb3bjzauh4J3d3smDGk37QZtHi+8mwidgP9jm0ZY1s00bb3O0WTF092oXR54yfY5mClRQ01ZvZwe319Iz3o1oc7meme3Mbs7nN6DAk4a/3bymXNj76eJtLPR0hOC9vJfz+rusG6v9jXDDn+o+zjP7Cvy6P8Q5dt5fsXFqd5ReX8/g3Z7gPOVJm2xeVHLGmy0P2zy0O3D2PMI5ZlvCHoPFadoR7Lj2c7yvG1ISZd5o449avB4rH9JbewPn6U/q4Cz/TcCxZwObjAMNVvj22MHe032zxbswP/AF0Mbad08e45zm1tBlg7PnLYzT2V5/3eY0V8lonwdxffdxxmNtFXYMb+UcMx6cmb7N4BhtFGcVBq6jh+zhtxsYWUz1TZ+Bnzto4rBQxfjwXxtng7DKxsBm8x1d3LbfhsknGI9ZqML2mXG4dSreu3hnF2eR7QHd7eTwOnjxkM2BpSnGvsff1c1Z29QPaPRVAb39pItP10PpNFJz0ceebHHRoNjc1uDBgtNIc+I=
*/