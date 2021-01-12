/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_IMPL_05062005_1226)
#define FUSION_END_IMPL_05062005_1226

#include <boost/fusion/support/config.hpp>

namespace boost { namespace fusion
{
    struct iterator_range_tag;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<iterator_range_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::end_type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return s.last;
                }
            };
        };
    }
}}

#endif



/* end_impl.hpp
z2KH3IxqfI0OvPA5Fli34a3vmgHO30qtmTr1XgkeTN/QTuMsa3gwL+CPNnbfeTj6GdlPZUGOCMSkZgV8U/0MO/nDhpsToqduGUbVz2OlDkLbCcvACRqWorxXofLI41dEGj7mvwmeQYnsmkGvSOu09ADZ8r1a8HlWqNxsThkrPqaCTePqac2n175JGsALiBLpCTO1EeCE7yBPoyTMWmC7AKC1stRtgi0Tx45tS0ysecwW8HxP
*/