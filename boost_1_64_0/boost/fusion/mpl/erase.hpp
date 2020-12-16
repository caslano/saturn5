/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ERASE_10022005_1835)
#define FUSION_ERASE_10022005_1835

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/erase.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/algorithm/transformation/erase.hpp>
#include <boost/fusion/sequence/convert.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct erase_impl;

    template <>
    struct erase_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename First, typename Last>
        struct apply
        {
            typedef typename
                fusion::result_of::erase<Sequence, First, Last>::type
            result;

            typedef typename
                fusion::result_of::convert<
                    typename fusion::detail::tag_of<Sequence>::type, result>::type
            type;
        };
    };
}}

#endif


/* erase.hpp
m/FjSA31cC+tpyFQ5zMMj/3Y0r0Dri3tnX3E3H00l91Bwzmfeehp5cm3CQta8x8Kx3hX2BPR03dLTsNPC5gpKm153z43ZnX1ftwBrWcfHkf4uzN9ouY+NHvQdcEJ690ra93nAXrxKlr36ePfB3oYf++A0J3D5SOAv3ubmE45FGVUun3ApImooS+O6UE55+8QMD6h/L705TM9PVQj5kzNfVrzWeA5udFtPW/fSjNhPRdvbXUKgseAR11B6e4DlT4d8HO6j7OMj4fL4bY6Hl8MfI708TqME8M7L2lMmH88McakMaFOruEZWl46dGxikn13UffXtIwf1jjfIcO+J695Rhn9DmiXmbqwgzX4Iddmne2A9eJ1WIcdyN8Lne2A9eZB1oUdrMEPiOrUAkQekklmYnYwH9MpCFkOA8mwHbBvt5Dpd52IzM3ayA+1I+bsvKwf0yktMozeHUKGhlJhE6U7so62QTr218K0rlV5Lmc175eL9QMZPrerBbSrMAz+nj2vMYgweF7B9rQZhMHDO49Vgxiz7uqFNrjqYv1bctI3l+uMi5rhcLgNFAQjfXKs2zyVde9vc18nNe2L4/clGb73w9FupMa+bgflKXT2c3n+na+Eupx8u2yId50la/3hFbSVOOca9DragmHYX0ZdR5kl1Xf2o4yuwy3BaJ+Y1xaSapyhlcG0Sl1RyDfkozw1Vtp391Ob+6PcLIsGmRCH9TnJsX/dhH9t9HZQVxxnUjNstK4KljN1NW8ZU1ddy9i6soypq23LmLrKL8WY0XVVsvzIutqwbLSuepJz/Vjq6DZxv0XoPg5+G3pZaPQzqc1/MNPoAqz3SLBerTTtH5QQZungpPZ9axhz7ysY6mmW00sFHZR9TE8TiDBKq4JBe+L0d5VO9V9N1pH+NamRDYizurnz7RZa27+0zfvX2/fDb2nbaP9Yie63ST3pQCeFZIKk3vyJ1DE6sl/0s6jultHZ9/65Yaiz5b5485ehrt8ZKf0q1P0N3VqtJe9pN0dxBKm1FcvJzpvz9r0oV1kU6+29eFguHD4/ZMPhK/Bkf0sN8V2WeHiNJl1+9ud+7o92Z1l3z82VP5f9ryUD76KCMKJ6+rEYrCX8xjBtKleZAa6DKGvLtv89y4Vl242GpcPpWYaa3phqoxvrktHf6YbvE2X4Q9UYk06P5mizGFw/yvG3uZHHS59fcbQy4OCCfAcgf5koQz3NyoLck+1ZLpvqLKC+L2uYtLchBmnfFWeGRi3iK1zecn7a1IKfZpns7bAW7PsKcSZtWVxH+d1RDt/8Rp8V4ahR837DFY3OI7OIbyvOZXnkucqV4txKp7YmuVKc88vVzG1bTl6L5rZ4ZcvxlWce9wdxTr/cKOaQpddeQfPBexFbWndfS6IOg88b5l6ndQqd1ze0RneYxRml14eafI9XvK8QcNTEJXgO6fy05PDNHNjC1mdjun4rdPDqKNNYrYq1gTOSkd/WF/PdzwUM1WVN+BC9QURPk8Lr5V+IMGmN00jI+e5/WXLZDiPPz/tfDXWb7+5rQobzDZ/ljYpxZgEt/yappSYPf8pq7lxkA+m3ujoTWXiz1emAEf1vsd4YYWZEGNtkE6HuDEP2b7m32DBOri1U5DpG3zB7XF4q8M/eanWZl3mrm7z0Igzlhedgb7N6Z7VNleZWgKr+nrdYIzoT8mljRf9vdTkUNtHvnR3J0VDI3Hycy/rt5s0zLsiHOR2eLsKvYU1c86TxWumW9i/8Ezw87yp9P6KnJlBFO/utYtysxo/NzPQt48dcZkq/N4wfc5nJ/8EwONuBOZZl5DjJ6zhxznz7M/ljnPPpB1eIcna87MY5dLzov+McOkWMl3+KcvY=
*/