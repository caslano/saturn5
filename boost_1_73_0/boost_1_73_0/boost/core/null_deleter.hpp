/*
 *          Copyright Andrey Semashev 2007 - 2014.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   null_deleter.hpp
 * \author Andrey Semashev
 * \date   22.04.2007
 *
 * This header contains a \c null_deleter implementation. This is an empty
 * function object that receives a pointer and does nothing with it.
 * Such empty deletion strategy may be convenient, for example, when
 * constructing <tt>shared_ptr</tt>s that point to some object that should not be
 * deleted (i.e. a variable on the stack or some global singleton, like <tt>std::cout</tt>).
 */

#ifndef BOOST_CORE_NULL_DELETER_HPP
#define BOOST_CORE_NULL_DELETER_HPP

#include <boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

//! A function object that does nothing and can be used as an empty deleter for \c shared_ptr
struct null_deleter
{
    //! Function object result type
    typedef void result_type;
    /*!
     * Does nothing
     */
    template< typename T >
    void operator() (T*) const BOOST_NOEXCEPT {}
};

} // namespace boost

#endif // BOOST_CORE_NULL_DELETER_HPP

/* null_deleter.hpp
AGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfREVGQVVMVF9QUk9UT0NPTC4zVVQFAAG2SCRgrVZbb9s2FH7nrzjwXuxAlXtZsd5WTE3c1ahjGb40M2BAoCUq4iqRmkjFMdb9951DSbaTrmse6iCUSfHcPn7no/1ND85+2If55A6++4ncf4QffHZGs0r/KWL73wZR9AWaPzTc4PMBoYZwtPoSDeBBVl+g76yiNtYb+h5FDwi3oSRpGJLxJqKvuNJYtvbnutxX8jqz0D8fwJOXL1/AI3j6+OljDy64kiKHhRVqK6prD94kbuW3jN/e+ka89UBY4Ll/x+EykwaMTu2OVwLwey5joYxIgBtIhIkrucWJVGAzAanMBZyHs/V4+rsHu0zGWetnr2swma7zBDJ+I6ASsZA3jZuSVxZ0ih7QfyKNRZ+1lVr5GF6AFVVhWjeUBM+NBn7DZc63GI5byKwtzavhMK6rHCsZJjo2w7iDws9sca+qNWZT8D3o0oLVUBvhAe33oNCJTOmJEOFiWW9zaTLvmBYGVMlQV2BEnrfu0FQK05QgYNGi5dFOKDF7aelhtDIUbZfp4s5GhLV1lNaVwnAIC+5LNALvQa0SUbn9DoguSouyg/w7R3bMPQGtMCvo
*/