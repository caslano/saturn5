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
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
*/