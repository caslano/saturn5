//  Copyright (c) 2001-2011 Hartmut Kaiser
//  Copyright (c) 2001-2011 Joel de Guzman
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_CHAR_GENERATOR_SEP_07_2009_0417PM)
#define BOOST_SPIRIT_CHAR_GENERATOR_SEP_07_2009_0417PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/karma/domain.hpp>
#include <boost/spirit/home/karma/generator.hpp>
#include <boost/spirit/home/karma/detail/generate_to.hpp>
#include <boost/spirit/home/karma/detail/extract_from.hpp>
#include <boost/spirit/home/karma/meta_compiler.hpp>
#include <boost/spirit/home/karma/delimit_out.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/container.hpp>
#include <boost/proto/operators.hpp>
#include <boost/proto/tags.hpp>

namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////
    template <>
    struct use_operator<karma::domain, proto::tag::complement> // enables ~
      : mpl::true_ {};

}}

namespace boost { namespace spirit { namespace traits // classification
{
    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(char_generator_id)
    }

    template <typename T>
    struct is_char_generator : detail::has_char_generator_id<T> {};
}}}

namespace boost { namespace spirit { namespace karma
{
    ///////////////////////////////////////////////////////////////////////////
    // The base char_parser
    ///////////////////////////////////////////////////////////////////////////
    template <typename Derived, typename CharEncoding, typename Tag
      , typename Char = typename CharEncoding::char_type, typename Attr = Char>
    struct char_generator : primitive_generator<Derived>
    {
        typedef CharEncoding char_encoding;
        typedef Tag tag;
        typedef Char char_type;
        struct char_generator_id;

        // if Attr is unused_type, Derived must supply its own attribute
        // metafunction
        template <typename Context, typename Unused>
        struct attribute
        {
            typedef Attr type;
        };

        template <
            typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        bool generate(OutputIterator& sink, Context& context, Delimiter const& d
          , Attribute const& attr) const
        {
            if (!traits::has_optional_value(attr))
                return false;

            Attr ch = Attr();
            if (!this->derived().test(traits::extract_from<Attr>(attr, context), ch, context))
                return false;

            return karma::detail::generate_to(sink, ch, char_encoding(), tag()) &&
                   karma::delimit_out(sink, d);       // always do post-delimiting
        }

        // Requirement: g.test(attr, ch, context) -> bool
        //
        //  attr:       associated attribute
        //  ch:         character to be generated (set by test())
        //  context:    enclosing rule context
    };

    ///////////////////////////////////////////////////////////////////////////
    // negated_char_generator handles ~cg expressions (cg is a char_generator)
    ///////////////////////////////////////////////////////////////////////////
    template <typename Positive>
    struct negated_char_generator
      : char_generator<negated_char_generator<Positive>
          , typename Positive::char_encoding, typename Positive::tag>
    {
        negated_char_generator(Positive const& positive)
          : positive(positive) {}

        template <typename Attribute, typename CharParam, typename Context>
        bool test(Attribute const& attr, CharParam& ch, Context& context) const
        {
            return !positive.test(attr, ch, context);
        }

        template <typename Context>
        info what(Context& context) const
        {
            return info("not", positive.what(context));
        }

        Positive positive;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Generator generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <typename Positive>
        struct make_negated_char_generator
        {
            typedef negated_char_generator<Positive> result_type;
            result_type operator()(Positive const& positive) const
            {
                return result_type(positive);
            }
        };

        template <typename Positive>
        struct make_negated_char_generator<negated_char_generator<Positive> >
        {
            typedef Positive result_type;
            result_type operator()(negated_char_generator<Positive> const& ncg) const
            {
                return ncg.positive;
            }
        };
    }

    template <typename Elements, typename Modifiers>
    struct make_composite<proto::tag::complement, Elements, Modifiers>
    {
        typedef typename
            fusion::result_of::value_at_c<Elements, 0>::type
        subject;

        BOOST_SPIRIT_ASSERT_MSG((
            traits::is_char_generator<subject>::value
        ), subject_is_not_negatable, (subject));

        typedef typename
            detail::make_negated_char_generator<subject>::result_type
        result_type;

        result_type operator()(Elements const& elements, unused_type) const
        {
            return detail::make_negated_char_generator<subject>()(
                fusion::at_c<0>(elements));
        }
    };

}}}

#endif

/* char_generator.hpp
n9I//W4r/YN5DxorOAhYv3nYfl6dWzNRNjyZKFMBE30M3wgvCsDeKcS9BFf6GMiFLa94hfQuvzKnqSKzMGS+ynQarRYm2IqEAH5GdG45YXCPWTFmHvGJ+8pCctxooj6fW0Yfc55joB5YI6LYeTmBla639H3phravOdAyAJskcsjfUn0nrVG42tgXMoJHVbEVKXLmFoje8FBmGYPk4fhGfXbKhYN6zNho3y50ThuhEla4klLKyvGKDQg13DieHv+aY/kYIgZAa7ROdwbkNnb8CdrL7EfKfyQ8UjhLVZQNGBblNuZ1NA7gdhqRffr5sU/eF/bp5wd6ayopt35+SPhq/Xx2+Ar9/HXaA74lY7w1V7gdOKXMbiYSaLAbUo99jEBS+EiYEpwh2rPj7yBA9+vyem/N0/S50FsDzRP6M0o9XZFipT7oQmieUzt60WbQMKXy8Z30EGjMjZ8X/9zFNOhKHN771bsoH97zfiFeMupusFXrp3LHvLXXAQQCOzXIN+acRgSSG+jeFtF8PAhuRisn0kIVRafu9++JjM+rXOSfcmrpNxcI95QFRqAlt5F+34oGWmDnT6yE9/VAiz/QGL6G8tiinfklp81pVotWfZkq7OjDBmZGFs7sBhnaIWt8knLdRLk63qGE5WWOAcvk+6WnTXnFidN8ikwjYjqSZiuU5IBsqnoLxpm4ZO22+KNygqccgeXlARlpKVhUY5U3PKwXeMPrmG8POlupnL9eQVudRdEOS67HZRKhNgzlPqpWSSoRoLGUXFNJB5IcXT3xVrcZKp8wZlSGzLxCwamWWlPLI5LUvIkV86iRyCMH/vY8Hkf51m2l1aZ5K5zm1i1Yli3ykYpz8Mdc4ZDD7zlrdlQAU3EriGY54q2JOiH+3MotTAH/c35ceKB+/gZvLVwwqSahy391OFTUvQ/59Sbr9RH7NfSqixRMLb/cjnL/isMCm0qRpl3Zf20Bfds4jkZYa/Nrnd5VT8eLtLbf+pfjGzWFmKXzb3ab/t7IghzteCxbaMf92smlD16UobaxemqO1ib200D4lQ3ZlX8wrVG1zceC7UUJu7Hpc6xCnEVJ5mK53c2BTcxII7DtdkPbamhbooFNVKCh9clRLdACbQmVlirncobWkhD/ULL6EO2Yevnn/zpn6vvGQQJjBA6FR9OKGoVei4PaAHn7HmLvUqV/L6i9Q0rMvEk+P+ucGbtSP39jeKg1CwO9tV3KDM69h5PSGo4c8tY8lWIvSH+AHr9Oj7nd/v3hQt+iheHhxqKF9tottQz5OK1v0SJ8XJT0kbUv4+ucLf24U77bOp8YlRGusuZ/f/hx3+Ix4W8J7VCykkC7EdwpgidBnxMZxgOY/XNs5ZJG7+vaTrU2hbPp44zB784y14S41XhXm+yD75ByzzcmL1TRV1qeuoy2wMh2QGqNuquaI9KYQ1PuDy1jKk8pDctjBCYVVchimEt1yK7RWwPf9km7K6sZu6t3K63Y1y5Tu+sQkuGsWG/oGspbAooggtvAijLoeG5jfT+yKHA0lLRzCyGoCHT6A21L80XgpD9w3BvFGXlsiTUcy4+nI9ybPHQtDloP0b7MuI/u+tdRr4qoLqMU6Eg7QwptZ2xecimFIVkXL+WtwkuVggZEhlmltNmlZPXbFBWq5bwlAofESnjWIxCVaTlPdCpRprkGXq0JVOmRfTQwEp94WWHM3ncgqhS7bqwYSWi3i0aT8E23t6aRpw+TZ4HZgPgRT8gHYZd4KFt9Wq9eeC0fiShxTy/NbAHEldXUwgtAbawigQTmWyAw7ZeIArEPkl8LCg6scBL82/sVwL9G4WQ3HYpV0U6aWru5phEzTb0JjxbBffIH7zOX78W9oHvK+24KDFqmiWa5cKyyybS86j52HZwz03qWu1tOX+BVd0AoJN/7O/EvYynP3ga4i1JWiiLgqXA/aHiMQjf7Q973SdIXY0ph/FSIH2dbPuHYd+uaVWrwRlKjvr/rQgNLvZo4lTvEzHE0a5dhoicq76bJNpgzx9PHEfIp/4WZ5yXsHzVPbbeWKv9xDE7fCynZzdE1DiLGl5/9F43UE9fc5SDkufgKU8swZo6jFCw7hSn30tOnTX3BOIfywtOEEqeMg0cJMWU812b5WyXe6L5J8LDaMWfzeSIt473PaQIZ2nP0uqbEIEwpzAl4LvF66qVfT7joteX2diLeXrff8pGPN3kXvRl/0ZsJiTf2jIzvP0GTkh+pl4NjCNodmlD7ttZjTGEXuGoURokpWKgZ4r7x7L5PuZ5G74+Je+lLOEusRKhMfJwlHT64XFyWPRT+cu+nHFoMSVFEeKh6T3dukTeGi+D28j6ZwNvDclx6nZiZh5WwT235qymJvhEOTGgl5BG0SLvjLM1YnkN/eSOgKXWTJ3w4q+WEZNG6HvNBypeSpyqB7gecGH83BxxBXsKNjFqdUq3OK/Tqhx1apl79CJxnFIxxBdKNgrGWL0TLlSlb67JJ7uVElAr46FYnXhf4GuIgOIuzSo3AyQSrhbjbVgSc3G7f4vJwAftnO1XxGSsLFRqBTr0xxQicKuXwNWwELd+7Pn7apHxyFcMxEA6cNtEG7mh2wEiej3gyRaDLZXlSNgJdeYiJcrVVwznrbWde/+JF/iT/fo4nPPAzoGhJyPJJQ2v3bQP/E76Vv4dzxDI+Ngq0y8Lr+0nzgp3RqVNSoEiRP8k6UrqBUuQeUG0SGd61TdTsIsubtgTwso+vxUOTCGoOFIF2Q0fO+KnW3864lRel+Cm1+NSAh67woFJxRD5BSCM2SKRVmOYaWNGIF3BckXsA/kqbjNV4oGWXds3M8DUzF/qP0f6New0QBViHV7GhfVYtos8kEGozkWk/m/iLURnWorLPudmpWHVWwqPY3aqUEVzKEAsLlVFJsatUTRg6SnCZyMsGRLZThC70QpusBKf8LsS+4KsuD1/rq16oDfJVh6F2tSg8gs0+rFOahVZHnpjgq56gHVMV8llv4BBoVqAyRNqtYc85h+Wt51hxsGaPox/18P5uBE/0/8lb8wsLw11QwfLIIYBLbakomBoiwj2+Nb9NhUKzyN8c/iqB8+zjIEO6/kkr9eahCnX6e8L3ibktoCyKmwNHx6PmkUfhkTnSmkJobSDhySx6LCsuvxYc2muIa+CLeMIeWpObCT2mKTSJnZdRRhRWObTlzcXZsfdzG+OLZE+PvUh4F+svY94d9uhMqu0OX6U883J//76rm+NMVmTEsXDc9zc88FRXOsrC4IZhYpbwpyAOA5m/zkOksJjopWX4Hq3CazcyKjqUoA6QWJtBvPmV5/nTK0Bs4dtpvH59BuzmJOIFDvtojDII45qzHqGCEJP0o7ctXztH5DtvM96+6hx0YvJi98kwO2VmH9/fnX3OhM8V2fxzVuqteYDKLI2u5GDUjTvP8zs/RBS0wkTLXPOncFBJrXmGNnaSzgb8BFypir0haUEc2MmtGMH+129b+atRSQMVx0fyZC9nnJSUcY3KeL3O2goObUxphaOZtekArs3bVvUrKo6P/FMKtXQCyulQVTv02lkzDl8ZIwCaXw1ofgXB7QpHSE7u64XofrD5RCEg+U0ffqZc09lZkn1gEF4PekpR8GIqWIWlcDTcewOt0SevSHUwPBHzKnMb2fdEAfueyLQBYiDDGcgUoyy/E5mW3wlxhD1PsDsJY16l1APElqeMZo8SylFLc9p4eNY8ffC0imHzyhRK8Tf15JE/w9MJ9ZQun8fTQfWUIVfgaZd6ypRPTQGvT90xJhmVbqPSY1Smh1jJotConmqJDGfOUHqs41kBY9L/9US3egIrd8wxqmcTPDWqQ/YZb/Lp7nr+xQQarPJh1K3jX9b6YNXI+Ryo2N2gQ650/eXx42UMAGFqy5UGzeBo31ZQ4+FUOYfoTH0jHgCUUkEdz8yEK4w7pxK1NjMDtzfzbTpux/KtB7eX860bt0PpVkYvj7vNQNxlhGGGv5Kf3pMUe5nhwpQMjvvDvmrSaS1iFYxveBltfj+rn08SJn3heSS/0sdCW9q0gUxXQLkpgf4DWCYZvAqoL/dAUZGNztqice0IDg6RlAuUeoUDypHs2cReXZ/n0iSYDs1bWlv5lfLGfOrm77OstaX0VqOPIXpQ3qkyxFJuDN/L3iZd0cfS5etXUqtaRVoRDYPxNWpWSL5wN3y3IBK2MQBxztLR1r56DnqBWGZrtqTE3dzTNH6IIZk3CtPIovxiuXnnaTjp7mJP0o3h9ApHKUGgH/4tRTmTpv3zACs9hYoQlGcbtHbTMdhw6pPEK00olvN2WvxFIsr0wFCpfMAqigsxn0RU5ZbfnTXl1lFJ6mkEb17qs876QUw0p7X9LRHgxU4S/izh8+QLXFv/QDS1lxGvA55bvr3jQl4nLcRxbKRvFILneBoOz6AMsymDEexkJ9vE5zcSnz8tm50zPt8kmuDbTD79B5qhwS3YsQSLmu9SbnZ2N98LaeXv9yN0ePj9Uv545z38dIj1yAJd5XNGjqDVKvtohm4DRNT3pZsTKhzlkA2YT2ab70I3rKlLtMrsKdAm6ywu/2HikwcSwgH0QeyVNZclNK4UkTStkDZiQaGYNtUomCqmzTYKZkenuRkajZh82oxO8zAsGsD36QyJzvmprGnjjYLxYtpEo2BidFoGw6S/+JEmkyHSe5ym3CgoFysUQGBEuIKBBqtAihUMZOqW8T2DkTo2VGZnfAYf2IgVCoBs4nsGIwqaJE2nrZAIkwmxYotKs8VOY2vybcukpXqCuZa4Ht90t9x6LwtyB+E++zRc2NealXOi05xKh4/edtyunN1Hp3tC0oleJXT3fkfzVMaae5TwstFQ25vutgXCf7yzn85eHaVFst3j1d/b6a88ndnPVzrouTfRNrAhopkHfii1kKNLuUQkvQzD3zdF6VNa09ivT3pThmyj7/35tMTXTLnb+koDk/FFGpgfjuCBAVsrh57oMaP5buER950iatgVzc9APITB1JOKG+jGmdYLD/tLck6D4jiFPwdlyb9NPlDR2/+sN+YYBVnR/ExqeEge951mScJBozpb3vxvEAENlU+NyKDWVC0dkUGrJCQnUGuaC8Y4HBlWxIrJYPT0mWMy1CNoZtfA6jHxECFaJlX58adMUQxBXMzxVgY3lEILxope4qDqWSn0bBHNZ76HIX0DtSVamfGggRAstI99+eXaY778SeGF+tJTKZEFoYobMClX/gd0SWWZmO6mIbjP3xSZES10wpqQHfDku/2Fp7zP4JBxgT658IbwlyqcRfb8z1QetKBV5ZStk9TkN3WxJyeDdjstU6rLEX4QUHZ/evnJt/nk8kt59Omh8cTU3FZe0zEiQ987ORpILw7J53tp4velCwcoicMh9hpVNB7FptvF3krFmk/S1zJ5B5bVA13y6rtYj1X+aDhvdHUe8NbdUGLzNJTm0YT/YhiAdu4HxtwuFgzUQsQS9LDqrGy/hw0KOr7DfE8Gj13VJNvxV5cxt883rzz8Zd+cU1oJh6QLdsnOO06b5VvLaUaDnfIn9zAAovflDfSKByPnBqwfJG109Zrljj8Mz1BJ5LAb0B84Als5t09+lWCMKBiXa/r3EndZMMm/l3j+3tgQUTCebtNEA4QIvg3Y/96a32KP7dzD4LRTVlIby3iIXvpSN9h4bw3gSpl8lh7FyEW/HJXxoP8dbTAt2581Y5vHUsRZ/7nwvApnGTO2TxTKW15manGMGFAMH3A4rVQxY+nbSP4Wvnn3GAfONa/wIpR5Kbqw+wsYsU6aJHoKyd/SY8VN+PC1icl9WwHIoXXp+7tKZc4dvBoepEElFmqA/Ca+NUuZoeRtnoa3PxqWIZ0Z7KqNFWepv+DZmcT11ux0WOwaFqVsaOIx6JJhFFtdCGBVJr/RyChkaBl/6piEJyJreEnGnopWw5uiTvs6Og8b6qk7VeuqsT4rBhHqLpZ1VALdOkvL5JLGpBnedRfPsDiSmOD7xzKAOCLbnYn5pcdbx9pDIFegrpldcin9lee9CnUewnq83MsAiDZmt/98Eu707yfc6T9MmDO0m4rJL4Qx+5VOq+uI83BXxp8djscH33U1/fHW4SSntLQctlaE+AzqLONKBCyrzke4S0/5izZShOBGFBb6pxdqw5VgQlEfamzNgAdsn12U+a4v4KnapexlQBSKfLUxvnqbvTE4fAZTjoPNxW6g8LLJ8SHrkk9PVjretMviY3bZdWpTeOSvHPFBQxLZdy1Se5Lxe3HIRugGLTUL3ctcn8JGdDsOt4HOmEtvMeVPhqpD3MyGXED4hiE0wGdyP/DNL9fKffMnEQs+zUONTYl8uZha8IBb3vDPbtpzVdPFAzbYy4PXk4NVQTENIG9pQIG7LzC46wwhz/xBAHcPeOBi9O+5ap4tVPcjWm1Ros/SACYyQYplGXPcsa8pYHQXrYDyVR1qZBYxQk1nGBqQIbl1QA+eSzmGxM/4od0flEtdIihZst8JB5udcDLYNMgYioFoTAEJXOCWYwFz98uXhigSpyn3QLNjLdVjFI41CsfphdmmUeg2Cj1GYaZRmN6cBwmCwygcYxRmGYXjLSazxHPJjKExoiT9UtlDyAtc3OxElr1iyph4xEG9Ot2hTdAjWY5ibZBeTcQ3B0rK/SBf3j4cbEGFWQyX5S1YnenMRM+a/RBh9kxbwDtG7/WE8/TegeGb9d7hT1yv92Y+MVrvHQWhZVZ4oN57uTasYkhsUMWYWFrF6FhKReqc2G20BGITiE1gpNyYERvLUbaGwTQr3ft8Y9T9B7ScwKqVpD1NbxyQzElLaD5HCybQOKRtxTh47J6DRw4ZM8cojjKZqmbqJfrYBLbIqE8SHRQpz82NZb6C9PBgKx51oDc2kAWiH/6aKIqZY8UkMccN5qp0nOsMsa/zXe/PM+akU8Uh90NxqR4o9lJEfcRIg3T/ztYE6Z4klR6uS8/ySR9+CF2FkPyWg2D13L3Nzo2dhHBVjNcztHPjvYVfTZsZuPKSJSboJ7esnhSnn+7Op9315UFxVhYVyJt2Wrz8J7fwNuZASYflb0Gd7pfuwQrGT2j4NrbmlZQ5+pRbDCAuLbe7vJCAAO0Kg6MAy9mTuAB+0SdfBry4G3sm/UvY611izqnSEFz8HpdD3zqNgCxwPcTi4olZ5ZO5qE5Da5fpdjmdDHjmWgV1yr1fZKBBdYtga04LDvamOJsDJ3lhB/b5u7zRJoDFbu/KE8A+A/yLiPo5rKifRZO9tRxvItCas9ffFbmxFOYKBPQbcmDxogelkxY3YcRzN6c6iI7ZHxjsBKlGfx3dAenEodMh/WvyPCDGNwhXLosMdoQHmoGT0fBVZmxKKQ6cqbhv5MB4sY3IIK0zJH9DhYlgi2ilEns+uOIDZB5Pmc/vDaebwZPES1InwmmmmHu8wK/t8666B+OuUJCbETJDzjO5oJLkEwNpNtItIqke0Py8GT7m09qXHhL7cwLtEOBo7eAE5KJU6tXc9JA4yFRGL+aAQS+P6S8AAIkuzeY/D9GfHO2oOOLS2mhXH5XvjoMf6AyHJRV0icJT+hln9e21Byr1Bfqka7Xx0SnnQ1Dn8eAI3011qYpc8pn+FeVRReWVvxueUT6RJpjSHhlDL+Y00Yvx6sVuvBhH9+XZ6sWv8WIM
*/