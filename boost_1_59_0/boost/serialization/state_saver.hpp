#ifndef BOOST_SERIALIZATION_STATE_SAVER_HPP
#define BOOST_SERIALIZATION_STATE_SAVER_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// state_saver.hpp:

// (C) Copyright 2003-4 Pavel Vozenilek and Robert Ramey - http://www.rrsd.com.
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/serialization for updates, documentation, and revision history.

// Inspired by Daryle Walker's iostate_saver concept.  This saves the original
// value of a variable when a state_saver is constructed and restores
// upon destruction.  Useful for being sure that state is restored to
// variables upon exit from scope.


#include <boost/config.hpp>
#ifndef BOOST_NO_EXCEPTIONS
    #include <exception>
#endif

#include <boost/call_traits.hpp>
#include <boost/noncopyable.hpp>
#include <boost/type_traits/has_nothrow_copy.hpp>
#include <boost/core/no_exceptions_support.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>

namespace boost {
namespace serialization {

template<class T>
// T requirements:
//  - POD or object semantic (cannot be reference, function, ...)
//  - copy constructor
//  - operator = (no-throw one preferred)
class state_saver : private boost::noncopyable
{
private:
    const T previous_value;
    T & previous_ref;

    struct restore {
        static void invoke(T & previous_ref, const T & previous_value){
            previous_ref = previous_value; // won't throw
        }
    };

    struct restore_with_exception {
        static void invoke(T & previous_ref, const T & previous_value){
            BOOST_TRY{
                previous_ref = previous_value;
            }
            BOOST_CATCH(::std::exception &) {
                // we must ignore it - we are in destructor
            }
            BOOST_CATCH_END
        }
    };

public:
    state_saver(
        T & object
    ) :
        previous_value(object),
        previous_ref(object)
    {}

    ~state_saver() {
        #ifndef BOOST_NO_EXCEPTIONS
            typedef typename mpl::eval_if<
                has_nothrow_copy< T >,
                mpl::identity<restore>,
                mpl::identity<restore_with_exception>
            >::type typex;
            typex::invoke(previous_ref, previous_value);
        #else
            previous_ref = previous_value;
        #endif
    }

}; // state_saver<>

} // serialization
} // boost

#endif //BOOST_SERIALIZATION_STATE_SAVER_HPP

/* state_saver.hpp
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
*/