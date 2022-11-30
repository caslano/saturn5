// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2020-2021.
// Modifications copyright (c) 2020-2021, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_POLYGON_CONCEPT_HPP
#define BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_POLYGON_CONCEPT_HPP

#include <type_traits>

#include <boost/concept_check.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/range/concepts.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/ring_type.hpp>

#include <boost/geometry/geometries/concepts/concept_type.hpp>
#include <boost/geometry/geometries/concepts/point_concept.hpp>
#include <boost/geometry/geometries/concepts/ring_concept.hpp>


namespace boost { namespace geometry { namespace concepts
{

/*!
\brief Checks polygon concept
\ingroup concepts
*/
template <typename PolygonType>
class Polygon
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS
    typedef typename std::remove_const<PolygonType>::type polygon_type;

    typedef typename traits::ring_const_type<polygon_type>::type ring_const_type;
    typedef typename traits::ring_mutable_type<polygon_type>::type ring_mutable_type;
    typedef typename traits::interior_const_type<polygon_type>::type interior_const_type;
    typedef typename traits::interior_mutable_type<polygon_type>::type interior_mutable_type;

    typedef typename point_type<PolygonType>::type point_type;
    typedef typename ring_type<PolygonType>::type ring_type;

    BOOST_CONCEPT_ASSERT( (concepts::Point<point_type>) );
    BOOST_CONCEPT_ASSERT( (concepts::Ring<ring_type>) );

    //BOOST_CONCEPT_ASSERT( (boost::RandomAccessRangeConcept<interior_type>) );

    struct checker
    {
        static inline void apply()
        {
            polygon_type* poly = 0;
            polygon_type const* cpoly = poly;

            ring_mutable_type e = traits::exterior_ring<PolygonType>::get(*poly);
            interior_mutable_type i = traits::interior_rings<PolygonType>::get(*poly);
            ring_const_type ce = traits::exterior_ring<PolygonType>::get(*cpoly);
            interior_const_type ci = traits::interior_rings<PolygonType>::get(*cpoly);

            boost::ignore_unused(poly, cpoly);
            boost::ignore_unused(e, i, ce, ci);
        }
    };

public:

    BOOST_CONCEPT_USAGE(Polygon)
    {
        checker::apply();
    }
#endif
};


/*!
\brief Checks polygon concept (const version)
\ingroup const_concepts
*/
template <typename PolygonType>
class ConstPolygon
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS

    typedef typename std::remove_const<PolygonType>::type const_polygon_type;

    typedef typename traits::ring_const_type<const_polygon_type>::type ring_const_type;
    typedef typename traits::interior_const_type<const_polygon_type>::type interior_const_type;

    typedef typename point_type<const_polygon_type>::type point_type;
    typedef typename ring_type<const_polygon_type>::type ring_type;

    BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<point_type>) );
    BOOST_CONCEPT_ASSERT( (concepts::ConstRing<ring_type>) );

    ////BOOST_CONCEPT_ASSERT( (boost::RandomAccessRangeConcept<interior_type>) );

    struct checker
    {
        static inline void apply()
        {
            const_polygon_type const* cpoly = 0;

            ring_const_type ce = traits::exterior_ring<const_polygon_type>::get(*cpoly);
            interior_const_type ci = traits::interior_rings<const_polygon_type>::get(*cpoly);

            boost::ignore_unused(ce, ci, cpoly);
        }
    };

public:

    BOOST_CONCEPT_USAGE(ConstPolygon)
    {
        checker::apply();
    }
#endif
};


template <typename Geometry>
struct concept_type<Geometry, polygon_tag>
{
    using type = Polygon<Geometry>;
};

template <typename Geometry>
struct concept_type<Geometry const, polygon_tag>
{
    using type = ConstPolygon<Geometry>;
};


}}} // namespace boost::geometry::concepts

#endif // BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_POLYGON_CONCEPT_HPP

/* polygon_concept.hpp
ARVpHeCs/GOBtv3V1RNlo5/f6JcRu5BnZGsXZM4xQ8vqlGY5Ri8NxqbC1KpV2drHVCsXSBm/9wQdGJoQlffGfz9TmW9hGygl8vQszI4uaRCzaUuWZ5znCUsF8rw6eJ7+MsZyQl0VzeaofnXEVSXlCYY7JU2AXsfZb4x7AYVc3Os7sxR67t7sbzzRqNgDfNftUlpjr2+uN5gqrL23/ARE4I43vc/NnYmynYgHB+zc14jA7El1xj2mjU0IVDpq2VFtwMdSmgt3ZNioB9sKQKi6Lk5pThA99EJEsjGJtpnhyr0w3515MCz4LIIHqPLbB4FET6YhdbClRaI7pxsm00alICV6aT33/l4AN/BgoPoMh2tMR/Vg4eVCEyiM4LEf6uyrur+P745SGPdyRyLo+GdjNR8UVa+HzqBnlO/9nuypOud72JlYTMuOyVyPqVBKUdrFhjve0V7H7GaNLN+VEGNxi1hW/nZF7WAkqLGEPS7gdH8ttvIja27bSMKGGLFVCamIsbi/K+z//5Rfn9dE3Jmi5s1YxMx44nBpuPdwrqko5mBNCkY2O3UCnwakXOueJev0B2J+eo/MhncBmYox726fWUsW5P/BAyf9dA3iX4qvUrFubgBvOQNMUVA+y6N995teD0feix6IHjWnP3y415820tqWbMZqfPB5PiRp7p7xVtkOldcTOt0LughDlnVxyv8NAzTGCB9RaTQVuWaZ6f15PBsyK9x6upq5vmCS7HXmUfcYfG0PSAvfKCwHEGNOv6e0Jn2sjg/pEc8Ri3FMjgLMq+kwHaDXQtMPmF/c8jLs7C7VBhwCUdx8o8967T9mPfZe0HBtw9DX7EaaHfdky6ocufF24xsI6wCGrK3zbKfALKwGM77wBE2mQG4xo4KU71JLPxA6XPPvwZk2JFd++f/+Es1SzTxpimid1i9YYQetEInwZ+iDCdxOk6KRmHJEEJH2MZs/jpr/YBrXV/B3hpCfzlVtVqg23n78C5h2222s6mS3t+GbrIfnV2Iff+xhMI6KLRVcwjH3ajl5kwcYQJ69/72frXHH8AAuLolx4NTHLJmipmZY/HpLDSUxuxztGxEbkdzGJHLEF78k9a6l7+/3S1y1mqYZalN/4vOVk1cAsjAQuDbGJlWIqa6cu7E5vgXfrD/gpJ4KhX+jdHbDmoxVnDxBwnOa5r9Sq1LmSliod5jmj8lRl54HXWCivzZY1WDi/d7A6/iq1fmhFEDGU+pgPXjATaXQNeHCCCR4Dis/qW6ZPTHp7Jl1h+096yq0V17LR2zqdGhmO18Fnx0WoqC4I/CroH6AP0iyAjfDzMR1LbO/5ddM0CuFGfnpn0yM/HJ3DvMgbv9D7KOWMSEzuz//iAT44Vy1WZR4PvTC3Wsm4n43eehgeQJ0f6WFHEsL6PARznZHWXblJ4lj5mm/Ld4viChyP9R1PbVqeuLUtO4wgF7jetQ62Co/KcbUnbRud8xIYjTyWIFKKUS/VHeNyhnW7T4TMpi/KxmJQcyJXwmyC0Ba6Z0ElnGVUUJvvWeU8R9nczexMLIMtg/lnigzjGTev7sXr6k7/wcILPfTku6al0MJ7Qp1OU3Htrvk1FcbRmwcvIoIBoouVjTZriu+qrm7Jzu6ceb8MwqPQ9/+aRrcDDywSuVLztHR0fGtX0+WXuHtWqTohvkYsd6DctbnFdXVqmLYxWthoaG6lpa01BPP1446d8LVSn0cZCT09mkrfqhW5VqIreUvv1BTJJVkydn5At+HVGbpP2RcVEyFcRynwyLrLjCQ4fN3/PmraMTH6G8PCjm2Gd4Bv68L8VHbDApbbZ97GQ0x6wj5ub+vK/8uCeSZRfzoey6u1AR8tv9Kbzd45MeN36xlV1Zd5etdRiqvNYnGCV3/x7HdPGh5z6U28/P9WWev72l6WZkj49HciPNexi35wHa7VbvfOydyWKN2+Z0Y09yW9AVtF64u8SC/dM569TsnWGCWz07nvrbciKNaMNULlVwbZagobza3IPPgMe/LNWjiYLrO9G893LMe1KFcvmE//yS/kmvOXY/L/OkzGk8b9Hoa2P24ph1RLdYjtvK/eKYeYwrZHAKfZRfUupe1aNdzzhK4Td7h0nS/HPO2f9vcrO3K95dDp5P9rjJtn/ZS5p3la1SlcK9Kcf9xOUmYv8Wue/PTlHbmPS077FU1abz3pMn+2ir5iVqAXH4/E/VuVHYhlu+nVm8PS6djR/2n4+OzxQ/+zvFQhjkaY7JtQP2MOYutgXU5tXbr+ia1mICfQaLa78cY3mXHaH6RkEIkNsq0DJaqL+bX0T82nPMzQShWah/SV5c14VS7h4COardfoKGTPPOQqE9Qft5Tq1Jv/ndsZDqdQ3y9jj6L8b/85tdDBuzKduFrLy+vtHyVvej1eaSZceVxei254r7olwmHBY1Nyb3+Dhm/ixWlj5L6KD2bY/bm27e/jTeXrU9PYfLdOXZCJM/FddNY8X36SZmZmf3K138YnporZhGdp9BJZfGHHGpyHP0grINuBiJlh5V5Fs9n9jKpY6ZMb6SvxXdF4iQ7+7Y+RK2Kw751x6NjSpZU4JVhwkn1Tb88AzjdOf4N0l8QU79mUMgOfZjezqZ5acyxCROv40dNNpWoTppIxJFtqtRmsYWDv3mRTQ6N7URay48ZMfGQsd3Cqg02Nf8BGSVjewKmKc7i0tRWlbeinZTDwR84EhKBjRGascSyToZOs7KVbzaFllaeqTQNLynY9uZsax/TlVRsSxnnC6TShGuVaCGiL2WNpXKlaG9F3s7417NZELu4BPSbtPAF4l9LvT2ZFTt83Mrm6Kl3ILwQZFhoDBV+9Pe2bXIz8/r4duxeQiRaXeSuhxEJGT+Q4jUhNDzD5f1oFsMqbpXc2srwWegLC2+AVKz1D4exGNmqKLw8P7dtAEbEMXTsbORx995mRuwoMpB3DyQ0PXDwPOkJxIu3AhF2dQiooVtLUAQDwRFKfTCixdFgBJo4fP3R8NKuLuebrCFfe+70O1BAfGl9s0ZgeX9OggVSlpmdKLhmPFWY0Gyger7hdGnf1bP93N4Pha0BIosC7hktQjWkKyisYQYcWSd/vQ8SCMjbABIZUaCbupLFEf0eZA3DAAw/FwTYiiHV2y4Qdn3c6hKRMflR4griMfycAsHcJbmrBKRYaARxMhgPGQuXBxMPkAyIk6Nrwxzw48npac8e1cB+wfEsKgseFwMdMJIhCdFAMpFYN0gNKpwUBiwMgi8aFNeiGaM2nHA2rw+kY9hS5vEkMA/IS9AvUVHSqu7zmOGCFpvsGWxhdQ01LV6mmmw0e9hoA0UOiDYkkpIYNeZKtpGJkQi7E5O5pg7QVjzl9IQKQw1zyFyDO1Pp4jkfxiNBIALyGpFwhraqHNDsrAgDNTTSXRndhQyGFqQS346gAJ8aXASrsWYOEA9BzCo4JurrIOTJqjCcyDCXmMiwGvNkrkizppHRkGoyWlE4ZCpqyH510h90tS0VVozNYCM7haKUhZ76HhlaXJi8sSZS3OVKNBvHCOKid3FdOUtimvwj849mv+9JMUNgp983nhwdhAg2t0f3x20hCqAHuQXw37fCHhgGOoNh522T1vuDqb8CoReY8bkGY8MgdOiWvXcY8MUYe4RSKs+BCpdBV2NI77vIUg1InGqh4Ke5v0jG4UGPW93vPs6yRf4mzIUyA1ANsNbIZGD/QhaF2cAEcUCnCTUHdI0i0B2JDZ1BfU2W1JUnPYWW7gPjQ/ruaN5iQCtA2LihgGAIfAcLDzOlJDjoMIaDJx3m0sj2OIFwx7fnC84x4Ow/DniAHaFl3pjYKOM51QLB3XC5ZL9ABMBWBP3pa5qH9kAexz4jzugX9JIYkjIHLKS/h1E6zyIuCLmCOgT3BDUTgPaGNqADhzAYNCrvMwSZOL354iiKkcVOJJgmiY7DvlGeYK5YyBKAwJpMhEwGVkJCAnN42hO3uZ2aEE4o2ExYcXb/BiT2Ucknc2/Pbm+g7kBR983Z/kmLqAhroZBTTa6gYMNwEFowp9oYz11/lIdd6BkEygnhAgqNSwDGKulEPu4fHHUY3y4hbz/UcD4k3jxsTHBAFJpaDD6+HH0B4wPnXxAhDbyC6CCGFmth1lB80Imxd0MxIlvAwOVEgFSo0IRMHJZ8EcFDBG7xfH5K1EOWNP17+11wKoQSG3pIVAZqGEWAwYzy9odIktg2/tjOTIzOGaj4GhwflQM901FTs19cDJg+FdxR714syVShteEQ5M5OZuHniF/KMvPacvbFDWLGryafY8TE8RtI7igtHrsU+EvyyIdj64DvDnBV/g4z5flt9NkGxDNiDIAzGO+Bak4N4UQWH/DGzzwDeyJikcXDdq5koB6YgHGV1Q1AOgQS66IP+wXOoNWedDn/zOn7omKBzuJNiPGdjUDbhCYK2XQgDAtzNIjhc2SanxKfkAYviJTx4DGawiMZenbWhjoqsdoIcXH1L8hBSaJgGkOld3/5u+AZe0OrGx6djLs/fTWLiTkmZyr04SkqCk3ha5J0w4R3Y/5iIJMxTFgfWTEskESos8bb8A6i4YBBnIKgqMeKGhYZYmmSmGI7Eu5AFIuGXnn/tFmASeiO6HorFgmJFDiZ8gcC7wjqs8c7sEI13qtTrf8c1csF/RNBcfl8W0KoU0I+FxEB6aZQTEmMpfI1plBTjYbPE5SVIKhbWEKL4xIKK/ZOKo9iIoLDyGXHkyOGYU9uAF5vT4djdC1bvLsRyidbUJ38Q35rI5qY3hEDIwU7aJfnF1FGDIbkwIVGL8yv+AD69cWtP9DjfCrtCgaFaim1QbwoDIasXFkk5OU8AEzTc2a/N6c7ToC9JqL2+GYo39wixkULhAhVXAcznW08CIYXMIEI2YoQftoxTOvp3golgRIjk3QA/e1yJeJLIoEVwH+YCKMspnVIzgNxR6/b9DrmBkxGDK41+k15YucIb9kRjZa9IrV+s95yfFst+cefTOgF7pVYWrD4sBqzyQhCbypAM0ZKdyp5+2tIhaAFP3bvl5KPUC2+MSQSLzLqU1Hur78F8WCF8yvWYIsOC50dXdgjw9H7UdEo7QmcrC77AEcNqReUpyX10SgpQX+7dU0lkTNpUTBzMRYjJjy6UFChMAm4ZmSwmESxUaYUm0l4WEhWLZWxEPkZyd0Pz6swrQoYdQHEpQHxEEpRMBaUuhzhLypJ2xc0Sh4qirZYppQcRpjZMNoURu5sSCiT2JFpl1KunA9S5aAIkOae54EKKRGosisSWFBAEM2PoPIoovh/UtGm0o2FMprkXMwBkHGhoUBxWLTiW0aNUosn/hgDg+h4LefBjfuDaDsOtsjFLhMJnr/UKYhGotIblIbfkOIpUN6nPEf5YNotJgeujhbxI8VMGY+7Om8I5J3lIrwaS8RJB2CiQ0ULKkLyD4pqYqQlJOVghfyICwcR/o6F2kPC5lQLsJrwhFjFAxEn+ReB8gOVYRqDTjFgJncLwKjxp0Ok1eIVkZDBYMfo1Zhn8QbZBNK4tCi6eN2WmRhwXzqq1CidVFubvyPi0KKowJRFYaFiJTtkZeSrmS8BrJ/9JubiFCkOSwPX/EmowocfFMxxtdiuXSGRhPcGYIqJG0B1964YhT2xnoaeKYPXknZMc4pYrrj/fnCXEEmKvN6ky1xhZNmMg4NIOnciLEfEPM1rQR1jPyP4JtNt70SYZ4t86ZR8f1IHpxHXF3p68/zIx3dGgUdwnOfRIywnQAM5TcHeYJFI3qkgiNYSIxzvwpmiydgCjoTOD2HgJ2NlkCcYM6BexTAlA8EkIjghPNHh0j3SY469N7n0/4j9QYCYTdC6DJbguB2MSM8EOuzJ38emQgHdAt7iIbmX0UwwLP2yF5aAteSOJPsDdZE0+8ZsDbLBnvinzZLVk9ALOUD/t2OTU0lNRzFxE/gSt15sgTESqOMkEsTSs+Ctkjj5g1QbUr7MEUF6jY2U9McbPE6iC6w5e7RBDOsLy5H6HOEITZjyJ9EhHPk1OrQD6B9UDYULdGYjT4jJGBwKjfBwY1TmZaRekEJjIxOHC5OxViQvs+aQIBcyhugEJbA3ezGba9JcZiE7HEafdHAORCZhaTWlUQraNmnSwpER+CJ9cujECHIX6tYWVD1QUpOJuFGUF0qIHUaI9wVZS5qjDpK83IG/W2CbJKSqMoUM1MK3SKhCYS+ylLh01i/unxny5GJAzlCkmX/hVVBOYeBAuDN5sEihjn6BhMGspU1nR0UIQ1RGfwj+exSuzP71CWEnNG44+d0ynI3Aovvex6Xzixxcwh9xjxJk1+7asOys27ytw94JKIwciCYyJ5OJBaLA+Ur5Szap+T4iFv8FZi6AsMMKUQ5uHyOKgjoaXUhuhAhWq/tlWAaKdftvbOiHVDiJHlXLTEFLJq2hFxU55xZpNpEqqFZmyNDRuG+zPqxiUdQkQ+iLc+T+9YxESqR6SM42D1E84VL3kAxykNxYHEm0zv4KaaTjhdCfKkrMEJ3YPAYPu2PtzjvEJfmNdsSWPGEGg5slEcve8vhFI5JY0txWQpxAW2gzwXPyCAHytKShpZC3YUQDDuFz3gwuHkVhTHdoaOXzdiJTlsiEzIgt8zc+NulPj6ImQfGAA/mjiOVB0wDqOwEtoXnkQFZoRTqRa/xwiA/frbBITD4QjK4QmUTSE5s/WSAhP1HwT388git0CCEY0nW1Zzp+OtSYlmfCYBMxOH1YBIgui5JAFkM/tjNccacTCjXx2LDri6v7kT7yUhAKXJTSF4qc6LFGZGQ4kyJWn/idmVhw+ie6CwTfYLADfrETSYuSwE8rqMlNEGJeQO5QMYOZ5ja8uxDEHvLiMDzO5rDzfFUD1v1G/kKluXIshNGV4eCwQSQBCdfr9NUHJeSV5SDUQCOX1Etoo/HkgiX0AEgtaGTgAugxCRHcnDVIxqrnfeEfpfMBpmilxh8zGk8G9KGAYmN6rodgaMTAURD/XXGxBrK8NFkkeuZNEqlE+hGnTqWuxCP2UN/v6EBi8qt18SvCCSzdiZEEt4OZECfETnQZqa1ELpo3ta+HJuH8zK95bhgoYdQofhIwWAw/PJqvN9l7ySQgMhYQbjWoBw3jxEgiMpGypMffauW+AKQT1IKNANWkoZKx5FWqDjuUAFZUaGwXsOqwLign6bloEhlETjBhuzqIoShFIqwENCJXTZlypqwAGHo43KN8JM8i8aUiwiXZE32/IFERecjt4+eRXNskvwjaQa68ojZP6CiKHbR0YRZSpxAziWgDIVRxGSw+l5N1FIbOnqByyMHU6GGHE8+jd4Qyzw5tOPwo6fJBzxGWZmZOlFcz5Ihkkr6aA5S6DW5oOMzJZPuQSEnhdTm3X2B9LJpk7tmjhMOwQxDt4Q2RphZzutYymPXkjtVCTjU0swlPTLkrZA/sTlwaZb7Pa0xnIuQMJK9DNqOxDEd2IkWXESFpNljV7LADlJuAbWZl2wHbIa/p+epggwcTBGfDRwcydRhFF7lzuGjDiV8CYSzsvuxDeH/uVQVPdD05bhHiiP3/TBvghAefpOaQyIqM/kqbu6er2fDMGnMfLTF1ZDdgSSEP3vDE7EiECw34uCRSMjozMQanhWLkH4F0BRsbDQoWGgzePx9YPKC+W5wdkKMZgb927EL3
*/