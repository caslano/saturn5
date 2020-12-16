
#ifndef BOOST_MPL_AUX_TRAITS_LAMBDA_SPEC_HPP_INCLUDED
#define BOOST_MPL_AUX_TRAITS_LAMBDA_SPEC_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/sequence_tag_fwd.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/aux_/preprocessor/params.hpp>
#include <boost/mpl/aux_/config/lambda.hpp>

#if !defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)

#   define BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC_IMPL(i, trait) /**/

#elif !defined(BOOST_MPL_CFG_MSVC_ETI_BUG)

#   define BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC_IMPL(i, trait) \
template<> struct trait<void_> \
{ \
    template< BOOST_MPL_PP_PARAMS(i, typename T) > struct apply \
    { \
    }; \
}; \
/**/

#else

#   define BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC_IMPL(i, trait) \
template<> struct trait<void_> \
{ \
    template< BOOST_MPL_PP_PARAMS(i, typename T) > struct apply \
    { \
    }; \
}; \
template<> struct trait<int> \
{ \
    template< BOOST_MPL_PP_PARAMS(i, typename T) > struct apply \
    { \
        typedef int type; \
    }; \
}; \
/**/

#endif // BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT


#define BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(i, trait) \
    BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC_IMPL(i, trait) \
    template<> struct trait<non_sequence_tag> {}; \
/**/

#endif // BOOST_MPL_AUX_TRAITS_LAMBDA_SPEC_HPP_INCLUDED

/* traits_lambda_spec.hpp
Pi6H0ZM5/IdYoWh/CaHbBgnndT8x62qyCJ+XDbT2QE+XVPzPjpWH5Rhs8TNKKeErtCB7kvYFRUopSyVJZEl7KaXSRihladWi0oa0IIlKadMqJKmUFnukXUKbUplzv3sv9+Luz/3nPs/1e755Zt7fnDlzzpl3zrzfvGqXI0ND3eiXuhQXTK/EdS2NpFO3FCZKteDVDblYNjrG/L5g3pVYHMf1V/LhhI87+luZ4IfcK9hvpYc+T99iQEgPFPhFEB35U7gtOQlLtQXwJfdN5J50G1z86jHwTSRID6QxY5CGU81iCKoo4bnHy7FvgAVHJp+B2O3P8PwjbzraOQskzo1iinwufpR9B0H+x1GA9hPOB6WgbKIJjz8mQEn5HOLS2A/865rossWdqJVjT0Mm62PjJl98erceTsw8RY+P/wpHbKfirCeaoNW0nHZlK4NaSjGVs29CTuuNqHO1G4L5t6N4hxuEe70hqz7rwVeJF/hRax5Ih/PQdiF1WOPNS4POGsKc83W0YclsZG0domPpk1AY5tDeAcSr4pz0a9MXaHI8ASjJhjcTM4meYSTuqNWlbXLJ2PAeSKN8K/ociESHB7dhS9xSyhapCjwJ3NBlsguOj9cmWQeXoouRMva45EGxhy+GHOiCHAUTIvkgH5MuHSDi5h4w3ZSNno4wwoPLoqDW1AqC7WfT3PAv0P1UAoYrwlHBiBf6mhOha6gT16VMxT0D0qi3ZzequQ0Q3TeTQGSTKH6pTsInctNpyVzm96S9IlhoLELeXXpUcNYkLOt4QgdiyuG1Xw/UnZgMRqurkVtpCLuOu5HdfBuhqlKObi70hZsv/EkwjyFUip6iBWkvwN40GCOVE7BOZh2dGroUQsW30AzdD8g4qYdvy3bjA5NpeNB1ATrKdGBC2zmsm8EFjsJOWF3vDfeexaGzlyG9/+QFar7+Qr46Z2HnEytsPfYZ81y2weTxE+Cj4CrSo38S3UP9aOWV1yBxZRBirHnhZX082qjzo9/zLOzVK8Njh+owcEI0Ft1wBeMdGYAMKXrI2BpdlnXifA9rrFxzGTrl/LEujAsElrGD2JQnVPa9OBSpeZG9Yc0wa7c4fR84BblXxcNLpxJ4f5qf2l9JhjcrlPHoxQLQfadJ3sR6Q62aHXl2+Rmsbb5M8m8HI4N9O3JWnQKXknOEW34RzDxiS1KeLEejr/Vw1ucKfs6IpjFqGtC5yphan1gJ87Tuk8L0Y8hhJUA1yyyxiziA7ctp6Ni+Fk6VnkSF2Is0lE0Hk++akK05x2BtbBNZ2fMOjQVmYGeaCU50G6bbF5TCi5tjVGNCC9xp2UBy7eJRuusi8VwqCbqT3fB20QqQSnXBE3xzYTGnN+GVFcBPE9PRTiEUXII/kvMWrrhMTwuqcnlQknU9ajtsxdsyqmQ3Qw4nWHsD1771uOLcKIQsqASxOBcqY1MKRO0S2tslQOyWxVSr8R2seFqFKcZhuLjFkaS39MLaLznEVy8AFQ8N0WAOF7yR6kc3DAXDe+YZriQwhOKr5TF+gA3mK8gT64ot4BlWA2x7OFHDXwVNdMyxMXUeynhroF3kMWqvdw307mvS4ZUOOOFpBuHIMYIPMyfQq1Uv4U6bD5hq9eDbXTOI7gthbC66T56Vu+HmzAl4SqUaMh7p05ExCbTaYUe+FsZiSGMsxg0uw6U5BmR6eSmGzttPaglC915RTJLrhPNtr0B2tgCMvJpJVML0cdPhu6By9zVqiXGTrb1qUJHzBVXq65FjXgxZt1IH0kpXYuB6DjCPG4D2GnlYKaBJdUpLgYelnMZdcIITwUPEfrcCruiZSLybfPBQoi05LFqEo4XVVCd7PdZ8fkO4FTkg/tE=
*/