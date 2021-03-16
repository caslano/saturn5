/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_IMPL_07202005_0849)
#define FUSION_BEGIN_IMPL_07202005_0849

namespace boost { namespace fusion
{
    struct reverse_view_tag;

    template <typename Iterator>
    struct reverse_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct begin_impl;

        template <>
        struct begin_impl<reverse_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef reverse_view_iterator<typename Sequence::last_type> type;
    
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence const& s)
                {
                    return type(s.last());
                }
            };
        };
    }
}}

#endif



/* begin_impl.hpp
EeBmKipez8hXCSI9NqQTkV6qEkU6Vo5XpAd1X8AYVNYAlZ55aIopja6U8lDl3JqqmGVEnnx4bh8o7lHUD9f4QT8vlH0FdCjQr/1syH7Yz7PW3/r5OOzv/WzIflaAnQBdEuBTMI/jPk2gP/p54fcnoDjo6wbxjwFNDbDxXBrQF4H2BPoG0MwAL/z2Afqpfu5n+rk4q50bYMuJseh2w2I8A+gwoOhqZzjQgRofBnRkgI3rRgEdo/FCoP2B4qzBQKA=
*/