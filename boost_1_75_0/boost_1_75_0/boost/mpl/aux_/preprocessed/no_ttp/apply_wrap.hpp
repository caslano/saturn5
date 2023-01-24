
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/apply_wrap.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename F

    , typename has_apply_ = typename aux::has_apply<F>::type

    >
struct apply_wrap0

    : F::template apply<  >
{
};

template< typename F >
struct apply_wrap0< F,true_ >
    : F::apply
{
};

template<
      typename F, typename T1

    >
struct apply_wrap1

    : F::template apply<T1>
{
};

template<
      typename F, typename T1, typename T2

    >
struct apply_wrap2

    : F::template apply< T1,T2 >
{
};

template<
      typename F, typename T1, typename T2, typename T3

    >
struct apply_wrap3

    : F::template apply< T1,T2,T3 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4

    >
struct apply_wrap4

    : F::template apply< T1,T2,T3,T4 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5

    >
struct apply_wrap5

    : F::template apply< T1,T2,T3,T4,T5 >
{
};

}}


/* apply_wrap.hpp
DienKbL8Sg994MK+QCLHS54CR5FtmSfoyWNsrFy59f53kzH3aMgzP0wfsVv5M9X1DMVsQg7FiYffnxh8iHy4fOhuKc4q1+3PfDcdMmwZb4XPjtdV18fXqc8oXCsP6onP/+Iq6UPjI+GD24LR8aLD6DfHbjH+CElpnQTpZZ4tJoTIj9KHoYWuw+z3vtS911l3fkBVSY0ZA28bIrt02lmOTJPR8kCzvNrBZwrPcLpPitOyD+TkPsVXqe/OE4hTqd+3HU4MpRZ0tLnN9l5zks9E13y+vpIYj7bIkMQf/OFNxZL1FxlvsqZp/67oV01Uh4SpfKv0gEKFF3D/T1M/qfhK2pdOlJ+9fsPe2u9EKkLF71SwUHu0cdIeuUG8uh9GEO0kV/RrlX2hk+Fpr7yHxo6J5OWp7sqXpyY/wxwZiN+yNUhsF7epsNhvQxvTvVaGbaQHNCVJPes/SM47DHFDr7o/CHrS5Tp6V/5g4D8SnVsqGUSR+ebUTkZKYBwWIlD6XGkuhGUtPNZLob2zdtf9spA3AoBXv8P64d1najai9g0HnTg8cEH18+l6R01q3qxb/1PA3NL86trSatng5moW70VpoIOqkwjcg8WYpl78aAFkejDp8ELC/prJMatdfVgV0Uc3q3gWHzKvUW5FAu8hjKWboTNByj07zvORbRM2nZ2pq1+CrSyvmJyShLYdNiMP2zElDrw8wgwdMkLG0VPR
*/