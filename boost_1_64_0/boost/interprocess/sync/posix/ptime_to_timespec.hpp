//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_PTIME_TO_TIMESPEC_HPP
#define BOOST_INTERPROCESS_DETAIL_PTIME_TO_TIMESPEC_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/posix_time_types_wrk.hpp>

namespace boost {

namespace interprocess {

namespace ipcdetail {

inline timespec ptime_to_timespec (const boost::posix_time::ptime &tm)
{
   const boost::posix_time::ptime epoch(boost::gregorian::date(1970,1,1));
   //Avoid negative absolute times
   boost::posix_time::time_duration duration  = (tm <= epoch) ? boost::posix_time::time_duration(epoch - epoch)
                                                              : boost::posix_time::time_duration(tm - epoch);
   timespec ts;
   ts.tv_sec  = duration.total_seconds();
   ts.tv_nsec = duration.total_nanoseconds() % 1000000000;
   return ts;
}

}  //namespace ipcdetail {

}  //namespace interprocess {

}  //namespace boost {

#endif   //ifndef BOOST_INTERPROCESS_DETAIL_PTIME_TO_TIMESPEC_HPP

/* ptime_to_timespec.hpp
a64NLktbxiyb+5FMPb3CssbsMNlN10bABcnB1JPsXsKqswpuu3FYaGhAtgHjSe5rpGsI5gpHmXFrRfa9dVGOnxB57TKjrdTWrYeKJQZ6+YpA69TZTTrc6HFwEz27yLafimUuhowjjuYkLrOdXcEykyDjFDJnzY6Ve2l5LJpllkLGRf6U/8ZzG0q5NZcZ7bRcZTuN+vs8Xt0Tbi8Iqu2Fdk9j45yK09+zRX0zGuvB+/L7tsbmeh/8Cqv1ehnXEbjf0lh+W1y55Br7VmPN8UBYT5tUpu5vGH7otrUK9vqEZdX7TBV1ipSXeXFMURmErXOEn5HMn7HfOcQqN7OskATNb2AXyT0OTR16wL2CJ0lmgdYLMRPvfhjKpNUDsJeI8kgzkUVseSSW5XYMMPYBjrbtAzTy+1DcD42reSxI5I3sZNsZJjzeye/DNj5E6e63BkKmrzU/rBzsfdhW3Zsvt4B7RD2Q7J8fuHtdi/wAPxTjeLJs/pDut9HFrrae6jUo8EM1lif3aZw8W9y/QZln4Fa9fkXZpmV5W56QbaoQetZCPRyxm6r7rCEw15NtIz+u0Zvh6+qC63ntFjN/ziH312oDtWbmmUB6E2F3O+I6BrPvTpZFiUqyz8H+btjZdEOZ9cpOel46zGG2tb4iCpvIn3PYjD2rZG5mk40VjRIKSwabsVuBzDE0nz0B5caqQZinp3J0mr18ZJkdg4xvpLP6G2E5bbDxjcxe4/+NcBud1qXv57k9fC/8zcjvxlVDmTqrSW2/m5rHVZV7yPhbWjPUG4B5ZE9nTWiH8LyYpvJb8r7BvMml3i2HQe3jhntV+8Ss95Po/nStB57aWztX9R3Bj+D3cEtZ+94oWm9O9yPNsnIwmTuj1HWyDEbGhR3MqvGUFnSvWMvBvxN4bewq5Id4pF+4yDshXTXbGVMskwWZCCETNtTHPtewjx5lW4tumPfWYuy9LnWvdaxgESt8+UlHvJiRqJPXevNCqVc/6oTJ0yaNzRtT6Ksj4oc4ListfaZBKcLdVbpY5f8cvvVV6jED9l+X/lD+lWfybaH7O/V30bLLxrl8nfRwdbkLOXXZKevRTSTzJfbf6eryt6ltjMAsa4ZQfEbq1nKohaEnkO51MfeYxuBqgKsJrua4jLLNQ3KdzTwX0ozWKvB9wxxFaUHn9iAtsNqB7jthepbcO8z8sjyodftuAS2b/JbmGJiNcbIf4a//uNZu2PmPa1XCzn9c63Np196w2yrtcgy796TdeYbdBmnXTrPkZeQDn7ItnO2sZZu7hrKt03D1WbHZqad3Vmx26h9/Vmz6CPVZsT1TT++s2J6pwZ8V2zP1X3tWrFHObFPENUHMj5hx9VcrOnaaR7Ot/1HPk/jF4URs8HGA38rzYjeMtIc3GuEdHTC844qM9c9Z1b8f9kPn9XrVneEqZeX6peDjlmV/Pzxnh+f5xbdslD2+p5A2HnV8WSVucPH1pNb9PF/4rXw/WVfZw9sR76dcGV5WU8t9gtHxtFZ5crFYah8gzOV+Ye4bRLobbTfhf4L03yfcOxTh/l3o1g0YbhRSQX4HS06jjJLfge868+1X28PbGelcETC8nsmeWuQN8ofr77fpWxBux00rKVB/DxV+ccwK4r3Y85IcBxfPTJDP9HlXG/PUZcDKwHHHMc7BxXtlLcqAlal1P8e5NmXA0dH2+DYUbcFA8aUNb8HFd20t6qS16rRRt9380qZBLcr+rGrrL247K9Krj5Fe+fb00sW6vurSS2iwzhN5Lbh08/qlq8ot9XiVfxlQx/Sg76OGsmzZGHWdURk4/pNLy4KLd6VfPFbUMR7W8N5fYA9vqFhPFDC81OgKquytqkX+rjqNNtc=
*/