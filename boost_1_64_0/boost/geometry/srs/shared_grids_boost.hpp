// Boost.Geometry

// Copyright (c) 2018-2019, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_SHARED_GRIDS_BOOST_HPP
#define BOOST_GEOMETRY_SRS_SHARED_GRIDS_BOOST_HPP


#include <boost/geometry/srs/projections/grids.hpp>


#include <boost/thread.hpp>


namespace boost { namespace geometry
{
    
namespace srs
{

class shared_grids_boost
{
public:
    std::size_t size() const
    {
        boost::shared_lock<boost::shared_mutex> lock(mutex);
        return gridinfo.size();
    }

    bool empty() const
    {
        boost::shared_lock<boost::shared_mutex> lock(mutex);
        return gridinfo.empty();
    }

    typedef projections::detail::shared_grids_tag tag;

    struct read_locked
    {
        read_locked(shared_grids_boost & g)
            : gridinfo(g.gridinfo)
            , lock(g.mutex)
        {}

        // should be const&
        projections::detail::pj_gridinfo & gridinfo;

    private:
        boost::shared_lock<boost::shared_mutex> lock;
    };

    struct write_locked
    {
        write_locked(shared_grids_boost & g)
            : gridinfo(g.gridinfo)
            , lock(g.mutex)
        {}

        projections::detail::pj_gridinfo & gridinfo;

    private:
        boost::unique_lock<boost::shared_mutex> lock;
    };

private:
    projections::detail::pj_gridinfo gridinfo;
    mutable boost::shared_mutex mutex;
};


} // namespace srs


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_SRS_SHARED_GRIDS_BOOST_HPP

/* shared_grids_boost.hpp
lOujtpBOYod+riL3KvNXzyfmVjgg772006ruh8ffmYHX60xgt2n73F4M1wHmADhPk+PdmrJyFLbrDmQ9bbcfYCaYiV7jHLkC51mmjur+9+eRcd/j8cBs1z+V34m64TsE8w5Wk9j4/uPQMsHKoMHx5tYoj3OUQDieNLv9yHI2ExicjtEud5hZAeuvM/Q/jbRBDZ8+wXQGacUVEk73uOERPF43Za4hbdr4XpNwXgfW1mollTn7rNuFMQ/dtQJ+EW1RSplvsR7APDTS1g2rgM9WGHtqxQsS7uWP2/yxzffSivHEpv9zjny+p7c6zoR6Q50xfyFaeBZHWs8otzcYZx+tmEjs16K73TDvfaGO0NR1FAZWkxyvc5mH/li3obB+IBa0f9A57GP9tGKwTlqx6VewHgxRWtGOHK/3sh5zMJ1R6vI0jdNWxXRGq/M+dHhmNNbRAHV5uldcIq9LDVSXZ4kT5S5gnx6kjrPMoaVY765w82ErCVd62Gr5zPMQdZw/lehYH+OMgb6Cpu4r6THq8lxx9wv53MxQXAeA2T2DBTaLWNcHf77D8jRD/ZE4OzZYsATTMkwL+6JK057Yj9dRTHFwjiM2OLnoVjweWBKJc2+P/vJ6eYJWeBKrfXPGFaz34dD/tNJmL168HNOSqMXnnpTxKbrVvnlYnmB6NPUzEmKUvFbpbnet0hWsPrEpb1+NwrbLWBpYa2IfHY9vjnGOztnMYHm00m6FFLyL6RynFTNIuLUbx8prVmDOxOo2+RjPf+l2Nrr/1UdYnmAu0uB8FzUG+x/YIWLv9reU66rx6jIrNnFOFwxnZ76LAkthPdhZmQJdV2L+Jqjtzt1Pb2KZ2dn+F/3wuqJBbXC9Z7R89g6M5n2iR1Rl7A9gW4hd8f6+PsaZpA5n7O9WDOO0s8BTu69gnHZ2yrwYy9MEVpiYW2j6K6x3sDkaaQVKXMFwYZPUcTZLnjsew9mZfPcRxjowerzddw6PwrHcLtyz0NVtsC2BlabtbOoWV6x3sLzE1mun7sZ6BytHbOrzXd2x/iar07ItuEgTLE8wHZr6eogRjB5vVf2C8h67XZz5YrrJ8rSz099dKIzjBFhBYotT3KdhuYCZifX0SPwB0zlFKw4Qi9FlXMf2MlW53iOtWlpAeUzLNC18YUXa85kFsH1m2pnLp5449pim51yeSWBFiP1xZH19zANYcRrnliwMlw7mS6yW3kM+0zZDKyKJxe/88wLGCYbtxe6ZvTSw08TGGbcHos2Ecw6xryuvK4p5BytOymxA8i+XsN5nq8M1rV0sEssTbDSxG0vmR2M7myPnde72cz7GTIyZGUtmLI2xDLALxI6dqDoOy2VuzuHEvJzNwJgRrA+xa0V0nbBNgD3Rkj7W4xN5v38hrAN0pI9lrAnHOJdqxUBivVzX7sJyWSnXCO52a4Q0sDhiZwNjjBjnKq1wtaZFOWkUfdhoAJbLaq2oSMzl5yB/PN5aLeyyIq1wjfwazB9jWWBwSLQybtNwrm/8TCumEKv+ujIez/w5zDGt1wAtY2X9d9hXMrZpxWohLVjXozr2oy+0QqOR5pFQ+jqmZbsW30WEtq/a99yQBvMXYmu69w/Fdg1WgtjI/aWbYbu2CxfmmVwLzyt24WpHFMqL4wtYGWJTx47aj/UHlkhs09PeejzeDhgniDn/EYNxhtnZu4F37mB5gpUitvh0hWtYt2DtiA3/rcYqLDOwYsQe9Pke8+66E9ogLbN5Jk8sMzBaLgPWt7uB9Q6Wn1izU8fwOooJjOahh7ZUIOYPzI3Y2QNrC2B5grnQ4y1rMhfzZ5eWla2PrMD2AlaYmOa7ZTHYrsHq6aQF7y42FtvgXq04RezWiYM=
*/