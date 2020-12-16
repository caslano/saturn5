
#ifndef BOOST_CONTRACT_DETAIL_EXCEPTION_HPP_
#define BOOST_CONTRACT_DETAIL_EXCEPTION_HPP_

// Copyright (C) 2008-2019 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/config.hpp>
#include <exception>

namespace boost { namespace contract { namespace detail {

// Using this instead of std::uncaught_exception() because
// std::uncaught_exception will be removed in C++20.
inline bool uncaught_exception() BOOST_NOEXCEPT {
    // Alternatively, this could just return `boost::core::uncaught_exceptions()
    // > 0` but that emulates the exception count which is not needed by this
    // lib (the implementation below is simpler and could be faster).
    #ifdef __cpp_lib_uncaught_exceptions
        return std::uncaught_exceptions() > 0;
    #else
        return std::uncaught_exception();
    #endif
}

} } } // namespace

#endif // #include guard


/* exception.hpp
BHnHfPEIuv0Z6UP3P9+NhDnK8wfGwNNCe04B3LuFNKFl9vEXFPvfO2cKjZki713SPzNN/2h8k93G7nie0kCTv1tami+oHoA2YpllUIZ44jIvaRmay3JXTeHow+c08vkqjCOk9xr0M+Xtfy6M4HrHMky8/Ev4su/9EIzvWO4lfDyz9g5tE5fnMlweZbUPZOVgEwL0w7+VT8BBPr0T8LulLzcbF2f8CaJHwRbBfswL6MeJVAbfz/+ksR8nQb0qmxuLQSZE4y2Eo/qY8gDPym+id6jwOEHKpqZDGvr/LmiDjvvjzP3QAqLFd+Hg/moh5eHaVERpLDON0go70nyHmQ5tdfUnp9LPxOUrUXkJbaKr/LK8Zipc6Fv4LG2/tkHSx5lvP86nb9t/eXFu2dlS1uXbWHuuvN5VrTG6aB7LYDzXibLql75wfPOdP9OWu8y69w6FQ30IPw5kL98lEJ9/iL/Q1Od+CF90gl1DLQ16rwhwFG7nWrm0/y6zvlVSPugQhnM8J6A5H3Ck3xinWmi6+pDmCQbfwflenOBfbng40eA7OMdwAtncFbDe1QLc8WTh9aavLLwR4JcH0F9FcFjnuA7VkTi2WoDOzTKHkM7JBJ+f+xY/+5vgW3E41e+ugsLbNifgt5o6ihlWH+TyDACM4mN7E3Q4vrTRLx1mPr9b0pSP6xWnsZ+7sZ8V373eDPJzebYfTqE8WEMZx667pyoOrGFW778HccResTinQ1tYN4udcdwM3654mOwKTL9k7AzXn5a39ULTwZSmjqt3EM4yWUMnmphKURh/F4yCtyEYj88TIV4M8LDeeHEu3kakNwre4Aj07B20ONIbBW9TMB7/MPZAUscLxAPA9TuNfI1CZ0sAnuPF4m1DvkbBex+ss7XFuevAdrAX8D1b+hE9pDPR+yDgYn1aJ+J+SMaWsz/07ojy6vIwTizy+mGYCygfjPd8rspZcN5h7KTzTlA7kuH6zhKNE73Lhfj53scNveF8c99V1odzCrPfzNOEp39Xw99HFeB5lqwNWmjufn0G+uRp8979RSI7l2/tjmuNf+Tzgnut8YE1m/QzkkZapxsb5ktCy+UrLsZ+7pd+QxvsK1QGcbYH4Fwu8nPtQb37NaN3Cc74Vwi+axPiX2nwHZzf/hf8ZoP/TYPfLPhXC/4zBv8ag+/gfM5M8J1cEP86g09wxr+e8vG7p103vqNw6U8L/x7AmwPgNwL8mQD4zQB3PFn4Lag3in0eLw24v3Kr6dvTA/r2x2L3vx/8lbebdfkOY3veqfwJLAXy5lhUUK/uSxGHz1ihDcU45n6dgdfYePrCUzPQw2+hzxh6vxZ8B8PvHofAO333mXb/1rT7fq1DYJQP6y/5UYw9ofoP58ZDZmw1Gz4flv44TnyEziZ4hPLUJuBvNwH7mbONXnlMeD/b6JFCk36uxMClD0843J8zZ5s59tQJsG8F++ZpaFeS79yYeFKwVwWdzG1B+s+ZOUlwpr9b8AsNP381+IXqL6F85BlxzhacvwlNJwOkucfgOzjH0oc2Tgyw+18FuOPDwv8O8LMD4K8D3NVp4f808/nsAN/HPrO3oPHHc8fqhn8bWkF+FG+FL59HZF5g24vNmj2BcBFeaMb1RIKjfTuZ4nvp2H3N3AuYLPVSPvQL5VE+9gvBmc9DoW6XZ+U2ZQXc0zZr5ttW+GmXb32H6WL/h7QKCR99VDcXUV9Ny5XbNOWHcWzMWToXY2hMcW0ycRhKDI7aWqi7Z0K70qZds0SGW8yad5SRIcGZ1tGCHzbzazbgo59qjuBPMPjzAB99UW8X/LTh5xiDnxZ+ykCGWwLWwGONjC18AcAnBMAXAjwdQH+RjNdLII604Os=
*/