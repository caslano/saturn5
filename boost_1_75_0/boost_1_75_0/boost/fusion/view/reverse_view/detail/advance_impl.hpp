/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ADVANCE_IMPL_14122005_2015)
#define FUSION_ADVANCE_IMPL_14122005_2015

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <boost/mpl/negate.hpp>

namespace boost { namespace fusion {

    struct reverse_view_iterator_tag;

    template <typename Iterator>
    struct reverse_view_iterator;

    namespace extension
    {
        template<typename Tag>
        struct advance_impl;

        template<>
        struct advance_impl<reverse_view_iterator_tag>
        {
            template<typename Iterator, typename Dist>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename mpl::negate<Dist>::type negative_dist;
                typedef typename result_of::advance<first_type, negative_dist>::type advanced_type;
                typedef reverse_view_iterator<advanced_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(boost::fusion::advance<negative_dist>(i.first));
                }
            };
        };
    }
}}

#endif

/* advance_impl.hpp
S8TCD4H7UHJ9O/D2FY2rXOIm2FXACIZPnmluPDqPhXv15n+xIRaG8rUfTqkgVK5kOUH7PlNMF5pqqW/eX97K/noyEwgVciELRAKcLDEjL3UQDOS7ZsvE70gj/d5sgwiykkgDW8m0XFxH3k8xIR7YGe4+EEhueP2jNfOtIUBV8Y3V/FF0Fwwoabhmhjt95pmFicChPBKUK6L2ZLHLqC4OmwaJG/AW7Ns6gPO9n2ufODLnI9qITRWKxbbYhTJSwqp9BGRxM/CopMsdgynCBv7TmsKzIDzVD1VWiNxY/pxe5Hvkzn73cPXCt+SwZfG3wBEnXFJDCHuUdw7owK742VzXqpmLjJygXBbn6gbproZV/kFWfsr5ZaYByjOyaM6hb3Ab3v9wWsVi6Bv11lSC/Vdwu46topQqVindXpClmg6DOSb0/wDroJ9x4ojfB5YCBiI652MuMz+upVLzhsR3OL/9i/zfcW32qUgTrPBGYJHfu8hcJ+8RF/ZyHuvJ5VYehglRC1O4kwlb5hQGopvT/lW92WrMr/KX/ybWX8Ezqt0pRzGS9ch30ajRzpKjmNB5xvbepmBmubc+ZHFNsJhyrZevAE58L8k6J5kz6BeRu+vx5B3+TYrThThJCbVmky8GFaVE5Ut9z/AdGwYoyGX4F0zvCf7a2zqdwTFpB5ZQhHld9Ru9waYZ0ue6rg7IKmhQ4PMRA9wu//7ezK9u7401
*/