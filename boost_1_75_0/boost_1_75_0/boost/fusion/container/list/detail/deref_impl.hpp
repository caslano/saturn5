/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_IMPL_07172005_0831)
#define FUSION_DEREF_IMPL_07172005_0831

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>

namespace boost { namespace fusion
{
    struct cons_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct deref_impl;

        template <>
        struct deref_impl<cons_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::cons_type cons_type;
                typedef typename cons_type::car_type value_type;

                typedef typename mpl::eval_if<
                    is_const<cons_type>
                  , add_reference<typename add_const<value_type>::type>
                  , add_reference<value_type> >::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return i.cons.car;
                }
            };
        };
    }
}}

#endif



/* deref_impl.hpp
C19LQKKFI3elmBkhryI1SEAcnItAbeqkfBgmC8Jt8u1mBzvCxnlz+sfImJCPmvl8s4UCKr5rfNTfWOGH+IA/NqkSf99iaCWKrsAoGMjdNZL8XCWS5T96PDDNt8S/5KsqMMoByByjZ3CQrN72TDToauJ8rCk23XQs08Q1eSc0C/IhpIFWciHEkq+jKhehP+T/eKAakGuqu90LqSoGyTQdKlUKlYSQLOAqgXHOLpXys3ExqHKTN6bsNJyVah56Gp8EH62Eg9AunmkhtIPSotQmEowiDEQVa5rFa1D3kRuQqEF2DnGzQJLjT+PBfakXrmETYLyNUQb/bxMShp4aykRv+hiIT+yMOqDRy4dtSSHg1j7gVW/rkjw0GDW1xrLgmcu2AtLoK0+Bw3gHZVpKS2Rrog4i/xHd3woWoWoAelZOeITErtNeCxJ5VK7wqJy0ATyaVS7lz1oK9+bc8kSmIUs95xbYgmwvvXwS2DbUix7y7IOHFaSCQy/hcwAtLNLTYVOga8vR07ge4y5p8v7ywOwtIlmKcJYkyALBXSKW4Hz0t05hZg1iJsqZWGPTfd6LMLMIM3MkHogS1wnMXCcwU+1FH2NmRqCe1nBmVqrwh1eymkJryiHSwEsbBmHPJMJL1OYDvYCXJ6X851YY5ez5YBubRx2EY/9vIU3SF2F2DkHVHEHVoEaOIHb+ciUIXCabNg5cBczSIwpLj3CWPncE
*/