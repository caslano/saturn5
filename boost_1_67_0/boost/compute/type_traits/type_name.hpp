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