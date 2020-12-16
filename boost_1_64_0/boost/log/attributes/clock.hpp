/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   clock.hpp
 * \author Andrey Semashev
 * \date   01.12.2007
 *
 * The header contains wall clock attribute implementation and typedefs.
 */

#ifndef BOOST_LOG_ATTRIBUTES_CLOCK_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTES_CLOCK_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/attribute.hpp>
#include <boost/log/attributes/attribute_value.hpp>
#include <boost/log/attributes/attribute_cast.hpp>
#include <boost/log/attributes/attribute_value_impl.hpp>
#include <boost/log/attributes/time_traits.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace attributes {

/*!
 * \brief A class of an attribute that makes an attribute value of the current date and time
 *
 * The attribute generates current time stamp as a value. The type of the attribute value
 * is determined with time traits passed to the class template as a template parameter.
 * The time traits provided by the library use \c boost::posix_time::ptime as the time type.
 *
 * Time traits also determine the way time is acquired. There are two types of time traits
 * provided by the library: \c utc_time_traits and \c local_time_traits. The first returns UTC time,
 * the second returns local time.
 */
template< typename TimeTraitsT >
class basic_clock :
    public attribute
{
public:
    //! Generated value type
    typedef typename TimeTraitsT::time_type value_type;

protected:
    //! Attribute factory implementation
    struct BOOST_SYMBOL_VISIBLE impl :
        public attribute::impl
    {
        attribute_value get_value()
        {
            typedef attribute_value_impl< value_type > result_value;
            return attribute_value(new result_value(TimeTraitsT::get_clock()));
        }
    };

public:
    /*!
     * Default constructor
     */
    basic_clock() : attribute(new impl())
    {
    }
    /*!
     * Constructor for casting support
     */
    explicit basic_clock(cast_source const& source) : attribute(source.as< impl >())
    {
    }
};

//! Attribute that returns current UTC time
typedef basic_clock< utc_time_traits > utc_clock;
//! Attribute that returns current local time
typedef basic_clock< local_time_traits > local_clock;

} // namespace attributes

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_ATTRIBUTES_CLOCK_HPP_INCLUDED_

/* clock.hpp
knNV5VlnvJ4jzFP+Hgp4NiDIHb6hn8POyZiepcr2z/jl9a6Yz2xESbg9Vbg9Cbcyz8FCdD71U+YXXKtd9rBb6/fZx1XYdwR4+03cpJ9NU36sZE1vV332bFOVpqr6Oe1ZpTOSHi7B+N4I1mkfr8zfdJ0ydlue32VNMix7bZeo8A8G2POdKOozeO9TOs8EaD8s32yoDP+s7BOIT7RRWDapZtnoPJqq4jJflc14yaOL+H3KXWauiuTR7bQT8oTnwEr0u55tyFbkQywR9Yz3bCEJwS3DybAytJMDlfXzYMT7PNqY6/Rnlzv5tzd3ouXMWp5XqvqBGma63nidVV3Q2h3Q/bTFivBeuAw/jC4ObVK94lBZbG+Xen5VWbnLC2hAa5qGuN8jiX+EMtXV33jX1U+3MbHT7XO8ap8qID1HaKzsOwV8ZyQ47tvW7u11SephTWU/07GeVIODlH1UwE7jdpdnDIztZpqNI/5x3m3EKBzHqyp3c0hrEGkNcnpXosP4u6mL/435/oFTGHocd6ddVhAZOg/qdUWX9F8z3O6jtPsMandLyxnok3SeT1VuapDj443X1XoRrZNgW/Mi5vLuVty/q9w/i2svt/HiVrVlc8wfQb9+JI41MOaYX2n+Zw5rC5TOOXTylM6CArvOUK5pImrNwOYquo2xbsDd5rbJupK34VNiPhu/sjDLRubIe5Hnqnjen1z/vYjZrnK6+deuqJeYqbLRYyH5od7VoqPyUa7RxC+t4/1O/IrWIx9t8+kjyoT65QY6rPvErGt31RYz49OLPpvJae17/oA73S6uqvlD1oxc5/mD1vWUy/wSPG8hDl5zAsLimrBszw22JhRN31OYjdXpc362sq6YOdLYEqRxbMnSaJ338M7HvzQOaOt2vAJxIcuRZxIIS6fR+dkIdc5nGueXII3oOq551t+YUPY91LMLWXPk1a9Vg6uUzlz1ni0TMZ8VPIHeE22Yf6v22zY0kNTqfPS0c9E71cbz3CFP64y36VzUOhlFdWRNxVx91sX11w2F6bbro5xsba1nO7djgdEWmcggHNdDl1ORZwlxlntX05M2Sreleq/pUG745X+5aV3L91nuqu1/G4yL8S/dJxP5T+7VI+AJaKZ7vk63/Z5dp1vPl+9Xus+6HOtqCdKMrs/1+RFwjYQj3weRe+nC+9souE7pPOPyNY/cqOz3iB9y/4sX1rVSS3uaOnF6Hvu1ug41HO7h9bPLTcrfHS6ZV4qOSqeacxSaE55lvDTbUl8q3eX2zO/VeryezuvxRC86Ud9L77K3k5Zch3B9N/azidRcONwc/+R6gbSfj6KIr5/jYVAvz3joX93CjPTKOkzJAxnnxIz02/rI3TcWHQeeJZ+P9NJ10PFeea/vcQC3/te7I71KNA54tbO9Cf61s8SO8j7JhcBguA+3BZ40ZpntjKqYOY5mZt3nkqqfM35q6mLUiP/XIl8hTmkvcE677s8b9XY/Kx9iBLIKKNgpT7QfMg+Vc4v0uloVpyh4XuldM+qR2tXI58SgsG2hL8+fPPcDzVTYvzZuQu8JQq5HnpeV/u1yrKyLkb8h9dT/Z8sP+tnXn0pyO54tY3KePDeOc59DlRWfWbQsbrX1eW2Vro9+vo/jcxo95g5W9onqWb9D3uPe8dmNfg7QX9l3Jj0Bjs9zcO/8rFLi3lHZDzJ6Kx3M4HJlFqvXL85UfcW//9nxZdj1ZzgrytfZT7erM6QCn//+6Ki9le94a6YRUuPgpHk8q2tu6oflhy4bX//jzl+90GZ/5JR+E3+6s6JKv5Xy038rZRnCj3tKBG5FZsnf+5GJ8vc7SKbl72z5+0PkTsvfky1/T7H8nSN/n0fmWf7Otfw=
*/