
// (C) Copyright Francois Faure, iMAGIS-GRAVIR / UJF, 2001.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Revision History:
// 03 May 2001   Jeremy Siek
//      Generalized the property map iterator and moved that
//      part to boost/property_map.hpp. Also modified to
//      differentiate between const/mutable graphs and
//      added a workaround to avoid partial specialization.

// 02 May 2001   Francois Faure
//     Initial version.

#ifndef BOOST_GRAPH_PROPERTY_ITER_RANGE_HPP
#define BOOST_GRAPH_PROPERTY_ITER_RANGE_HPP

#include <boost/property_map/property_map_iterator.hpp>
#include <boost/graph/properties.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/same_traits.hpp>

namespace boost
{

//======================================================================
// graph property iterator range

template < class Graph, class PropertyTag > class graph_property_iter_range
{
    typedef typename property_map< Graph, PropertyTag >::type map_type;
    typedef
        typename property_map< Graph, PropertyTag >::const_type const_map_type;
    typedef typename property_kind< PropertyTag >::type Kind;
    typedef typename mpl::if_c< is_same< Kind, vertex_property_tag >::value,
        typename graph_traits< Graph >::vertex_iterator,
        typename graph_traits< Graph >::edge_iterator >::type iter;

public:
    typedef typename property_map_iterator_generator< map_type, iter >::type
        iterator;
    typedef
        typename property_map_iterator_generator< const_map_type, iter >::type
            const_iterator;
    typedef std::pair< iterator, iterator > type;
    typedef std::pair< const_iterator, const_iterator > const_type;
};

namespace detail
{

    template < class Graph, class Tag >
    typename graph_property_iter_range< Graph, Tag >::type
    get_property_iter_range_kind(
        Graph& graph, const Tag& tag, const vertex_property_tag&)
    {
        typedef typename graph_property_iter_range< Graph, Tag >::iterator iter;
        return std::make_pair(iter(vertices(graph).first, get(tag, graph)),
            iter(vertices(graph).second, get(tag, graph)));
    }

    template < class Graph, class Tag >
    typename graph_property_iter_range< Graph, Tag >::const_type
    get_property_iter_range_kind(
        const Graph& graph, const Tag& tag, const vertex_property_tag&)
    {
        typedef typename graph_property_iter_range< Graph, Tag >::const_iterator
            iter;
        return std::make_pair(iter(vertices(graph).first, get(tag, graph)),
            iter(vertices(graph).second, get(tag, graph)));
    }

    template < class Graph, class Tag >
    typename graph_property_iter_range< Graph, Tag >::type
    get_property_iter_range_kind(
        Graph& graph, const Tag& tag, const edge_property_tag&)
    {
        typedef typename graph_property_iter_range< Graph, Tag >::iterator iter;
        return std::make_pair(iter(edges(graph).first, get(tag, graph)),
            iter(edges(graph).second, get(tag, graph)));
    }

    template < class Graph, class Tag >
    typename graph_property_iter_range< Graph, Tag >::const_type
    get_property_iter_range_kind(
        const Graph& graph, const Tag& tag, const edge_property_tag&)
    {
        typedef typename graph_property_iter_range< Graph, Tag >::const_iterator
            iter;
        return std::make_pair(iter(edges(graph).first, get(tag, graph)),
            iter(edges(graph).second, get(tag, graph)));
    }

} // namespace detail

//======================================================================
// get an iterator range of properties

template < class Graph, class Tag >
typename graph_property_iter_range< Graph, Tag >::type get_property_iter_range(
    Graph& graph, const Tag& tag)
{
    typedef typename property_kind< Tag >::type Kind;
    return detail::get_property_iter_range_kind(graph, tag, Kind());
}

template < class Graph, class Tag >
typename graph_property_iter_range< Graph, Tag >::const_type
get_property_iter_range(const Graph& graph, const Tag& tag)
{
    typedef typename property_kind< Tag >::type Kind;
    return detail::get_property_iter_range_kind(graph, tag, Kind());
}

} // namespace boost

#endif // BOOST_GRAPH_PROPERTY_ITER_RANGE_HPP

/* property_iter_range.hpp
Y4mgnYFDmgqLKH8sc5NxyGPBoG8EKt3/W0wAVfb4RmjYeJf5eQGARM23SLDnCoW2yD4Cxma/eEHI1wo/QASFfJ1nLXZ3C2vr2W8d/fJOWrqxX94aYrTTwGGe9Dg/7UFsiFRRbD79NTZQwijBqhNGkM0w1MTEEWTKSN+hyhWZkXfUeRND6RmgsdPTLOWnWcpPI2UBdoK4P6KFziMgYmapir4WcSDg5wSlFzF0eQYvNE2smxGeASFPfokD0UhlGuKzgCgW20SWwUxvzlFLQ3mC2KBm2dY0ZbYJDMRxlx37f95EQpazFQniV3ZPvh7MT+ER9C0Hyo3q14CUedbZBgunobS2BIXeIO7/UYMyfuwF8RlAzhMD7AgFS1/FXSJjXmzJfF88ueY8MpX5oeXU8qszvRqfnPs3gdNpkHzf8MHgShZLaJDTsvQtM4q+TK/4jXQr64WcSSRZ7oNOY/jgHOYvo5cTepPlN2Dpo9z2zWOnQes1syVjBg1x3wSEmiWHFbsPJ1bqHXul9dybvS5ML84RNcze5Ad26MVFae6LjmulAIY9xZI3n6tJ7lwne8GG5hv0/GQrdviUdII7yi5sGIq3qxdL06Q/9zKXBmRdYOspNC5JgqiSSZavZ9E/k4X8VCE/Xcg3w8hY2ojKFRalSYvnKaYgbkM5+MT3Jf0lmaQjmVgcnx8++4DnS1iu9+XjfM1f+PKZRehLYr/5ye2jyTLNT91Fl6h4DWu6kmP2k4gL05AJgUW4F0vM0O48lHtBurBxJou+xQKJvVqEX88kFh2sTqisFyobhcomobJZqGwRKo8LlW1C5Rmhsh2hGytZKI3KbnQUlQHxfRZfIjjdU+eZ6alz1WtnOLunOOuc43g8eWGyYFk0FBL/5DXyjFCO8CpijrGY5eunrPTUOUfc5+ozLusRW4WNiLFluVChEzyAES/UGuECstJd59TYnL2Cey6+dy/TCW72vVvIYX3NsY8tTRXJxE/mAk+dsRrbm+/TnLY0lf/Vo3ezfsOD2FjiTENd5klhSzbiZFX/FadEHha3sNBoM8fV5Ry0CQWrHaac05qZ4+pdDVobvV3t/FLcgqLKOcjOs9HQe2HLI0ziHbeKW1CWHnmTBAtoJqoEvUvc4mA7RDQiA73P4kE5l3tFzkaVgW2W8LCK8PB4Y8iZeFZwAzCnvve04J7PaALS50assmAwvMmHpcSr0NJqfNZEytYzfWOdwOJ/iPxXxVZeMCdhUwueqXCUvZWGSySAQblKrFfzKukcGVqtDvJDDYIM3Majxnm0OZYW4zOYtso8K2zJBaEx4fNqWF2KG8F9kHGpfhUQpOBYDWUes7QsSxBbeDy1zMPMvj3WbnEjgWX3uo4EM1nUMs0B8VUWu+RQxW330c8tnaN5/JJXkVNEV2E34vc19ZYDy5LuyzxgOVT+kehm+5pVst0qsJBmmpY1/VuxerR2DNvHgybgmXRAZNxRVfECRKABIZsTEEz8I0+D6nWG+AYKv2YjC7NXx+qg2sN8rj0sd75jksiOWhAfGBS/yeyr3pjHigEg3qAmMyAke4WVXm2nTm4L2SITaI929BQ3iyP37H62BeixsBzU7L+todrNyDAZ8OjXiG6IhsVbPvKAG5TrO+8XcRqlxVsxllkj1x9cfW7rau9DMm+BzhtIHxekYq0MkeS8RfKHgmRxqs7FqGnFV5n/36HMw3KpiQfEw8ckCxOmihyRx7vTe0P1CwLCnZ5JLI6t8ARc8o9wYCp/TovV7QNy1boPOHQ53a2S+4AzwFIg6h/ldIdKGAgzbn7fwvcLOW7KZAEIw4C2oW/ODoHhuN6AgKjksmLyZnTPvRRqMy4m7dr7Zd3RanxmkHX/U9xo5Y5RcBFKxIrP0J6gQmN4Lo6NN7D8nG4v05ZdUyRHTgi2sihq2G3qsQ7Kx76waRI7G9WUJOMEIVXZNWXXzKYKkZz9/GzJdFfwEo2ApqW2940xdV7nCg444O7lukvl1NPbOnr7FhogS9JsDx3ZODRsVvCzFCdlXpal5AiWTEVLa2lUvHQyftTsXLKCNHpvlk70ydzhcNFjzLM6ecpkY9VptlaUCocQPp9mwt7xpbs+AxX6mVfk0f6SCFCnUSQ9N0TEeQsJ2RS1c+SaSh0SWv5jsThDnGa2z2EzZ6GZCZRFGtYais322ZT7df1jTFgLDWeYisd5YwTAY/1y8URBDTpQeDNDX0MYUVC84DMIqvOqEI6u/1sKnMrbpxrJz8bzqRPR1yZkSGNMPlVGYIwpNl6n7D9ZmC3m64vF0kl8wGQ5vEwjlmaJ+abMk5Y20ndkpjoMrkrdAGJOsY5cvSg5s4FMBrKv0fkX09B/6uxgCzbwW6di0io/WywJFNOA6dJ4HinBnqVeGNA0wNTb7/w3kUZJBYNT7JOcGqFwEqX8j0lsPSVGydA79UIWXLggIMzSC9ZszObEn68WbRliUXpZGg3q2co2pTC+pkBXU6KvtplIhqqLrqL2wY12wZYsFKUq7TWc5wWLtDSNzFHRiBOnrFqsgRamYyhqn4RwKYU4CsTSWpGYeeiBzkSxMCvzEOIA6mjwZ1yr0VKnxnusoNlTd73BZNxjM8HHnpKz6Xwqpk1y2TJcW8W9/FRyDo/DfY1VFzTssOmJBd3GPVA77QxEXRBwNehGwoKSQhNybeXviHp3BrXbm3EwSo+Yq/Nomyg59bFHB3HJPGnco+M7k5JFm5ZAGAfw5PEXsWR6LnpNjutd54yYGCyQxAe0gk3rw6SGyn8HQVz05jrHgvk8iQh49E2chv9q9i3dWOXUYAwEQ9D/DYbYzBeAMjaZcc1zNOHvzpGamC6QKDfIie0qVoqpLA+ayFKcwu01nhpCkvyDyy9+Oel9ONVZxaKNUDkZq7CPlTdYMoabqHX7Fw9XJPq/m0k1lYFcJD4VdAL1lvTKSi1QIjvzeohjE5ZiCzqwVN6h8VqsGeUXeS5cK7SU+Cw5njnzTa202LNI0VGjKsyweB1jxVZLC0n2fhtJtjULXh1dODJSsE/CiUfSJrgnUDOgcYo1G9M+LRVJiB4U0RBA8HpO7Zo41JCqsWqhWt5DI9WMDOZJwYKu6lH0cH8o24VZzhFMrUhBm5ax7cZ8IotP8ffw3d7/j+H7j3zvDxzTRt1PXMv8ysHrmAp4GucHlH3DFFa3YE0XStOEWVrMNjRlGoUk9SwdMSXN4se8hQ93HeSQNMLip6EqoFkWxikwwoK2kwSNHYzULRSytPK1ZZc610cl3/myayBp2RhmB6nzul2duokIhqUrAi8NfaxwsIpmz3bcAVVcmA5szjmpv5OZEwSjehEH39CnZL3Hh9OTVdFMqP06qrGyS/4vqV28lmIwHaL/bdcaTKaxBtMe+r821WDSXWcw3UNK8g/0/+r1oZWM0Hpfhphrns07blLTpMypsqYKOnGEK6B1JLoCiU6TaNeL+RniLLN8xrTrnhHOUTj+ySfVsamqDME6CX2GdXLIhTGNX9JVYQc4/AVbwv3PkD+jHd0AyKeX5WJVKWTn0OhqXoaYn74UxnyZjrFIPZMZE/jirAxxXsgEWMQm/zmJYkaBAWbgSFzRbh5indGTrRSTjFWgw0bhrJx6oVBmXgpg7614YGi+dCrrr+zpcpeVhIURqllrtlDQIxZOEkoGhYVdiADXRPLsleXZi4NZJNZfnRoR7n9IZJitS/1W+y0Gk2tAU/F97lv9GQFNLKHWGjDuuQqmMKmp0BH1C7tG72do6hLMbBJW+SFMoiaJra6P1K1+wZ7KIiosGcEo675DlEkzHSYIr6Q5JtGYd2EXn6AjdP+94CevvchTcsZT0ObJOy59DVfegnYRTihtZAgen1M0m2p3TIC7HlnZEV2LCc376KCGSDNyrI/7iiqH0sC7vEH2Gt2G/wwcDAfSKzJzDk4p6DFWzRnBPMSNe64OFvQEYTTp5DyO3s9ylF7+ntjU27LmHLYjeiUa4xjdk0ewk4ULtWzJeNDS5DCKC7vY+cjCCP8T8Fy0ptIbLL242pPo3b8myiGnqjaxO4l0GnNntWdNKel23iTrsiZHKlVXhY4qi+qoMymzVdwvlEgkMD9hZ6t0zyaBlkwoFBgipM8mMX+Rbhp5jRJbM1tmEHTnaFQzVrIlGt9as6bkdTtvoLZAui2ZQCuSMps8s4MkDPaszBZQP2qsepLxTM29J1S1eTiaJ1H0IgAm9S7eZRrcIZZTgLQDPM4+T2bOVGrqyqhryuueSFLVqJ9o1Rrdy7TIWmrvqRuOuj5KEq71/6sWxT6mwhIan/PCMCcOK1tRgjWm/J1bgvfiZAzXuQlU766+cca12ayOE13tE1wBerwRmZiX7qnSJTDfrowybRE3BQUrPFyqzmuZoIzB1FbnGAgF92H2jYDi5WO9Qq3XP8rl1U4p1FU40Qwms/E+59eh5fwygbksvxrqugt1YrLnMeq9xUI9xIDGLHIrU9t1PCEuoZQcF1JKtFysvQZTS1Zdxa2R8x9ETM+Jlep9WlHFqRBYeQfpkjmkCj2FyR6raXbRHPFDbpVJr13gUY5MiHJ0P+qE1AE778s3IpFnVmz1nk90fTSBStWzbhTKjXgwup5Ty+VBLPxO1g9ioclyssISWX+LNVHlQTDDFInlZPlhygGMGdGefHOTJ/mQcc8MtThHy5zMml39pop0aAQqLGgtSs+qE5LXhMqLnYvi6r+aBlN5XUn82IcZX1LXnXOQ3ho3eD36dzTMaVGC5VNAeq+F2L2LH7oe5Px6mO8kmV49Mr8Rptfo/WHRH7QsbKH6K+g4JuGskmTG9c0t6hLpmKQp6ACPOsagVmyRi699gqcqgYldiaRppQxYWoxrJ2pQUM0m59Vwo33qeqRu1YvTqwc7E3LqqcoEbc19wQLJ2SMU6rj4Eckmrz+RqoORVLMaseqMT/0c0zKFZgKYjZ3HnoJGunawei+QZoeQ5txHaLMTMfgtIjGwJvO91BJfqeqAZpTu7OZSkQ6pOApjFE6NjZRdGmVLRbPnYP/DlyHPrKoP4ENEbBHjrHNDk0L8MJzdJx+3h8OBrek4Dqo0TWzJHMsMB516ng5nRJEdMol0tnhE2sSI4kgtoxvzf6ynlgtdGk0qHacAk/ExFu416MQGWScWEO1pzME8qh9zrUrF8cHiKaMbEY94JymOYWbY7X3MDGPGDJgq6RHmDZlhYkm3bIm93R1ricn54JA0+uZWWVHnwbLBzpcJhNqsb4RsgOUOYLk/HeZ1w6WwAfbrSEIojBCtos6qMGo6oZKBNJ9PALEFqR6Z2xA48Vzkn8V2xQZChpkuVMYoWipimT3WMfT+VZGbEowZBHvIJhv0I2ZQOP1B2I5x6k6mS2yXXQLRFxVEXQOXnNdG212cJg9Oz+ilgR7ZJUp6xSBXHM0jwfkFJtx6bgfB6AuXSJjd9n64WoSLh2qTV2IScUkVOfgFW3xScBkpsRFcDuKwYrKNC9OK/R9fYudshd9QIbVcQiElMaM23OVu+QIMss62oHtKYTYO9GRZtacPGcqtlFsjdY7IbeGkImnpFwqjfYSOR7xVVIravwQsBP9HmsE0c5zB1ID/8QbT0gkGU0m6wfT8TQaTgwyyJvq3mw2mgwTnp//vEVz1zUM2MzNWL+TUS8d6mOEb0Vat5ogHVm18uikVlmZoBgQrcActfY5/EvPTyFDIEGYlI7zzrFTRpufnZCWR7T0vzS6WJ1Mqj1IqpTn1ixpqcTDeooZmMou/J1rTyKS+w7XKrHJkcH/LJPGA9GNmiqeRfUMdVaguuCGeU88JMH/W2cQDNteugJrMT4PueRQK9F65oxFVpOorddpi40av/XVMnHoeD7o+HRCcOlfAYFw7SgMj0+24zWAiRQJ0LbDGBvN14qw0G5W2cU+CcJ82mGQ2imen6hwTKD++BAPzgKfBV+oOapG+XC16Rj/CbyCavI16aS3iedlMy672qQxcGDcQpP95bP7hUzo8uY2khSgxpCQmGffockn2iUSu1tvO9kUM5hzdO4HAey+IZ91HHSlINURxJSjaiNjFvMF0o/snPHl5duUuZs6kiQ8kY0+aukeOXQgpT1XkIZfpAv8oNduQlyCedQ2Qrr0ko58VH0/23KeVdn0JVZuGaBuiU+cY7VNhJdJ/nI1ldUP5eRt4RjlHMNDy07wfpSKm5ay0YJJ41qceOQS8SS2XNQceBeBzJrUNQsOAE0YNAf80HmWdmijnc2DV6CHge2KBw5A2rXjWYtPxKMLhwlxMhYlyuZ/VJepABQl5+iw1tdIfcZFl2mdWmk+dMJQSSiBKXrztqYgmEMqDZgj431Vx8mCKzIM2BOxYdfnMJoYBS4bNqK5UmJX9Iz6Bx0YaPAdKCZ7LJRhCEJlPrFMPZVjPv6pDNOj+UghyCIds3jtuNZi20H/pRGpR9F9L/+fofyy1MHWGwfQo/T9P/z7676H/WfT+R7cZTBHng2Bp2vjau96/mtwXnUmLPFZ1KT+6mmyPqiC34rh92bBmYFeKSlWeWItLZpuw0OQKmIzr/sA8ubznteKp3tOInNHAz+vYM15z2LinVK3pY9cE+aqRr1r5mihfR8jXJPmqk68j5eso+Tpavurlq0G+jpGvRlw1fa4DphlG93IW7AgOvaONe67VHLJq+mzOr2sfX520GntvjQ8fNaqCQc0h/uazoTf9ML1GsgW7H3nbTYtGe+PE6xYL9MY/F+CMOk+eHpvHdvxgMOy6y/Z3Lr91ULHf0xdU7v88oXh2dengGbZ/wtAB1kb3OGwE0HryAkV2qS1H3ujGvjCHobzA1AlG91fYIT8oGt3n2Vb5fp3RjeObLuYNtBvd78PhaoRdeonTpZcYzDiysXJjlzbcNBg0vtbEnQlAFr5g9H6lgovfcGo6xw/Y4dnSqhsJa08Yy/nkeupLbuDukj9RfnN8AmklZJPjLp7kfVHId8vnjd/Aad80DH6CI7kswS59PJ4xxhpDhP+lHdtlx/axjQ5kKVjNgjUDLjzMf9lqgucFPDDC/Sl20o0onl0kFRM9aGsdKeQfzPNY9dIvA3DpscGRxZqac5Bu0+FsZvLYbThDtjBNeLoIb56eiV/4EfHzLeX9xRYxH8dp3yzO0jFvH1eDrXj2PDKZumGwX3T+YJHsboOpJ524XJvZveYbAC5LYk47nVrqq0+LY+2aljnAlW5JZN4t6uU4q2iR8JhJmK+PicjnWWtjLiRrwZQ957SQn+rLTwM9eTz4C5PKaZwnMW8BHljXeUOZypOvl24MhMx+xxiqjhum5Kctb4FKahCXpwqvIa+W10DWeT7kKMTsmW6xD+HpZP3wG0CIzwI685DlSHmCeET9LEpO05p5QWBfHSOlEr5O3rqoNO551fNEnEFAdNmx4WuBXnGV2CsVMo8e50/x0TkoMroW7zJDpld8V3qcexHNd592zB2K38YKQmTcZ3ZbviqHIxScdoqk90hs1E692jmoZtlSvwZyVMKZZ4nDv3DnobeGfIYwpRf3fHXmDYmpvVV6d9BxrbSC1PS8YmnNzbKb5TD+QzhFDP5DyVJSUOE/RGPHYrFUN88laYvsOUGp9oaQL/KNvOX4eKNkh54HHAk5wWK79CsOJPoWRfunFpMYYMvRlzjtGKu3qyffaXQfYpMDuslGdz2PUFT1CsbUpalTStNxknJ6epbBJJRmTCk1O5N8VnM2PcJeLUwvSx2aI02zNDgWCPOTMfT7od4yUKknC7L3Q1+unq2ZzQq4+pKWF+PrkybYlu/K3jaytdrbuubcLuqJZpP5+d3zmOBOg+l+PzUcp1Eq+pptfBsMsi1dBBLswQsm8lIO//gN/0h3/UHlzi+lPEX7CKKqPYv0wlrWhJmQyG6CT/bLHlbOB+3Sy9cPBoX86b5p6d2Z1IFOM5tQDNT0/zljjQ8trWxybSN15nsvoD0d801jfbpgkaq4SxhR0U7ROGm8U8v9GaO90Li+513wqjShclDq70P6bKdXFmJVkTYRNMI0rTBNJ0zTC9NMwrRkYVqqMC1dmGZGj7N0LjE/T/h5mvRWuuyHTwZjwJklHhEbxBNS3zcyQcdYGq7Nmy1J6YN8I0/I3174uV5yXeLBGIxV2BlImmirSmXke1fzBj0l+jn2Iund7DB9xPxZUlSmYvG38rknpeWA8/vSz/vZOJmSWYNkSrAzg3QxcV7Bs5AMd+drfNNSu/+JzBDOAOb2c+qJ0qWB0CC6aLaUy7JjIuWiIRwqW+bXNo1PBWrY77Tk9GzUSySx5uAtm18wmIK3bGK/G16IXLEI3lKteLaL083Jo+udGeJMs4nu9TlHyexvozsdXbvFht7F9L5JPICrprUzn+4X0Ju5Zj1gWv2tp1vPt7aNPujs6f1K7CaoZIKYbjb1fqppLR9jIbjlunKjhWCXjSzMpA83zDUn55ymOx3d6XtP9ba5TqnEQ+Ix8STSKd1vUkXI7zx7SU4w53POZWVKfh6lbOpt6z3lalMJ9FKYy9hOo4/J+fQtdehbGn1LlbOWCgLhrJnCWUuVs5bKstbGIIk/wLR2tp5kWTtNWbvAspbGspYazlqynDUTz1oqZSiNZY1lsuCJpJjczXKG3i0sXYScuu6Weq82qRy384bg6gh8kGb+0pilNR9sCH27ytWlPTnVPH+Jq/0XS1yBXziOyafcdnSfrD9Jmfxwpdn04SOsVpBRGHpTz/rdR58YfzLNLOrNay5A663xQn5cLSrk0HVU1Zklf+Xv2/j7UyqcQ2lO7t2Pt87akwvMqfg/CLmqYhK1mv2uZHI02zPTrM1suqG+t+XmJrHxFlU3izgzSvQ+uEFUCVpzw+3ofN2qTj/hr2CYDvb7GPt9hP0uZb+L2e9D9Fs2KpiyfavBtA0FoDji1VPQ4f+0ZyBILOo89+vFGe05TdKb5weCtQGXyeS/vZsakFMnbbzxq2CDp6DFvy8StplgnwPsQ1UEqyZYoqej5vKiwRQGChDQowBKfpqAzvx1IKhY7yvodnnNMgruM6LQuwn9DqDbgL4lCh34/tq7+4MK+G/8BO8A/KPx4AP39CnhjwB+K+DvjgffFAnfRfC/B3wz4A2x8Dr/pmj6PwN8APAffBEH3nZr7xC8RPD3AN68luBf/iIOP6mR8OBnDOCLAF8ZD143NgK+h+DPSgS/EvAFcem/dVEJ/wrgdwB+XCx8l19686KS/1WAPw74zz8=
*/