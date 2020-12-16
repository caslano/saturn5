/*=============================================================================
    Copyright (c) 2013 Mateusz Loskot
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_ARRAY_ITERATOR_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_ARRAY_ITERATOR_01062013_1700

#include <cstddef>
#include <boost/config.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/fusion/iterator/iterator_facade.hpp>
#include <boost/fusion/adapted/std_array/detail/array_size.hpp>

namespace boost { namespace fusion
{
    struct random_access_traversal_tag;

    template <typename Array, int Pos>
    struct std_array_iterator
        : iterator_facade<std_array_iterator<Array, Pos>, random_access_traversal_tag>
    {
        BOOST_MPL_ASSERT_RELATION(Pos, >=, 0);
        BOOST_MPL_ASSERT_RELATION(Pos, <=, std::tuple_size<Array>::value);

        typedef mpl::int_<Pos> index;
        typedef Array array_type;

        std_array_iterator(Array& a)
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
            typedef std_array_iterator<array_type, index::value + N::value> type;

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

            static type
            call(I1 const&, I2 const&)
            {
                return type();
            }
        };

    private:

        std_array_iterator<Array, Pos>& operator=(std_array_iterator<Array, Pos> const&);
    };
}}

#endif

/* std_array_iterator.hpp
/j+PISHl9+EhFP+s7lcImb9Q37sphAmssN8RYcnuYfD424c5Gun3s8KUMN3v48NkNjGcHk7zeaLfT+TxcUPT/Y/E8xv/8nesT/BVEh9Nspv88bFVYYj+BkKf7+I9YXY4EbtDp557wqzQq001bmMlR8qxIeYMv4fwunCY+lht5oZCaNd+cTgN5zo7PtrCHBYZXQF7whS/JvmcC33Oea3aTNcdoTIHB7Q6LrzMr4Uh/nW4No+d1+9Xd/zZebN93WEenuvaj491nPTrzT04Z8Dvvc5z/Pm1tZpjhH1qHT51aznDJxVjd7jKnn/U71nS55wn+ztCizgZc+Mw4n20N1euqi22O/OJWeCuYGT6j0emn1PDONeOj5PDfs49PcSjni2Pnevafjfmv9vH4dLtl8PzNExfj86s6vx4Zv+htWjTvlcf57vGgHZHuv8/6+fPZuGpc1AOr3TOJK1mx3dgR1g5Y3VfKvHahr9Qi/RxrF+jwmGumvHpaLW/Ns4xxjIQ5ujFSFxbJb53fKJH9SheWezEBX43R649Toa4C6v81N3t8C/MhODK9oGqvYZ/tIe8rypNYfAYPAYPhyNzSBga4+N+yx0SroLs6tzq/OrC6uLq0ury6srq6ura6vrqxupwZerK6MrMldkrc1fmryz8oZ1zhXKdisLwgYWoQEQgKhARPMpjQVgLUYGIrEBEICoQEYgKRAWiMgJRGVmByPSZPqaNQFRGICojEBWIysrKSr59stuZO3MHOrwfPSZwmTs92fvb//n3Oaf0o37cT/pZP+8X/V3/0DcDZ+AOvIE/CAbhoD2IBvEgGWSDfFAMdoPDwAydoTv0hv5wN9lPDpPjxKSV1EmrqZvWUi+tp37aSIO0mYZpK22nnTRKu2mc9tIkTdMsXad5ukmL1IRvm4x5dphhlzn2mGXKPNc3ZlBhBrVBfdAcmFFl5I5qo/qoMWqO2qPOKB71RtloPdqM9qN0XIy348P4OK5MqpPaJJ70JtlkPdkwMz7ZfmrKp+3SfWqmlak7rU39aWPanHam4aw1i2bdWTJLZ/lsM9vN9rPjrDqvLLxFfREsmov2orOIF71FulgvNgvTftvEhkHsQmKWEyuXGEXEZiOxITJVG5lgGA2z4W7ojHxmnIyKkRl743Acj3Pm6k4OfI4zr85r88Y8nLfmnXlv7i38RcgnHheV29pt/bZ527rt3vZu17eb2/3t8ba6rC0by+ayteqseqt0xTyit81nPMKklURJN+kl68TcVG7cm9pN/aZJ5jsSVRvRzc3+JumnzHnT3/aPfRO/bb7g7zbT9Tyfb+bFfDvfzffzw/w4bzKPln33aNGV92dGzm311mVeHjPzbxvMqbjd3u6Y2YG5mWVlyS9L3jbf8ljzlhvyshvveduuzUlis5JP9Hc//M36e1/8jQ5vGy5by/ays4yW3WW8bKyCVXMVrlqrNlGIiENCJLLVepWvNqtCYpK9bT7l0bERiYlJkqRJlmyTXbJPDjY+zo07rpGPaNwlI/xw/rZ5k4cLuQHERjCTWWb4w+Jt4/KoTfLZdnaYrefdZW3lM4v2qiufd+Dv8siWm+VueVw6q3v/1X+HeBCWaTrdT+sQVvA7jjNvXp9H8+68B1XFYrs4kHOiYGPQIOsReU9u09ucKG+JhbOsLr1lfRkQD2JBHHrLbLleFsvt8mA/s8qnNmxcIj6XmBCR7eqwOq74nz5yomNMNXETP2lASpuoCCm5jQjRsLSEtgapP8vKFpU43lT6NTSi0W/2O9DeQyHW0LPva3WiDw3qs4M69KiANRWwRR2Og8qwhjY0huGwRR10h73helgMt8PD8DisUMk+lRyOWlSyrWOqYzs6jI4=
*/