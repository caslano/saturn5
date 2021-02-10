// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2012 Bruno Lalande, Paris, France.
// Copyright (c) 2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_BARE_TYPE_HPP
#define BOOST_GEOMETRY_UTIL_BARE_TYPE_HPP


#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/remove_reference.hpp>


namespace boost { namespace geometry
{

namespace util
{

template <typename T>
struct bare_type
{
    typedef typename boost::remove_const
        <
            typename boost::remove_pointer
                <
                    typename boost::remove_reference
                        <
                            T
                        >::type
                >::type
        >::type type;
};


} // namespace util

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_UTIL_BARE_TYPE_HPP

/* bare_type.hpp
DrULEskuL5BDE/VOyUZ44PKSK/t7VaIUUHA4kEQ6LWnwuUGdmnZfG1Bjg7xRGKRG3lB9rQ9aAbsjObAcBacdMtJFYeI0KKLNavlFDoC3wsWTqtS7X73rUvwp5C/+WgoSrKxBfY8hmHkP2uFRj2w0uVSfGFKFYhUDdcmeaBwM4XKJo92QBq/9YwABryX+gfVTp2XVerVCQd5N6hu5VddwtNuYE/QTxwBNHeJwFOpG4V4utueVV4ojIbipATWWG5gVpuJ5JNBH58Ep7OAZj04taE0vNTVUcq3hVHofkCqaIPtkUcTEMnKaDRpMq2D+WJPx443SvhF3F3+zqVlXcb4IMTXgfZfaVo3fnXb6hPDrBDuWYNk1eAEVrC/GclsRasKCg+6qwuBU96hnRKB31TjMDJs7rkUBmYHR0kTo7h2RsX0Y23f7QeZbrf7k9lFxbbjEDXzDn7p2BWy/WrhhW0n8pWHAJTQK//7JfPhLhZ346z99wzXWY90wvlrcaDmewmmgq1hSQBPPeEL3iFnfHVngNWY9oyKLbP+TdIyCddCxdyScohtzCbEoYMRzo3ZlLdvFtZhBDKyfPTvkJCBvLLajcaTsLTYlyVcxV9KREcro4EBlA07UH3XBPm/812UsomoYFWjk5gDzW0LKmXCg
*/