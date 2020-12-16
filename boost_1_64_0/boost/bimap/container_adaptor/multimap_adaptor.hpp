// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/multimap_adaptor.hpp
/// \brief Container adaptor to easily build a std::multimap signature compatible container.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_MULTIMAP_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_MULTIMAP_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/ordered_associative_container_adaptor.hpp>
#include <boost/bimap/container_adaptor/detail/non_unique_container_helper.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/vector.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {

/// \brief Container adaptor to easily build a std::multimap signature compatible container.

template
<
    class Base,

    class Iterator,
    class ConstIterator,
    class ReverseIterator,
    class ConstReverseIterator,

    class IteratorToBaseConverter          = ::boost::mpl::na,
    class IteratorFromBaseConverter        = ::boost::mpl::na,
    class ReverseIteratorFromBaseConverter = ::boost::mpl::na,
    class ValueToBaseConverter             = ::boost::mpl::na,
    class ValueFromBaseConverter           = ::boost::mpl::na,
    class KeyToBaseConverter               = ::boost::mpl::na,

    class FunctorsFromDerivedClasses = mpl::vector<>
>
class multimap_adaptor :

    public ::boost::bimaps::container_adaptor::
                ordered_associative_container_adaptor
    <
        Base,
        Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,
        BOOST_DEDUCED_TYPENAME Iterator::value_type::first_type,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        KeyToBaseConverter,
        FunctorsFromDerivedClasses
    >
{
    typedef ::boost::bimaps::container_adaptor::
                ordered_associative_container_adaptor
    <
        Base,
        Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,
        BOOST_DEDUCED_TYPENAME Iterator::value_type::first_type,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        KeyToBaseConverter,
        FunctorsFromDerivedClasses

    > base_;

    // MetaData -------------------------------------------------------------

    public:

    typedef BOOST_DEDUCED_TYPENAME Iterator::value_type::second_type data_type;
    typedef data_type mapped_type;

    // Access -----------------------------------------------------------------

    public:

    explicit multimap_adaptor(Base & c) :
        base_(c) {}

    protected:

    typedef multimap_adaptor multimap_adaptor_;

    public:

    BOOST_BIMAP_NON_UNIQUE_CONTAINER_ADAPTOR_INSERT_FUNCTIONS
};


} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_MULTIMAP_ADAPTOR_HPP



/* multimap_adaptor.hpp
6h6b/Blt9vedyp80nHdJE/KPsB18U+3hz9JoTmR7V2rcMkPjljkat9ylcct98D3V+w/gC/BDaTH/Fe6WluWb8DD8ELZ29RvStvwcfgW/hiel1cxvU8++gcHwW1gbfift5u9hGOQAaU8ANocBsA0Mgu1gLdgF1oS95PeBIfAiWAcmw3ZwAKSPNdqIX0ij+TicC8NYfx0MhwthhOptA3grbAhvh43gXTBS/WVjeB9sqvodBdfCaPgYjIMbYAf4FOwIn4Wd1A7i4cswAb4GO8PdsAvcA7upXSRaWrq6/4QOnXdLS1canRHw5xp/LoY9pM15AbwbXiRtzuFwCUzR8ivhL+EUaXbmwVvgLXAZvFXx7oC/klb3bXAbvEPn/074J8V7G/4WfglXwG+0nGu60ReqMeTMukToEBndoVjipRS59YdKsb74O+A+7DgWllCpOTQE89EaksZQVX2hZEtjyNIX8qstFIdNYn9joF9NISyYQcu8m4ONtlA81gt/CObRFiojva++0B7sMHYKu5P13ppCWV66QuVubaFz0hVaiJWzLW8NoT2YozvHxnJv7aBJ2DxsiZd+0HqEtHcSz592UF9shKUddGbNoGRLN6hSL+gw2w0bij4QNgjLwsqwFdgmbA92GAsdFuLoio3ApmILsbXYjmH2e8F2sEN1oQY27V///P/M/BLX0/8/7Nl/17P9M6Pd96xx9lziTzaX+N8+Z7jOacYN5zRm0FjhB48TznWMcIbxgcYF1njgTGOBH20c4GcMcNbr/7/ium8HO9jBDnawgx3sYAc72OHHDz/R+/9K8OPMAZTacwD2HIA9B2DPAdjBDnawgx3sYAc72MEOdjiv8BP9/z8vd/IPv/d3af99ykOJQzYY7b/snAxeUEtHws9oALq1/zKZG+gp/aMmuoWYidXFpkuXZ3cDS/vPS5Wn2ncJFX+8oxd5rSdtsg4NXcvC/eryRBJnuFe6OEddK+1wK22Q2d/TzRxVNFqGkC7YrG/AtvGt+M3ZboDe7arUMOjlfTLP4d2sM+neBJn9cK8cK90bleNC6Qauw+pjD+v93KKGVjnqxdx06+W9aspSaXJ5bybA0nk7aJb14DnZSL/vaFq6Uibe3SpHz7Yi/GplRKosXzRx+pu9NXU00nLPPgewJNxxIWvrUa4BruMK/+f1Ic70PuwLKtsnY93+Xsuvqtl1soZ7J4+ozj6APU6clEaVZY2kZDW6KIpH6o4c1zysUoMsMz8LSoNM8cJMummkm2T836JhEOyYgbnSRZh0eRnFU9zbn+q1/c7krgzz0myz4l3hFS/a0ZJn1xt6ypeyPWvdHea3fLVsiPU+KMejZSkummUmr2ZZqsPSeWOZu8wfN3nimXGVuaefyJO23pNYC+xe7AXidI20ypwMTJ6dkZVVzCqvYzZL1Ccovpcu5njjz/U6Bzl5GVNKdA488VsZv4D4Vxj/Np1bq1+wtDKuNuvne9X309vIYhNnkLVPX22ASWZ9oPGb4Gcqj553eqdEm/fCDaOiKt8BjTlLW+hqlbcpEx9tOnPcVbRIT6rMQ7WhOnrfNqaxVebuRI5qNU0UN/Sseq3SRfWqS1XbXLzEYZvq3d8G0lfp6pWX4uzs09ucynyAiVfTmc/ftZjyR3q972udi1zWDTD1epJZ97HRTztFWaysxVrz/m7ZZk8fnxxRVffk7w283s2Vfdfgh7yny7JK/UDTRhaafPE+mvqp5yy/apvZqTJLVj/VB3uJOMuaWGU2JfscrgcmPlvp5Aj9wdc272vWJj32m65r1jiHW6utwsqflNrSLak2X602S8Pha5NmINu2zq2209Sk+dS0VfcYJELXnRNm/VDKK9jq+/I=
*/