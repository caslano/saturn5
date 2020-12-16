#ifndef BOOST_ARCHIVE_POLYMORPHIC_TEXT_IARCHIVE_HPP
#define BOOST_ARCHIVE_POLYMORPHIC_TEXT_IARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// polymorphic_text_iarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/detail/polymorphic_iarchive_route.hpp>

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

class BOOST_SYMBOL_VISIBLE polymorphic_text_iarchive :
    public detail::polymorphic_iarchive_route<text_iarchive>
{
public:
    polymorphic_text_iarchive(std::istream & is, unsigned int flags = 0) :
        detail::polymorphic_iarchive_route<text_iarchive>(is, flags)
    {}
    ~polymorphic_text_iarchive(){}
};

} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(
    boost::archive::polymorphic_text_iarchive
)

#endif // BOOST_ARCHIVE_POLYMORPHIC_TEXT_IARCHIVE_HPP


/* polymorphic_text_iarchive.hpp
IfzQZv2aZqz1NtB3KNI7wFWznEYV5k+uqXR4EjUe4+NJ3tgVFQvbME9CceprKsM8sTJOQkQqTmB05vm/olHj257wL44v6STHlyvjo4G0okd6WAIFxfEdCnPmbtIqucEa3uswY8fCGrljWYp3un+GwTulTpqiE+aKVn/oBAGHpvmGtNBuoLYPVg4hRYdzaiorPENxugb7ymmlsrz9xAhjCywwlul9L2ad4pYCsV+7UCwubmXOgyfWjP1BkJf+NlKeIvao9eCfjL7W4e6EkR//tAp8+3y64Z/hJ9RyvRRh+mfY2k/5Z2gkvieCfGrzZmkTdEypK+D7/FgBXLJrR7RvycVgZOnCgD8ZptelX8TZ6FEmW9lI3/aA/wwxz75oEJtneyNiD/kdpQua+LDe+a6yR+XFO2cJO0PQ9Dk9hfRRoZt6LRHG0GPEGymxMIZOA9Ctfp4kqFkOdkXevziwMCLtA3+KL9BkSSv3FCgVtc1yV+6PIH9ZT4G4D9/tb47xfemPs5WOOai/sIA7qsl2hHl6kBY4xVVbTJK8Z2iuDy9h7hDZIjzFqc9Saimnrhb/sPD7yDkvUE6gj+Q8LjnzOedFXvTs1vo+ykVsLfqV5FxBQmszYr9visPueyusyZWsBUPdlKTllFwbkV8yNwHFu9NCTQSHoi8GTsuSARrcfTq6fCWNnSi0Vemsz7JR1kn8/V5LDJ67weAp0z8Hv82fq9ws/G1Y0DnGFlq7t8Sb+3SuSalrpYXnLC08jBZoKC61VrdfSzPcSXOfv9hcq2Wc+g6lTkaqq+xdWY/LrxWcOn+xYWM4qbaN4f5To+z9G3wU/J9q+Iu4tzqOZrirFVLvnMD+IoqRFPQXERr+SX24RDCgmu9wkyVt3FMqsb0DnqAmI3B890a4wwUalp53EJ31QssMC37w/pLTDigbt66q/TvJ+lv8dm24jPvHRabb68Bfch9VJaqiTTfp6AYX2AHox+l0hyH4HyAuFqphBsvJWxvj33O8dJWvNZ2t07z6jX8cf7TDaR+wvSARPlEIe9HE35xepEd7Hwig6DAURS/QiJtZ/AEudoW/m+9okyUJ7ilVwZV5w9+8dNRBqvW5h2sl6NRyVtLx/edHBKr8xVpVHeVf+Y1Jn0L9XyX/nGKcl5n/UGuLKfPO6s+nYlmxoqGhumavnai5IqrqrbeC0F9fKrs6NMDWMgKYh0LXDf3+8HcAZpot6OKzBCZv+p3sZxv0Tn+bl3QwxRuzJE5LeakCCVMEJPxhPoGE21mQtgZyai6aVnECQV2sR2OIjFfiCIHQ9zZFU9bdiKHRnunW7mDeEPbtdP3LbH5vE8raI6l+OLCJCeT+oBUHVD9Hcdre0buJ/s00t7bMQYQmXqrtMC1N78UEVjtRunxgDpYjPcKTJF7Cz+jFAsb9GFK9UzLWQb18znEWZ5lE3PZFPLRtXL6sw6+jR27gN+GTee0OLidURgQce7wYekmqHbn3DJPgSK/GUYbGaWdDt1bTqLj2tu9Twot9rzM+eGFNpd3jdK6trNQjfHvtgrxolWdmoaNB9J83tizcxG4otmVZhPmTcMXTanyEK0YjI/LksKAG4EebScGgAd8RrtgJKjLKsi/zanOLz1/Ii59Y1i6EUj9t7wuQ7NGGPcV/79itTlQc5S1m1M570cHreTUxO0+3mpWCf+bWrKRlKvIOLOsWommjWHspFgFjhaQQxdQpOvUHop49wYFL6hwMMOcYHARPxxKIG/jEc8jhmzgtbiqZGwS8LUqzw1h8ZVHZL80OCCwZFfCfDVjy+KcMS5JwO8VduLwPC9IYnkj4yNLCJr4j+E4s0+KdC9ulVTBH8H1tU53W3YFJCb4jTZY=
*/