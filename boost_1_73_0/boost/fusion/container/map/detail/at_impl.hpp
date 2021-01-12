/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_DETAIL_AT_IMPL_02042013_0821)
#define BOOST_FUSION_MAP_DETAIL_AT_IMPL_02042013_0821

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/utility/declval.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template <typename Tag>
        struct at_impl;

        template <>
        struct at_impl<map_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef mpl::int_<N::value> index;
                typedef
                    decltype(boost::declval<Sequence>().get(index()))
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& m)
                {
                    return m.get(index());
                }
            };

            template <typename Sequence, typename N>
            struct apply<Sequence const, N>
            {
                typedef mpl::int_<N::value> index;
                typedef
                    decltype(boost::declval<Sequence const>().get(index()))
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence const& m)
                {
                    return m.get(index());
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
MTYtb/3EfqHX+wdxxz7vpjA+HX0evS3nQ77Bdhz786/3fGaaOMyzm6ea6znwezk/lfn2faTfMxwJQ05X2j7mRA8w8em5mPHbkoJZzkt5Uanpe7PhA9MkDlZQh22v5607XYki4Sm1+pkXSfhjKZsttS3nmSZh2vg24voyz8chpE/fSTgmmeeWT8L+aPfmDraw411jcVPKS6eLDKWN+YnjI4mzlfYpR8ZXonX9fTmf7etvu/t/
*/