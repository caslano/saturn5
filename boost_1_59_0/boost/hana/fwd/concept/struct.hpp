/*!
@file
Forward declares `boost::hana::Struct`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CONCEPT_STRUCT_HPP
#define BOOST_HANA_FWD_CONCEPT_STRUCT_HPP

#include <boost/hana/config.hpp>


namespace boost { namespace hana {
    //! @ingroup group-concepts
    //! @defgroup group-Struct Struct
    //! The `Struct` concept represents `struct`-like user-defined types.
    //!
    //! The `Struct` concept allows restricted compile-time reflection over
    //! user-defined types. In particular, it allows accessing the names of
    //! the members of a user-defined type, and also the value of those
    //! members. `Struct`s can also be folded, searched and converted to
    //! some types of containers, where more advanced transformations can
    //! be performed.
    //!
    //! While all types can _in theory_ be made `Struct`s, only a subset of
    //! them are actually interesting to see as such. More precisely, it is
    //! only interesting to make a type a `Struct` when it is conceptually
    //! a C++ `struct`, i.e. a mostly dumb aggregate of named data. The way
    //! this data is accessed is mostly unimportant to the `Struct` concept;
    //! it could be through getters and setters, through public members,
    //! through non-member functions or it could even be generated on-the-fly.
    //! The important part, which is made precise below, is that those accessor
    //! methods should be move-independent.
    //!
    //! Another way to see a `Struct` is as a map where the keys are the names
    //! of the members and the values are the values of those members. However,
    //! there are subtle differences like the fact that one can't add a member
    //! to a `Struct`, and also that the order of the members inside a `Struct`
    //! plays a role in determining the equality of `Struct`s, which is not
    //! the case for maps.
    //!
    //!
    //! Minimal complete definition
    //! ---------------------------
    //! `accessors`
    //!
    //! A model of `Struct` is created by specifying a sequence of key/value
    //! pairs with the `accessors` function. The first element of a pair in
    //! this sequence represents the "name" of a member of the `Struct`, while
    //! the second element is a function which retrieves this member from an
    //! object. The "names" do not have to be in any special form; they just
    //! have to be compile-time `Comparable`. For example, it is common to
    //! provide "names" that are `hana::string`s representing the actual names
    //! of the members, but one could provide `hana::integral_constant`s just
    //! as well. The values must be functions which, when given an object,
    //! retrieve the appropriate member from it.
    //!
    //! There are several ways of providing the `accessors` method, some of
    //! which are more flexible and others which are more convenient. First,
    //! one can define it through tag-dispatching, as usual.
    //! @snippet example/struct.mcd.tag_dispatching.cpp main
    //!
    //! Secondly, it is possible to provide a nested `hana_accessors_impl`
    //! type, which should be equivalent to a specialization of
    //! `accessors_impl` for tag-dispatching. However, for a type `S`, this
    //! technique only works when the data type of `S` is `S` itself, which
    //! is the case unless you explicitly asked for something else.
    //! @snippet example/struct.mcd.nested.cpp main
    //!
    //! Finally, the most convenient (but least flexible) option is to use
    //! the `BOOST_HANA_DEFINE_STRUCT`, the `BOOST_HANA_ADAPT_STRUCT` or the
    //! `BOOST_HANA_ADAPT_ADT` macro, which provide a minimal syntactic
    //! overhead. See the documentation of these macros for details on how
    //! to use them.
    //!
    //! Also note that it is not important that the accessor functions retrieve
    //! an actual member of the struct (e.g. `x.member`). Indeed, an accessor
    //! function could call a custom getter or even compute the value of the
    //! member on the fly:
    //! @snippet example/struct.custom_accessor.cpp main
    //!
    //! The only important thing is that the accessor functions are
    //! move-independent, a notion which is defined below.
    //!
    //!
    //! @anchor move-independence
    //! Move-independence
    //! -----------------
    //! The notion of move-independence presented here defines rigorously
    //! when it is legitimate to "double-move" from an object.
    //!
    //! A collection of functions `f1, ..., fn` sharing the same domain is
    //! said to be _move-independent_ if for every fresh (not moved-from)
    //! object `x` in the domain, any permutation of the following statements
    //! is valid and leaves the `zk` objects in a fresh (not moved-from) state:
    //! @code
    //!     auto z1 = f1(std::move(x));
    //!     ...
    //!     auto zn = fn(std::move(x));
    //! @endcode
    //!
    //! @note
    //! In the special case where some functions return objects that can't be
    //! bound to with `auto zk =` (like `void` or a non-movable, non-copyable
    //! type), just pretend the return value is ignored.
    //!
    //! Intuitively, this ensures that we can treat `f1, ..., fn` as
    //! "accessors" that decompose `x` into independent subobjects, and
    //! that do so without moving from `x` more than that subobject. This
    //! is important because it allows us to optimally decompose `Struct`s
    //! into their subparts inside the library.
    //!
    //!
    //! Laws
    //! ----
    //! For any `Struct` `S`, the accessors in the `accessors<S>()` sequence
    //! must be move-independent, as defined above.
    //!
    //!
    //! Refined concepts
    //! ----------------
    //! 1. `Comparable` (free model)\n
    //! `Struct`s are required to be `Comparable`. Specifically, two `Struct`s
    //! of the same data type `S` must be equal if and only if all of their
    //! members are equal. By default, a model of `Comparable` doing just that
    //! is provided for models of `Struct`. In particular, note that the
    //! comparison of the members is made in the same order as they appear in
    //! the `hana::members` sequence.
    //! @include example/struct/comparable.cpp
    //!
    //! 2. `Foldable` (free model)\n
    //! A `Struct` can be folded by considering it as a list of pairs each
    //! containing the name of a member and the value associated to that
    //! member, in the same order as they appear in the `hana::members`
    //! sequence. By default, a model of `Foldable` doing just that is
    //! provided for models of the `Struct` concept.
    //! @include example/struct/foldable.cpp
    //! Being a model of `Foldable` makes it possible to turn a `Struct`
    //! into basically any `Sequence`, but also into a `hana::map` by simply
    //! using the `to<...>` function!
    //! @include example/struct/to.cpp
    //!
    //! 3. `Searchable` (free model)\n
    //! A `Struct` can be searched by considering it as a map where the keys
    //! are the names of the members of the `Struct`, and the values are the
    //! members associated to those names. By default, a model of `Searchable`
    //! is provided for any model of the `Struct` concept.
    //! @include example/struct/searchable.cpp
    template <typename S>
    struct Struct;
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_CONCEPT_STRUCT_HPP

/* struct.hpp
4OcEpRcxdHkGLzRNrJsRngEhT36JA9FIZRris4AoFttElsFMb85RS0N5gtigZtnWNGW2CQzEcZcd+3/eREKWsxUJ4ld2T74ezE/hEfQtB8qN6teAlHnW2QYLp6G0tgSF3iDu/1GDMn7sBfEZQM4TA+wIBUtfxV0iY15syXxfPLnmPDKV+aHl1PKrM70an5z7N4HTaZB83/DB4EoWS2iQ07L0LTOKvkyv+I10K+uFnEkkWe6DTmP44BzmL6OXE3qT5Tdg6aPc9s1jp0HrNbMlYwYNcd8EhJolhxW7DydW6h17pfXcm70uTC/OETXM3uQHdujFRWnui45rpQCGPcWSN5+rSe5cJ3vBhuYb9PxkK3b4lHSCO8oubBiKt6sXS9OkP/cylwZkXWDrKTQuSYKokkmWr2fRP5OF/FQhP13IN8PIWNqIyhUWpUmL5ymmIG5DOfjE9yX9JZmkI5lYHJ8fPvuA50tYrvfl43zNX/jymUXoS2K/+cnto8kyzU/dRZeoeA1rupJj9pOIC9OQCYFFuBdLzNDuPJR7QbqwcSaLvsUCib1ahF/PJBYdrE6orBcqG4XKJqGyWahsESqPC5VtQuUZobIdoRsrWSiNym50FJUB8X0WXyI43VPnmempc9VrZzi7pzjrnON4PHlhsmBZNBQS/+Q18oxQjvAqYo6xmOXrp6z01DlH3OfqMy7rEVuFjYixZblQoRM8gBEv1BrhArLSXefU2Jy9gnsuvncv0wlu9r1byGF9zbGPLU0VycRP5gJPnbEa25vv05y2NJX/1aN3s37Dg9hY4kxDXeZJYUs24mRV/xWnRB4Wt7DQaDPH1eUctAkFqx2mnNOamePqXQ1aG71d7fxS3IKiyjnIzrPR0HthyyNM4h23iltQlh55kwQLaCaqBL1L3OJgO0Q0IgO9z+JBOZd7Rc5GlYFtlvCwivDweGPImXhWcAMwp773tOCez2gC0udGrLJgMLzJh6XEq9DSanzWRMrWM31jncDif4j8V8VWXjAnYVMLnqlwlL2VhkskgEG5SqxX8yrpHBlarQ7yQw2CDNzGo8Z5tDmWFuMzmLbKPCtsyQWhMeHzalhdihvBfZBxqX4VEKTgWA1lHrO0LEsQW3g8tczDzL491m5xI4Fl97qOBDNZ1DLNAfFVFrvkUMVt99HPLZ2jefySV5FTRFdhN+L3NfWWA8uS7ss8YDlU/pHoZvuaVbLdKrCQZpqWNf1bsXq0dgzbx4Mm4Jl0QGTcUVXxAkSgASGbExBM/CNPg+p1hvgGCr9mIwuzV8fqoNrDfK49LHe+Y5LIjloQHxgUv8nsq96Yx4oBIN6gJjMgJHuFlV5tp05uC9kiE2iPdvQUN4sj9+x+tgXosbAc1Oy/raHazcgwGfDo14huiIbFWz7ygBuU6zvvF3EapcVbMZZZI9cfXH1u62rvQzJvgc4bSB8XpGKtDJHkvEXyh4JkcarOxahpxVeZ/9+hzMNyqYkHxMPHJAsTpoockce703tD9QsCwp2eSSyOrfAEXPKPcGAqf06L1e0DctW6Dzh0Od2tkvuAM8BSIOof5XSHShgIM25+38L3CzluymQBCMOAtqFvzg6B4bjegICo5LJi8mZ0z70UajMuJu3a+2Xd0Wp8ZpB1/1PcaOWOUXARSsSKz9CeoEJjeC6OjTew/JxuL9OWXVMkR04ItrIoatht6rEOyse+sGkSOxvVlCTjBCFV2TVl18ymCpGc/fxsyXRX8BKNgKaltveNMXVe5woOOODu5bpL5dTT2zp6+xYaIEvSbA8d2Tg0bFbwsxQnZV6WpeQIlkxFS2tpVLx0Mn7U7FyygjR6b5ZO9Mnc4XDRY8yzOnnKZGPVabZWlAqHED6fZsLe8aW7PgMV+plX5NH+kghQp1EkPTdExHkLCdkUtXPkmkodElr+Y7E4Q5xmts9hM2ehmQmURRrWGorN9tmU+3X9Y0xYCw1nmIrHeWMEwGP9cvFEQQ06UHgzQ19DGFFQvOAzCKrzqhCOrv9bCpzK26cayc/G86kT0dcmZEhjTD5VRmCMKTZep+w/WZgt5uuLxdJJfMBkObxMI5ZmifmmzJOWNtJ3ZKY6DK5K3QBiTrGOXL0oObOBTAayr9H5F9PQf+rsYAs28FunYtIqP1ssCRTTgOnSeB4pwZ6lXhjQNMDU2+/8N5FGSQWDU+yTnBqhcBKl/I9JbD0lRsnQO/VCFly4ICDM0gvWbMzmxJ+vFm0ZYlF6WRoN6tnKNqUwvqZAV1Oir7aZSIaqi66i9sGNdsGWLBSlKu01nOcFi7Q0jcxR0YgTp6xarIEWpmMoap+EcCmFOArE0lqRmHnogc5EsTAr8xDiAOpo8Gdcq9FSp8Z7rKDZU3e9wWTcYzPBx56Ss+l8KqZNctkyXFvFvfxUcg6Pw32NVRc07LDpiQXdxj1QO+0MRF0QcDXoRsKCkkITcm3l74h6dwa125txMEqPmKvzaJsoOfWxRwdxyTxp3KPjO5OSRZuWQBgH8OTxF7Fkei56TY7rXeeMmBgskMQHtIJN68Okhsp/B0Fc9OY6x4L5PIkIePRNnIb/avYt3Vjl1GAMBEPQ/w2G2MwXgDI2mXHNczTh786RmpgukCg3yIntKlaKqSwPmshSnMLtNZ4aQpL8g8svfjnpfTjVWcWijVA5Gauwj5U3WDKGm6h1+xcPVyT6v5tJNZWBXCQ+FXQC9Zb0ykotUCI783qIYxOWYgs6sFTeofFarBnlF3kuXCu0lPgsOZ45802ttNizSNFRoyrMsHgdY8VWSwtJ9n4bSbY1C14dXTgyUrBPwolH0ia4J1AzoHGKNRvTPi0VSYgeFNEQQPB6Tu2aONSQqrFqoVreQyPVjAzmScGCrupR9HB/KNuFWc4RTK1IQZuWse3GfCKLT/H38N3e/4/h+4987w8c00bdT1zL/MrB65gKeBrnB5R9wxRWt2BNF0rThFlazDY0ZRqFJPUsHTElzeLHvIUPdx3kkDTC4qehKqBZFsYpMMKCtpMEjR2M1C0UsrTytWWXOtdHJd/5smsgadkYZgep87pdnbqJCIalKwIvDX2scLCKZs923AFVXJgObM45qb+TmRMEo3oRB9/Qp2S9x4fTk1XRTKj9Oqqxskv+L6ldvJZiMB2i/23XGkymsQbTHvq/NtVg0l1nMN1DSvIP9P/q9aGVjNB6X4aYa57NO25S06TMqbKmCjpxhCugdSS6AolOk2jXi/kZ4iyzfMa0654RzlE4/skn1bGpqgzBOgl9hnVyyIUxjV/SVWEHOPwFW8L9z5A/ox3dAMinl+ViVSlk59Doal6GmJ++FMZ8mY6xSD2TGRP44qwMcV7IBFjEJv85iWJGgQFm4Ehc0W4eYp3Rk60Uk4xVoMNG4ayceqFQZl4KYO+teGBovnQq66/s6XKXlYSFEapZa7ZQ0CMWThJKBoWFXYgA10Ty7JXl2YuDWSTWX50aEe5/SGSYrUv9VvstBpNrQFPxfe5b/RkBTSyh1how7rkKpjCpqdAR9Qu7Ru9naOoSzGwSVvkhTKImia2uj9StfsGeyiIqLBnBKOu+Q5RJMx0mCK+kOSbRmHdhF5+gI3T/veAnr73IU3LGU9DmyTsufQ1X3oJ2EU4obWQIHp9TNJtqd0yAux5Z2RFdiwnN++ighkgzcqyP+4oqh9LAu7xB9hrdhv8MHAwH0isycw5OKegxVs0ZwTzEjXuuDhb0BGE06eQ8jt7PcpRe/p7Y1Nuy5hy2I3olGuMY3ZNHsJOFC7VsyXjQ0uQwigu72PnIwgj/E/BctKbSGyy9uNqT6N2/Jsohp6o2sTuJdBpzZ7VnTSnpdt4k67ImRypVV4WOKovqqDMps1XcL5RIJDA/YWerdM8mgZZMKBQYIqTPJjF/kW4aeY0SWzNbZhB052hUM1ayJRrfWrOm5HU7b6C2QLotmUArkjKbPLODJAz2rMwWUD9qrHqS8UzNvSdUtXk4midR9CIAJvUu3mUa3CGWU4C0AzzOPk9mzlRq6sqoa8rrnkhS1aifaNUa3cu0yFpq76kbjro+ShKu9f+rFsU+psISGp/zwjAnDitbUYI1pvydW4L34mQM17kJVO+uvnHGtdmsjhNd7RNcAXq8EZmYl+6p0iUw366MMm0RNwUFKzxcqs5rmaCMwdRW5xgIBfdh9o2A4uVjvUKt1z/K5dVOKdRVONEMJrPxPufXoeX8MoG5LL8a6roLdWKy5zHqvcVCPcSAxixyK1PbdTwhLqGUHBdSSrRcrL0GU0tWXcWtkfMfREzPiZXqfVpRxakQWHkH6ZI5pAo9hckeq2l20RzxQ26VSa9d4FGOTIhydD/qhNQBO+/LNyKRZ1Zs9Z5PdH00gUrVs24Uyo14MLqeU8vlQSz8TtYPYqHJcrLCEll/izVR5UEwwxSJ5WT5YcoBjBnRnnxzkyf5kHHPDLU4R8uczJpd/aaKdGgEKixoLUrPqhOS14TKi52L4uq/mgZTeV1J/NiHGV9S151zkN4aN3g9+nc0zGlRguVTQHqvhdi9ix+6HuT8epjvJJlePTK/EabX6P1h0R+0LGyh+ivoOCbhrJJkxvXNLeoS6ZikKegAjzrGoFZskYuvfYKnKoGJXYmkaaUMWFqMaydqUFDNJufVcKN96nqkbtWL06sHOxNy6qnKBG3NfcECydkjFOq4+BHJJq8/kaqDkVSzGrHqjE/9HNMyhWYCmI2dx56CRrp2sHovkGaHkObcR2izEzH4LSIxsCbzvdQSX6nqgGaU7uzmUpEOqTgKYxROjY2UXRplS0Wz52D/w5chz6yqD+BDRGwR46xzQ5NC/DCc3Scft4fDga3pOA6qNE1syRzLDAedep4OZ0SRHTKJdLZ4RNrEiOJILaMb83+sp5YLXRpNKh2nAJPxMRbuNejEBlknFhDtaczBPKofc61KxfHB4imjGxGPeCcpjmFm2O19zAxjxgyYKukR5g2ZYWJJt2yJvd0da4nJ+eCQNPrmVllR58Gywc6XCYTarG+EbIDlDmC5Px3mdcOlsAH260hCKIwQraLOqjBqOqGSgTSfTwCxBakemdsQOPFc5J/FdsUGQoaZLlTGKFoqYpk91jH0/lWRmxKMGQR7yCYb9CNmUDj9QdiOcepOpktsl10C0RcVRF0Dl5zXRttdnCYPTs/opYEe2SVKesUgVxzNI8H5BSbcem4HwegLl0iY3fZ+uFqEi4dqk1diEnFJFTn4BVt8UnAZKbERXA7isGKyjQvTiv0fX2LnbIXfUCG1XEIhJTGjNtzlbvkCDLLOtqB7SmE2DvRkWbWnDxnKrZRbI3WOyG3hpCJp6RcKo32Ejke8VVSK2r8ELAT/R5rBNHOcwdSA//EG09IJBlNJusH0/E0Gk4MMsib6t5sNpoME56f/7xFc9c1DNjMzVi/k1EvHepjhG9FWreaIB1ZtfLopFZZmaAYEK3AHLX2OfxLz08hQyBBmJSO886xU0abn52Qlke09L80ulidTKo9SKqU59YsaanEw3qKGZjKLvyda08ikvsO1yqxyZHB/yyTxgPRjZoqnkX1DHVWoLrghnlPPCTB/1tnEAzbXroCazE+D7nkUCvReuaMRVaTqK3XaYuNGr/11TJx6Hg+6Ph0QnDpXwGBcO0oDI9PtuM1gIkUCdC2wxgbzdeKsNBuVtnFPgnCfNphkNopnp+ocEyg/vgQD84CnwVfqDmqRvlwtekY/wm8gmryNemkt4nnZTMuu9qkMXBg3EKT/eWz+4VM6PLmNpIUoMaQkJhn36HJJ9olErtbbzvZFDOYc3TuBwHsviGfdRx0pSDVEcSUo2ojYxbzBdKP7Jzx5eXblLmbOpIkPJGNPmrpHjl0IKU9V5CGX6QL/KDXbkJcgnnUNkK69JKOfFR9P9tynlXZ9CVWbhmgbolPnGO1TYSXSf5yNZXVD+XkbeEY5RzDQ8tO8H6UipuWstGCSeNanHjkEvEktlzUHHgXgcya1DULDgBNGDQH/NB5lnZoo53Ng1egh4HtigcOQNq141mLT8SjC4cJcTIWJcrmf1SXqQAUJefosNbXSH3GRZdpnVppPnTCUEkogSl687amIJhDKg2YI+N9VcfJgisyDNgTsWHX5zCaGAUuGzaiuVJiV/SM+gcdGGjwHSgmeyyUYQhCZT6xTD2VYz7+qQzTo/lIIcgiHbN47bjWYttB/6URqUfRfS//n6H8stTB1hsH0KP0/T/8++u+h/1n0/ke3GUwR54Ngadr42rvev5rcF51JizxWdSk/uppsj6ogt+K4fdmwZmBXikpVnliLS2absNDkCpiM6/7APLm857Xiqd7TiJzRwM/r2DNec9i4p1St6WPXBPmqka9a+ZooX0fI1yT5qpOvI+XrKPk6Wr7q5atBvo6Rr0ZcNX2uA6YZRvdyFuwIDr2jjXuu1Ryyavpszq9rH1+dtBp7b40PHzWqgkHNIf7ms6E3/TC9RrIFux95202LRnvjxOsWC/TGPxfgjDpPnh6bx3b8YDDsusv2dy6/dVCx39MXVO7/PKF4dnXp4Bm2f8LQAdZG9zhsBNB68gJFdqktR97oxr4wh6G8wNQJRvdX2CE/KBrd59lW+X6d0Y3jmy7mDbQb3e/D4WqEXXqJ06WXGMw4srFyY5c23DQYNL7WxJ0JQBa+YPR+pYKL33BqOscP2OHZ0qobCWtPGMv55HrqS27g7pI/UX5zfAJpJWST4y6e5H1RyHfL543fwGnfNAx+giO5LMEufTyeMcYaQ4T/pR3bZcf2sY0OZClYzYI1Ay48zH/ZaoLnBTwwwv0pdtKNKJ5dJBUTPWhrHSnkH8zzWPXSLwNw6bHBkcWamnOQbtPhbGby2G04Q7YwTXi6CG+enolf+BHx8y3l/cUWMR/Had8sztIxbx9Xg6149jwymbphsF90/mCR7G6DqSeduFyb2b3mGwAuS2JOO51a6qtPi2PtmpY5wJVuSWTeLerlOKtokfCYSZivj4nI51lrYy4ka8GUPee0kJ/qy08DPXk8+AuTymmcJzFvAR5Y13lDmcqTr5duDITMfscYqo4bpuSnLW+BSmoQl6cKryGvltdA1nk+5CjE7JlusQ/h6WT98BtAiM8COvOQ5Uh5gnhE/SxKTtOaeUFgXx0jpRK+Tt66qDTuedXzRJxBQHTZseFrgV5xldgrFTKPHudP8dE5KDK6Fu8yQ6ZXfFd6nHsRzXefdswdit/GCkJk3Gd2W74qhyMUnHaKpPdIbNROvdo5qGbZUr8GclTCmWeJw79w56G3hnyGMKUX93x15g2Jqb1VenfQca20gtT0vGJpzc2ym+Uw/kM4RQz+Q8lSUlDhP0Rjx2KxVDfPJWmL7DlBqfaGkC/yjbzl+HijZIeeBxwJOcFiu/QrDiT6FkX7pxaTGGDL0Zc47Rirt6sn32l0H2KTA7rJRnc9j1BU9QrG1KWpU0rTcZJyenqWwSSUZkwpNTuTfFZzNj3CXi1ML0sdmiNNszQ4FgjzkzH0+6HeMlCpJwuy90Nfrp6tmc0KuPqSlhfj65Mm2Jbvyt42srXa27rm3C7qiWaT+fnd85jgToPpfj81HKdRKvqabXwbDLItXQQS7MELJvJSDv/4Df9Id/1B5c4vpTxF+wiiqj2L9MJa1oSZkMhugk/2yx5W
*/