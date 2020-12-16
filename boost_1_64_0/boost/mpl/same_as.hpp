
#ifndef BOOST_MPL_SAME_AS_HPP_INCLUDED
#define BOOST_MPL_SAME_AS_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/not.hpp>
#include <boost/mpl/aux_/lambda_spec.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

template< typename T1 >
struct same_as
{
    template< typename T2 > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : is_same<T1,T2>
    {
#else
    {
        typedef typename is_same<T1,T2>::type type;
#endif
    };
};

template< typename T1 >
struct not_same_as
{
    template< typename T2 > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : not_< is_same<T1,T2> >
    {
#else
    {
        typedef typename not_< is_same<T1,T2> >::type type;
#endif
    };
};

}}

#endif // BOOST_MPL_SAME_AS_HPP_INCLUDED

/* same_as.hpp
K1bZq0sY/+jJWPszdfp38bP2OwSfp09qoacWDpmtpmQGnOrBAWabv6CFRweZhUXCjyZYd9BBwBl6syUhXAjxwiWWxD3ZYklsgXjRgmAxLYIYiqV1DVr0Uba19h3O2GJbhBaX0BkBVk6k62Cm2Oj3M062TfFFPGyPP2CZLv/6Duv6yM8eOqAnh53ZfzyB/heoWmKXOJASC27+LHXE21tYAFkn8qvUspPicmGnp9GK3segXMz52ie0IsgDVqytD7P/s/kcJGLNYEqkbD3PJtpdT51awUaGTZstQb2ID19s8s5kyDuHGS2inBPVbGM1RiAD7fumGkUQ7FrsfbHxWb3SIpy5bB/JuOHLJWw6QTRtxTWkz6cL4R2Zv/aAeEBjbtBYmaSxoazCO8gC1gfAltu+dJOnz7ijqNyo182+Ds0+7340G9FXS2hRM/Kn6qZ9vFrh3UcR6j9YmYPouCXoaiQEK8yoT7Q+Z0nhyExplA/cT9DDCMS/Wd4UFc/X87PgJApAt1neOxee1Eh3P4VL9wRLt9B6njkno2mwgz6La7HmZsrB2FpTvVXwkO44LtyKs/OtrJ3air0vfZvs4Y8+ChzD3/0L180ka8epxjlnCDlvy1DcLtdA9jM3iN4bRLfNUdVCiJhzNmIKz0M+f80aJ+crQj4f7Ow2nwQ2xGVCVMx00ANlQ7DMERTB8uOISd8RMPPoyiwqhC2uyLs+7WzKCAvABvq+3pkmAKwRACAj+8zGlWJyuPFGrClc2siqIecSxZB6gBR2/hTjjoA8tMDdrPePs+F5ToSUey8ISQUTfujx1I/kD+hP6Ls3W9Nz/Es8PVkn8ePr0azCNef+vlN5RhgZm8YVeikRsyvgANNtnGmxa8RXOTIwWvGSK6kvsu5BXxh1wAM1v7wixX2wXt/6U/1ie2/+QFFjq9jWlrYOJDeNr9qrTgxMR500ja+iOuvv5jpXoE4M4ikruO08hBddJ9se6UXWKyJsRTbR3IY08euaPLViGPj/L5ri73uEAwxYXzsqvbEOKJhHzlHXzorp1MMhsuCavd5kelEGbA9GVopVJa93FYt14UIUx2L9ZylBehe9ARbfiPU337zhNwL0VipB0xDrL6bs4wLH+VdSmr6y9k6Ua9iQ5lJc6iNwP9oROldKoW5LSMycLbhAaQuiwNMMEv4mNOvFwrY33VrJfyBby6kQaQ5hgGjQk9dK4C9dLoFvJqwRoGkz8NycxvTTGDmW0Cozp85FPlzadXodno1sm6bmGhrmX90VNc2KHv2up5m2t6p+WMtf5skL7BLXavqEoC4kv5gep1086ikd3+4BkYBEnsBFAzrCfy8hysjbpBocVmfPjPd3gjj+plP5O1VPJMmHtWFfOpULXMABu+lTYiuZ1KoEwhtslXSLPCSm82GY5Xtu5yHY5rSGYJY4/7wzRVF+n346/kwr+0N1EL8G3umx8Vh+/1jn+ma4CiXRN394W/L03OUdpsM7vSP7y9s6hmcemyD/j5E/QfzzqoTtM7c/Ed8fzy3vvD8+uzV5ewc/mjz91wnKQ/+fQv2v/jJx+V2Pdl7+3eXJ8bs4AXzQ1/SE9AVxfjLZGd1i6Rsmp2k5v9xsmGsllOiEsnLz9kVWQllaCrtF1AfRcbK+awEQE4LQ/hN7idUyphTbRu6p4D457EYgIXa9Q4yJljh7PBtZygV52iy5HDYVOlBQ+ziEenKQb8Hub2Cqo6Ur/tQYe4EJQCGvHPelyLPj4UJ3rr4/qThPMxiRj7BGtsaqTPJmJIYU+RUADTHOB6pAbsnTQFXuHx67RqFaxw6dOL85gfggNpf3zpDtzSAn8zus9p6qgADkDAUkckqowkRjG7Br/OA=
*/