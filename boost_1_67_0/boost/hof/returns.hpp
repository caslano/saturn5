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