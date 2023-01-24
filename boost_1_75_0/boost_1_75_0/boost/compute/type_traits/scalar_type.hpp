//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_TYPE_TRAITS_SCALAR_TYPE_HPP
#define BOOST_COMPUTE_TYPE_TRAITS_SCALAR_TYPE_HPP

#include <boost/preprocessor/cat.hpp>

#include <boost/compute/types/fundamental.hpp>

namespace boost {
namespace compute {

/// Meta-function returning the scalar type for a vector type.
///
/// For example,
/// \code
/// scalar_type<float4_>::type == float
/// \endcode
template<class Vector>
struct scalar_type
{
    /// \internal_
    typedef void type;
};

/// \internal_
#define BOOST_COMPUTE_DECLARE_SCALAR_TYPE_FUNCTION(scalar) \
    template<> \
    struct scalar_type<BOOST_PP_CAT(scalar, _)> \
    { \
        typedef BOOST_PP_CAT(scalar, _) type; \
    };

/// \internal_
#define BOOST_COMPUTE_DECLARE_VECTOR_SCALAR_TYPE_FUNCTION(scalar, size) \
    template<> \
    struct scalar_type<BOOST_PP_CAT(BOOST_PP_CAT(scalar, size), _)> \
    { \
        typedef BOOST_PP_CAT(scalar, _) type; \
    };

/// \internal_
#define BOOST_COMPUTE_DECLARE_SCALAR_TYPE_FUNCTIONS(scalar) \
    BOOST_COMPUTE_DECLARE_SCALAR_TYPE_FUNCTION(scalar) \
    BOOST_COMPUTE_DECLARE_VECTOR_SCALAR_TYPE_FUNCTION(scalar, 2) \
    BOOST_COMPUTE_DECLARE_VECTOR_SCALAR_TYPE_FUNCTION(scalar, 4) \
    BOOST_COMPUTE_DECLARE_VECTOR_SCALAR_TYPE_FUNCTION(scalar, 8) \
    BOOST_COMPUTE_DECLARE_VECTOR_SCALAR_TYPE_FUNCTION(scalar, 16)

BOOST_COMPUTE_DECLARE_SCALAR_TYPE_FUNCTIONS(char)
BOOST_COMPUTE_DECLARE_SCALAR_TYPE_FUNCTIONS(uchar)
BOOST_COMPUTE_DECLARE_SCALAR_TYPE_FUNCTIONS(short)
BOOST_COMPUTE_DECLARE_SCALAR_TYPE_FUNCTIONS(ushort)
BOOST_COMPUTE_DECLARE_SCALAR_TYPE_FUNCTIONS(int)
BOOST_COMPUTE_DECLARE_SCALAR_TYPE_FUNCTIONS(uint)
BOOST_COMPUTE_DECLARE_SCALAR_TYPE_FUNCTIONS(long)
BOOST_COMPUTE_DECLARE_SCALAR_TYPE_FUNCTIONS(ulong)
BOOST_COMPUTE_DECLARE_SCALAR_TYPE_FUNCTIONS(float)
BOOST_COMPUTE_DECLARE_SCALAR_TYPE_FUNCTIONS(double)

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_TYPE_TRAITS_SCALAR_TYPE_HPP

/* scalar_type.hpp
nnDOuU6tcNpp9upZ/7SHdfU+veXDJ3GfvkeVn3KffnhSsE8PWdcTex7Qdx6X9z44ydN3VieD763md9j22Jbkd7qpUkyy/idZ1iOesyes9GqSD81+dHkpp7wfx9x3L6bLdipXJMt82YThy1wgzgPWN0N62Gr5P5IvH6A39rr447tUeTXpypcuuDxWI/bRlJ9R3+fnwlq/og7oqpC1Orwmcm/03nDCSRB71aX1gyHrwjBRz2hHJBb+ML1cqsHHE5xON2c3YCyGGoI8wYsh6039DuTrSe/9CfoZ7OBU2dkgOuORyHVqVBfUHsJt8If8I7jmgQbGNceoYjVGVWNjBa4ZCWKc/wSuiTQGcU0/45rfhw9GCtH3CNOcFypjmoSTtXcA04TbDKYBL/0f7J9tjb79cyXd/JX7UdoUX24MboquaH13YFPcXN4UDX01atG2/WrR+D61iOSVRSSvVK6T5xtZXnmZKvGTZZ1ciW4fNWNw3AwO4ytw69NmnUy3HqR1Uhey1oU3Ru6JPsTr5JjWT4VUylsn7vyuxuwIb1FJY8bo0+0X0eVGtw1+GvM3tGuWPO5efuJeXnMvf6CLdXcoeuAEOnvoZKaz91PFXqFe05t5nTTPuE6ep5/9i7tOfkWVpU1RNdJkcLq3Tvbrpd5yyYf8Im5opuXCC8m3al63XJReaPImruMvSQJoWnaRu2pO15GD0ULsvfhliXN0/Wyt
*/