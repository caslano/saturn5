// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015, 2016, 2017, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_INTERFACE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_INTERFACE_HPP


#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/algorithms/dispatch/envelope.hpp>

#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/envelope.hpp>

#include <boost/geometry/util/select_most_precise.hpp>


namespace boost { namespace geometry
{

namespace resolve_strategy
{

template <typename Geometry>
struct envelope
{
    template <typename Box, typename Strategy>
    static inline void apply(Geometry const& geometry,
                             Box& box,
                             Strategy const& strategy)
    {
        dispatch::envelope<Geometry>::apply(geometry, box, strategy);
    }

    template <typename Box>
    static inline void apply(Geometry const& geometry,
                             Box& box,
                             default_strategy)
    {
        typedef typename strategy::envelope::services::default_strategy
            <
                typename tag<Geometry>::type,
                typename cs_tag<Geometry>::type,
                typename select_most_precise
                    <
                        typename coordinate_type<Geometry>::type,
                        typename coordinate_type<Box>::type
                    >::type
            >::type strategy_type;

        dispatch::envelope<Geometry>::apply(geometry, box, strategy_type());
    }
};

} // namespace resolve_strategy

namespace resolve_variant
{

template <typename Geometry>
struct envelope
{
    template <typename Box, typename Strategy>
    static inline void apply(Geometry const& geometry,
                             Box& box,
                             Strategy const& strategy)
    {
        concepts::check<Geometry const>();
        concepts::check<Box>();

        resolve_strategy::envelope<Geometry>::apply(geometry, box, strategy);
    }
};


template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct envelope<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    template <typename Box, typename Strategy>
    struct visitor: boost::static_visitor<void>
    {
        Box& m_box;
        Strategy const& m_strategy;

        visitor(Box& box, Strategy const& strategy)
            : m_box(box)
            , m_strategy(strategy)
        {}

        template <typename Geometry>
        void operator()(Geometry const& geometry) const
        {
            envelope<Geometry>::apply(geometry, m_box, m_strategy);
        }
    };

    template <typename Box, typename Strategy>
    static inline void
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry,
          Box& box,
          Strategy const& strategy)
    {
        boost::apply_visitor(visitor<Box, Strategy>(box, strategy), geometry);
    }
};

} // namespace resolve_variant

/*!
\brief \brief_calc{envelope (with strategy)}
\ingroup envelope
\details \details_calc{envelope,\det_envelope}.
\tparam Geometry \tparam_geometry
\tparam Box \tparam_box
\tparam Strategy \tparam_strategy{Envelope}
\param geometry \param_geometry
\param mbr \param_box \param_set{envelope}
\param strategy \param_strategy{envelope}

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/envelope.qbk]}
\qbk{
[heading Example]
[envelope] [envelope_output]
}
*/
template<typename Geometry, typename Box, typename Strategy>
inline void envelope(Geometry const& geometry, Box& mbr, Strategy const& strategy)
{
    resolve_variant::envelope<Geometry>::apply(geometry, mbr, strategy);
}

/*!
\brief \brief_calc{envelope}
\ingroup envelope
\details \details_calc{envelope,\det_envelope}.
\tparam Geometry \tparam_geometry
\tparam Box \tparam_box
\param geometry \param_geometry
\param mbr \param_box \param_set{envelope}

\qbk{[include reference/algorithms/envelope.qbk]}
\qbk{
[heading Example]
[envelope] [envelope_output]
}
*/
template<typename Geometry, typename Box>
inline void envelope(Geometry const& geometry, Box& mbr)
{
    resolve_variant::envelope<Geometry>::apply(geometry, mbr, default_strategy());
}


/*!
\brief \brief_calc{envelope}
\ingroup envelope
\details \details_calc{return_envelope,\det_envelope}. \details_return{envelope}
\tparam Box \tparam_box
\tparam Geometry \tparam_geometry
\tparam Strategy \tparam_strategy{Envelope}
\param geometry \param_geometry
\param strategy \param_strategy{envelope}
\return \return_calc{envelope}

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/envelope.qbk]}
\qbk{
[heading Example]
[return_envelope] [return_envelope_output]
}
*/
template<typename Box, typename Geometry, typename Strategy>
inline Box return_envelope(Geometry const& geometry, Strategy const& strategy)
{
    Box mbr;
    resolve_variant::envelope<Geometry>::apply(geometry, mbr, strategy);
    return mbr;
}

/*!
\brief \brief_calc{envelope}
\ingroup envelope
\details \details_calc{return_envelope,\det_envelope}. \details_return{envelope}
\tparam Box \tparam_box
\tparam Geometry \tparam_geometry
\param geometry \param_geometry
\return \return_calc{envelope}

\qbk{[include reference/algorithms/envelope.qbk]}
\qbk{
[heading Example]
[return_envelope] [return_envelope_output]
}
*/
template<typename Box, typename Geometry>
inline Box return_envelope(Geometry const& geometry)
{
    Box mbr;
    resolve_variant::envelope<Geometry>::apply(geometry, mbr, default_strategy());
    return mbr;
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_INTERFACE_HPP

/* interface.hpp
7pSeFQmHvX74dKEkJN1H1n8lcO0CDuQHoz0SKzo2ymniBO+EcJoiMCxcVBAaqudOpMTWXSKidXNkb8DVlWOxHrDqMf8sVQPdQlVjaJHL9lQehcrTBrNqlLu1s/8b6pEkvxzLWPi66S4BHqbq30TGJc/MQQLu1Rkr0K+R5+itUXUZtL0ogHEtGayrj/I/tbEjBnQej177z5kQceoqgSyG7FxzU3nHKolkmI4xvDwazXdIMEQoLILZcAnmw0atyv8kZxmZukJWicu6vCzmybEzkOdjmYF3ZcmCmq5oXQwLvrZRKbojMK1FlVRYKEnHAtd1QGilgh6Hhk1Ppimy4efsYV1dKCpaoFU/uEpXCt0AKqZ+8+oJzYKV5J8u5wu1jrMWA+125Bpoepr2B1A/kTOwg6fBgX50Yih7Nqbg7lxBL1pr+Pxx42XE4bKn0dBRoc4yWQ3LR4DqKsWqJXMvz8RhlMwzR+hj3XF0FRFCFpO4KfH4HGEuLx3U5LXuzzo97wGnNka2ui24a3n9JD6hkHtYLSkukwavKizOv6hI8BgTsSt15IPGrgwGA+W2FU0EiGeUi0JHtTjbYZb3hJPzIlDqkYWDQZyAp4MtOe8L9Zb34bGgrckRNirwIkDmnjfZbDk9Cx0yXo5Tdwl7/BUdit6OJq266IKc4adWX3QLNjX9Xju6/HfZKOk2mRjp2+zJdzeYOdNbY0sPcwUVM3v/9ioIJ8QaUm3tFYn29PEw8gQAanzarfwwzpHbX3PauMFDEl53UDHCxxmO3RKzxiZFolx3jwDpnPcUWqlyglZ8ZD9F85xkm/7uk15Iartqixki00gvqOgQb+HukkVhv+PCiFjc+UnYqN1D3zwqiwMH03Xw2b4ikQFnpZIuKnflKpdOr6A8lUZy51KVmXJ5JhE2p7KCqWbpwI4pKt1wePUO8B60TxpGsM4foY2Mu5FJaSFBC7PWIjKA/FPAfCC6z91/zFKfvP7/9f5w/fs4O5eOUD4pw08R9v9PTJ7t32YnL0o+EW0UAHN99j91Rwfo/LbDn8EoGf/Jhu9TXMyt47Qfu1HWGwbcrd/3l4aV732u0Zcrtoxgw+lP53tNUiJ5FhoP583z9TPOn3jOzvu0UdG15mjRw05i1k7M7TKdxGZt6Wx6zlikajNOhsh344+nHlxrzSRajP4we1D4YHJOAR5soeHRPAjTh+Ske70bRjgZrUgk18P7/CU4zHDeTa54jK2AYe5YK/LFyqjPJEhN0IF3WRtwXbYb8ByR5BW1OIlJy/xVUlKlzwWE5SVrAushZLo1at02gUhAdNPyEo5N+TMAu2mQ3EXG8FT6cXDCX8ZmCtUWZrmpszmJNbfORSQeuoeljUdBLgnrDlemnPs1ZFy8ByASnQh8vD3j2awMqd9Hdp7vI1ZywO08YDr8/+YocrcE2rRaSNfOnGPflNulsHGwH9F43KBlhJi1GsvAoYOahnp4nGG4lN+8eVm5yvIgsCNNmBNhBSHz/fjl1wdgtvlh7Pc+9KxvF+6FL1FAzJtZKkllvWSHhZT9k858soxHRokJn7Pr69HFeVIlyz0GOyasTV+ryJwz60sONUpYAvzI7m+Nf54bOyRPPcQr5S3ZZ9toaUr5nGaxGxFFRjzqct5gn0WsMCFdsotLTcpMs9PmKaQnG+9FN4lnTlambD5GIRQ/JaZIvw7cXUPpxolWL0YgGJltfqnFjcrBxFVtcbYRcSSjHsGEPETass3pZDRSn3O2qk8W/2GFmlyLKTeLG62xBd8+779gm0KJorQy47pV22IUIhNxrIC6p7HIsouIAN439mRkSmdwSGFjpufDSkRreDF/Ab52KZC1kiTpJNs2EUj5uzclwKqaHWFANwzyWUBPz032fCxn30Glw5JwMg4yicA8ywvVcEtUq1jZccvnTBGOiFUjyh/ENM1Q5PBIbX0cCjP0z2pB4Px8Cra28c1z56e/xJVVnWl7n5jX458bptC4t7r7ixtQuHfDlk8tHf93Yc45GEG0z6+lsI8HPgZsmMNLecALhgePBorCfhcVm4fUI4+ADj0dAfiBxR2G8YF1qDFeUeeZ8atYc3AT1pSSthgoFEEAVxxAduq85oyDPr3baIIriI7B6qFfIfJKRfZUWFmbaXF2aRO+lzQjujIUlXsvGdJj3SDDTpeQwxwY8D07KWrjARGXWyim/NveoNRsid7qU6xQp9tDLzKLeePcaOga+OQxbtwvggeShtZbFvbziih5S5G29xopYVak/jyWUmAtDtypTjg/bDBddJhOeygRTNz+QQhTAEDQkB9IDzEpTi5zG+0Df8Fw8vLQdCZyeaXBpUgd1RxnAqApI/qK+29fVMpKdR33siS6G3pwnjQ0d6SnuwPxSs4xzrpe8uFpIX2eCMpMgN7LmMlr2erpTK1juwjYi8j+QZu3Is4tH2ncpFyj/wKh+ylmxDpIo8Arp/KU3lCR2gTACg6YKa6xQrp8Tq39cFS8fE0t1t9adhPpJZYCG6lJzoFZHwuYVJjb6rCCkWbf5iVSdU4TrFynjkUfDvly6PQQ5lWNSP1VkAlLcFbU4UbcAiRyGvb0vUaW9VXZoGDmxU209y6Blz35+6uDuZWRRsw0nD/zwmKBelkxbfEgP1Wb7CwSNlHftd26pqbXGsghRtJnw9NaqVszkLnCHYV2Sx8mraZNsQ4i4G0qOzSCQpMwNvzkyLWVR8Vc4xJLrWmI/b+Q2waKylNxI6mdFk3SxxoTcdhpBd/VPWyMIQkI/nLtd3NUx6g9cDU7MsUc0xkjJ6/YZWuyvcanAdSM/8SW5W+X+TFlynD+/eK86WW65+5qxNuWHaVCus3W3YGQIuPGuasi8fOy/pOFvmftuvDIzPX0+dHKySbpWmnaxLzksIR7nLbNTzn+78YcvOE6w6utaJ8sfQpV06G1kCE2lDKbx8TnZof9YDomMIRBovO4NKUpxxnvoj2yKWQe3nweHuVkKXn5xfFVJ6alB970WTwKrnoEFtaKmyHPvjkVpaJF5ePLaIzf1JwIPPlSSawg5Xv7GPMt4ZVQ701LlJ9dS98fL8AO0KJXEkh7an/4+hGhyDH4NCasJIOj0a+UHrn50t9Uk8dLJxvAsu8nQa09mTqkPBDAEjzDIDIBIzRfNzJcBjczpUdpZd6Axbl4hWhdhmO5IrTTXf7Opitbad9zZNeFTH7DY/Rat7MEZaEoDssOn7HDdmYHU4i4SekaUCNcVN3wy7DLYfajGaToKUS1gQVsfMn06mHNyX8oQ/swMrwgH4k37HQXd1YOpmSPCLnWSuzb9TA9Hqpd7dT8KnjPt5dXxrTh4tXEp4yH51451Rpedi6uhecgbqnThTjr/Z5Q9LioxZCKTCP66W/7gZ3c0erSDRgkiHIHbD6mRNoyJStLY17IjkF868xggrH6+H0zl3OQpVt4axWivVhdN7lbjTSyNAMr6utpUlLI72580cB8txCWFFB9s6JXMvUgUIgkRR97mhTlCWOWYcTcZGcum6v0iZZIno/OIRFqkWdIICAwfYgIT0eLCU8LkKPpfK5DIyocOjoGg0vRDAPMBvLEhkpVbLUB+zlK3WVqBb7Wj+fCnsD5QhCQBEKYvkCRpg/EltdRli6V75qyjG0eZUr7TVI9g6yum+uV0s7UT6bXsSjbPIlQgkaIcqQxkhpalEB3rO81wvKzd2Cied/pXB3m7UXR0f705CTRKMO7EJmk5q+ZtTScSmV+tEJRyAi+j5F1jJ6E0q5RP21qxN5FBMvsSfZY0swrxN4Lcl4h5XpMRP+Ccy2hlTXwaohQB2C3MvLIyHFyQkyRTl9ijF6Yu2dNzqN3P5Ua1eemI7C7PM+jDr7AtJ0vTPn8BNBUTIVUwtyuGslPz+vmQce1XTelK6OEeLY2FvFNLTMRO9g4wxgQjzNX99yxV3/79w37i11HfjrfAav227oEVSFDHsNw434cpviVTvAxHeVxLW7Q8YzqVwiYtkvzuZQVCRy7MD+higEVbv93YK4Nk54b9U6i7gLDSvoF5D8xhiwI1BbOcYsDDTSC9606S1Mu4xme7qFbGHNMZnZPNh220H8nmW2TzEdTNIXqkR07ykbwa2v/XmHY+QnolqR9eM6I06NxnZk1G4B0gq84wrymPsbYnsXhC3qzwbPBMnrPhI3t/hi/1GDd9u68wXqeenvV7/CMiuo90pVeK4m5iVhtghcjgxU2ITitJzakFI7k/490PC3o38U7dwk2fHssrhwmuVgvZZAGEJb13U3hj0zS9+PkTwfq6aq2LM+43xni9so66pb9qzjnNCmmOrXcFLsnx2ILQ5ODAXqEcqHHB5Gz7xmUtWZqnOw49+uLZn5JgFxVaB8zywLb8FHw71KaT+j2GYfo27FKvV/qtlB2O8CAzNE0uOb4F/2cMeVTY+/8aU3u7IrfyPkGC5h2eZkZ7+95DS+cZMxgan2uqLSGiT4t8suAGyeVyEwg9fFJvW3NO3MAP2jTVttLMG0u6SiLdk5RsPpMUH18U2KEueymc/MZJ7Z7tD+aGmgklchHz4YkidXJj3fyXQ37QxP1CFntT71aWgPkb7+c2+MStyelioxcUMZmsAg6JhjT6KRkRYOS1efTfk43TtVjP+7TMPgPu4zPI/yQ5iZ6CJ5h1ElqGlbVSCZCMINVTvDzWopD8/YArhf51O9TWdN+SZMHY0E6APZDgyFS8R7vkOrVYMJQ+LQk1suAct1vxxdXFZXIQN754/QdK5nWoighWAADZbdvp4agWBdKakEMWAzSCW8lGz35AccZDHRJGmRWDG4xCRsMMn/aZ7oRiOOsRYamg9zAi2JLQw5vte7Vkt6YSLFDn8Jcc57UNRpy43C+TkPOBzwc1sSIP8Xr7mgCEdg5gndvOQfnbHX5Trn5DIL5yAs6Rb3wlE3oMwIaP0rcEpLfkoc9ErKHnOvlQdU+xKheUdbvBxrgic0Qh83ZmJ55q5CKV0T6fOXVvtdmxPR/KPfNHkTCESktEVYWNczNwE1ELV4jVBnUeeP8FeamVWU5Q4BeL55ELWAjPM5n+s66hfK17TBNTvA6E/lSDfbukskHH7OgJAgpfHEZdeTc/Jct5qEpd5ed8ToUnG4c6o+jXjTNmbkB2KTM4trfKUrn6bNy9b3YMG31FdETmXo2N4Q107XXJUUAHLI8Xjs2BVwQHSE39n575ugAXWmtIUQr512A5/+hZ4hi2aWtol5U+1diAMTmk1woVnkuV+oy2PIuaTMxy5VdNCChqVR7ZktYFBUh6ducIoz7w4q4bCBkCGC+ovxYb4DbWM0Wvy04yJ3KiwF91rl3xsu7fLCGApQOtL4vPVXkN1uQbmvhwOgtRoh76xrB5ISikJadagChTjelrcep+hL1VFnRKvBIGStYPqs6mS8/FzxFqLZC6aFsLTfba2TBGtzqjtVpKc/9nEXzd+JaRgEJPTd38HgFHfbVdEIZu2w+fVeWYbBo4tFVWkLArHLPLAsvF6Zdr/F8GrTsbbzM25UbL2gUZK/D51Dvnuv3Zppw7U38l6tpUE/S9TTPahmu3589wVyatrtq7UsN/stMebjSdHdSyZxkNkBslyLKN1eE3ECjGmRTMS/kJTNKMmmK9o7yH2SFzkMZ081GFVyePSvlRpyk/hlG7U4qKmVN+Z7bnmMk96fQoYkZ0dJWqeWS1qCW9bBAq2c8NqFeoy7Zkcx8QZgmMeUwfNEK9/P1NLgKDvMxHVEch0UTDik6ApBzMCh6xn+8KpMnELdMQMNRdKP/dFLwu9+12gaAR/BaFosgj0ajGQTxGMi3tYJcJ9rLu4vQk9tZyoAQ5u/xzVgVRKeJorlzcwwZBixYJZcSF633nCeSCNKr9zlY6jnbKSPNn5s4O2U5ZW7HJSxEQdnq7hTgen6yH2+rUf14MnOy93SzbKk8sRkT9GXdFXoLJ61ch3RyUzN3giDD+mjdzxLv1orQNi/6cCG27VnhUj8SQV6Njm5GSCdLiqZpTz0r0U3nJMEJrO1+/PqDPnHAT3shkuk/pWS8yJIQMKjGuvLFkMNO+b3mUSiQDG8Q4BVE316kKsgZ3Te6f8ogtha9Vn236dBJ0zL3tx8RXr/DXvGWvq38BMEDbGttz1MrrVi0J6Oyni/8ukq0xLB+iKJR78qfUe3ZCOcwxPIBtJzAv2ed6H9CjYWpWkLkSpckxrvHcBUwCpLsgWUHfdg6dqFmIt7b1PpoxlolLMJ6rn9arO24Nsdac9Rq9H/3H5vl1dy90uS8NSkj3qYz7PnzY52tQxB3PGnzqMYypdsaz8rOgGCquPFVri6eeoUkPd4LuNN4v0h4r9FURjvvVrQyRB+hqxw3QqBM0HQj7NFCs3TSbVwFtnB7Vq09FLqPpdQRlylOFoheYs3WHOraiV9w+NIpUNMaF1XxfliFfWoMT+d9DWeJD6W1DgPm8fmMIw7c2JYspjQ2Q+tC5P1KC05dPiiBgMxEBa83K4wuTa20YFoP9N1cKYEyFV1C2BRXaFMRZb8Z0neqtApz2U6XFjjnFDOZ5HA45ahcZrsccjlJcmodz+tSfjbP7UC/Wxb0sL5bFncFHplNcjUN6awLdgsul4w/3bILvoW9qkR3sNc/SXY8SRCY6ZDEAWVrcmZ70okTYlNGgQbOwxjf6ZOVOnQfFEYem6M9bOXMzjI9NCU4dXwQOrNr76q5nAl0Ns4qyZxRdWAKqw4JwHQ2zivZmPFpo/6lvhPt/wsah2LarxA3gUwwHwA48Ltpa7KB8cZecXCvgUNLdP069bMCRu8dr9alaphEhUfdgD+dbiJVGmp5aZ7n2PuKMjBOOYYpfr9tabxuTT7GP6liisjMMJYxlbZBEZYOMJtWwILLCzRnoIuvY8XlAGGsDfHdF3RnBrV8ztF5gmZa2gynsj4UL8qnammAsYMNtj79xdwVAbNEqihErWVi67bF0iHfHx9Qkldhvjkek20ZJtW6b2W9KeOTk/Yu1/TBab0PATujZwreGcCC+ZYxkQ62j0DlmNY5OjUciGleaF+yxhutKW8dBEISeBfCjT436EhsRXl8j6NreELseWlhLHev1wJlZy3VYC27MN/wO5/JW0e5Fi308sZGadmudWHBHUOwDBrrgSjyFVVf9I3zTNVqt9NNYDrzdwfuuij12L+XPCtvLfkFC/k8IjMTC2NnvanvjpPDB3Owbp4pihUd0lr89FHV3afi1q3IoYbcCAwakP0K4A2nZp+JsB/5rY8tn2vECX4foX+wKItxQniC23QpaYYNCqKvhvwmWh8P+yBcFfyYn2qrLthcoKuverr4kOmfpS2H7lm4ynwWUt6FqlLQMoGWle0mpC+gAVXia9OEOIYs4i0EsQ3+Tua+V2oJ7Div0BQA52U/cmdVgV96k1hwfibOI/heCqP7pzJZF5Hq1Zj0I1sTzU1xx/ZAPCltMqZx06oRO9K0JbOw8+udSxlPURfP0X0lDEDEW4r8sg1TFqyNfaYkY+u48O/+zsd6QF5QalYNo4J0sG/u+3nQ+nqYW0qV4574sWKEQnjXjYPVVUxycaCUe5CD/Dodj2UGC8zAqnBHxsnsZseUFlqeNqL6OZhIdhOIBTKLzEy6y1/9KTFfGXUIkeZ3etIwGQnsxJRit4RatCCW7QTTtW1Gh4IGDZws+BoRfwP0BdqViCK5yQ/ThjAN8/VesNGc7biKbZX5Bgp22XZCDS9rOa5wSdKS/z8vo9ACoucQFsOYf8egPJ3sYv6OUuOohE3YgAwf+zgI8s1FP83USXBbNKKA0FCPFh+nH3NzgFo/CRXdsMpscbBINIcz/2BU1xXLpSCAqeU1LWZ4nOgYUZ099zUsp5mj34Efcwh7YYvmnVs8NW9McECpujshtbbJ2nP1mRQAFNv7O+tk793zaoNWgw4uPVfvKwqIFnO1OLeI9qETiOS05ciI25nOAQAYYAlbGqREryT056VXnOb1EwGVBwx+VzSqASKCNQlbYMZWLQ5LG0iNJTgDxByt/iX/FLDF38ilmTzDscTRo6BKf1x3BoBsEfIRnbQob39BBbN16v9zXj9IOVc8x4beTB4EClBAmAuFpGOeK7WUlIWkKs80qFfa7+Od0hdiqw+MRO+IT3qe/HVDoSbk3OOE+G7J5pTzog4I3mN3jPVwBdk3t7bUIOOpZ/KZdoLHqYWJlr7NnLz4hPQB6Jc+G+lpWcVdMxdTszIR9JuvNOkHMWfbmqeLP6LDP+MQ58G2fbmzr4+Wrakk+hDbrUUkE8cQYx+9259Egq6nq6loxrH6J/tLLQBU360Hv1iGFBiPOLnEOOSk02FfOk6zpjdkC0ue0olmvY5+lGe9jYANQoSC1wIuB52HRkusqdrBm4I+I5KGr1h1hZXAxfjgFDnHguPZ8mIfM1UB/LpwJOMYE3npwGSxSKl1vtDzjdyhYx0PsGQpNhQiCljydgDbqY9FRJo7DBgmIucdAqaj2zE8ZMWBz9Y7nZaRon3QdmO72c4cfB9BxRWDi0zGzR9b7AgK0ZdZbVKYVJRDE/vcmUZ0pyv8XMspgDYPqpQgMbBvUIlHkTFaL+ve2PwZcD+bn2FPGbHcXoojtHg1ARw4IQ+J1RVmmRsEY3Q2d4KYPyiz7TQMPj6G+n4NPAsn4h8r7cRRtihnq11W9ZMpGxOLzy1LeSsbu6Esal1yEuwoo2e+hNcMcKf0aLrQDSBWyrNDJw1Mk9dhlDrqk4g6DITwnpS2kLjOSMktyzzUrkI9uCk0ZrlANDCPfz9fJltSRKJTqTp11b//OEj2PJ/T28//m09dEQjXCV/VKrrTv7KQF5rOiYGqERs6cq6YzJdH9PLtgQpV5iucf0fksUOsVp9uU2XDWIgUVSZaVPcUgTe3PFGbT5B7EP8lsAZoA+c7QuNGmAGzyQ7GMdFAS/Z+IA2AXd/NGyGGO4DsESC+zKW9dLB5I3dcmS21Yu3GbG8MHlLEYA2XM0RJGcG4fvKSlrXTJRQ0guW2aNtv24C6oOvIzJ1lug4iPjF6+msvaJMtwH8vxlTAVuqgf+CxWcLI1b0iGi4Ith5Yq6CNARUneUBYKCH/HzsmLT2zCgQh4XpxR73tmY+S51WPn0pgt0RWzm0VvfCkonUw+Bk1m6BtiPZjvzOzdag1Ul5n2xgxXTd8M1c5WN449+nB1Bbxh+83AFape8d2gm8seoz96JK2R5ssCfhpV/E=
*/