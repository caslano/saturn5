/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    noexcept.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_DETAIL_NOEXCEPT_HPP
#define BOOST_HOF_GUARD_DETAIL_NOEXCEPT_HPP

#include <boost/hof/config.hpp>

#if BOOST_HOF_HAS_NOEXCEPT_DEDUCTION
#define BOOST_HOF_NOEXCEPT(...) noexcept(__VA_ARGS__)
#else
#define BOOST_HOF_NOEXCEPT(...)
#endif

#endif

/* noexcept.hpp
HBzRnSOL3wwDcxCYWfOZC//vh7PsmnYfCJ1jvsNESrcS11mX7pS4pk6UyPY2XoTnLLvDzHlwLPxJg+B5Fh6xc3AEuYGpt1ZdlJ46gy79/uzZUzqhJ4+fPE5oKCrFmhaeq5ztRUIvZNz5oxRXVz3HrxJiT0L3oqJlqRw5s/IbYZnwrFXBlWNJwpFkV1iVY6Eq8iXTSmmmwXR2Npq8TWhTqqKEjq1pyJWm0ZJKcclkuWB1uVNRC+vJrCAN3VI5D32NV6bqwTSTZ7t2UBGMC+0MiUuhtMhhRngqva/d8zQtGqvheSpN4dLi5uq90q/3tziDB2uxJVN78oYaxwmFcwmtjVSrMAMKbNZNrpUrk1tXYKiSqbHkWGuogphit3OZabFHJgmnqIa3yofJmcoFS5vSrL86CAihZNXYCmYAAc5IA4ATairJNp6Nl76xsEczQvsfIbn1VZKp4Akd9hc0WhxSLpxyCX0cLf+cvl/Sx/583p8sz2h6Sv3JGXT9PZoMEW8FS5b4qrbsYNmSWtdasYwGH248pK62FHJ1ScvZKQ3ez8c0VrkVdovoNbaImUDTxteN/x/cpAUXacgrVXHMS6lQxt7YUAwbZM9u15XISWRhHtjUodKdktzC3ebT6XI8ej0czRf0/CUdd1bGsihK
*/