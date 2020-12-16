//
// ts/timer.hpp
// ~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_TS_TIMER_HPP
#define BOOST_ASIO_TS_TIMER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/chrono.hpp>

#include <boost/asio/wait_traits.hpp>
#include <boost/asio/basic_waitable_timer.hpp>
#include <boost/asio/system_timer.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/high_resolution_timer.hpp>

#endif // BOOST_ASIO_TS_TIMER_HPP

/* timer.hpp
LWWbS9R9+qPEHdfl+Sxz8ALJvx39gfI6i07UZMqwXAnznvMcOfMzg/0b+Zmh74PaSYXNH6thr5H4G/Bs8ksy1v51Z+FIXOgyUTIsnDK1SHTzg2M+bZa+l4XpkMtf1cdVzWcA5LRlzMejePKypj2oUjnep8TfpFqaqlotONbQUWP++UjTXGhOVPuDuiKb4818anP8DRX/Hvz4D2egTNmv8zXHp6y6OT6Dpf/zA3qZx814p+hl9mPY5YfNsBXxq9QFcSZtAe3rP3jUDO/uMsMuZ9gqoa0teUofIGzLCX+eQsewB46YYY9I2ACGNZKwSTqtORw/SViOhPVn2CNS7kyVQTqTL/ZK2DRPDdXfI+UwfNebcg5T0+aa9qwlbDZoh/hpGf7nt0RHUNOa/HTZsSBthknL8G5Ce9BoCmvnAXq5b+ytkLwZnnJc6iHt6Muw7tIvQ3V7Td58Q9KfL2G9GPaRpE2UsEEMyzwpc9fFsmXPf7/0/bdupzrqlrIZfkBoR+pyChC26EhwTHoxbLzUJ0dJOxnWQNLuMYaoLZpPBiP84qOW9AxrLrQ1JKwfw1q/LedMdNrh5px805KWYV9Z0l7OsC8kbXOddhzCXrWmZdhTQsdyGfb4O+xvpi0xx/2YJS3DFggdy2XYnHftac053fet4LzoxbBu0ofVYmurt2NkbBief0rOKMrZsTbTF7iyLPOOYY7ckLA+xgKk1DKDYYbbFx7mTA4P82SFhS1w5oSHeXPD0xrNwsNceeFhjo7h+bnzw8M8BeFpvYPDw9Tw8LRGiSUs+Mwq0jKv9iuyHkzwqNoJATn7p9fNsFXxHljfDdxVd72ELUryopRH0Ttvx9cx85C59+zLZtzLMT3QQ8Eyxqo6LGPpHjkHmuVRR9zvuL/CQn2aMSehtvu+VI8RKHPQa6BBrl51wCxTxj5L8k1O9+AGiwLv+Z55CaVGMP9x+qzu7pfJh4FzsuLf5zG5K4P5X3tAzjHGx6hnPHs9OZ5A3VsJz6V5vOZ5Ap55nA5apE/1IOwxTz3Pe/FYY+py+zeXBRvLHixtuy01AbL3FXUUd1W8Arv/b6ornW+oi117VZL7TfWV+1vvJwkXqkaJi9T2xOfVnKSnVF4ytPXw1eGVlD+oOqz3A1LuVLTEpxLhqsLVhbsAbhHbMVrK+1MmyoN+33HckfGyutXxnJrofAnlvaBquPeivN1qt+dltcz7uhrve111jtmjMmPfUY6459WhuHvU5PjHVP2Ep9RnCU+rpxJ3qAVJD+E8zjblTXlSHUp5VN2culv1SXtCxaXvVyfSn1f3VdmlijJ2qfqZj6tVfL7Olj4+llUFz/thaiXuBLhZfW+sVu87ytUm52Z1k2uNGuVer3p6RhlPep9Tt/ueUyUxz6oesU+qmLgP1Q+oy8H4pWpywgaVl3i7OpDYXg1M6qDuSspTmcmd1TDcnnY8uYPKTmmtVqZ0Vu9h9TE8tad6KDVPtUyLM/qn36++Tz+oTlTZoe7L2KaKMrep+lmb1HE+t6tI/f6W7VHxkBwxqjZcE7gL4YpgUf9enIDbZMSox+Geh3sNznD80flnd4z6Gk55YlQ8XBZcT0+RegT4DNxeuCPgni88SaqBN1tN825Ul/o2qXoxW3Af/33qcOwK9UTcenV3/Eq0rUDtTshTFyV2UHMSu6jGSQ+7Pkq7QF2R3lWtTc9Tdaq0V6OrXKQ+qNJdNc3IU5szuqqvM1qrqZmd1eOZeapFVlc1JytPnc66VHWs2lxt47nbI9K26+OcaEsSXDW4+nAtlQu2cV919nXFqCvhJsDNgFsIt931leMhb5J6zhujDsAdh/sTXJZvnFrkS1L3+mLUA3CPwv0B7gs=
*/