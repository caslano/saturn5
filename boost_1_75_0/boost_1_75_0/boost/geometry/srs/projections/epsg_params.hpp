// Boost.Geometry

// Copyright (c) 2017, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_PROJECTIONS_EPSG_PARAMS_HPP
#define BOOST_GEOMETRY_SRS_PROJECTIONS_EPSG_PARAMS_HPP


#include <string>

#include <boost/geometry/srs/spheroid.hpp>


namespace boost { namespace geometry
{
    
namespace srs
{


struct epsg
{
    explicit epsg(int c)
        : code(c)
    {}

    int code;
};


template <int Code>
struct static_epsg
{
    static const int code = Code;
};


} // namespace srs


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_SRS_PROJECTIONS_EPSG_PARAMS_HPP

/* epsg_params.hpp
3+oLDmnCOWkKTw9fVALB+DXah2HhWDxtmGkPYwpKluqWXXx4sbk/XM3UqlxPVdA4AZqcL8SoMPaVrBlAwO3uIl/1C2mYDhmAb6SkaKv9MIETEtTpMUmZxCQ3HuWGWM5eoF+uHoqn0feytPntaazo9kRE7FnCnErVR7jqzCfQ7NZkLRph/+cRd4nZ+zuqRfxtaACn/pR2U4v/P0uWdhP+oUBvfamv3fJ1X+J0FMiau386iCz3yAlQAJ05N+6y6n2ZffhtByHmrg2Cjsxrgz6m8esEecEryysZIMg0/uXUkbKfBXFrhpV0XmrfwDQnuokgYEVz3nveG9knrV4myKSDiVsU1J7qP/rbpY2TT4ivN/RjBnaF5ly7whPuEiaO6axa7E5IhWLh16RKYU/RQ3Od7I4uiSh214SfcOJnkpJ0AJjUjz9Bq4m4yzFs8xJ5eMJJ6KlOGuEhxIatzHqzcOSR0h+dgQWOyreg8DlOHucekaqEtsi372P8J20kylbaOjZ8g9tKruVJZ35fSGnZh7sjRS4TCYCkXP2PDeI8PTX1tKLsJQnbWDuksVIwoh8uc7WyioCoT9kX5EPaRW0lLaXGAHniAt4Qe1xa3Esk3bcSIdHy5NMlDdvsCzDSiHoNThtWxtLBZgXlnQTjOPKWOOOOEZ+H05cArfkNMeYeXd5CMiKbZsebMg9/nE4ZYI8z/JspRuSOy59xfXB7zmT5
*/