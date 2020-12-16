
#ifndef BOOST_MPL_O1_SIZE_IMPL_HPP_INCLUDED
#define BOOST_MPL_O1_SIZE_IMPL_HPP_INCLUDED

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

#include <boost/mpl/O1_size_fwd.hpp>
#include <boost/mpl/long.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/aux_/has_size.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

namespace boost { namespace mpl {

// default implementation - returns 'Sequence::size' if sequence has a 'size'
// member, and -1 otherwise; conrete sequences might override it by 
// specializing either the 'O1_size_impl' or the primary 'O1_size' template

#   if !BOOST_WORKAROUND(BOOST_MSVC, < 1300) \
    && !BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3003))

namespace aux {
template< typename Sequence > struct O1_size_impl
    : Sequence::size
{
};
}

template< typename Tag >
struct O1_size_impl
{
    template< typename Sequence > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : if_<
              aux::has_size<Sequence>
            , aux::O1_size_impl<Sequence>
            , long_<-1>
            >::type
    {
#else
    {
        typedef typename if_<
              aux::has_size<Sequence>
            , aux::O1_size_impl<Sequence>
            , long_<-1>
            >::type type;

        BOOST_STATIC_CONSTANT(long, value =
              (if_<
                  aux::has_size<Sequence>
                , aux::O1_size_impl<Sequence>
                , long_<-1>
                >::type::value)
            );
#endif
    };
};

#   else // BOOST_MSVC

template< typename Tag >
struct O1_size_impl
{
    template< typename Sequence > struct apply
        : long_<-1>
        {
        };
};

#   endif

}}

#endif // BOOST_MPL_O1_SIZE_IMPL_HPP_INCLUDED

/* O1_size_impl.hpp
Z0upp3feuBql4ILwVGpISADtjTAdK9NEK6WGcgpARbuEomAgFeCUa9eP8wtOF4pmpv+8PDnQubX7x3r4NddomYqi8PukFH6lGIQqtfuDZ25hY0siyL9mEaz2CBEHaZBdV1lSR41GJQ/HTyFTJbt76bYih7aUSP9+LgFA7bYVuXgzPCEFgFeuj5YnAjJW24rMdHJLQAQ5xUqjyj7IK1GiSSyeM3TO21Mi/XPzojW2Br8QaLvbdPzMPGjapoP2471lLL4ASNnP1EMExOjSDgW1BJUapX2ooJbIJZLipDEOOgMaMWmkGZVvZmnquI+UAzzmt1g3Id7YOky9i9YwbScEckqo9y1d/fRlSVlrKyoDGgBqC1olgxvn3plaorJVKNFMVlnuId2zSGcW/DxACBTtJuUzxCVts9+WtIVA3y/AB+htDYCX5Zpn/H1j5d5a7ljxybA1yMLW2RryrQ5IS6wXt5/6Qycll+l/IVMHpl7MmCgxvcnssZNB4pY6PX3Z1xmVfYlR2bMQrtOd217HwBtZk0mjynruGLuQYToWUnO5c0AAvITenAjuOPsA3lpfLY+v7589tqLZYi3PDBAAluAt7wseCQNAlT1Yv3OFhrLErdeOtzBQIajtHtuftmNz6KQeFXLq4wdeUX9uO/YHLw16U1njOxG8+rUoUVld+CXJX+uqANP2/HxcbNpn2o9zs/E7gkeFnPzpu7XQj0xecRtsOWN/VSnyMq6DsIQ6XN/AHfcZkOtlwRttReY6WUOAyvznte/ZPaQdDGNDVELbVGG1zVTdeKkO3NrD1bMFnu4h457omQE08FKr99N2ss00mkdMvoa2EGxi2kkEuCMOex17mqWdM1UprMFChh8Mvd3OlMjGiB8G/mcpJapmxI8Gv0MHSlTDiP8L+PEDKVFNI/5M8GObU6JTRvxV4KceEooqmXH5WeAPDeG2SdwmrIUUxgtoiXbDIdP97Uu2dt2geMxvYZ/NxHg7xLRZwGbtutEcVKiTl2X3RaZ2LMJL0pi5mZv/B8gtQa1/oJ9jpC/aa8vZ55rutSV9PY21/niCt7Ias8+93Mxd24L3ctOU7uWuz2QtBi/nsBDzkbXvknSZNbP5Fu68SoXcsCZv4c7lK3t/Ppf17c2sG6ZlI/N3r+l+8nCvdnzPYqVXRPQIj8wrISDI4u4dH4zqUCWLW057hB905pbTGTzxICaN4K3c9vU0SmNQlun+o8ni7j9zjdJIyeLaOKkIp1fm2jhp4Jl34+49JwmPu/dcZ/HMWHP55RFmDbuylVnnhcCHrNLbWPo0wtK4dQjYx22H6H3adpjFmquJ+8jaYZhPS1hpWALj9pnOV1q3j/xsPK1DXIqlK2Stv1NZeeTs0885ZryeLWGdbnqP7FeGvaY68JDEZY2nNO06cwu0KYWwUfkts03HQsNs7lhI3cZtx+bZ3L4IQ/iYiNPvpD9nsvake0ZpDMouef7x2XM++4f7Nqe91oF3y4bi2A0Z4LmzbOsqQA54rWRM39pvZ9bG6sBZyKdSemearsCQLtM2Wdu59boHuemazR0HlsSGZPZwIdB0P3fcUTuYdcAW8Nz/8/UK1z8YX6W3fw229g5mbbQFZhrllbbfdIxk7eeOkUM7uO2wYLXtT6+N/+/+7/5bnTo+fLAsQoOTFH+pTKGRR+JV9gb7RaI9VlFqyNEOOXfpIcNJjxyaJcSQNlMRrv6MBoGOUSqZzBDHOIJxmr4KcuojkyKm3r6MD4+RRyCsP/dRyaPkColGqQpmJCRvpUFCeCb6TOZBeg04JhZFXPyQWEpVUnnUFPXjeikilZTWDTFqFqLv29W45tAbIpcy8hKSImn5yFTyBEnx7w90jIk=
*/