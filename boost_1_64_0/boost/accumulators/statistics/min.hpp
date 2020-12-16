///////////////////////////////////////////////////////////////////////////////
// min.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_MIN_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_STATISTICS_MIN_HPP_EAN_28_10_2005

#include <limits>
#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // min_impl
    template<typename Sample>
    struct min_impl
      : accumulator_base
    {
        // for boost::result_of
        typedef Sample result_type;

        template<typename Args>
        min_impl(Args const &args)
          : min_(numeric::as_max(args[sample | Sample()]))
        {
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            numeric::min_assign(this->min_, args[sample]);
        }

        result_type result(dont_care) const
        {
            return this->min_;
        }

        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & min_;
        }

    private:
        Sample min_;
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::min
//
namespace tag
{
    struct min
      : depends_on<>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::min_impl<mpl::_1> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::min
//
namespace extract
{
    extractor<tag::min> const min = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(min)
}

using extract::min;

}} // namespace boost::accumulators

#endif

/* min.hpp
Ptn2F5+xmWoSL5Ktqt8c/gtlb5WGT1ym8vxURxaHtCcKHA7ZHN2yOR6fZDLPj6sD4LAD5wI8lxR9TLWqSCCBDH0C2bezYF/MmE40vmJXP3wTD9WlELXRHJCL72e3ciTI637Ks2CLedHvO5ttXtDIdNDtGEiBs3lNPci3x4DN4lsx3M9ecdUPgCAGdeXmq6Q/wY17QFiL894HfKGja/neTopeRTciviZqz2wufAUfjahwI6XWcFQHiiJbcMCK+Im0eUp/Qu19FfiIcsgUS/6Qd2t0z9qwvcP3qehVHG2LUxmp340N+cnIFjzPAWTUQpBdXVUuQX6F19U4obZjJopC7AIIkbSSazsqnmMzSzzABqOL6g4YJbd7jL9D9zpxL5gD7CLq9fNiAK1pIo2Cq4il6t7UgM35xAQBFWkD9YP6cSlAtQk9+gPuD7m1aVLRMPH6400NXfYrwY5taVl6cNXFDitEq3JaULiIgcA5X+p/TNxEnvRx1gRhYrJ3mTf7w1x/+MONv5Gk/0f99P1fIS9mD/soA988JUf8XsJmwFHTJISMw333m8vvJXX3kkpW52phSEE2eIuoiLdyTVKc0orkMt64AsanzKm/FEnb3nshc7XzIsWgrH8Br4mLC8p1E5O1/VNqYn9q4gtq42Jqogyc+DJm1+UYdl+aunOWNXUvo/ff98k5qRvAMMy8AQDSx6WmAwjzipUgGYe0C3QwXqrHRqZ46gr8FSqWtFFTMcgp340g66S4UIN0Ep/cj5fwQdL6LuAIzZcpsr2KR2vroli8tlyB5nGzVNkrvBildARoCZsNtft68VqlIq1Sq1CqZKzXkPdB5v6aQVZFWYgxfD6emghm73mBWr6KL3MyjC1s5Fdb2x28VHY/aqwmjQKf7J+NDxGjv6pM1EdLkHJiSFH2hfWaX1RPrZdF6IYaOq9RUdT5fLvo5jyPEyTRlrHIxgvXWMv4t2Nft+e5nVqlKlyOp5GrpX3t2IKquCOGOGS95LoTsURpIlbwascWcQwygNSiic1DeXN13jTOK+1nuxM7GB/Y4oVx1/ivp7Mvd0i461Sh8VeBa0UxvrrijWYHUoXCd1blBk/dZGvAcqwBG/Rnc8CcL2OYV4MRUN++p5uE0pr/3owGQ/9MHdghSXFmkgovFAy0RUlq0OsgXjzfnqKhApqYbE/eFtpQHhWSbTkf33av2YQHX0ITugOQXO3pnnxMAIbkhXa4x2mTercgUsMeD6aKak5BzSzJQmkUZAAayW1ncukk80Vk4D5gW3qlc4yfJseOhmxxiLJcxwPypmY7z1JZYIUxnYW7RNiNsNY4q8M69B7/1YHHoAtOEGYShBaAYKF8iqA80MAeeY+OLEOfTVP7gVa/2HJoV6iLcwRHsrXd/CLw1NKe7WLJNs2WLVld9WKIGv3fs/o/5cfnbd5k9Hm7oMCUV7voUn+rCwfXhqtlpuQYO8CGiRs9U5EoXvmXW8ecpqyf4o+r6EkBHH4Wkak5zzE9QwYHBe+AqCPk3KfWJ/Bq7R8VaIWxkP+jovJgdZbcLM580LX6pJifxfovy3W35X0yOkDnL34REuDtKUNeWKakG/vSDaUeyNes+C415hmthMxKrN3N7eqyCKGwjefx0m1Cs3wnc4S8gC9AsnI8Y52+G7EJE/EE4QrUpcJ+Wav88E815lfJdVV92b/IB7a3Wwfn1D+E6/qG4EOtnxFSw02liE+K9MMqjkqgqHU6KomjmmkV55J3rLv4ZtaqPKyXd8NwIdbHcRA1dhlTeQ/Ki+FnrakbJzTJ6xlikP2SyqICCLA006/cU1Cr2c+fpJ8RAXrihxwMLnIzgyuakMonTld+NIK5X9aFQC09sUg=
*/