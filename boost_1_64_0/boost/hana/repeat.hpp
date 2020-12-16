/*!
@file
Defines `boost::hana::repeat`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_REPEAT_HPP
#define BOOST_HANA_REPEAT_HPP

#include <boost/hana/fwd/repeat.hpp>

#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename I, bool condition>
    struct repeat_impl<I, when<condition>> : default_ {
        template <typename F, std::size_t ...i>
        static constexpr void repeat_helper(F&& f, std::index_sequence<i...>) {
            using Swallow = std::size_t[];
            (void)Swallow{0, ((void)f(), i)...};
        }

        template <typename N, typename F>
        static constexpr auto apply(N const&, F&& f) {
            static_assert(N::value >= 0, "hana::repeat(n, f) requires 'n' to be non-negative");
            constexpr std::size_t n = N::value;
            repeat_helper(static_cast<F&&>(f), std::make_index_sequence<n>{});
        }
    };

    //! @cond
    template <typename N, typename F>
    constexpr void repeat_t::operator()(N const& n, F&& f) const {
        using I = typename hana::tag_of<N>::type;
        using Repeat = BOOST_HANA_DISPATCH_IF(repeat_impl<I>,
            hana::IntegralConstant<I>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::IntegralConstant<I>::value,
        "hana::repeat(n, f) requires 'n' to be an IntegralConstant");
    #endif

        return Repeat::apply(n, static_cast<F&&>(f));
    }
    //! @endcond
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_REPEAT_HPP

/* repeat.hpp
ba2UtWQeVRBKjOIfUVqumO1l3Va1iPiHWEMUcWD2xcQwk1ZDu9GXk/JaKjtuYC27UK+32UZ5D+1dvz7CXa5MBQpOReumLj9RS05dfi6NGMKPz+1cZMXb1hRsMPjxpqabiB2C7yW0fuExWDS0WFtAVJ9E3yA0GHoILIStYL8NTRkSQ99vksaxDfs5tDlzmrdJ1nnjt5Od6mQrmKmCTJPyLpvbR4LmCO30wCaC5tFb/cIklb/1LA2Wv2OeN0y8gcMk2XctzqPxbygxf2kuj7gPDryOJbute/47WmLzKXK6ZJoQmCFGyVyaaRxFl+eDBDrL475jmhGPB+X5w/4YRzj16dRcmmAyuQ6d2kp1nZ1HB/Md9RdXT76voC0CkdCHecS8918i2vYhqMIj+qRTGPklKcmVcmUxlXnHysxZPE36Hnf5b+Tvuq5r6tr2FeWXKzX3dxIoKbUEQsyHEYZH5wre6qaf8ktKbmBINdJ3RVYF7gmUF++9H2xd9SVpW76hEik/WfIjr/MZr45VlbWFbWR+V5j8G35sas+V9dEyUfay1E2R6+8ps/n6e5XOixG/3pamrfVYf59xXCPYJyh3fHMUb6fisMnU9NhBlGQwLjnt5XWPgQ9fMXtPOJLxKZgFKcw5aSmjHCpZ5UYbJEaTo7yga6JvdQnfMkFMU1UD3oOgTBavSBS6g5sxBbs5EMyF3oOyfkjW8EZakEb+y3tQWH/0ffOnlN+SKp11BXBz6znY+jrK198c4RM0pRam6UfflS6n8RzZ8/r/F+OdJNoT684ZyAx56CN8X7ms1QOWJbfw28J1Yt6hkCcg774Sigzp+DZwQlceMCGlox+wk3IZti2Sfm1MV3a5g/uPT8d3ABCmCO31U5qRiCVz++sfeC6ifnkTNr+ben11cMgk6Zf26X5DC1pivBvd8QqQTvdJovt+8HV9Huwx+zthZ/ZpZdoLsntTw2rTettCm/BAcFOKjp2ICELWyPMoD154/1fRqQIxSeLETqrQtZkYzEReeHCTxiXQpJHBc/v7mZ9GtJUPpBM82y5+F5wZUx6oQ8G4qvNsrbFFUzuDt2Vj0zLTSQWSrj74LRFn68R/5xfe6OD+IGbrJWBOjNtK9ZxfGOFO1zC4PeczPuQgPeeu37xJY4s2NRkvw1prJNdN8On7L5khr4u/TGVEyUQLgriP07gMg4I3OBIHM97P0JuS8Dr/1PzchTNcCtVbbBflFiwhiLAf+4jxFmm7lkxdGNX3ksG0DY4cM36OH6P0nHuALvivaSK+xHbWAkSsAdCFrWD8VKCPJ+VTekdfXddlU2Af/AUBjBw2guwxrKVHrm9ujvF5Dn1lHE9AStUXNl9LBKgn2rXgff+Lmbyvuei4sIrt7cJc9VNvFeX9dbTxyNavZq2SpSuFHO6fpCTOEFSj+5tOkfSqF+o013Gal4gT8oN56zaM6gLGrZ63tuN39us38brld6Mv0SzmyDpijqC/UYbpsp30sztvS3vEsOQWY/ofvz+zN9BayGAsnEHb8VfmMovrG65EZ1gJSwGHLBfHRrbjl+6TjJB9i5IpZSsQGf9LrA3fnxAnMJw/z0U8jZPy/gFsA86EmH61IX25EPqktn1hog7ueZBHv+P4refyMEg3Dnmjdye6txzz4eC6xpRgJbTzMHTExreQbB/izPHeVoXFtRIgRpcybAes53Wfznz5Rc+b1lnwa9/YS3osjlhfWT0N00boSgo7zOu7DIsQyiXRKXhUBR5E10F5XMSrVsHVvYP6wn0pl9U+9oURXmZVuRKaF+oLe+l6BFXb34qXtvW1tJOxKdbtbyifRdMbXlU1RD6O4VV2UaYa7ec+CoV2bZPjtB7ziLc=
*/