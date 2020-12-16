// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_AS_PARAMETER_REQUIREMENTS_HPP
#define BOOST_PARAMETER_AUX_PACK_AS_PARAMETER_REQUIREMENTS_HPP

#include <boost/parameter/aux_/pack/parameter_requirements.hpp>
#include <boost/parameter/aux_/pack/tag_type.hpp>
#include <boost/parameter/aux_/pack/predicate.hpp>
#include <boost/parameter/deduced.hpp>

namespace boost { namespace parameter { namespace aux {

    // Converts a ParameterSpec into a specialization of
    // parameter_requirements.  We need to do this in order to get the
    // tag_type into the type in a way that can be conveniently matched
    // by a satisfies(...) member function in arg_list.
    template <typename ParameterSpec>
    struct as_parameter_requirements
    {
        typedef ::boost::parameter::aux::parameter_requirements<
            typename ::boost::parameter::aux::tag_type<ParameterSpec>::type
          , typename ::boost::parameter::aux::predicate<ParameterSpec>::type
          , ::boost::parameter::aux::has_default<ParameterSpec>
        > type;
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* as_parameter_requirements.hpp
cAkcBUvgaLgGjoXrRM/s/5slHIND+n8o4Rgv/f0k2BVOhH1hLhwk5vK8JfOiadddnrd+o7oC0gG2ha/AJPhb2A3+Dg6Ev4eZ8DU4Rq5z4B/gYvhHeDF8HVbDN6Hy32fOV6YsSb2dg1RKvZ2PXjxcIM/ti2BfuBiOh/kwFx6AZ8MlsB5eBK+CF8P1sABuhoVwm/Rn28XeDlgCH4Jl8AlYDp+ElfAtWA3/Ai+Fn8J6GE2gG2AbuBImwtUwFV4OM+AVcABs5P9hcB2cBjfAWfBamAevgwWwEq6Ba+Am+By8E74A74YH4L3wargdXgN/CL8BH4JN8Dfwm/AVeBN8B26Cf4M3w1PwFhhLGm+GHeFtcCj8FhwF74DT4bfhIngXzIdb4FL4XVgJt8IG+D14E7wH3g63wfvh9+FuuB3+Av4QPg9/BF+FD8A34I/h2/BB+DH8KYwyzjOFbeEumAofhRlwN8yEP4M58HF4Afw5XAX3wnXwl/B2+CS8Bz4Dvw8PSPnbZs7Lhqek/CchxF/9HfXIewpU/ZqU92aYDT+Qcn4SToYfS3n/G6yEn8C18BS8Bf4dfgd+Cn8EP4OPQgKg3uN88DCMhm/BGPgJjJX6SlmV+ddQwtsJ2SrhHSfhPQt2geNhdzgBjoQT4Wg4T+rpZDgOToHT4FSYB8+GF8BpsAROl3o7A9bBmfBaOEvq1Wx4u7h7B5wL75JrSWeZ/0wdcUnnqfLeMg22hdOhH+bDDnAGTIez4CC5Hgnz4Gg4H+bJ9flwMSwQ+0VwNlTv23C5mK+AC2ANXAhXibk858gcYfo8l+ecthLeeNgb+uEAmAoHww4wF3aU9j0BXijmFbAzvBKmwEbYBV4n9r8GE+FWmATvE/PjsEbPUSVtJVzxSIk5rift/xkwDvaASbCn9Evp0i/1lnTrA6fCDDgd9oczYD84V66Pw7HmnEzYVfyNRoaIv7Xib53kV730Pw1iP1/mHtrHheKkrTfP7TZ4GHaGR2Aa/APsA/8Is+DrcBx8A06Eb9qeSw+I+6Uu+XWh5NdFUr4KJF0KYQosgt3hUpgNi+GZcJmkTwWcJ9f5sEzys1r67UvgxXA5LBFzGQeRuWY8C7iMg0yMDsQ7Fw6Dk6Fpr+k09saJvbPEXo5pz+gjxN4AGb/qo/JXns8lnd+Fqj2T9G6G6fA4zIAfwTHwY5gDP4HT4KewDA7Hvxo4Bl4Ku8IrYHf4TdgD3gl7we/D3nC76N8P+8InYT/4tDKX9zD4AhwCfyXmvxZ/fwdjuH4dxsF3YTx8H3aAXuKYCP0wGXaBnWE3OAZ2hyNhLzga9lfmUq+8Ml9DjSlZ3wBKbOe0euFVUn/WwXHwaqk3X5Xyca2Mo14Hq+DXYD18BjbAr0u9vwE2wW/AH8B9cCd8Gj4i+o/CG+ETcDM8CG+Hx+AdMNp4jofp8G44CP4AToI/gnPhA/BC+GNYCnfCWvgTeCV8CF4DH4Y3wEfgbXJ9l1xvhbvho/Bn8Bn4GHwePg7/DPfAd+Av4UdwH/TIuayx8BkYBxthvFxLuyJzFXiGdmlXMGs0OBimwWHS/w63j6tMstUTx7gZuo36e43oxbh8DxnkE3+gqV9zGv3hop8J9Xca0e/sUl/7in4/mAz7w7xY0nVSC2e7YmEqUolsQW//5SHntMoZrfDy0HNaT2GWfoX7ea0zMC9EnOe2br3C/ezWfZjbz2/daZghh5HkNYQLyUfSqRDZSA2/G5E8fm+Coee6Ipjbz3Y9xbX9fNd0KstYJB9Zg9yB7EKcZ74ewsx57qvnK9bZr3eQfs7zX6d+xX4GLOS6CbGfBbuN672I25mwhzDfAE9C59mwqVed/nzYnYQn8yr3c2I=
*/