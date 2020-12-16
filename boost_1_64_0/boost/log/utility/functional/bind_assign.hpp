/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   bind_assign.hpp
 * \author Andrey Semashev
 * \date   30.03.2008
 *
 * This header contains a function object that assigns the received value to the bound object.
 * This is a lightweight alternative to what Boost.Phoenix and Boost.Lambda provides.
 */

#ifndef BOOST_LOG_UTILITY_FUNCTIONAL_BIND_ASSIGN_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_FUNCTIONAL_BIND_ASSIGN_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/utility/functional/bind.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

//! The function object that assigns its second operand to the first one
struct assign_fun
{
    typedef void result_type;

    template< typename LeftT, typename RightT >
    void operator() (LeftT& assignee, RightT const& val) const
    {
        assignee = val;
    }
};

template< typename AssigneeT >
BOOST_FORCEINLINE binder1st< assign_fun, AssigneeT& > bind_assign(AssigneeT& assignee)
{
    return binder1st< assign_fun, AssigneeT& >(assign_fun(), assignee);
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_FUNCTIONAL_BIND_ASSIGN_HPP_INCLUDED_

/* bind_assign.hpp
MVn6tUM75I0X7LOGywpc201Vwiz3BpdH0r72QCRdL13prdnl55rWYLGR1CbTmEy9rXtEajKfd67BVDsgIQtb10MZ9QW5zZlcYV+Ey1Ue2GO2DpMiKb64jW2ZJO5/cFn+6xqAdjhw+VroWNSHzi1z+tCxK74Pn+vXXrWa6/+E852HQ1/Gm8hzCOPUh1ifPMnuNtdfQ3468GOEelXy8uW122rT9j8YtL1XH4ozGvXV5K5gOMNwTXYF63BWmPPPI68FtK9DwBlXsOx4oZwsrZz1YBu7qd7RfZ3vNhf0no48P8G/T2vy1p2pyb8b9qX+3awv7TPB/TSZS6CNLXHcx31o+17vQ307kctU1mWa+fZxfK+R3rchok3XTVVclv/6V3EPoo71HkR4Pzo3Ne9HfbtHFPft9Q/DHoTpumkR2nWDLKxZsR03Sl3cMEZCJF037cS8yQRjrIzSfGOKFcZ4ui/FGMeQFyTiOi5PWd/PbM1UxOqit8OmvhRjZEbSOXZzX4oxxvfntnnwGVzT1rFe09aJorbxjzLAf1xugwfnmK1pz0N90tBfDgh7G4P6UIyRjfbPl7zcxp0FyM/EcUffJ1oN4LZ5sEtNfWI1ymgk1GlrPzq3r3fJvAvGHNN10GTU/20P/ZgzBHn9ZVVqIuCMon60v1zj5fg/tBH6S402+drAJn81sEn6QN5fHppuNhecAP2HoJ+8I/SXsVF8fZUg9JcWfWl/ycC8aZLstt90gpcvP3QPgD7L9el8Wifob3T/LGIQ7zMPOYzqUwH1iUQdAwVcPimK4oxOfWmfmRJF956W8TIDH55b07rnjf50T+fd/rQerQYzmcEPjzLDF8/juuFHHnfHuo1CWYeEMg/3p/iiN/JyJLsbTizrTfFFH8xbJtndYhYlXEf5YU81wMe0zmn9acwiCXkNxfW9Ju+h3yG28DLEFrjvvg/1bO4lxGX7U2yxGvM5BBv2x3zJQl2ih7CyQzZMhLnDFFeMHcDGHTdcMRj5cwmuqOBy5Q33sHiFA+IV/qbruAF0jl80gI49g4Zqbf+pFa7oEYXvOvS4Yjjj6cttO4DiirpRFFcMHEBxRQjLJ8RTuH7Kw2+Y4YomAyiuaD+AzknXuCz/jV3YnOSwGv+W4pnQuwW9HxxIzx1EDtNs82NNa6+xA6ldpg6k2GKDS+ax2qxvQwbS9Vf4QLoWuMLlKht2m62/bPieKsaAsD2ni/hnOG/PR5pg7CLAOnYxdxCt+/xBNNZdxeWGbvzSbP3lPM/2M85xHwhz/O/6UWzxAdanBEqeIMwnN5CfIclue9cBI3jbb9yFbe9t3fa3B9KxWB1E9xILuVxl41ozvHQD9X9BwBUfIO9uwBW3PfTjz5+x3Ali/FcrY1OoWsfLVOfkwRRXFA6muKL+SN4Wj7yv1lMMztTo9mQGU/vei7wgcb3gkvmo1b7gH7ANmwryfjBo10ouT3lklplPvzyIxi0+Rd5EwfZqNPfpTZ8yTKFYYYp+Q+h6ov8QukZaw+U22LQP1q2ma7wFaNM/Knr/XYht+LDUyQ1TTBtI10hHB/M5KUYo/zIvX96Ua4UpXhxMx5G3BtNxJGaU5mcTzNZ7BajfXkVvh6cGE0wB60e6Pnp6MN0XquBlBpa/qCrhqmKxPmowVLO3Vo8myPMS4zmj+VhT/gCMNaZ7yhnoK68JY82oQXSsWT7EeB/jYeSnEzxRwsuXy4fXhCd2D6G2OTyE9q8rLpmdGJ4wXL8moP6ewlgzEnnjZF+pi4AnVg+hexgRY/haZ/NeVYk31VsaRscF+zDaRw5xeaGbZ5vhiLOgdzz6xk6hj6QM1WLUQh/pOZj2kVLMmwJljxHKB9Owdtvc2Wo=
*/