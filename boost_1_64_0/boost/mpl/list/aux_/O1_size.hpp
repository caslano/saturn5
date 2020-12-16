
#ifndef BOOST_MPL_LIST_AUX_O1_SIZE_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_O1_SIZE_HPP_INCLUDED

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
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct O1_size_impl< aux::list_tag >
{
    template< typename List > struct apply
        : List::size
    {
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_O1_SIZE_HPP_INCLUDED

/* O1_size.hpp
MVtNu9QZuPMNg5LXGVzSrEtlvNAhH5dd5sO9di2eOoYbW8cQtEKZ/tBHR+scnDto8ZS6q7ct7n7ph79fHUPUXG0dg+vvRpfHNpo6hjNzXNcxPCr3do+hL27HuvgEBuOT2AR3YDTuxBjcZa9j4Pzluo5hhSx/FfrhavTHNdgS12EnXI+jcAOm4EZMxQfQhJtwEj6IS3ErLseHJR0JhHyHfFbAIZp759LYDStgjKSrOzbAHtgCe2IH7CX57Y09sI/9Xp/zk+s6iOclnt1YCV9AH3xRynGPJr0+kt5RTtLbTtIXLvNFYHOMxDDsiF2wE/bEzhiHXXCYvs6Ec4nruol9kt6XJb37Jb0HpFxekeUwXc4NzCPLqYG7ZDn9Jb0D0BcHyXoejME4BJvhUE0dQVccIekeKekehQk4BlPxDszEeMzBBJyOibgAx+FCTMKtmIyPoxGfx/H4IqZKPgoNcp7AS5KPOnhW8jFR8pEh+ZiEQZgl6yEbQzEHO2AuRuEUHIBTcThOk3xMxwk4A9NxJs7CWTgHZ+NivAvvwzm4HufhZrwbt+E9+BzOx924AN/De/EkLsSzuAi/xqVYiAV4Supa0uv8vepa5tfx/r+vb9lAGewlnCFcJdQK4F14Qj9CKmFugKe+5X9x+DPu/9O5MboR9//15f4/QXf/n56WaSSCFH7AoNQDRGvqAUJd1ANsmm2vB9Asoth7Hy9i6GJ7hu2iHiDKumz7UtXKgBvz/Tp36gLaSxo3yf3mh1hZ/JH5fKYWSaNaTxFwrbTJexA5M/TvRQyZYX8v4sR09b0I9d2GU9OKviuxdFrR9yLOTi36HsODU4u+x7BSnRZhGR+ujncw+DHe2pqeDArelKR0QGHKcrtci6vLCIzk9zl56j1YNSf3llmEaoyflW9UJLMvMEnu4/TvM1yUeUzjsi3vJyyylB/j9Q26dRkg9/BZsr1lSt3BjlmO65JKkxI+x05ETf4oH33c22VBjnUoR/Mc46Yi5Q98i9LdehRbeprKvflGKYu1UhZnZjqmR6lMKVlZUJfiuK51cW+RuOtLWQRJXcqmImVhzr2espD6FF3cMfKNPcc2FkH6uOVbOiXMt8H9OhVNewZd+ubK9/Aay/GmPl4kfaE5DumTihMlfUF/IH3Xqjcp1NWL6NdjNc3+lmLKzUyWeS5r+o33M5Su2otyNpOXO73IkyXt9u9MKhGa5Xe+/CadYOYHv8nv/PjdGds+nZU2Pt7Em0iy/RIs+/iwyZp9XOpqojx1NX9aXc2gFZb07K//dETh8Li6n/2QO8139RLXdTWTvZXpj4+cNuJiuSVbZ22rfubww8te+++tw9k023UdTojci7fA8thSU4cTNdt1HU5T6ePyNvTF5lgXQzAYW2ATbIXR2AZjUO2D1kuuO+Q6RFl+jDK/PAc4KPfEb6IvHsG6+C72xPcxDo/hKDyOifgBzsYTOBc/xMX4ES7HU7geT+Nm/Bgfw0/waTyDR/AzPIZn8SP8HD/Dc/gTnscqpPkC1sAv0B+/woZ4EVvh1xiO32IcFmIafoeT8HuchpdwNv6E8/HfuBQv40b8GffgFTyIv+Bh/A2P4+94Cg2U7+elAEtTll5YHsuhH96C9bA8dsEK2AcrYix64wishElYGefhrbgSq+Aq9MFNWBUfxOr4CPriP7AGHsSa+DbWwgtYG79Ff/wOA/AK1sXfMBAD2B6CMRgbYCdsiF2wEVrbj8i1DmY5aT/ST7afgVgdY7EmxmEQDsJ2OBj74hAcikMxHodhGg7HTByhbVeU57ourn0paVeElTAcfTACm2AkWvuilusT3CjL0fZF3UHSH4nB2BGbYCdsjp0xBrtgP+wq6Y4=
*/