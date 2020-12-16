// Boost.Geometry

// Copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_IAU2000_HPP
#define BOOST_GEOMETRY_SRS_IAU2000_HPP


#include <boost/geometry/srs/projection.hpp>
#include <boost/geometry/srs/projections/iau2000.hpp>
#include <boost/geometry/srs/projections/iau2000_params.hpp>
#include <boost/geometry/srs/projections/iau2000_traits.hpp>


namespace boost { namespace geometry
{
    
namespace projections
{

template <>
struct dynamic_parameters<srs::iau2000>
{
    static const bool is_specialized = true;
    static inline srs::dpar::parameters<> apply(srs::iau2000 const& params)
    {
        return projections::detail::iau2000_to_parameters(params.code);
    }
};

template <int Code, typename CT>
class proj_wrapper<srs::static_iau2000<Code>, CT>
    : public proj_wrapper
        <
            typename projections::detail::iau2000_traits<Code>::parameters_type,
            CT
        >
{
    typedef projections::detail::iau2000_traits<Code> iau2000_traits;

    typedef proj_wrapper
        <
            typename iau2000_traits::parameters_type,
            CT
        > base_t;

public:
    proj_wrapper()
        : base_t(iau2000_traits::parameters())
    {}

    explicit proj_wrapper(srs::static_iau2000<Code> const&)
        : base_t(iau2000_traits::parameters())
    {}
};


} // namespace projections

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_SRS_IAU2000_HPP

/* iau2000.hpp
ldTpPDY5LgPLDKw0sc3fJ5+xWRJYdWLnYu6Ntlk6WCkazu3jKJtlgj0kNjxg/ToslyoaGC2l9U95NBvrAWw7Ma9+v9/HcqmqEXuIaT/J2IRxVtOIq8TK7R51B9vZRxoRRaxv5+DiWLdgLUl5Xun9x0dYZtXV5flzny1LsKzBFhCrXuF9U+xjNaBuSfucEeeyEvNXWyPGkXCLI84vwzID+57Y65R8RjS4oNqLWPM+/r0wnXBOqk37WMcWezAtYO7E5P1Njd25TIfnMsW8vOHrosRmFp1w1WaZdTTirJA2MdLXuletzu48Ib+/AGa5sFpWGs6VFPMCq6+TVvroir42MzZS9l+VtiDixySbmcFea6WFhn1cCeNsqg63cfSMXTYLA4skVmHcH0NtlglWlNiDzdV/xDw0g75J7Ga32OM2M4FNJfawR76rGK451AMxWQ9Dzer9ZSN8lP1lbWYCcyZ20GPrrzYLA2tObFj7NTqbpdnFeaLb0O9slgl2VCMtz4LAnZgW6AydiLUsedbJZhm+GnGFxDnxwLT8GGcrjWhD7PPW2s42M/pphC+xyb/+/JvNUsG2k+MVWP6ikc3S26jz1yuhYm+bubaFtkRMtiU4Htg4YklVb0/FdIK5EcPzEZjwz9kMjBkZCwNrQOtv85CVWEdMuAzGshhzbZezeTFmYszMWDJjaYxlMJbFmGsAkz/GTIyZA5j8gcVppd36I7Attt2OGtiXW5q2+sWX2HYDNWKCTtqY+F+GYFvqooFnhqStDVt52mbKTaZ6xGb6D/XAPIDByUL2lcrvJ2O5dIWvduilnc1b9iMM10sj4NSJtud51G5MZ291Hs58GS2wr4RoBPwi2oI35bpj/fWBfXJpHm7seoBpCdWIWcTifUxJeDywwsQue+qO4PHAYomNbt1yH9ZRmLpPP24Xj2Xt2k899oxMONsBw4G1IvbG+dJnmAewr0m5ZNbZ0QLjjICzp5aMrXuDErH+ojXCn8Q54iNZLklgHYi9bvM4HvMXzYw9A5ixZ4B6rCv16hr8as77c+M9jVgN3MuR1q1nf/xehxGsAbGA1LvH8F4nmBuxKu17+uP6F6wlsbk/FDyHxxuqjjNf0p0yeP0QTE9sSfftOrz2bBduboFjBnzOA6wosYt9yuK++JlgzYnlPTBkHl6/hYfe8xPbXLzFWMw72BaNtOIdm8RgOuM0wkmGUz3DYwarRWz/y5VlsVzAdMRqdHN7hnkAq0Qs4vftTriuBitMrH21YnOxPOOh3tHUz60ZwYaTPGysdro1PocEUJmEW1nwyT1sL2D7ieV3Db+McY6AOQMtzxYHMjHvYDHE3nqvw2falEVOR2LfJAbI8rSzH5YE9cJyAatD7KT3H90xzkR1G5T9Af6NMSNjYYwlMZbKWDpjmYyJUUz+GDMyFsZYEmOpYIWIdf35YTXMH1gisTkPdzXC443WiB46aR0fObfGMWS8MleUVurlpD54vAmwPiLhVtfPeoThJmtEIxJu6K6xRbA8wX7SSluar9hJbJ/T1X1Fc6nXKTwe2J480l77X0vCPgYP2i4i/SjSdWg3tIUauAsqrdi2PfJ7VWB5C0gbFf/QhPWXqoG7ItKie/f1wjIDq0uswsik7zCdYBNJubhkHmqAaYFvEZQk4c48ahiEYx0YHT8/PlvUl/uGAZannQ37fiuO5cYNaju57Z0fphNsG7HYVm3O4vE2akRXYhWK38BwWWDtpcFBbmObMH0O1yCIdbwxCsOZwcoRO3jvmy2YFrAexA6tbPMxltkmta1v9zYe0wn2gFjprcvD5PejYM5HbNqUohuwXLZAmyDmc6t5AMYJtpRYv0o7JmC4rXCepvXwrN0=
*/