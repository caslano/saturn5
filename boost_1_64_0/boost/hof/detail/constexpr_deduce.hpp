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
o+9ZCkVXfFYqrmNqAEtVkwJs3pGIohSdXMwppAbzvvwJhRd6aO0vuwYvmh7GCH4m0+T5ikX5ADe7Kz621asyDr6SVgbtKsjG6UuosyB5xMvHlYEGydjcus+iSrJLH0DcY/RRGt0ILJXb7AGGkNxml9zL24yNAJeKGYC7NmAssWuK8JPQjgOE6LM+786qJW3115VWQ4RccRce1yyYmqs66VkXMyrfL+BT2z/Wrzu3KqIYeqCsxZeI8Vgq8un3oehEKFR+SW2OuHwJZWYeKYACkY87fmzeHX05IoiIKV6Q+/iUSh2tudKqjwKxDCyUTW9TbC6JGJx42uSvynyAZXfDAA6MtNRqEsMBXAzfu8m1FTJq/j8gtPcFfgz5v+8Z+h9KtpvFfxRP2Un2YMowB9IlmCTlP8tCZD7S/3wkQbIMKP8fJWeAMsL8SdAtltQR28BGQCIyq7Gpnj2Ab30axHHDja3Vy+uolMcORrqRSh64fuKKaqWUdxElEbFFz/IViR/8SAmOsWSZknSKOCnH/LnGNfBlEhRHEjp8TdkXLlPWlP0ji/zrIxb51x8mhtN+YqF/PWyhf1nq6/PVxHDAUt+DlvJbLOXfvstC/7KUv95Sfpal/CcPJYQZ1ftGOUA6M9tF9/YVw0KrwDNON86DfLveNdSQSnHBv9RC6aGpfxVUEy7TbMtwVt3sFM/jvj8DlbJUvP+ItDQJ7WRYry9nKdFFOAjWb1Ei2VI7WfJEv/tDkyeq+KFTHjKOFPZUF0wKXw3eaLHop6kDPRMqxAfu5PtlIYpLK+jkXQuoQqM24lo6AIsBlsA1sv2l3L5ry5lIGQ28RkcxlnIuel7qUz+L739QlpV/h0nZM7F8r2ccSgM+TNe5eOQhU6ofuLAPMPWSMlDAC/v/O983XZFlk31o/wYclR5xGxfJxlBfxiU5D3WSu/2XxGvfpfhZrexz/a5lie8zhA38/34r/q/Sgf8/acX/reXN/yL5QYU/qvQYvjTwp830l5+zrN+7f5AYXv+QhX78lcTw+dst9F9L+U++n6hPWn1z4nu1vDwxvCMxrCFsyH/dZ4WPmS7ufKJF+Oy4Wb1/LeVVe9QfS34xvsX6+KX+QtRHR/VGaVMCStCSxRHOzR8avDV0yrXy5mj2E5Me6YINy4bJ8hdJTPrVskYjZs+N1pi+t1pjlv7UGuNebY2Z9wBxwCluT1kjLvgy8ml39Edd3B8b/w/hv/MR/svhHvg94JFz90EBUMJqQh+bW5s9zwZAbbYsKK1awfu8e5vDW+p7kdW5JCij0REIqSP46yerJw4EUxF0IUjWTxxWcgd/qAzVgYzOsB2F7HBtt7IjvNpN+XEXN4rCeB3B4HKEzvbfUrXZfwzr8RbXE61XcSHSwweQA+ejvZH13exS3c1JC4SM59paoNi0MB64mlnZGW5m3D/BKGRNtV3gT8SJ8Nn+n6l+1j8nc3uXSMUq6DiOhOm+7PuUUEY6zmKSibjnemV3mjHVljqN8Sv7l99S89scPvbHWt6P5Zbzyne/Oq8U/C3yj4npO6zpPVS6at8q/3hfYvnyePs3j1mWr2pf2b951JKu2lfyj9Z01b56/1rTlf1AfSZzuqb7A30LtXnBDLdXbLrfJBNDEL4fYpnu/DWJxr+wOeb2A1jdChd4K+8SvowC+5wptvB+JOSd3SWS0q87LzBUtnBT4HpUf5NZfaNPOB9RqiaBcUY3OJNHZSIlsFcs+kbFwGszgjxcchnuE9Ou5TXAuSFj1koSWf2sFYn3wfXM//pW/H2+ABukXD7kKsKCRlRB0k2rob2os8/5dHHo2ybO/apkPi/fRoMqxVL3i/HfMezZQjyKUr1hIWYgPTo=
*/