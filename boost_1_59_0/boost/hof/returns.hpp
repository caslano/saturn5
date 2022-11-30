/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    returns.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_RETURNS_H
#define BOOST_HOF_GUARD_RETURNS_H

/// BOOST_HOF_RETURNS
/// ===========
/// 
/// Description
/// -----------
/// 
/// The `BOOST_HOF_RETURNS` macro defines the function as the expression
/// equivalence. It does this by deducing `noexcept` and the return type by
/// using a trailing `decltype`. Instead of repeating the expression for the
/// return type, `noexcept` clause and the function body, this macro will
/// reduce the code duplication from that.
/// 
/// Note: The expression used to deduce the return the type will also
/// constrain the template function and deduce `noexcept` as well, which is
/// different behaviour than using C++14's return type deduction.
/// 
/// Synopsis
/// --------
/// 
///     #define BOOST_HOF_RETURNS(...) 
/// 
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
/// 
///     template<class T, class U>
///     auto sum(T x, U y) BOOST_HOF_RETURNS(x+y);
/// 
///     int main() {
///         assert(3 == sum(1, 2));
///     }
/// 
/// 
/// Incomplete this
/// ---------------
/// 
/// Description
/// -----------
/// 
/// On some non-conformant compilers, such as gcc, the `this` variable cannot
/// be used inside the `BOOST_HOF_RETURNS` macro because it is considered an
/// incomplete type. So the following macros are provided to help workaround
/// the issue.
/// 
/// 
/// Synopsis
/// --------
/// 
///     // Declares the type of the `this` variable
///     #define BOOST_HOF_RETURNS_CLASS(...) 
///     // Used to refer to the `this` variable in the BOOST_HOF_RETURNS macro
///     #define BOOST_HOF_THIS
///     // Used to refer to the const `this` variable in the BOOST_HOF_RETURNS macro
///     #define BOOST_HOF_CONST_THIS
/// 
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
/// 
///     struct add_1
///     {
///         int a;
///         add_1() : a(1) {}
///         
///         BOOST_HOF_RETURNS_CLASS(add_1);
///         
///         template<class T>
///         auto operator()(T x) const 
///         BOOST_HOF_RETURNS(x+BOOST_HOF_CONST_THIS->a);
///     };
/// 
///     int main() {
///         assert(3 == add_1()(2));
///     }
/// 
/// 
/// Mangling overloads
/// ------------------
/// 
/// Description
/// -----------
/// 
/// On older compilers some operations done in the expressions cannot be
/// properly mangled. These macros help provide workarounds for these
/// operations on older compilers.
/// 
/// 
/// Synopsis
/// --------
/// 
///     // Explicitly defines the type for name mangling
///     #define BOOST_HOF_MANGLE_CAST(...) 
///     // C cast for name mangling
///     #define BOOST_HOF_RETURNS_C_CAST(...) 
///     // Reinterpret cast for name mangling
///     #define BOOST_HOF_RETURNS_REINTERPRET_CAST(...) 
///     // Static cast for name mangling
///     #define BOOST_HOF_RETURNS_STATIC_CAST(...) 
///     // Construction for name mangling
///     #define BOOST_HOF_RETURNS_CONSTRUCT(...) 
/// 


#include <boost/hof/config.hpp>
#include <utility>
#include <boost/hof/detail/forward.hpp>
#include <boost/hof/detail/noexcept.hpp>

#define BOOST_HOF_EAT(...)
#define BOOST_HOF_REM(...) __VA_ARGS__

#if BOOST_HOF_HAS_COMPLETE_DECLTYPE && BOOST_HOF_HAS_MANGLE_OVERLOAD
#ifdef _MSC_VER
// Since decltype can't be used in noexcept on MSVC, we can't check for noexcept
// move constructors.
#define BOOST_HOF_RETURNS_DEDUCE_NOEXCEPT(...) BOOST_HOF_NOEXCEPT(noexcept(__VA_ARGS__))
#else
#define BOOST_HOF_RETURNS_DEDUCE_NOEXCEPT(...) BOOST_HOF_NOEXCEPT(noexcept(static_cast<decltype(__VA_ARGS__)>(__VA_ARGS__)))
#endif
#define BOOST_HOF_RETURNS(...) \
BOOST_HOF_RETURNS_DEDUCE_NOEXCEPT(__VA_ARGS__) \
-> decltype(__VA_ARGS__) { return __VA_ARGS__; }
#define BOOST_HOF_THIS this
#define BOOST_HOF_CONST_THIS this
#define BOOST_HOF_RETURNS_CLASS(...) \
void fit_returns_class_check() \
{ \
    static_assert(std::is_same<__VA_ARGS__*, decltype(this)>::value, \
        "Returns class " #__VA_ARGS__ " type doesn't match"); \
}

#define BOOST_HOF_MANGLE_CAST(...) BOOST_HOF_REM

#define BOOST_HOF_RETURNS_C_CAST(...) (__VA_ARGS__) BOOST_HOF_REM
#define BOOST_HOF_RETURNS_REINTERPRET_CAST(...) reinterpret_cast<__VA_ARGS__>
#define BOOST_HOF_RETURNS_STATIC_CAST(...) static_cast<__VA_ARGS__>
#define BOOST_HOF_RETURNS_CONSTRUCT(...) __VA_ARGS__
#else
#include <boost/hof/detail/pp.hpp>

#define BOOST_HOF_RETURNS_RETURN(...) return BOOST_HOF_RETURNS_RETURN_X(BOOST_HOF_PP_WALL(__VA_ARGS__))
#define BOOST_HOF_RETURNS_RETURN_X(...) __VA_ARGS__

#ifdef _MSC_VER
// Since decltype can't be used in noexcept on MSVC, we can't check for noexcept
// move constructors.
#define BOOST_HOF_RETURNS_DEDUCE_NOEXCEPT(...) BOOST_HOF_NOEXCEPT(noexcept(BOOST_HOF_RETURNS_DECLTYPE_CONTEXT(__VA_ARGS__)))
#else
#define BOOST_HOF_RETURNS_DEDUCE_NOEXCEPT(...) BOOST_HOF_NOEXCEPT(noexcept(static_cast<decltype(BOOST_HOF_RETURNS_DECLTYPE_CONTEXT(__VA_ARGS__))>(BOOST_HOF_RETURNS_DECLTYPE_CONTEXT(__VA_ARGS__))))
#endif

#define BOOST_HOF_RETURNS_DECLTYPE(...) \
-> decltype(BOOST_HOF_RETURNS_DECLTYPE_CONTEXT(__VA_ARGS__))

#define BOOST_HOF_RETURNS_DECLTYPE_CONTEXT(...) BOOST_HOF_RETURNS_DECLTYPE_CONTEXT_X(BOOST_HOF_PP_WALL(__VA_ARGS__))
#define BOOST_HOF_RETURNS_DECLTYPE_CONTEXT_X(...) __VA_ARGS__

#define BOOST_HOF_RETURNS_THAT(...) BOOST_HOF_PP_IIF(BOOST_HOF_PP_IS_PAREN(BOOST_HOF_RETURNS_DECLTYPE_CONTEXT(())))(\
    (boost::hof::detail::check_this<__VA_ARGS__, decltype(this)>(), this), \
    std::declval<__VA_ARGS__>() \
)

#define BOOST_HOF_THIS BOOST_HOF_PP_RAIL(BOOST_HOF_RETURNS_THAT)(fit_this_type)
#define BOOST_HOF_CONST_THIS BOOST_HOF_PP_RAIL(BOOST_HOF_RETURNS_THAT)(fit_const_this_type)

#define BOOST_HOF_RETURNS_CLASS(...) typedef __VA_ARGS__* fit_this_type; typedef const __VA_ARGS__* fit_const_this_type

#define BOOST_HOF_RETURNS(...) \
BOOST_HOF_RETURNS_DEDUCE_NOEXCEPT(__VA_ARGS__) \
BOOST_HOF_RETURNS_DECLTYPE(__VA_ARGS__) \
{ BOOST_HOF_RETURNS_RETURN(__VA_ARGS__); }


namespace boost { namespace hof { namespace detail {
template<class Assumed, class T>
struct check_this
{
    static_assert(std::is_same<T, Assumed>::value, "Incorret BOOST_HOF_THIS or BOOST_HOF_CONST_THIS used.");
};

}}} // namespace boost::hof

#endif


#if BOOST_HOF_HAS_MANGLE_OVERLOAD

#define BOOST_HOF_MANGLE_CAST(...) BOOST_HOF_REM

#define BOOST_HOF_RETURNS_C_CAST(...) (__VA_ARGS__) BOOST_HOF_REM
#define BOOST_HOF_RETURNS_REINTERPRET_CAST(...) reinterpret_cast<__VA_ARGS__>
#define BOOST_HOF_RETURNS_STATIC_CAST(...) static_cast<__VA_ARGS__>
#define BOOST_HOF_RETURNS_CONSTRUCT(...) __VA_ARGS__

#else

#define BOOST_HOF_RETURNS_DERAIL_MANGLE_CAST(...) BOOST_HOF_PP_IIF(BOOST_HOF_PP_IS_PAREN(BOOST_HOF_RETURNS_DECLTYPE_CONTEXT(())))(\
    BOOST_HOF_REM, \
    std::declval<__VA_ARGS__>() BOOST_HOF_EAT \
)
#define BOOST_HOF_MANGLE_CAST BOOST_HOF_PP_RAIL(BOOST_HOF_RETURNS_DERAIL_MANGLE_CAST)


#define BOOST_HOF_RETURNS_DERAIL_C_CAST(...) BOOST_HOF_PP_IIF(BOOST_HOF_PP_IS_PAREN(BOOST_HOF_RETURNS_DECLTYPE_CONTEXT(())))(\
    (__VA_ARGS__) BOOST_HOF_REM, \
    std::declval<__VA_ARGS__>() BOOST_HOF_EAT \
)
#define BOOST_HOF_RETURNS_C_CAST BOOST_HOF_PP_RAIL(BOOST_HOF_RETURNS_DERAIL_C_CAST)


#define BOOST_HOF_RETURNS_DERAIL_REINTERPRET_CAST(...) BOOST_HOF_PP_IIF(BOOST_HOF_PP_IS_PAREN(BOOST_HOF_RETURNS_DECLTYPE_CONTEXT(())))(\
    reinterpret_cast<__VA_ARGS__>, \
    std::declval<__VA_ARGS__>() BOOST_HOF_EAT \
)
#define BOOST_HOF_RETURNS_REINTERPRET_CAST BOOST_HOF_PP_RAIL(BOOST_HOF_RETURNS_DERAIL_REINTERPRET_CAST)

#define BOOST_HOF_RETURNS_DERAIL_STATIC_CAST(...) BOOST_HOF_PP_IIF(BOOST_HOF_PP_IS_PAREN(BOOST_HOF_RETURNS_DECLTYPE_CONTEXT(())))(\
    static_cast<__VA_ARGS__>, \
    std::declval<__VA_ARGS__>() BOOST_HOF_EAT \
)
#define BOOST_HOF_RETURNS_STATIC_CAST BOOST_HOF_PP_RAIL(BOOST_HOF_RETURNS_DERAIL_STATIC_CAST)

#define BOOST_HOF_RETURNS_DERAIL_CONSTRUCT(...) BOOST_HOF_PP_IIF(BOOST_HOF_PP_IS_PAREN(BOOST_HOF_RETURNS_DECLTYPE_CONTEXT(())))(\
    __VA_ARGS__, \
    std::declval<__VA_ARGS__>() BOOST_HOF_EAT \
)
#define BOOST_HOF_RETURNS_CONSTRUCT BOOST_HOF_PP_RAIL(BOOST_HOF_RETURNS_DERAIL_CONSTRUCT)

#endif

#define BOOST_HOF_AUTO_FORWARD(...) BOOST_HOF_RETURNS_STATIC_CAST(decltype(__VA_ARGS__))(__VA_ARGS__)

#endif

/* returns.hpp
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
*/