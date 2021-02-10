/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_ITERATOR_RANGE_AT_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_ITERATOR_RANGE_AT_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <boost/fusion/iterator/deref.hpp>

namespace boost { namespace fusion
{
    struct iterator_range_tag;

    namespace extension
    {
        template <typename Tag>
        struct at_impl;

        template <>
        struct at_impl<iterator_range_tag>
        {
            template <typename Seq, typename N>
            struct apply
            {
                typedef typename Seq::begin_type begin_type;
                typedef typename result_of::advance<begin_type,N>::type pos;
                typedef typename result_of::deref<pos>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Seq& s)
                {
                    return * fusion::advance<N>(s.first);
                }
            };
        };
    }
}}

#endif


/* at_impl.hpp
283az4qROU6Q2RPsIm7KnQX0rHWdt5f0XXOGbORKJ7lW6e7OqhMgD7VaRTMy4IktQWW7rX8My/ZmP8cUQFHvZegbPTz1ddxsukXif3fy5tnB4Q8QTgxk+aWw6BtyRzAC5hKqKywoOf0BCqnj8oFBqj9eFoR1WWmpcEwTwlRnABUDEbpYLwB+bCFGyozDfNu47Hq2csf0swHYNyaBpMV7Potv+k6qwNaGchgUkSb2teYgxloVDVD0ryjilizzXUCYddrOVmTOrXaifDY1mgDTL375xenkjQ8DDfZ82ByanYE54/KFY7i6Hi2G9TC07A31qwxSLL2iHPexICkiloF0SSB4k0QlzUTdWHfOrIzWr+enL9k5ko0sb5aFNlfw8BmUuUX4fSpX/Hs1XXp+wanSMceMo+PgL7S4ElBZr8CwbjTZ1+HmMCsMgxx8aFHVwxxjQZnGkGkTPh4NWoJfRenFGB3L46BlCSMZID+RYVG9CtMvOxYUw82kwAGna6vfg4vSxF3ay0JtMIBqnobJBVccv+YyTjbRttbegL1C0bf7tTOZx75JgV6hbQvQaweY1+aZFZ8FodCO0KO9dkAA31C5rlm6SJvBKESkcQSd1h5LUo8aC2d9dpqONb2Uso/0I6Ks0cyAcQ2Kw+vJaLaK
*/