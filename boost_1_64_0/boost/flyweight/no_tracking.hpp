/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_NO_TRACKING_HPP
#define BOOST_FLYWEIGHT_NO_TRACKING_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/flyweight/no_tracking_fwd.hpp>
#include <boost/flyweight/tracking_tag.hpp>

/* Null tracking policy: elements are never erased from the factory.
 */

namespace boost{

namespace flyweights{

struct no_tracking:tracking_marker
{
  struct entry_type
  {
    template<typename Value,typename Key>
    struct apply{typedef Value type;};
  };

  struct handle_type
  {
    template<typename Handle,typename TrackingHelper>
    struct apply{typedef Handle type;};
  };
};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* no_tracking.hpp
5+L9UgDNl6D5DDSfjorvkmYgv+J8AONpz7clsFlI2yzGLAQ8SMss6ZGubVuuo78BVBo65HBIDt/bOJkL9Qu1JyBBdikUPwdkob1BDk70FQDdDCW4QULyZEeTtNMthocIWIJfJDyau9NrRTWcN5NJ250S6feZ5Oh3N3kRqJ6KMsdhKHO8X8oc37iXmQvM3V4dX4C2X/nXtH+ar55WhYyqRAI1J6fTsTejnaoEpjDRMyjL1SY6a5w4vnpCLI/HkDlDepnJkcN0rFvyjn/70OUQJSAlwckP4s4WyKdj3S868jcuZZ/soPhdU4SUfegfjBIKV3iqtru1El6Fzuzc33QuFjhb6/kgAfllAT8K4LGEH0t4uYjaLS9mcTm4myQ743DY/Y6GXZspUtS9Sg67ibClcClItvSdlNLaASWnUwveKxbqhxO34xA9tqoi86jZ8FS9tddZV3iGybks/oOL17YX2XTLRT6HEt3ayxnYgtnUgixogSiepU3Yhv40yinrpyuocV7ND8k80KajJYEGLfi/J2mrHL1a4V+Kt9nmX1Zz+NTVCv/y6nV2+JcyDrr7aeJfemy1hKL98fHfWPNfPo7kxxUK/cu32qb/0CqCX79CoT/1uvj0FcT/ECYRZbDuDskWnMklYMJziN9DkwjOoDC/ZUBBNZNGkNNOMG3qn68mR9s/8aY1PMjtnzbb5Q+LmP3TEwy89kJ46Uv+Bn2waVH7SrRusxVPNH6SMn7M92U/c2lS1j2v9ltS4w3/jfAsUwlEkGjwBVGYuzrJVZzN4BPgmHd4QOaCW6Vea9pmXBQxJ9E573Be+Y1WyRPnTBbJLiV5ZHCsOZmQ9DcnE5KOIjnBgCSdkUbNC9LajdnEgqAbUGQQB0tdU7H2BLCgwyEpmNS4EBEiOG9wQMcV7JZX66LJvvTOBL4hXweg8w67QDA+DocG83XmU+p3hbuq6HL1Qo0bQHIJ0RldDONLk0TnOzfxzg+PxCX3RBdbcu+fhEtuCi65ZdJf0Gd34gLUjTCUSwybXjr2q+ux/5nX67TH1PWaB3UjowUlHvNQN4mJA1rfLUZn+J1lMAXPDKMvfLdY+4+hN3yL+J+PSi6lCA4h2jvL6iO9Lu3DWMlsJfpdqzkyovOFLhHWMt8lmcXEdEiQXlk4YJ125TTuHJn7Rp6XG2E4WglIWqmEXlsySYUhnfepPJNxPZlrHb2qHIywU0VCqA7iy/kycZh3Yml8wDLPOmzAesMbdOaIAs2x6gjzODEVyeAFxHZOUccZ0VlY29EBem0+EfxOqe1RY6uUUA5eUukcgjdTe4KS/cHU1Go3vVJTfMZ2SVVR4woFEVL2W6LsYgb8isNrB4m5Y9upCNswhGXbw8PV1ARIZT1S7bRTQ6MLDx6yTxCQVjQ+KlpoVvCr/SyP8skraTvcYy2fOH1NnPKOtQ8RvsxHLfF9+px9ecc0jmrIPWZ5xZ9s3T/qy+HnPxKl/4gFT/a/K0yuV4Tnb+kfvRWOIhgsgr/XUp3s/OurmASV8bReTmFW2OXLSARgWdSqvHX4rzyV1+AC+9B1umt6OjYNDnfAf3EzTahjW2luONRSj7lK13hWKPLCt4DAGPLQAw9S+Zr2NTfAEwPDfdKGfzeyfyF4Aky/zpZ8cjrBKNbdz9rhn4cQmPadkBZatl+lp/z39uS7+5eb5bNfxSXfXRYFf09VHPHoJi83+/98xjY/7yVYgvOWNRcv8dsHqP/W3tRM/+15QME3Yoa9/lv2gLn9z9wVT/9NioKfOIfDN30eMeHoSDiY8ZGO5/5pHE+z/p/vN/X/+qft9H8JG/8EGxArBz4EDBdecG3BFQH+8uhyg+mQ0GEsnYBL2Qn4Elg=
*/