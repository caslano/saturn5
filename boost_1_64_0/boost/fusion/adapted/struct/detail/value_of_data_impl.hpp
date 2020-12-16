/*=============================================================================
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_VALUE_OF_DATA_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_VALUE_OF_DATA_IMPL_HPP

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_data_impl;

    template <>
    struct value_of_data_impl<struct_iterator_tag>
      : value_of_impl<struct_iterator_tag>
    {};
}}}

#endif

/* value_of_data_impl.hpp
qTVXrcUa+bYJ6FtyBPRdu8L75ZvvQdgfPgQz4cPwQFjv19OWPit8HE6DT8Dp8BnFlX5ecQNekP72i/Bq+BK8EzbAeviy4gi8Al+Hr8Fl8A34HXwT/iQ99F+kb7498r8PM+AHcBT8EI6DjXAi/AhOgp/AfPhZyAeg1ku1jro4ygfgMvXDt7A7/A7uApvgXtJXHQB/hAfBX+AY6aUeKb3USumlHiO91LPgn/ByaOilzgcbwAdgS/gobAWfhhvCBrgRfAduAptgW8h3fn3UDrAD7ART4BZwU7gV3AxqXLBW6TzO9gvXr2xmnO0TPh5VXvdmysv2aF1P632XrQF7Aq3TsX5HvVH2BCfJnuAUnZ9T4Tg4S/ErToMXwNPh3fAMjbvZ8C14FvwKng1/h+dAo7JzYWt4ntkurZ9Rltof3q4qyVENe8LpGhfHwJnwWHgyPE7l+Txay4I3qby2sEjllbYIjMMjYG94JBwAy2AunAYPg+VwGqyA1dAHr4RHwetgJZwHq6D6U+tYxjVs7c+jVe8xcCc4A/Yx5Ib7wePhUFgDx8CT4XR4Crwcngrr4OlwETwDPgjPhA/Bs6GuQ61JcY5srsPzJMf5kqNWclwIs+FF8HA4BxbDi2EFvBTOgpfBOfByeC+8Aj4Lr4Qvw6vgu/A6+Am8Hn4H5+m6ukHX03w4BC6Aw+EtcBy8DRbCO+AxcCE8Ed4Fa+AitZO+0JoS40Xt3NSQW+38TO1cpnZ+CdPgV3Bf+DUcDr+F4+F3sAA2qb3fw2PhCnga/AmeA3+B18Df4f1wFfwZ/gH/gn/BFsjTYoOAnLu2CK770AbJub3xLqJ9yc6SsyvsDreFB8LuMB+mwiq4ncbD9vBcuAO8FO4Er4Y7a3zsonlwV3gH7AGfgLvB52FP+AbcHb4P94Cfwz3h1zBN/dsLroJ9odGGfnA/uDccDfvDXDgAlsGBsApmwDPhIFgL94WXw/1gHcyEN8Ih8BY4DN4G91e9tFlrTNzbdB1tAnN1Xoervw6EB8AR6qdROl+j4YVwLLwFToBL4UT4DPSa14nWkajP5jq5T/Us1vi5X9fJA7pOHoInwofhbPgIvAQ+oXqfgnfDp3X/eVb3n+dgI3wBroAvwd9hAzTmxVfhZvA12B2+rn5/A06Cb8LJ8G04Fb4PL4QfqJ8b4ZXwY7VzIUlrQawRBdq5udb9jeMC3S/mwN3gxXo+uUT3i0vheHgZ3J1CroB7wyv1XDAXXgKvgvPg1fAWeA18FNbBp+G18D14HfwIXg8/gfPgL/AGuAreGO4j6UDT3oHx5mzHoHw9YuSrDysvJyrfDWH5mszymsmn9QrY1SYffonNdijfdjHy1Shfzxj5eHeXfM756Ae9V3Pt6LzvGLju/cdQ2QftL/ugA/S8kC37oAPhYHgQHA5HwJHwYHgsHAnPh6PgMzAHvgoP0X1/NDTsFMfA3jAXDoNj4f5wHDwCjocVcAI8AR4Kz4CHGeXDiXAOPBw+DifBJ6AXNsB8+D4sgH/CydBDWwvhJrAIdoAlsDOcCgfAI+FQWAYPhuVwFKyA81oH7F4Wf4BOOqnVh7HtX+bdGNsGZsmNph3MkijfVa/xf9Vw9w/Xvl3MshvXjW1M3odrzz5m1ofx2cisujFxO5lu8zlv8+P3Cz1sfvw2M7nzTbsZ33zk/bBZ+xlu/qYNzdz5q29Hs2j+6vmMXvphpE3N8/MDdjWNHybuP7pxvmljs3J+8nY2nkarrU27BfHb26QuWL9sbkYsiG13k7/AanszY0Fi9jedGpGdNJFUQ1pAaiCtIHX7iDaTckkzSXWkRaTnSZ+SVpJSPkYGUjaplDSbdCupgbSClPoJ/0fykS77xLU=
*/