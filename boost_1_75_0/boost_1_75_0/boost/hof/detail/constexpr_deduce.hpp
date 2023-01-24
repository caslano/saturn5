/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    constexpr_deduce.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_CONSTEXPR_DEDUCE_H
#define BOOST_HOF_GUARD_FUNCTION_CONSTEXPR_DEDUCE_H

#include <boost/hof/config.hpp>

#define BOOST_HOF_CONST_FOLD(x) (__builtin_constant_p(x) ? (x) : (x))

#ifndef BOOST_HOF_HAS_CONST_FOLD
#if defined(__GNUC__) && !defined (__clang__) && __GNUC__ == 4 && __GNUC_MINOR__ < 7
#define BOOST_HOF_HAS_CONST_FOLD 0
#elif defined(__clang__) || defined (__GNUC__)
#define BOOST_HOF_HAS_CONST_FOLD 1
#else
#define BOOST_HOF_HAS_CONST_FOLD 0
#endif
#endif


namespace boost { namespace hof {

namespace detail {

struct constexpr_deduce
{
    constexpr constexpr_deduce()
    {}
    template<class F>
    constexpr operator F() const
    {
        return F();
    }
};

template<class T>
struct constexpr_deduce_unique
{
    constexpr constexpr_deduce_unique()
    {}
#if BOOST_HOF_HAS_CONST_FOLD
    template<class F>
    constexpr operator const F&() const
    {
        static_assert(BOOST_HOF_IS_EMPTY(F), "Function or lambda expression must be empty");
        return BOOST_HOF_CONST_FOLD(reinterpret_cast<const F&>(static_const_var<T>()));
    }
#else
    template<class F>
    constexpr operator F() const
    {
        // static_assert(std::is_default_constructible<F>::value, "Function not default constructible");
        return F();
    }
#endif
};

}}} // namespace boost::hof

#define BOOST_HOF_DETAIL_CONSTEXPR_DEDUCE true ? boost::hof::detail::constexpr_deduce() :
#define BOOST_HOF_DETAIL_CONSTEXPR_DEDUCE_UNIQUE(T) true ? boost::hof::detail::constexpr_deduce_unique<T>() :

#ifdef _MSC_VER
#define BOOST_HOF_DETAIL_MSVC_CONSTEXPR_DEDUCE BOOST_HOF_DETAIL_CONSTEXPR_DEDUCE
#else
#define BOOST_HOF_DETAIL_MSVC_CONSTEXPR_DEDUCE
#endif

#endif

/* constexpr_deduce.hpp
JkqVC9b1juoA4fNPtPXvnDAzFIAI+J53e0GaoGnBTY9QChejsNt9Y4nxH8ugtO1UP0DO+fhHTBU2Lw+uvEI1+Heauk36ISYa3hVEdHXFsKfRe4U/edjJGsMfjax43dYoKSMj0EhfWUJK7srmAyhfXG3I8Cm2z2bCFgxwYNXKV6z7wmDlXnN8gEpSuILTcSqvUTt8u7ezYbasPn3YngkhbS1lvLs8fEG98tEZqA/YT0Dkgbv525GVzZKxRvHTBRPpzvydU66+242SBSgXxKr7W2r+9HfDgYx0gkNHtLW6B/SXxaIAx0+X/d60eF627e/Cjcs5vztska3eGuA3O3Vt2ndsmz/uuPuzGJXDbBrmnG0zJp7AL2pqSEaGhwG0cKeH7Qcir84Xdsj3Tk8l26EWHqgGpSzKFLoMZJXPJoKlsY2CJH7IUWxVkhkuvD+BYxw+FDYPzdp4TQox7MyekxAS6n23j//atl4BhNDX0g6zguGbTduNZqT44BaeMUmZFgHPAC1y/4KhMKa/ExE9DNlcBTPUfsy2odDiUwNnkgYiGsMQaNiHmmWDV6nSYsoiPDY3v7Om+r9vFYRncyvjnk+p1quihXYqjFImoneKuh0mJD00S5CGlP7tMHthCbW4xNpQY6E6N4LoXgTGDNxd6QVscC2YqBJlWOCsnIiTelsN3/AwxLAWSJSh7waeS5GPPMzyg7xpDRxQTem19Zrd
*/