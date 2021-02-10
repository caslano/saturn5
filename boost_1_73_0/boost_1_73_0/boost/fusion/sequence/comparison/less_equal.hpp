/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_LESS_EQUAL_05052005_0432)
#define FUSION_LESS_EQUAL_05052005_0432

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/comparison/enable_comparison.hpp>

#if defined(FUSION_DIRECT_OPERATOR_USAGE)
#include <boost/fusion/sequence/comparison/detail/less_equal.hpp>
#else
#include <boost/fusion/sequence/comparison/less.hpp>
#endif

namespace boost { namespace fusion
{
    template <typename Seq1, typename Seq2>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    less_equal(Seq1 const& a, Seq2 const& b)
    {
#if defined(FUSION_DIRECT_OPERATOR_USAGE)
        return detail::sequence_less_equal<Seq1 const, Seq2 const>::
            call(fusion::begin(a), fusion::begin(b));
#else
        return !(b < a);
#endif
    }

    namespace operators
    {
        template <typename Seq1, typename Seq2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename
            boost::enable_if<
                traits::enable_comparison<Seq1, Seq2>
              , bool
            >::type
        operator<=(Seq1 const& a, Seq2 const& b)
        {
            return fusion::less_equal(a, b);
        }
    }
    using operators::operator<=;
}}

#endif

/* less_equal.hpp
KqA4bbLhAwZbpE3jib7YLQejhWyCUlkhOpEgH9P98iEeRNV+tJGTmkT32stRdru2+WBPyiwOm+pCkUf5fPZ0nzrjgKyDtakiz+KFdf+zrkfp27VsEPBXr3lOqon45fbbUvG+irqsEgz6l19sNXH3mJ9TN3D02stQ3gBUJJ2+RGG2X3v76aY/urm+HgzHXRAew8F40BnY2tiIRieR2PkSTDUZI0tbtNz83KunAhiqhfI91eZGlKDsQdsy0YWPng9nxZUxkZ8hG60cP7QVG9VKTJGVE4xVqmv++WY6lXk+38TbrmRs3y9OIDvhmdl80EDhhquhW0q3EAPAY/q0NTaBMm5raIITv9neaOnESfgISns7/atmRyqc4bNOzkWW6irkq37Jq7O9LZa1pgQOpVI5Cy04Gk7S1C43wuyNo5KEUBcQkMPF4bRUIt4d3smltyzkBU/wngCFKKLkLr3lK7xWjGImAklQdad3VqEf0i+JuabnfosFXsItnDrq+kiDHtJy/PVMmYuOEl3axDcN6VI8t6SF6x1XWy0Ok1eGDR9HBc3Q4K1sJq/OHuefEehWxTymQtHvzzy1fIBqfisfYKyx8LnhKfLXqPv9uMH1Gf+fKf79TOE6Sk9yRfLKLSvvIZssZ1veB9PgZAGAiG77
*/