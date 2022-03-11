// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.

// This file was modified by Oracle on 2016.
// Modifications copyright (c) 2016, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ARITHMETIC_CROSS_PRODUCT_HPP
#define BOOST_GEOMETRY_ARITHMETIC_CROSS_PRODUCT_HPP


#include <cstddef>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/size_t.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>

#include <boost/geometry/geometries/concepts/point_concept.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <std::size_t Dimension>
struct cross_product
{
    // We define cross product only for 2d (see Wolfram) and 3d.
    // In Math, it is also well-defined for 7-dimension.
    // Generalisation of cross product to n-dimension is defined as
    // wedge product but it is not direct analogue to binary cross product.
    BOOST_MPL_ASSERT_MSG((false),
                         NOT_IMPLEMENTED_FOR_THIS_DIMENSION,
                         (mpl::size_t<Dimension>));
};

template <>
struct cross_product<2>
{
    template <typename P1, typename P2, typename ResultP>
    static inline void apply(P1 const& p1, P2 const& p2, ResultP& result)
    {
        assert_dimension<P1, 2>();
        assert_dimension<P2, 2>();
        assert_dimension<ResultP, 2>();

        // For 2-dimensions, analog of the cross product U(x,y) and V(x,y) is
        // Ux * Vy - Uy * Vx
        // which is returned as 0-component (or X) of 2d vector, 1-component is undefined.
        set<0>(result, get<0>(p1) * get<1>(p2) - get<1>(p1) * get<0>(p2));
    }
};

template <>
struct cross_product<3>
{
    template <typename P1, typename P2, typename ResultP>
    static inline void apply(P1 const& p1, P2 const& p2, ResultP& result)
    {
        assert_dimension<P1, 3>();
        assert_dimension<P2, 3>();
        assert_dimension<ResultP, 3>();

        set<0>(result, get<1>(p1) * get<2>(p2) - get<2>(p1) * get<1>(p2));
        set<1>(result, get<2>(p1) * get<0>(p2) - get<0>(p1) * get<2>(p2));
        set<2>(result, get<0>(p1) * get<1>(p2) - get<1>(p1) * get<0>(p2));
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


/*!
\brief Computes the cross product of two vectors.
\details All vectors should have the same dimension, 3 or 2.
\ingroup arithmetic
\param p1 first vector
\param p2 second vector
\return the cross product vector

*/
template <typename ResultP, typename P1, typename P2>
inline ResultP cross_product(P1 const& p1, P2 const& p2)
{
    BOOST_CONCEPT_ASSERT( (concepts::Point<ResultP>) );
    BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<P1>) );
    BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<P2>) );

    ResultP result;
    detail::cross_product<dimension<ResultP>::value>::apply(p1, p2, result);
    return result;
}

/*!
\brief Computes the cross product of two vectors.
\details All vectors should have the same dimension, 3 or 2.
\ingroup arithmetic
\param p1 first vector
\param p2 second vector
\return the cross product vector

\qbk{[heading Examples]}
\qbk{[cross_product] [cross_product_output]}
*/
template <typename P>
inline P cross_product(P const& p1, P const& p2)
{
    BOOST_CONCEPT_ASSERT((concepts::Point<P>));
    BOOST_CONCEPT_ASSERT((concepts::ConstPoint<P>));

    P result;
    detail::cross_product<dimension<P>::value>::apply(p1, p2, result);
    return result;
}


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ARITHMETIC_CROSS_PRODUCT_HPP

/* cross_product.hpp
0i1Jfi3fKJDl/vJZHJc4i/RGMjXwfrCOUcRj6ycBtW2gXYeXNdh0CL48CG3XuCfWUjT9VDxQE4r+LljGa/zFxUIS6/ICWXI8bwjXrs4wk5c1VH0wxh/Z+gVkQ92OG/wsoHYJr5JoiD2ug8OSCIfNwyoUu4g3TQrjxHqprHoPZ3aPrQf/VSzuk8jreoWDlSY1JXRyG4kym0rDJd5SqWgMY6/4O8UXzNjj6HbyTQusL/mXtT+NzhPe7+8N1kLta7ypXc4Vh0fPPXJrvM+X7D9uW0Y/YCaQHTofKs+r/xu/Kcw/YvtvHn2Xcjb7X8YNwTr/439ISeeu/YdHh/Tq6Jw4jGIYSMGPFI9FgCUeGfsCCsikRf1BgKU+UUD5AVBi6AOxAurE/qDAwcEkn+K0e6OYVvTqzLDut8033WWdVgyBFec1fCdTU0fi1TXXus2Wy0Y3FS6Xg616aKuvvB8DcVPFe/W7Xn5+ObM/LhFUWwy7mmIPJY43ucdfvZ/Z4aG/50AfFV0XGJHvvhHVAShtTiMGhPtqMaA7IKlSM+kZtfCs+33q/u33cwjCC0e/1ZUGc8V/EydSO1lypaT+8iaMIUHqtcZ06UvvjSlmQpL4ojUALu5GR6biTOjsBcKRChPNh8AZO+A/tss6iRfuAzATHvpmTrtlUUgFhrscFaVBgzuLCBH6vUDrTlddNdEELvsetibUUWnS9TJNM1c4svsLkFZJNYoERppWHEvv5ou3gqH52IBhoWz00boDxeUz+imnyJfAAdKQNv1DsGgnO0pKEbhJueN4HvbvnrSz4tt+xndmQNPu3Ow+720AajlQARPOh57g+521n4dv7h8Hcnq7mfxeD6P83sbOcfA/Z2KenHebO10e4X9yQBQdZ5R2q+OuEe342jM+AjN9oThJ3WRT0n57G7JKN2qqpXX5wyHLYtwbRr3WYFHJoBBDuBWAEgVD92SuyuD3Tl3mk7IA90Nz6LA4FYhMUQfECdX7s+rilbaR8iTUKqhPSBmkzh9ilnQNpUhSkvujEFu0jumyjkqjidZBXR7gotLNZcUejxHfx/HPTHutZIAngGN6nroh5rHtfgir0lTBYkjIsEA5GRQRrkho2Ej+UozwDoCq3CW1RoFxb5wO7FYW1++vJ5SObUdpAbPeRFHuSw1OrKOcQianoJy3uYC1tTUWZWLn9jSQAxUd8Pyzi3KLKyYJ/KJdIAU6uWvbTLP7NF7FCS0VmwiZU0SPZJ1/8a3TvzlFLYhMjpR4UITCZbbpE6ox+zDr7X/WejF6WTeA13EDh67n9VJiNfJcW/fyfdvBD70fKMf3Wcnb5hfq892fR16X0s4GyzxIq4950onX+/M0S5tbpQg+HdHGozUj98s2+JczzjubUZqJ8qJtbLwBTy2Te7v0Ll26dn8NPmTdmDvTiQkiNJp5c9VW0IQ3a2OkyTFD2s231sNIian8PC1Ia3YirtKPCBjCdHlZnRmiezuCHtptDnv3OBabzaoRY2I/4Mte7hY3Ydm1nTs4kaLKekWo33aq0nYjB3fegLT/jwUI3Htmiv/WzPriZAc8mPmbOVKHy2RVKG+tFVfYLvGYEEZA/TzsLjw9kjEohR5UI1RXudfQ1GXgYQgvFaxPepI0zAyacOI82SnuxYWQZvVJkdDkdru4rXPsm1ofivD+uz5/xiNFRPLU4xH+q4HB06zbb7Purc+RiemfT8PtxGOdsvFzDxzEOZ8Tuqgb/qdFK9GX1rqeGwKvXwShAZutdiij9bYoG5s9JydPnjGkhZ0EYJdpWz5Q2xAtaIqSwhJiWHG/ypJjf90k0RpfMrfsauamE4A5vmS8Ydrn7QK8pe20Yt1utnVY3Kq8PT01ZY8RuAcz8LpgOC1mV+uhExmZDSENLFvwszc0bKAMJ0+vIeiUgfVN4Ylo/Zub2cwNNx+ZqJ7whcRhjt/rbToSXoZBt/VYbEKAezDk5OQIcHwwMDBOTJ81eLi5vQ649jwvVqrTDpTucgi0mbv02JYXz0l8Xhgib55p8LjZaCfQo2500x9I+hxFZ3q0zvain9aF7raSyEwMjFPROvY7UzKP15gvpbfZPq4lRC+AXqyTVHZ4mSoNtpOY3q5VR5hIWm63Pn7FcnJU9nycW88We21rXChsgT4/kXfYIJVMosgfdA4az02b7u6zoGPv8PpwpAodQ032dHI8W5xKMxdNABnfbyUdvZS4KucqHXRW08SsNZRZLvQddlJgecHYMgkl3dDjaXG8dv8UtFH2eG3Bq3ykiVx03nz+9Hz4oUY3DQpX4Ez87+aR0Pwj5/9+H3Cfdc3/F78Kpv5/Fmot68hUkq266Hwob710JCwlRnC7CiDD/4ICwiGGNE6UGKO8FwD5YHD2FejLBZexQST9bXEI+yuCN54oPF4i293aKBkWVXNtCHnI9rfbJJHqxdYGTdBD82y50/nB9urxW//RSqWX3XKFjpVfnpMkYDeIoFvm722vmm43heNPmN3djNnN7rVU7Y56PoLvMzzf99EopoRn/qIfyD4AEoDRQ/5NZuhLvez1Zfayyl71wI/VcnBy3jr43cnQHTuK8I1ftIPkl4//x9xD0RG+JgwNJtoQhrbSJnW3/KyVZBECRQAoGBBkXJJYJyKx7sHcXqcjpR5z+8lHXhetRngUIP4bSC0whRXbXrACrq7KPL7v/QoWHcDhIaE48KbNIQ462lXLoTdtdr1LM2jLZp4PzkKr7lmXz0mE05qHNzARwWIeoEJyRGXjVVdxDAK3AKeHPqgmuYk8lhiiHwSONycPog1CB0KPqByTDdZX1D498ov0THLT2UGmQwodIKOU0m/ZEU64ngkObp4YygxNxl3eZ2IlMGMR33diQ830K5JbwnXsU/pZFQ7Oc0UfjNartZdNR7UQnHZZki0wprW3VODJcNZbQivx7z5sU/K1dsP8jOwezG9GJdoSKrhrxyjWXWA6bHwr0YDxNY1mFsjWvKACf5hOqzpbCD0vZBETNRocHDrlBnDsnnw1IPVB5DpBkPkv/XEw7NO/y6WdW4p1xkY64QhDwoZ00OIQf2jXlKpulx1dLanUX/0t/1q6l6T3S7pI/Wnb7Q734OBIqikAXpJSxRqaoTlArWI11whJVTYpyqrubwBa0wSp1edi1/ldGkDrf6Sar97+BVcXkqVyYJt0tgBYEU9Br6q09UOosmZUo4OyOuhughxxpspX4khr9qiJ7msDR98sn0u2nqQSnrHMocpHGltjKYNwhlkDaxwODSTD/gOHBALHAv7rdzhM9ry0W2hgM3G1auAfuDRuMiizGWxiswdDI1A+kTrrrJpgqjlCE2g1hACxH+Rirky3VfdxqC4bEQ1Nieaep9FPz+dZ3rXLDWIGiodtrnHdOitkm4wK8NfsrRGa5D65atvWvRvN4zqsKleedA+oSukAl8TSlL3VlE9J2XwBBm5GQBSPNB1cldByhqlNoSbLrhCZKYl6OdDMopOR2TonlVrfJZThynexlUSXcVJ5xQVI84lm4l/dMvkrDGU0rAfe8b1SktmEDbvzWakVk5ihkYbSbPtf6xrU1T+rGsTNyBJ70tc59533P/XT3GdSmsZBTcYBqzyCiFX9KydJsrfdTysTfJPy2XEpfNh1L36fvAA/2L4ARET4YpC9/OhN5BYy69EbiTkLqJN46F+D05Bi6KE+e2BPH8J7+YgK4T6joDyeEH27/b53k3pMzQCIMX1FHLMWiKS7zKWyMX9uUyvV5dypTlfHWiqqVTGCnou472o776uR1tSe7+mbcO8LHL2DG789GMzcT1xZW3xxMkYdX3j+tzM5Xjg+vyfAtWOwE3koFBrJSiRRSuZYx/vYJ2LjRk36DdRDi2yf8xOAPwL6eYA5cNBgiEPSkiZfZfscaBtzYUISStp8AyPgeJTEwcUlpbq/sRXXVocDVzQANrEaTVIib7lW6w+dFM06WF9EWwdxLkda/zZ+xCYGPAbEeLNxQsNC+7LV9aUfasjQ0i9If7H+FEQhIzMEWYc9UIgTHg52Oy+0lPdqA9D3HHK2QW0qmD3oPir4AkPO0DmaHXiljFojqMgpoFqRcCsbJhoZNkm9qdcRZyjLc2zNp6zWbdP1NSAZ5KMu4ShVBmG6NSoyk4hLYhM0KBjeTrISS39jvKnZSBbakiiqIDRZ5vnfEYdkbRQ0a+vgRgddw3wDZ8qL/v6SfLE03FJRErQvmfRsVk6gJ8N2YOYWhDyBxRC4WXjYLDOqcdo5tTbR4OuvdcOLhZ5DpBZ7SH3mHJUqeCSGh9l2wPRNt2p99E22V9UMVExAmN1VpCsQiVh7jiGOdBFbkkAtXG/ZGYyCNnBNCpnN2keBvg4l/eY8QBjY0SXBFuaGaLToicuWXfXg5hxQNfIBOFHMYHDqcNx1W3JF+nPjbuhRWkQmsUNwCSvE4mx/RIqMq5Jj/alBxWjW+zSWAZLI5iPEbdf5fcBwmfpaqHWJLdlouMx1mfzjTHVw4mxcgR3c295mv+ehEjL+AZGoHGW9VLL25SwHfIL4avmp03h1sKRy6iGHbr768Vc34ZnQJi1TmH4Fzkp9JjpZ/CnKZPtr2fZGTZYkbZL7zKvJETXJRZdL7iCWmUo0iNuu6ALwMdG4tD8W+hw4vaR4IvF0GQfgxbRSv0NqUCP/NLNCqiChv7mVBjRDD3uYdBYu97NhL6VnNMqnQye6aPTbSm+51zSlgn8eMr1GfeyWgIDn7ZUm/814qYhiGNO4bTmtRBuaS27HnNDa+xI/RQn53Db6DVKA4A1juOEQIcWqZrhjDn89Of97mCnIxVMoRnOlxPNaD/vG9LewhqSSh1CUOQOx6/OwNg+GcZAxBrQW3Z2ETo0GFVW9yuP5j6i0Vn7ipWQ4g2h7y+Gm40B4sfvdQhuhGScNuP1nQJvkn6Gu3sUk1KwFsvUVCRrQetkI0YmVoAhQZjKTWSOX4uSmjN/WVX6qoiXx5ojZjfhT9R3TiTQdqgMNC3FaZ7RQMYMNEuEoqDmyFln0arlzj4peRzL1ZArr+FWASQybTWviaYcMEsDnot+3Ro8QEAtpr5I5kQyAHJr8fZacNW/YIS05OQJ1DbSgBFVD1P3kdCds3y90b+Rbx3AN+zYGcLuh90kG0McExQyVj0Lra78FFsbdBf8d8xqZ2pk7qg+CoeQmF7TNQhbsi1oWanN4FZEem1vr93Hda/j5zt5LMsic93ZlTtf9NsL7vUfgHbFYhMDE4XYgIFfxq+uWePun9iceCaDb/QTy+T6sxgk6Q86b0G5ph83ZzSQVL1o/k+kCxCSze3UGcc+ne5vtc52x6X7dvoN0InShoqkixMlbqSOzvF7N8EfotnJTo5+e3tbA/ZlTEnBmDJafPV+j8bii26FZbHD4eJgKmLpWLTRAkXBpz8jjlypcmI1POkJkLiVt0zwulcK3y09i+o0X31BW3eZ40x4vM4U8amgvTL98SJMmukC46f2FbrdCQzEt+foGaC9jxINRy0TWdP21tkX1hm0GdaWCMwjgJFmnUjMcEleUbT/SWuuTJVZEP6kqGBs2plnnskI7Uw+mw6jfgm7K8nAANU+mHZ4FSCheTb0l5oTAWZ+u5adVaEFJadwfOh8FYSwiqQFpw9lSmSTERA63D6G5VE+rmkjfyiCn1wzoQ44zlQRnupOQ2IO1wZkIp15FyL7pKnav+JNdOOgslmWAyx53VS9icMJVsdnQHohTo0hmWsaw9A+M1ia7xpq8XNkcIJe4GdZimvXgRoWAVP76cn5EPjocRePQAI/60jdLtF3p57hhhBcZZ1YHkaTvU5DM2nREXLj74LXvtuSgYbDkZq0wsE6kcrTvIM4WoNXPQu2ATmYJ3CSrUz+fEaaD+JNiSOXDkrRFB8QLPg5uXG6rH7o2MTLPE2UaBTONkBqDwPoRNfDXeUqACatctj3BjIzrwXIBU7j/6E/F8gf0ImqScooJtSzSDnJJcAAyMNeddoHEqQVqrMt8/eq0kYLHQobUEaz5hmoetXyxMqMiLysmuY4omJH4pwbGMVta5weVtG2CFLfJixMGDVhQBh61P1etMZPsUp/JMdQAtb+VCx7GtzN6fvrIr+Z92z9UlCX5gti6ediTeGcSB+i1nkwtQemGsCCV4ESTQBFM7LQ49kd9f5csEJ8vVP7qo2sOgmRE2Zc8GZJ50KFJ83/pTYjdoASBgENE91iTynq/iAb3RCsPt4WIxMPJdExI9VMuH1L8GW5AUgkoChyF+tziB7bfxOD09pk8Shu6YhTeyNigq0hXM+7HTvbRG43vwAS77+izjhD25mVbtjq7O5poTda/sgrXz6EqWb2rthbHdLn+qP5VkEmGJnYOFyxuACfcwFKdXJLs+miuKOGchJbEhkbLnmPRKGpXoZCJZA3MfPgCXHd4X5qkOJDV39FizArra29Q0bqoPSoe9KZj0hE6L+ViHzDIymqZT6OP85ZSCMTGqtVkzQibAK2RwLwWCK44339EIEKGY4xP4YxDWM04N6MTj5s7ktqtSgdUqY8L+8cANnJZvq6AbBlOue448rGbjvWGOL5o6JdpvDXuHHOSdfLhqQWioKgkaVQ9UBXLyPqSvkbtCEl5sIJx6kAm+G2sfnS2SzykI2aXU3gi3I0tU0aya8B0oEqmbhJyenF6FL5T7XhBJBwiB5dQNogxS6KtOPrYNCIty7Wp/jLqT0UopLbuJHlm/VpHvf7P2w5a3wlECiO3BCg0RqBLWERBM2pgfoQBY7gkNDdMTrlWT4vHmRmdB1rCX937XJ1BDtgQki9caupbO3ID76tKvxBjuyI0xpV+tOriJcX7ZxFNqdYlGD6s8oGW1E8prDBLmYLuYossA8inHZ8Pgi7/He+D7Rg7uq+nna4rLalWu60BJzUETljHB00plCO1sNmxWv430rndkJsHjFH+vT3CR7emKgxxnYa0HDSvFqlGD3GMyvHJaOuESpK39sGXu62fNyUC4u32I8bYNEwEptI78+wMdaJ+6PDHA7UzFo41KhykMRCKZeywtrguLsXcDGlrew+PPnt73GwC4iNwCZpWiQrq0Kt1QISriQLGiM+ibJX4T5aNyRyDEMQtI969RQ7OJyR/54LwI6HrUcQACZ1yY9ozQ9WMYUwwnGs2cz/73/QJtuzIs3VTbbqFBp0FzNJzTUXbFcP5Z+vlPpaRyGhkTLGLfnD5ZRrkA2lECd1FLlyHC5/24ft+bHWTeHoUsk/rZUwXOIzdsrvfQDrW75Iec9eIVRU0EeB2i4kBTiZF9cDB5d5hnXSDISX9AGm++z3CfE+RwgdF9HLK+Ug1r6IrHBLu8oeCctoJUcFxlrmCw0swidLDxH0rMGQY8Opxayll/VpLjl5/1FFCB2XHiSKikXZCb3cw/bZb3IgLd3Qi8n7GUlVthgpNyvHWkSnsJJVkHsG71WMybD1Kc0ZcRYuEQkQHophZBc/uX6V15jmto7a1qYcPwlKhWASk/kYAbA9uXFo4+n55zWJCDCzl4Bl2FbI1CuKpEZQzhuAFW5zp/or5odNmchBH6CCvvyUOXIMlpAmjldnHrRHVYDIxieZWhHYFwu3lCTzppQeSLFoK/ftSoVJK7JgMAl+9hHR2HcHL72HJjvN/DSX9H6XuU2xMll/FbdmqOhMqtg3GUCmAD8D85YjN7N4Qsv3Puy5i0PLiFxarbihVZNQvYUuJr01VmFvqX7t4CDws3ySRMW2x6q6J06HuRgTIohFQwyPl/lYFc8dwqz2oYMPFady01LumYcuWe3qPB8WkhbuuMCQcN2AgISkO6BPMnARUu2KvnkAksjj1/iIrDDbpaiq9+GWeM+mEeiCCFuDa7S2PU/IcKlDg2N7CoYZxIcQfoKz/p09UTYhLgGKnOgKGN4mvLqI7xPQmdXKBvrSYUUYHbiK5CilmnCgIolH/yF4LWb7ixDKT5bhhXi+bQhfOSZJJuJmtD1nPyKoP+OjwLmOtT/icpSjufL7979hyc4jDpkL7Eb2NAimlujP0XqazqEzLSlm4omtOgFh1haEKUnat6ZSH01DtHpWi4/MADSavb4NupPus8HB10CzXm0zDdCaZDvgvjLPzMaghRE0+oj8SRrWVqb5M6AE22Qunfv2w7jSKSKymHLX+qv5k4Lpfn3weTP4Y8IMhQbi4fwn7+oGK5jgJ0im0jkmDIOa0V0vS88KNJxuPQbjebLoVpdWg4YoSyuTQRilQYvOoT8McxcWt4AM5XFdqnA2lHoZb7GQ/hj2KHfWW7fsGSiWNywiQizyoJXn4KI43NNzH7eMjwV16BSYKtepj3jDrqqOUXlLLG4OYFpqCbg0ygnSCt90bNdNX2O6x7FL/oP6uXOk7fjbLdNgPbId+T/DCYYRpaoiEM+x3F1jmE1rXaUpa06bbcw2qL39sjlDxyp1zZHeTjQxWEC1m1bCelZpIKRoCHgJWnzLznGNJXSyEL1BmiDVxW864gVSqSI/EbQZOQa4uhYxM3qQbt6UjGt6u5lXTtCEzpCa9uI/kkV2oBMVqgViEhxOEM9EtTxhhJmV5NmcFeSpdEQQHK33jHD4KyupHchH7C3aERX0xd7aFLtgmUFI/1KksKONpka/RBH3nh/4bbEFfD6ukC5uiYNq45FJSQqvxaKPU3xKHy8A1sVI7C3pvAPMt05d8BtPmlqhGlRbjeMnZ2t5K3x66x4RPuUQ9PipFBq7oJMeOK6p4OcRJ72ua/fpOxOMwR/WReF/gbnJeQTuzoPiWrrQOM1faoUURm588qjGVtCkBVFJtSvke5ogzVOThj8FI4sh5rjeqmX/X87JXAd8JYVAQx44B6t3PBw3egNc+a44Oohw6+hAMU0WmJSurWixnSMqXCzBF3sSt+6PD4KGWlJ3PC8HXPP/rblDWT1WJmi5Su98P3812d9Tk5CQOzON4EoX77a6gtb/2/j9FExiqM1luYqR1fjj/w+tZcXLB2CcI1nD3+O1vp59n7b61dyEpyyeEF0nX2eH1m42rx1diGsGPEPw/F4mXC3fmogsYs5qRyNVknWCvLkr56PrAnSeqL/A9R8QtfyPQxwIbFZbosJcUe2wlH9vWgfXEXWPAWdNaJd3ihNXQrKGU4zp7JWjk/VWWa35dMamVaU9tVDNM/KlwGn++vMKGO4fhEimUck5fX89slAsqsvJPPWVcAW8Dd4gsrhls1oRRoUyvQE8=
*/