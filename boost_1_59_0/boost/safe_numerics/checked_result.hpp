#ifndef BOOST_NUMERIC_CHECKED_RESULT
#define BOOST_NUMERIC_CHECKED_RESULT

//  Copyright (c) 2012 Robert Ramey
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// contains operations for doing checked aritmetic on NATIVE
// C++ types.
#include <cassert>
#include <type_traits> // is_convertible
#include "exception.hpp"

namespace boost {
namespace safe_numerics {

template<typename R>
struct checked_result {
    const safe_numerics_error m_e;
    union contents {
        R m_r;
        char const * const m_msg;
        // contstructors for different types
        constexpr contents(const R & r) noexcept : m_r(r){}
        constexpr contents(char const * msg) noexcept : m_msg(msg) {}
        constexpr operator R () noexcept {
            return m_r;
        }
        constexpr operator char const * () noexcept {
            return m_msg;
        }
    };
    contents m_contents;

    // don't permit construction without initial value;
    checked_result() = delete;
    checked_result(const checked_result & r) = default;
    checked_result(checked_result && r) = default;
    
    constexpr /*explicit*/ checked_result(const R & r) noexcept :
        m_e(safe_numerics_error::success),
        m_contents{r}
    {}

    constexpr /*explicit*/ checked_result(
        const safe_numerics_error & e,
        const char * msg = ""
    )  noexcept :
        m_e(e),
        m_contents{msg}
    {
        assert(m_e != safe_numerics_error::success);
    }

    // permit construct from another checked result type
    template<typename T>
    constexpr /*explicit*/ checked_result(const checked_result<T> & t) noexcept :
        m_e(t.m_e)
    {
        static_assert(
            std::is_convertible<T, R>::value,
            "T must be convertible to R"
        );
        if(safe_numerics_error::success == t.m_e)
            m_contents.m_r = t.m_r;
        else
            m_contents.m_msg = t.m_msg;
    }

    constexpr bool exception() const {
        return m_e != safe_numerics_error::success;
    }

    // accesors
    constexpr operator R() const noexcept{
        // don't assert here.  Let the library catch these errors
        // assert(! exception());
        return m_contents.m_r;
    }
    
    constexpr operator safe_numerics_error () const noexcept{
        // note that this is a legitimate operation even when
        // the operation was successful - it will return success
        return m_e;
    }
    constexpr operator const char *() const noexcept{
        assert(exception());
        return m_contents.m_msg;
    }

    // disallow assignment
    checked_result & operator=(const checked_result &) = delete;
}; // checked_result

template <class R>
class make_checked_result {
public:
    template<safe_numerics_error E>
    constexpr static checked_result<R> invoke(
        char const * const & m
    ) noexcept {
        return checked_result<R>(E, m);
    }
};

} // safe_numerics
} // boost

#endif  // BOOST_NUMERIC_CHECKED_RESULT

/* checked_result.hpp
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
*/