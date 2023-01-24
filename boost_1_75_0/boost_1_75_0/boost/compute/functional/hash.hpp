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
VasoOTontjH1YuVtT5IccM415OlUiqJ62TtzAiH07PjS7HHyZ+zfm9sOEPOTdFso3xeHz8yC5Wq5zyemGv05p5H3/W6NrRZ4/G6cr6b4qQCMTRic3iHmS49EJpHPPBK5G72A1UIyRUccyzTUVgMZEtCkndgH6iZz+ZH5+XZVmPPRMzj+VpRF5cdKNd4XIkotsVsOGk6O+LtIxOiYGD2riko9qXm5J3OCPG2fk8yf34EzTTJ1sbgFvLxwusGqjSs++6TYr6XR7/eJzqUA7fYJtb/KiCbSREuv7rXCuTcQAL+VE4xZrfJFrnkSn8eoQlerBM8XvDdsHvZBF17ArwZhxpcXUA0vlOwIbN5vh3BwOyMOPgkkw/JHBx+OIwsXbuU/spWkQIM1vl8Za8+uXW4ew/rTy2kVM7dUyG7d+VG2/vbQ9Xyc7fp7zJSWkliWuvLLNy4/t/PFlcMbaak+6p1B7Ecj20b/52DTfDFbMxkq2yfNUpTmYx2XSyP+z0y3zHEa/5rqGbX5qBqZhcMKN6La5xpXp14gXtQT4ausehuH5gitytug+gqooUqm0/yCdoUZ6TYyF3l0VrQGpDO1GlIhgsvWrZ4o6/d/krVVrosey0u08FnHhe8Ozykl2W125tF/uNgnBL1GIMfIDnL2J3Ta3aDofVsyyPzPQYx7sWdp3VVIVlYYHTfpqJE5bIV2vz/e5Hv296yqSsoE4nYg
*/