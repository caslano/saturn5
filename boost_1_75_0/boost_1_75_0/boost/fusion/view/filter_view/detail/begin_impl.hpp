/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_IMPL_05062005_0903)
#define FUSION_BEGIN_IMPL_05062005_0903

namespace boost { namespace fusion
{
    struct filter_view_tag;

    template <typename Category, typename First, typename Last, typename Pred>
    struct filter_iterator;

    namespace extension
    {
        template <typename Tag>
        struct begin_impl;

        template <>
        struct begin_impl<filter_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::first_type first_type;
                typedef typename Sequence::last_type last_type;
                typedef typename Sequence::pred_type pred_type;
                typedef typename Sequence::category category;
                typedef filter_iterator<category, first_type, last_type, pred_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return type(s.first());
                }
            };
        };
    }
}}

#endif



/* begin_impl.hpp
I6CccuBr/9mqPeVoJ+hZA5nxKeRt9AkP/F/5vMT0qE+68W59tEesOqMSWoCKN3JMXDoXvyhonM5Y+8RXIko8otxfmx700tVrU6w7par3BevHvmi1oXXHxNy6+CSpLro3tB8vmUKM+PGWqIZr8RKbbpUGLUP7PckVrfYjQ3sGs+VVNh1PpuwWgZKb72LZbvthX15BW2layKYbAcqNBhYQeKwDtGpKGTdlDvtg9/f70eI25uuw+Mea7EP4+c3HseNLgFDgEzF2plYmO2E3qRlZj5qXQYvJDHCsYmzPMpLD/Vjno5G/2MUL+GkcXK7fNeLkZurerpvw5ErtjhVkAlLSBD+/HSm0ffzRK0h8HfBqDjvDgl8MkgShWNhDXyNSg5xDNrYXzL7vu+epfZ04ACVtMcsoGyGaD3L36r4KUDyUCRWwMiLmBfbiUrpNTL5BEkO9kHN4oVZNZwBre9I/4VeefsQsWwS+iWwjq7q0OnYo1lvPyB+TFqlGjhJqTj/jH7ER3wxxKV/XsWnRU/dqCyw04YZ5DEIl0TbhPx+1iVFT+0OnXw3UBuTC2aun84bJsxRWs9j48GF3To3MOcxY3wULwUTYO87dzYpLO3v71IpHJitlf01Wm5hDjpQgmq5OqkyAHnLCUKhoHeq69rkHHs2TNTHuAwckVdRCK1prvS7970raaAPf5q5xFIT8DS4gB2fVKoKYl1rSP015a9Tf
*/