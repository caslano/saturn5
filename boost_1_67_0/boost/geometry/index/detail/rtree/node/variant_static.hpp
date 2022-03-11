// Boost.Geometry Index
//
// R-tree nodes based on Boost.Variant, storing static-size containers
//
// Copyright (c) 2011-2018 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_VARIANT_STATIC_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_VARIANT_STATIC_HPP

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree {

// nodes default types

template <typename Value, typename Parameters, typename Box, typename Allocators>
struct variant_internal_node<Value, Parameters, Box, Allocators, node_variant_static_tag>
{
    typedef detail::varray<
        rtree::ptr_pair<Box, typename Allocators::node_pointer>,
        Parameters::max_elements + 1
    > elements_type;

    template <typename Alloc>
    inline variant_internal_node(Alloc const&) {}

    elements_type elements;
};

template <typename Value, typename Parameters, typename Box, typename Allocators>
struct variant_leaf<Value, Parameters, Box, Allocators, node_variant_static_tag>
{
    typedef detail::varray<
        Value,
        Parameters::max_elements + 1
    > elements_type;

    template <typename Alloc>
    inline variant_leaf(Alloc const&) {}

    elements_type elements;
};

// nodes traits

template <typename Value, typename Parameters, typename Box, typename Allocators>
struct node<Value, Parameters, Box, Allocators, node_variant_static_tag>
{
    typedef boost::variant<
        variant_leaf<Value, Parameters, Box, Allocators, node_variant_static_tag>,
        variant_internal_node<Value, Parameters, Box, Allocators, node_variant_static_tag>
    > type;
};

template <typename Value, typename Parameters, typename Box, typename Allocators>
struct internal_node<Value, Parameters, Box, Allocators, node_variant_static_tag>
{
    typedef variant_internal_node<Value, Parameters, Box, Allocators, node_variant_static_tag> type;
};

template <typename Value, typename Parameters, typename Box, typename Allocators>
struct leaf<Value, Parameters, Box, Allocators, node_variant_static_tag>
{
    typedef variant_leaf<Value, Parameters, Box, Allocators, node_variant_static_tag> type;
};

// visitor traits

template <typename Value, typename Parameters, typename Box, typename Allocators, bool IsVisitableConst>
struct visitor<Value, Parameters, Box, Allocators, node_variant_static_tag, IsVisitableConst>
{
    typedef static_visitor<> type;
};

// allocators

template <typename Allocator, typename Value, typename Parameters, typename Box>
class allocators<Allocator, Value, Parameters, Box, node_variant_static_tag>
    : public detail::rtree::node_alloc
        <
            Allocator, Value, Parameters, Box, node_variant_static_tag
        >::type
{
    typedef detail::rtree::node_alloc
        <
            Allocator, Value, Parameters, Box, node_variant_static_tag
        > node_alloc;

public:
    typedef typename node_alloc::type node_allocator_type;
    typedef typename node_alloc::traits::pointer node_pointer;

private:
    typedef typename boost::container::allocator_traits
        <
            node_allocator_type
        >::template rebind_alloc<Value> value_allocator_type;
    typedef boost::container::allocator_traits<value_allocator_type> value_allocator_traits;

public:
    typedef Allocator allocator_type;

    typedef Value value_type;
    typedef typename value_allocator_traits::reference reference;
    typedef typename value_allocator_traits::const_reference const_reference;
    typedef typename value_allocator_traits::size_type size_type;
    typedef typename value_allocator_traits::difference_type difference_type;
    typedef typename value_allocator_traits::pointer pointer;
    typedef typename value_allocator_traits::const_pointer const_pointer;

    inline allocators()
        : node_allocator_type()
    {}

    template <typename Alloc>
    inline explicit allocators(Alloc const& alloc)
        : node_allocator_type(alloc)
    {}

    inline allocators(BOOST_FWD_REF(allocators) a)
        : node_allocator_type(boost::move(a.node_allocator()))
    {}

    inline allocators & operator=(BOOST_FWD_REF(allocators) a)
    {
        node_allocator() = boost::move(a.node_allocator());
        return *this;
    }

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
    inline allocators & operator=(allocators const& a)
    {
        node_allocator() = a.node_allocator();
        return *this;
    }
#endif

    void swap(allocators & a)
    {
        boost::swap(node_allocator(), a.node_allocator());
    }

    bool operator==(allocators const& a) const { return node_allocator() == a.node_allocator(); }
    template <typename Alloc>
    bool operator==(Alloc const& a) const { return node_allocator() == node_allocator_type(a); }

    Allocator allocator() const { return Allocator(node_allocator()); }

    node_allocator_type & node_allocator() { return *this; }
    node_allocator_type const& node_allocator() const { return *this; }
};

}} // namespace detail::rtree

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_VARIANT_STATIC_HPP

/* variant_static.hpp
5YLBbodyvqIWNiG7F+aA/msgaNfbzebX0gtKs4lM65kXnfLlAPgpf3v1L3cw6FEHCYq/4jukdSF/W8J2+dhPaHt4MLuNK8+gpWvDdP+zqxPx6pyb3h12HaQSD5MOmZERRbU2FWUlkvRdGuCVpZ/ir1pfIa0ei5zWB87P3c77dIbIELMGRNsN0WNflX7xVnx4fbu14wSfm1pkotIA/js8JGEcbcO8QQfYy7lh6EfVZ2Lz5wVc35EzCSHgQy9iqm5y4nhmaz4HhBqIAdafq/lWQv7Ux2qx+UQgWX7Svw4Jq27s0NxjrhNlYUtqXqvLENjoH+54H2u8jM2DCF274n1Xccj+U7MiFHWNQqwGWHFvpgu2xYcsZIF7d6GHSRXAotczUXNvf/C0LLCBptEowgcDCOppvoU49Qwoa8KS7EbPhOKwTkanvf9YGCzcQXq7BIqkpLDVT2YybsJM35R2RknV9jpgSzn+lVF0qY8UNqU/PoFm3ugs8wNq9RAPMANjblgjA2evDwYSk4uGoWynC1MIMhmTLhNlqRjUUxXaBqtyAYy80q+8G6qvPzS2GFMQgCDjgilcCU5c9LKp35XlHeVDN+0SIom3Z04A2AVwdtuOSl3eNaLFFo59QHS9ypX3mYvRu9/Id/Q+RvrrSdW7jITil0t6Xj90i+c2kqvqPdYyFPcyehjC/A02ccrhsCwzmlGJ03QSe+uSF37KXXdf5Pase7VwjcqLcQV5a8jI5yQHtPoPAHPtiOh4wcZN4ZX0tq0zgeJLtWPhD8M9Xv/WR2gJD+XDxIgviDdaNnPzX7UMY2mxqMwEn9Z/ctFHfAfvDcS5bVKmo8Gw0PVYY2xi28HfLje1CI0Zk2rSS6/qxLH9q4EUs72smhr71C9mecTH4tfZDjmeqblRQR9Jq41CS7yZsJdqky/ZqqNhoBTBrEJ7ttmp1H8UV+l92PjDq7w+uPso7uM2twn7adwPbLhgmlxQdOeCA0uHzGHk6vYfwr3fOqv+NOh8Z7rl1hENX8SoaaqOqXzGeA6F/919gHBTgNDrFjb11q1Si4jHjBZHx3B53yZtQ8ireHQ/ca5MFNYBoJ88J9557An6woceAtgYUj72aHonFdE8GmQwAtyTojsF/fnEtxvd2bK2Hy2iejC+54UqPiTz+ROkEIfxKSMAlSsS6FgwXs7zmSbWXjLOrR1VxOuhMj2fSxN3qscdjPH6ivdFOFa4L4YnT89V5NkZE/tQ9tLztchJQj704i1kPkUkoFR77ZQrLnEatOzDeP8n6zOTf9svmvk6lxBb3FYz3nua227Iz8a3OBblChmASTJ5Z5vvFhf99hnKrRWZy9mzCIvPW9qP4z6WqcySWo60B1/O8vdNbvvk8G3x5W028wr8Se/7elDCS9Yj9Dj0GkJu5/fTygG854A2ekIXIGgTnvtL6vfF7s+9TNN3XNpX09p3jL8qC3hJDPi8jrJacRmOtppJVeebD4BLWnWLgBMMk+D7LSRD5LNLswdJXeaLUL6je1MEkW3ra0Q90nkT94LijKRmGude8f66xl72x2n4k/RtAl6e91opYiYk0pdtHTlRdkZuOemlX/2I8QQhI0QvShmnfJNBdQBXXpK+IksE9UQ1UqKwW1kLB/EN5riezt+hBnJCpx15kHmwmlesxexE21jJu6q1Qhvnz1nIOWvkeYY2b5bwcvtV+bm1l26FB5YSb6x/y4+EsmueDl6NjLLt0WxxRavAk+x8fk7N9aO3359i0fDxgSVys9MLX8ZEmbYSEQdjC9cEyl6dYHeWZcMFUYY7O1ARi5Lp1oMpY8rXIk06ZpDEuldvIjqLigLER/DJwiNXBqx3jV03aseMWE4iJLrVO9T5kCMzsebuuAmgdqrwYdr7tIbZPN214M799yqLxakRrxSjFpS/TWR2bniyoTNs6iiN6mNoZPfqy1FTdJik3Nq+ZmeypjubIWustb6UjB8mk61Vl5nYiPTPxuWsY2Eb4BBb7e8l6UPnfO3vk5Xi8Mepf0etPntJRqcwaBIMB5C2vQiCrYkYox10UxYZjA7xTVeyeImlMdgEVPzECyiJvcVJxpSg9empW7BrBU3k9SD3zatRKm9zraShMXg5nMOlFEPs8KYx6RY7CBh8Eaw5WvYDYCDhsdL1vyvFRhtU2fH4AifYr8S9jYuLvgDSuKlH/5XyN1U5bfur1Ll/rvlcfMP3FpeIAziUgd6DTHmd7yI1XevCczfaC5ua6mEM1tKhTHnBNbN+tUJRSxkaNJUf7ZFxo1X3WtKrA0y8ePJNcTagOH3F2k7PzM3Uh+V2M1cP8b5vH0l0hc/QfueWNvo9sUUrkHoCXAWvjWzFBG2R2WOSwFXgbsNESHWHDJ257qCgg2qBZJNFyN+LXNK/Pl4R0Sz4qZSUs501NGyx9QO8Q8vkC0FIHCiCijShUWSWTrHWlTeru8/JRNydEE+OFEJ1DcxjzQdD8Hak8ZzMnwg+vtF5jRRiRPKirLmC0bF5ePGPwUlIwfTLZVhSdew7SoXmWYTXptnuFj59f/KNfKCe0UenhxpqOAfIx7J1/CnqbThVcFveGTAXw/h3wWQgaS51fpJWb7Dgdms9RHAMh2WUpJyAOjPAPKogX2BbLsQ2XgGU/675St5u6ZuYs0F/vSpF+nQ3tdrInEuKvK/wWEh14O3UIay73VdfXOE1TchVfxoyKyxwAkm1MsJwzoM7TL9X0oh2ARsPTRBS1itMhEbkvEJhhogorFHTE1xH2NF4y4a7rOJrSS5N9v7slzwo2yZLy9RrDXVaDlRq0c4n7YWmgVV0qC91cPkDWsvncp9A8l7Ix1YQq+7YMIX+uu+QilZo4fXc1DRFshnaeE/LBPzD9hwh3T2idbz/45C4w0YP9LiFVArEMFAbEj61G4vMCuKWq6lFVahDsK8m8KnsRjug4Hg9kXK9+N3e55CrvGzbr/hUuzGOui1nFEGMmt9o8hA4+hHeGiownpVw5DbVNjyR+OaQDBlVFjMJG5vAnAhUudhRqxH72UuMYzjdDb82D7gNerLRlthFHbJsU6Mr9bxEs0DRITfxShrmTzA1gnCNLrVLzmAaTBdMrR3wmx4qk1ER4/3OQm1xxM/s6KsJVJQ9fSLzIOzbOSQHjEcjxrCnFCUczvhSeZPhbNE2Px+2BDjWodrMYYjqa3mj2tY5Ue2HK7SoWFEbvj2Yq63HlBCwgqdm/aOko8y1+f0QFjkCoTJcRFPSHbX8BurLa/g00pw5QXkAuWB0VDeIEg0cuMFqeA8CfByegGvktGpIh+CgtG4KPk0dvBUzhknYwASmfelC5zZTwo+XiTM2AKYJMxqiazmi6P/ltZgU/GPBuEunvyZVp4Gp2Frc3bahQE7f9OGGse1GvYCrDNy7fprB/AFEvN7Gl4+VUStPU8HzhEbf/UTDVxfCVq63GRcOfIAHbVNIWVzaEYGcT4l4vcX7EMJ/N6Y/H8m06+LUGSEDcGUUBsTP/YJZPIi5n/86FQDP6a0CiNkc3LMUUdiVcOXQOGoYepiqctxVGu96ICdTRCk130w1yqL0GlKJr0FF7ua10Wj9UrKrRdYmH9d7JY0QW7pmX6QN2Evt8lan+zxoVOi/dS+VbhC9CzSlmv98blXsv6WWXOy/TZRBru8h+APDC3iRwmwKMrhTT/oHRrdA48P7NPNM7NU2WyL4PLuWNN9FUZ5hG49RrgZdxFYiAbcYeTxOKSlFF0sso5do+Onkto3Lk1L67sIPD8aB9uPaT90JjfUtBoDs2fuTVRBEsPTVbeKyOtRVAt/rRIxS2BLc+DkHLICT488IDej8+MK82IgZ5WH2OLVwqFc0hgqN445+ns5M4VeJ/PZwVkgvMpRWUT/CuESUvqAdsLyJb59WxMkI1eQDs0r7Av1jeO4AO9geRpKdUq2eNpUzbuOaprwzRNAoMfhayyt/5yiZLavszwe+VxQK6vjpMlOX47jqkOkmBUpd8ZP7m18D7xaDFsW5Pnq3IqvCwBbYqvl2qZI1Wa/5vt8a4jSS+oAPek2/11dBOTeKFJSTrDZStpBoGahgFu6YQCHEqagb6UxZdJOgUR4w2F8/JzSshkgtQ1mShxObAi+CGBK/XqN7rcoA4uO08F3Nt6boMXMEjr9iexXLYKjbWZZbaIqVIMMMPKAYFcPGTBMrRY5NLwgMuoAA4FvNtfuBQeS64M2U8jjIlMpOEBY9bbOuSlgjpTj+3EEQTm7NidfrFJl69Smoz08XCeEz2SoFjBDvpPThkkU6F9EzANtBK+Zm1CDGCgsvqVLqlsP2cZ4gGFIc+tRmFtVihnQlqQM5t9ZuhiLXWJpKCDBq8/cqUJqVYvrQAEtFPSc1X8BNf2FHXOmSgUUspyY0EcMv5q4Tvnr3izYhgFiKWa/94AwdW7dYSWlskcO3NqLvPQQ3DM1g7d8AwiU0EvnVDUOWTVMAX1GF/f6wANIDA/H8DDereKwrkt08MK8ofLtcFL9tjLo9mH6lpL+B/Mh2NcuHDItv5/uFDT6JWzh/qurioTTVuMoQPgU5IT3DSRluOxVuQgaMsatcUijfUDuL0i/w9vH2VUHEIwKbyVgQug3lhkkpGDhEDqi3NIdrxJWnto4coeV1KLzSlGWlJU8c4BiEvznpiZIhdr5G6Evk+QZwHY4kfTRJOGOmjoFdatD58LPJUZLYmizYd2slL+0JrOxJ+hGT8h1Ri+l0+KHUAZDR1X6W8Q5Stj0QeoBekHLndBXWlTjOFqNLnmqaAGXG3SogCywkCH4FNrAvqEqpuaZiCz+IU70jMKQKubRB+z30Zgt3WuSOTV/UGVec+Kg+zk1U6pFvdmasfXvjedx6lOt/7Fyx/XzMh6Zk/XwV3C8VR6L/hU/V0bkjsFjUCIOt/Y6zeW8jjzLB1EG+ab3Wb7LyEeST9jzKoIJSHvgChPizzqv3DQY4VJlow8WCnZs+rVSCYIbbrp7G9IMSiFuYmCgTURttL4aWGQngmImi6dpHBFQoZW3AZfqAXAj4AFrCsr10z3/VhCbQsUJwpunqFaxkcw0290FaYhAVXFnQsUEiHo2xNyUqlsAxpJl4gwY4XY95SXjlvOqRS1Sc/v2mF2KiEdhq+FfL40gAcsaMmQfwssag6xHcmmZ4Kq9BcN00+qlZtuhziIgP/ETy2+YqTP80q4qOVR9Gfjh181o1iMA1EJhZbiTPjUkT4TADo10lzRrueIksZe6vUBjuYvA8BnO1OhOTqVERu4lOY5uDoc5X5hcRtxatkFLgZWv8T75hH4PkIHJ6EX2EetZddBfO9j1a2ZaYo2+/zHfovMeRoB3A48QwRspGEDRHeRmgtQYzXYbIl3QVOKoQ8LG+9LGrRG/X6/eI0RKSBnuFFkE8j0elLYAyCgLBqyvAB3NlFjpdq56VEVMYCgYiWo6TWxY4TupCu89iB8soh9f79jYVcT1rXQfXpak23oha1/qjwd63q+eVNNWoWiiqgshV4efQ6NfxDXG5hgJ3Fzxt/QOIvtWs9YxaFudyjtCfv6VdhgPRwMfF6Hlm7U9paXFjYALxiAsjx8cXO0kJtI5rW4kwHZwktGtMeHHujGA1G8qsJjhmoHcGJ26beoNnd9hcOoEVgd7fSMBN/kIs/hL8ECjZxcvrZk4GUQB+BSX0s+lycqxBJ+71K3AAmCkY7XfqMuIZhPWIPYPnKFwYT03uyqHfeYyhW9fVaaVwTypBiitD7pRolXC6RN20OkryS3UAnCGpZ5Bs4w5t05+bU2jAjmJPLuSVHMoH1+L9CBkMf+R84S8EOeuP1xuMIxuGqTzHMuDOM1S+cNeO/EiURAshzZdF6yCFUL5FGrrjjOe6glkH6HN2MFqv5MilIU5lbf701iPKmDNQnk0G7sOXlee9tsHicfQox7WI3+2Ytn3NXP40xCFZDdqSiWFVf58sWJBv6AOanHaiMGDX8Aa7RpdgRxXZhNDF3RI6ZK4QT6IAYKRyY9xibCdTTbSZUQM3FAX1nmAYJXE5G5tIfd4HEyY8p+B7wnozYxxxEfyx8exMKaStBdkPJuMJoFiO0NJsEv3AT4b9CwPN1uPYpkNJGuhS2xTnwkjbN3G3P/TxmPxA7IySeUSRdVR3olAU55OdRIbEj45FQmlSVwNYfpfhter3zIx9pNTrWMxoMzvAnYPciqzK1oZvz70RDiwdJUhxC4Bps3bF1lO8H9GGjbEjGliTjSVETU8Xl303o1Y288+VKDBh6ePPYE3gSFRwHfc1fuoSaxq1UbZ79ojzTtKqC7ZSFZRt8V97L+hbpscZ55T4VSLC8Gq6Vl2f64aBq1ONGjD6cTyQVZCov+GrBvBSJSqkatl60Ods3QxU5URELN36DYQacqDeJCiyMPQRh2JRxo1ZlzWTFIBPH6MFj4zClrRi9JHmqUPCIavpanoMH0wq/4iB8Phmn3m0y3XGTXWJsWMQEp+X8fz+VD4TOqJ54kA/dqv5zVd0MJ/PM53vXdLhEWSYoKbLL2p/oA5tztazbEQmMXtoOde5GZApTQ1sGOhEC4Yr+mJiAj/pXSA089nyY48cinpiL4G01EAL5h/pDO7gAFc/nY27Yb1GnfHBjVh5xF56Da5FkQ+PRBmwGGbQFy5plDMLjR+hZSqiDOVkUaFZSx4fL2Ap+UmaEl8Jv9kjBYE8XaOxQM3FSCrnsG7oX4E0Yuqey84mNn3cyjAFbUP1RbbucoulNtlKt/Cqc7R5D0yXEIbmGOYMkKeXrl409Qyai7bWbbjfAQif+w5cCsEaYtagcnYNK+FKgjr7FKLaJoP7AfgJSgIC+P34Fq483QRwBF7CNA6ijVjNEC5yCv4LccuF00xVp9fiNgw55yzZ3tfGVSH92F9nHnFQ7tJjZkrKl7JnGP8wVJ70X8n963DgmtgK1Ndn/q+aAwPiSjunhlEQBLPLpluEUCDV9IPGLPev6z9Eo4Zm9Poc5nZS0lLSUZe5OO/RzebRuvd7IHvb0BdzVBZM/zGbSYHWRrbWzzEXOfgy1Ch+IxYUTkIWEgYS4ScxsoX6CPl/5krO4R/Wp2VyAACAAxKf770GIVDV+y6kVEp7LqHaj9nOe97x3g38Vt6s3OTJViNOcV15iu2Zb57Q/n8Pk/XZ+nsGAvN2XdZiU8L7g92Yb0b1CL9B0+2GkCq4if3jN18eupwA8pINW/jpGqcqx1KP81FCwtuXu10bIodQC+FcXTmoaBIBTIri9aZcrdAJ6daBHdYkwCeMRd3PdgDON4jBM5yUFBvyBl5aYNPig2GEJqXNpLPgOmOWyqUljAi04yXNSW8xUlsLcwyKswCW0NfBpg61JWa9QhhhDafEv6SapDedYLdTcCP3UGc+Q9eATbgidEnRY5+FpuSkbCg5JM13hwsi/GP0orbDJj/1HzPGs908qXo3BHWCA30ADCzz009ZvaPLn9CzFC+BrKvdKRDwLfDywF9qwAyZayytmAkE3G4XkomcTMOUF8+9ma/BtplM+ho+FsvasXjWoRPoxVKhFw65QE8bcTC4tW9pGFxDUSBXKsP8saCD+s+l+MLfWG/xZuinC3DnOg3vTWpb5AOpnwIIak+wbjXQZAGOpKQqmB6jn38EgdQj9OSUsBaXE7dQBc/2oH0hTghrjd9NOLVfS4x7uW5AyDSIOafTBd62fxyxkavL/kw0v19zCz1Jpm1nC5eb11eYBFzZDn/uJ+aRbYdhooMRhO+yW8KUtPCUMGuKZhqI6LH5qbZMIaKsIkwMguGGlj/8dHFcVet9NLzsujxz6nuicSKUHi/h0C0ESedPps8tRhF4k7vL3WQJvLTXOxZBg/yQNTj+m13lWBCGK18r85YSzNTU7lZ7HgYsrCAZuu67AN53cERTB4+8O8flECkijz9gPLYFM+a4bKB55+g3igXSeliYUJpOqWnB98amjSXVTHIZjcCGKIRDjPbnIHajovRDPhdvho5Q+XN/oIW+3YTjA3LISRRptgUo6cHlQNxQ9228aQD+Vy0/Xvpzq1fNZ38r8dagGgUd5+gf+vodWA3CFmLPMbflBg04bOTSGBwMX3R3jFWiT7zg6HOfTrYrllVEtk9QAAGI65Wmgofh+waMb+feidFdYXT5STiq8MNqj7JLV7r2wbhSQMsYhhTBHO/Ms0W1Mu4zh8qz+Yyy2zx4nWS06bK+y4Ezset7P5ULG00vPpUqVjVJJkXKJahaQ6s9tUAbRmnVZcSgx6Cc4HZYerrBeF6G9JIYjLICGQJnY7ivA9iSxkbQ4wx2kilQgxGZXz4lhVLkVU5IGHOFG1Rr2CIaYB1YkIUcdjMBmgryziBeCUZVmyIx2V4EYo0TPBTVx6UDeti0H31T7TPadWAo6n7/n6FXk66iblCVEqfIfFnRKiajP+9SnAoGl+1A4G4H6cTkOn3TsmDjsIkMR4KyfGMPpnS1MjbhZ22XEXHnkXIDnmOayaXcZtEuCJzNKuoI4TIEaICAFv2aoR5L7H8zpjUBqxIWEK+jTvJyctu2OjOFpE2lD6CSYhwsMNEPPnOd8tJ2EsiPsU7408ICu+wBhz9R8LKlFO+91pDyw2FSwq9EGPT67Cpk3sGasuRGabDsOWN7zgnEcSYuETOH5a8I8H1GLtR0gyIKxSJZjRo28bdxa0dMpE21DQLIYvYdFPYPB6d8E7a4aZ/dFA6H+By8X7iyip5R+baTyyQ1KeDF1ohj93HFJuCvekqS7eg61pQkZfko2TtQ7ipX8UrV/onzUZg0jxQZ8XU2LCWgg5xqeShQ2Mtdr7NFXIMrKtgpQ2cy0zrqgdLV3RGaXuzAX/Wnp8JWM7IzcfNwC+nKUzuX79yfi40trf34eMJvE8fzIORsEHrv06BTvq9ntIvxey8oWEhpoLhgyNZC9MrW/Px0LIxIdohStGfQZSNtAhWFwAk7S5B1jXP5GDMskQG0lHpF9AO6LS7V+OwmnMIhuLNlhsbbFhvImxzSVjZSaek32HmDO5sAMKogSmWACBlwGd0XMBWFDGm/6+ivTrixwla0hK5KnF4TrIr2vBJSj0ociNPT9BxgD0drDPHylVB24SLeiA6pnAeFjWdjONQnR6iDatRgJcY9dr8otq4sNHPQrWj29lW8+Ir/k8Q1vKDb8O8NfJcMmWsPw6lWm7ubR7jIYbv42xpdSK+PCo5Tq3g5EAfdONnohkFRTX6das6b12Wyuy4=
*/