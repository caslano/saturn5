#ifndef BOOST_NUMERIC_EXCEPTION
#define BOOST_NUMERIC_EXCEPTION

//  Copyright (c) 2012 Robert Ramey
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// contains error indicators for results of doing checked
// arithmetic on native C++ types

#include <algorithm>
#include <system_error> // error_code, system_error
#include <string>
#include <cassert>
#include <cstdint> // std::uint8_t

// Using the system_error code facility.  This facility is more complex
// than meets the eye.  To fully understand what out intent here is,
// review http://blog.think-async.com/2010/04/system-error-support-in-c0x-part-5.html
// "Giving context-specific meaning to generic error codes"

namespace boost {
namespace safe_numerics {

// errors codes for safe numerics

// in spite of the similarity, this list is distinct from the exceptions
// listed in documentation for std::exception.

// note: Don't reorder these.  Code in the file checked_result_operations.hpp
// depends upon this order !!!
enum class safe_numerics_error : std::uint8_t {
    success = 0,
    positive_overflow_error,    // result is above representational maximum
    negative_overflow_error,    // result is below representational minimum
    domain_error,               // one operand is out of valid range
    range_error,                // result cannot be produced for this operation
    precision_overflow_error,   // result lost precision
    underflow_error,            // result is too small to be represented
    negative_value_shift,       // negative value in shift operator
    negative_shift,             // shift a negative value
    shift_too_large,            // l/r shift exceeds variable size
    uninitialized_value         // creating of uninitialized value
};

constexpr inline const char * literal_string(const safe_numerics_error & e){
    switch(e){
    case safe_numerics_error::success: return "success";
    case safe_numerics_error::positive_overflow_error: return "positive_overflow_error";
    case safe_numerics_error::negative_overflow_error: return "negative_overflow_error";
    case safe_numerics_error::domain_error: return "domain_error";
    case safe_numerics_error::range_error: return "range_error";
    case safe_numerics_error::precision_overflow_error: return "precision_overflow_error";
    case safe_numerics_error::underflow_error: return "underflow_error";
    case safe_numerics_error::negative_value_shift: return "negative_value_shift";
    case safe_numerics_error::negative_shift: return "negative_shift";
    case safe_numerics_error::shift_too_large: return "shift_too_large";
    case safe_numerics_error::uninitialized_value: return "uninitialized_value";
    default:
        assert(false); // should never arrive here
    }
}

const std::uint8_t safe_numerics_casting_error_count =
    static_cast<std::uint8_t>(safe_numerics_error::domain_error) + 1;

const std::uint8_t safe_numerics_error_count =
    static_cast<std::uint8_t>(safe_numerics_error::uninitialized_value) + 1;

} // safe_numerics
} // boost

namespace std {
    template <>
    struct is_error_code_enum<boost::safe_numerics::safe_numerics_error>
        : public true_type {};
} // std

namespace boost {
namespace safe_numerics {

const class : public std::error_category {
public:
    virtual const char* name() const noexcept{
        return "safe numerics error";
    }
    virtual std::string message(int ev) const {
        switch(static_cast<safe_numerics_error>(ev)){
        case safe_numerics_error::success:
            return "success";
        case safe_numerics_error::positive_overflow_error:
            return "positive overflow error";
        case safe_numerics_error::negative_overflow_error:
            return "negative overflow error";
        case safe_numerics_error::underflow_error:
            return "underflow error";
        case safe_numerics_error::range_error:
            return "range error";
        case safe_numerics_error::precision_overflow_error:
            return "precision_overflow_error";
        case safe_numerics_error::domain_error:
            return "domain error";
        case safe_numerics_error::negative_shift:
            return "negative shift";
        case safe_numerics_error::negative_value_shift:
            return "negative value shift";
        case safe_numerics_error::shift_too_large:
            return "shift too large";
        case safe_numerics_error::uninitialized_value:
            return "uninitialized value";
        default:
            assert(false);
        }
        return ""; // suppress bogus warning
    }
} safe_numerics_error_category {};

// constexpr - damn, can't use constexpr due to std::error_code
inline std::error_code make_error_code(const safe_numerics_error & e){
    return std::error_code(static_cast<int>(e), safe_numerics_error_category);
}

// actions for error_codes for safe numerics.  I've leveraged on
// error_condition in order to do this.  I'm not sure this is a good
// idea or not.

enum class safe_numerics_actions {
    no_action = 0,
    uninitialized_value,
    arithmetic_error,
    implementation_defined_behavior,
    undefined_behavior
};

} // safe_numerics
} // boost

namespace std {
    template <>
    struct is_error_condition_enum<boost::safe_numerics::safe_numerics_actions>
        : public true_type {};
} // std

namespace boost {
namespace safe_numerics {

const class : public std::error_category {
public:
    virtual const char* name() const noexcept {
        return "safe numerics error group";
    }
    virtual std::string message(int) const {
        return "safe numerics error group";
    }
    // return true if a given error code corresponds to a
    // given safe numeric action
    virtual bool equivalent(
        const std::error_code & code,
        int condition
    ) const noexcept {
        if(code.category() != safe_numerics_error_category)
            return false;
        switch (static_cast<safe_numerics_actions>(condition)){
        case safe_numerics_actions::no_action:
            return code == safe_numerics_error::success;
        case safe_numerics_actions::uninitialized_value:
            return code == safe_numerics_error::uninitialized_value;
        case safe_numerics_actions::arithmetic_error:
            return code == safe_numerics_error::positive_overflow_error
                || code == safe_numerics_error::negative_overflow_error
                || code == safe_numerics_error::underflow_error
                || code == safe_numerics_error::range_error
                || code == safe_numerics_error::domain_error;
        case safe_numerics_actions::implementation_defined_behavior:
            return code == safe_numerics_error::negative_value_shift
                || code == safe_numerics_error::negative_shift
                || code == safe_numerics_error::shift_too_large;
        case safe_numerics_actions::undefined_behavior:
            return false;
        default:
            ;
        }
        // should never arrive here
        assert(false);
        // suppress bogus warning
        return false; 
    }
} safe_numerics_actions_category {};

// the following function is used to "finish" implementation of conversion
// of safe_numerics_error to std::error_condition.  At least for now, this
// isn't being used and defining here it can lead duplicate symbol errors
// depending on the compiler.  So suppress it until further notice
#if 0
std::error_condition make_error_condition(const safe_numerics_error & e) {
    return std::error_condition(
        static_cast<int>(e),
        safe_numerics_error_category
    );
}
#endif

} // safe_numerics
} // boost

#endif // BOOST_NUMERIC_CHECKED_RESULT

/* exception.hpp
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
*/