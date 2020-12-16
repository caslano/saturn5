//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_HASH_HPP
#define BOOST_COMPUTE_FUNCTIONAL_HASH_HPP

#include <boost/compute/function.hpp>
#include <boost/compute/types/fundamental.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class Key>
std::string make_hash_function_name()
{
    return std::string("boost_hash_") + type_name<Key>();
}

template<class Key>
inline std::string make_hash_function_source()
{
  std::stringstream source;
  source << "inline ulong " << make_hash_function_name<Key>()
         << "(const " << type_name<Key>() << " x)\n"
         << "{\n"
         // note we reinterpret the argument as a 32-bit uint and
         // then promote it to a 64-bit ulong for the result type
         << "    ulong a = as_uint(x);\n"
         << "    a = (a ^ 61) ^ (a >> 16);\n"
         << "    a = a + (a << 3);\n"
         << "    a = a ^ (a >> 4);\n"
         << "    a = a * 0x27d4eb2d;\n"
         << "    a = a ^ (a >> 15);\n"
         << "    return a;\n"
         << "}\n";
    return source.str();
}

template<class Key>
struct hash_impl
{
    typedef Key argument_type;
    typedef ulong_ result_type;

    hash_impl()
        : m_function("")
    {
        m_function = make_function_from_source<result_type(argument_type)>(
            make_hash_function_name<argument_type>(),
            make_hash_function_source<argument_type>()
        );
    }

    template<class Arg>
    invoked_function<result_type, boost::tuple<Arg> >
    operator()(const Arg &arg) const
    {
        return m_function(arg);
    }

    function<result_type(argument_type)> m_function;
};

} // end detail namespace

/// The hash function returns a hash value for the input value.
///
/// The return type is \c ulong_ (the OpenCL unsigned long type).
template<class Key> struct hash;

/// \internal_
template<> struct hash<int_> : detail::hash_impl<int_> { };

/// \internal_
template<> struct hash<uint_> : detail::hash_impl<uint_> { };

/// \internal_
template<> struct hash<float_> : detail::hash_impl<float_> { };

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_HASH_HPP

/* hash.hpp
gGBQLwU817i7v0045r4nxLgXFpbVJyqOry3Ho5hN4FWnFVzXPMGhzuc9nRSeb9B9qoUObVyq/t9LcKuWo1JviD2L7MOBB+UYdlkH6NMnRpxqhnJah9PaelLE883E47f+rmEc+kesKzZha9O4WF8sBxCZ64zvvyLC14nA/fHKGCetgbZsvkrgfTJMz0J5sEsLGeF6lZdZVzu+Nb3CXoauY5kjyW4XpxYo8Jr3A0C9rldxWmMT09Mn6Zx7qk2lE2M1u77FqTMWGd+iMzbGxyfGZ/R6fy/CXQEQs7ljcX9tm16bp9hmee4EcA7y98gLCf7JO3iTiPN7lMV7dKAhbMJHp3CaZ5f5zKT2GM3xz46gDHWDuxpzTKMDg/vw4afX3elmjrZ9rOF1qbdJbWKue5zG7Zpr86EW7y260SvetHrYUE45gPlMNMkbFHPLni3e+Ww+fDiXUyZdA31m+YO1KmBRkbVRF8OhYUanxB06BxJvPDzBcArVrrxfual5vgKnYRNZnAvdQ5ltXqQNVuaKlUy+gfP+iwjOXLEwMlinffQV9O+9ZBqkws4im5Fw5HFTKVv0wMgIhVSjfGQezXeJNNzxXtGRd61lHjj+Y3z/tJAvL1YZ4Ti3OSPxxS6lvYy0byXLt7zW766pu+UHCZxmdToW4XbMbhtzKJulJcHZvJnkUBvQnYuNEVqjCs7eUcOhdhqhJpM+s40bC447hkRZ6/e5kMHalXdYT7T1tmqLbkHCeIq8tHh/4DsXM3h/sCzmw1zqMvWQtb9kXIiY77eQZaXdJ2e/cQzdi8m8igeQnuvklTkq7hNeQnOCLkTbXzKJt3MRL3E34tDwIZlDm1xK494YaaOcKdzEX943nBDTGGP80hoPehC27GUsXkRvYewajrXJ88vGuL8TwPtDhuPjaa+iLSye9/ISh92fwCM/t8tZzqBYkXfHLe79TWGnXj7GS9u/es5RlLUe8Va6S31xTznCqUGpmSDbFh+sVykQtI558gqa4x2GOe6AxR/U2ehljB8oGSCBXl0go5HxrVtGOA1/xrNbGXydLKVM2H+zQub5US/qNK7D/gekDif9PUJ6nHQC8A9afNBfOsp4/iGFEzZCJOHHT77VhM/QMwtwTufY5grzQ4V/23qEwpW/SFP/VvvEf7LSQxR/lspULj8K8sYSunQ7hbvBjnZpTZ2dOBTndaQ1OjV651C2Ac7fNa7KtqUx5cuyOeExThbYjsYoyQzYrsLMu18+P3pkUZZ2gHEmcE6a8Wza4N5GRj/868KE07OK7tnQchhxH179IhZT5witf6vfnt4gu0fZcP+Jcevbl9/K58HxLrg9bw0MLx9A1ygMbpQ8N//e5+2eQSw3a13lZCypIRxfxlWsSf4W8bgyxOMYsKFM8+UbbTKtLvTGuQOHvCDbC2Sfz88tPIDlYvc8jD/AbY3MBax2PmC9cDiEvdcLBowMcnq2E++flKWlMkK2aoFHi9kFF2sFPrwBcy3Vh+3xjnPju3unVayjj8jfUCgcE8un+c0LK3x6tOUC+bj369B2mxGv3brrMbqyI9633Is4PjPiYM37LcUZO966U4vD/XB+ecTjYgXOjuWgSGKN923FSTtJijVeS/DDG6TSJqlf4yIWP1risMMSeLs1NX63NhXMdfZxyIjKC4Ufx3pxRKfFLcB+lgc6jSnTfxPYt/lOxKsCMcn23Iw43KAY/yTXzKkETtzziLD26F3vAXyP0rc4OWbw778b43S4yL7EF/Xps+TyvSWSAY05OcA5743sb1kW0HeUv+WY9jwOnZPkskwEXvY9y9NyEfJuRTwrG5z3dpLLxYT+TPG4S/ndqO9b3lA54fdTo9+wrEDfkiw=
*/