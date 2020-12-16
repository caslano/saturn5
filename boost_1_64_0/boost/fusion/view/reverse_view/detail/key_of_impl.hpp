/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_KEY_OF_IMPL_HPP
#define BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_KEY_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/key_of.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct key_of_impl;

    template <>
    struct key_of_impl<reverse_view_iterator_tag>
    {
        template <typename It>
        struct apply
          : result_of::key_of<typename It::it_type>
        {};
    };
}}}

#endif

/* key_of_impl.hpp
fLXO4EUT49kMjd53gRZEq8iM3neBZhuG48mM3qGB5kKLY8Z/99+NJvprrvSK6s+PVpEZ7w+GY3/MeH8OtDhp0ffS0epFrAXm8qzw8t+E+dF6MFuQPnuSMMcIPbRntq/N6ynCAmgdYqRNfbp9D9lomQta9OcWaKL2lsr3snY03RisnRnVjuZCK86MakfzocVJY/21Bz9auoi1UnqANe/wU8ICaHpmC71vDgoLoemY0fsq0cCD/Ulj/fUFnUfW11pxy/rQnGgVmVF9aD604syoPrQQ6w+N9VcOwqy/Nsog2R+afSz2x4z6Q/OgFWdG/aEF0JYr0t6OGlJGWHCcen+68ermRFPLxYemlktIo03bBHVzoan150dT6y+MFseMjzVMVDedhtk0zK5qfcCBNiD2q7VV+sJ8k/GVMO9UefxDk/cn0GCaHq4p0joPzKYX5pwRHUf3EtACaFVjyHAf1injV+sCPq8c63Z8u0ULoVVkRmONZv8Rx5oZjTWaGy2OGd9HetAaR6y9Uhhabl5jEBbWMNfsaOvaskxYWFDDHHP0MJjZudyt2wkLob1gdsw/cJow3Tw9VGe2I+fOwsLcyWxtmph0lAvaSGbV3tfbTXHz1U23QA/lmPmS0k7+aoPBhaZEzIX7CXqXEJobrWoKaTnrPGkhLLhUrgk0di7VBRzL9PAssgY7KCXAbtoWS3O7Uo8ZSRsR3/aUMD/ae0Xax1CeVxS3Bu97szazxcNZYa71Mhc0lksvCKLNiVhHPO9JKnlwvDDvBmmd0B53z7Kc1vxGeYzrjGPWYcCx88JCaHmZNT9VYIUw3SY9OJk9LZlujjAP2npm21cf/0mYa7Me+jNrUK3SKGFhtCqKtMLLn48R5t2qhxMsrva0e1Yyf3Sbf37qn1KYbRteczGj6z80B1p7ZjX3DiotLIDWmFmRAf1/EGbfjnPEbECLDW+F+dB4XN0ML/+gMftFDz8wM7erXJz6Q6vIrNbiDdUoboe6uTTMr2GwE68feA3HboyhNtGKMxta+cpYqg8tgzR27YT9oTVg1vVzqns0D7v08CezHBOzZRDm3K2HCcweNrtgEAZ79DCGWX5/TWrTl8zCJealpbndi/sJZtM/5GkvLITWnNkBQ8GUlMs+PdRmdmHjxIxUXzJL0+C7ujRHv0bbv0dTFBHmTmZrZ3/IJSyI1oxZ7iv9FlIN+/VQjNmj+Lo3hXnQSjMrkD3VEGoTzcksz+be8rh5QA9JzEZ9fveY6kObzaxHfU+Iajioh97MHK2r03YLh/RQR5HW8tCf1KYvIK/V0OS1GloIrTOzHZlX0O+2uA7Lz5K7KPhe+fVD9woLoe1VpE3KP6+zMN1RGdc1WZwX7aIi7e3TsX2pzeN4vzXmq3VDa7W943+EeU7p6bv/3dH+WdyU3rsVOoOf1UXs+/+/b+2I20b2e+Qz6Ih9WtAvm7Dgucg9/4jtWWq4IMwfjI7b5hySR5jvgh6Gx0i7PLLDXWGBy9G5FL9lCZBdjW5zUukKU6i/a3qYyOJuV0/oSf3d0MM2Fte+ZYvZwjw3cTyZzVvd+7Ew763ouKTtlW4Lc9+O7m949l1/CnPdjY6rVKXuAGGOe3Jf3iPZe7BcaDWY9d16qBjVjmZmNnNdrns0R2hWRVrXm3VihTnvR3KJWL2Fh+Q7Ux/oYTezj1fqTBZme4i5sDbrZ76RinJ5FN1m93Y35TtMH+P2zuzBxNXDKU+03sx2FLE2pfF8gsfwSH890Qofi6tGY/YfPWRn1nb0suU070/1MJnZ3aEb01Muz/UwHaS98TYZQePyAueBGd3HRHMnM7pviuZNZnR/F82fzOT9XWwDLSMz+h1GtDDabGbrRy0=
*/