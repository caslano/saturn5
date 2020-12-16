// Boost.Geometry

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014-2017.
// Modifications copyright (c) 2014-2017 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_VINCENTY_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_VINCENTY_HPP


#include <boost/geometry/strategies/geographic/side.hpp>


namespace boost { namespace geometry
{


namespace strategy { namespace side
{

/*!
\brief Check at which side of a segment a point lies
         left of segment (> 0), right of segment (< 0), on segment (0)
\ingroup strategies
\tparam Spheroid Reference model of coordinate system.
\tparam CalculationType \tparam_calculation
 */
template
<
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
class vincenty
    : public side::geographic<strategy::vincenty, Spheroid, CalculationType>
{
    typedef side::geographic<strategy::vincenty, Spheroid, CalculationType> base_t;

public:
    vincenty()
    {}

    explicit vincenty(Spheroid const& model)
        : base_t(model)
    {}
};

}} // namespace strategy::side


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_VINCENTY_HPP

/* side_vincenty.hpp
PtgPZ2B/TMABuBAHYioOxt04BPfjUIvpKJB6NNeZDg9Zb9pjQ+yArthRhqdsedZMOTK85Tuqw+mvOo5AJxyJzdEH2+Io7IOjcRyOwQgci0txHG7G8fgUTsBM9MWncSK+gpPwPZyMn+KU0vrxDNp2/QKkfoFSvyCpX7DUL0TqZ5D6hUr9pkn9wqR+4VK/6VK/GVK/CKnfTKlfpNQvWup3tZw8l8Y9st0pp4iXpH6ZFeR7NtAVD+BgzMKReBiDMBsj8CgmYQ4m4zO4BZ/FQ/gcPoMnMBefx/fxJF7CU/glvoDX8DT+jLlYifq9iK3wJfTBPByLr2EQnsFl+Dqm4VncgW+hfJ+nPJtmXZXptfw+z3yZ3vewOZ7DLngee+H76IMXMAA/wDC8iFH4IS7Ej3ArXsI9+DE+i5/gGfwUC7AAv8LPUanUZayKV9AZv8CmeFWm+2tsi9+iJxbio3gNe+N3qH3vlDwz9lWny/pzyH+gP0f8EVtjsUzfdRyIN3AUluAY/AXN791ES7n8n2P73/s+6nSiPhOGybI8LL8XJKG8qZ5zsTHOQzdMRE+cj+pHUGMAJmEELsTFuAhTcQmewqV4DZdhFca3HFvgCmyPK7EbJuN4XIXy7rc832VfpPN58Kekni9gGzxtMZyLDOehM9xxGe45dMcTKMcPeY5KHXWOH/SjDvcTNsZidMfr2Bdv4Aj8GQ1YgovwF+17euV5KBp01o+zUq+3sAW+jV3wHRyI+TgU35X5/h6ay82+Q7nvS7kXpNwPpNyLUu6HUu5HUu5/UNY7eW7JMpRyLde7l2V+vILN8FXsj69jML6BSfgmSnk8X7Rd3ttSXr6U966Ud17Ke1/KuyDl0R/PBq32K1bf5/ypTHeBrMefyXr8ObbHyzgEr+Bk/AKD8UsMw69wGV7FJ/Br3Inf4H78FrOwEA/hNTyO32Eefo+XsQi/xx+wNvX8CZ2wGJvideyNN1C2T/MzQp4dlt0+/yPz6ZKshwXYFj9DT/xc1kfGbZo+9MEvcCp+iaH4FU7Hqzgbv8ZN+A3uwm/xJSzEs/gdfo1Mi2xn8hwQu+hsZ8Nl/o/ADjjScvuU4Tx1husjw/XFR7Afat9XKMMZddbz0TJcoCzvIFnfg7EbhsjyNmAUhqJ8T5g8J2PfKuVafk9YipS7Vspdh23xSdkfrkcv3IBTcCOG4yZZf1JxF26W8dGvPP+S7fW2z9C4KcuXfaV6nKiK3bGabJ/Vte1TnlNhiM72lCb13ir13ib7u+3YF9PRH3eUlsezJdvb57NSr+dk+zwh2+cp2T5fkO3zdOn6wbMg28v5NanfGVnOr6N5uHQZrqPOcC/JcC9jO8wrXT945mJ7/QiX4WbJ/IiR9SNW1g+jrB9xsn7MRu26Qo6/83WOC1vkuJ6GHXA7dsd0Ob7vlOP5LozFDIzH3SjXBeZnGzzzKHtdsJt6NMFMWe/2YX/cjz54AKfhQZyFhzADD+NhzMaTeARfw6P4JubgTXxa2w7kOQRu0tkOWtOfM7aT/egj2AM9cDC2l/1nR6mPJyZiJ0zCzrgOu2jLS54R4Hyd5VWH/upgE2yAzbA3uuJUbI6x2ALjsaX2PdNyz77s9wuX/b5d6c/9Dv1FkxTpb7HU0/J734yy/OOwGc7GdjgH+2E8DsIE9MO5GICJGIfzMQEX4AJkVyTfpyj3trFYxmv5fYqLZbzLsDEuxxb4OIbgEzgHk3EprsJMXI2HMQVP4Vr8DNfhVdwg1wEb8XvchHJcknvWLCOd80Y/qc8UOb+diu0xAPtgIE7GIAzCYFyPBnwKQ/EtDMN3MRwLcTr+ijOwGeONwJY4E7tjlJyHR6Npecn9anxeZ3k9Lp8=
*/