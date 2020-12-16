// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/map_adaptor.hpp
/// \brief Container adaptor to easily build a std::map signature compatible container.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_MAP_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_MAP_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/ordered_associative_container_adaptor.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/call_traits.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {

/// \brief Container adaptor to easily build a std::map signature compatible container.

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
class map_adaptor :

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

    explicit map_adaptor(Base & c) :
        base_(c) {}

    protected:

    typedef map_adaptor map_adaptor_;

    // Interface --------------------------------------------------------------

    public:

    template< class CompatibleKey >
    data_type& operator[](const CompatibleKey & k)
    {
        return this->base()
            [this->template functor<BOOST_DEDUCED_TYPENAME base_::key_to_base>()(k)];
    }

    template< class CompatibleKey >
    data_type& at(const CompatibleKey & k)
    {
        return this->base().
            at(this->template functor<BOOST_DEDUCED_TYPENAME base_::key_to_base>()(k));
    }

    template< class CompatibleKey >
    const data_type& at(const CompatibleKey & k) const
    {
        return this->base().
            at(this->template functor<BOOST_DEDUCED_TYPENAME base_::key_to_base>()(k));
    }

};


} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_MAP_ADAPTOR_HPP


/* map_adaptor.hpp
ofv6qdY2m5k8nYqV5m5uaW5hAemk+dqnm+mjnY86Wnt9J861E86X2nqmibOBGe7GjosYTY/liG4x8wWsZ80ks74WkigHfce1Vp/6mMnLq84k1Xv6Se9xp3UdDzLbmuKMov4EqU854rlv+lH7DnNuOGr6Dmt+q7oyrqXyG3p5+uUjBw32WuZ0LRs0+MqhAwdbywJcyy4ZOoJ4Vb+16PkHjpO2YuZy3GOsolZe9W5GgRll+da5Fp55LxP3U1ohitXYQmwHpr5J24pweI+DIlW2fzbrljriuPrlYa45E9c/k7Zg882cyZWhwSGOKnO3pi0rXkUzz5zJRb5zJlacGtHW2Gqb79jKGif/COfT1b5rt7bGS5YuavJPoIv6Y+mK+tdXrU7ntHp91fmBruX3XflSjbqLvn209fq9rePuGdavOt3V6vRDz1+HdJXRb+2/5ERYzspPfpaxfPCOT7oXH/vx9FL967pWpw9bvS7tzgCTz5jsEz9Lm9IpcOaUOvM+zn4TLTez/M+3vvfKgOzce6//Ys7kx1s/FMR4XPPZBDNPvIPjyQsy88jm9/og97XzJL/fcrjbRIxrLorfZV6/r/P6Pb/yt7nvdPXPH2PSJtD/is3/kFlXVZtgrLQiroS14Dgv7cUKpWOT5KeqRsk+pXsLBsD9sK40JRvDA9KifAdKk0b/yzT/v+VYq2rSPBbk1kBbD0fBDXCc/PHyJ8rPkO/RPlnp+T+ijs9b++SvTpNPysOdr09gC/kd4acwHn4mDbK/wa7yPVqdFdp+pMt3VtXqJE9WPEf8ucWLOcd4yecQrxc2SfGyVK7eGh5f1HRrOJ2AHeE3MA1+D4/BlQ7P/DvrVH7hcLnSr5T2yIPS0noE9obl8FL4OzgC/h5mwHUwBz4Gi+HjsBSuh2XwSXgj3ABXwY1wK9wsbcu18FP4EDyi5dIa0Zyzmb8mn1W1Rr53ujWq6gS4tb1C4YWwLrwK1oMZMBzOgw3hL2Aj+DCMhE/BlnAvjIEfw9bwBGwDT8FYGMS+28K2sB2Mh53gQBgPR8AEOBZ2hpNgIpwOL4A3wt5wKbwQ3gH7wN/C7vA+mAQfhj3gH2Bfacrt88wBav6RcjB1YKe5ZSQ+5dAA9oRR8ELYEvaB/WFfeDFcDEfAfvAK2B+Og8kwFw6A0+FAOBMOhrPhJfBmeCn8JRwKl8FhcAUcDu+Bl8H7zLjHfZ5T4AvwCvii9r8bjoFH4Fh4HF4Jmzrph2AzpzteJ3gV7AqvhhfACXAcnAgnwHRYDCfBOXAynAcz4Y0wC/4KZsNfwxy4Ak6B98BceD+cBrfDa+BhWAiPwOmwBuVdDIPhDNgJXgu7wFlwMJwN8+HPYBGcD2+E18Gb4AJYDhfCrfBGuAsuVn/zkUNzXfBS1fMo05+6Q7o07ybBlnCytO2yYHeYDfvDHDgIToUpMFdadtNgCbwGLoF5cCksgA/CQlgOi+AmOF1atCXwGVgK/wBnqJ3+DAY4OU7YGF4HoyFt3bSP62EHOBsmwDkwES5Qu15szcmYOShzvEarT/V5idOtUbUUupbfArvBW1WffwUnwNtgFrwb3g3vgffDe+HDcCUsh/fDrXCV6uHt8HX4a1jDyXUbhsA7YQf4G9W738LRcDWcCNfATPgAvAY+CPPhQ/B6+DBcBB+BD8ByuA0+BnfBx+Gf4BPwAFwP34dPwr/BjfA43ARPwadgIOXzNAyCm2EY3AKbwGdgS/gcbAe3ws7wedgDbocD4UswFb6serpD9fQV1b87HZpXgCGqf2Gu86D6t9O1P7gbRslvLr8XfAMOkH+J/PlwL7wJvgVXw/3wIfg2fBkegK/A9+Bb8F34CTwET5jl0qDz3Hs=
*/