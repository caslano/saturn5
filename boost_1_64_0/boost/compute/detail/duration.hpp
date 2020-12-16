//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_DURATION_HPP
#define BOOST_COMPUTE_DETAIL_DURATION_HPP

#include <boost/config.hpp>

#ifndef BOOST_COMPUTE_NO_HDR_CHRONO
#include <chrono>
#endif

#ifndef BOOST_COMPUTE_NO_BOOST_CHRONO
#include <boost/chrono/duration.hpp>
#endif

namespace boost {
namespace compute {
namespace detail {

#ifndef BOOST_COMPUTE_NO_HDR_CHRONO
template<class Rep, class Period>
inline std::chrono::duration<Rep, Period>
make_duration_from_nanoseconds(std::chrono::duration<Rep, Period>, size_t nanoseconds)
{
    return std::chrono::duration_cast<std::chrono::duration<Rep, Period> >(
        std::chrono::nanoseconds(nanoseconds)
    );
}
#endif // BOOST_COMPUTE_NO_HDR_CHRONO

#ifndef BOOST_COMPUTE_NO_BOOST_CHRONO
template<class Rep, class Period>
inline boost::chrono::duration<Rep, Period>
make_duration_from_nanoseconds(boost::chrono::duration<Rep, Period>, size_t nanoseconds)
{
    return boost::chrono::duration_cast<boost::chrono::duration<Rep, Period> >(
        boost::chrono::nanoseconds(nanoseconds)
    );
}
#endif // BOOST_COMPUTE_NO_BOOST_CHRONO

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_DURATION_HPP

/* duration.hpp
YnI9ziBNkymBm+o7J2TJU6JKmxVbrnYzNSdDkTpdxswI3lwbXInrkabGiAWBW6gzJ7TpMWHF1W6pDuSoMGbJwRlicQYxTikzYk3gVuYhNyNKiTYrtkRuLWdyFOmyJHgbMUlQpsOUwKFYpCjRY0XktuYChySpM2PDGbcThwJlmvSZsmbv9vrNzYhyQooqPVZEjowdcZLUGTBmxobr3UFbpClQpkaTPmv27qgeXIsjouSp0mbCikvdSV+IU6TOgCUbgsfqzSll+gTuLDbXIkWDNisidxGTQ3LU6TJgxsFd5U+MAh36BO7meuGIE/JU6TFhS+TuYnM3KoyZEbyHucb1OKZAkyl79xSXa3FClipDVmyJRM07clRoMWPJle4lVxKcUmPEgsC91YETUmQp0WPCnKvdxziSIUeFOl1mLAnH1IXrcUyaAmVqNJkSuK/2uBw344gSbXrMCd3P/CFOjgpjZhzcX39IUKPPlEBcXG5GlBOyNOgReoDxJEeLMRuCDzQPiZGgQI0mU/YeJCZZ8vSYsyV0ojYcEidDhQFLNoQfLD7HxEhwSo0mIxZc7iHaIE+JBkPmrLjaQ7VDkRZjNlwpIT4J0pxSo8+a/YepMXmqNGgzIfRwdSZDizFLNgQfITbHJEhTpkaHBWsul1RvUpRoMyT0SHOcDBXqdBmw4eBR5gpnEKNJnzV7j5YzJ2TJ02DIikuljCNFKrSYsSH8GDFJUKPDiP3Hun44oUSDFZHHyZMMRVp02XCQFotjEpzSpMOINXuPlyspSvSYsGJL5AlqzCF3I0OFFmNmLAk+UTskOKVJnynXymiDKFnytBkyYcWW0JO0RZwMRSp0WXLwZDXnDNKUGbFm/ynmOSlK9JhztayY3I0cLboM2HDwVDGJkSBNgSZr9p8mLlnyNGgzYculni4+dyNHhRZjNoRPxSdNjRGBZ4jLtbgZJ1TpMWfLjZ4pJnGSZMgxZkbwWXInRoI0pxSo0WHElAVrrpUzDkTJUqXNhDmHz9YeRQYEn+Ma4nokOKVMhxFTAs91DXFEijZDtoTyYpKjSJfg8+TNGcQ4pUCTKWsu93x14YQ8bSZsibxAbchRYcyScEFcziBNmSZ9pqzZf6EaECVPgx4rLvUicTkkToUxG8IvlitlmkxZECjKlSNOSFGiQZs5kZcYR3LUaTHg4KWuFxKkKdCkQ58Fey+TL1lKVBkSKonLIRkqtBizJPhy8bkeZ5CgwIg1+69QX07IUqLNnBVbIq+UN0mKtJgRLKsHV+IMYiQoUKNJnymBV+kDR0RJkaVBjwkrQq9Wfw5JUqFFlzEbDl6jPRKcUqbJiAVr9ivqRZQUVbaEXis+N+JuZGjRZcaGg9cZD9IUKFOjz5QFawKv1w43I0WWEm2GrAhVtUWcDC26zNhw8AZ9IU2BGn2mrLnWG9WMLFUa9JgQeZPYdBkTrBlnYpxSps+IwJvF4YQUeRoMCb1FvbkbcXLUGTBjw8Fb5UmMNGWa9FmwX1cHjijRZs6W0NvkytW4G0ly1GkxYEb47eYSMdLU6DBizd47XGPcjBRZSlQZEmkYW+5GjhYDlgTfqTacQZoaIwLvEpObcUKKPFUatBkyYUvk3fpBhiJ1BizZEG7qA2cQI02ZGlMC79Ee1yJFiQlzVlztvcaCJBnqtNgQfJ8+kCBNkwV7LXUnT4MhkfeLRYYiLcZsOPiA8+kzZcGawAfF4nIccUKeEm0mrLhUW47cjThF6oxZsuFKH9J/CvRZsGbvw+JzLY6IckKKPG16TFgR+Yg5ToYWS4Id8YlxSocpa/Y+Ki4nZMlTpcGES31MXbgbGXLUGRD+uLgck+CUPmuu1ZUrKfI0GLJiy40+ISY=
*/