///////////////////////////////////////////////////////////////////////////////
// error_of.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_ERROR_OF_HPP_EAN_29_11_2005
#define BOOST_ACCUMULATORS_STATISTICS_ERROR_OF_HPP_EAN_29_11_2005

#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    /// INTERNAL ONLY
    ///
    template<typename Feature>
    struct this_feature_has_no_error_calculation
      : mpl::false_
    {
    };

    ///////////////////////////////////////////////////////////////////////////////
    // error_of_impl
    /// INTERNAL ONLY
    ///
    template<typename Sample, typename Feature>
    struct error_of_impl
      : accumulator_base
    {
        // TODO: specialize this on the specific features that have errors we're
        // interested in.
        BOOST_MPL_ASSERT((this_feature_has_no_error_calculation<Feature>));

        // for boost::result_of
        typedef int result_type;

        error_of_impl(dont_care)
        {
        }

        result_type result(dont_care) const
        {
            return 0;
        }
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::error_of
//
namespace tag
{
    template<typename Feature>
    struct error_of
      : depends_on<Feature>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::error_of_impl<mpl::_1, Feature> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::error_of
//
namespace extract
{
    BOOST_ACCUMULATORS_DEFINE_EXTRACTOR(tag, error_of, (typename))
}

using extract::error_of;

// make tag::error_of<tag::feature(modifier)> work
template<typename Feature>
struct as_feature<tag::error_of<Feature> >
{
    typedef tag::error_of<typename as_feature<Feature>::type> type;
};

// make error_of<tag::mean> work with non-void weights (should become
// error_of<tag::weighted_mean>
template<typename Feature>
struct as_weighted_feature<tag::error_of<Feature> >
{
    typedef tag::error_of<typename as_weighted_feature<Feature>::type> type;
};

}} // namespace boost::accumulators

#endif

/* error_of.hpp
xpAzB6a7P1sC7gcIuk15ZPybRVXE6NFJter7qrfjfg68qYbenbhup/VmiSpWVJz+marHxOeKfhrsqms8d0QF55UhIsDKaG9QbpURuwRlFv2FBUJgTnOzIj6YbWNt9Z/ARnYBKLWrymS8aFPH4xSiTtIef2/sv/kVtyrBofel7Mk+8+Aty+PNgjjQo5VvohVnhx0bf2tkfeUpSQyPi0W7iTDoQIRB0qxdmj/LLbIBfKqemUlhOhx3wz3I17FXClpmXmhoTe/yVVoSk/3b1Agm3dfzkLwj9x4+i/NAbiNYCBLKDoVTfBt9c7OhJ/iTCByC5CpUC866Bvu68TalHNgCqPyJ0bZM2/HLBVg3q5SEk2oTpxYxdFs2rVESvLPEqmepDc6ejchpqcQLYynKlWdfovXxqCErcmv0jOa981SPuSkBK9mMBzfcynqfcM/TTx+tEq6tomXtviKYnjRFkCAhu239Q2MonMf+/jILYWHlaRGwUK/aunKMD7Z6cXWgGrGntHGrtHGRuBHF+XVJaWFQrY2R1JQYLwldXEk/VdzXOxcfR9M/JBwR5RV1E0g/CjARpUURDfFpCaldVQFdWwk4DgFV28PbYkt9o4ORQpuTU/ODkkLij6wfyGgKH0P/fBq0bvtg9Y3maplAGXc9/IXWJ+f3kyYWqu46AHmmuauBZo1IjIj7FkYXHoFgcdEA9AFcVVXZVNFd2djYQEBcBQ0tkQ2JiQ2BJKmYLPX55RH1+QkJGSiM1RkghcUJCf/RuAsr43NwcPyljgFgDc1Ji8J5LAQBAgQExIDAwAMFxROUFoR9t8GLyQKAdvWFycWD9AcCCAMEDAK8WwXufVtb5MG51aVned+RAJSRD+1J1P8scMT1hQYFrAaFBMYHGT0D+TTBto1x+NGt4fyZLALqAwPnHMauvNz8SZY4eq3ROpdR4oWnRMMa2VH8etGiiH260aSAf4WjSTqxwUUZpCAE2t/VNTjZ3zM8+RMWKmobFm5Xf+/ri73JCxELvlrg70UdEwpCBofFgcUaQsyRUspWkVoKnhGIziqrKCn5mOOh6PzsM1AAxAIAH6t7A04C5usbBuShuO1zTOKHzXn5wycdHxEFDfJ5QnO/QvXzARsfFfCkwzb6PjhTP8vrGAZbP/JKOIjQlLL2xMbWXjoboUNBPJixk8m9XyZjibo25tDGdm1Jw5oixJyCWQ8XagbpXewnwjzoqrENxgyAuZZUYoHBm2LJQoYNBwnB+/m5lkeIWa1MJAwkUybuI+6uedR5wkJNGnvh61rSj1FG8i3SALtHcRq+yAefkmQLK5reuytbYX33RCLz9fpJtn1nZIHN33xRufV5VHZDzyr+RUJ+8kLSeW+xMTNwoLac69oNIQATYArwlx9kLl2todjqIEAbdBQMlFxbQVj+rwnuaN2MEz+Oy7njUzlABslLWjeXOklTsmCgmpfbwQQqY0c2jbxN6mePl2Vq1fWDhBLWRhIRKWj1IKXisi5CyIVtuZicYvyygn4cK3eNj0M4nf9VzBVjbFHSkBhMEBrOFG7O7el+UaUe/QlYBdvAxnOqoVFYDl23dNNJwB7lFDB9DMpPQS3O/sN3ysrPRbYkoiW2bhzxLevNY8/phneXjZWfYa8O2lDzbgbMqwxndmlcw5rCFRVmufk5pjj0ubF0sbCzsG7IsSXQtJXhyX3ieSUwyJf+C6KzbkR9Y4NuHD3oRnlRBFkCU4R/XBVG65WPQ6pM8fh4vvHP/PT92Oeor0/rTHbj1zZ89o9INdrowHfFyZH+x9Sdv6/PfYcIwGIOI3nvI9rPg8/gxbdjKhsABjnAaxoA8OVUdicOrit/wHuDhp9v0Aet5nEClmc6CgGgLitb5eLrivUZbec8XsnbT4XXBCjI18njVUNJtf/7AiEwIiYQJOwf1MzRSFgA3r7eXoGv7S/4WNlZ9NVxutpWCohU1cNyWqQHUl9CUOE3Zp/rN402BhUsizGi7WbnbZPzkPvt+swbNX7wW3w+1sOH9KXjoX0hJqZvYBEv0ETiBXBqNU8eKji2K/DJaclsNXKvfXuaOw5kcPvXyfhAeQ3z1Du7+gHqD4UEtXPd003kis/9a/GI/D3C0wfjlilc7qm4iTt5sSUFvYI/KoZULtovBWNqNIfpFsug27M6TjxQS/duFhkkd5OuHslv8XsdWOWHtx6YhSoEqsZpo2HH7aMWJ8gHfMjHoIpZwKAm+GrXqjDQoJBG+kE2Vkau4wGKDBZRcApMAxrzhIpuWeXKEUgKArNADhoHneD3N/5jajt5lAwikXOeKELgcpCPjnLgu54h3/tudMsnnmiB7kW8RMz1llyVmrbKVIOcpw1ZVKIazPUttHtmCkMutZX3uR3iQgKY1ufM7ESCr0+NCrS+BECOSMZbCOCHFQPJjq6qgsssXd1LzzWddlZw5+gfdW5+xyJDNavHbJA9mkbvQi0+CEWm2phYrLS7vaP+Zk4t9oTHA+y9vaLJTA39POnrh04GqUW90D/3fJGu3IySeStY6oppu1JlYhHmn9eWRXqtVCSluG8t8uD7x+dudSGQ+iTDVn6HjnMCCr1F9YApwFEUduaRTFfoqFFxEDZoGQF/gvjomfktJeaAyP/N5/GKu7PKMauJw5S2+l2s6Y419bQP+P7EXNPBxz7wnMAOgNK+/Fin+/+0kNYkBWn4gANgPCqIj0xOHShQQf80wE8MCYC5BsXAQsD/cRB9+U4iA/jpObeb7XHW1GfYL8+epjFuloFSs+UWIlNgJKsdIDwwAavRZWdnI2ldZXdr7b1QU1bmu6WY6EfUDCFjQwGXTjoEsbPnHFPSwsG2nLTMCY5AuYzqE1+6LDIcPIrC/j5+9W6vJ2M9Mzy7bUwFq/95tO+B4W4dVQgmGwD4SroArv8aOIcZ/POJVsHa5epWgat8CD+k2a3C6T5KJOVeq+8Z0t/64pZsWtFQr1xjCdlagLqxIAV2TyAlGu21MqZ1Vc94i7CT91cRGfQ92ERjvP7OaSg4vwYlesBsdYxQkq7iWEnk9Q/LgPbsS5mb5zmNLLE25G29LLG6D47z5eRs5tGnbKLuJwQ9Jn9d1FzFtzsby2o5K8sfGXK3CNg38vx4TIsbI2lgwgYT9ygLODKKRsomMaUPAO/r6YMmFb6H+y5j8SS8wMjhFWuqz4sCKLcv6dflbbNo/z1SF7Tm9b84jecTxtKDgRJZVYZH81/4BB1AHe8+2M7PPFSVOckkMjJTlZVUhNaoPZuombsf/JOjeysaAVCDTxf3Q0GREJ+Nj4tpqNOGlzxgvI9mU1ODfe+MoJzGl5o8TmdfkiAu3RiuXY8OYT8Ktw5GDy5/SIG9ZWuZEOoaaumJDIziWO9fn+Kys0IihFAsXc4NOX3Qb3dgAoUeVp7tah0++6DZvvugfSvxna91MG4HEENDAg50UofyWkpC0gcfY+qrJgT1XzX0tO9c3cy0uz3LBQH+UHICGeYqyHdAr7jts5N+Pjzxhp9c5FEjd3ZOgh46MktV1HnWgeZ+2mpra7O0RxWbDvLduIgg3dNKptRscDX45N791dbs+VQfpkx5imYNxsTBx7mvX5D9Inx4LK181198fag6bjFrLdunYyLAA/QlUiToWYYsvritTPc3IGuTknDSxrg93D2oB9BdaRevNfA02uZ7fihmBBGFZ1CppPaaWTCEvEC39V50wFn7x9FMLe3xHNB9MmyntnqkLv083ujZmFNywGR5YzFWl8KecXsE1du/fnG83Hcuq2O4jDlowYUQrcm4dWwf6MXnu2hQh7g0xVoIML0SQQuYOIRN8DR03kwlcEY90/xJEOAjexnBS75WlvPXpeYunYtx3yzDTzfnQuJifw3ztqjknh7P7jM1opKysJMO1cNLXiBtuAfiDJmFG9vrGdoLYzzS9V/nZtq/983XTpCgjkxzjjF3/Aq6YSMgG5VrbHHEHUGCIo2u4m+AuahljorDwXIubpPW+MI1C7Cq/C7Cmv5SoAJ+lYKtf7P/fHYUiQx3TIzL+jXgpjL1pluOl6GvGMX8AR6s2uImNDSmMsqPrrEWTS5ZOJR6r/WRcb7RZj6bZXb5OV5v9JftQx8GFD8fGtqj00wGmqxKZ+NFXeLEPZ70FGzvIG1fTJ4YZLK9idnL4xvXzEXkAxQHeJSmzaeuopqf9UNZegQYqkHzntvIkSqbm0PkF6khFwDegJev+/pwHGmwluV4/9xAF0rkhVFTHdAf0MeVgB09UiNCjT0Z8mcs1veuifq35EKfTKqf4C5G/pD2DJgBlOm2t+xp8vokpfGKEyaG7c42DeiugrUqs6UXJFH8jIXMwKdQ8i1O4WTHOLR8jRRIXLdckY9046mZXyZ9xKcLooTQcEcbFRdfWiZtz8oY7QosGbl1S1WhSQstjMlM3eUc2TiozdIh4s0NkHnzvNRB8tOJTseqojXdJdQAp5iV/B5VISSac7I8pTXSULPH3g2kYNL9Arqf6jQk5AxeNqJqZV4RdBuz1SFz3nJR+G3MJrA6b99hzBEURA+TYYhLPl5VGmGP24+mViQ2uMJlpFQO5GP886VcQkdf+EYEI1savn8YDMKt4M3NBH5w5yZEqe00uGDxkoWtMmqw/kdcNeuAcKHfeiFBfuap9a8W+4DsFZVm+UNhyUGhdf22S+ie0f2NnDbas/UwnbaEVAVyosgyiXySCbLgHNpPf4w8CU7IJd/4rRBuzChKSTj5g5hE9wInEvpEHz5hzdKC2+ncKPossjJn4ysjKYJxEoSCk3PhbdBArZPsCSeRExQlHknnZpDlJZ6jxdlixTm11vFA8CGOQIaIFKAVunyl1MPIWIsiQks6gMGdnnLwoeXpyMZDSHc14n1wbdNjlWJccF9FUYSJUdID68Zk7NxeNyH2ido1PodzmcgZ/imWdhgm9ANL06meJrigrBu5TEAMjqQKBRExWIi8kGBMBybzffD5SX0xcsue5i/OUIP9YZ7pnJmNWWezmD+PT2Whnz49NhQjR/sDL/l2LLiJ+AFWx2I0XXtCXG8mfIDD2jQdCo6c9afHpj9TbnLsRw/Kn2rPiMHGDHGEmAajz4J8prQjUPnN6P5gsFlKCA3ar9TSjXOJdeFA28MtsLmNXsG+mwbcvf7lsp/vch+jZlWWdM+A9NbqgfuGbWrCPJL9xpPzxEZ6UnkRXWQdgr3kFuh8rOGwSNp2tdcYmiLVs6nvaAKTxWVZ0M3mmFNEVyCePlxjiIVsHT57iUMfN4mlseSv7SNVcIG4vRxvLUHq2CTciizIimo3p5RKd78oxkrgWDCvieBGaJU1ogIo/ErRdVx+RGFD+J7feTfrGe8NkYpeX+35aqDv+pBz/kHg451UM9OV4Px0LhSpQt8yO8uPyobm/DWlPXOGkDEOEzcQDFYLHYs7rjksqR9QlEEf084GlLxySN0SiqH/YxVBPPLJEFLkNxshbA1tg6oXfcHA9Ibraitb2RjkZvQFQ2P4DEbgZCZxc/wE6c5fQ4h0z4ZP9YpYIln5S2fB2y8sqJYHde+rUO+2Uu2MxKeKhwzkYajW3s59G1jFwGV1mKrqLs6NtSgTF9o7R65hj50GT0cMlgbjM1U8+6XXWbsEa621/ZWo/qbL+6wyu7Wr5Ne1u/yJSXmRjef78fgPosW+EpQ8h5AgmxRJu88ptKVmqGswbheERvYHtBPLAn+e61jV6E/nFqZHLzjaVhoOxk+u54NLjm48aqgmZtydAq13iZrp48f0P0ZPp1KWqsje5tgzXnhrtW4jL191BqbXGdAETxVtxZkBIrcLyoUVLTtw836+I+h+s5N7f/yUu8F+8r8mJvpHOL27oiOCDJKOv+Q+8/G+S6eq5g4xFClZIbS3nUWo7P5MbOE6VnpRf2e7ABJ7hc+IoyZvxt5I6Ed/Xl9m3lRDiyoXd9Ror7+9YwOyzt2SBVzX2FSHSxlzbAdldf/Yu2/1/dxyeSDB/cQrXuZ1quv6VsQkttwMe++E4mXcBi8WOvGkGjIaEFlfxQngY1oXLMXTPkpL6t6uiv34b9m0nZXyGHhQzRyO6wBbGbxyPMF9ehGQ4TU2pCrMdHB3yKV+n2klwcbLUSAFEL2LXEHMapjLRJBEY1dSJLo3nOiNaa7gedFZAzZBcrjYb8gP5ry9hvXMtA2HCPIYaKlFLr038+DgtNiN4o8yBa/3/3vbl0ajMyj8ef3MaPVLpk65G4XJjW5tkevRYz8+iEsV+aHfTezDONKAUEnhuvWK7CkdqQOULMjbgKHxs8vyxdYQHCLrdJ1LwsXi0D/sNScBJ87t0A4sgdoBhNFYIkiSEh4FK6AlTcophtup59xmN/CGiHONAAHrzIqSguoKv84g/ZRP/9frxoPxdTd4Sb0IiZhjTyJ9tqkCZlJ9497flJx5bMB+AVwWgHZC58Txnt6cE1B2DSsTIZONJftGaKTlZX2e3Wn8Lnzk/l3Jzo8HahWf3uR7JyBgt1CRnWDfx6KkZBn0ffy2lpA3SZBfQ71A66LFA51idv7Peep62bpHUQQXY+z5Zn7wYNE0HY9umU5DdJjLW+uHlO5mIKYls7OKYmyx2biMKv6uHEJNjR6o+wIIqvPaHcLgCUT8b9Tx2umjwHDSjYGk+DV4QRq/3oOIxi1HZg4l6Cr1YBnbeDTxi/oMOfS/cYsmV0/T791Pedpkv/n9243rQ+gTCeOWd5mj7OZZqOt2f6lmAbYdNN7W7YBZJ9pTX+OUKga+pm2LyISNDNpAT547C8upl+cm8XGhU9pO1YFsSKVSUYksmFhbv/43w52eerumOwxmautrw44s64Fd56SDdynzYUSBicgBrRWCQFlQ4xApTmLDJ5Mv6/NTZsj067h0wD2rrfQ6vksrs4jQG3MSRrwSnmlVivnxyMO0eISJF7uJscSleu9IxQM90f4Bw32+b/gIKg6RV6MEbxrbeA6FkySkYk1GFxAXs/yyoFaiJHNxe/tn7dxr/aLqqcq8pGWHkXI0438bjHZBQw/KdA1nYX5Z7GElEjZ+8hFyuc5Z7YB+zi4S72hnm8nISFXtzBxIc+7U54IgWdcQ9pbnguqXWUtykcqlqKiq20lp7ytWZKh8qR8cn8waU67vbc+DnUjzz1JWWyhV2SrbO69KQH+yoHoUrCEs83JCEPp6wtauG3EK8Sw7UB50TiVhTbFIGnIduGtzcZIm0td44B2760oPltuyXkEOLM5Qe43X1ujmrZZjekFcrJNrmzeoHRzku5OR1TNKJqLdU/ss1z4DMrysnqoGK6pleJe3lvpzS3cL+AMOnhv/dqxTG3YXUEa2l2u6jNiNXBDx6MCngX6/zVrg0fyrk2v6skru2IoD1dbmFCbhTJYsO4SmYQ0SuO6wU9cvs00Q4TGAEYPblvgIOlvwdcHG/fhAWG45D5NI30AbHC/Ro0QYLLgGG2lgLEl9/NuYSJ/BTrM1AezQoYpDkCPLg4qNZQpoNBK6tin3osGT/pq1VOC9bvSyQOJQYP8DRClVu/umNfcj5DHQfZSCYOLplsL2pfY6aB2/m9QWvoJq84mdz7KY8XiSS+dKEDPJqJyEYRJps2GMt2et61hAw7AvFsngGvROw0P2gRIvfduXW1Ro1n6F86+2aNe0eGZuEeDdSyBLC7qmZEvXkBtUTXZaBoUxOAzaq3I+DViXqpNis2pc1c+6LmiusXR81F+sypqeymXf7Ioy1Sv3H1H8YVB+q8G4e7eO1UTBxtIckWwUy06G25h+6klgufM8QmA9ZcZnaAJ/jRih5KWwy0yEsu2g3Ym7/bJWEgoYXznhYUx6vMUttjqO4ehJO4H9Uf2U88kpn2u5rQXrBKcPdanYnIx0ucAcHKvLOUB7Y5KmtPz5AvWg/9sfBRIu9E553nLpZuS9CZXGxJyORaNtLcmEFXqlZf49Qu+YsEaVlNnJF/T2ogUktcIEcbvpD+ukl8cChUmEi8fuUOt5gsMXA4HucL39zzW8rJd6/s7Z7qf+I7UXX/5A7IQkKikfGOClwd6oDgJluMktqJgT8BljdO/QWqmZyhZ7DPVnFmSt5siRd+W+GzgFzfALTK/A7LVbas/LsmbGAnXodUJam8lbCRClP9Za3+gSdw69mOeh8KlPgqx2IYS4L4I7ttQA0yBSlqw4WTHGThDO9pUglgi3Doy6Iv2r+4AFrOsdbutH4Pmuca7OfHU0Z85cE+pKtzlGwPyyU0jYU3X0t8725Aw+sVK8ptuH0cvEhj3Jp6B7BFuFzFoT+1ApjkDgFHdr5Gwknv0mHDsU1oeVHkc4UoHNzHt1z1FzmQXQ1ewSILZhEZvx9bB7s20nM/W+tkkoVVf5aXSrptsABthqlrebhDv+46hdrP/UNPe75qS40TBrDodyxTz2ngACLP3T80o1gY4L/KAvBoKkw+PSt14cU/oIk3qhIjWWgCOJ10bApZ7rmQsLGaMzQv5wTQToMRUpIjgWCRIFanCWsz/4h6iYjuzjRPphqOmA4YK+R99Jl5vfCmMFtaO96l0VrOpfandw2p6HV4EIhkU0IqqSWgXRt9xc8ZEUfXDBpwbl77EO6XjbD8XcczfQNOYihzr3tYXB9cCbKY82aq5IrZJOGpev3Sm8/GsY9hDkWs8Ya1PG2Tgcrhs9kYnqHo/Ju6hmYKutPuYnyMXv8/AoURnmuw94HeaJ1iHncF3N3FGN2ItfRjw3yvz5ZHzXHEZF/jiBurbhqjc4QUaIeiP9k7EYI8w0rgENVb7nW6rzGlgDb6230MyBuBcJnj1Vj80nGrhb7bflbUT2YqnrcOiVNI470K4oU6lT15U+bmac09B/WVIwJldjdI/xEG+OqO5eB8XTQRxhJumdF3wzOkfO22KS8YBCkAlFYBDJSHsOLwr5cORy+QZpruRRnhlbf5e++MFpoTi+wVLpAjvnM2lpZOSnm1QIPhg+V/6nXGUQccfbu9eyHXFPO96Rd3grKgBzoQ0x4hirvwBciB7cpqATj0xLlW58nS6LaxG6Z2DtjYA+YuNkUBZTgtYLW9Yr2WsK33tKOYkE3uUNQBb/da98sa1QUc/8cUixOMCnlSjSM1QgodExiIw+foa+XstUIhdC3DGr8KQDTqd56BvQeQBoE5N7ew5S4ykPxSBRrpJ6IDBYbiq/6Y6IZ4Lf/FUpnOMi6hhwm5rIO3dwn2zHXkWyxA7G4LCbJDhuW0WuhuE=
*/