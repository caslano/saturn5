
#ifndef BOOST_MPL_AUX_ERASE_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_ERASE_IMPL_HPP_INCLUDED

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

#include <boost/mpl/clear.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/reverse_fold.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/aux_/na.hpp>

namespace boost { namespace mpl {

// default implementation; conrete sequences might override it by 
// specializing either the 'erase_impl' or the primary 'erase' template

template< typename Tag >
struct erase_impl
{
    template<
          typename Sequence
        , typename First
        , typename Last
        >
    struct apply
    {
        typedef typename if_na< Last,typename next<First>::type >::type last_;
        
        // 1st half: [begin, first)
        typedef iterator_range<
              typename begin<Sequence>::type
            , First
            > first_half_;

        // 2nd half: [last, end) ... that is, [last + 1, end)
        typedef iterator_range<
              last_
            , typename end<Sequence>::type
            > second_half_;

        typedef typename reverse_fold<
              second_half_
            , typename clear<Sequence>::type
            , push_front<_,_>
            >::type half_sequence_;

        typedef typename reverse_fold<
              first_half_
            , half_sequence_
            , push_front<_,_>
            >::type type;
    };
};

}}

#endif // BOOST_MPL_AUX_ERASE_IMPL_HPP_INCLUDED

/* erase_impl.hpp
5D8o6Oa6gDmWMdziJVMOREv8YNUpyVOFgrUcCtZy7MT7tHYm506N3PmG04a5TPFP2ASTEl+NLyL64mWolaRuwphcENlSIRBtHWiCPdbA1tJTaGlgMHHzQo31MBK0RYJkEGPPdSjVArF7tT0eBNIid/+szZvEX3Xzlb92e3f+rtD6upy7QM+g6YJmWVlNbqXmhScRXL44lD5zZDUyNqkDDWM/IkOyUmH0td3C6xdyxkfnX1bcG5l/+XRI5PcNo+g/XD1C81s97w/B/1WjvTcOiY5v/6OSbofi/+7R+av6F2y/w2avUGb3L3CPtPta3xHev+C+ZMu/4HK7f8HEZKXdJBud8re0+tFuo3M+yMDd+2qzn27SjkT3zHeyvEQcsT3Bt+yqk5d+ImD43IZrj3botRfS4XVRyK7PYoMKaQw7CpetnNqinDSy0PHsUXfcJ5kODr+Fb5bCakdpYE1zFO1CC3n2Dp+DwsPbrrelguzub4ecsI24VToR1zGLPOyz7pDAEI2kq4LIUWpzfEmWo+1/UV4rO/nGonW+a1TTdg9VaNsk52GlOIAtGt53VixNf9pH8zfjRit5vNGPumHDMVWXsUM4p7zGEPG6j1dJ9LRv5np+XzObMeBbvRV83+0d/Ntc11bbv48MdV+d3xb27yFvQND3if4V3C75t6+uU4wkNPAtR0iuN2nuKxyHUQwHlrEpdmKBCJr/QbyNrYLIttx/glOL3ko9gCChvo6Y73bjbJx/Ba2XTC3v6YiloA+orQNkc0whlpnsakSG8ZeIhfUompFIEr4TZE8d3IA44SV1Z2BuKD9pd/4jgsUh3aJlE385ardefVBXMTYgRLTvzW9qVa3BFXjhbK9S4JkB/5CmVoblpaC4jfBfkRNRjveThAorrFM/dUOwj3hdHFub77aPOBG+py3vcOIKYHsHjykxnH2uD1oDI69Q8Z9HiikSVq3mRXfazQOnx29JFgNN3GFpXvp+GrG8zKO8PIoGmq/FybEzDSFrAx3AoKZfh0aRlA4jagbi/ded2dNfrP/ic7T+c3io/fG2eG82yIqMf3abwkNPUGGSWxA0s81Ytbfy/GyNXegNE6X6pQS97Caz5XYimQ4lqNWlytMGuijy4G2W43buFfHZjSXMgIsPpGK+6QfqIwE/G3e/ZbaL42xgKzzwjzuTbkI0PiraexNfDFbhgvuVw4dcFKPg6c8pMIQPVE5xNQ2C2H7XeLr19EyL33KReHg+lIAeVgImst6GMo8sk/eJLE5XTWD/Kvi/wzGfcGktZ18Vtkglq/qZh3EzHGkZL0y7VH1vnxxLsgYYZ8HW/8KsZltx0u+uoHlO2uF15P5woWpaCxXZoaJh6gnIpG3N/kmrXN8nPh4Wqv2+HqjNkoCX0RMiAvqJOvUlEf2tvElkX6v7k92dSoPuv5t72nnqe3t3bPpJGxts6xDGajp3ahIsZK8nqtEtvTzrCqIW7QWXUtq+z8luB1XPBxORaA/Kg7LsHI9K0pFKUL54pRxK5owPZbU+2r963K04HzHeJbj/8tWALExxEsLzrYzOBleWh/71qGNqBo+wO6su/ZuWFY+ngfFEdQ993i2zTHVhOM9lLLFW6aUh4ujQ+NE1jhT+JTQPSZvFpeyf7F0LfJPVFU/SFEIJNEAKtRaoUBApIAo4oKCAVBlaLMWqY1NxQ/0W0aGkylxbwMKk1jp0vkUFQacOJ1NUVFRQnooCiloVXMEWv5i61Vm1OiQ793/uvd+X9JWCzr3qz5Dc9z333nPPPc+EHPri6buL8CZ/VWmOvluzd6mG3eHnjgQ6lv3TdO1/t0kzA0EA7mhnOcao0K6UkVWvr09gLgAw2xl0hZ9XPnI=
*/