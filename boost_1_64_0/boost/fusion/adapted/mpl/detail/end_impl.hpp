/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_END_IMPL_31122005_1237)
#define BOOST_FUSION_END_IMPL_31122005_1237

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/mpl/mpl_iterator.hpp>
#include <boost/mpl/end.hpp>
#include <boost/type_traits/add_const.hpp>

namespace boost { namespace fusion
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<mpl_sequence_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename mpl::end<
                    typename remove_const<Sequence>::type
                >::type iterator;
                typedef mpl_iterator<iterator> type;
                
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence)
                {
                    return type();
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
1HlFliLS62HdCg1YMYaIKRCVOeBBXhd4ePZV/gFkDeWy8DisZLgKScCfdIyjRR2k+rWV46ZmQSfeyR2rv+0DMSt0M13MU3SxPYIkP7Kfk7ST6GhLHcE6pSMpFgwDEaLXlCX5TPi8UzptxCitOP9NwJdlqreY2tssPWh5FdroPobaJFtby4xmr0bO9k5Ei9sRRnJvQQQOQz62IBrvj1HkacX2KU0ekGGCPOSnJvOVR83AO/aKL/coJ3IGlvxjvPFo6Ui3DsuuBrx2Nw5Y8QRwq016ESRVl/DBuOd3CCXyyE+f+FI+kZmuSCbcpju0T+Y7Lpgd6+Cny6ZwiQZjLGUzAQyvIqGTujDjdLXe9zKXEo7pUTPIFkoufR8GkfvzqzTYYtCOZ6IZEDduowSgkzV9EtvRZ/b8XpE35HQ3xIIit9SAEE23iEPV126i9CIBldp0O63gDMg3PqaQ336lwk2wIjaScLF+KX3bfE9FsZMm7z3aaqBOCihy+nULGkQe0p6ReErfMeMad12NnkFkT5ZZzm5S3nFxISn5cxqJB+/CNIq/8cYPB10GqxbnAg==
*/