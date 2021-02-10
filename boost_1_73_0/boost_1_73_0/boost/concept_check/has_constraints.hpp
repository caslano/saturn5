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
vUT9FAM7wd68g5/d08J24BD+1ep+I9y9fEO22HVOSdXUcDI6IKI374711XIL1vLtffaCifcxmATJwvLaXmMTcU7d0/b7zE/msxA+e5O5b82oxhWo4FvJrNt23ewataimroXURlZmvXaO8/A6jG7DNGrHw4AqoTsB2LHvgzeJI5z7j7OnZIKNunHAftLTbx+O8pwm7Xfb+gdQSwMECgAAAAgALWdKUikXPXZCBAAASAkAADcACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMSU5GT19DT05ORUNUX1RJTUVfVC4zVVQFAAG2SCRgrVVhb5tIEP3OrxhxysmOKE5aqddrk+qogy8oDliGNGfJEsKwhD2tWbq7xLEu/e83u+AmvqTXfCiWvbDMvJl982bsLm04/GmX5Wo4+OGVmm+KF647p5ngf5NcPe+QpvfQfdBxiesLQo3gwes+HcKLvO5hYLzSPtaJvk/TF4Rb6iT1z0g7L1N9izudZ+8/5s1W0JtKwWA8hNdHx+/glV5+d+AsqylhECtSr4i4ceCkMDt/VNndnSvJRweIgoy5e4BJRSVIXqpNJgjgPaM5qSUpIJNQEJkLusIHWoOqCJSUERhHs0UQ/unApqJ51eNseQuy4i0roMpu
*/