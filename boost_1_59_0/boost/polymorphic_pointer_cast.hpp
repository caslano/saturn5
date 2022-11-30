//  boost polymorphic_pointer_cast.hpp header file  ----------------------------------------------//
//  (C) Copyright Boris Rasin, 2014-2021.
//  (C) Copyright Antony Polukhin, 2014-2022.
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/conversion for Documentation.

#ifndef BOOST_CONVERSION_POLYMORPHIC_POINTER_CAST_HPP
#define BOOST_CONVERSION_POLYMORPHIC_POINTER_CAST_HPP

# include <boost/config.hpp>
# include <boost/assert.hpp>
# include <boost/pointer_cast.hpp>
# include <boost/throw_exception.hpp>
# include <boost/utility/declval.hpp>
# ifdef BOOST_NO_CXX11_DECLTYPE
#   include <boost/typeof/typeof.hpp>
# endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#   pragma once
#endif

namespace boost
{
//  See the documentation for descriptions of how to choose between
//  static_pointer_cast<>, dynamic_pointer_cast<>, polymorphic_pointer_cast<> and polymorphic_pointer_downcast<>

//  polymorphic_pointer_downcast  --------------------------------------------//

    //  BOOST_ASSERT() checked polymorphic downcast.  Crosscasts prohibited.
    //  Supports any type with static_pointer_cast/dynamic_pointer_cast functions:
    //  built-in pointers, std::shared_ptr, boost::shared_ptr, boost::intrusive_ptr, etc.

    //  WARNING: Because this cast uses BOOST_ASSERT(), it violates
    //  the One Definition Rule if used in multiple translation units
    //  where BOOST_DISABLE_ASSERTS, BOOST_ENABLE_ASSERT_HANDLER
    //  NDEBUG are defined inconsistently.

    //  Contributed by Boris Rasin

    namespace detail
    {
        template <typename Target, typename Source>
        struct dynamic_pointer_cast_result
        {
#ifdef BOOST_NO_CXX11_DECLTYPE
            BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested, dynamic_pointer_cast<Target>(boost::declval<Source>()))
            typedef typename nested::type type;
#else
            typedef decltype(dynamic_pointer_cast<Target>(boost::declval<Source>())) type;
#endif
        };
    }

    template <typename Target, typename Source>
    inline typename detail::dynamic_pointer_cast_result<Target, Source>::type
    polymorphic_pointer_downcast (const Source& x)
    {
        BOOST_ASSERT(dynamic_pointer_cast<Target> (x) == x);
        return static_pointer_cast<Target> (x);
    }

    template <typename Target, typename Source>
    inline typename detail::dynamic_pointer_cast_result<Target, Source>::type
    polymorphic_pointer_cast (const Source& x)
    {
        typename detail::dynamic_pointer_cast_result<Target, Source>::type tmp
            = dynamic_pointer_cast<Target> (x);
        if ( !tmp ) boost::throw_exception( std::bad_cast() );

        return tmp;
    }

} // namespace boost

#endif  // BOOST_CONVERSION_POLYMORPHIC_POINTER_CAST_HPP

/* polymorphic_pointer_cast.hpp
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
*/