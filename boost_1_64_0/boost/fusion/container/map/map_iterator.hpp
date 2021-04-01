/*=============================================================================
    Copyright (c) 2005-2013 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_ITERATOR_02042013_0835)
#define BOOST_FUSION_MAP_ITERATOR_02042013_0835

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/iterator_facade.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/if.hpp>
#include <boost/utility/declval.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/add_const.hpp>

namespace boost { namespace fusion
{
    struct random_access_traversal_tag;

    template <typename Seq, int Pos>
    struct map_iterator
        : iterator_facade<
            map_iterator<Seq, Pos>
          , typename Seq::category>
    {
        typedef Seq sequence;
        typedef mpl::int_<Pos> index;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map_iterator(Seq& seq)
            : seq_(seq)
        {}

        template<typename Iterator>
        struct value_of
        {
            typedef typename Iterator::sequence sequence;
            typedef typename Iterator::index index;
            typedef
                decltype(boost::declval<sequence>().get_val(index()))
            type;
        };

        template<typename Iterator>
        struct value_of_data
        {
            typedef typename Iterator::sequence sequence;
            typedef typename Iterator::index index;
            typedef
                decltype(boost::declval<sequence>().get_val(index()).second)
            type;
        };

        template<typename Iterator>
        struct key_of
        {
            typedef typename Iterator::sequence sequence;
            typedef typename Iterator::index index;
            typedef decltype(boost::declval<sequence>().get_key(index())) key_identity_type;
            typedef typename key_identity_type::type type;
        };

        template<typename Iterator>
        struct deref
        {
            typedef typename Iterator::sequence sequence;
            typedef typename Iterator::index index;
            typedef
                decltype(boost::declval<sequence>().get(index()))
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& it)
            {
                return it.seq_.get(typename Iterator::index());
            }
        };

        template<typename Iterator>
        struct deref_data
        {
            typedef typename Iterator::sequence sequence;
            typedef typename Iterator::index index;

            typedef decltype(boost::declval<sequence>().get(index()).second) second_type_;

            typedef typename
                mpl::if_<
                    is_const<sequence>
                  , typename add_const<second_type_>::type
                  , second_type_
                >::type
            second_type;

            typedef typename add_reference<second_type>::type type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& it)
            {
                return it.seq_.get(typename Iterator::index()).second;
            }
        };

        template <typename Iterator, typename N>
        struct advance
        {
            typedef typename Iterator::index index;
            typedef typename Iterator::sequence sequence;
            typedef map_iterator<sequence, index::value + N::value> type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& i)
            {
                return type(i.seq_);
            }
        };

        template<typename Iterator>
        struct next
            : advance<Iterator, mpl::int_<1> >
        {};

        template<typename Iterator>
        struct prior
            : advance<Iterator, mpl::int_<-1> >
        {};

        template <typename I1, typename I2>
        struct distance
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

        template<typename I1, typename I2>
        struct equal_to
            : mpl::equal_to<typename I1::index, typename I2::index>
        {};

        Seq& seq_;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(map_iterator& operator= (map_iterator const&))
    };

}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename Seq, int Pos>
    struct iterator_traits< ::boost::fusion::map_iterator<Seq, Pos> >
    { };
}
#endif

#endif

/* map_iterator.hpp
CBsZEhEUC+OpeW3nC2CHT2d+79pYw0x4+2VaDVlhwY/FYAEU8w+h3rjmMD/cYWMxLexG6p63gccPgBsJ+AbxiKpiYx3ouS1YEt2iB0ni5eXFLm6UQp70X5BMaBtjvFcv5JZPVpP9kYk4kF4JPbWEbKdHlrTxBR7Obkrh/unVmJU1FvgE9E7agRbRQFrGTCTT5QVkaGczviTqB1ewlax4dO0rNNvNeggTtEFXGkK6iqASe9q8dzdP+bhq0A/87oBqhZXZXAscHNbL+LJD9VfoSGiI29kZ/ZAYPxsGdY0pd1XR7lD5FfE5uYgQaNXHaPhRIqtlxK3ZTreAh6voB6nYWBV6+F7pKQEQSZm70G3cItBSkf1732aB9CsDbJbn08KDs1ir7Q8lS+QmKiyn5NlLoAi9+fd4eJaae8rnfbQ34bDR7yxt6C9Mrs/Kt/GINtlMcVWSm3HNEvA3hLDHuMz/qKB9qjS1eeVDgrU/XR/nxRxgvqibjRyByTKAT+lhdH0rQcIdElc0eMyfbEIPReTBHNE/ubzSlR4DwPlsvoT9etNYX11esyr4eH2GxQ==
*/