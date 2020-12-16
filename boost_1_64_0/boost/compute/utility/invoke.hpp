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
nw7/kvQosyDDYctM4dJPKpXO4N/Zr8OpdKb/m33cT1cZxVEaeJa7LHwLRpt6nWD1yt/YvEXx67ohBHtgoxR+YX6Yzla2NDjXWb1Nh1s6+68Op+VHzwj/8g4dbumyHtfhli4P7tLhWpeYozujxriY+ZHvhHUs2DsDZTP27+X+FOIod2MveeD1eKPftb2GfunekO43/3qq3x+C0qMOoWypfvZYPwxqXbzI7myf0HUBG0acrTcYrYPae2fTWwmXafMKg96+Ogac1eMvdjbhVGEIl/YxOlxXDN6M3d2Eq4pBuHhIh+uKQZvdzX02eWWQ+FkVi/OzvYWTx7XHLvIepupotGy+D7t5HfmhU9auFzxoHZXNd4DFV4uiCrys9Pz/s69GrwOuLEiM/mG+93LPjM/PRRJnSZnlyX3Et7q4SPF5uRmf2GPGF4s6ytLSC4L7j88vzPheZPElIvESJ6mD+8kflRfxpU2fMeNzaSIZ5X497L2cZfO+ceMcpMDdLCtvVVwGfpik95G3zrJOs/4cCC8o6twN6v8T38aFNV5WjJe7zf4szXd0f76j+7N78jj1Z9Zvj+t+22/Wxtveo4S13zb9tQqXcXf2VzpSB8766/HtOhz9FXeFdTjvr3cQLl1e9hAubfKacN6Pr+/V4bofp02d7eK+CDM/jbyqioVsyOHKplSs/LvH/ppv/qVnWFvNe6rHlB+xtXXyR62c9fX4HYA2LmcZ5nuQY52cxTXzPXTFac8rXt5G4X05OYdRvmnOyDMj8gpzJq8itYesndPQmP3pPnbaOwNEhZ8zwy+sIXwO4aqSKFylsWSmAYkRhX3BxCDF56RTo7KUfd9r/WFOu19r5qTw9zDGx9w0T50syfKB38GV5fPrs+uNA1K8SWHK1SJL47z0ilz0XuhtLFywpQZyN6z0XCd3isLzxXnp1HzzgvLnJ73NLvSsvZZfmHKlCPMw8aPYF+R8kcsYPhFZWolwgzyoQqcQvvRHvCy3dGI5rZeOoe0I4IuSyWci89w4d5JUyLnT8sbsCn2QLi2syC+LFYOUhS/5bdxvaRS7UVhlDvyeat/adhngF5fJ5yJy0tzPg0isnv/8whw55ZyXfpWXZXHWh+rurBlHKeq6SoLIT0UdFLbMs1izc5mgzrOgjgNBDoRtGfgAhwx8+CZhWUXi8onJU3IwXVinjM7NbryOvq5Z+qqyws9SNxa0nWvMAIbp61UmX4iwTMI6y2pBzqSWP7e53jiulEP8sHq/bZUjqhKnTr1Q+RFf7XeJfqcaXo6R7bztlaUX1p6fCFpJrm2QB9G5zfVLrTzAZ7wpX4u4ijLHc2MReP5pp53sxabepk25SsSOV2RlSmKxLSUamdiUKUXkJGleerk4fTofKnOWy8RRGWZulQg3qVoyTZmWeJlC1/cy3ymV6/2nO8r0wWaMYrp0RZ75QZ3lhTir2tXHj7VlD2GcYrKOyOqwLkJfpXl0qiUo4Avcqr+oqLPaqyNBvgBXLwx8kEqvx8pJ7rrlw5PJh8L1aegICuGfruAH20qe5OALnMkHIiliv06KSmwsX1iQEWzMXlgb1nbGd/AyF0XspWHmC3l8Itm22CHsTZtylcjThLZZalF5p2tbqJGZNGVk6SrHi+oyFx9LWoWDjODpFH4duoWXiDCpTw9LpzZlSlFkqRu6lfAKJsHTOcfTqd20CKIoEnHheMPSWePlyZMgzConF94ZS8L8hpoytcjyMCiSqBbO6U+WXlsM+r7Gy+QGmZcGUS4yP7SlsK/7XVPmRBhmdV7WqVik5Y1OYKHh3jC5T2dO4pZeXNFIeFF+Oni5b3JdlVmeRnGSC1qCL6xfOv/CRbkJZuVl7Xsj5vk=
*/