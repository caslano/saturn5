/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_ARRAY_ITERATOR_26122005_2250)
#define BOOST_FUSION_ARRAY_ITERATOR_26122005_2250

#include <boost/fusion/support/config.hpp>
#include <cstddef>
#include <boost/config.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/fusion/iterator/iterator_facade.hpp>

namespace boost { namespace fusion
{
    struct random_access_traversal_tag;

    template <typename Array, int Pos>
    struct array_iterator
        : iterator_facade<array_iterator<Array, Pos>, random_access_traversal_tag>
    {
        BOOST_MPL_ASSERT_RELATION(Pos, >=, 0);
        BOOST_MPL_ASSERT_RELATION(Pos, <=, static_cast<int>(Array::static_size));

        typedef mpl::int_<Pos> index;
        typedef Array array_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        array_iterator(Array& a)
            : array(a) {}

        Array& array;

        template <typename Iterator>
        struct value_of
        {
            typedef typename Iterator::array_type array_type;
            typedef typename array_type::value_type type;
        };

        template <typename Iterator>
        struct deref
        {
            typedef typename Iterator::array_type array_type;
            typedef typename 
                mpl::if_<
                    is_const<array_type>
                  , typename array_type::const_reference
                  , typename array_type::reference
                >::type 
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const & it)
            {
                return it.array[Iterator::index::value];
            }
        };

        template <typename Iterator, typename N>
        struct advance
        {
            typedef typename Iterator::index index;
            typedef typename Iterator::array_type array_type;
            typedef array_iterator<array_type, index::value + N::value> type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& i)
            {
                return type(i.array);
            }
        };

        template <typename Iterator>
        struct next : advance<Iterator, mpl::int_<1> > {};

        template <typename Iterator>
        struct prior : advance<Iterator, mpl::int_<-1> > {};

        template <typename I1, typename I2>
        struct distance : mpl::minus<typename I2::index, typename I1::index>
        {
            typedef typename
                mpl::minus<
                    typename I2::index, typename I1::index
                >::type 
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(I1 const&, I2 const&)
            {
                return type();
            }
        };

    private:

        array_iterator<Array, Pos>& operator=(array_iterator<Array, Pos> const&);
    };
}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename Array, int Pos>
    struct iterator_traits< ::boost::fusion::array_iterator<Array, Pos> >
    { };
}
#endif

#endif

/* array_iterator.hpp
w45G/2Jt5ogColzuHysiMx08+yp5W+Dy7O57s7BY/St4KMDvVMChe7dJsgZsp5rY23k0IX1ojCEAZo3Ppz8Rd8CHlEYnXU0Fv7ug0TP7kl3uhH6uhbQUivPEQektl0PhxYhZ236fnaWcQks/GC9aPLH/ZNaULOznDtTFLU9DF6r2+bdYE73sUf+eLu2+vThAjv2/ZZ3U/eVxQCz4vPgJrxlkZhquLiCeGSqX186Lw48IPA0xMRb9FGfFRN5xIMs39GirSUrWA21nYP6+lWwtL9siw++jpQEkY4dVE5qGvUWQQZxMhhSxaRFIV5ga8e210mXG4mocZGBKZxlX3hHJX506K/qzMnbSNiZ+QbkAPfgLKzeeNfuypN+hAL5Vb2XsTsJzZ8BhafGnytH8H+aeoCm6mdqGPUpnJHOFBgyAMkV+/Zpbk5Jv8PLQ/lGpGJezX9IHwYcYo667LuiNDHW4lD75jzCglpHhkvEJkMnb0632E7memZKLD3ZE9Kyz74dkIjawSllNbXB7l6P9h8/cUphYywc7NyHjnwSpYVJ8Rv0gXI3ZV9ZwTJvVDQ==
*/