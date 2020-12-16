/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NEXT_05042005_1101)
#define FUSION_NEXT_05042005_1101

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct iterator_facade_tag; // iterator facade tag
    struct boost_array_iterator_tag; // boost::array iterator tag
    struct mpl_iterator_tag; // mpl sequence iterator tag
    struct std_pair_iterator_tag; // std::pair iterator tag

    namespace extension
    {
        template <typename Tag>
        struct next_impl
        {
            template <typename Iterator>
            struct apply {};
        };

        template <>
        struct next_impl<iterator_facade_tag>
        {
            template <typename Iterator>
            struct apply : Iterator::template next<Iterator> {};
        };

        template <>
        struct next_impl<boost_array_iterator_tag>;

        template <>
        struct next_impl<mpl_iterator_tag>;

        template <>
        struct next_impl<std_pair_iterator_tag>;
    }

    namespace result_of
    {
        template <typename Iterator>
        struct next
            : extension::next_impl<typename detail::tag_of<Iterator>::type>::
                template apply<Iterator>
        {};
    }

    template <typename Iterator>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::next<Iterator>::type const
    next(Iterator const& i)
    {
        return result_of::next<Iterator>::call(i);
    }
}}

#endif

/* next.hpp
+Yjn5CgTPmob0owxR+Jj2pQhplgkNSANspSIXKp+6aHAHMmP249hKkQ/Ie8MMEUYdBzS5KkR+6Rt6GOCRVovk0dGqRK/XDzQT5EFWrLywwgzxD7lOGSYYJ7kp9URI8wSv0K9MMIM8SHHJUuJ+JXeZ5gq8au8T5YKMfc/9zNIGFaXFJij5Rr5IU+d5s+Ib4Yoseez8k+RMOI5fSzR9jnxQIEl2q5VDqaJXCdNhpglnpMfItfLzyvkjwxlwin2pYscZRKn2oYRKjTuV08MU6LpNMdniGkaT7c9Gcap03yGspBlmkiHNiJNnirxM+1HPxMskHqlvJBnjqZXOQ45Gg+IcbKUiJ7lOTlmiZ/teGRpOMffZKnQdFA7MUKF+Kvtywhllmh9jbQpUKPlXGkzzkSnY77BMRmiSvMblYcCdZrepF7oZYwFEl32YZpF0udJkxmSbxaz5KnR8hbtyxTxw/oFw8zQ9FbbMskie98mppil0frAPYwwR2u3dCgSO99xOPQ8fYr2Nvtw+PnqjeYTpWt95mnrKM81R32Obz1m5ghN1jK2TvDoy1yT7Ixay0qa7nsG6zEPWd98nDkWj/HevDVyjnF8v5HsZMjxKic4lvfze62lbJ3sDuuJD5O8UXls0yg/XXf5Hf52a/fVraHjOOXXqq+7rUFC8ZA+yah7x41e73qd4xNnwfOkbcY8DtBJ2zLrrxe8XyHyenXBYQY9H/Y4Fo/6jpzrHvoct8tjjhILNLr31soB9rjG7qSfyvHSsE77AOPMEt1tTWu6aDlV3pVzkbSyxuyT56A0UkRYdB88n7IWIZlnqlemGN7muXXpRtl/SB6tSTd/kutGdTPLEgvSbzpBu3q/1VoQB+hhmJj/yz/sd0cTzDJ8yHbWKF9SPyVydGuHMWuWV+m4QR3aL3cX31XeknUUvD7i9WaPh4ieqVzWTNzHpPz1N1q7j7I87rNmX229tf202x6aSN5jbSnbtTf6mxl/Z+w7QkvF2kUew4z1labtS7B93bFi3ovYvtBore5Ll9fysr45RZ+zR3xO0Gb+X3qluJS3/ZPmSx4nrPfa6rG0fB3jvf7lMtwm9v1doKydD6i/Lscf2+seATWC15ooPcO9YLqs+Zchf5bvLnic+4A1nNwvGfyh9R/8nquJfnXUrd5HTlbnU9bYcE80snw97DhLXepcu0zZv83zXr/7au9xv0Deu31WWDMPTyjDHnrodl+mbLsOea0Yi5fO1Q7aKqq8zQejxizroPs7xYi/qwSvdzPhtWGmtcs+a7jPrY36bo910MV7XUzH9ym7Nj/g/Rl1mXuadrRWf75Z/VAi962dIftXc8rnbA7lsxK+45II5bvWhsTOdaHqXnfMdVvsnTtC7mXxkC1tD50jYtlcsPD0XX4vuDXkduwO9fntIfGQ7dZu9L/jd4ZybVfouH9jSPx4a+j8wW7/Y1Iab9vg3mk8pK81p06u9jsOc92Zzb6P5l5Vi3Z/QLt92XH+3hjaP+YY5ybd57Leu/VJs7bp8Hp6cW3I/nynNRN3hkx7PMS8lpva7X8GJ0LnkzeEmDVqqndq68XGkDpvbcg9fXfI3RIPiQt2hPSfjc/jW6xJHg/lUtT6ueuML8bDp24O2WfsNFfx2Lned3TXh+qb1vsemfcfXeO+hnI8zZg57f9hHNoQEjuM6++1X1MixK6Mux+zzjqnznMf2RDSy8f5rfzZL7tmXYj9dlco35bwPwLjoZhXf8/dEjoLiZDevjakP+w4S2tDZ2fS98bMu2/aEhIv2O13X5tD7rENvke73u8l7NuhDau7/GYyEYqJ3aF83vrQfsk690u3h/Jb1FFKXd2yPbhZFRJ7N1n/ZUsI1+8=
*/