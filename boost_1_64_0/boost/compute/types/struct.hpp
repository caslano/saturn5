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
nVLi9CCQZvtnkD1KnGBt0I0j2zFIfHxIC4E7jRHPkrap0mdtdvxJpONTXvDa2J+Kcq1aZ4zlIc/o2vpuDMuHHYsU2ucfUD7bpq1N1XBiZwxYZx04d8w5DeGW29BYOz1Q6KyhcGFSHuf2B5xH37SOKaNJPJc84ucfK5TZDNhmXZtaO9GCzVNLp6EPDfPahc1GB17pRiabEf8fbT4P23S6qmvvK7AJF15lNl9X2OSqDkZVKtmM+P9o86PYJguK2WDDrGwXxvn8TGHTeOEaxbp8RvyRNgf/8c2c/0BT27o1hqCKfOSA/R7C+jQMdFVnaIz9GcJaFWpRt4LktQXY32Fsy2teaZcUj7F/Q9hQsTr+aAI1kmOv9keEpW3t68YmvWPs9RBWUMecNZRAqefYm2JsRVnbOJ/0zrAQe/xHXD9OMOVbS8nGMA26hjvsUz60CZLzHdE+sEpZMQ1dXt3Z6i5zn3KeMew3DTnnlPSm0pQb8rSV3WIfZY57UF2xqq6N7nDLT9ufjeXhDluUl5aE4LnwdPq1mXuWUTrwdja2hn48slvJVlglG7KzzRK8uPMSYS0PQoZakYPdOdiPIqxuKslUILsARfs2/lic2aka5qwnqwu721de8cBT5TlEX8H4ujvoSDrAl+cQXcb4JmhnAm0BX55D9KsiPcarVgL+QQ/E6UmOH+GD9Z4JZyP+IOKXryjxJzDeiVZIyhrAl+m/I8a3tbOGqRrwZfpPYnzdBbALFvE7U/xpjCcY33BmaG3oDL+I8QHjFZetMY2els/CyaWnFfl9YlE+zHjFRF8+c86Z2i3Kp1aC8tAAviyf5xXlI6QVoqkBX5bP64ry4VVrKteXT8SX5fPuonwaa6StKODL8vkoxtvgmGxa3pfPgxbK8vnMqD3otMQ/xZ86ebrEf6VIj9LcGOGm+T21OCrPyxjPtKKKNaLX/8BRff0K472qasGZnuo/feqKvbL9/zlf7xSu8k6ybj/v7hVXLOzBQAHaP8Iz3QhrHAP8Qom/I8YrK6Sv9RS/sDTWfxKnx9eeOa0AP9JPMF5Lqqzp9T/w5JNH+gPCc9WYltpqwI/T80SE91VdCVkDHJIza/84v55V1PB2SlheGKfneQjf1kKzRoYOHz+CY/zrEN5VLbOioQN+nP53YzxngQYnO3zsbYz1fxThleVO2maKj52Isf7PIHwQrJZCTAtoceGKMf4rCG+YdpXRnf6DK644NcZfxumpJW1lbQA/ag+/QviaJYINU/ypMj3pn7/keFvbSgXZAn6k/wTCO9rUTtimw8ev0bg874jwrZBONkYO+DntH+G91ZTZxgB+3P4RXjLmXFurKX55jv6A8LoW1AatAT/S/0SEr3zruVdT/Qun5uR3F5enE1Wj63rA743bP8IHZkTrBevxy3PaPy6finkWpJzil+ak591Yf+0ra5pmwO+N2z8uH2prZcK0PZw+OSc9n0F4I4xrAxUDfk77x+2nldzQelr+iw+6Yqz/Mm4/oVHeqmrAg/7Zea5/KWLGpFFtaxT0RtPlTlvpJLWNtfj7weY+qCBwt9pfsY5WS1H7YI7WcWqk42Shw1aUCyvo0TpOj3SEQkdFWUUrw47WsTjSsVvoaBohVd3wo3U8cKTjdYWOmvOgmyCO1vGgkY6PFjrSl8cY0R6tY2mk4yuFDtHWrdTGHa1jeaTjV0iHJSE412rb/pv20d+4lrWPv2EdXrc6mNb9Gx19I8vaR6Gjdb6pJfX/Rges5YIv+xv+lrDKp9YRJ8AgEgHdrfJEZJMTLmVrqVEwSdRNhCHuAsxB59xAWqm1dSL0xw+3K7u7s53jMI+B7BniKhYo5250+DCmU4hrQXxGuOJc1Fo=
*/