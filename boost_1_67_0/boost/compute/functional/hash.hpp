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