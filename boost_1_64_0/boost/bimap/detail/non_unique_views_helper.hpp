// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file detail/non_unique_views_helper.hpp
/// \brief Details for non unique views

#ifndef BOOST_BIMAP_DETAIL_NON_UNIQUE_VIEWS_HELPER_HPP
#define BOOST_BIMAP_DETAIL_NON_UNIQUE_VIEWS_HELPER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

/*===========================================================================*/
#define BOOST_BIMAP_NON_UNIQUE_VIEW_INSERT_FUNCTIONS                         \
                                                                             \
template <class InputIterator>                                               \
void insert(InputIterator iterBegin, InputIterator iterEnd)                  \
{                                                                            \
    for( ; iterBegin != iterEnd ; ++iterBegin )                              \
    {                                                                        \
        this->base().insert(                                                 \
            this->template functor<                                          \
                BOOST_DEDUCED_TYPENAME base_::value_to_base>()(              \
                    BOOST_DEDUCED_TYPENAME base_::value_type(*iterBegin)) ); \
    }                                                                        \
}                                                                            \
                                                                             \
std::pair<BOOST_DEDUCED_TYPENAME base_::iterator, bool> insert(              \
    BOOST_DEDUCED_TYPENAME ::boost::call_traits<                             \
        BOOST_DEDUCED_TYPENAME base_::value_type >::param_type x)            \
{                                                                            \
    typedef BOOST_DEDUCED_TYPENAME base_::base_type::iterator base_iterator; \
                                                                             \
    std::pair< base_iterator, bool > r(                                      \
        this->base().insert(                                                 \
            this->template functor<                                          \
                BOOST_DEDUCED_TYPENAME base_::value_to_base>()(x) )          \
    );                                                                       \
                                                                             \
    return std::pair<typename base_::iterator, bool>(                        \
        this->template functor<                                              \
            BOOST_DEDUCED_TYPENAME base_::iterator_from_base>()(r.first),    \
            r.second                                                         \
    );                                                                       \
}                                                                            \
                                                                             \
BOOST_DEDUCED_TYPENAME base_::iterator insert(                               \
    BOOST_DEDUCED_TYPENAME base_::iterator pos,                              \
        BOOST_DEDUCED_TYPENAME ::boost::call_traits<                         \
            BOOST_DEDUCED_TYPENAME base_::value_type >::param_type x)        \
{                                                                            \
    return this->template functor<                                           \
        BOOST_DEDUCED_TYPENAME base_::iterator_from_base>()(                 \
            this->base().insert(                                             \
                this->template functor<                                      \
                    BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(pos),  \
            this->template functor<                                          \
                BOOST_DEDUCED_TYPENAME base_::value_to_base>()(x))           \
    );                                                                       \
}
/*===========================================================================*/

#endif // BOOST_BIMAP_DETAIL_NON_UNIQUE_VIEWS_HELPER_HPP

/* non_unique_views_helper.hpp
BW0ONuo3ka+U3gc8z9WuNotTwezY3A0jM2I6PD32p7jqTcduSSMnONryH/WlaTS63Knlc7MVHgyr2VHvgE2PyZSf45M40w/V7/z5OGXIO37S5N959BExY4VKlWC80cpFLRchxrpPaRDlsfUROlfVFWJ+Nv04BywJRmhj/+nx3iOcrR1dQzHgiD+SAHLw604Z/VYxJcqQ/IxZNhZ2pjaejAtbcoxFuKZc/DV5WAu7MuCewfGkkkOpaZDQHZ4Hj2UTc81CyprF70VO+tcSalUk9pTCrw2D5z8BuZrEdpY2o18n6nsm3NsNXHrl2Yaro0ioE252bKLtyadOD39Pzl1Ml8eEdJArgoZJb83cx1mh3092oYrjCTO8CaxV5/ZVZKZJse/W4ySZhhe7ap1MUdxzOjpIOBETe/BtX53y5JkvKIrAIudOAUPp/nWZT4J0pY7h9qVhTlBwrHxLccyLumsGwKYz71f4fzqF4UJyMuX12UQxz0fx8oR8op6D+ex+mM/QWYj29FFNb/gqCd25GbWuZZqxiMHMYHxiZRAgUTl1xKSOESsnc+FeWq6eZw==
*/