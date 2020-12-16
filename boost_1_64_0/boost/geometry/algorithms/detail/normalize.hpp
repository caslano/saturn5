// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_NORMALIZE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_NORMALIZE_HPP


// For backward compatibility
#include <boost/geometry/strategies/normalize.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


template <typename GeometryIn, typename GeometryOut, typename Strategy>
inline void normalize(GeometryIn const& geometry_in, GeometryOut& geometry_out, Strategy const& )
{
    Strategy::apply(geometry_in, geometry_out);
}

template <typename GeometryOut, typename GeometryIn, typename Strategy>
inline GeometryOut return_normalized(GeometryIn const& geometry_in, Strategy const& strategy)
{
    GeometryOut geometry_out;
    detail::normalize(geometry_in, geometry_out, strategy);
    return geometry_out;
}


} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_NORMALIZE_HPP

/* normalize.hpp
2tvX09XaLaQqBGSvzJW3nWSSdrII9Szp9v3MRt6kmwOP/Q/Pc99bnqtMZfq5fPC5c2vL39l0GI6GD94htzR9mU7KX6pTTHkoeaHAOsXWZ86vVvl9rN9bHilvPuqUP8g6pYAyEjqueB95YPdswF4nhtsL9WxfL23T7UoHbJhJSdifXT0tYMqOGAu8mKcdqwO+2eP5Nh0p6um/uDrNWwmffEmWgT32JTefeXBlcB/Jy6KNraoMP9/2CuKYuPrMJsFCz529TnC+y0PJfBNhA9d7x59QtG8h/ISglfP7jzEvnJ2sDOKf4Pg4O+n3TYAfKMFP7b39j+Ij8JbPey59sUdF/75oYnDueNhEF8f01w3VcArb+7xEnL1UnBIVZwSFQ9ugAtowu/dEydmHwtLOH0DYwHWe/E7lyYdAa+Ca9s+KthS0BBe0w6wvyXn5fSfyWVnha/ROz0RH/4SiH6PonwB9OehnKvqxin4m6A8EvekvSvqDFD3hLf3BoH93Ao83rM1k3ENUXMLbuOMnBn3qV6pvXanwTyl8lY9HWdXnguM+Hn6k8dWKv8bXCLxJr8ZPg/+SL7H/Tp+o3t8JkVsr+BaFyJ1F+Kg9PImG1SuPbkzQ41h11sEDEPJueWfqQ3Q25GDUs3Oszd385cfoO+bZQSrfQTbX4PHvF0VD6u/VAYiS8wUvXM68EDmHCTk3eIXJOS9CzsdD5MwXcq4qUM4NEXIWhMipE3LuLlDO9RFyGkLkLNwDOQ9HyFkUIudIIefpAuX8PELOkhA5S4WcPxQo56UIOctC5CwXct4tUM74iPKzIkROs5Azq8DyMzZCzsoQOS1CTk2BchZGyFkdIudoIWdVgXKOi8ifNSFyjhVyugvMn8EIOceHyDlByNlaoJxtEXJODJGTEHJ2FChnZ4Sc1hA5bULOfQXK2RUhpyNETlLIebxAOa9FyFkXIqdTyPEK9LeKCL8+OUTOeiFneoFytkTI6QmR0yvkbMtDTvgcUoL6r900cknQyb6eZHavooKLfc4p9EXs28UTYZ99SK+o/kTTkpZViaa65Y2WsQQQR8cnPTGbn9IeD0Tk70CIPTYIezxaoB/NirD7YIicTULOwjzsLuXsiJDzqRA5pwk5dxYo5xcRdtscIufTe9BOdkbIOSNEzplCzmCBcjIRcs4KkXO2kHNWgXI2R8g5J0TOVln+CpRze4Sc80LknC/k7CpQTm+EnAtD5Fwk5GwpUM6pEXK2hcj5vJBzQYFybomQc3GInEuEnAcKlHN3hJxLQ+RcJuQ8VKCcpyPkXB4i5woh58UC5bwcIeeqEDlX70F/dm5E/XZtiJwdQs7iAuu3ZRFyrg+R8yUh54QC5dwZIefGEDk3yXKahxzM80acH+k194Uy752CdyyPNjVwz47eEwl4Me9DEHLd+o4F+uvXo8S6xBys7dwi9cljzqBK6oO0Ie32vvIe08UgmD+vfavm3zbQ1Z3pwkY3K0IDef1/jpgruX1idk/NN9W8vtblDqIdiTw14TttHmOvAHQtF7rWwxZfFbpWFNifkvOOHyqLmHcsKP3DYndPDM4PfR19K/nO3T0Ts/OHpg8n9biPwrAXz7d9XK3P6/MAiG+96oGJ6h3l4eod5b09q+el4Cnnv/Tdcd+FboTDeUI+k8i6DQcf0PGeYRMeURkMG31lOKbwtSo84HGY016E/f4nl6q9/pT2R1lfnntFmPMY5xKFPdUeab3f4WfIj4tD7KX3k/8C8ifwPB/vyVZxXRqkrZ8mWokfUHnxDHiNEn4xGt9ir3fo2sRvJmbtV4J0Di8Rbw2XuLQ+Dxm/myj3w4PWy56JfGFicH/K7xFvP6HbLZXB+fc/TQzOk/8=
*/