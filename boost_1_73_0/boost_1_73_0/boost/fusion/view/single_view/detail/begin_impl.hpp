/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SINGLE_VIEW_BEGIN_IMPL_05052005_0305)
#define BOOST_FUSION_SINGLE_VIEW_BEGIN_IMPL_05052005_0305

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion
{
    struct single_view_tag;

    template <typename SingleView, typename Pos>
    struct single_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct begin_impl;

        template <>
        struct begin_impl<single_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef single_view_iterator<Sequence, mpl::int_<0> > type;
    
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return type(seq);
                }
            };
        };
    }
}}

#endif



/* begin_impl.hpp
GYYnw8sj+C88Oglf2B4/5LJO4b+NNB+M91Z+J3M4wQX9thZ03Frc8/DHZp/kakHr/fOz/ZBmcntE5TTawHnme4XhLy8vnKZqB87vXi9vsovh5X+8PPNmAqj9NpkuWNzF0U8n+8d++/Q6B+peMMHZ+enB8OLC6zEtixiQwe+iTw4OLonqCI/NPqyg2ch/NC6qOp02nkXV2H9SAv00hhoDbjce1aUsy6L0nyL9ew8QjmFeF9OWx9Ma2Iv3eDLL6jRtLDopGusDQsszgkVnZWOd+FMWVbX4vTBtkEArzeyuJDPGFEkJ6RrQvoH10zLN68a89GIiJ0V511ilnCTyanatqQQY8Ag2lHQPXp0fnw8vwos3JwcvAvH4sfh1BcWEfs+oerx//pJe6seAH/vHjWcacRjXAtxnlEXlpA88BDlVOpHFrK5EDOylyLM73OQM39wC74CmGfGrRE4BCWQeI5usojqtRsBFaP88kXh1oVYUXh69HAJXstilWrzc/2v44vTi8mD/4MUwPB6eiO6z778XT8QfAgGrmkQfxPP/PDyBB3GRAb97IqYFyJJ8NgHJBr/9XZYFzghbQA6nUDBG7pZFuFd8ujv3MdxVwhRwfAenL8+Ojod9XKY4HD4HYr9Ahv1eyike7yQFpn87ljmI
*/