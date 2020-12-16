/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BOOST_TUPLE_ITERATOR_09262006_1851)
#define FUSION_BOOST_TUPLE_ITERATOR_09262006_1851

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/iterator_facade.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/tuple/tuple.hpp>

namespace boost { namespace fusion
{
    struct forward_traversal_tag;

    namespace detail
    {
        template <typename T>
        struct boost_tuple_is_empty : mpl::false_ {};

        template <>
        struct boost_tuple_is_empty<tuples::null_type> : mpl::true_ {};

        template <>
        struct boost_tuple_is_empty<tuples::null_type const> : mpl::true_ {};

        template <>
        struct boost_tuple_is_empty<tuples::tuple<> > : mpl::true_ {};

        template <>
        struct boost_tuple_is_empty<tuples::tuple<> const> : mpl::true_ {};
    }

    template <typename Cons>
    struct boost_tuple_iterator_identity;

    template <typename Cons = tuples::null_type>
    struct boost_tuple_iterator
        : iterator_facade<boost_tuple_iterator<Cons>, forward_traversal_tag>
    {
        typedef Cons cons_type;

        typedef boost_tuple_iterator_identity<
            typename add_const<Cons>::type> identity;

        BOOST_FUSION_GPU_ENABLED
        explicit boost_tuple_iterator(Cons& in_cons)
            : cons(in_cons) {}
        Cons& cons;

        template <typename Iterator>
        struct value_of : mpl::identity<typename Iterator::cons_type::head_type> {};

        template <typename Iterator>
        struct deref
        {
            typedef typename value_of<Iterator>::type element;

            typedef typename
                mpl::if_<
                    is_const<typename Iterator::cons_type>
                  , typename tuples::access_traits<element>::const_type
                  , typename tuples::access_traits<element>::non_const_type
                >::type
            type;

            BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& iter)
            {
                return iter.cons.get_head();
            }
        };

        template <typename Iterator>
        struct next
        {
            typedef typename Iterator::cons_type cons_type;
            typedef typename cons_type::tail_type tail_type;

            typedef boost_tuple_iterator<
                typename mpl::eval_if<
                    is_const<cons_type>
                  , add_const<tail_type>
                  , mpl::identity<tail_type>
                >::type>
            type;

            BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& iter)
            {
                return type(iter.cons.get_tail());
            }
        };

        template <typename I1, typename I2>
        struct distance;

        // detail
        template <typename I1, typename I2>
        struct lazy_next_distance
        {
            typedef
                typename mpl::plus<
                    mpl::int_<1>,
                    typename distance<
                        typename next<I1>::type,
                        I2
                    >::type
                >::type type;
        };

        template <typename I1, typename I2>
        struct distance
        {
            typedef typename mpl::eval_if<
                boost::is_same<I1, I2>,
                mpl::int_<0>,
                lazy_next_distance<I1, I2>
            >::type type;

            BOOST_FUSION_GPU_ENABLED
            static type
            call(I1 const&, I2 const&)
            {
                return type();
            }
        };

        template <typename I1, typename I2>
        struct equal_to
            : is_same<typename I1::identity, typename I2::identity>
        {};

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(boost_tuple_iterator& operator= (boost_tuple_iterator const&))
    };

    template <typename Null>
    struct boost_tuple_null_iterator
        : iterator_facade<boost_tuple_iterator<Null>, forward_traversal_tag>
    {
        typedef Null cons_type;

        typedef boost_tuple_iterator_identity<
            typename add_const<Null>::type> identity;

        template <typename I1, typename I2>
        struct equal_to
            : mpl::or_<
                is_same<I1, I2>
              , mpl::and_<
                    detail::boost_tuple_is_empty<typename I1::cons_type>
                  , detail::boost_tuple_is_empty<typename I2::cons_type>
                >
            >
        {};
    };

    template <>
    struct boost_tuple_iterator<tuples::null_type>
        : boost_tuple_null_iterator<tuples::null_type>
    {
        template <typename Cons>
        BOOST_FUSION_GPU_ENABLED
        explicit boost_tuple_iterator(Cons const&) {}
    };

    template <>
    struct boost_tuple_iterator<tuples::null_type const>
        : boost_tuple_null_iterator<tuples::null_type const>
    {
        template <typename Cons>
        BOOST_FUSION_GPU_ENABLED
        explicit boost_tuple_iterator(Cons const&) {}
    };

    template <>
    struct boost_tuple_iterator<tuples::tuple<> >
        : boost_tuple_null_iterator<tuples::tuple<> >
    {
        template <typename Cons>
        BOOST_FUSION_GPU_ENABLED
        explicit boost_tuple_iterator(Cons const&) {}
    };

    template <>
    struct boost_tuple_iterator<tuples::tuple<> const>
        : boost_tuple_null_iterator<tuples::tuple<> const>
    {
        template <typename Cons>
        BOOST_FUSION_GPU_ENABLED
        explicit boost_tuple_iterator(Cons const&) {}
    };
}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename Cons>
    struct iterator_traits< ::boost::fusion::boost_tuple_iterator<Cons> >
    { };
}
#endif

#endif



/* boost_tuple_iterator.hpp
c4G/MLwOn/2IPk+sM98cgd/VR5wcWWcav1SHr4mw5vALW+pMArFzcp1pOq0OnwWJ3E6vMyedCUacGV1nOt06fG8GfU6vM89cXmdabHxdnRnQnDAZxCU3Ye6cl8DnSmKOCxP4PmrC5Oy4VyTMpjcS+F4O5tJQb379gXqTsv0n683h/etNs83noHrzZajVtoFP+1A9Pk8S84XP/XA9PisS/QyoN7dAeTsu/OBD6o2POA2PHlpvAhvDJ0LtNgf4dVCHnSP8lMPqjYs4hL8MFey4A+vN56CinSP856l649l+BtWbyVCX7Qd+CxTafODPQyXE5i8UnX2clOMax6+yaedt55mZZyhtNSWELZNWLywNFmExsSh1mFj0sjFpETambFrZmLTVpsWUdfSyMWX1ZmPSysbSpHUqrUzaarExURTJ+V5//D7fb/e5n/u+nuu+n+m8fM45l1qkH2nT+XASSet8uIqc0PnwCJHVzB/IfJKJB+AXZAiehtfnWsSHh6D1Mvqjc+BmYugceN4gi3TRcdhM+uIy2CJbSEB9iEXMy+mn+hUWqSRBPAH/ISPxYJ5F5pBxeAx+cqVFQrhxFT0mYVyGWWQEmYqH4Q4S0Rpg9CbOSGu4BdfgcVh+G/3EJUj9I+i57gUvHEVvcd9oi9x1P3Xj/iJ6MMEi7XhkIvVM5s9rqGGKRWZM5WwYTz1FjdMs0ofx4LOs+ZxFsvEAnERi+ix8hyzTGuBeUoUbEe7MbIvkMN83x8K3Sn/wGOzxCv3RdeCZ83h3XCp59/n0R8cX0Lc3eAaPxyzywxLqwP1LLbKUGO/TTzjlLXqla8I3llmkHk8tZ/8VFqnGk3DiSu6GzoFv11qkBk/DF9/lnqjDeR+wn+67jj6TFC7rLdJpg0XK9N3hxHqLNOicTRa54iOL1OER6N3CvaKeQAPjn1qkQsdh/23cW333zy3S7QuL1OIheGkTdxIPw6ov6TnPpuHr33Cv8Ogu7v9u+oaH9rDPdxbJxZP7LHLL9xbJV4c9UxbJ033he6RA14Ez91ukEE/Ahw5ZZIyueZjekmJc2izyACnCI/ArUqrPwqt+tEiJ7gu3kTIdhzU/W6QV97VzJ0m7zoFvkWO6F/zqiEUy6pjzi0WeJPl4FF7/K3vhEXhh2iJN+izcdJR7pfN/417/RW147BT39DT3kznBfy2yhxQwrv8rIC+QHF2ng1U6drRKLu6HDxJTx+FOUqM1wyvOsEqlrgOXkWqtEx4nFbiRYZUDnaxySus50yqXd7ZKHuuE4feknnHJtMq9pBaPWBkjDXgSvmKzSp2uCZvsVhnDswGHVWYTOx6Da7KsUoqL0yozSTYeh+8bVmnR9V1WCZIS3Rde5bZKIR7yWGWaybp4Er7hpQY8BbefxTvixtm8E6nEE/D8LtSjNcDdpAKXrlaRbGrWOdDXnXfQOTBEqnVfuImU6V7w4h7UhgdhgrTqvnBlT+r/AIeDfLwjHoRriYknYc/eVumDR+At59JbPRf4A8lgXPpYZTRp13HYRo7hxnmcEWnWGmDyfPrAfOMC+kny8Tgc1tcqRXgYfkpytB54Vo5VCvA03N6Ps9Bn+1tlEcnDE/CtgVYp1vm57HUZ90cdPj2YM1KHq4dyFrj/cqs8chU9wSPDrHLPTfRN17yFmu+hz3joXqv8cR9noR6yyuEHOCM8WWSV6x+m/1oPDJbQZ635SatEp3NeuK+M/WdzLrpmhVWeeZWz1vFKq1z5hlVSuk7MKq+voj/qcat0SVglcy1rbrHKJZ9xFrg0WuU94sdTcPA2qwTwIPyaDNE5n1tlARmOJ+BX26kJ9+3g2yEj8QjM3MWdwMO7ea89VhmHh77lXrVYZSo=
*/