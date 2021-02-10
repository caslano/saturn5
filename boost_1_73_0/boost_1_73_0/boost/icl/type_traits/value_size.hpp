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
SKloh6GU/7GigQJDM59znMH7v8/pkNqf9jpi9R91OyxuvsXvVDF0zPEQ5LTnkej/p+shpb/Q97ZYauB8w742JnhY4TM+/WW/QsNy8YR2N76yKS4vNlQIXcaxpD2jNRo2rbZ+iXTh1e7qn3X0O1UAH8f1ap+7omhtVERWKtztSrIY2JSTjBkztgGvVg2XpHtqKl3Os6yd5mGXP3PGn0WWY0uh8NBCZgme7cBvyVxdrrZ5rDUa8mdku3kBjP+1KNT+6gTx9WB22LUHbii+YXFW+4/tArkaixJEfizquZoQqPBZDchKML7ahNC3IChqNtx2S1Y2uJRZin1iVZYdWzm5n1Y7f6tUluqblrDJZfdwSp3GlIMyi34g9mupeRURxNJ/4ISJeoJUrqvGX75OsAJTjctcteEy2YXGxJrz57wgqWigBkDCh0vqflYaj7I3+bKNZfZbRT14XJyeQPLekXqRy2KLA5yDZz5i23IJBbdIgEdVKFIXDtYD8FtqWcL+5B5UvqZkip0M3IlEqi3uZ7LvitsSBL6H7AYz/IB6fEgFBmLZ41twfwrpFCVGGtLmKETrOzGLgDPmFY1/UI838LzWNpRk/gTU9q+3b1hfzgqS1fnSDxbwfm457M3boidCBwnypCBiMAJAaSyLa+kj
*/