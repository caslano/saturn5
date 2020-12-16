/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_EXTENSION_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_EXTENSION_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/category_of.hpp>

namespace boost { namespace fusion
{
    struct struct_tag;
    struct struct_iterator_tag;
    struct assoc_struct_tag;
    struct fusion_sequence_tag;

    struct assoc_struct_category
      : random_access_traversal_tag, associative_tag
    {};

    namespace extension
    {
        struct no_such_member;

        struct access
        {
            template<typename Seq, int N>
            struct struct_member;

            template<typename Seq, int N>
            struct adt_attribute_access;
        };

        template <typename T, int N, bool Const>
        struct adt_attribute_proxy;

        template<typename Seq, int N>
        struct struct_member_name;

        template<typename Seq>
        struct struct_size;

        template<typename Seq>
        struct struct_is_view;

        template<typename Seq, int N>
        struct struct_assoc_key;

    }
}}

#endif

/* extension.hpp
nAuKPJ4ONrDMv1PXH3oOHlhVryv4f3Uu/t+qL7heV/Dhz9H/2/QFH8m5+m+lKzi4Hu8cbuP6+jl2/af+U5fPbzT/D5QUBX71/F/OU27vhzHqPTL2LC0OZhRkZRRlqec78DzuI/U8EMyYkpdt6PP+C7obobNIpVwvGMH5+RC49/C7ygVqvDhuyKi0KcXZGUWZOWkFmNNGfbY3qOaiatIZmhtObCPPpmQUZ+tnyaE5pDrbZTvLu4xi6zWv3gN8Gdwp+Vmo0pWKUkxLnjg+edyERDmuXetZHZlf33yVOb+2x59rPbfDZ8GikuKgepYeejY1L2NacWiNIVbPwWcYYWsMBRn5zGNp6FmxPFTP5uOZT5VPRtE0y3y6f0t9Xiw/wHm3m94zls8Blo/4OYb7cs2xVlBxdXj5ZOZlZxSUBGpd47GGn8d1jvPh5MF4uA9Q/tUu4eOYcnw0a0jueTLXivYwzmPhYtQ7wx65rBVd4x5nmpRoFPdDJN4GUubqfZUGDEe8k/3u8c6PFK96lb8+3poz/DNZxnmSBqzXlLnHmzZFlpWY35xI8Zp60VjOImYKi7PNM8tm+VvOlzVoYT8vN4RpLGMac5RfbX/7BDn3vThiGlk60csKS/uIdOafbaNUNQ5rGfpjeXaA7SAe7vdIX2WE9GUWlhQEo6ir1rZQyjiO4StrBPehyNxr3ePIzfr1daOacTZmnMcwzrgIcYq0iuauVKR4z3Sc88+QesQ1iSfPwvTOJd7i7GCt77ixrT8IqLqZ5KybjjRkNWCf5NFr2EPAj6RPsqQhMyc7c0ZaxozcrOjPaa7XZ9GLi0uyi6zyvlqthaqw4NfXtBRlkN5An4XJ+xd75wEeRRHF8QsEREQMFsRK7AWF0BRCwFAiQREiRYKiR0gCCaQcKRgFFayoqBEbKir2ggUVOyoiKipqVMCuqKioqNix+5vd/91e2SN3AbHdft98P3LMzryZnZ2d8ua9c8gz6D2ZZaVRVhq8VnyfVZfjWAWNrtM5wh+n0ipr6LkqlTfPpKk6v6s9MpwbXt78vFj6WenNqrw1IW25dnO1ZdVtM/gayhYrI/Ky6qkglvdYa80R9atnrd8rq8eML2T92K7jZZR5BrLsY3R3ZpB3RP9UUai19xD5R0tX/k7CToRbCQ/RPtPOC5dfbSsG+VuGyF+j8Urw2CB8vGI/B7UJvUu+Ko9rH2vblFxhy+f5ICP0PV+m8nTTs+9M+ND0Lec75bG+Oao+r7250KA24O/TB0rnPkd5Hk5YZb6zoXl6MZFZiDJ2gZVndWXeuMKGtT1/WRcq34OVbyflW+eWb2VxeZnXGm81KE9/e0lr4V7W1AtC8gwUMZ7zcsov5F2erfyGm/yU70fkVxuWny+vqoh9kwblFdhb21JjNOU1xM6LzMLyqiivOcGfYwPL56/PqcozVd+ltoQryNwXlGdlIE/z/Or/Jpn8mkUpY7L09XcgmK6rDeFjyjjHNT+VMYbvYHie5u8UZz8wRIb5kuFY/X8u4RPzPQqWodrnK6+oKixwWm+9/Y5//HPg1rZdW/WZ6j/s36xZl2y4rybPZkeY/tDJjf/mi6KzeprTtdnKzmSpntHzprzmG36hJa//UxJzHS0Ifi7KY7XymKR540ST13Y0vanKI6gL9uZXlHgri8eVxdAXq06CxyeyB+zIEdEX65uyMzKtIuxmfJnbcqg+nbhePiuqL/WJsumsmjhB5alSeRae7FKeskovM33aXcWkwoq/rkzu30NH5pxWdiaVkrlMMnvcnkFlaXFpobewzFqG2PQyq92YCNZVLZl9knn0KVFlpuXE/i5tbHlnS977JO88ybt2ipu8NIr8kmKOL9Xbx2o=
*/