/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_SINGLE_VIEW_VALUE_AT_IMPL_JUL_07_2011_1348PM)
#define BOOST_FUSION_SINGLE_VIEW_VALUE_AT_IMPL_JUL_07_2011_1348PM

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>

namespace boost { namespace fusion 
{
    struct single_view_tag;

    namespace extension
    {
        template<typename Tag>
        struct value_at_impl;

        template<>
        struct value_at_impl<single_view_tag>
        {
            template<typename Sequence, typename N>
            struct apply
            {
                BOOST_MPL_ASSERT((mpl::equal_to<N, mpl::int_<0> >));
                typedef typename Sequence::value_type type;
            };
        };
    }

}}

#endif

/* value_at_impl.hpp
/ZqZY09aq178zfJk/ZgCmdvzDDAO+YI2DBecQ6LBgP5tVhhGOVYUSnA8ICVK7fGyhqw2Feb+8C2E9tFo4XGxIXc5sWNIYM2CePJ2cZDl8UFEtWPbAYeMJTDMhePIRsZgEEZrsk/XoUAbop/Ow8lOsA75835iqVrcDiahfp149FMUcgFMlgVDahLUX75733HsITzS2rk3wj1Ma/IsQM08BIiJjJwI+qH8h1tdanOiDmho1Kan5gvrbypVM3DLxE7urHQHTQfFswyfXnX0mLXH0sKadhDrpcgFJ0lWwZpZ870GIyypxISlY6lR6bVjbvsYAyoS4rP+bnng8PLm2m154fXpWMF4nRwgOMzjYhGsQU3d9e/W36H5lnTrgh7lMjJn9s5U4764K7nGG9y42dB00lfpLYrMBFU5jYyhEmbMEBqbiNxLDGJW9aowxsfVbsIuYaLPLEZA4OX5noo1XwM/K+hLksDDjGL0IIGm4c+aayIyZouhGW0wHCRClVJgS/9U/zJNccuSyqRRTsD2/hOMPxztG6sDhE2wN6ckeoBY8qlJdDw2Hun+YMKwvA==
*/