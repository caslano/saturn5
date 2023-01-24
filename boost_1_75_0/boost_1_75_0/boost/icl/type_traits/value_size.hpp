/*-----------------------------------------------------------------------------+
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
Copyright (c) 1999-2006: Cortex Software GmbH, Kantstrasse 57, Berlin
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_VALUE_SIZE_HPP_JOFA_081004
#define BOOST_ICL_VALUE_SIZE_HPP_JOFA_081004

namespace boost{ namespace icl
{

template <typename Type>
Type abs(Type val) { return val < 0 ? -val : val; }

/// static class template for the size of a type's value
/** This function is needed to be able to order values according
    to their size. This is used to e.g. prefer simple test
    instances and to express this simplicity independent of the
    type of the test case.

    @author  Joachim Faulhaber
*/
template <class Type>
struct value_size
{
    /** The size of a value is used to be able to order values according to
        their simplicity */
    static std::size_t apply(const Type& val);
};


template<> inline std::size_t value_size<int>::apply(const int& value)
{ return abs(value); }

template<> inline std::size_t value_size<double>::apply(const double& value)
{ return static_cast<int>(abs(value)); }

template <typename Type>
inline std::size_t value_size<Type>::apply(const Type& value)
{ return icl::iterative_size(value); }



}} // namespace boost icl

#endif

/* value_size.hpp
sCbLnpbQaeyMAVQI1ykopwafSNYX4fsiwOo43MXciKtZgBuxcEpMSMj/O4CgOF574Mk+KAnxokupyl+IYYTsDPwfk/5i/RLmwyrnpIKZcTSdhJ3wOSShGgP8n4AnaVr475M9h08Jn6SsPy1WeOW7vRbrM7zQ7rcI3hiFN3wK55XFYYm9aShzyqJOGJ4tH7eIn8HVlp/l9nX7un3dvm5ft6/b1+3r9nX7un3dvm5ft6/b1x/wdaO0nXG1OPXI5F/wpwrTELQz4ll0eXbGviWunfF40+2M74vdddoZ0e63uQ5rY0UMwZ15ZVGryt+jUPab8P+UbMF/Jh5L2iJ3SEsWWrZ2iZ3wC21iPfDJfxXA07x8uya/nxdPSCvhPtlruILzqngR+vN1SEfEsNgGd/HXNu8J2S5x7SVlu9wPLcC4W7iV5A/FZqlh7oHvg9JPdFjc02SbpYCaV+faKfP6Ey9c28B2YSuOQJqC+l+RWMbaqV+EaI5dcwW0elychdacVCVUIM956JlxsSbxrCL7YQ4orsPINQO5xuT9u0ta65dnpdj4W1d6zLXKvn4VehtHwBH4zSW/CZ/nBa4fPQ91zEnaq0iqwradkLhB7qTbi0sz+6C2MbjHGMZoF3dD+UhfxzOsIDSjKmcNqHbcKKXH4ob3ZiVha86rHj0Nv7BfcC8C9idyh5ocO8gvJiRk42IlQH4Ofk9JHIx7cJnXUvEQ
*/