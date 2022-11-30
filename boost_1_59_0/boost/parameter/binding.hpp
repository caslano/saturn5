// Copyright David Abrahams 2005.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_BINDING_DWA200558_HPP
#define BOOST_PARAMETER_BINDING_DWA200558_HPP

#include <boost/parameter/aux_/void.hpp>
#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/utility.hpp>
#include <type_traits>
#else
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#endif

namespace boost { namespace parameter { 

    // A metafunction that, given an argument pack, returns the reference type
    // of the parameter identified by the given keyword.  If no such parameter
    // has been specified, returns Default

    template <typename Parameters, typename Keyword, typename Default>
    struct binding0
    {
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using type = ::boost::mp11::mp_apply_q<
            typename Parameters::binding
          , ::boost::mp11::mp_list<Keyword,Default,::boost::mp11::mp_true>
        >;

        static_assert(
            ::boost::mp11::mp_if<
                ::std::is_same<Default,::boost::parameter::void_>
              , ::boost::mp11::mp_if<
                    ::std::is_same<type,::boost::parameter::void_>
                  , ::boost::mp11::mp_false
                  , ::boost::mp11::mp_true
                >
              , ::boost::mp11::mp_true
            >::value
          , "required parameters must not result in void_ type"
        );
#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
        typedef typename ::boost::mpl::apply_wrap3<
            typename Parameters::binding
          , Keyword
          , Default
          , ::boost::mpl::true_
        >::type type;

        BOOST_MPL_ASSERT((
            typename ::boost::mpl::eval_if<
                ::boost::is_same<Default,::boost::parameter::void_>
              , ::boost::mpl::if_<
                    ::boost::is_same<type,::boost::parameter::void_>
                  , ::boost::mpl::false_
                  , ::boost::mpl::true_
                >
              , ::boost::mpl::true_
            >::type
        ));
#endif  // BOOST_PARAMETER_CAN_USE_MP11
    };

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    template <typename Placeholder, typename Keyword, typename Default>
    struct binding1
    {
        using type = ::boost::mp11::mp_apply_q<
            Placeholder
          , ::boost::mp11::mp_list<Keyword,Default,::boost::mp11::mp_true>
        >;

        static_assert(
            ::boost::mp11::mp_if<
                ::std::is_same<Default,::boost::parameter::void_>
              , ::boost::mp11::mp_if<
                    ::std::is_same<type,::boost::parameter::void_>
                  , ::boost::mp11::mp_false
                  , ::boost::mp11::mp_true
                >
              , ::boost::mp11::mp_true
            >::value
          , "required parameters must not result in void_ type"
        );
    };
#endif  // BOOST_PARAMETER_CAN_USE_MP11
}} // namespace boost::parameter

#include <boost/parameter/aux_/is_placeholder.hpp>

namespace boost { namespace parameter { 

    template <
        typename Parameters
      , typename Keyword
      , typename Default = ::boost::parameter::void_
    >
    struct binding
#if !defined(BOOST_PARAMETER_CAN_USE_MP11)
      : ::boost::mpl::eval_if<
            ::boost::parameter::aux::is_mpl_placeholder<Parameters>
          , ::boost::mpl::identity<int>
          , ::boost::parameter::binding0<Parameters,Keyword,Default>
        >
#endif
    {
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using type = typename ::boost::mp11::mp_if<
            ::boost::parameter::aux::is_mpl_placeholder<Parameters>
          , ::boost::mp11::mp_identity<int>
          , ::boost::mp11::mp_if<
                ::boost::parameter::aux::is_mp11_placeholder<Parameters>
              , ::boost::parameter::binding1<Parameters,Keyword,Default>
              , ::boost::parameter::binding0<Parameters,Keyword,Default>
            >
        >::type;
#endif
    };
}} // namespace boost::parameter

#include <boost/parameter/aux_/result_of0.hpp>

namespace boost { namespace parameter { 

    // A metafunction that, given an argument pack, returns the reference type
    // of the parameter identified by the given keyword.  If no such parameter
    // has been specified, returns the type returned by invoking DefaultFn
    template <typename Parameters, typename Keyword, typename DefaultFn>
    struct lazy_binding
    {
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using type = ::boost::mp11::mp_apply_q<
            typename Parameters::binding
          , ::boost::mp11::mp_list<
                Keyword
              , typename ::boost::parameter::aux::result_of0<DefaultFn>::type
              , ::boost::mp11::mp_true
            >
        >;
#else
        typedef typename ::boost::mpl::apply_wrap3<
            typename Parameters::binding
          , Keyword
          , typename ::boost::parameter::aux::result_of0<DefaultFn>::type
          , ::boost::mpl::true_
        >::type type;
#endif  // BOOST_PARAMETER_CAN_USE_MP11
    };
}} // namespace boost::parameter

#endif  // include guard


/* binding.hpp
frUb3dM6IX+kt645fQQCyF5MH0JOpE/ah45Tz8BMs8gxvhfLm4W9qRv3PqTAtr6Z/3Ygp8HNA+2R6Kal+ytOsXsi5K2vm70sEY+E35Jd3QAqChkSGVIZ4hVFsgWyhdmhpdnGyCXWZaK9Iids85f0ydfW+8/gV9UG/UN+seLqbEG9ds36mfqy/uoDDSpnqDEFM7WCM2fe4XXnDSw+mxgazCYnh7Ey7JCwao+/dsDZ6RjrNv0tDA2GT+ku3Fyz0cv1u3s8hHN5Zmmy89p0X1bTe9Qqi2iLacsmy/5tUHa0NjqtVaRESfy1bu1MwSwxyrIaZh85NxLOP7ANscq8DdumT9gkSCfEKkxitdmKZ28auLpZjvyjtnb55Gnt6sq17MNHP0PGoYkwpatAfiC5trfMo57Nzt6h4bye0N2Gevfv6Cjd9gm0iWrlumE9+SYdPkfjv6pEenZuZHR3gim8lsYJFkWpv4a3i3/mqLxD6B2vKn9lbbNUsOsV3CVJTpagGkdUHPix2TZ/zH6IRT+b+PSUuxbuNVU5KSvFrNDkNHCN7I/s4FwUM8G147g5JMvVAx/PqQAy2cR+tQXLuqXudY1YsqrJXDqto/zDmV8bEudxFirZvm8lCA7wshxPCtdxL4TrTM1/eHy1y3MWiywlqhD27jPXuwHmwjxKSoBZM9cwkkXsrAXDYW6dSkRhZyRcMghBMUvZ8EwTgdFRfn+pZ+O5SR6s2LK/6hYjJqp3UZWhjg1P3bE+2MTNM2TWIzxd1tRVISeuyn/6AT6x8ynv2ZnXrDgLeGBxa/eZy8JXD/YFbm8tf3iGMSxOCG/nfz/44f7v45RLXTgH3SFPvTGFCCkHmTKzTLPFkOkIcBRN9lZhvNnHFDpdAVJDPtr04ruW6xbX28ee8RST4sVfcpngt4xMMKvMpb8HZFrTDPpA2n79gSaCvHeARkrj/GcJTbkbtH7WnFvKcv59teY8k+vsNsO30jjRfFCl+Wk+8/UO9H7e8X/+ADDTK3h6Hn8xlCgrynJntij6GVICWFXpCTsAhn8AIi6+qecHENz7W3ydDVZSskOY0AUm1Ygze1+zLz1IAh83vk4jo59wHUijfAnrxms5/nFwXP6YQqPRmMj/ekJr/HdTe96Y6K8ZH35Ow5yC4u3xvNPg8Cd9wQ2ti7J/H9aObO/t0//7T+jmYsR/Zk0zX+JXYZiIvTMRC/Y3Puaz8gb0NKTC94zOZg4lBTT2+NeOk2FZUdJuHjIez3joVCx3kD+iF2BP+Hs3sI2TB/MdJeiX2OUnW7hHUAmM8MjMLYnO6cUZMbTnFF7Q7EbTt7rO6XUFyYu65LdcrC1nFfkL9sv3X212Iegvtn3CY3jtxz0OzlZgdfRvl2fVnum1V2j/mKYZYkJwgXCf7vE1iHyJG2EV1v4Zki19pyeI5G90+ssYFeTsKK9XCMxnCyiYaZL2oF2f0QRovRAv/n9ExwYS+sc2RP0bMMKsTOG7mMjfZNP04p/IHygfDE4RfBro/QxFX3q7lyiLuELQyePQhf54fKMNWyYi4JhF3eBFEd+8I60p+P6xTWSUhP0lN4S71RivpND4eUfgxpTAGa5BNQ+E/qNRDqHROIncIxuyO6F6gqtHlmmc2Vpw3ECJG+ZdvsE16maofvLD5zKdUxh80tUgH2QbiO2F7JowyYDfD4Gx3yFNE7e5u+inCuCWcDOIcU5P6MUiN1Wjz8rZhlWAMAOegbxD4Tx39H7O0490lgglSBi3fHyYAYzpG9RssgSGoAvBE8fpZRK+oF8//SAr9Pwi4ORGtp62C3kY9/tajfATapo9iL4f/jzKAMPjnWsQShMdvKDlfdYYz+jXslQ97qNwPdSZwLgmw53Ir8LEBEJHx7zO7N/NSMCdEU2BO6FfbULLvAPYrL5IvJNrZs0s/VWBz7/MV37zBe0IegOPhBW0sYUs1Aj84pvsiQkFDuGJI7jADfELbkGme2NcuMxnA7Ykf2Wqjzw5QNqmBIMToVBRePANT9lN2wn6k0HPSUD005Xv6GZvgfsE7Yj5wdhB5CBP24kDSF/4dlH/xZQPPju7wb3h92vDTFO0IwCBB/DEufxBIqMU/fiUOz3ZW2EfyJt/vQDhcO86P43fZYjcICYD7aavRflQ8cT5UEMkbS+QON9B9lG7cQ9Sfoua67o7ujHccU1i99oBSSKw24J+F+OGXx/aYM4TteMe5Pw2W27g4TzIl7kBSf4Gcr0TnWfsBpczBP2yxe/JaQoPkLgxXITrl7jxozB/F0z7LWpmjuqDdnDCPk0g8gWz31z302+hiMBdeJQM2KC4otwwTm/Qz4DdOEW/IIVC/DZnSGRdCqFN70ypGwqLNttsvpg75A+q4fuabD6wN3D/sC8nOPMZ4k/gTz1n3H4wSuAzpzfiKyCj6SQBWJONL9qD7APySg6dcL/rzuUN8yh9Y3p4QD6NGIjYr5/v1+rwBHsDLQyuI3ej2g1IaFqJ5+9fYUKE6QX5RsjGh/x6zBYi5XPCN7cvxAvO/pSmTD7an97abcn+1KLMO7qkS77gyf6EPPpmTzMvXnptmo+sXeTVVmOSS9BWeXiIej5lsGjqiCR01ah4USz1jPymfKvdJ5TwkTYvFcfMzkQE3e/5a+czJHTgwlG1/sp2sbtyqwCYuALSuL6rs0/Hte+ntQ/K8D5cvqUXVsTFWd5xSYKHSWe/BfgX/6tAenlO43wE+Q5EKePfFZC9Jh4SELcL3BeQtyvYz5PKqL4L8Z9D9Wug4GvpNccaZypb1I29UwAALP/TcueqlN46KqdxTSuq+bkw/XNhlj0FYt033iFs1Fa6Y+Nzd4V+0+nME6B9d7P3xNGqy9KZxDnXYeXhoxw+sbO+qFL2VvWlwdZr3z+HjjTZffYVbG3mX1jr1O/D1j11ALx/YbDP0T67a9O5/rHt1XEOOP6EsOeo9rJ8ypGrvuyP29pxbRn5biP4Novz3+1hWfG/3xdpItyQesCoBXwvTLSamE2RfdumEn42F5sIbii4HrR2/3Nye1eT8i/Zr1N+s8yCz6sLcR/3Y6Xxb+vLk9f/u7TsjP4dnyifh0d4jyYwLGEK0gl1yJlR9TKC9r+D9LIX89Q3wNobjwKf/sntc+/95TPQS0D3ffH6uM6H5FGqdx+ubThWp9F5zXXh++7UHND9YWkPKH4tUX20v8wESD26q9Gnl71d8H4ZnbSREAKuXntUn9l4G6v3N4+jzGuuY+0nK/agOiMoiNXlrx1SX1CdVA+Hmf/RxFeRuPuQ1Gwcro9OkbYJyPngdXAdItrkvxyOj+H3Ju4nVRFzpBa+HJ6P4gOLX/6/Wv58QxQc4ZuBrmh5Olwdg1KRCrWRmxpBP3VJ3LuD95OsSTiSNr9a0E5SkJ/GxJ4b9tSurVm6206iEmzf12JQykj/K7uc1LXZjda9fPnZT0Xr2vi80S+zh26nXBd+tUY9ykXXZxzGfp9Aa98T/huKjqu/QxLXWGpAZv/4gt6Q8R70HkVIwCXliLFckjr0RwUDszEyCkCINwYVfr4D54tNzPrlXn5E41WemqvIHuDwhtuXkxRodQE2AILnhYwgTJDfYiFs4YBhQjc00IcaMTi5fK1jC8Co1SJWmxCQwWUaRfw1/x+fShIuPj56Qbu8a+1HGPLHF4QTfZt/k9vlWJorNd+G0Ej40+FJnqNX68gVBM/T4YEbteMKpWOWO6fjhRunI+bValIegPrUszPMLEPYOfbOz2bU099lVEomxttDMi8PM7mRtyA5FInrFZtg/mRERaAc9Z2juLhLdWwjRrpzR2n+SnledUGaxmUdjZsGjZvaLyZIv2T5b5B+abF3a+K1Skn3SBtw7B7B+MGmbk/i9BVerrPOzn3e17Ar6ZplI8Vr+7q4y74riX7nupinutg7KvE6P/HazKsV2OU61zRVRna6pqe8fvpK21V7+npw15GZe/VOc3+29qXXnp1rvuEMx/f9tzT6hNL0UmXdt1Jp2H+nlBBzpJXLMc5G+W2PneL6lB3KHxA0g/5hCOEfkeuereB74jMBCDXQ4t+RdAj26Q3cTbl79QqievXB75d/5RW9oX71seczfl7Uvt8yuRonCFF6fZO0/QTOdF6VAsrXXJzfxmJKijD1eNZe3769fCZKcYybBCiuinT3eTnoXXMnznNO5uqYn87UOhB1a3i/MWO87bb8Ww5SqR1lTHXesR2vTs436Lg9CDw2PQl8FzyHJXTyAZQ7PFCHnSY1ykZyhVDVDEUS4msv988NtwLy9d5h4UPrJMv0Hb9hAwAwBVlSo2sh1dGanZnkVRL+Z/Ml1S0tqrN+jjvy7LdFNKv/NrLWRHbKzQT8Hy5q3RGykOSpa0IkOP5buIF5AioTnSVbncoqX2+uuXVi0mmhSZprgXCfhE3GXZfNw2gLsJArzuTdXiK7cCOYW23nkewxVLB0y0wv6nXqGyNfHdnej7Vi8oxduQ7DNKunEy4T+VS5E3+aZx5/do3z+W+9MN/uT3bWarh4r12LblQdorWkyZXN6pTPZ+gZfHFJ9I5w5Ai5kG93yF7yfNV3i/u4w3yk9bIGMpGLurTJtp1ucm9VTtgu1PjV6/bmUd8LiNzB5xlQhMell87ySCwDyw43/9jpCqC/Z4QuL6k79jYtdrZSDjtFuR4pZgfnd2NbY6PduY6WIo36zi6jXGSZXobn85RGwz7TORkfxv4hR5xyuDM6GdyWqGBdN9Fh2z5VlhnqBHveCFaHa7Pf4d+78aXVMTUlq6qrw5y9rnI2fVWcgcYtdX18XNHHRPSQk5Mz2hq84cL2kToh69JYIevy+Ty0OTuWVCfPOeNbdn7viVEmWnlra9N4MPee57wHn+fSBF7pl2RTjI+P89+5R/EeYB84aSVwR81y9F9kS/JOgiyw3jsUeMiyjIT/De8Yub5QjpREul9k1fQvGSqWuN9qJr6zGBnMxmr1seJt3skY76Ia12IuifAp4lOAxG8GjuUbx22NzQu9z9zcYLl1yVMV7hQKgM9RicrU5GHDAhlVz1aUo0bjesQVWBYVLEe/gr+8Skt1yCg0BJRB12lsPsuPMs896UVF8BVYQM8pbPwYe6VhLzkWmdAwMI/go6wFwvvF/JGiotjh5NLepDR0Fn1/MCw/1h9AuVbvp4WUm+MCWGW5jnKJbPxMvuBq6ay0119hePxBAKykvu/3x/WvhFVVqK8KIRru9Bc8ySN0zTti/g3PoKHLCt5ZqdBMbd732kqifjKRo/ZSyK8IAy3vUPmY7uJ9/JPbhDEKSn6ub+7/V54VP78EgCVwPTKjHZtuhCl4+9nm7tYbkD7fJyU+8M8+juo4z0SOFM99E10xd8nTBzhemJzvsU0lOlenr19dWN98ebj3QTtQWeHT+N4Xkjanq4DPs75rHu6J1mtz8zTZXsJc6s478yg1KHJytZPXRekxgJAZdI9rPKZel23BjQhgCz0xTZLygn9/7aN16nvNp3Q8Lzbuu+oG4HXKBVJgj/SL+/m/Anek2Y+pjPsrSGOhnWz0f1XwfzkYSLc/4j0wQ/9p/0KxNyTqLlf5dfRlR1c3P2jNsa2mvj/nmPKwAP0CyY4z5upSyt4RHf3Sm7Xgu2Dl707RcrwWSeTLGTpQ4MOZogkUWji/aUIP67TE6l1CfYWDvj/NWCxJkyi4KXqOgebicgmKBVaYHbj7S+w+1/hsfvY4/vFlx+k1tItu9pygVYFypVAv5k7MuCZVsbe+2mv9ZzPIzhW8rQibJgWrqrvtMLHOYiWQO06K6snD+DD/tj63fEt2El+4v/52lniR2GFSCma1Y2NEISjhQ7f+m3qJyAXUJQSyU2oOGe3mlW1dTKkyhk61ymr+IZWNvkIVGkNMYTE5fNtkXXG2KHDd2le7CoW6N9uPmxxXhT9UZdIeTJaS2+Jcllxu5wNjoIH/MObJ7dmEo7S3tmXETK6/KjG1hMJSvhEZcvKxsx/P+yjQg46pSo1460VH30VO/8smu88tCpbHupbJe3tTpogm04jt6inKk+6qha4h8/x86I2/Uny5zJjN3BdjmPkRNURA3uTzLQBbTFl+KlpRtIOtgQ+9oP9mJbpX70ETTl8BJIkITtc9UFTnEYaMYg0+ptCiG8pN/22L6zl1LoJmyjtznMqFxWz/7NdCXIX9hdmz0foGvvLGrl3yjbFQFpva5gu0RnekrTtqQsDH6bpE2ybWpQmanAS9tlsrudyMlhrYMeyzlZ4swHFk8QmXQ7rhczipBfWcQ8usZNXP+LdRtTLZDM4nJj3expv96AfaYTarJ/MwTA/9KU932VDM2Eum7s5x4Bpt4ZYIY9reBuC3OXZjbw1nWXdvjclAXFNfdW6IlzvLXmbnPIOr4YUU4YayglfxjavJpFHCI2p3BfQaIdy1rLztd6bNDrfmZ+Xp6zSr/oUDDcJ9KyKHfffWYlvOlhayTztFaa0IT4Hhq72tW+QVoHfKnOlTrQ2MveVvzEa9nW4lCTYiptVd8FuIlgdCbJUd6ACN3B3mJydLaxEFqw3PW6QT8QGVKI/WreG4n1RedN54ddk2A2t13SR5omXF0DatMVNdBcRbUA3P3H5K/qe2OWAC9TyS0Dp62dxbadE7BAQpaStYQ2Yy5HiOwiLe1Qu+/fWoGGSP5qBCdjsyaUxctpk8bT1ZBx94dlrdmkvnOk+88VmpZBeH/4uwtC4WHU+/o/otzsV1Di1tas5PpPxMQNXN5i705smzDBP21ea/72tg3YBJWEdX54iHjJkIubfqMAdHhFAPK+LR52fmR0dQjHWHP+3bAddrpyPwZ+0mzIZbG1cvgpDwQbT8sqMCt8JpDSODOh3wzzDGKxsO2vxFDK5sIIAlyoFar9FhGcshlo9zQJxsWg1sGjVkUC+Vc8orewPGHEiUcaIm0gF9ckrDPAOZLRbC8pU52QQysiRPo2TtfKsDqIlY4pPPzlBh+f5TDgCMNUHkyYEgyVszr8SAwW91BMsV/Yp9+iBe9NHPmpo3oRNvZwvKqZDbUTAsJw+ePCzRDOqwVOWooTk4RCbtvi+KRA9rpaNKQgNLvIsfJsaxHCbWIqyIYWvjaGblaGXtSp3J7z4aO1+ZSjKfKWGax/g7K+DrfXQ1PjSpesCqUcRKjyk4ojD897gRrqj/fv7xgLMFI/rEUjXJFiaZJ1WS4t4LIgfU6xLhyEGw05Fkr0by1WZ7yMLVSnq9tcY68WKfdc/b0SrxzOO7khSeW3yhorZlzYMeGVIindW5SfPLecvGTsRdvVvEOo05pSGVIIePYo7onqY6jzAUApvLpmHvTzvKM1eVZ7T3Spvbefq8xswAbA4e+XxSqRjK+T85axuCooxSTOuHMaylQMdlV6wiT9fRTmE+N7lOFEfDft62se1fL+esSweDTvdeapQe2FjI4VMo7xGTM/fuZAtnsdMmI5BZIg/36XJzZA3D5OUrU2aZIRlaKdmxeczEXROgnV/QVYn4a9mlApqvEaad3vsZsSZE6xhIdsJuc7baHQPJZot5ZgRLeRznh/uyjQqmRwgfpYRzrOG/nLTuriph5NtiqNHDsa9eZlFa/g5zoRNJBVOpb+E42zgOyLZDowv7DergJfGKKzPnXpyGJN6Y0KOv3GQ8+YLN2A2K0cCWlM+eVcqEp7pj
*/