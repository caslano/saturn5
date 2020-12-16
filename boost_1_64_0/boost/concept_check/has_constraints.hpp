// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_CHECK_HAS_CONSTRAINTS_DWA2006429_HPP
# define BOOST_CONCEPT_CHECK_HAS_CONSTRAINTS_DWA2006429_HPP

namespace boost { namespace concept_checking { 

// Here we implement the "metafunction" that detects whether a
// constraints metafunction exists
typedef char yes;
typedef char (&no)[2];

template <class Model, void (Model::*)()>
struct wrap_constraints {};
    
template <class Model>
inline yes has_constraints_(Model*, wrap_constraints<Model,&Model::constraints>* = 0);
inline no has_constraints_(...);

template <class Model>
struct has_constraints
{
    BOOST_STATIC_CONSTANT(
        bool
      , value = sizeof( concept_checking::has_constraints_((Model*)0) ) == 1 );
};

}} // namespace boost::concept_checking

#endif // BOOST_CONCEPT_CHECK_HAS_CONSTRAINTS_DWA2006429_HPP

/* has_constraints.hpp
3SJWByKZVVFYggjLY+T3eZy8OHbSLJYgwFobvrXifDeJ/SxwPeCzZnMAbR/xfrOQWSXBJ6c1LbFtYL+RyfkiKLwqqJSC4emKEW37UJ5vQSgzH2z+0VmMbSP2Ik9XEIRxqNqblhnup39qhZHLqggjzef91CG0oczSFIoyKtxKBq4W6uyn0bb+F622mueyKINSy9pV1cG3FlROiiQsEt/1S8FnVjxt4ot8TAhkKXMn0TK8c0RffSx+sagqT4ZREQmVoOWlxfna/vwptca2LPyiLXkm7ws3dquwrKRQUx+4+6ZWUDNqcwGCNrIO+uZnsqGQThFEeZmL3qn+shKC5nhoQs3TV6aXiY3kMdyjoPL3KNxcxmkYC2ZSGX1KW+Ug3cJ1/DLEVbN2c6DcWgz5VrzIZKWo8ko6aSHgMGUB7EDrDmoCGkSHNWS0y8z0RKLMgqRMXFk7G1haUvtFmObHqmvPZ8xYbOKx/UtrmM/4MPSr0PdjVVYr8zPapjPktErLbM/e4iG+cqkeNxFe4RdBEbpC54My8zyYZ2adeT17BJUvROGUcdKYP1d83oVOhGjriu9NuaVq2lXsiyltynt4Q2pW1TrIjMdMDYgdZBb3QJRJLMHmjlD9NwmdxRvtbTJZKWQSRFkQpAJyqy7E+kksVLmp6ZONnWwomJW+XopTW6csPYVIo6h0/MplZQG9JNQrXR5LaktbuVWARNa6sFzZuicQYVWkTpZkTNfKwoiSbX2xxloP+kmJ86BKokyYejmleo3HdttdhzXT22GP4V4qYjAPp4aZ9Tua591Kpfs+iDPDznhmXv+g7WYgovFm2B+4Tb3+d+r9gXs3f8f9AThzuC980/eJd5AzoL/UX2cWtVMhhl0xGDhrIWuOD6wxGAAwwq+ws6pHfI6vN4PAj90sjVe/3pyq15s3JnH5cx1evaTHOOZr9Xf0XtnG8ZfrNFbfecPLopifuzYwHDXQ+zAXvzWu9lFVbMwDcHQa1Kb1p5+19ivd1Mur1P1f04o+QT/H55J+VcShG3pCETH4+v6n5XOKyQUiVTnul9Lhco8mkmP70XeCtZaL/bz0kyLjsqdMt+uYNeIH1M+fxuoLq8DU3Xa7vjy6huFwEoTYe9ZyDBb6Ru/ODUMYVHaUvbyR4fXZNcZpE8PUn3VxIX5lHHGaOtR98VoMhwqOsjPXYZhuMWTM/gAfsxM3izM3ddpzArioPUGn3ViP3viZNcxedJa7WZU75f9aj6A/gfa/s+5vtABEt2OP5o9129GRw30BuOcDGMhg20fsI+sMhn0GYsc2GQyvLeC+4hXEoLjI/epx/Z33JXifeP2WYXxyYXGy8aRD9ris/CsDWB1W4f+af7T/+0OdP834pWKF2Nk1DIO1ZHvPaC3D4And5FS/b2xCYP9zuYOnbVigriesszmTx1U7XJyZVPfFiK5t620eFgBy3jjE0RtlpF+/zwabUxcW6rg4hGP7Qs7MRpuDEUbOP4c42A4xLmc32Zy6AmDe7Bq3cVaBMKyPDPOw3eKbm82MAxt0GM7ytRg2GFWe8bVt3t2HyrO/hXNGlWd+Hc7rKs9rrss5XeX5S4tjl+dbr8fxrvJ8wlbO6SrP/Pqc01WeO2/AOXZ5XrbwUeX56RtyHi1PfKvN+oJMRGUBfu9XfTfS9AXwHvhWu5Q+a7/bIfu0NyZnK7+HeOHbDP02bY3+rq+I6ULCurd7rcahi5n0Y6ZzvcasvetfbtDfm25D+cxSK3iic34jxaFMW2x2E8P6jz5B6uc4wSZ1ejv2pLdtprzeGd0YEP8hw4fzauZaGse9cF229HtHuPkWjfOHMJi2sesgPpTu+LoMY+l+7fUQu2q677MVeTQ=
*/