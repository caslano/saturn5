//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_TYPES_STRUCT_HPP
#define BOOST_COMPUTE_TYPES_STRUCT_HPP

#include <sstream>

#include <boost/static_assert.hpp>

#include <boost/preprocessor/expr_if.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/seq/fold_left.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/transform.hpp>

#include <boost/compute/type_traits/type_definition.hpp>
#include <boost/compute/type_traits/type_name.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/variadic_macros.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class Struct, class T>
inline std::string adapt_struct_insert_member(T Struct::*, const char *name)
{
    std::stringstream s;
    s << "    " << type_name<T>() << " " << name << ";\n";
    return s.str();
}


template<class Struct, class T, int N>
inline std::string adapt_struct_insert_member(T (Struct::*)[N], const char *name)
{
    std::stringstream s;
    s << "    " << type_name<T>() << " " << name << "[" << N << "]" << ";\n";
    return s.str();
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

/// \internal_
#define BOOST_COMPUTE_DETAIL_ADAPT_STRUCT_INSERT_MEMBER(r, type, member) \
    << ::boost::compute::detail::adapt_struct_insert_member( \
           &type::member, BOOST_PP_STRINGIZE(member) \
       )

/// \internal_
#define BOOST_COMPUTE_DETAIL_ADAPT_STRUCT_STREAM_MEMBER(r, data, i, elem) \
    BOOST_PP_EXPR_IF(i, << ", ") << data.elem

/// \internal_
#define BOOST_COMPUTE_DETAIL_STRUCT_MEMBER_SIZE(s, struct_, member_) \
    sizeof(((struct_ *)0)->member_)

/// \internal_
#define BOOST_COMPUTE_DETAIL_STRUCT_MEMBER_SIZE_ADD(s, x, y) (x+y)

/// \internal_
#define BOOST_COMPUTE_DETAIL_STRUCT_MEMBER_SIZE_SUM(struct_, members_) \
    BOOST_PP_SEQ_FOLD_LEFT( \
        BOOST_COMPUTE_DETAIL_STRUCT_MEMBER_SIZE_ADD, \
        0, \
        BOOST_PP_SEQ_TRANSFORM( \
            BOOST_COMPUTE_DETAIL_STRUCT_MEMBER_SIZE, struct_, members_ \
        ) \
    )

/// \internal_
///
/// Returns true if struct_ contains no internal padding bytes (i.e. it is
/// packed). members_ is a sequence of the names of the struct members.
#define BOOST_COMPUTE_DETAIL_STRUCT_IS_PACKED(struct_, members_) \
    (sizeof(struct_) == BOOST_COMPUTE_DETAIL_STRUCT_MEMBER_SIZE_SUM(struct_, members_))

/// The BOOST_COMPUTE_ADAPT_STRUCT() macro makes a C++ struct/class available
/// to OpenCL kernels.
///
/// \param type The C++ type.
/// \param name The OpenCL name.
/// \param members A tuple of the struct's members.
///
/// For example, to adapt a 2D particle struct with position (x, y) and
/// velocity (dx, dy):
/// \code
/// // c++ struct definition
/// struct Particle
/// {
///     float x, y;
///     float dx, dy;
/// };
///
/// // adapt struct for OpenCL
/// BOOST_COMPUTE_ADAPT_STRUCT(Particle, Particle, (x, y, dx, dy))
/// \endcode
///
/// After adapting the struct it can be used in Boost.Compute containers
/// and with Boost.Compute algorithms:
/// \code
/// // create vector of particles
/// boost::compute::vector<Particle> particles = ...
///
/// // function to compare particles by their x-coordinate
/// BOOST_COMPUTE_FUNCTION(bool, sort_by_x, (Particle a, Particle b),
/// {
///     return a.x < b.x;
/// });
///
/// // sort particles by their x-coordinate
/// boost::compute::sort(
///     particles.begin(), particles.end(), sort_by_x, queue
/// );
/// \endcode
///
/// Due to differences in struct padding between the host compiler and the
/// device compiler, the \c BOOST_COMPUTE_ADAPT_STRUCT() macro requires that
/// the adapted struct is packed (i.e. no padding bytes between members).
///
/// \see type_name()
#define BOOST_COMPUTE_ADAPT_STRUCT(type, name, members) \
    BOOST_STATIC_ASSERT_MSG( \
        BOOST_COMPUTE_DETAIL_STRUCT_IS_PACKED(type, BOOST_COMPUTE_PP_TUPLE_TO_SEQ(members)), \
        "BOOST_COMPUTE_ADAPT_STRUCT() does not support structs with internal padding." \
    ); \
    BOOST_COMPUTE_TYPE_NAME(type, name) \
    namespace boost { namespace compute { \
    template<> \
    inline std::string type_definition<type>() \
    { \
        std::stringstream declaration; \
        declaration << "typedef struct __attribute__((packed)) {\n" \
                    BOOST_PP_SEQ_FOR_EACH( \
                        BOOST_COMPUTE_DETAIL_ADAPT_STRUCT_INSERT_MEMBER, \
                        type, \
                        BOOST_COMPUTE_PP_TUPLE_TO_SEQ(members) \
                    ) \
                    << "} " << type_name<type>() << ";\n"; \
        return declaration.str(); \
    } \
    namespace detail { \
    template<> \
    struct inject_type_impl<type> \
    { \
        void operator()(meta_kernel &kernel) \
        { \
            kernel.add_type_declaration<type>(type_definition<type>()); \
        } \
    }; \
    inline meta_kernel& operator<<(meta_kernel &k, type s) \
    { \
        return k << "(" << #name << "){" \
               BOOST_PP_SEQ_FOR_EACH_I( \
                   BOOST_COMPUTE_DETAIL_ADAPT_STRUCT_STREAM_MEMBER, \
                   s, \
                   BOOST_COMPUTE_PP_TUPLE_TO_SEQ(members) \
               ) \
               << "}"; \
    } \
    }}}

#endif // BOOST_COMPUTE_TYPES_STRUCT_HPP

/* struct.hpp
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
*/