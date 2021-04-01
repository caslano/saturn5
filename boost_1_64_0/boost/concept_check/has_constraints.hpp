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
FPHXr9qR7FBOaf6Nksnhb9FMhsCL2g8LYxd88dUyDSVUT/5fl2EYDjTRwVUO9VLGL+jlCYLjGpZcfxtD5pkjsgdMHdjzmXmYYBhnhO+NYepLsXUyzIP7H3ZyA4Szqfmi71IrhS16iiKcZVsBLa2myfjS2BZrxRXUPaR2uM/xNVSe96tTrioGgRAVbvH3CZbZ+gMmyFzPH6+/kBTjLQl4kfMx8u13PbtMnMpGzY8nfO0g8BqYMw2j5t+GBYHJkgmZnufdyVuEKdp4uUK+rzyLaexVfOplm3FoT5xiTs2qU2ZBXLRZP+5V8MsUqqRM24ZmHepbjnMPNB2W9WRbQSsZvJ62/cTEOaQIJ7Lqy7r30mf4iMimUR6Uohpt0elVNsFNix+XzHsxHsov1qLwRDINKQgyJBLBOyVsEDkTpbO3eQRwlZmtchMfo3asPb4wA4v3rPmDTVtLE8cW1jmMCn9oSfpiS52aQNEreachjTbrdxEOr1uPRsILJTCvSt8NNYO5tblcDN75zAc0cFsEsFBwUx0tP5RVlpSrZidobG58XQRa1TGLtodAxDXUrQ==
*/