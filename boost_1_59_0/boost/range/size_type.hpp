// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_SIZE_TYPE_HPP
#define BOOST_RANGE_SIZE_TYPE_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/range/config.hpp>
#include <boost/range/difference_type.hpp>
#include <boost/range/concepts.hpp>
#include <boost/range/has_range_iterator.hpp>

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/make_unsigned.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <cstddef>
#include <utility>

namespace boost
{
    namespace detail
    {

        //////////////////////////////////////////////////////////////////////////
        // default
        //////////////////////////////////////////////////////////////////////////

        template<typename T>
        class has_size_type
        {
            typedef char no_type;
            struct yes_type { char dummy[2]; };

            template<typename C>
            static yes_type test(BOOST_DEDUCED_TYPENAME C::size_type x);

            template<typename C>
            static no_type test(...);

        public:
            static const bool value = sizeof(test<T>(0)) == sizeof(yes_type);
        };

        template<typename C, typename Enabler=void>
        struct range_size_
        {
            typedef BOOST_DEDUCED_TYPENAME make_unsigned<
                BOOST_DEDUCED_TYPENAME range_difference<C>::type
            >::type type;
        };

        template<typename C>
        struct range_size_<
            C,
            BOOST_DEDUCED_TYPENAME ::boost::enable_if<has_size_type<C>, void>::type
        >
        {
            typedef BOOST_DEDUCED_TYPENAME C::size_type type;
        };

        template<typename C, bool B = range_detail::has_type< range_iterator<C> >::value>
        struct range_size
        { };

        template<typename C>
        struct range_size<C, true>
          : range_size_<C>
        { };
    }

    template< class T >
    struct range_size :
        detail::range_size<T>
    { };

} // namespace boost



#endif

/* size_type.hpp
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
*/