//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SPIRIT_KARMA_AUXILIARY_ATTR_CAST_HPP
#define BOOST_SPIRIT_KARMA_AUXILIARY_ATTR_CAST_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/karma/meta_compiler.hpp>
#include <boost/spirit/home/karma/generator.hpp>
#include <boost/spirit/home/karma/domain.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/home/karma/detail/attributes.hpp>
#include <boost/spirit/home/support/auxiliary/attr_cast.hpp>

namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // enables attr_cast<>() pseudo generator
    template <typename Expr, typename Exposed, typename Transformed>
    struct use_terminal<karma::domain
          , tag::stateful_tag<Expr, tag::attr_cast, Exposed, Transformed> >
      : mpl::true_ {};
}}

namespace boost { namespace spirit { namespace karma
{
    using spirit::attr_cast;

    ///////////////////////////////////////////////////////////////////////////
    // attr_cast_generator consumes the attribute of subject generator without
    // generating anything
    ///////////////////////////////////////////////////////////////////////////
    template <typename Exposed, typename Transformed, typename Subject>
    struct attr_cast_generator
      : unary_generator<attr_cast_generator<Exposed, Transformed, Subject> >
    {
        typedef typename result_of::compile<karma::domain, Subject>::type
            subject_type;

        typedef mpl::int_<subject_type::properties::value> properties;

        typedef typename mpl::eval_if<
            traits::not_is_unused<Transformed>
          , mpl::identity<Transformed>
          , traits::attribute_of<subject_type> >::type 
        transformed_attribute_type;

        attr_cast_generator(Subject const& subject)
          : subject(subject) 
        {
            // If you got an error_invalid_expression error message here,
            // then the expression (Subject) is not a valid spirit karma
            // expression.
            BOOST_SPIRIT_ASSERT_MATCH(karma::domain, Subject);
        }

        // If Exposed is given, we use the given type, otherwise all we can do
        // is to guess, so we expose our inner type as an attribute and
        // deal with the passed attribute inside the parse function.
        template <typename Context, typename Unused>
        struct attribute
          : mpl::if_<traits::not_is_unused<Exposed>, Exposed
              , transformed_attribute_type>
        {};

        template <typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        bool generate(OutputIterator& sink, Context& ctx, Delimiter const& d
          , Attribute const& attr) const
        {
            typedef traits::transform_attribute<
                Attribute const, transformed_attribute_type, domain> 
            transform;

            return compile<karma::domain>(subject).generate(
                sink, ctx, d, transform::pre(attr));
        }

        template <typename Context>
        info what(Context& context) const
        {
            return info("attr_cast"
              , compile<karma::domain>(subject).what(context));
        }

        Subject subject;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Generator generator: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    template <typename Expr, typename Exposed, typename Transformed
      , typename Modifiers>
    struct make_primitive<
        tag::stateful_tag<Expr, tag::attr_cast, Exposed, Transformed>, Modifiers>
    {
        typedef attr_cast_generator<Exposed, Transformed, Expr> result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, unused_type) const
        {
            typedef tag::stateful_tag<
                Expr, tag::attr_cast, Exposed, Transformed> tag_type;
            using spirit::detail::get_stateful_data;
            return result_type(get_stateful_data<tag_type>::call(term));
        }
    };

}}}

#endif

/* attr_cast.hpp
0vTEoiTNGffc6xOrBsZhM3O+AZt8C65E/x97EnaY+Ohm9PVMO9UgeLI7fMQrMQ2vH2UCKLZYcbByyuwIqyYIGWLIQNP44s/BwEDXXRmBlCKRir6FsH6Ios4EcbQ4jYijPsghdptmMPBvh1zxfAmIsY2BX844yiFj5osavvFASB/GPtc9RW1oPUyfoVNJ8i5Sb4tcEjGxgYeEZXv7gPhRSv+f077DqSJLeEvlOz+bqZWboWfSt41+VMpYAoif8alEsHILucGceB/tgPjD+UCtzT5x7wPdeutliAUB7651hCH0lcMZv/8DjqkNBieVk6ryo/Sko/wTph8EHMK2iBNf4OgsdEZ3lP8Tyy3Ed4H2OcJvoVWQhO4ENsbcHXW87hWO1wtbNEvVv50D32G6x5ck8TsUW7T5GblF/p6C0uQVQHjNhLWj94dOWZQlaMYu0F9UZXGcsj2H6CRq9GuSvkQ/DPIs6tFCE+Wku//bpAdGa9pEYzCBYqjMgVymAU6x1XnbtTFcwBIOHvFARp/rCH3m5HlOYYgBz1KFb5TwyEfavKcBV9HcQagV2gisb5JUBREQ46P0wbAhgwwIwT1imiaPgB1NPktcLAvN7nB7RCCHOjbKoM82s+5wjBxj1WGP+K/x2R25BkwlbOMLwx0LAv17z2nlTnLTNBqWWCcTlzCrvsfvP/Xrvf9UbKCBVG0Fb1FEg4WWLaKN+ydYPrtA6ppitxQDF8qpOBp6jsNDz0k6PMS8hUGH82qdYZXj+ZmJD7dfg4hX3qxzvcbI0u56rZTD/oFumc/WR3kFYx5TVWaH24mY5oD4Y5Q58gTy2cVYIdDP2L/ZKM10GDFRplL6zigbdqEsl8eGmeEO5oJzNkk6kAUQNItgE9toi15kwQVWLKuQjGnRJlBReVSUTOuTXFGB/gSSxnfzA9f02TgSnItTX9jLt/aI5Eod5VZJKBqO5jIiz2AfDR8zfM0VZLi/doSbMdIspqbhgjKEP31BUcTT7CfOe0EBH3X6R871sV+yZiL+iPtWmsVXLbjM3aaVtMvatLvmqp6mrOpQl9mxFmCuqShSXL8TBD6h7n6Oh3D8p2dGjmzt78xqj15iaY+OJfR7EBfvq921wYxwx73nUUvPgRWjgVnfRPtZvqFWEl/YcS8xHdGjmlGX+665gUK/qUicIcKUSAQC29drgSqGr38e3pbNfIYo1bLBj0THhaaKv4HCPd8HfucQbeI1yQjB2hOVIIHHcoLe9X+1HOTIdaaL0Vx6rqPHS0++8VxOzwx6DMk/9LFX3s+0M+7JjQrdb+uvDNP6+fvHRLnyouEvKRGU3pV8okDaeL3cZMV68b1H2+Z/CmLqIIEJoVu7WGehV1DCb0sNMIXu6qwArqsTEgIfsKBAOyQiyinazFlhwlrhgbxs1S9jQlTLX7t1LpAFrzUpy3dQjes+B8PL0mRtn/jpr1JM1ZGViGcB8EQKD/R3rRxPfxVzTnWs0J/GCpWl8K12WYgh1T3zuTyrI3Ljole6ddHwy5iMKt/xFm7LgOycsCrFNM+/DL6oso/BpdZKE3irnmLJCTRJ6L1MfjXLr/Mjq+6genzZlbe5SuwFcPPONfpElFj36BRtD4TWyIL4skGxYgIX3hQdGCslMHxmsdHQ5IXdOm6j3RDu1nVvj1Iuldjjvhr78NqXqjFpuhgX5Lt/WXFpRMYPiSbWQm4OmINsgCX3NIJLMIJf3hKblkv+/n9btj3+m84E2TYBJrAma7AQPhMdvk4Ct4kf0+SX5fMBJVPP8qbObDuNxa9bYsS4uoFPyfhIToYQPVpxM8FvWbZBrn+4/Ab3eoQEp2sr+A6wfT1Ez+vq4nmmywTL/yk/E89zVKbWCfJev4U1YcQER0z5EVewXhe9V7BmJZ91BQvcC1yvOI1CuPCaVTjpw8JObDUuP7KQxp80V53mMwRi0+YY8r5pX/B+oOXY4IUxXFn2m4JiDd61lt1KiOkXHGXV0lfz7oMx/NtNuPskdWJZO8t4PcyvRXDZDhbMZIyCIR8q1n3jqCxY7syxuTy25X9eOJ+BQlw1GIfQqRXhXxNo1C8g0FDlYLsPBH5e42luKyTYwG2IdqbzhfTd2SOmd/EGWCLKxrm/WX69WxFBj+ZpIViNWLdpfBWMleK63N1Kei5FL2+QouNm8Znao2dXimsW8rjHQt+lUK0mKsSWQWiRreJZAOu1aNFXoaDtXmVoTHk0tpsqKRReooyEwSOtyldE8HOsk5XoW8HCg2GSp4cpz/GNrk9hkgSdC/y0uMbT1l5AcPjIUZhRQO+mTnhxpCFmRk4zgbbum6yORnDUJcW0gcvjGYvOzmic12lm45Kt7psRraJuzl3A3TSQtYQcx+u1VcJZTAiHESvxUN6uXtx6EP5b//6xLs/Izy2IbICUgXboHRcS82eYioLasHHpIIYaR5TEFvYftnTDetX3UC48iPSi3D0lvS0DyD95uhfk5yf1gnzFmteHOatjR2Pbbo7V8vmO/9vo4z9fJKKP3qOxP5h/4GjsL2NiR2Ns2V8ej13UDDs3vVJVAi4cl713szTxl17xMUaqbX6sDxf9X+/DJT/Sh0Oms/rApqGOxDthdODWD+GCo4GXXbCJL463qMFmwgmQIFFWi+iQlE0xW/b752QzK38s6oZ/igauatWqHnT6xHypKG+AR+fPY50OPA/w4L2ThklCCCgTCSTDziQCyZPz5cjZK1IzqJC/xQu5nArRgrbsY8Z+RkjBKOAJaM5sQAE1q9oHS5SIdrmeaafBCBTIvQnG2MScLhyjiLJrXCVtZVdRNz74N81XoXC8hQWyPmK/Xitsi1ivVb1CJarW9QwOTwK4FRyh3TNqy6e3qfRGDW3/ueztoopr0NC70VBCd424+V7reo2X7yhN42m1aRpPbJ5V/BPZbMT0gGo3DrzyxunyGNK7UZz/58QjvPVhPsLbKC7fkHCEV8dHeO22Tt31Gk5kHeX9zLHCanKgqm58aBorgORlaNoKrg6ghsM6r5Bc1+xI4UbjLNEj3Sjm6bBRvlHseRq8OxeSG8jKvUMrW5ZVthgG8UV+dqUvwgWqwTYx82Y+6/q1FkIIMWm4ViJkVeHKB2zagmVZCxZHrw/tkRJym7vrgau0hqjL3VV2aQIvlX26M8ZLvXtdrxQ7NqHan1EgLAu1aUot3KKmqAusEplvFFP/hFsorRsIEt7SHwATg70x4JbD4NqWBzr0MpEyjpLRJPxkfKdx6ExbFQ3BbKn0mhnxVvOx7L8v7TIOI7XVyEqLiIb8XGNonnsK12Bq/QPmUhtyra1LCQW4FqcGproWZyqTtVqQQDlMzskqmOvR8ucQNUBlWY5kvY1l5mlj6U8zTUfrjviMSW4uME422bF2BPS+VswAsSELy/dppoiVmBRYeIjuRpWTYolbvzsrMSe/bk4kdZ3RCNmC/VlV0QnZ+0PBtiTHM1Xug441r1BON3fVEXkOpazjUnJ8EfvDWv9I6kqtxjgPKGzA9QqlHtbPCg/zYe9GPuyVw5W3LCtvMY0TfJ7mBbLy7lC92zFmv/szgBWT4ijns00uTaw9weztWqibG4xs+M/xaLgJUtrU4G5V2asqdeIWTl1WDN1ymd/7CQ7ziQ9dJ0/u17k8FcstsE3meczl2Y3X3ZpnvcvTxv5hNc9TLs9evO6VBeieOjHgBDzD1C1/Ufszd2H6HO0GH82vpTLLs5vGylth8ey1eNvUwa2DMRue7RSpphBP2HqGhqoUdv8qlgIH/LYoBXfRtcaCooi3XMy7j9asDmsZ1JjgGsWieVZHvIfh0yUlH4LTw2qwXg02EN7VfT71TVjqrQnDP0rtXlDYh30MljER/1jpvnSxtM6PZGL8kwSJ3hURzuQT3/wBrOoKiT60CeLnK3sQ7dOLxsXM4IXhhIgt4b1q5bx+s/hkjXTuAIHT9wzrRQhCg5WbN/st9D/stW2WGhEQRjCOmywy5vda9uCwiFIp1fxWsJaNE6Bk6BVAa9/nbK3sRVFMIqts0N29L+DRVu8FsRyBDWN1Pd5F5c/j5cdKZsvTxLCsiJfPRo/VVcgQnW2sogtEODErFBwKOM9m/VGcaEUvEYsoQVFvvObcvPkHUs+eKGEDn2waagb1TZcOnfhC+jjcXhD3PEoDyTPDLkriUym8S2OKDOXij/d26qJmjtw8Jle8AMCZRJ8dye3g02EhtVFVdisXhgZxgFhL3IDvjTZ6F3n3d+ilb0cox/1XEEOphSAThjKho/wYIUnXsgxH+REzVGdiTikyXCmO8FuQjrJySk1gFM2y1h5DuntOdurudkf4aewfB8QdjezZk5I5XRU9wJl81WilGdvn/8F03wF4dgs0QmTq7pTy2sRjrsBAKv/4b1kb52VcOKiTNy5lz2Ctcf69uElQF9N7tZd16M8izrXspKO8BxTua+huaSCc6hR/nS4VTtmc4l8BTd5aonEu0n5fB3xdWKv9vhYv66B+qxXWqiy9dL0BV2+0LdP6q1NvreUmZFClYB/uoBYXSa06H5dO4T5xXpbV5NqFXVa5HhdSZA+u+cH1YqWhCO0jbHSYpWKHWSp26e8hFWvD/Q+U99qlVlNcZ2iUlOr7h4VqCQP4fKUVj9Is103okj2HI91p9tZ7ofVbKf4wW2qTOiuGGQcSIKKfgzaZs3SbMtKp79yIztbqO7GkDEW/R5vpvY8BKbEYdutkWqdMS3mM1C0ytd3U2n2DrldseyNWFxsryu4ozs0+pp1SX8ee7CpJV/pr/aShtCRtH4FugY+18Q6JXDvOa7p84niUeIjBWq4tqyrL08VWd+8l+jMyxax5erRZ1kgqERj2rLcNx6kcN9EMVZYCUGz+gVSecdwThLaTMLfhRnKPZZ/qOYkUBZyWU8EXtBpsFyeip6TGZoapoi7eA0NP8L0P4OeUeFLtIGwBiMGXd0lDWBWiNylUFeLCkFITAGP7ouFOv0m89DHfqXZK2Ia1Gb6duzzRPkyCpJKYp0mQ5hZn8/EVLe1EvZb3cU+IyW4DjPT3oXrVlM/Ghw7o6xbxyoN4VTy7Fli6Ca9PrAVI2bVJdl57Nj7ieF+qUNopjQ6LV/QdwM3huKRv+aUJCi758YZhVBqp3qC9WH+frcS4Qjj2KVuC+wi4bOoO4QQj+AARsYCViSupJgdu0O+T2txBe/RqeHi7zu6elUrDVpSeVZRqeZeC1Hx7dExxbAcL2BNy9Ndy07NyU80z7TSZObBNw7UufxjtOSBORjr1YvrbRn8N5Vuhf9dhCEyI0MYhboq2Eqs6LiaBuS1zXI1dx81lU9zaVhH39JSYNARXksMdjCFzS9N/ypdrc67BtOJOuEa0te6zRv8NlUKpF07sbyqf5Syr00b66JO3HFgKk7dKcxKMekEsHXoL8abAIH34XtyAfYE/E20m3Nt+hi2BGYYSxN+/PaOH9vTN9Tx/LqimLq2ExZ+iyKtoRU2KFLeswLHCRTJe/a/xnDv7iHslTiYdT72tvc0ST4RC5TXEufW49eHLTF9TK87JCwzKU9JZ5IqtcijeDuONZS3AsvFxLwLRk2vljMUBR55yrmbWrtbXNSD5APlen8SXBvSRC3mxEZN4BjvfkRsN/i6yFpoyNR5IkE3i4GXJxO5CVwfMq/hp4Ds9stYmP83iQv7E3Tem1ocFDCXKg+KPb53WRZE3bku5ihiWPKuaZ1fznGpeKoFkjWnT7mHOmhzbEJAdeWloTI0ZYa1bm7ukCQmakZoUBIknKSgmoqj4qiNBKsenZTiuMBEt9XaL2RRZdbMF0xUzwtR1Q4qpdLwZKrSUUWufR52URpjaAw6wkblE7aXY/z7MSczkczcmmmMqv+GUDvvT0OqvSdmOhlwGUgNWBHFbv2YVjD0zVySbQ8tcClzZYnbZDcaYSnkMl8I9FO982BUbqY99p4h+jFebnx8TwhcBbRPq65XD94p5e3AbpAuIzzCnNeINH208YvWiTtw82vYCbibk9DWeta6L8GvCMc7Nfc7DszvgQLLONWni0pHOgO148vil0J1uxEHV8ZJ6n0jZC/+XLe59yiCXIhSb3zlPqyL+9binPjJ3QKMgTjBUOfiDVhiXKGmCA5IZ9196zNPU5K03vCpVNe4Xr0yHB4tmrYGCT1SJjfSJW/seQ4vW9fpGOzSB2MOiwE1tOCO+8BPaaUyhygHuBjhs3+sTzlgInxFJ8yvfO1d2KS1GW7VHcBc52k/+vU7znNTaszxtoeozWZ6WLJi8THqyszu0L0lVarNqtYdwZ1n1Hib0mk5bqHtigtW4tzL5PNLTQLwHzgNfwuTPtREzW8C2qFRvg/gTLHfNg6O9w2VXu6uUq7S30C33qcDggsgjOAIS711wRs/er1mIK1O97IPVWxm5f05E2Q60fAA2nHXv4ehUzduEy67PID9ssbZgmL1bdMtBVdkEA9CebbRRIeOmeEZ/0twsT5PZUws/lBqMQHthzg+W7cWMLkLdBJ83XEDweSIvJtMJnz7D0rC2ymHOyAbY/Vbd6v1W9X6ber9d3TMBAXsm8u9k/p3Cvzn8O4N/mT3fc2MSxGOQybN4zMeBc+hX7AtbCKTX3pJk4I4/9uiEO/IcBma5lBZtzSp82nfBDPr6ERxhEUMookAbjS2yZhVCEa+/F1mFRvn09yBeX7Wb8qmr7CNxeweN8ql7rEm8Ps2GZH4PkJa6J40bdBjJ92SMRIp0CknhFEDz+nuhtYyFcRtItt7Ov6n8i54QlgjmJRiJV1fiEnYcB/txv442PWbODAzLo714ZvwAi4eZuxjDsxuplwmj8Xv+jI/Vy5Dx8agynp37sCVmAV6niRNfzIw1B4exbICbCYertBJbWF/mde9husEjjdho1orQsom4Z3aPNVTp1LN71XjPn+nmnMv3JxgJGiM6pY4r0Fv0W2Hu4N0f+PGXsCjO9Bc2uQUx3PK/xGFyqmC4Oa4rcZ5oG96pl4Yf4Jvrw5ehAb3obCzYlS6+cGiQAXaJ9n6/sFOPvk/D8e6nnX1wXJ+jaqiUEuEnnv3oTFz1jC/AhzDufr0AxF52B6jMHKYyIxoi+iAW1v0qKvKnyThxvNBi8i8yPszFFiinjIgXllgUguPZB8lvscHIzh9vF1lMpSZBNTLXDGfgSlP8ggFY4abNm0tt43J8myMaYEMzs3GSgs36ukzcv5+eoe1CeOg5iKVNMpEaAvWl/3E31TxWb39L98lw/Y84mAw9B4E1TWwcwZ04P9GMbnEfO7dpn0I06JxIQ75zEnNmteH9gfzIHnQ/rBu87swMt8euXOBnXZWTaNghMWIMu9HGXfDtY0D350QvjuxBt8/KZvWbozVx5W2XpYvJM5u8vC1b8egn8VZMmGQIKAeFKtZgIcHEFd+Fie/h1TqrUKIOw+Lu7QfOJFjcjZ+2GpgjDovnUsdrVgEpMB03vBZWZcRwqrzvvvpYy5kEo5SxBYh8SsJVzl3ijN4KfSVtbTtI+UOO8lfpb2gPYxtHudQjBCrN8jif7DwFdpr1lRgdWaoKiGNZhVd3zfIkrUuuuo0sYgjae79wiQ6pwpVg4NwNMs/8QB6S1KxKjfVGUqXP45uqBda2cOXM+6me3mPlDF6r3IvhqzfjRoFxpMxU41PXGjgN3Nkd1xIQF+88
*/