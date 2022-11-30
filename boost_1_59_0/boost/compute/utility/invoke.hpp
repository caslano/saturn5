//---------------------------------------------------------------------------//
// Copyright (c) 2013-2015 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://kylelutz.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_UTILITY_INVOKE_HPP
#define BOOST_COMPUTE_UTILITY_INVOKE_HPP

#include <boost/preprocessor/enum.hpp>
#include <boost/preprocessor/repetition.hpp>

#include <boost/compute/config.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/container/detail/scalar.hpp>
#include <boost/compute/type_traits/result_of.hpp>

namespace boost {
namespace compute {

#define BOOST_COMPUTE_DETAIL_INVOKE_ARG(z, n, unused) \
    BOOST_PP_COMMA_IF(n) k.var<BOOST_PP_CAT(T, n)>("arg" BOOST_PP_STRINGIZE(n))

#define BOOST_COMPUTE_DETAIL_INVOKE_ADD_ARG(z, n, unused) \
    k.add_set_arg("arg" BOOST_PP_STRINGIZE(n), BOOST_PP_CAT(arg, n));

#define BOOST_COMPUTE_DETAIL_DEFINE_INVOKE(z, n, unused) \
template<class Function, BOOST_PP_ENUM_PARAMS(n, class T)> \
inline typename result_of<Function(BOOST_PP_ENUM_PARAMS(n, T))>::type \
invoke(const Function& function, command_queue& queue, BOOST_PP_ENUM_BINARY_PARAMS(n, const T, &arg)) \
{ \
    typedef typename result_of<Function(BOOST_PP_ENUM_PARAMS(n, T))>::type result_type; \
    detail::meta_kernel k("invoke"); \
    detail::scalar<result_type> result(queue.get_context()); \
    const size_t result_arg = k.add_arg<result_type *>(memory_object::global_memory, "result"); \
    BOOST_PP_REPEAT(n, BOOST_COMPUTE_DETAIL_INVOKE_ADD_ARG, ~) \
    k << "*result = " << function( \
        BOOST_PP_REPEAT(n, BOOST_COMPUTE_DETAIL_INVOKE_ARG, ~) \
    ) << ";"; \
    k.set_arg(result_arg, result.get_buffer()); \
    k.exec(queue); \
    return result.read(queue); \
}

BOOST_PP_REPEAT_FROM_TO(1, BOOST_COMPUTE_MAX_ARITY, BOOST_COMPUTE_DETAIL_DEFINE_INVOKE, ~)

#undef BOOST_COMPUTE_DETAIL_INVOKE_ARG
#undef BOOST_COMPUTE_DETAIL_INVOKE_ADD_ARG
#undef BOOST_COMPUTE_DETAIL_DEFINE_INVOKE

#ifdef BOOST_COMPUTE_DOXYGEN_INVOKED
/// Invokes \p function with \p args on \p queue.
///
/// For example, to invoke the builtin abs() function:
/// \code
/// int result = invoke(abs<int>(), queue, -10); // returns 10
/// \endcode
template<class Function, class... Args>
inline typename result_of<Function(Args...)>::type
invoke(const Function& function, command_queue& queue, const Args&... args);
#endif // BOOST_COMPUTE_DOXYGEN_INVOKED

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_UTILITY_INVOKE_HPP

/* invoke.hpp
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
*/