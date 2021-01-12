/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_VIEW_IMPL_03202006_0048)
#define BOOST_FUSION_IS_VIEW_IMPL_03202006_0048

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion 
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_view_impl;

        template<>
        struct is_view_impl<mpl_sequence_tag>
        {
            template<typename T>
            struct apply : mpl::true_
            {};
        };
    }
}}

#endif

/* is_view_impl.hpp
bXp9hpkDWcnJIarYGee3i/bXbzdza81aPT7k4xXOW61SaqXcm2nvnSlxeZPvCCuNd8MkX1OuX3Iy8924fi9zfWaU9XfGrVPc+8LFz1MlD+BO/LvGdwZ7Z0XzRXqRPBOe+85lwnniZrVvitUBN+iMm0Szv1Mp1821avZdq0KglOFzEV3DZ8pzzNCU7cJj0mtzQ5ydW9RcoefMGg3PstuMu0kcnYCU/AN1z1rffDP5Nl5v8pu3
*/