///////////////////////////////////////////////////////////////////////////////
/// \file utility.hpp
/// Proto callables for things found in the std \<utility\> header
//
//  Copyright 2010 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_STD_UTILITY_HPP_EAN_11_27_2010
#define BOOST_PROTO_FUNCTIONAL_STD_UTILITY_HPP_EAN_11_27_2010

#include <utility>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{
    /// \brief A PolymorphicFunctionObject type that invokes the
    /// \c std::make_pair() algorithm on its arguments.
    ///
    /// A PolymorphicFunctionObject type that invokes the
    /// \c std::make_pair() algorithm on its arguments.
    struct make_pair
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename First, typename Second>
        struct result<This(First, Second)>
        {
            typedef
                std::pair<
                    typename remove_const<typename remove_reference<First>::type>::type
                  , typename remove_const<typename remove_reference<Second>::type>::type
                >
            type;
        };

        template<typename First, typename Second>
        std::pair<First, Second> operator()(First const &first, Second const &second) const
        {
            return std::make_pair(first, second);
        }
    };

    /// \brief A PolymorphicFunctionObject type that returns
    /// the first element of a std::pair.
    ///
    /// A PolymorphicFunctionObject type that returns
    /// the first element of a std::pair..
    struct first
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename Pair>
        struct result<This(Pair)>
        {
            typedef typename Pair::first_type type;
        };

        template<typename This, typename Pair>
        struct result<This(Pair &)>
        {
            typedef typename Pair::first_type &type;
        };

        template<typename This, typename Pair>
        struct result<This(Pair const &)>
        {
            typedef typename Pair::first_type const &type;
        };

        template<typename Pair>
        typename Pair::first_type &operator()(Pair &pair) const
        {
            return pair.first;
        }

        template<typename Pair>
        typename Pair::first_type const &operator()(Pair const &pair) const
        {
            return pair.first;
        }
    };

    /// \brief A PolymorphicFunctionObject type that returns
    /// the second element of a std::pair.
    ///
    /// A PolymorphicFunctionObject type that returns
    /// the second element of a std::pair..
    struct second
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename Pair>
        struct result<This(Pair)>
        {
            typedef typename Pair::second_type type;
        };

        template<typename This, typename Pair>
        struct result<This(Pair &)>
        {
            typedef typename Pair::second_type &type;
        };

        template<typename This, typename Pair>
        struct result<This(Pair const &)>
        {
            typedef typename Pair::second_type const &type;
        };

        template<typename Pair>
        typename Pair::second_type &operator()(Pair &pair) const
        {
            return pair.second;
        }

        template<typename Pair>
        typename Pair::second_type const &operator()(Pair const &pair) const
        {
            return pair.second;
        }
    };

}}}

#endif

/* utility.hpp
htudXG7TmKFeR8vOzP/6aSeXO+ZqWEC2wuBZpzpn8079ITTm/LKtvnj/Gcfu8Xj2DcXNkx20nv+5sFXIvKFr62Yy/1eXD4atRha+7hbJ3rv3rdvCVuuyEtk7wfvfcOpz2QYR1+sWl+0UYa0u2z3C2kJ51sjWkbnvDx2ypJ9M9a0dYX0yXyhurQgblEWFbI0IG5LVzJqugxFWrKyCobhghFXJ8kO2TIT1yNYIWUqETcn8IVs8wrz3zu4Xmc5fhPl15c4MxS0aYbmyrJD5I6xSVhGyRSJsXNbol4X2vNuqn51bh+gIq5WFa4iKsCZZYH6Zxtw8wjqf9+jeL1NcSeQ6yMLzbRBho7Lw+u0RWUM4TvPtEmGTLjs+wqbBPC/MzRdpUYYtoI+F59MfdGH6Qb88+vX6JfN7Fpz9u3nO35Xq+c9C882O5vydV2P+/N9FOX/Xt7/+XtcH/XL+7gf9qvZMx8zOovmW1y7bznO45wLPnZ4XPV96Fp9v3fl2m++E+a6b76n5Ppkvbt5q87aZd+i8c+fdOu/ZeZ/Mi5t/9fm3nb9i/ob5O+YfnP+r+ROj1o3aOaoq6rKo7qiRqJmowAI5C5QsUL1A8wLdC4ws8N0Cy0RvFL1n9BnRN/zi4+7op6Kfjn4meiT6o+iPoz+N/ibaG7NYTGrMqjHrxmwas03MtjGFMdvFHBRzcEx5zCH6ODSmIubwmCNi6mKujemKeSbm2Zh3Yqb/4oeqVoeCOudBfSzrWVb/TJ19pOmRrn6k/SQRH8uGHkFpavjf9afU3/pvQ3+brof71yKeBM09T78vMvvMP1a/L/TTQ3/y6Z/zzX4sGfpdeeq/0Z/02chSnsX1Md/sP//Or7X12FOPNj2+1WN7TdOsx6QeG2qfHK7Hg3p8oceKOn+76NGux0vz/3xN2VCP0/V4JerncZbX86bd9bhAj249JvVYQc+FD9Hjaj0+1CNLHT9Ej3v0WECHZT2vM7/85zkP8youFNOlP2t85eTkN5vH+94/lu/6C/57+f6R+ff/n+c//0/O37Xgn8vBNW44H+XgrJ9y0BgaU+NoLmccza8cZRpb+c7Op3F/riM+9pc5qT7lqvpkml/1zM3/imveDV3zRvZhM42pHMLzG/XLQ/VqTs0Xri1ctzO36nbmd/UnnIvz32tu7WfNrfE052+sk3GeLo397fwei3Wvj+vsuGrb0DW+8tEcP+e0+ELOHE59ykk5Wr0I5+bU6fT312fX3o8bLfTLtTh8oT+3J69Y6M/tyQH990v6/ng+B/v+XD4RuSi/P35ONZ+Ty8U+3gd7hvaX5nby+HUOTr0RfXHmd/LRNdP5s66xGnN2To3rjDE75qP6XTVpnNl8NJaTk3KfnVP5uu8dkdfo0Bny/bJvyk/1z10fDnethc68HrNjyH5rvZwcNbeu6wv/5popt99aMydX1Re5XyPXz312//xeOmDhf3cvhed37ZvZ8RsWdl+vwuf098+1aw2dObN++zqm/P7Ytfb+hf/6tVbzKX/nWqscXXvM6ak9/zt/Ym5nrzo5uOv9rWu93f+F4v6b/lvzr/Mfzq95nOtYZB57xv0iB43z9/IIz69csP4z/6P6f+8ee1fcv3uP5fm1///l+f/Ic07fIn/uGrjOIn/u/v5HrkHli/zx68Cffb73R3pw8b/cg987hw8v8v+cw4lF/ptzGNFX5eL8t7O5JPhnc9OcTg7OOdC4GsPJRff42Xx0n/9lv1WX7sfOPlANv+z/Ic5zGNeeNJ4X5Pp/sR+VD+xJ53lA+PnQH78//t714UD/v3t9uCCiTs2tXH6e+w3Zg6GefBGaV7lobnc+fy4Pza08fs5HOSif3+/Bgov+fz0=
*/