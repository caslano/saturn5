/*=============================================================================
    Copyright (c) 2001-2009 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ADT_DETAIL_EXTENSION_HPP
#define BOOST_FUSION_ADAPTED_ADT_DETAIL_EXTENSION_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/fusion/support/as_const.hpp>
#include <boost/fusion/adapted/struct/detail/extension.hpp>

namespace boost { namespace fusion
{
    namespace detail
    {
        template <typename T, typename Dummy>
        struct get_identity
          : remove_const<typename remove_reference<T>::type>
        {};
    }

    namespace extension
    {
        // Overload as_const() to unwrap adt_attribute_proxy.
        template <typename T, int N, bool Const>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename adt_attribute_proxy<T, N, Const>::type as_const(const adt_attribute_proxy<T, N, Const>& proxy)
        {
            return proxy.get();
        }
    }
}}

#endif

/* extension.hpp
ZQYIx8A0H5anmcdXICawgys/ZDVuYDNczwoLrqdh3x4I0HWqro1D5Ylp49J8f6TBTpGkPjTdP1UFjxN9Fr5uWqrGcqka60vVTJY1U/q6arg7bRL3vkJ2K62nq6zYR+BQZ5OPQErdVhZrtZIPQFQugLRBIQDpBu2z91HqSXBxlQ4XVQKUgRb99jLU2ysO8ldEzQ2iiWegCbEXT75PF63+H9CzDz8zP6B6afD0FC3PqbwnymIJokFShNNwcSwcCemdgUn4rNRCt72Evitl7LA+Bnm3f2jibt0CxHFSEpLGHm+fZRm+ygxv2pq0ttUZ3oKpYGYt9s8uQAPMxKdqXXv/G4Br9xjUxQ6b6q5O81gp1DwG2+k/AQLhOGjSx15yWJYCeah6gEyvI0RbYHfanowrDWhcztAAtRQal0N7UFYbjasBOPqFkZIsRkFDZQ9xEV+TNgZc3dakTQhBmfUF0cRMw7Aeeol5WhzWThrWTrDrOSuHtYuHtVMOa6ccVoZv2M4M77CZUMasdiSz2mB6DuZ885HUFXxNRkqy1wMFhl6f2E+97gf72HPBve7nXqGW7LVgPzQJZbV73Qu9TkIy+o+osdDQ69OmXg9Tr4dFr1tqzfWw7PWwvgUFgtYVLISyi/Qah73uFRs1DXptSL2eyhfQjgdD1YPi4+PU7XHQE8huU30Vot940e9x6PdqT9ETxy0SZ8TeH8cmodA98hx2
*/