//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_TYPE_TRAITS_TYPE_NAME_HPP
#define BOOST_COMPUTE_TYPE_TRAITS_TYPE_NAME_HPP

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>

#include <boost/compute/types/fundamental.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class T>
struct type_name_trait;

/// \internal_
#define BOOST_COMPUTE_DEFINE_SCALAR_TYPE_NAME_FUNCTION(type) \
    template<> \
    struct type_name_trait<BOOST_PP_CAT(type, _)> \
    { \
        static const char* value() \
        { \
            return BOOST_PP_STRINGIZE(type); \
        } \
    };

/// \internal_
#define BOOST_COMPUTE_DEFINE_VECTOR_TYPE_NAME_FUNCTION(scalar, n) \
    template<> \
    struct type_name_trait<BOOST_PP_CAT(BOOST_PP_CAT(scalar, n), _)> \
    { \
        static const char* value() \
        { \
            return BOOST_PP_STRINGIZE(BOOST_PP_CAT(scalar, n)); \
        } \
    };

/// \internal_
#define BOOST_COMPUTE_DEFINE_TYPE_NAME_FUNCTIONS(scalar) \
    BOOST_COMPUTE_DEFINE_SCALAR_TYPE_NAME_FUNCTION(scalar) \
    BOOST_COMPUTE_DEFINE_VECTOR_TYPE_NAME_FUNCTION(scalar, 2) \
    BOOST_COMPUTE_DEFINE_VECTOR_TYPE_NAME_FUNCTION(scalar, 4) \
    BOOST_COMPUTE_DEFINE_VECTOR_TYPE_NAME_FUNCTION(scalar, 8) \
    BOOST_COMPUTE_DEFINE_VECTOR_TYPE_NAME_FUNCTION(scalar, 16)

BOOST_COMPUTE_DEFINE_TYPE_NAME_FUNCTIONS(char)
BOOST_COMPUTE_DEFINE_TYPE_NAME_FUNCTIONS(uchar)
BOOST_COMPUTE_DEFINE_TYPE_NAME_FUNCTIONS(short)
BOOST_COMPUTE_DEFINE_TYPE_NAME_FUNCTIONS(ushort)
BOOST_COMPUTE_DEFINE_TYPE_NAME_FUNCTIONS(int)
BOOST_COMPUTE_DEFINE_TYPE_NAME_FUNCTIONS(uint)
BOOST_COMPUTE_DEFINE_TYPE_NAME_FUNCTIONS(long)
BOOST_COMPUTE_DEFINE_TYPE_NAME_FUNCTIONS(ulong)
BOOST_COMPUTE_DEFINE_TYPE_NAME_FUNCTIONS(float)
BOOST_COMPUTE_DEFINE_TYPE_NAME_FUNCTIONS(double)

/// \internal_
#define BOOST_COMPUTE_DEFINE_BUILTIN_TYPE_NAME_FUNCTION(type) \
    template<> \
    struct type_name_trait<type> \
    { \
        static const char* value() \
        { \
            return #type; \
        } \
    };

BOOST_COMPUTE_DEFINE_BUILTIN_TYPE_NAME_FUNCTION(bool)
BOOST_COMPUTE_DEFINE_BUILTIN_TYPE_NAME_FUNCTION(char)
BOOST_COMPUTE_DEFINE_BUILTIN_TYPE_NAME_FUNCTION(void)

} // end detail namespace

/// Returns the OpenCL type name for the type \c T as a string.
///
/// \return a string containing the type name for \c T
///
/// For example:
/// \code
/// type_name<float>() == "float"
/// type_name<float4_>() == "float4"
/// \endcode
///
/// \see type_definition<T>()
template<class T>
inline const char* type_name()
{
    return detail::type_name_trait<T>::value();
}

} // end compute namespace
} // end boost namespace

/// Registers the OpenCL type for the C++ \p type to \p name.
///
/// For example, the following will allow Eigen's \c Vector2f type
/// to be used with Boost.Compute algorithms and containers as the
/// built-in \c float2 type.
/// \code
/// BOOST_COMPUTE_TYPE_NAME(Eigen::Vector2f, float2)
/// \endcode
///
/// This macro should be invoked in the global namespace.
///
/// \see type_name()
#define BOOST_COMPUTE_TYPE_NAME(type, name) \
    namespace boost { namespace compute { \
    template<> \
    inline const char* type_name<type>() \
    { \
        return #name; \
    }}}

#endif // BOOST_COMPUTE_TYPE_TRAITS_TYPE_NAME_HPP

/* type_name.hpp
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
*/