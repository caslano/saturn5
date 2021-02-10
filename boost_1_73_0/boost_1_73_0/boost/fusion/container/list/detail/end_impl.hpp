/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_IMPL_07172005_0828)
#define FUSION_END_IMPL_07172005_0828

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>

namespace boost { namespace fusion
{
    struct nil_;

    struct cons_tag;

    template <typename Car, typename Cdr>
    struct cons;

    template <typename Cons>
    struct cons_iterator;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<cons_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef cons_iterator<
                    typename mpl::if_<is_const<Sequence>, nil_ const, nil_>::type>
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence&)
                {
                    return type();
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
csI0Kq1LECFVIik9icIQPPg25Dg6IF8SuEnKXjPTC8E00Y5pxqUTEwh7iMFktIXl17EI03kFXSu+iuKHEnN85fNZtiDkAoFkEGQAuqDg2X8ajKkmHJ8KQJ4kBUfYbfzSRZwjJ44zKzyKnUUQzdzAEaFImy167AYBKNQ8Bt9CRBR6oEfBT8INxL85k880ugHAh7cijsIVD1NEdnYWgSDCCLgPFww8APmYowawu4WM20j4rQbyEgN0xyGBW98ZfQdcbGXCC7gbZuvtfJhO5Bw5iCt6+LV8IKXbSdG81BC+RezcTR600A8/yHHRmocbe6Anw1lAUIew4RBYJGvuibnwbFZY86Xu/BKCkhUEajoOuI6DCY7DSaQGZTFvSS5R/F4EuldBu9K2U00xO8B/24wkc3CgO8vtlNLADl34Zh6y98wD7iOvCXFkAixF82ZRsVstHCDmzRfWjAi9RQW5njqjcwVj3Seoz3a9oY3ItUbvhRdECZeboR7+/jtRoW+2orGSvOcx503TVMu+n62XEGAGfJsArE5kOBmEbx6yZ3YROGbE8aHmGGd7GtO76l5OzSMKmEb6I/JjqyF+t5VkU7flRGkkJYeswSbSZAo2HOgQeg5qaIEOamYHrRxy3dCD5AgEy9ZRkogZxIjgAuFr
*/