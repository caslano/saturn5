/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   message.hpp
 * \author Andrey Semashev
 * \date   13.07.2012
 *
 * The header contains log message keyword declaration.
 */

#ifndef BOOST_LOG_EXPRESSIONS_MESSAGE_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_MESSAGE_HPP_INCLUDED_

#include <string>
#include <boost/mpl/vector.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/default_attribute_names.hpp>
#include <boost/log/expressions/keyword.hpp>
#include <boost/log/expressions/is_keyword_descriptor.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

namespace tag {

/*!
 * Generic log message attribute descriptor.
 */
struct message :
    public keyword_descriptor
{
    // The attribute value type here is not essential since message attributes are not intended to be created via the keyword
    typedef void attribute_type;

#if defined(BOOST_LOG_USE_CHAR) && defined(BOOST_LOG_USE_WCHAR_T)
    typedef mpl::vector2< std::string, std::wstring > value_type;
#elif defined(BOOST_LOG_USE_CHAR)
    typedef std::string value_type;
#elif defined(BOOST_LOG_USE_WCHAR_T)
    typedef std::wstring value_type;
#endif

    static attribute_name get_name() { return boost::log::aux::default_attribute_names::message(); }
};

#if defined(BOOST_LOG_USE_CHAR)
/*!
 * Narrow character log message attribute descriptor.
 */
struct smessage :
    public keyword_descriptor
{
    // The attribute value type here is not essential since message attributes are not intended to be created via the keyword
    typedef void attribute_type;
    typedef std::string value_type;

    static attribute_name get_name() { return boost::log::aux::default_attribute_names::message(); }
};
#endif

#if defined(BOOST_LOG_USE_WCHAR_T)
/*!
 * Wide character log message attribute descriptor.
 */
struct wmessage :
    public keyword_descriptor
{
    // The attribute value type here is not essential since message attributes are not intended to be created via the keyword
    typedef void attribute_type;
    typedef std::wstring value_type;

    static attribute_name get_name() { return boost::log::aux::default_attribute_names::message(); }
};
#endif

} // namespace tag

/*!
 * Generic message keyword type.
 */
typedef attribute_keyword< tag::message > message_type;
/*!
 * Generic message keyword.
 */
const message_type message = {};

#if defined(BOOST_LOG_USE_CHAR)
/*!
 * Narrow message keyword type.
 */
typedef attribute_keyword< tag::smessage > smessage_type;
/*!
 * Narrow message keyword.
 */
const smessage_type smessage = {};
#endif

#if defined(BOOST_LOG_USE_WCHAR_T)
/*!
 * Wide message keyword type.
 */
typedef attribute_keyword< tag::wmessage > wmessage_type;
/*!
 * Wide message keyword.
 */
const wmessage_type wmessage = {};
#endif

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXPRESSIONS_MESSAGE_HPP_INCLUDED_

/* message.hpp
/lK+pt8uaK+6hdpvL0LakbbsUWHliwKNKVfN/4AO3TBxP1VsQE7UProykfQjvUSnrcAK0WnTfQU1X6O0y2qnuXiU0TkL0pds0bSM0rSMRDrl0X870iK/Plo/D56g/aSjDG8Qt8Pc6quGY+zJSnxXpbca7yD9Cp7p62dC9N4G6bBVpnrqhiSRgP3OuOuvi/Zd2i+bNLj3KSbO6LNF8TuC+8DvSEJ0vyP4aZM9vw8CeWD65QOR+uUE137Z1N9Hk8Pt8D5m18/RoflWVbKyLLo8s0Z/8fQE9Z0dwu3Z/tDuO8PiVtOwFKvMxeeVXRhtuaYeYRz9beaArmX4OSLzp0gHu/074qjmX6VOnC42QIPia94Zrhc/M62J7nuuEmZof0+ZuPb3xq220/D+pkDu3yX9zRbE7r8rye9K0tPbXsPSuM63LbA3PcmtvcqexVxv5+h/bldmR9n3bh0d6IeyNJ/JH/I5KH+C+2BJs9YT1RVr1H0Gz0NSkArESxmkjpEy4KV99TBt9nRf1SuLawhY4mDKgwuu9UTD8OjajdbbP+7df2c133Pk/mLKQe/Ls3ndqZXWafRkTxB3ucxtttNnO91aZk2sf53HJem+vM9xrOlJaOV3YNmYcB18zX+eE+hbeHZQ38J1ebZcN3HS/ljLZNAxqnOk7eJC5BjKZIu/TAhOVEqlQJZVV5Vbks6OuPFYvu8sd10+DUPz+M3u4h7/ruWB2/A9xZexN6q7fr1xr+9BJs+X8jk4ssChx/wncXe81YNeqat53ywtq1tWW1Gj4Xf1ryERt6VWb/5diGi74X1FysywT07rv9/+PR/JJ/Le5JNpI+QH1yU/xK3XtBuTbv02U31XLSfiaezexhN20VgtJ2Mm1/d+yhubvgKY97jD2PfVcPjvcN+TVoTfesIOtr+tca5R38O0buXZxO2Sw8SZqhbxvXOV+OtttcHGNvEMqu/GYPABpIPq3T/flfoUIU6cOuokZ/L7GqhfPxR/g61U998CDdej/YgzDOlHXNuC+pF8iJe+rKR2ueM34XW5fyp6EfHWCPc9+k0YaeZ3xdRB0yeF9H1mbcrn4vdq6xhZzcSaW9PG6lfWONrL78Xdj6xRpH0aYr8L15NPh8iYvjnEo1Pj5aHrMXqpm3lpvt+vxPj4xm+m9DvMb1jkd9gx4+znz5Nw/f3rTJ7dT/vWxtTWbQuk0b+OkHCslWUri+ljte2a9hgo8yynnnBwORrd/Xjpa7W8tP8l7oE+IKQ+Vrro9CdS9/eM8+tP66uJ0er/4nr9qS468x/Z3/ahz2pYKXn+YWs68+O+uF7/h6p/HZofCS468++PIOyQOKLZH9S/vdNKXPFv2sMxefINju/yhqpl7m1Q3TvG26JP2zsmbYHfZp7JNfPMoHUdB1zSnG73f4UhaWalQLTpxW/gvfLwawVw+8XXCrzjokd/0KwVCE7nXpe1Ap/gPzU4nbpawIqqDqYWRr9eILXwi68X+DDK9QI743jHEz32T/c9kvTNS9Y2Tf/9ByUVZ/bfH0nvve36859L+NPmLMt6bfHB3OSaHvsvHXHoIcZqZV3Aby969vHP37/u4IXX9O5274Yz+VAceoeH6zf8dPxtr9160StbNv292vrzsIJI6xcirwv4meh6t0ya26Nh0LUbHswsvDZ5/2dvR17X8InEJ+vhNRs+7bv451ddMOtHVz5wz5OR9PYjr4O4UcL/3nfumHJ5Qvxnk5aN+n7VH0eVtF2ff7aEc2BD9reOe7Tq07Xvbr3/sq297xZ9aq7X7Fl55fstAx9/9vrJPXJfG/1Q29dfuK+ziLyewn29Q6R1HJHXoayLt6/fuuixhI5XfvLDPjue7zPollk=
*/