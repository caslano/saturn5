/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_EQUAL_TO_05052005_1208)
#define FUSION_EQUAL_TO_05052005_1208

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/fusion/support/is_iterator.hpp>
#include <boost/mpl/and.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct iterator_facade_tag; // iterator facade tag
    struct boost_array_iterator_tag; // boost::array iterator tag
    struct mpl_iterator_tag; // mpl sequence iterator tag
    struct std_pair_iterator_tag; // std::pair iterator tag

    namespace extension
    {
        template <typename Tag>
        struct equal_to_impl
        {
            // default implementation
            template <typename I1, typename I2>
            struct apply
                : is_same<typename add_const<I1>::type, typename add_const<I2>::type>
            {};
        };

        template <>
        struct equal_to_impl<iterator_facade_tag>
        {
            template <typename It1, typename It2, typename Tag1, typename Tag2>
            struct dispatch : mpl::false_ {};

            template <typename It1, typename It2, typename Tag>
            struct dispatch<It1, It2, Tag, Tag> // same tag
              : It1::template equal_to<It1, It2>
            {};

            template<typename It1, typename It2>
            struct apply : dispatch<It1, It2,
                typename It1::fusion_tag, typename It2::fusion_tag>
            {};
        };

        template <>
        struct equal_to_impl<boost_array_iterator_tag>;

        template <>
        struct equal_to_impl<mpl_iterator_tag>;

        template <>
        struct equal_to_impl<std_pair_iterator_tag>;
    }

    namespace result_of
    {
        template <typename I1, typename I2>
        struct equal_to
            : extension::equal_to_impl<typename detail::tag_of<I1>::type>::
                template apply<I1, I2>
        {};
    }

    namespace iterator_operators
    {
        template <typename Iter1, typename Iter2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename
        boost::enable_if<
            mpl::and_<is_fusion_iterator<Iter1>, is_fusion_iterator<Iter2> >
            , bool
            >::type
        operator==(Iter1 const&, Iter2 const&)
        {
            return result_of::equal_to<Iter1, Iter2>::value;
        }

        template <typename Iter1, typename Iter2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename
        boost::enable_if<
            mpl::and_<is_fusion_iterator<Iter1>, is_fusion_iterator<Iter2> >
            , bool
            >::type
        operator!=(Iter1 const&, Iter2 const&)
        {
            return !result_of::equal_to<Iter1, Iter2>::value;
        }
    }

    using iterator_operators::operator==;
    using iterator_operators::operator!=;
}}

#endif


/* equal_to.hpp
EI91Xg42yLK4o11KDEg+0jVy1Bkz/yjjJE+L0KOtZfYo0iG86xz7lBmwP7UPjjFHfW1aPrfc63vvEfK/bbwP8tw3hjVj3d3SFxMWHmBd3t/83M1zlxbBurbZo0ib4O7WEzuc0CV8D+fYo0SX8D3dyx4lukQ2nGOXEzpE72XNkKbEgMS9zSdZmgT3sabYpcSYhU3jpMaIxfvqizrh+7mf6F2Ut3fuDvpeFSO7jEneUa45ZUZn2Rq8lf5v6nngudG4rn4X1KPL4DX2BjrbBP6K+maTDCX6RJNiZI8Cp4SvpE92OSF5ZXNMhu73vMd7VhK+irywT4URyZTYqbBxNev/Cp5751Kf1Ln1Q53weVynwIilkLzRJnFe80SV4HzmnDwDFs6vP5pEw54flJiwfAF90SV1QX1RJ3whfVFgxFJEX7SIX9jaoUJwEbFzwpDFixozLeJR9TiizpDYxfTJLnmajElc3L5kpCnQYkrv657f37DPElnqTJj/ZjjYpciARMc+SuRoMGHuW/bl4YQOkW/bi4gDqoyY+0442KbIgLmu/asoMST+XT+HkKXBjOXveUyLyPfDwRpHdIj37E9Gng7xH4iLPH1SP9Q+FSYs/cjzlybhvvjI0CT8Y21zSIvIT8TCMV0SP/WYY04JD+SJLE3CP3OdY06J/Fx7HNMl/guxkqdNaGhs7FGiT+yX7iHLKeFf6YMsDSbM/TocbHFEh/jIY47pEP2NNshQZ8rNf+sxTcK/c51DmkxZGouDMgMSvxcrx7QJ/0GuyFBnysIfzSUntAlN9MMey1M/myoHzP3JOeoEf3aNHA1mLP/F+GgQmuqHzVkoqCpHJP9qTin7ueJI2SbyN7nmkJv7mrRPjQm9mfj/IXa6JP6pPfIk/+U+DmkyZT7wXKbEzVuukT91L71Puv4p4/yEOD9uLXlt73zEuqrJOUc0mDD3UXP4YTF/SKxV/X7Q9Q9Y/+/VF5H36ZsCXeIVcZGnxZS59ztHjjp7Zevgndp5h3veLE/6P3616y88X7CunLH2GnNAIu85ytErxEH0lWJm8dHW1wv1vytHDEk7X6BF+Ni8rPobwWPtHHkOq9sh8SJtM3D/sbLP4q58vFg+lPvKBpFDuSDH1r7+aRE81dywS4E+sadpk0MaTFl4urxSoEv8wHxzSIMpi88QM1WmzD3TPZzQI/oszxOyNJmykNE3ZQbMPVvcFOiTfI42OKFD7LlyT4E+qazrnBB7nvHRJHi+cZGmTI/4C/RPlhpj5nPup0r+SWLwvVr0ye5lh2MaTEg9RXs009p6nLqPMg/ynudoV/+Pcd/D3UeJCSvbYn2QPN1f/JvWy73M5d3Nx/Vd44AqQ+ZuIBeUGZNaNFZO6JG8odxQpEf0RtpgnwojUjdWhyJ94kvmkgxVhiRuYo2To86Q2E2NjRIdgpvJDVvkqDLk4Ob6YkD0FvpnjwItZszf0n0cUmdE4lZyzz4lukSW5Yt9qvSJ31pOKdAleRuxUuCU4LZeB0lzzoLcz3utIXltcdAgeh3XKDNj/lrivYZ+rq5vpvSS5/N9ixiS7l08f7CkPIelW9nLS1ll5nxfGbuSnNzQvszKAyqHfk5RFm/kujJyZbFdRRvK4CbnD85R5qgQO0c/yvp1z+e9DPm65vnso6EvcgQ3Ol9QUw6IprwWsHmt8wd7ysqnz2fvCOOj5txMuf7Z89nPVH6Znxerctw8X1BXDole+vz2M5Vrco4PlBWCuL3KlHFjH19ZW1fQ7sXPF8zLQd3vPXdu5j/+ucX5gi2Pc5xcTr4uY1yUI2I6j7UVaP+v5w8Kvz9/MGbn135XSnh0/mD6S/n5lb12aNkrLPEz319TJfxz/08=
*/