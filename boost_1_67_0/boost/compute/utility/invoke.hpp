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