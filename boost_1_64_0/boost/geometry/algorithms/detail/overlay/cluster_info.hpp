// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2016 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_CLUSTER_INFO_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_CLUSTER_INFO_HPP


#include <set>
#include <boost/geometry/algorithms/detail/signed_size_type.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{


struct cluster_info
{
    std::set<signed_size_type> turn_indices;

    //! Number of open spaces (e.g. 2 for touch)
    std::size_t open_count;

    inline cluster_info()
        : open_count(0)
    {}
};


}} // namespace detail::overlay
#endif //DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_CLUSTER_INFO_HPP


/* cluster_info.hpp
x2TzdSOdPWgdZp9Y3jyrlz5CvCWPTzQvxVE3GqcI4zac/W2kDRX2iLs+MC9eDMkhzQ2+fpN5dce95t7dgfqpNZoBfN2jfGJefoM+hMRBZcVSC5bzQeXFxvpfawhfwF7fn0dNcyX7qd5WfxZ9Nnbr9PehAewFf5xfvDn1DT5M3Bu8pOb4uHW0OLHcY2pqL4XEY/ad38N/eP/ZtXTffMo2R0xFlgPEe+8GZM/OTGqlBludTZAjJ+Rgy/R/Vm0xywR9YN9L9uEzQuplbMun7dVztrONYqvIT0P2bas70MeS6szHWqiVHwrsZWD3TpM7m/2U2LGNOPlu419oC3nGqpWXt9ZjXPK67r2bxVB1HZsmD2QzT6s/f3rAejBbvZydmmGsMstHi66WD5cTW/VUXzP+n5vbJ+QQrZsbr2HG5G1jwhYU1o5+2lh0Av89ir/JKBYUA143ib8dyU/SwflV1eLZlE70IeozMutvbm2O9PdSKyjJ+EfOrSqK+YZHBQ9HnjvHfQTnzoX8v3l2PyC1CXo94IB/2YI0uSLd41BQCLzfkdZBKlGSa6slDB6SNGj44JHDeiad/3H4gLI9RiYP6FW2QmyF2PK9y94yvGL5CjdcPDe6SuWyw/t2H5bUq2yvpB4j+6Sc98z6l57ZK+mWhJT72tdLaDt48IDhCc3a+LFC5dgK5WMrXh8+0yN5UELDwcNHdKxSOWE0eg6Ije8YHxypmPKc2NgE/7vw3vOtSeg5bMyQEYMTuicND5PYs0fP2J7e3eO/3Z+EwU4mDh/RfURyz9ghvXp4R2TE+XeUbfRfe0v0f/FZF0STPKjngJG9kv6rj055ZnAkfYoM/ubTzz/3H5z+Z5t6/upLl8W1aBnfvE2bpont2sQn1mnZsmmj5k0cjWvTIrFDo+aVKl52RduGrePrxLW57EjzFolxnZrXadaoXmJ88waNmsdfdq5lo3p+O3+4TVyj1jUTCmvR5U262KZeycNH/LVhwY8pOndJjP9QjgkDknskJCQN6pM8KGl42QqJFRIKX2rFP/nef+V1Tobf0KFSdNlRvSqXv7F8dNkGw8P/Vx9jossOGjxgcJ/BlwmiTac2F0X518/EpvF1mifWaR6X2MwPF/vsdFNijGtUp7kfE+u1bpvYJr5eu9bxfxVzfMvW8fXqtA1LuF3zRvVaxMWHL7r4Y7O4XtFlWyAuLr5uuwbhcyk/dE6OLtuTOvyzJqRO26bN6te7oCD/wo2X7ihcr1pCy2GD+wzrPjC6fvKApOHRJUZXrVIyoUPyoF6DRw03749f6HOT5BHDE5rHt63fsU1ck4TKsVViK1x4UMLIgYX/8cPOP6FC+Yt3aU/52ArXl69SKbZ8wsiew0b8+w+pXOnG8EPOq8F//BjdUaOLypUqEBPyHamRBmmRDu3JJL3P//Q9o5IH/bXTbc2/jmSdLwh5Z4QnRyKEKFwD54II4yCm9lud+DZh25+YNOivpiT4l3xG7x58xm/flelX7yqY8q6sKe9yT4WKVS++7ornL5796Yr3V738fNgnX+tc5UCsjlBw/lisY0KxoPhlx250TCpjPC4dq5ZyXfRlx2o7VihC3AbH/jU/OnhYEqH8RiZ5fiWTXCl9qpvSp15J57vzm+MXu3lBBk1Sjg9PGnHhnsT+igJXOO/ei+f/pTFN6nmlMS14Rf1plvI+91xsa1h+LRzvR3aTq9L5FJm2Sjk2qeWlY23OH7NWeOlYu5RjP152rEPKsafjLh3r6thKx1rgwrGejv0SIXYJXTrWN+U64erFY8McU2YM8l52bHTKvXsjLx2bnPLe9Ze1+eGU6/542b0zHJsRKca97NhCx95xbPNlx5Y4ppQq7Lw=
*/