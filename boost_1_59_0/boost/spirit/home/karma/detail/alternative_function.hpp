//  Copyright (c) 2001-2011 Hartmut Kaiser
//  Copyright (c) 2001-2011 Joel de Guzman
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SPIRIT_KARMA_DETAIL_ALTERNATIVE_FUNCTION_HPP
#define BOOST_SPIRIT_KARMA_DETAIL_ALTERNATIVE_FUNCTION_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/karma/domain.hpp>
#include <boost/spirit/home/karma/directive/buffer.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/utree/utree_traits_fwd.hpp>
#include <boost/spirit/home/karma/detail/attributes.hpp>
#include <boost/spirit/home/support/detail/hold_any.hpp>
#include <boost/spirit/home/karma/detail/output_iterator.hpp>
#include <boost/spirit/home/support/container.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/variant.hpp>
#include <boost/detail/workaround.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace karma { namespace detail
{
    ///////////////////////////////////////////////////////////////////////////
    //  execute a generator if the given Attribute type is compatible
    ///////////////////////////////////////////////////////////////////////////

    //  this gets instantiated if the Attribute type is _not_ compatible with
    //  the generator
    template <typename Component, typename Attribute, typename Expected
      , typename Enable = void>
    struct alternative_generate
    {
        template <typename OutputIterator, typename Context, typename Delimiter>
        static bool
        call(Component const&, OutputIterator&, Context&, Delimiter const&
          , Attribute const&, bool& failed)
        {
            failed = true;
            return false;
        }
    };

    template <typename Component>
    struct alternative_generate<Component, unused_type, unused_type>
    {
        template <typename OutputIterator, typename Context, typename Delimiter>
        static bool
        call(Component const& component, OutputIterator& sink, Context& ctx
          , Delimiter const& d, unused_type, bool&)
        {
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1600))
            (void)component; // suppresses warning: C4100: 'component' : unreferenced formal parameter
#endif
            // return true if any of the generators succeed
            return component.generate(sink, ctx, d, unused);
        }
    };

    //  this gets instantiated if there is no Attribute given for the
    //  alternative generator
    template <typename Component, typename Expected>
    struct alternative_generate<Component, unused_type, Expected>
      : alternative_generate<Component, unused_type, unused_type> {};

    //  this gets instantiated if the generator does not expect to receive an
    //  Attribute (the generator is self contained).
    template <typename Component, typename Attribute>
    struct alternative_generate<Component, Attribute, unused_type>
      : alternative_generate<Component, unused_type, unused_type> {};

    //  this gets instantiated if the Attribute type is compatible to the
    //  generator
    template <typename Component, typename Attribute, typename Expected>
    struct alternative_generate<Component, Attribute, Expected
      , typename enable_if<
            traits::compute_compatible_component<Expected, Attribute, karma::domain> >::type>
    {
        template <typename OutputIterator, typename Context, typename Delimiter>
        static bool
        call(Component const& component, OutputIterator& sink
          , Context& ctx, Delimiter const& d, Attribute const& attr, bool&)
        {
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1600))
            (void)component; // suppresses warning: C4100: 'component' : unreferenced formal parameter
#endif
            return call(component, sink, ctx, d, attr
              , spirit::traits::not_is_variant_or_variant_in_optional<Attribute, karma::domain>());
        }

        template <typename OutputIterator, typename Context, typename Delimiter>
        static bool
        call(Component const& component, OutputIterator& sink
          , Context& ctx, Delimiter const& d, Attribute const& attr, mpl::true_)
        {
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1600))
            (void)component; // suppresses warning: C4100: 'component' : unreferenced formal parameter
#endif
            return component.generate(sink, ctx, d, attr);
        }

        template <typename OutputIterator, typename Context, typename Delimiter>
        static bool
        call(Component const& component, OutputIterator& sink
          , Context& ctx, Delimiter const& d, Attribute const& attr, mpl::false_)
        {
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1600))
            (void)component; // suppresses warning: C4100: 'component' : unreferenced formal parameter
#endif
            typedef
                traits::compute_compatible_component<Expected, Attribute, domain>
            component_type;

            // if we got passed an empty optional, just fail generation
            if (!traits::has_optional_value(attr))
                return false;

            // make sure, the content of the passed variant matches our
            // expectations
            typename traits::optional_attribute<Attribute>::type attr_ = 
                traits::optional_value(attr);
            if (!component_type::is_compatible(spirit::traits::which(attr_)))
                return false;

            // returns true if any of the generators succeed
            typedef typename component_type::compatible_type compatible_type;
            return component.generate(sink, ctx, d
              , boost::get<compatible_type>(attr_));
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    //  alternative_generate_function: a functor supplied to fusion::any which
    //  will be executed for every generator in a given alternative generator
    //  expression
    ///////////////////////////////////////////////////////////////////////////
    template <typename OutputIterator, typename Context, typename Delimiter,
        typename Attribute, typename Strict>
    struct alternative_generate_function
    {
        alternative_generate_function(OutputIterator& sink_, Context& ctx_
              , Delimiter const& d, Attribute const& attr_)
          : sink(sink_), ctx(ctx_), delim(d), attr(attr_) {}

        template <typename Component>
        bool operator()(Component const& component)
        {
            typedef
                typename traits::attribute_of<Component, Context>::type
            expected_type;
            typedef
                alternative_generate<Component, Attribute, expected_type>
            generate;

            // wrap the given output iterator avoid output as long as one
            // component fails
            detail::enable_buffering<OutputIterator> buffering(sink);
            bool r = false;
            bool failed = false;    // will be ignored
            {
                detail::disable_counting<OutputIterator> nocounting(sink);
                r = generate::call(component, sink, ctx, delim, attr, failed);
            }
            if (r) 
                buffering.buffer_copy();
            return r;
        }

        // avoid double buffering
        template <typename Component>
        bool operator()(buffer_directive<Component> const& component)
        {
            typedef typename 
                traits::attribute_of<Component, Context>::type
            expected_type;
            typedef alternative_generate<
                buffer_directive<Component>, Attribute, expected_type>
            generate;

            bool failed = false;    // will be ignored
            return generate::call(component, sink, ctx, delim, attr, failed);
        }

        OutputIterator& sink;
        Context& ctx;
        Delimiter const& delim;
        Attribute const& attr;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(alternative_generate_function& operator= (alternative_generate_function const&))
    };

    // specialization for strict alternatives
    template <typename OutputIterator, typename Context, typename Delimiter,
        typename Attribute>
    struct alternative_generate_function<
        OutputIterator, Context, Delimiter, Attribute, mpl::true_>
    {
        alternative_generate_function(OutputIterator& sink_, Context& ctx_
              , Delimiter const& d, Attribute const& attr_)
          : sink(sink_), ctx(ctx_), delim(d), attr(attr_), failed(false) {}

        template <typename Component>
        bool operator()(Component const& component)
        {
            typedef
                typename traits::attribute_of<Component, Context>::type
            expected_type;
            typedef
                alternative_generate<Component, Attribute, expected_type>
            generate;

            if (failed)
                return false;     // give up when already failed

            // wrap the given output iterator avoid output as long as one
            // component fails
            detail::enable_buffering<OutputIterator> buffering(sink);
            bool r = false;
            {
                detail::disable_counting<OutputIterator> nocounting(sink);
                r = generate::call(component, sink, ctx, delim, attr, failed);
            }
            if (r && !failed) 
            {
                buffering.buffer_copy();
                return true;
            }
            return false;
        }

        OutputIterator& sink;
        Context& ctx;
        Delimiter const& delim;
        Attribute const& attr;
        bool failed;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(alternative_generate_function& operator= (alternative_generate_function const&))
    };
}}}}

#endif

/* alternative_function.hpp
XmSqF+vxAkutPF29EHgxFS/c6sV38QIYqbx3H7/4xpg4It99a3wUt93KtGYHdKYaxtwyKkMdzchZf2CjvYJFuQeMgnBz2iHaF8bMyuYCxBF2CPuAieOpfio9e/uwPMs3UgEym4jeBx+krEk7MGh9+2tPf77GmDIxmWc/lkY8O4g+edWWC3n2VPkVsOx1A/oFj0W7ZGxfX3z3X70lSRSwqOElbNG/pNkGr8EMI7iGuoTo5ulGsMYIrvQFs7TLfcEx4cye/LEOR4ojPDj37XvFW/haslJfUgjVZWW0iRs+iQ0/LCelA/qzCiKRHhC5QgtRBDazo/DJVmDMTTh+OXOsd0pez4kidnNw1JIIAZRnammmtjkUc9MS3aSERWyqX7JGD5xMjWpHlaFt7oF6/zFvTQuk5dPd4VSRPwn6aRP9Td5V27hiQjb3h8Tjs43gekPbqN0kIkexp5vZtYAoOX6s19WMSD97UqNVd6QYgc1GySojcjL2TdpqOfuFdjxnPyc8Sgn3G4FVItAeneoZBOVj2kH546OIGaMcRNxChZTD0YdRslmETtHrslkhk2g2bSM63JbTlBM4LoLrubxVVB4UDk7SuLj+bQTWUuugq7reKFkX1daq7lWkVKREA4314i6MS8h8T+Qvyu32bV1PLGV4uk8b462BmrBPy/LWQmppaluiwfXy9XHnzQqztMIkyFpRYp2TsUeQ4Pp6eei285Yd5Hq5iVLmdsce8C0uDE+SSwepiVsfnzgR2OjT1mtu//7w5da8red5u+9Yb2GRck3xHq30MXynbaHNFH6zz/QtTpoLMX1sOVS0SktLlxMp63YUieAagu2Bla7AKvpT4wpsRl454cU+M1aM9TaT+ulbyb3Mp0WonEFYnXv/RnSOKFjzwq5Zool6+feJiR7uoeS5B7CSZ1LJ2kBeyS5HOE/kj/0Fr+lUvB/wCwjnwwPlkoE9ZoUzNkA+jpuU+DEj6ihGDyHYxFjjuDLLW8PObPPH+wgACSz203fUvMFzMSacWpEyL5Zu1+TK7S7ge9rb0xeFM/Q3WtMpYfjal5ZpozJiaWI5TvqI7NeusT8NeKkBn4bJf3g4NHMx5oNVN4Jb2NBxgr6kykF8dTgTb5wVw6Il7bPMxaeKzVA5kUixjGK56SYiUxdlGNoaTtLsHptB4IPTPXGKhgrKtaWUHGxLC6FK+ZCL0EW2gj9654QLD2+1DEiG07DqC9wcN6ZMRNLFCdqr3lpIs8pPfgSqt1V+dwLVHFA7mlDcjj4OfygQmNsISPkQ8PLQnKAE+OoE2x2k9kDV3OHLzyLOJX+8GMX7CGaQSQcNp0SpW9wuzuREOqNTUwZh7xz291SliCOiOKzvcfuPLfWId/nNe7mN/vPeDY1GflUHhzCc6bbqYgcPqOceqscMnLpUVdTKaP54u/3nzqH90l/ojsCveU6gy1/gXtok0tjjwynxhDs6GwChNyfYJc77P6Xqz0BhvLk6FW75BxnaSXrpMoInm/MViqBxDJ4kotM6uDMyHpID2nB0l+Fo2PyPETai+estfSaB8X/YEcdx1/HW+D5F2/ULcIMpUuEc/8On6RVmPXWiwgQ7QxXXW4C1G1uVEp40NUlb9cAO2qqXXK8ynMYLzz6jVsfsvPahLGwnHShnpPF2GaJHxjjC18i70vptGutsXsY3TfyoctQH6K+12kplKldXces8hDZqQfimZztxeNACRDgBTr0RzsjGhX8w3Y5yaCjI4fUX48I3Ydj4XUd/XEhDJ5/JSeDCEfUXUMKUzHxiYfm6LxAqfqrrNMeqZXY9wOLJkfpd67JHIZxVRQoE/7d/9bwZuzHpzG/9xrhm551W9nATJez2nwUVoSJ4ZzZ8BKSbSu2nvVNraoOITDtCTwiQcXgrSzrS5dM3KOF5xbg5C4zA38E5RoPt+wNyoBz1FI5J0tUzEUxf+S4NwvMqY5csugGkMNjN8hfvdjiUUO3cZz0QfoiCU3kVKSFZchvo1Uxj2ljq3zhs/oMEKGByjBId8lAlZoldxP/uJnCcHQ/hUJXw76afDc/Qv57uQJ4fcJ6C2IEGaIjRQBcry2uwhatPAljrqzFBZlluI3wFs8Ta4EC2xICaRh0EEdG6ffQbMnZDacnYDRfkzXUepzolba7rdAA84wukEsrm2tjNBpWrG1H2O9G64w62v9ZXQ7XVNHZncMoJ/JvJv6wBubuP8zr4fiz//v9oex/4Jqvrfzxp0hIgkAAFqlStioqWKVpUssAEIQWFYEptA8OC29BPl7kNRx7ESQqYFnl2CTKHDjfmcAPHHNvYBK0TsfwZLYJQlGmRot3G9HbpZyvalgLV53fe5z5PkoLb9/d9vX4/5abPn/vcv+eee865588o/h3Nv2P5dxz/tnPOfL6Gds38eXN70XM1rQb2kzX4MnopQZ3qmgpSoiL1stFnBmRBqeo0fS1t7xump2bzNGgesU4dJ9gxVymNII5qw4ldGJWw8U5NKpBZOlBbIWJ4Yoho1ypeouXTT3RAahigQJ1Wv5s/d16a7VUhLKqiWl8Z5wppmddN9FUt0f4HWgu+qoei83x8IprYhdLC0ZGpo+PAha0YS82eQKUkh6fyXNRSL3qdgzE7rNTyMmT68O0P5QFzFBaL4mk41/4OXUfESsxYqXgO0xdGIRNQIhUEzlpBjPEePddXIgc4P7P77/n5m/k6lzBXy/YFemg3SSu6zISiWl/WkoXRf+84Ad9+n0flil7zM8gq2+rmlaoQ9FYg9hoVNYOKSvaFGaEcd9Iw0r3kAI/AKmOUGuXVbbRmTsyZ498bHYzv0ScoPSxsBVz6ngOMeqoF/foq3JozUpDMinjFrQhjf1yqMPaz1Q5GC1xMc4bFOD2G6I/+T6PO43XJrOO7j+8xQ9w/Ni798P1g98ns7u2Dvc27jx+Qb31KYNmNtyffTzpPHj9+4P1gzwe75Q48b8CTk01AuuMI6c5PPoSmuMQzWMtEqTyDpe1/J9YvJfWaLmaO9R+MDvY9i5mp6gcwH/Vmli15k5g5ml68qwpY4crmAlb0OOAFMfYGwXGF27MORKNLtvbhI00VKMgUqxS9PQuWm/ZZKigmjDazP+syTOUyaBeIqiU1RtSbAUjO+INLbPJVA/ok5Wp0nxpDKESvWtJb2+M/fhvr9e24i76Nt43O3HTdKkJaiMB5WCJwKqQjBDOwCeEFhz7ZqU926ZPdvsApra8vID3V11GB0JvSYy1pFbjB0PUmCtUbHSQCp0BlN4rigqPnCvcks0WfeF0/HWEr8bx85NHuwkbe00uderAtFQLUFFgx6PJxZKCZuvR1Asln3mPsEvYVVwJlLNCCpnqUnbUI7xBac3z/QxcHu4u1CK2JMlwOYiV0f2GI6K9uxPt5U2nNEbXToE93ZhYWHR6vqkTU+6oFNq2/KB5JA9DKAmXOtFVlukJMdTumOk1mQj6rmEAurBVOJ4HggL89NT/FSiheYPrLPywPvssr1Jsq4Gh36y9t0JWttEWvFVNdjj5mqaf45dGzVGr/jNzUHqXll+loiSg6By2nmfmmc7KY5iseWeXJaOXRs0knPa8wW6vampzpK743OtoX8GqXiGFEKh7j+O4LhacweErYElPsTpq24pGFARmXBAfO5GXIm/cfm+lAxN3JLjHZ6QhIAhqmlMRe0ErJo6CVzGCY8bY8cye68QNrNzGH1lPPI4fds7UMSLTohP4cnvjmVXpq7uQLGk4fT0m4NBHsNi2W2V46EZTq1jfvPuU83zfvfk/Nb9ScmNgJfJiYkImSIgVzCAz95y9GQZPTDwn/EAZsPmDioT3H35SBfztt8ChDeU6eSLpOvn/8wPE3KR344E3CRtf9OwMbseccBKwaqHzn+BuW8TkKbWDUcF9FN6H6ip7oSP/eZJ7ZYeuZ11chtf6+ijYtR5EFPn4fddcH2rOxUGIdycsi2bPDocQakCTyjiN8sDQ84jBxLWwp2zEwa5vsvKemFOyIhjWIPnf+e4g3RQaszCAD2BmfonT0lXX8u49/G/j3EP828u8x/m3iX/bYsbLFBhIILDi7iFgJSwd95Qz+nca/sNuCvyVElmLblpX38vP7+fc+/oVnXjkfXreJgajEF7XOG4kA/d8Op5L6GIvGKPfRaota/g+QdXPm6DUtsCbfH/22mLZET7Cv6elL9GlL4BPzdOL1bZYr2bN8HJ12kULEp+Y1dhxS7/VEE76EZutS8TpfK7/VCRSf2GEWo09asrmVdYUEoMx/2FP9DqZKc9NijzPRxp/599MscmPoVWqD7AWNs/WaZnbGyRXwtXAhjpvyrV6DNvg/vxhWi9MP3+esGTvmT9sIUtklOzKldk3uG4HqUn6NGwWuvkVL1DlbInEKnEj1cz2Qw2Q0ebbxUgF3Cs0zdrA39YsbDHNuVYRyLSqv29RjlBs7mjhjHX+KRqk8Ien8To9hyVki9nJCErnqlWHNiDzyRI/5achsnDds+sRStyLWY7Syx19HxDEfB4JQZSE4GETb75ojXcavbbaJxCFGhswXDDY0JepIc6IzXG42TjVL9QvqxJqXUG4todzkMjF9rP9wtND3ByYWrjZeAj0h7KUKeLiRBD9s0MGbSjIopo+mL4pFIK8w4IX8O78wkBu9DaPpEnGTLOGISuUIhU5k1SCiKqiQUGahXOKs0XLJJ8Rq5dnEJKhaOKAHvxxLdVokK3rJtNmEMiaN11rFXePBR8bPOrRsQjF7Z++1+M7gaeI7YeInf/LMxXznx+dpBLOoBkuXOU9pMJ8gwvs5rMSq6/3nl97r34Xr2AzB6xWx4xaPZr1+G8eOw8ul7zHGPmdhbPjiVuYx99fUiRxtqOXixgjd1/pXtMe9sdO4GKG3W7cZm8QQ3sddugsuIac5WzczGpGtALyybv87oqJHD9Dg1pxQoTfjVffazKOQHLVF1AekQp1tCif2ogG8KF5xd6wEb97Q04R7kmDEGK/LFmcJh2eJ7l6fOuL1WXFWu7ThOgeRvZ4BDk1MsvsbKXujI+Zm0jQxo5+9FUcfaFz08pq3NWfNieiwxJ1ZielZpkCJMW42V91uNmj8JLGGDZUOVOU6Ghxnze9cXEqWo/vCexVl0RfsqHJAzsMlOurisQ5bIt+lZTmaemv2qTu4mnN0x3eBSYMZkmJthmB7jrPrMVtVjmMXeFurr32ZbEKPrf6BsM7kn0Kz6bEZR9OErZFfBFshE7am/VfYEjkROzsYuwg2hopgmwkb7awjI7f/rNOkMdAvCM9YRUbzE1xqt9EmSTCnDj1FTmqTJHD6SQ8sJ3p8z6GLSvE+HujJacXWd1z6LgPOjroUziakW2fh4SH1gVPEIdgIxsD6E02ddPNWDO+3CSJFEQnReAq1YFNf6qto1x5RW4BJjnjniN0Q9TFNknO87rhM5hyX9PfA8bqT//yw5eRx1HMH0ya7UXXzgDH/GOLNwPe/+QiUSRtTJscJpxNlciLQzmTJWn7VTg+bTvLsFxmp+b9KQRnTdL7nmEfvS2CTWOqyE4qKdRR232OuhbL2hHuqg4faQYvQJVickXDfPX8ercjMWfZeOMs3+897VoNCUJPpSYB++G+zfYQxCbSJGJPAbpFnrd2ibtKzlgnM7vSkQ5EWAGPiFtq+iK+OOTDlTO3QHQKE9pi9GD9NfXqMAUE0yifPIbCYuQSddzqYUHIEuk3wT8zIs9Ny353DgKcvcSaHyq/8lOVY/xH8S00KuOhNgzhqc2hmIHZt0M83sYA5JuPXY0w46CVGJT5h1cvDvTBlYnd099dYAb0n66y6qb5e+rIVo3rHTzqtgJ1hVHlWfnDA4OM8JpdKmml1NM2ZQ0gjKJ7Ap744frU7you6auqqbq/pWvJl/yvcolvEE2qWtvlf4gdXih/hgTH2j5gzzGOxyrr0wLz5qvrbUtVzNM6csDhrPDIao9u7M9bWYHYmHnMbSgk18SSoQ60/K/5/f+U5I9mfSAMaWtln6PmUlqUV31ThERWVnJt4Uwqy2MqNQyM5U3gkYiTWoHhYqi46ZyBmas2zqQanhF6fvm8oDc/iOAvabNqEcKq2m6m2IrO2QrFG1fZq/NFptugArg/h7UEdp+BZNVqOUDX1avq1KsQrF3Z1qunsPSejhPfni8PzWp9poM363fUZzQVAldUzt+xPNxCB1G82y7w+vdCUCj1I0xoVOZaLTgVSl0svLHnw/13Jzv9Y8lWpktPR2fV5o8xCEaD9BrPQqzKGoNRYuy5jDI5bAH7sx6l2hlMz9tBb7KBflYh47DeaJV6rSvyieOxc7DFzcqpSpVIbP6MFkzUmy+ag5KSUTSmHUh9KLkp9KfWj1J+Sm9IASgMpeSh5KQ2iNJjSEEq5lIZSGkZpOKU8SpdQupTSCEr5lC6jdDmlKygVULqS0lWUrqY0ktI1lK6ldB2lUZSup3QDpUJKoyl9idKNlG6iNIbSzZRuoVREaSylWyndRul2SuMo+Sh9mZKf0nhKEyh9hdIdlCZSmkTpTkqTKU2hFKBUTGkqpWmU7qJ0N6XplGZQClKaSekeSiFKJZRmUSqldC+lMkrllMKUZlOaQ+mrlOZSuo9SBaV5lOZTup/S1yh9ndI3KC2g9AClByn9D6VKSt+kFKH0LUoPUfo2pe9Q+i6lhZQepvQ9SosoRSlplBZTeoTSEkqPUvo+pccoLaUUo1RFaTklzD3DaLmxyCUOyjNxFeb8/wSrMzKAKgWrowBVRIrHwMHu+dhp6SWBATfPM+VNVGOczwtsxLOsxLqn3awPMSA2GNuxXN8mLvPSTZRQRI9678ARgnpHaGelWtb8VGE4Pmo5MBghbcerW5s8QrfgnGC6c5hwSV9pEf6l5WG15ue/jaOCCJRF1PEAHwwkdqEMuHfNOBSRqxaeMxLznBFbckC5Mv44+Pg5o7g8UkDD9gB0ettruh49ZY5F5P7asRiFaz42+XhobUxewmqa31his6xt9MA6ZX6zGRv4ehwJCgdcEYWgRaCtJ4ZH2xClSkw3y8rYi4NDBDeYsRcepQ3FDi2FU0SOQEGhTThwtMfGPHY+8t9shJYmr/e9xGZCV0pfW5dRLrzl1uHhVpU5bRHk4PZBbYQtbyzdVA5yAv6ugN47AlaUFfgd1OpMHQsEt0Y0g8A2UyHEFxsVvSIy0Bi66leDveOXLx4iGna3upafXb64726JB1lFXURwTriQ4PzgeH1gCxxCgO6cFO1Dd5h+uIsW+5XeoCPE1Whb9NhG6oUe2ySnr+g2znwwogvZ4h99Ft/vKFeKDxl5rqM8CIMSaGIPMLCdawzD4MlSb+EzfNPgqfFCg6d1psHTbd5OQx74hzPT4AmUYNj3HKDbAm7/3hRwiwmAat9zAGMQoz3qNUHxe+ZDE7TNhzB4gLsxmJcclgcOw7wEfLS+kpnyJyRfs1OIJ/iAjivUuXrxBDYofaWTr1187eJrJe1iMveJOr6u42s+gOM2iSdYosNN0blh4gkWh6ws4Gs+nls5kq/5eG7laL7mQ7qVY/l6HF+P42s+sFuJX9/PGa+UEeu6Clr0fr5XYQ4t6ms94ga4OG6A7RgrDkJBmohZ4ynwJobWo5Y8CKa7liE2ARey9DfiCRwxQvFEIQF9Je5l40PnQIL+HLK1qpuIAr3F
*/