// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_CORE_MUTABLE_RANGE_HPP
#define BOOST_GEOMETRY_CORE_MUTABLE_RANGE_HPP


#include <cstddef>

#include <boost/range/value_type.hpp>
#include <boost/type_traits/remove_reference.hpp>


namespace boost { namespace geometry
{


namespace traits
{

/*!
\brief Metafunction to define the argument passed to the three
    traits classes clear, push_back and resize
\ingroup mutable_range
 */
template <typename Range>
struct rvalue_type
{
    typedef typename boost::remove_reference<Range>::type& type;
};


/*!
\brief Traits class to clear a geometry
\ingroup mutable_range
 */
template <typename Range>
struct clear
{
    static inline void apply(typename rvalue_type<Range>::type range)
    {
        range.clear();
    }
};


/*!
\brief Traits class to append a point to a range (ring, linestring, multi*)
\ingroup mutable_range
 */
template <typename Range>
struct push_back
{
    typedef typename boost::range_value
        <
            typename boost::remove_reference<Range>::type
        >::type item_type;

    static inline void apply(typename rvalue_type<Range>::type range,
                 item_type const& item)
    {
        range.push_back(item);
    }
};


/*!
\brief Traits class to append a point to a range (ring, linestring, multi*)
\ingroup mutable_range
 */
template <typename Range>
struct resize
{
    static inline void apply(typename rvalue_type<Range>::type range,
                std::size_t new_size)
    {
        range.resize(new_size);
    }
};


} // namespace traits


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_CORE_MUTABLE_RANGE_HPP

/* mutable_range.hpp
bTjV386U6IQv6+xdpsbrK5DXqsrr/AR0DDlKKUM+4IQFR3UCdtYF2dFmDfvt+ZXl5Jc7qo4YQHiPyQs4YcWJIIx0ik17e/02VusANnfhgY74PUJXE8XlOYdWgu18kCNuQ3Dia4HJdgg6t/ERCSvcuVmLuNneDnGzwbULa+ZXza2cbS+1DbeSJ6k1H0H2+njv3oBvHVzCfGPUb/53fJKU9+00HzXr90Oht4EZR7wV4fPNrOdbpsUtL0PeaitscTX6XqsI/z6E7zQb5YQ4AvgYXJQ3QhBWQ87ccqob5nj4AHYQPQmhusywh0XBRQSm/XWT2Ijx1YoFWE6POeaDfl7tiBcj/MTj05MWPVdWiFtfXinWVVfJeSvCfwbhbzotCww6AZ0AnQBfAVoB2gh/BBOm242VaDdWiI1lSEntBvuvK+iDfBxzp893xIYXwO+lNR8NC+aX1k7Aa9Ng20LLvN/ycrtBYzPtM9j/zD7NET9AWND8Q7AG2oVwX+9JjriIMLBc89SwGjzvkBZ3GE+KWz1vw0LX/LrZzuE1qs+5qVlsuiz913Ky64vPccS3EF6geUdgJMdMQnzigiOWPxc2qeNGYM6qZWJVtUmsymE8NZQUNMvr22dCXHg2yguhrUXzCMKk3pvEppvRqLrUQhrm+nYVW2+vOODLcz9Pd8RXEAY0rwiM/MpQO3xKG3wKjUNmA2MdLDi9EeFlLaYfbiHY1xHeoXnbYBF65yYpcRPMD64a7lD6vlObuNPVtaL3yjrhXsaG4Y93Qffd0P0GcfFFGBMitLU26zUmxBWIKxBXIK5AXGGNK0KwJfjQGv6f+wTDVH/Yvuc+4ogfI3xDy2HCao/Hu1Lxc7287hmGUxuK9gxyUBsaGHOD3+wXHfFnhAe3mW0j2ugojvO7hL7xCO5kx44/HiPdcD9r4TOOuNlnHXHVlAU4sWic0LA42Ue8u70M665N2PpmSPdeCO9oN9oJK1yYsMb630t9p7XsFvjk5XIte6F9vtXoU6UxX+eIlyOMr9AyaphdxnBfkuaB2NY7Pu+I/QgfWBHtSwZxUR/uje1nv+SIHV9GHV1p6DMAv8YxxP/a/VYt4lZoK2/VS+3NXOfs6pLnAy1rPXaY7u/b36kf2oAs9jvbeEoMdCTEBMLFDm0nQViUprQqIZ6JcFnTRGBcF+15I356nBW0w6jdDPzOEc9BOLzKsJtFwO06iM4jDbcmxGMR3mLys8AdOcfY27SA2eEBcw3Z7UyIEYQrHn17M/paLeSbhQ3PY1geS1vwIgCzreM3bE+NrDEG3m3zZHouXdwqIT6G8PnVWtYgLOyf64wzyLYb833dW5KYeu4RCZ7zKDnC2AtzO7GwLiF2wrZya3zZTJhlD0UDbQrdPduEzaxPifXc7g53JcQXEebXhNrdReIa1te13gN6bqC9pHU5rMcBd3Pgbg7czXvXzcfVKetc5EitOfJ22Fab6Hqesq2GYcyjbj5D60Xz7QmxfEVCPHGt179NKVu24CLy0/wI159ec35kGc0Xl5YnxIcRvrHWKGfghBUnwjCWGeuuz6Oysfuq5yHPMXWy57YJ8RCE4XU6HQ1rsF8S8C/aBy/83RG3/IcjPk18eE0yh+cIjvJOcOwPWSROhGDW8SDdg2Ud6ruB9/zNUZ63wH6I9YYvt8JFCBa11br2dq33Rv10wPdoeequ+7Q3KEcj95GYcYCub3pMwvvZBh6QEOcRrnaZ5bDMAhcRWND3Nrhn1IvbkRQdh9T6fnicdOE+CfE+hKdiv5M/13xV1uVWzIu0EO6TCC8mPMsMXBQuQrx0++DPQQ2izUEQGwxeFrhZpiQ/7RFrFTdBH/8m6OPfZHDVvNm/Lz0=
*/