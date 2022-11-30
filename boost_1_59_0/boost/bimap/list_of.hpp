// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file list_of.hpp
/// \brief Include support for list constrains for the bimap container

#ifndef BOOST_BIMAP_LIST_OF_HPP
#define BOOST_BIMAP_LIST_OF_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/detail/user_interface_config.hpp>

#include <boost/mpl/bool.hpp>

#include <boost/concept_check.hpp>

#include <boost/bimap/detail/concept_tags.hpp>

#include <boost/bimap/tags/support/value_type_of.hpp>

#include <boost/bimap/detail/generate_index_binder.hpp>
#include <boost/bimap/detail/generate_view_binder.hpp>
#include <boost/bimap/detail/generate_relation_binder.hpp>

#include <boost/multi_index/sequenced_index.hpp>

#include <boost/bimap/views/list_map_view.hpp>
#include <boost/bimap/views/list_set_view.hpp>

namespace boost {
namespace bimaps {


/// \brief Set Type Specification
/**
This struct is used to specify a set specification.
It is not a container, it is just a metaprogramming facility to
express the type of a set. Generally, this specification will
be used in other place to create a container.
It has the same syntax that an std::list instantiation, except
that the allocator cannot be specified. The rationale behind
this difference is that the allocator is not part of the set
type specification, rather it is a container configuration
parameter.

\code
using namespace support;

BOOST_STATIC_ASSERT( is_set_type_of< list_of<Type> >::value )

BOOST_STATIC_ASSERT
(
     is_same
     <
        list_of<Type>::index_bind
        <
            KeyExtractor,
            Tag

        >::type,

        sequenced< tag<Tag>, KeyExtractor >

    >::value
)

typedef bimap
<
    list_of<Type>, RightKeyType

> bimap_with_left_type_as_list;

BOOST_STATIC_ASSERT
(
    is_same
    <
        list_of<Type>::map_view_bind
        <
            member_at::left,
            bimap_with_left_type_as_list

        >::type,
        list_map_view< member_at::left, bimap_with_left_type_as_list >

    >::value
)

\endcode

See also list_of_relation.
                                                                        **/

template< class Type >
struct list_of : public ::boost::bimaps::detail::set_type_of_tag
{
    /// User type, can be tagged
    typedef Type user_type;

    /// Type of the object that will be stored in the list
    typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::tags::support::
        value_type_of<user_type>::type value_type;


    struct lazy_concept_checked
    {
        BOOST_CLASS_REQUIRE ( value_type,
                              boost, AssignableConcept );

        typedef list_of type;
    };

    BOOST_BIMAP_GENERATE_INDEX_BINDER_0CP_NO_EXTRACTOR(

        // binds to
        multi_index::sequenced
    )

    BOOST_BIMAP_GENERATE_MAP_VIEW_BINDER(

        // binds to
        views::list_map_view
    )

    BOOST_BIMAP_GENERATE_SET_VIEW_BINDER(

        // binds to
        views::list_set_view
    )

    typedef mpl::bool_<true> mutable_key;
};


/// \brief List Of Relation Specification
/**
This struct is similar to list_of but it is bind logically to a
relation. It is used in the bimap instantiation to specify the
desired type of the main view. This struct implements internally
a metafunction named bind_to that manages the quite complicated
task of finding the right type of the set for the relation.

\code
template<class Relation>
struct bind_to
{
    typedef -unspecified- type;
};
\endcode

See also list_of, is_set_type_of_relation.
                                                                **/

struct list_of_relation : public ::boost::bimaps::detail::set_type_of_relation_tag
{
    BOOST_BIMAP_GENERATE_RELATION_BINDER_0CP(

        // binds to
        list_of
    )

    typedef mpl::bool_<true>  left_mutable_key;
    typedef mpl::bool_<true> right_mutable_key;
};


} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_LIST_OF_HPP


/* list_of.hpp
0ExUuZtRaDisCQRSazAMBfOWuLplj6fJEuOwjMfKc4xDToXKixo+yV1RXMfY+Ye/8Hc8r76EvJ+WRsXqHf7JKJXhIjRl8FkLLDqSsCElEqeA3IzymUi/RR27UsgtJTg3Td1xyFc0ElssGk+bfPMSCr3cI9KBHYtWLNTdCMucq6clsT2rhfDxx74yEiCvYkwEdihlJ+QD2FARfwVlLS9tGSEZFcW74ltx+2H0ikcLETYMISABjJv9G7uFQ34QhYzqJ7/xMh2j7D26x/n3h6VNv5FLSFoY1ZRZ0VdzBb7Iab1UGSuv17EcgLP3O6wNyRilXq1ZNp8HymjqXugdxU0Cuzst5q23m/OnLjiYmf3rruFjFRzRBErIXDJ0UNhQxfkLoBiu6sDjtqWswnxC3VF6J1/1Hu150Nr4mtDblA0zbN7SUhv4Ue4rb5kKCZjltyN/F0n7kHwC2ho8n8yAQIOPm7CpuUbsv/KvtVNpZtJxdvir3SO2ZNo0ePnz5itunVdJIXu4rxEw0cKhdr6r4lGwvto9bzHrBXFm3eY+zTn1yJJLr7WOBAQ5zwBoYlX39qzTU8f8e1/OfjMqKlAIJqbOk+olWE2Jr9nx3vAlOcj9QJB8cg6Nv9z3+i4JQrk2a0vItgk8OHQoYTDAIC5nviiLCv7lXrAFsQjpoeqreVYX+mPVZ4puZ9o5i9VIolSjyZ4mDzbWfI5nwHJ9XBZlIPlbOPCqXgWnz1Ci1ygLEMiKLT1DNRvogQo9QaVi6zdQJUyptmtKTgAOGQ492Lx1O8RW4N/dpMu8N+Ax5Lt3x1KAk2HEgcLVo6RvbJ4+8LS4t+K+Ru0FOq6xAerk3LjIblASZ+BKzqs0PgIl7leupUrtOvZPHEhIVcKxeQJrMXa5hZJKKtwTOoUcNZ0wWfjvEeKRfRkXKt86UtjnvC7T23iBukKXKdo2yyPblwrC8opMJIcPkK0ZlCp1+Q2ayjxVim8QzDIEfVOvLutOCK5x/rTbxOg/cHCNSeOFz01D0QNcHgdBOT7NOWssBoCgWuYq3ZaiJfkxB70Do7C9SXcizq+Ej+fztsSbi86NL0TqwbqTRK46Hor1uZlTw0dfcMDwvU7OTXf4vafr95Qx1bnGnckEfKpnVPdcWwyObD366G3xmw5gPqOwkUJKizKoT0BFIPj7D2MKDEv9Et2EXV+CBaWZCI7bMnNX7yxo22YfZrgQ5wq50rMrbtziCZ5yB/7ZQvFtHsBJRmYXeCiD+G1984vrYnjcvO1KH1vR56bb+6vfbEkojFDHviPaJajsiYkqJTAX1AAIIsOOVL0XMYrzP3wUDDuZKPotACebv1sbeCh1T540cr9zLu4GU+bEjHpSN6ug+HKEuoXGsBlm9GL3/Avnztjseb7a56fzYX5o4wTfRbvT3aerfvAHCv2UYPPTzudzumh3ynac4SMVHx/FjEczmY2GzH2KjhNN0/L1F/8jkd/uiKEarp91DsywDeWnxcmnJxe9gGqYNbG5wj9yDQQ3E59/VBAmSet8XFzEJ4QMu3GM/TzYp9p9HNJ5l3n/7+v5FNt6U1Z/ocFl66Y1Xmb4Umb62Hd7qCzkVXpSlGt2j82EoDrVCr3dBdkcDeYqUrZockJnwq6YYobX1Fm1k4upEc84vvIypH4o6bAugAE5wm/Y+dEZFFPu5ICmrpc95nDYm1XEkOr2HFrQvMOF3UJxVIpJpP2lxK5tdtOSYeRX/V47QFPnR8FS4mDTA3DJzfSt+fF0diO70nX53W97AahOdKmIhfJGSuBb+dpeUr+v9s9mwof5q7h6HriW8hyVPVMczLUzcU7iObNxEhQvuXwcIKX9n1a2Px4B9K6cAek3J0oWLHuUXu2oEIhjBA4qm3cxn/w+WIOXX6ybzS4zv4ejpxBj9hxE1v/Rlwpwpt+tfW5mvE8pSeLtRDPBTyB64QeJfGiFykvIj0kqVBfb9OKa6Nv0kEUyxoxyX3+yyYu2XgnrX4JEROgR55SqakMqN0Myhypdp9/O/Q3oKJ5GZMoOvX+7K+Xn7q/oMtsiPvnM0g8+KP+QjwzzQpt0cnBJbuXjoJPUqIBrYghlkJJ1xMOC3qsk0QV4OW34+/5H+x896DTZegmRJdSqvc8sYedhnzr8TBB1d5GF1PXcTT712a8daqmtzQw88Das6Sl6/p7lFcgYi+A+bj6uUXIWxvXd8H1/nZXYIoU0x3mhCbMsEMxtMqX0E0JvyuXKwINw5ETgRzcg3ow+z5ZwWDZ54VVECzHtlQ88+DCHxrsKUwFLJaKx6wQfbr/rytUKziuUn7dzyBTr5gW5bjnpRnGh9WoxodUC96vsd8IPRAq6fgW8ycHiywk4LY7y9IunYBOpxBYvtwmdYRUnUN/CBYXizxw2hVwz8phJczddZomNSc+6hQLmEccn4dPcYrhWrOpjakYiayQcCpBzASdMnQ/bJphwPhmftaXKFXb3HvXf9vR5jct8u/zq7Dih9oVpeTEcQ5fhyGPs/xjN6W05/G7qOLMOd07tg3zTA+OJW+yAffc2W2PpeFneMmkOt4o0a9PbbJ4+aUDT7jqCs8vQGrcd2/52o25MyoVWviKDzV0I728E/oc9PFqyb6S6V5gC4rJHEE4ALlWqZjwqPkPI7ktNnjKDH5etF1oD9HKSlQzJ46frNqs3jj8V9RMyuZFaRxQhabP4GBd6mF3qzQ8Xwm9DhIWsSAfmWvA3coKpofE6HkfFxWyx7q3Ji5SMDVIoSiRGL+zAOtZKQsnsRv1c+YfnK0NIc4yW+M/GpLFDZGp6wl7URAsW/oGvAsLbzbFClz1ZsIFFtW/3vu9cIMQf42UU7y1dYbrHbv1okk7HGkmDIJ6Pez1yINwLFcmxH8QL9qUSETTDX5msP7GmAHPMu0XUf/h8QkHyKEWzfoSO9rrLv+Duoje6ufe1sf3EyWA2GmTyplFdB3R3SyLz7du8Hq2JDvyTPFHqHmqmhj/MiPkdcWuGkBJfOrnO+ue8GtGe/0g8G6qbcx8p1BtsFhetLRAfucZuRjSQBJGA9+F+xbYLmyAUGTbTpR8pglbu6W+fWeff5qXO1Mu1/KakDLChPdVEdXa2o15BdvcsCrmz5c8ARg9LY+9pcRznwVvna4pqXiWubHNxzWntQZdwHye8tcYdvOzQmBkqgm59YP825s6GxsgMvwDj/QIruusaNq+tMxQO3nloroMXHynE5oZLy8+sukq4rw10YnrKUIsnRYkKMp7IPpw2Ml2fXolcV+Op2+Yic+IfsZzLIfdhoyJDVIwJFfRDOc0rjB/kY1O39lL118NvIpOAqqjmSBzZJ4hELwxmdlBDJmIA3+n8jRnn/cN25fci1bGJFwO8j+f2hAVdPpZuugM29NnhnfPDmKNYp7pfYd7nmV+aQUv0djv+jnqZ/Jm+9Oiyv4dIfL0krwz7uK11dQZh+5L7UIT4KxFApO1Qbl++pJwctWJPD49xxVaJRjGP6tMAtHAZzwMQmaQi2XYjDXhZK4ZzD+hlRDU0eRfpFxLZnZi6ABSit/ihVU1jD84MvnH+UJ+7KOOp20eErShVo3vPT6NqVmXffAjgOqASr7tdr98PJYVkuOoLv+LCbQKP8vcVMZuxIP7O6tK4/nruynzzeXikdZxNJzlHIPtvYDzyhSqH7Qhbd8jO6Qc64l/xHAgJDjk5v9bK7SLoMxz53rdtnA2nAnkwg7GKyzOZJsfqT2D0Hx4plG8yjW65eW+1PZIEa1V/i7ybCg4LD0PRTv80iD4jOch0zGJkxJdlgBI6SBknxd07o8Fca4tgYclynBTgutrOV6v22g04SG9lBZkqbD9l+FgBQjkGhtF5hy90LzzULf+cLpcrMGQXJhHbtFSU3HpKK2rCHFsJvj13vfN1RFXwKSTutLYPOjjg+0yYt0RHbV24T3quk1IMO88/Wa0t0GBwxhU9M1nG+SvZtdnb9DBDG+u61YYPfB437uc7rRGt06NHQhq9zCPxY4lggmERcnrGRYWBEPJ7dM2gXnJmYRx9vy0VynYphnfMhidBSKO5iSD/2zdC9hkPF6YjLDnRIWvi8SmcDtEPZVfmoidy2IRXkOrTo/3vhENMHRokeGlT90D7BkiK9DoK6hScJY9Kr8g7tgxmDxRir8uebCyG0Q/SxPQ1PR1tokT41ylfH8M9cZVwzJGIF1IcnoT0M7gcQDmFPO8alyZa0kgimG1S/HG0twxxk1cEQ6hB8O0qtmn9vvO+OKQ2f0lj9JBntR0TxFVEcHU7q2ib7XFcXs40F91aWLSPhP8KcSOpmWTu7nNmqS/bZ+bm/KiwEo1TWi2jzhW9MuCwYZKqyyth6UMeoj+GVSEA3HDgojkwxYMkA+9PYqVamPZvOQ8hV+Yy6M+i/RWrc2D7mOWvlxt52NtEgCi0JkRyMZUHZIhYo29Gi7KmBI7+nfdzAafrYWAhw7JqmRVzBs9wR6xrZ6xmtlVkUuj9xQk1PhXSER2lxVDTpMEDiQtlt5SQYDiaaz1tn1h5vTYqjTlE0ncNyKp428YI13eBg8mLe8f2VIjs+ZSnGDTLImmvLvb0kMqKCtdA791yie4dBuRCtx7i+cWW8hSA007KarFvLta6vQWVxM4EhgmfwYKfaKLJYqvTBYqYWdyadGYLQeEazfm99PzBA5d+W1Z3wHCkEEy4HydhzKap7/A47jesX8W4AvAFP7flbvJeFojENNDRu8+ReJdB3Kwxyje5HWL671m0vz2dlF4Y69j0K7sWKhiRHrau7rnjBVqYUneT29WzrVY0zX+me2DLDKndPDyQ5YjJ1sADreb2taKLDsjp5YOnHWjUDqPoN3lfeG7IRptTkDH29g40OL8wlZYhe/24+tux3XmC56BI4rN/AVo8zWhxmIRy2hhUH0UohCblpraXzelhMbHzsQWeMhMzHiDw6XINfmMjLWSMRhcvrhFB7od2Bv86211kBE6DORZocQQmwOYHl17RZab+46h6SWyRIV4gIAguLCPsZXGUMbyPAaUpi3oIUP9nySh2IhNrEA9ZOX4L4u3Pr2TmwiMPP546++ezJtcQWCDbVLQEnvUiFacCMOSA/4DnqA0JGW+mcAqXlVjI/Sxi1D5rDIzgIcKx7axRthQr7WYa5hViNFifYIgqVSehU8+pjUJU9JaPYZv3ukoUMkNZUFlieKUdC/S7lzeKZC0kZwZZq4McMHwxoIX/XT8ssnvP8OGu9eCQNftnBowIDj7eqbGF5xKNcJyP9gxH4VzUdChC+0hrZZQ4WR9z9Jhxxg6BDSXLHfjll1xq4Sd+kjuq8e5azCzOfC11HXvxkw+LFD/5eN7yAmAyOLO8ijG/cJ7lGHTP6ycFK5dkv+xLgdW1nreezMRhdY65uTY/Mm1HA/vQUJAI2bqvzmAJgsQNciq75mBFp5EYYtFLL8cirxmNSCmp2ZGkqFu6vtNviMk0Km0lhgXisauJJalCKcRfW4OZgyJuVPpApLha6XZbAgG5PX/fz54k5r4YnzTvxMjCiOJ6DQBNnCh+sfmOy2YjTR1kQv2Ru0VTQPiWEJ1PSrI7HtQEZ2blcv5I3L/hHBdTp5NTe6IsVrrIYrbNfQqXO0TsaaV1GeZAX2jtM66fU6XgpakXGhj/c80flnjJfLLgepPgdQBEeNggwXXDQfVwYql3k+EBAwFKQ+nfP3THkF8gyWY1GgSub1rvHAFVJgCAPFSA9Ti/rfL6C6AnBGKKDgKRP9ZRt7t94G/fip8P1AF60AaAi3YDRKHSL3eEN5uhyMg8/vFUfiSbn/BjcgkIz03tikbYHZxw0w7gYiJBfUcHhjEYivys2aTCLkkHHqrJomvf3X5ENOlEXGOE1PvkO7b7ZdEchNs9IHn8wikrv1daN0lxze5yukTo+aNx9vklA1cQBsOFCSDndY7Me5j3FUZme/C2XBtnHVOUnkSvZZVNK4brm1735WSiAvU5XIZbd3OUnmozwS8kU8BGi2NfAGMhbspz9iB3iurArF2/MnZ30+ObzPRLuk/yKoNn6S97Vb2ZQbfFlb2bKLm0+2vo/L+M+tPTCU9YI5gVqdCw+7Vjub8wXC/5IMsJDBFCVnV+jxeGq5cx5ROP/AgsbxVc2jzDRzsNQhSDCxtIWw0Yj5y9shK5oh6PhiLjU8Raq7s2bCaYTmvdiU27rjgNel5Oq8HNOeCy3tF4s3vKR0lzRS6u6+pvwt6f5tfwMdlTH/kprZdq+nj5EsLVDlJ6Ts9htb5I5dOgiB/6Gd4hvNW1wPWknnSlY0YKLVaNNU3V9f56QdIj7EBRu733cFft6y0Zhk0t2eIJfeGd1sXG23+wyX8Jx/z+dvG+/vR237VxJM2ik4QRdmfXqWe32xOxP8joEWMv7nPIk2t+36u+xp8kohXobugzUtrOgE0qG5rZlDbkHq3bmOuok5zakATSZdv/gqh2Z9gm7gsEnFTb9LhDZafQ63Sw6QfDbEulBeeloHdJ+5OP8riHUVtGyTVvo/UBD+rLwjZSCBXvcTkRGmNyiYtk/JhWXg64ryPfk74oSOc2eDRD6+MivOB/H3XMaOWuLiTAJdwZ7ZVmn0F97LXVS2/23aPXP1rt27O7Wapk/L6rhSX5+ivU+bimD5n+TMDM9FDTtGfbmbVVjrBVl2pWBZJ1mjM+U/zBVCVn4An3iPWedLCIzrH+269j3NBQlIp1IPQ+MfAz3lf4ZO6hFVufls6b+txXq4NDGEluFnT8HvPosVHiGLvRegJkjz7pPi+8Fdw4xNyrbThH7iNAEV0gtX2t1WitvVXrUUnlX4ArfpLkW+Fe9TRLvGGd3hT3XT7Ru28VSr6SdCv3R5WGJl0/F/eRAmklFFnKgNTYjGYOYsKJFk/bPn9NihatJldWIBqmOZjYuX4htNfM6tNFCdF6f6p+z6g6G+Le5qHB7xPu3MPTuSBfrdRTU9oxA6yi6Dih4JiDp6p/lWjivu5no1tEzjYUR38FZodVpjaw+7CchxDYuKWZ3hEf4Fxh9n1CCgrCXFIrugiLJ3Cy2bNHSpwJRm6UYjcIcRgfEq9VAZhnvIWKxft3a+M5RQZKImIIeaJ5DQwNmD7GRcKQW+sxH5CMcV8DcsHuagNuCE/UVHFmIJRBZxueFx189DolXcA7jC6m9/A4Gi8Te2Qu+Yc/UkGRn/X+1KUyzjLVTnAiOGF1STDfNGg0CA+y4uZg54OBEb//oy+AarWH6tFxMs8PIGqaIzh5WLFeSW/q3x5l3sNb8XgzODwLLy1ev7AKEwgDbR3CWBUte1rIB5k2JnliHrMWnA1iHMdZhxoUBB9358YeDYgFEHweYOX6Hm/YBnvr3dmrL4O22hRuNx8yJ1qUvnaHoCExVtkNAOlEn2muMfqucAZa+LcL7TcPpqgjSE7wX23UWZ5ktNY0L+NyUoeFCDLW8maEs9IhWFCtv2fTte/+fYNEH2xiKoCFwImxSX7vj+KVxz7+ebqM1FcTFXrz2kFOdKbZDzqu1F5HuXknAr/7tqDHERyf3s6rNRIiX+7WoCVfrLXki9qbVHAmyiLWI7ntsV8hclWkPdBnsTxCv0mzv4Fm07NZY+sT5I0Gpm0nkSQeZ1RYS3umEZd4K7bzNG+E/SHmoJc18kQi8gb1/Xw7QyqevTqkf1iy
*/