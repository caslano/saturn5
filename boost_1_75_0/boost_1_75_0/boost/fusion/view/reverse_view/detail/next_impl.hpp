/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NEXT_IMPL_07202005_0856)
#define FUSION_NEXT_IMPL_07202005_0856

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/prior.hpp>

namespace boost { namespace fusion
{
    struct reverse_view_iterator_tag;

    template <typename Iterator>
    struct reverse_view_iterator;

    namespace extension
    {
        template <>
        struct next_impl<reverse_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename prior_impl<typename first_type::fusion_tag>::
                    template apply<first_type>
                wrapped;
    
                typedef reverse_view_iterator<typename wrapped::type> type;
    
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(wrapped::call(i.first));
                }
            };
        };
    }
}}

#endif



/* next_impl.hpp
FC7GilLXy6DiUdQMWOhEYGAF5uwBFFtI6DdeFgNEeEIzfbtYDRIaWAI9efJURI8gdm9E3jjX6N3mem5T6iWIoCMcTU4LFfHd4zIBYhFfUfSmgsxeq4aABJMdzB9kMZzHY16fhIs6MjerAHh8x6gmPKWCYSJgqDiKmpboVWsh/C6nTM1bDHxjM384jITk/6gsJKAYuWF1mghuGaO5sTlVLJQluX/ShG/FD21wcfgaT5SYE8R4Qha3svpELCNIDr7mOeR+sSZYxN+6AGmAM4guJNGgaARdRBYv4k7ymLIiQoxYsBchDlvkQ/6wCeZk8VOE2GdLSMhniG0RYuqmsGKITShkiDUQ4u4wLLvs3wCRESRxBDtiPWqUyFcHhQubUJsSFVh2XzfWBQjnzg4b4Mi8ETe0fNoCFYgUTsuTedPZmgTuwBR8SiisIMBzHtCZmyN6oEjuDJjA+SCeZWoCBSUg3mzL5oosWWzO461utoWHwcLHoAiDk61hhI3VTL1rMSThdDFogwgSWTAD0ExDQeicGMHjRSCELTyeOkK4CyEc4vGgi3Ts0KjYEoIyg6AcIOIfjXQnQF9Xy7Us/Oaqm5SoFUdg/YzRhEROMlr44THsrRE9gnAgHqpI5AYN3DO0Ri3PW6Cl4yBI/owvnrn+j2T4Jg7PHQIYi4QbLCMGkjrDIFTixTPdFYjNnzHkGSpA5O5dGcMQx3Gk12EUAGyN
*/