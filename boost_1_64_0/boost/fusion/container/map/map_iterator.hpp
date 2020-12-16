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
zbqVPl86dSy+DvluQPHndPn8XoBNv6ZSns6EOoR2hPeZp6ijTXkG8ASclCWgjLIYHZSls6buaNfpQQ9p70Ne/PBWPE4iwZ0c5IFVWp7nQuvRt0NBl+K+HdImJ5gi01PMD/FZ16ODPIY7qN9R2vptfgYxT2mzTJ6Ve9W+nUkDq2vKGGsun8xLe8Hiun22i8wr60i2mTKveRv17+p4GyVWLNlGfrKNHiBPhm4262eUiS963A1tI9v9RbB2f2HOZ5g5Xe5H1LLp11vy2UHqkpEwl3lMJfkc3DsyZGR4ZEyKaZqzdUmeg5V8zmGcPAerqUu50jf/sArkAUNRyUO+wzxQmcpRl6S+2OUj3CYf8py+fGfTk0yR9I0g38cKPaSdus22XSz95mdYnlsh5BDnjh62+eVRzhvc96UTGMfORMpkHWdqC1Im63O4QZa+SWjHyL2o4vvk/5FyONxPSj2u2LN4nu9qa8t6VcraWVle6vEHrI+wnrZlnZgaF+ds/VDKqk0v3EuebyNUk+dMThJhrl169J1Qjn2bo779r0hZfiDcTz4K7eJOjUuLSy8zbruySL3pEazaJ8hztkpbwEnMzHOzQ2LqnQu/FFjZ5Ff4YIcrr+k9v6r3PK3zz5fyDA3js7es/uDfh4zGWYdGZCYs2XxR/7nWe92V8UW9hvplBCxdvN+3+9LKhb//h3uHgcr4eq/PWHy1afi++ZkDd8579bkj+s/39jc/x3ts+vG3rv247NK0RY3qvLCYdlW6z/c+Zh4//tXpG71P1t4ycPaFcYlXwp90/jleZ59ndvbdvk+by5teb8GPs4Y9MXZuy7vXebevfF7/uWhudTH+qdFvelSb9+uzTXadbBKwbmAP2i6Z68PTT27qPcfjlt97xXTamvxZJ/bhQebniq+ePeC1auas5f1OX45OuOeOQnObfcZ3/ymg+cjLM+Zv6zfW96Lnogc51jTPf3GxYXWrg8lXZ32/8eXZGxtx05T79Iw3FSTN+7Go+VvHHw7xCzzXmfq2uakyfv3OJ14/9vZ9V6bX3ONzp9dPg6nHMcr44wcrfBnnWb3enmZpCQndbl+u95yz/vPSxe2R5RhYjo1zK9i0R2ZyY7yMd+LP2A5/wU74K/bFq5iH1/B5dHenvTVWQGkfJMec/F5LOur2QatYzg9XY3tcgz1wLfbCdfi97MMLJJ6zEs+tGCvxrJd4NuEo3IzJuAWnYB7m4NP4OG7FLfgMvojb8Tg+ix/ic5JuZzc5bsPOkq4HShcHjKMdAXaR9dVV1lM3WT7HXY655FhMWb618jycu/TLI/nuKeu5H47DATgBB0o5wnAGDsNsHI4P4wjJ/0jch6PxNQzHAhzrJvfl8Rscj5cxEpX2PVHoj9F4J8ZiB0zAELwX++BkHI6JOBKTMBKTcQ6m4EK8Dx/HdNyKGfhPnIJf41T8Baehp/IcGzbF6dgBZ2AEPoDxOBMX44O4HOfhGszB93EhfoqL8BwuwUu4FH/FZagc+y5HeV6SYzz19tQ+L/mIbI8Vsh0fVdUDkyzXwUE9eF7qwQtSD3ahEXfL8gHucrwkx1G5hCbKsael/ZEs/wq2xFdxCO6V+pyPafi61N8DuA7fxB14CPfjYTyKb+F7+LZs/3fwMzyCP+Ex9FDaGWEN/ADb4Unshh/iIDyNGXgGZ+FHuAnP4jb8FI/hZ3gez2MR/lu27+dYC7/ABngBG+NFNOLX2A+/xVAskvVF/ZXjNeqQrG8vDJX1TRvbLANWwq7oiRHohTFYGSdhFUzGqmjCaijbk2Mk/e91EPkwH09JfWgv9aEDWp+7l+VbOKhHrZivGrZGf2wjy2USCmW5K7Kcul2Tj6R7u3TdW1s=
*/