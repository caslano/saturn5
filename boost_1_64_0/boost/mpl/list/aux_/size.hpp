
#ifndef BOOST_MPL_LIST_AUX_SIZE_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_SIZE_HPP_INCLUDED

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

#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct size_impl< aux::list_tag >
{
    template< typename List > struct apply
        : List::size
    {
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_SIZE_HPP_INCLUDED

/* size.hpp
XglSXqkYiWkYhROwD6Zjf8ywtYk2yLUanpPlV8WVsvx4SV8CBmIyNkIjhmAK9sNUHIRpaMIJuBgn4jLMwNWYic+iCV/ALNyDOfgh5uJpnIKfYZ7af6RcV+EyJ/Wss6Uc5qAf3o1BeA+G4RLshUsxDgtwIi7DObgc5+NGXIz3q9/lleshKfM1Dt/lfVzifQPr41vYFA9jd3xb4n1HlhdL2CTLGyrLuwVjZHltpLzboi+2R38MxyCMxHAchXE4Wn3uIdcVGOjkucdm2T4fwkq4RcppKwbgNqzkxXwN3KtTDv25ouHU+YqGWEz/uaKnjrmYOuZdlKureuZKFyq6Xdd8qIH3H65vPsm8lwi1GnobwglDCDmENYTdhGOEQoJPI76j28hTF+0ZPINn8AyewTN4Bs/gGTzD//PwJ7T/N2dRCX6j2v/31zznj5Xn/OHyrCCMMEJ57ttSfVZgiTulBM/8rH1qmdTnBFUZTzFlZSTmFHlOoLbJNVufe1BFqmtXzAhB6hUqSzpHkb4Ee/qyM60pdDt90oeZ+kwyl5Bpe3Z2nekNkefot1KuNdGAY0jvDnt6J1uTK98JLO/euxTulK0t/fa0SX9q/3ZIP+N3kKbU3PFGW19ul5iWa/1NulHaW1+UafI75TGp9Xt8sry08ZkmNlvrs1SmKfEmT83kp9b5L8g0md9scGhzcFXKKlnWbQIhXtn2Qu1lZVu57jwj/SPrV9qJ68pM1rG+PDTPgnOycjOTeACZLPlpKf2bhctzrdSK5EdMVJ7lW/NDQxtzli0fzKsZnPcXuSVS319kqsN4lMN4iMN4Ld04g8P42Qh7/5ONItRvQarfm/wlXJ2m9g2ZpU4LV/uQ9LdPU/uk3NlBnab2PzldndYhwjbt1/bqNDWOS/Zpan+Wk+3T1G9fZqjT2qvL+7adOk1d3uUw27R29t/Zp6n5aG+fpvZx6W2fpubjfFu1r051eW/bp6nLW2WfpqZlhn2amrc4+zS1v80jbdR+PtX1sck+TZ23uTqtjZqW0vZp6rznW6vT1HX0ln2amr6n7NPUOFbYp6npS7VPU8uqVmvH/kXZH6UdV7b0Eatt2yWT1P0yV+lbKTGP/U3dL5mm3wdrMS2njGYflHgCnOzXQU7268ua/idt7VJ+ZzArbclTrXHsleM7bX4mJ6bn8nxb34doRlqmZVkXZNzSGkGWv4Fp0cryZU7LsVWOJUm5WVlkRNd3KPm1/KZQxpMkYcq0LUyrzjTLoqQdh4F0FVCogcr0cHt7h938tmoZaz+GHJPU3+4tb31+uU7z2138tpqT314orzwXYx7Nb3coaXDyW98K1vffPtH8druSB/tvre1j2lj/7u1nfUZ/TB3XHzt3y7EzQs4F7QhJHDs3dVZ+XypxXHY8xVD8NUg1Q1XLNhdN8LOWHFa1rHfrNFpk5aZT1Pq+KTdVtC7kqLR/O4xG4i+0xp9sSjRnxdMJZlJq8W3f/sh2L9uGbPf6feFW23ZPSJLtYC/ltYE0t2U8rCtpRO21SU6GmWgsedSVc0JleX/uFq5P8CiOV9q2RFnymZKRw3lazlHbDO5dm9zo/FaT/Gr3o1tlf5b9zzLeUMZt+1BTGZddyDItBK376NR0I/rJfmWZxgWMum/J/tyPo14ab1FONmapbS83qdd/iemW5ciyC2T6NHNisi0va5hWn2lcs5gTWYQyLV+mkc7WoTLvDpnXaE5PTDJa49kmv0vJSkyyzCy/3WVrByS/VabtlWkStWX+Y5L+FEm/bf5U2fZzpTCV386XaWwnumPcBulX2ZhntvxuvyzT6LDM3bbjqC39bJNb2B5D2b6mMD0yxr5NrpTfEheLtWyT6u/H8Ps=
*/