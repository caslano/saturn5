
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/inherit.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    >
struct inherit2
    : T1, T2
{
    typedef inherit2 type;
};

template< typename T1 >
struct inherit2< T1,empty_base >
{
    typedef T1 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (T1, empty_base))
};

template< typename T2 >
struct inherit2< empty_base,T2 >
{
    typedef T2 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (empty_base, T2))
};

template<>
struct inherit2< empty_base,empty_base >
{
    typedef empty_base type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (empty_base, empty_base))
};

BOOST_MPL_AUX_NA_SPEC(2, inherit2)

template<
      typename T1 = na, typename T2 = na, typename T3 = na
    >
struct inherit3
    : inherit2<
          typename inherit2<
              T1, T2
            >::type
        , T3
        >
{
};

BOOST_MPL_AUX_NA_SPEC(3, inherit3)

template<
      typename T1 = na, typename T2 = na, typename T3 = na, typename T4 = na
    >
struct inherit4
    : inherit2<
          typename inherit3<
              T1, T2, T3
            >::type
        , T4
        >
{
};

BOOST_MPL_AUX_NA_SPEC(4, inherit4)

template<
      typename T1 = na, typename T2 = na, typename T3 = na, typename T4 = na
    , typename T5 = na
    >
struct inherit5
    : inherit2<
          typename inherit4<
              T1, T2, T3, T4
            >::type
        , T5
        >
{
};

BOOST_MPL_AUX_NA_SPEC(5, inherit5)

/// primary template

template<
      typename T1 = empty_base, typename T2 = empty_base
    , typename T3 = empty_base, typename T4 = empty_base
    , typename T5 = empty_base
    >
struct inherit
    : inherit5< T1,T2,T3,T4,T5 >
{
};

template<>
struct inherit< na,na,na,na,na >
{
    template<

          typename T1 = empty_base, typename T2 = empty_base
        , typename T3 = empty_base, typename T4 = empty_base
        , typename T5 = empty_base

        >
    struct apply
        : inherit< T1,T2,T3,T4,T5 >
    {
    };
};

BOOST_MPL_AUX_NA_SPEC_LAMBDA(5, inherit)
BOOST_MPL_AUX_NA_SPEC_ARITY(5, inherit)
BOOST_MPL_AUX_NA_SPEC_TEMPLATE_ARITY(5, 5, inherit)
}}


/* inherit.hpp
CPeeDvtL95WZF0B/mV93G/aZUfvLNDXoMxMytdp595thTOc/rN/Mbl3fmSL21X7CCULo9/SPIcQTphHmEVYRdhMOE04SQst5D2E4IYNQQNhE2Es4Wh5sxx1cgktwCS7BJbgEl+ASXIJLcAkuweWvu/xJ7f9TbJnn3/5faYMfZzC2/w5CTXlu218Z73S22u7I2UIsJS1N+u6fV7vYJvU87Y3UdqPymtL+TzsG5oNE5LBLeyl3W0nvNv6lkm8rQX4bVsfjXZHnzPeFGI9XO8ZlgbS7Hyb1NJgwgPQi7JKebnzaQMYLr2B8Wl09eNpBHVDW53iPsd1Unm33knx2J7QjnzaTfDobX9r9bt8WaF61+yxEEjgseSshtCdvxbq8ybHm95wEFeTJdGzdM562ZoZ1fNJTx2o/iB4OzdiYrC91r3uX0yHlHCTHZry0qS9xaMpJQzLnoXn+x2aCtKlvQ2ZqYjTGU68x+d7p6Y/Nhshi2o6w0xz/2hFq61r7GbbPkmPV3V7brJ5lfY53X4FSKdff5HhZSxiktM9U81VJyYa0HU6lcXjFY/MathuW9emevElevfMyRPoNdJTzfXvCYOVzNVefF2X0d999GnKWvMxBbZvlvZJWlBw/9QhDSatorlG7XWuW1WE95za7SvppuvSHV/NNfxjpl8w1azcceJth17FzH5GrUUgeRkoeTlTzbbucQB7KTPOQnDBc85rFEnieXHUyUteOmb9LO2ZPHU2UA62O5K82oS7bRczzzV/FY9Ib50ebXmmo7z4ZTXoxRull5titeY6A03OVv4nBMTExzDf9K0k/0Sh9zjWB1P8Y4slIz3Gnn8h6KuvatuxHwow/Ezaj9POsXECsc86lzo0+F4MkD2nVffOQRB5WGOVBncgid26O2j3n3PPRipCW5d2u/4RBPsYr5wdnPuyzfM8PyTZHnt95kHO31/HA9t7HQw3f43+Cco5w5eE8jn9J36vMz9bw7dN5kgooM0qP44/+HFlZfqSpLVOncN8ylSmVfK1RGvnZgRzj30ZJmTTpbQn33Y/lrEQbpWfLt2cEkJ4/+7BTTd/0f2Ql3ih99eLmf/qU1yt9ByEzbZ7XNXVLTd85NUYofWmd6aspqseOek2t+HvSf9i7E7goyj6A46tgqXmggqKiIt6Kioo3KYr3BSoqKgoIKCjHxqFoZKiYZ0VmZaa92GulZsZrVvZqRWnl+0pJZmW9HVr2vlZUZFRWWu9vZv+7Ozu7K7tm77nz6enLjDPzHHPvPM8zuuu7XGO037ax3aeipA/9j+X+4kPCPSxbZBc/rb8SF8mlrvrvMJnT0VJzn1Gluye6pLsnuqi7B6piuk9NZ+0E3O/33N16/47bD7jfz7jj+vTO6v07q2fvrH2F++0N3G1X4KzdxXG1/UCzS/c8kfPDsp9icm746omLHY9fu/YAztqNmOpZyfO5PLdv0dWzCpF6yb3QF0OxFfbDTtgfB+MAHIqDcRqG4Wy8ERfhEFyBQ/E+DMc9OByfwAhL/W157sZkSY+2/vadUn+7CBvjXZKuzdgB78Fw3IbRuB0T8UHL+uU5G0c7WH8zzffWm2NLyW8AtsdW2BVbSzxtMAIDNfXtjbL+frJ+bX37DrL+zhiIXbAjdsUQDMbe2F3WV04olfWdkvU1w6OyvtGyvvHYBCdgC5wo6Z0k6Y2U9UdhP5yME3AKTsGpOAujMROn4a04HVfjDFyPs/AunC3bMRYfxzn4JM7F5zAeX8QEPILzsBwTLf0JyzMsDpd8aetTLpftfCvWwQLJ50psiquwBxZif1wt++EaDEdpr8C5Sp5d5ZmWeNQ6kHslnudkvc+jL5ZiS3wJu+ARiecojsc=
*/