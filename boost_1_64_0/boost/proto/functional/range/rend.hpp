///////////////////////////////////////////////////////////////////////////////
/// \file rend.hpp
/// Proto callables for boost::rend()
//
//  Copyright 2012 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_RANGE_REND_HPP_EAN_27_08_2012
#define BOOST_PROTO_FUNCTIONAL_RANGE_REND_HPP_EAN_27_08_2012

#include <boost/range/rend.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{

    // A PolymorphicFunctionObject that wraps boost::rend()
    struct rend
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename Rng>
        struct result<This(Rng)>
          : boost::range_reverse_iterator<Rng const>
        {};

        template<typename This, typename Rng>
        struct result<This(Rng &)>
          : boost::range_reverse_iterator<Rng>
        {};

        template<typename Rng>
        typename boost::range_reverse_iterator<Rng>::type operator()(Rng &rng) const
        {
            return boost::rend(rng);
        }

        template<typename Rng>
        typename boost::range_reverse_iterator<Rng const>::type operator()(Rng const &rng) const
        {
            return boost::rend(rng);
        }
    };

}}}

#endif

/* rend.hpp
12Sw08GuBLsb7Fmw98C+B0ust9cvA2wTmd/a12B7y4LW3pVZ69cgi7euEzLrvHfDmE9BnsMQNw5x05BL/Dm2ZZwDvZZZuRTKrFxKYcyjYcxamXUemsDawXpkAcNGZNbafiLzGfYt1OA9F567gaXLrFzWh7gtwXYFOwjmq4a4elmidR7AumDMPrAhyPNDmbVGX8msPRF7nh2XeB5cl2Rx1hrBmJuDbQ/zlcmsvlTJrPrqz4PPgWC+TlmSYf2yZOseIEu1zkODnUuyzKphNbBNZNaZ3gPsOJnVz7Mgz2awW2VWP3vBhmHMCZnVz7jz9f6KYWvKrP2ZC7YNWAnYQWBVYKfLrHW4WGat3x2yFMMGZFbPPodcPBfY6xAvs87DyrKAdd7B9pZZtR8BdoosweoZxF0PdjfU9+wF8Foz5PIJzPc9zJd4IVx3ZdZ8uTJrzGKwCrA6yOVKmbVfOiDPXpm1J0bBZiCX+EbYn2CbNML1E+w4sIsbYQ/KgoY9LrPO7bjMOu/RF9n3o+BF8JrORfA5s8xa20KZ1c8ymZXn6WCtMmtt74P6BiHuQ5jPe7G9fmkyq74ciCuGuAqIq78YXs+SxVv3AJlVex/kMiqz+vktjOm/xM4lVWbFZV8Cr/mDlYJVgtWBNcusvnTKrDUaAJuAMaOa7F6nyKw815RZ/cyHuBKIOwLiTm+C10qghi6Z1ZdBmG9cZl17voIafJfa86VfCp83ghXIfNaZBttXZtVXBXG1kMvFMOZNYA9CX4bBvpJZ6xB1mb0OyZfB5ysya8wcsC1l1h7cG+y4y+BeLLP2bofMut++AHETYNGX2/ecNJm17uvI/IZtLrNq3wPGrAA7RRY07BqY777L4V4MtX8Ocb5mex1WAyuUWWesRJZg9aUZnu82w/NdsE6wp2Rphn0is9bIcwV8Piaz6lsB4rJl1lkpAquQWfWdLrPWtkXmt84f5PkIzDcEcR/KrLWdd6Xds0SwlWVWDetD3DYya3/uKrOug2Uyq/YTYb4LZEnWvQPm64L5noXa34BcPocxvVfZliKzalgHbJuroNdXQa9hzBqZVXuDLNnqNdTXI7N6Ngi5TMisPf895BnXYlsK2Got8JojxG0Ptrcs1rBysKPBasDOkgUMu15m7Zc7oIZHwF4Aexvsc5m1tlFX23s3XmaNmSqz+pIhs2rPhjHzZSmG7Q95Vsqss3KuLMlaI4jrARuG+t6TWfv6W7C4a+wxk2VWz1aWWdeC3Gvg9TpZinUeZAHrHgDztcms+rqvgfdowYag9nGYbwbifNfa5yHlWrhmyaw9kS+zel16LbxHey28R3stvEcL83WA9YGNwnxT0JeoVjsuCSxDZuWSB1YiCxpWLQtYPZNZe/5umbW2A2Afyqz1m5ZZPfNeB89RZFYN68usXIpgzINkVj9PgTGbZStY9yqw8evgbMJ8idfbZzNdZq3f5tfD57AyK5cjwE6XJVp9gfk6ZXFWz2C+l2G+Cag99gY7Liiz+rkmxOXLrDXaG8aslFl9qQdrlVl96YI8n4VcRmHMKZnVz/g2eN4jS7LOpizO6qfMqmGPNtifMqu+WrCLwdrA7oPan4K4EajvczDvjfB1/jIrbh2ZtT8LYcwyiDvlRnjfF3JplwUM6wMbg1y+h1zib4L3Im+C54OyoGGlEHc0xF18E3wNgcyqrx/ixm+C1+5vgu+hutn+nMR3Mzznuxme88msvuTJUqxrJFgN2JU3w/dNyKz77ZAs3TBPO7zOJ7N6FoC41WRWzzYE20Zm1V4us/bL6TKrL5eB3Qr2CNjLMuuMfQJ98dxij5kgs8bMkFm1bw5j7iqLt/oJcTWQS5PMOpudYAMw5vgt8P0=
*/