/*
 [auto_generated]
 boost/numeric/odeint/integrate/detail/functors.hpp

 [begin_description]
 some functors for the iterator based integrate routines
 [end_description]

 Copyright 2009-2013 Karsten Ahnert
 Copyright 2009-2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_FUNCTORS_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_FUNCTORS_HPP_INCLUDED

#include <utility>

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {


template< class Observer >
struct obs_caller {

    size_t &m_n;
    Observer m_obs;

    obs_caller( size_t &m , Observer &obs ) : m_n(m) , m_obs( obs ) {}

    template< class State , class Time >
    void operator()( std::pair< const State & , const Time & > x )
    {
        typedef typename odeint::unwrap_reference< Observer >::type observer_type;
        observer_type &obs = m_obs;
        obs( x.first , x.second );
        m_n++;
    }
};

template< class Observer , class Time >
struct obs_caller_time {

    Time &m_t;
    Observer m_obs;

    obs_caller_time( Time &t , Observer &obs ) : m_t(t) , m_obs( obs ) {}

    template< class State >
    void operator()( std::pair< const State & , const Time & > x )
    {
        typedef typename odeint::unwrap_reference< Observer >::type observer_type;
        observer_type &obs = m_obs;
        obs( x.first , x.second );
        m_t = x.second;
    }
};

} // namespace detail
} // namespace odeint
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_FUNCTORS_HPP_INCLUDED

/* functors.hpp
hu+iXs8YlzP9nBZFTKdf5zrgW+CqVn+vdYbrduFfqfgIz2mNv9/YDodDRw+Jj25fMFYPP0sFe2cRt0urcGN8dI7CNcSGMwq1FGzxKjWQPpMZ48EGm2JjCcXAsVHwJ55zh7a4/wAHJv+JIW7+tA8bnaLFYPjuMHgAtlnlEfIFk8rRvzfhAdteIlesKcQwcGkGPrxxHLUIuEp7dP8KNuaBLMcJuLebIn7gviUZ1C0nazUI4jFjgoIc05PYNx67/ewt+oD91YGbrKEOtxjuXByu152YUbEP8aorcf00fGkzcQWZ/dELWcADz5G7uMEVkuAATdLhb/Xw55bkkRzvBm+pDm/qxHjczR7gO749bzs8eDix+QPkmQjOJDEWVB9+7MTYCxyj0zRq4WmMxXQCW5BNDTDdi/7XBg+EVsdfCqfCD1oS09OJs7P5fYQY/9IM/GcrvtyKfDQQnkFbnZzQ/1xqhz8ocB1iN/ZZEhsuMpD49Dk1n0+JHTHMMVkArnWgvgBHHB9C/Xa3huHwm2TekQcMXEGugewqROBXjM2sJF5GlSKeMicjUvOzNdhOQ+LWJ3Dcc/jWB/j1Sc5rY7SDiR/a+Au5em98tg99rUJulQFeRTck/oOte66T49el3YxT96Utt+DFHjfAonGMJ+cBR6h9J9Gmu/2pu94E57S6QyDv+hSc8mdc+V3kjM5qE4PqI+9XGM+aPZlrwIWdjahjvaGNW5HTgeWbeN79ARyj7Z9gm63Ih/9OfAsvBw+tAS8injbQag/47xchjH2B2e9CuAtvIdbVYYwnEk4Czjd7Gz5EzJ8wn3b7UXPimaHovDycyz8ZjnhV1WtPMcSsZPqe2oaxgDTykgpwiH7oEv0eWoj+ia9769HPh2B2BrokFx8ELuevSy6ILbvC8/YR68r2Q9ZgbEHigSC3WKfVtomp0XHEGOzeF7/OA9Y/8ab29hvy+5Xx0rv4YRB+XBXM474LVal3WeE997D3ZegdrJwaR+2tFZytBlzTC9wGvx7hZ99Ri3vvczg1uFPuD+rVyHTzDfQVQbwBQ+tQS71RCu5HrPXnb8ssbDUWO19OjgiWR/Hvuh9UUZyY+mQ62PstWFgcP/kemWEbh/eCBy7wsTjs9gwYtAS7BMvzLmYsAI5TnrhzhXt/v4t9wEObdUffJxnnxGbP5ce34SrJrYn9TeBF9H/hJOZNgAXOziq6gtO6k5cUxx7CFZ3rzp1FH7CFhcyxAQ7EHZ45YAGyg5+VugZP4Lp5jPOV3EAsiUVXzOmq+gU5sjbOOZYbTqMHL0WM8sNWwNvgC2DVNPwKXU0kDlWcCCe2kr/2gb+mYHcD0D19a9FBGweEt8YQv3hxdWqP6afhUJ2IJeD8pzNsHHTXL7T5PWII7RrrCt48pu47DDlQq3Ni3Cp0CHldOXAeziiugucDwdkAcHIPYylOzBWaSzvx86vgVdhO4iRxLQUe0qcoMRGb2vs3eAnzyBKJU8ph8q8MOHUldExNJRxdO2eApYK5MsxDiUU3M5n3EAnmnP/QFnsftwbnp8NPnMAIOG7oKGRHnGwO9tfYTp6ODXfg78RVmCcyAOZFCLnBWC03xhZWwgV3g/FFU7XVwvAk5DcgP7FtHvkO9nrdCb8GZ7rUxAZ6wAfAkj3Md0gbrDAWT86JTQ5vwly6KGIIssizgNhXnbo32PIN8aMl1zoFkktsxHcrkztoYzjklJVHMu76D3JP2tYgDzKqwBghnONTcvFUT2INc3T6eiv6eGQ+gY0uQ3a38A18zD0MHHFFn2Bze2fy/5fpRyjjPL7sY7Uf+/AhD4HfrnDDxhcT4xbAC4kDkWBySzhWaXL0BHLjqkmMj45k3lFZrdY=
*/