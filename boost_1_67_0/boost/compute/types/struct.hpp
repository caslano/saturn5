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