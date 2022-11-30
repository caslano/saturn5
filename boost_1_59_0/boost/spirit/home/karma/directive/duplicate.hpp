//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SPIRIT_KARMA_DIRECTIVE_DUPLICATE_HPP
#define BOOST_SPIRIT_KARMA_DIRECTIVE_DUPLICATE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/karma/meta_compiler.hpp>
#include <boost/spirit/home/karma/generator.hpp>
#include <boost/spirit/home/karma/domain.hpp>
#include <boost/spirit/home/karma/detail/attributes.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/home/support/assert_msg.hpp>
#include <boost/spirit/home/support/has_semantic_action.hpp>
#include <boost/spirit/home/support/handles_container.hpp>
#include <boost/fusion/include/cons.hpp>
#include <boost/fusion/include/make_cons.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////
    template <>
    struct use_directive<karma::domain, tag::duplicate> // enables duplicate
      : mpl::true_ {};
}}

namespace boost { namespace spirit { namespace karma
{
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using spirit::duplicate;
#endif
    using spirit::duplicate_type;

    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        ///////////////////////////////////////////////////////////////////////
        template <typename T
          , bool IsSequence = fusion::traits::is_sequence<T>::value>
        struct attribute_count
          : fusion::result_of::size<T>
        {};

        template <>
        struct attribute_count<unused_type, false>
          : mpl::int_<0>
        {};

        template <typename T>
        struct attribute_count<T, false>
          : mpl::int_<1>
        {};

        ///////////////////////////////////////////////////////////////////////
        template <typename T
          , bool IsSequence = fusion::traits::is_sequence<T>::value>
        struct first_attribute_of_subject
          : remove_reference<typename fusion::result_of::at_c<T, 0>::type>
        {};

        template <typename T>
        struct first_attribute_of_subject<T, false>
          : mpl::identity<T>
        {};

        template <typename T, typename Context, typename Iterator>
        struct first_attribute_of
          : first_attribute_of_subject<
                typename traits::attribute_of<T, Context, Iterator>::type>
        {};

        ///////////////////////////////////////////////////////////////////////
        template <typename Attribute, typename T, int N>
        struct duplicate_sequence_attribute
        {
            typedef typename fusion::result_of::make_cons<
                reference_wrapper<T const>
              , typename duplicate_sequence_attribute<Attribute, T, N-1>::type
            >::type type;

            static type call(T const& t)
            {
                return fusion::make_cons(boost::cref(t)
                  , duplicate_sequence_attribute<Attribute, T, N-1>::call(t));
            }
        };

        template <typename Attribute, typename T>
        struct duplicate_sequence_attribute<Attribute, T, 1>
        {
            typedef typename fusion::result_of::make_cons<
                reference_wrapper<T const> >::type type;

            static type call(T const& t)
            {
                return fusion::make_cons(boost::cref(t));
            }
        };

        ///////////////////////////////////////////////////////////////////////
        template <typename Attribute, typename T
          , int N = attribute_count<Attribute>::value
          , bool IsSequence = fusion::traits::is_sequence<Attribute>::value>
        struct duplicate_attribute
        {
            BOOST_SPIRIT_ASSERT_MSG(N > 0, invalid_duplication_count, (Attribute));

            typedef typename duplicate_sequence_attribute<Attribute, T, N>::type
                cons_type;
            typedef typename fusion::result_of::as_vector<cons_type>::type type;

            static type call(T const& t)
            {
                return fusion::as_vector(
                    duplicate_sequence_attribute<Attribute, T, N>::call(t));
            }
        };

        template <typename Attribute, typename T>
        struct duplicate_attribute<Attribute, T, 0, false>
        {
            typedef unused_type type;

            static type call(T const&)
            {
                return unused;
            }
        };

        template <typename Attribute, typename T, int N>
        struct duplicate_attribute<Attribute, T, N, false>
        {
            typedef Attribute const& type;

            static type call(T const& t)
            {
                return t;
            }
        };
    }

    template <typename Attribute, typename T>
    inline typename detail::duplicate_attribute<Attribute, T>::type
    duplicate_attribute(T const& t)
    {
        return detail::duplicate_attribute<Attribute, T>::call(t);
    }

    ///////////////////////////////////////////////////////////////////////////
    // duplicate_directive duplicate its attribute for all elements of the
    // subject generator without generating anything itself
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject>
    struct duplicate_directive : unary_generator<duplicate_directive<Subject> >
    {
        typedef Subject subject_type;
        typedef typename subject_type::properties properties;

        duplicate_directive(Subject const& subject)
          : subject(subject) {}

        template <typename Context, typename Iterator = unused_type>
        struct attribute
          : detail::first_attribute_of<Subject, Context, Iterator>
        {};

        template <typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        bool generate(OutputIterator& sink, Context& ctx, Delimiter const& d
          , Attribute const& attr) const
        {
            typedef typename traits::attribute_of<Subject, Context>::type
                subject_attr_type;
            return subject.generate(sink, ctx, d
              , duplicate_attribute<subject_attr_type>(attr));
        }

        template <typename Context>
        info what(Context& context) const
        {
            return info("duplicate", subject.what(context));
        }

        Subject subject;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Generator generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Modifiers>
    struct make_directive<tag::duplicate, Subject, Modifiers>
    {
        typedef duplicate_directive<Subject> result_type;
        result_type operator()(unused_type, Subject const& subject
          , unused_type) const
        {
            return result_type(subject);
        }
    };
}}}

namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject>
    struct has_semantic_action<karma::duplicate_directive<Subject> >
      : unary_has_semantic_action<Subject> {};

    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Attribute, typename Context
        , typename Iterator>
    struct handles_container<karma::duplicate_directive<Subject>, Attribute
        , Context, Iterator>
      : unary_handles_container<Subject, Attribute, Context, Iterator> {};
}}}

#endif

/* duplicate.hpp
NbgGPXU0k+ttZ33npx/L7ssa/wKkOwkshKk3fTyqMx3Hciy5Np7lOC573lzrbWY127wq6vlfn415k8VxZSDOcMd//feJSf0xFs91LVg84vBSweFp67EAQ6etwaTQaZtyu7YCM521ArRGMEN7Dn81SW0cLztvmiQ8Iv1uUuWbFY2c+5jMvRp/teeQ5nmv7DzK1Mi5J6vyzV5a7c4KaMTTSn9S/nlZrns448oL3kVLfz3rpjrAMT7Xpn8/a9e/QR6WdkMYEj8xDWexc58fh1dZkEWF4k9UcUsOal/PrZniyJpiUwZoU+xZVmfFBayb/z3fWg/qjTDgCtAjJnT8ixO7Ndb5JgzHqbovs9AgAL2douhgpy49M8bX5juOlncb1aznp84WPkb6vlZVJPxAq+zcgM6+rbrlf2tVr9BaoOLVeVZtf/0ovlV2blWv8fQtvWP2NB40lCHxU++sYDzxfe1cTKW1hr7N3IKvbWdq1tupb2dyHI7D5duqerzFp4z2s09lMeqgnHIEqxV3fa3rlSfoQ7fZCo0PnWJc1mlU4v3o/7TWbNkcA2FWkKWBx+HMiQFvxFe6RIWHxe+IK5BMAn85gjeSaJYnjizzdliqGn9jHnIUFCDUnLiwP81/ju3AXu3JjMEcKiWs4kZ/CjCYXQ2xwXILJUyqrq62mFpPy2tSYF1yW7sZvkeqvoVXj6XtX7xVQq2B+x3OdC1lCr3MlDbxqHG2q2wHdh3UO6CWSjybPkwybLXLkRs2V3vlbULsFtXsDW3k6oykpNgtTPsNB4x8xKMNzj4RquLanM/sLdRn22LyqrNzJPyvORLPzZF9Qqtxr8VLzvm/VpH0v+awnpPDNJiTLsuLK3LgIWPlcnjrH5OAlGc5ZSmnbOCUxznlTkpZvh+TUFS8nFNmLzfDuQeKq664lTD1y08YxtbrxJ8/aNc3guPAHuML73ZZOUrNBtOIYpV48QCgd4N0KWDY6q4Su49AGoOxj64qZY0YCHJ9tQ2xVZ7LpN/iDMshqeOkrIHLaDvebM+gX1/B7CL+TPFG8DyS4VgnORI/0W7fxBYR1fvWUey5q8SbR/gv773vHDH33nViIvVCFD4BVmtC1UJ0ce9qo4u7xERatdknwkSgL+gVH9ShN9V9elMv2g6bvelrz35MeOjLkiUz+tUte0E7rzQ3OWaY+ecLOWRs8wR3UsD0VMG3H8SWe3gFd53XPAyito9LZA4zvx428q2HzQ7tEo3UOfGr1ehQsOq36FB7mP0H5R8SH32gc38OoT9FR6FgogwJ6IXFFTfQyvtlGeHE/QQQhYFE5P7XB8gQ/Kww7F3mk0nLuEzwkK5UiO1M7DZ69gbfoYGNF/HBhcBLtRjvXUw/P1+LjmDICtku+bgPDd3+PpHbfP+a+OP7YN0aUYNSLRLQ8W61bBONSKx5J0qpeax08D3DvVUc4uZsoeQR0SJbqAh4YarzT/S65SgjdExC/MREJ2TrWRNizFtNlneNuqCRhcwlVthu7GZorM3yPiOjiOKkIFGrz8pv9OSvKbVq+Wvo5R6P9xm69z7jOVh+sWdv+Qgw48VAi4WF4bJdfoJjnfgravqgEYiuuoV7v1VY6zEWm4yx+ObI/wEI5DD/+xCG/DUAxIlDJkAcohp0XTywKurbuaAw4NRTnwEAi3ZAL46k7i0K5IkdY/nItQrDG3DdrSbPK7pbzSWE27uBEa44TtmLxHuULbtrvqr0hs7YS5NCZxyll2JzCCQU6Q8RCFgAAvxM+y2LIsZgpXp7c0NnUkoPItpnwFd1EKDp16CtKB5P7NJFZy6TtKNEhG60OjG4uEN/G4YrlTXBQdldRQWIdXgTJXKg9zfRyLAGbKUSAPlasLfVEweMeCl9GVicQvEEG+/O8VQwJQPQ3VRg5JAWeTI2pyk6KQpr2ObEqmG0/4VwW2whGrPYPjrHVyjf6WswO2ykKE5e8o2uPY1UaCpdOgDyyqIiGqCi4v43ot1yz8T2J2uTKap3l75mVwICNI71ERtiVtyU8AP5LtXb3tXPzhlICvTHZTT5x3fJIDDG4/xE6oEloN9bbQ3oRcX6YyBh5KsRE8zOEfbbVGDWuYm3q2aC0PBUe/8imI81gX3gnNFcY5ELkZAbs7zNWZAFEMQPC1X3o+Y1ZHnrwxrvPlgERcJG0yjHpygwNFSn+2AGDpscc2QA2TQvaiiIToNPf5NJqzcXp2MK4wyZ46ewusDIFz+FpliAzXyrXNBM3wViQVW21Xq3ph8Y6grthBjCTgD9WP9w2VZxrJeoox/7/WENE1RcMT3FJU49cVo3Eqg8aAhR8rNoklhB90Y1jyWFvVv5xP1pvCK8sosawfswQAVp+lM+GwZZln3rF6eNxbrVaJC47lVaym8Cnor0N6sZancZYSGpCmzaYsImmiyNEVRoNH53Aill1ViTAzbpdDLZWqPKV6ExeFVrDWFnNV/zg7VW5ZfhELZvrZtYYegTSh3fXVr+a+GdKxPhA5k9RheDttosnryTPQ2I9JXYZfKqXLfRUi56HLsMXH1iZTorShMYjF7DVtNZB8zEW6f4dc25m0G1eIW3i3pxH71FupXT68WTlG74smlWy5oMOoDxsq+AsCXsWPTUoNyNm8S177VD54E3jV9jB3h5KaF9KWFohsual9/DLtH6/Tu2+p5JgzD1AafDx2Dtzh+VToj3SbID+pV9Cu8TM1HYK86uc/x7xtFbitTbq2BzmFS7VHpLRaNfJzLJB7rWRYlUfmC09UKhwqkOBKXOhyWMlYZAXPgKDxUGT3Tsjw3sl/uj6L+BRk0EVmB2dJq1lahrHdVVVfnrQa69gfSqRzBjD1Qaom5iAYqTCC2JZ5rOgD7g2CU0b7XJh14k0P9ieIf+ruMBWFbgRXg1FjJ/so7eqLvxGF69QSYmijc5cQNPP5P0aLh4/ktpA8YDr67nfXc9k0PrXfybwr9p/JsOiGTmAPOrrs/g1Ez+Hc2/gFnx/LLTcMo1mLMlieIKOBZo8NWuQNIzv01xyWnuc/jYqBHyWsHLxutSV6MFbH3r3OH9j7oCC1jbL66uNJTTDFHEr5/viYoiDl0RE0VUzdkY5Y+K/MUNc1NdlPvRFYDwMa9wlK8EHzGorO0BsJgA68DitUWpMA8ppHxS/WMsm7whuhfoXcpOWR1Af7kZ2dXqQ3fm3BZn7y39cfyIsNroVyQnKD98WCRyhan4MoGc6M3s0EOL77SE7s4wjfxw6F6cc9FQ5C4O8n47TFfStGR4MTgMfwSKQ19zH80d9c8waIwvM+4Hyyz5wTKWHyxT8oNlDj2EMkoSbQ0IepyOgmkomGKWLZVlDc8I8WXXcNlgf6lgFpT5aK58L0UV9vLtoZpDQlS2x5zKGGk3rohLA3+cD3s/vCnjN6YeCrFgXkdlXRB2q5dMDzqmKxdsSSAypTonMnRLYjApkDgv0n+LLWgL2CLfwNLDbgnkVK3Dsvvpr/goR/vYaDAcITU+yP2F0eEnLKZNQY8ld66vWUZJk2jlLXNWYtM/R2UhprCwUewZLg0KWUN8s88Hyea7uo7jsLJD5nljijYeB4188EilEdW0guVNSgobmbs4TSlFvBJvU9l5td5DFh0hoDxeUdqPnhJ0rJ8Uj7e5LNm53XsoMsjjbS114HYg2G9I5Km2OjFt8SkiKbOrfZ624BBdOaQRGNQhhNEWyhVxavl12mDWX3gKMbZhHUDNdJcdUvLdj452VrRCtTt/mxjxN0NV3KI/lImEDX+DUWGKZkUf8rfRMBWg4oO6b46hyqA+Olp8u0/XW7ZAYz112e9xinFI9e7zFI4OOtQpY7SBrVAPmjE2a8oYz5SxS68JJFR2BV1a8mzZxDXcxEFoIq0xIwo4PJ9MGbOxDSWnjKU2Kv2Rm+PN36l5D6lTRhNghJocEx1Kvyra5JdFHF1eh72Kyi5TEnKEWCZDqo2u+gDAkLHMONcT4fxGcfAWwhwLHGxCc8JZAXYlVJZukQqamrWw1uugqVzGLKjPFi5v84v/Lsf+0qpeJAZeTDRVN80KnwunsfegZulhQuptCi33ECTZs+jX5dd9xSocP5dMApOwa6+uww99/iHG4ZP3YXjNAvkoUOBHQd8ccI98gpsgfkuFtLnp+jWwHGnuxRQ5LGqinIBGMR50vNcRuUjLbxVzr6LtR19D24/5ehi9rvJb+i0T1Y/RmKRhTHoxJo7H4sdkxywpxYbHYeXC3Shg1nDMyye4y1E8xUKjUOu1m+Mjzlwkh8PFw5HyPw+HA8MBRqjkBozGn/dgNPSlbeZ4/Hjv2ePhMMZjHj1pDfzFVXswHGn6NYXi+GmdA9SpidSRFrjQwhgUjKEeO54y7VNDrWmsbOXnnnaL9/N5KsXUi+BWTGgNtbmdWLniIm4OTTcCqguxCd/JPVTI37/TL/7zGDZ+IRx7sFi6xTtTocqQXX0btgwa1Mtvp0HdUWYOamj/IQzeonxzXB0EYN0AsLL0St1Z8V8gAgSMjI5lbe5obserI9Ew6q4I1/AAKQ5zgFxo09mgF1MZFkBnJiAVwqJinjZ8tk8gQh/edsMlTPJsP+WQrxfjHNWmdUcu1ZIr9eD50CJE6Wa/fH87oYr+2XokmZ/uDO3PLBJflAPe0jHuANIJPCmnqk13fI1i0xRksEuA3HclTcaap+MAsnKKCZBXl0mAtFV9/lMcT5SaihEf3NLOihHNL7EN8e30J2CDYkR5hlqeaY7TRURquSd1whfWTUQIvES79IDiasq7M+/Foa5CYt6vKd5Aj4UvAV3zYwk/tvLjS8AutUkoT1iDWiFyFAb0taXwJZdCWKVqHub0Ftmut5oJ2mSbOMIV+s0hxGEiLupOEQ6E0rVYfBXMy8MC7kfPf+mkrr3VdBoGLtm6vxiC0nC49TQcqsCY26r7HFBgDFcizReYUuzblOIqTnuHSNFK1FDcuwsChPsmERTtS4tkfE+OZs5xM+dI8fu1d5DqF38LELjeImPL3/QyNcM0Fq+a9CyWBnfHUIRQafGLfY/G2+j2xhkj52TE0WK2zXD2k4FfmrjDGKAnfhlV5pi6GYbJrYlsmMzsW+VtIDJLJIFqE2JjNxGTNpNe/ZgfETGKG/oeP6bLxwSxkx+hBbIfAsXX6NFo8fSBNLpf/1J6iaaOnRT3DIVz/1LmW5aBbL01uVOPhbMIr0A1vuKPc7D/2sWn90Iuiy/5ij8x0t67F5JZRLUqKj5hpC29zwh1YXb2948YnQ1MIJKwBTS/OsR0iI5vyEEQQx1Ezpc+CHIeqXG96hkAyh2PcT1v5sQ1nBgdnSOciMe4EfwrJ5ZwYqtMTBL/mc+ybkTggI6BuqKUfzEQ6uqVktyufqTvyd+kuCleMPLs+FpGoElj3N5thqS6UPwhEBs2kYOTsWc5ZQ2nfMkpIU5Bq33FLZzyAKeUcMq/OGURp7Ryyj85JT+AwUezi+g744shEo8LTMXxE7NPFBZqJ4tXgnbbDiZCP14ItuJ6OTzqep743UXw9sijKN6Q92y88rK8R3/Eb+iefRX5il+Iq02OmAwrgHH0yYrFvZTdAKtAUif8eHHtc2LJhTKZPzQpmgw7gRJZD392FN7IbyxLGUDdhm00+iy2uLjDe+N6CzblrN5y0MjgTAR1/KFmS3OMYEahhA7x41uldAwCNJny658RwWUPELVWTSzvIu3wwttanjcV1wsK/FpP+HFkzD6gers9NcE73HkZwQW0h45HqwoKdmoJCD6xA99WaTkSDVs+kTkq2Sh+oX/k8dqDw3VvL0feMRPd3t7SY5FBcBmRTxPXK74rJsbhtkVRS4kCQ9dbO3l3qHu0s/JpGrYqQAi8jjgrce5eGDc+Z40OcdMYoEVnDxBRKByaDoMjR4GG6HztIj7go1Y4aPngqOvpDHoVySgUp+cxmTwskGCO2hxqaHTMbmNvHMAPa8Z16OyNxXQl+yslwVK8ClN65IKzXckm+8Rb2BauXSodMuhAKAVKFHt2vkzM9OpN1Ei4/jI8O1RuIOTNfD8liof5aa3x9DN6MoDuyuEJBgJiXHlqXRRXjiAKQ+xV5CcvWUCf/DRofFJbbUdNoE+otgu5Nthsicmx4n/78htdVCi8J1LmKh9qWMc1IBQvIM9ZAWunonC4Cfagoy5IMHBw2CvYr/iga2i1y5fDvv6GTVjYnbvmFaHqNp+Y/Vv68DzXfHVBqyxYyIhSFMSvI7DLNGs/NlP8RjREDLDnSPD8QlGF/N624gQbIv6y0jWs9v0GvPSBFUT4/lU8HiFYWhYADCzz0/esb2fc6W3zFf8mHpDkat/jY29PFlfQBfF7mwEjY++WgYHbilf0+RRSno+v5bC4jOAgPKNN/GH9ScOZKw/PrfgZHozfiY/FxUncnhbn5g12eVXLMRuDHoI9od+wx32JXvB2JB83/dcY8T+D+PQ284g3vWCOuNCO8GBXXsF2dP0DORLGI7+U670QgSFXPivNhD5Sva00B4uio2Usa11pjQ2VkSYH5gkemOF39RkYM0dsYIwU7YgY+K0cmNW/MweGezEZoRfOPAggdlSdf3KwS5z/ILsSeqPlGw4JDXStjPXLLVX8lSbIvL9P3jPGXizvecXMofuNW6lnnlolGHewnzUU1nFrfzvUJQ7cgZiaMNbF+utaBjBPJDbGQOdDqAYZaN7vLwZWNCb4Q8KIwygpDgo+pDm/poftUsV16AaEmLVy4RgW6Z7P2J8BJ/8YJR/KEAeHSH9qQ+m5+PZLh7u0g2LYHZBiOCvZCJk3d9FvNDXkoNYtzlzeoXu6DS8gHKSz1YplI5UvQzsdtOlYnJV70Podlxihrx9ae9LQYGqDAtfiH/Ey4pjSV74rbuAj6oultMfPBY4S9BhqUloNKv8V1Udz2XcNscVLYfz6IegxTPYOisfy+yyhVmMJ/fcOs+HA1b7Yi+E+UDjRyNq/IJRB014mnJVvEHy0TASQLLqoXT8UcFX9AYui5xdsZPvBxdzLVhF+/qS+u416k32iCNLyxzIgxA4OKuK3Oo0BzPjEhVSHprQWBojVWb6IiOru5KA9PKuN1VhEZfI3ODQb1+8bfeOGVHh2vZBwextCwAPZyciHbb63n6F3It3xjV4oFe7ETFlQpYLuBW3KUWNxFaoL2uL3U95Mp8iFEb+ZYm8nrk9SJZWwncxvBlLE7OvetrP22LbSd4j3wjDl/eakLmp/IcPcHP2Uls0XP4/H3MESsTXDAIP7njtpoFt0AXi7aEyHLtbI961iJr3n4ButxV/TMPoYbXTd30l8h8OvlbUGMv3iloU8YsqgGN5GE4kREe8Q0BiB79+gW/Fjs1WYrJmyVSfcTMI5Kz7FYLdnQrbgOa0MNJFSy36kn7nIaNFfn421uNWHSd2URS3+VL5vE795Fi1upe4U/zfa4qmyxTTB1BmxfoFs8K0S4Rfq41cB1z2cEYsSH4cTxxUW9qU+z9pECvsgflryN8KqW3b6nbXoP8/KG2vR/5/LHdmzEP2/P56rwJoT2cl9uQoQB+w6sZZJ8t6HhrrimIqQM0EyEp+PROeZQhC/eeYkfGFaxSGZyCdalTLRJnbIRJAbYgklsus7WZJ5ikMEO8Q2qPebuxEo057wi8jAeWkVb0EexV7ZFbwmVJ5hUQaGc8cAh7ie
*/