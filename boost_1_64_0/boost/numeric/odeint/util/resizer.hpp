/*
 [auto_generated]
 boost/numeric/odeint/util/resizer.hpp

 [begin_description]
 Implementation of the resizers.
 [end_description]

 Copyright 2011-2012 Mario Mulansky
 Copyright 2011 Karsten Ahnert

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_UTIL_RESIZER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_UTIL_RESIZER_HPP_INCLUDED


#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/same_size.hpp>
#include <boost/numeric/odeint/util/resize.hpp>

namespace boost {
namespace numeric {
namespace odeint {

template< class ResizeWrappedState , class State >
bool adjust_size_by_resizeability( ResizeWrappedState &x , const State &y , boost::true_type )
{
    if ( !same_size( x.m_v , y ) )
    {
        resize( x.m_v , y );
        return true;
    }
    else
        return false;
}

template< class ResizeWrappedState , class State >
bool adjust_size_by_resizeability( ResizeWrappedState & /* x */ , const State & /* y */ , boost::false_type )
{
    return false;
}

struct always_resizer
{
    template< class State , class ResizeFunction >
    bool adjust_size( const State &x , ResizeFunction f )
    {
        return f( x );
    }
};


struct initially_resizer
{

    bool m_initialized;

    initially_resizer() : m_initialized( false )
    { }

    template< class State , class ResizeFunction >
    bool adjust_size( const State &x , ResizeFunction f )
    {
        if( !m_initialized )
        {
            m_initialized = true;
            return f( x );
        } else
            return false;
    }
};


struct never_resizer
{
    template< class State , class ResizeFunction >
    bool adjust_size( const State &/*x*/ , ResizeFunction /*f*/ )
    {
        return false;
    }
};


}
}
}

#endif // BOOST_NUMERIC_ODEINT_UTIL_RESIZER_HPP_INCLUDED

/* resizer.hpp
x02FpXIpOlFm09Nd7hjfh3Lrc/NBeeqtl0K8Arh9WB6YshIPduu54l2nRdXdjarufF5onbuHeXPOMu6XOir8ws+BX9cF/POPDb68rwzyup+BRN3YuTbKUBX7VVX0YFU458er4ovCq45IeHbC2xA8OjxyWYFtq24pe6V+GTtZ//IykXlHRxQ29ieHXvOE9HMbfl+PwE96QJ6tWqouiC4qR8+Y1JZWGLhYdwxtlqdT5dlUrQ6AjQOq1LuRU6fl3E6dFRmibi62PGQxSJdysXae1NBbnKEm4fEH2X9xh/B9X/D8Wbw/t6VlQS8wqPDgeKm+3bfSqnSwvLlKNqXs3YnujXca7uzezMPRs8AWYXI8+BgfJy8v726cqP43l9KBDl0e/Yew61zueC7U5Un+0EZ+LcG+4vF5PNXebNxnIy+rdVaa5/233sB6Uyyb+6DX+FhPNB9H+ucmpa+u0jPSH//lpb/TLP/1TH/nEeWHC8o/70tP/1yVfnL5Vfrjv2D6xn1xE6keaOp1VA80US+eOBMpWJV0/xJMsd2EH9JV+MI7OoVXSnHdvFZt1AInrgJY4A6mz5oZmWCFQlaRO5eY+cnXKnqEHSy4qabW0HJxIZzlUdJF4xSmVC6+cb25fSaBpcRprjwpGCt6h7oeDVpQEpzfXW44+0QKIpeLp68xztyDX4pBPWvm8cm6mPqZDrxymkO3HBmV5yHRKn59plMqPPih0aQz3bAW6D9kk8KUzVnqq9nRyHUZoUYI3li4sFMEog/oGs2HDFJa4IKS0DZ7qJEaGeb9DvUMp9lqDjzdWyZ+vlKO6qZiqcI/runAUN2gJtJTEPD7P+gyoFJhCxo4K9r0ps8/IGIu9T2ggJf7/JEbMqRCJ6nqUU24I8VXvi3x38h8OzUy7dPOjvndYBcHK5WGVVgmijORK21oSmxm/n2lJELNmvm5GdM+sxkxKrE7qewszW6e589uQ0Weol1oAveKTdfEhNQ5tNQlj+NMf24ir1CwwguIDZ0aucy8byGtWNKnPpR1Fl7AW6ibShwJ9fx5uY3rc+hh1a2Nhp0yE+EyUzYbDODzIkuGkXpX5IksyZGG/MiSXGko1JewS1EesCgnsqTdQsfcxqYij9w5FuWrX6H65ahfruWYbyKK54ey6PH8rLYY+XnIYuRnjcXIzxMJ+Wn4Z+dHqrUJnqb93GxmrcYK02XqxMVl3zK4R41ynlL3KgpHqnGLS2z9lXOS3yf62A2fwOI5oYV97MHeCP6GlY5sSHbmDBBJ0yPjPpsOu24p9xkXRi3qMX1WvU3OsKH2jqCd3m1pbqjE2hzLWXVCzp7RMPlos+Hs165h7wTVRGZ2yHRgdCruUK05FndJQtyFiGvEsok3NTUMZEmOOr0f91Oupi/08T56Gg9+KZWoi9pRYxl6uo7qCLwP3x6hMdbF9uxXIS7u5YTonlxepltDez8LNVvDVnF3ncRcUE/9Is5aNq/VhVj9zga86ayxwE9DO6JEsDbPmnk8M428To5IjTg/xWy7k2iXbmNspluq67nCPl1QoDjWhjcASd3cjm2kax4lBIFu5Wzbf5vdjd/H/KEGxDjZNdxHu7SL64HaFjn0sJrr1Y6olFpHKOMzCvt7n+v2hkhOLR1SPqTC5d7iSrR+OC2GSTBRzo9VlUes48d1bZgcr0VOqQCjiPk4V+nQ1C0+4iv6CDHaYu4lsDdTaaPT74vIBuNm4nPT4nLOWwRdA5cqKUDnJ/WUxG0y6OMr+o52B09eCunrFWXW0V5rEGpabaEG29JXg/ugOSb1lAZ0ENKCikMd6fM2z1I3zdo/2QAgs46hO7c8fXXn8xrROUfoP3A9V+pU59BwD3UgfY0=
*/