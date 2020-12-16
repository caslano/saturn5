/*=============================================================================
    Copyright (c) 2012 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_CLEAR_10172012_0940)
#define BOOST_FUSION_CLEAR_10172012_0940

#include <boost/mpl/identity.hpp>
#include <boost/fusion/adapted/std_tuple/tag_of.hpp>

namespace boost { namespace fusion { namespace detail
{
  template <typename Tag>
  struct clear;

  template <>
  struct clear<std_tuple_tag> : mpl::identity<std::tuple<> > {};

}}}

#endif

/* clear.hpp
gdthcVgGyNzbOsfLWYjHvvB3FIeTrxvq/Qku5It3fRneo8eR6S3mcXWc7ziJhasbw/ryIPb/fUMOZ4sjzh84OO4LeHsd0/FVKt0+dMlw2mCvo4tPiSP+Me+reE5yXXf1V8WpaCHpec+j4rm9HhzF3K+JI0Ux92txel/kE5NT8QW/08Vr+eBTxfPZMFzawH2mOIRH9ZE+17mkTIc6vhYC5/RafHIhzuk1ceRnyX3pc4ijdrb5V5LDQKRc3U1q4HxAO+N/N3A1t/O1gat24hsD534W498auGo/vjNw1TZ+b+C8NE7O7QbwqnqvTxVqLTk+LqVwwtSKfKhawGcEePTDse4sMx2vppXkPsf0ctASYZ/jnuSSSpfXIiCn9I4tA5w6i+2AIKdfq8wyrdwyuOBZyhzolpE9SoTxoICM2lt1cIBTusjWAU4uS9TDeIhbBmGUfrSBjNwKmjNV1w0cGuDUvra2AU7tDW7nc4XGPfvtNVy/j7yDjmvrQTr6eFmR0lpK7rAAp8J2eIBTeotOOjclv6IAu6K9dzsHeLUW5wiNk0eCNEbmN8z193h20Xn9wkG4faTG2/e+dtU4LGJKpKiTOwtpdJTB1/vr4bvpuFIW8zvdNY5vhoFbWRqOmRvGj9ZwfZ9WDw3X92kdo+Gcs1lTq+4w6eng9bMiegV4vaXFebkBmbrqBDqunsyxAZkYOWT2SfvYMmoag/m+Fu/dg+ml83EWr3+7fg4OVRvz/R08qjSuzwa4eaX0hj8DHXKoiZk/3uLt+5yzdV4d4cHvDrI5lczMDzZ4jHo0fd8Qm1efgL/RUI0PLEr35n9tGShJ/f2dGs936eKitPbEnaBzWKs6QsPkha+Y59VwfX/6SB3X5txHabjqieLMWo2TtWswf46xZZA4usxYXSY4GpXzuJYMvh/W3cg0HG/IBL9TjsmrNEYaTNB4fT9Zro1zl0m+k2dwDf7dZvkajs0ejE/UcGi82I9JwNVhBOr814IA5+5DFKaVQ4FDfE4KyKm+weQAp/oGRQGOc6pXVDmNpzhl+COwG8VOHs0ywlcSlIl6XGmAU/2Ck4Ncwg5fmVNGha/cySN8+LYVkFHtssSnArfb3WkeXlRSMnlqqfgaGHNjbjbI11IPO9LI5U1+28qgDEoAGhX4NT0ol0hpfZ5TTB6nQknuVJOThyqAm2Fx+rjqNJOT29XD0Ubv3dMtPqrd31Nlcn5/Y6aFJ+akkuLiPC+vV4OXI106v69sulkoIDfLLacKBeRqgnJWxxp7S4Ny/jx0JMgZc821QV4VDsjMdssY/dY5DpkouGiQ89dSnBHkROaWc7EuzgpbnUvGClu9LsMdPd4NxO/H3JwxV97glsHHkjLx9DJJb63APF1Gdhr5GzXqODqN8nUZ/oTBo4OIvJo0uZTnZkrHpWOya4L35uu81o9foOMYZkUaJbfQ5rR0XGRzcj7OSMcz3TJGOp4VkElqvTcps9gpA2cQvx/rMlz6MfcawKsa6qBTO8fgVH2wRMP1vRHnGnhDLEI7NyN45yc6Jzsp/M55QZy6hZhfdXLUt4GbF+g8lxLsHwUuop+v9jmymxeZnPyiAvD2kjp4+86Zi4MyxpniP7X4aHihquOR9y8xZfwzHZeZuH9RqeYA+3FpGjn0I1lmuSmDLg6yPdLwMk+GD9NS7eQKHdfaycuBe8cnFZfk5Rv7TsHjOgNjj8TPLI7Sjd9ZGcDVHdNXOjjsmmE3r7L4KNL3ahP392NcY+BcN7I/1wZx+IN9p4ovKy0p5yrNC+P1Fqc045iztXiOBN69weLs80J+4eQTQoD5GwM8Zv9x1/cqNw8XpB83OWSQS+Q+VRcfDcu5XBdH82cJvHs=
*/