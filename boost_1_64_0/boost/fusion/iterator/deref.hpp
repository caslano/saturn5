/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_05042005_1019)
#define FUSION_DEREF_05042005_1019

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/iterator_base.hpp>
#include <boost/fusion/support/tag_of.hpp>

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
        struct deref_impl
        {
            template <typename Iterator>
            struct apply {};
        };

        template <>
        struct deref_impl<iterator_facade_tag>
        {
            template <typename Iterator>
            struct apply : Iterator::template deref<Iterator> {};
       };

        template <>
        struct deref_impl<boost_array_iterator_tag>;

        template <>
        struct deref_impl<mpl_iterator_tag>;

        template <>
        struct deref_impl<std_pair_iterator_tag>;
    }

    namespace result_of
    {
        template <typename Iterator>
        struct deref
            : extension::deref_impl<typename detail::tag_of<Iterator>::type>::
                template apply<Iterator>
        {};
    }

    template <typename Iterator>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::deref<Iterator>::type
    deref(Iterator const& i)
    {
        typedef result_of::deref<Iterator> deref_meta;
        return deref_meta::call(i);
    }

    template <typename Iterator>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::deref<Iterator>::type
    operator*(iterator_base<Iterator> const& i)
    {
        return fusion::deref(i.cast());
    }
}}

#endif

/* deref.hpp
vP3M2jv7HsTr75KcVxlTuop5M+5zmMhPRhtFmqx+z7qkSoeK2Pe0ua2tLE3ruv6/fQ/a2lrWRu5R5wnqjz2Pn/PPYz9HJbv6zdNkTOIX2uGEFsFQ22f3qZthix4zCqz9XPzq2QfdepeHkNcAZVMZUS6wzwkDwuqtEfut9cQ2Ocq0mRD/nTyyzSH9mXn+hzXGGluXkguKnHJ0Fb8vpcvpX6yHi7k+d25v5XhN/YO16zhzDfNBg6Ok34tZ2n3WfVZ5U5mnRsjjefZIq1emLoYh0bH1yyYZirRITIyFbbL6P76wOaRHIJaUz37OxLaqjE7NuXNb4rj5HP/bi+yQKsnXu84hXaZkTjznaDB4oxy+yXOTKl2mxAtyvq6f+8nP/cX5WvFeWN6dGzGOmCOPe67HXV/igJh660Q9Dxan2v6nc9b+InHr5lCs2UtzBfkmZ01Gdvw8fvb31M+XN3M59JmCBefa//t/3G7OPnn2XK/T1Pb2X+WHPXO4fHGvlwSeWyNzeHh1c/Qvc0GR/dnZ77zEcC51ryvXJT//0yQIPHdYYZssRZqMWTqXsVEi5N4kW4z/Lo/abZAMvAZrP6Hvm3NyGXMmhok5mdPDsvk6+7dGzPEOkz+63/yeE3GvuU3ITc+czVgxT1US5ujmbJH+395vTXM2EUsrbI0r4+e2hhxnKDFm9QHa3nKdGXMe77AZkntO5X7CqTkrMOLYXO5SY+xr0Dmub22ZP5Y4YPC/PenmOBHH6ke0yyFlOsxI/W+frTR5GmS+ry+Weo5J/Ujb/9tz5pAKbfZ+KRaWvNZM5XDJ2o483bp4qjETepp8s8I2OYqcMiSlbsz7JPNkr2QuuLlzW6yd5Y8BYfEvsMEBc9b9Gnusn32fLNYeM+I9538gN2LuUnqztfYWc2YOl5g43hFrl8hbrTMxJ5zbbVjL53itZ/Igr+PK5Zs79tmXGuFrnq3ZiD1BIkGBrOM10jGPlXV2aLm2oIyx5NoxSSKMnetSVWee9sXUUx5yDhsx7SlX2b2kkoDYpdVVLl4qEuSpnJ1TTpQbyi4Tahw5l1aec2ntxsVCiC26zpVYuUwkSNCJi824RpePBHvGW7iC+5XVq0SCnHPh25zH7y71S+hm+mLlppGgyRz16zpecA8b15MTznE8Iek4pjxWL6vekKWzazeRC+emNn/oqDMifFnjupZ7SNxOfpxbVh6xS43Q7SP2j4kE61fT57XdT2xev9eMBPGEtlm8urhZuJs+uPkd5equ8s7sLh6vqevcVJlVbipjzger7ruTftfES9nxhvv7dxGf4zadNfW1s0SClVX3rhmvawd30ead1WHB8aHrYccFWo4376KtVe1yxCmNu2jDvXMUxLKnXthx33GDHXU2lYWztle1aU62tJde059ycH/PGes2ui5Hyql4Vxznz+Lm2HH0+h5fW4z3Mr7v+KTna3x+5Z7ytGE+7q7c8r3hPSLB/r3ERd21DhXXyq++gN+3yI3ri9bB6cND/p/kSHCyIQbnE+qHGXvcpcneffSjPIc1Tj2eqFM8q79hXI7TykOPc/dh072sncXk2oK+gvs69jgjhtV7iWXDeJ2/ufohx3nHcRLqbGzifFe9kMclZWVTHffenMGNtbkkj+So0GVG/CbatQ7XrcsdRtbYzW9ytuY9N91Xdlx0fOK47bjruOF4y/GS4zXHGcc7jvccR24rBu0ueQ5ty/sBi6xRvaF1wIAZixfV/oUjQS+i/kXEcCHzzJTViDoXNKcXsEbDzp1fztg9jzmlzoBISDtskaVMhxmp8+qXEwq/upD3UXxf6Xju1xcKiud2/z/sVfF3e4D4LGNPGZnZn4nWXy/k/+47X5D4m30=
*/