/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_CATEGORY_OF_IMPL_20060217_2141)
#define BOOST_FUSION_CATEGORY_OF_IMPL_20060217_2141

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/mpl_iterator_category.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/static_assert.hpp>

namespace boost { namespace fusion {

    namespace detail
    {
        template <typename T>
        struct mpl_sequence_category_of
        {
            // assumes T is an mpl sequence
            // there should be no way this will ever be
            // called where T is an mpl iterator
        
            BOOST_STATIC_ASSERT(mpl::is_sequence<T>::value);
            typedef typename 
                mpl_iterator_category<
                    typename mpl::begin<T>::type::category
                >::type
            type;
        };
    }

    struct mpl_sequence_tag;

    namespace extension
    {
        template<typename Tag>
        struct category_of_impl;

        template<>
        struct category_of_impl<mpl_sequence_tag>
        {
            template<typename T>
            struct apply
                : detail::mpl_sequence_category_of<T>
            {};
        };
    }
}}

#endif

/* category_of_impl.hpp
4TOftw6puavtnXWdH3jRWunSS37zMUNX+QbM1k1+BbN0rB2If/3bmdT1l52Ndf6O6DKfhcW6xrdjiW7xFq/YX53hlR3nUzf/OxBHvuU86ypfjZW6wc9hje5wzwbnXBf42Xf93dzVNTcOxP7v2yPd4R022xdd4FMH5aOoax/Nx5c/lo+CrvDVGKsb/OzgfAxN84fk48CP52NYms83YXN6Nn4Fg4zH1vnY/f/s3Q2YVFUdx/GDrqmFOSYVptbd2bWs0EYlRaUaBBQUdYRVMTFmYRfYXHaH3eUtLcekwsIakwqKajAqLaopqTSxBqXSohqTSpNqLEpMzDGpsND6XL1qZW/P09vT016eH9/v/Pfcc88959y7C4+RjHiJdx3WZZd6amgUnrWPNup5fNYz9cmz+GVp5al9ozBRRvI8jt0vCgfxKmae5bo8hx37R2FzPDZ84bAobOU5vFm28AbOeXYUtvMS/kw28fCcKHxSdvA6Hv7cKGzkOVwt63gVZw6Pwnpewk/LWl7Fu6SDN/DAA6IwwDN4jnTzAq6UVbyCt8pyXsffyDIenheFZrmQZ/BcWcMLuFKW8ArueaA27jfCKZJ6qTnB1TKcV3HZQeb3JRyvODgK23gNdzzfnPPsC6xDs3HyCj4/rX+exSNajJkX8OzWKNzOSzjvkMi/u689vviF9gDP4cUyLe4fh7zIPPAc3ijLeB1PerH75WW8Ta7iddzjJVGo8BS+XG7mWeyXa3kRPyxVXsHvSI3X8YiXRmE0z+GrR9irxlPGDdKmXsMHZBwPhxmzTOJZfOnhUZigfQEPeFkUcryCIROFqTzCbtnGi/g9uZ038OAjjIFn8Dy5mRfwo1LhVXxIruWpI927VHke3yRX8RLeKnXewNFH2ccj3At+VCJexftkOA8jo3CYpHgWF8rOuB+8RYJ6HZ/78ijsxTN4pjTi6+JqOTTuE4ceHYWyeoQLpcRLeIMs5TV8WIo8dYzxyxyex5VS4BW8WxbxMCoKh0ieZ3CerOAlfERuP8y1jo3C26XGK/j848wbz+I1UuU1PPl4Y+MF/I5UeAPHjDafPI8/l6t46hVRaJc6L+IDEmJ/ZRQ+J7e73xq+8lXmiuexInVew0bW+vLsmCi8Rxq8hl8aay3isY3z/hhvn/PcifbhBPfOsxOj8NqTzRuv4iGnuF+exfdMMm+8gSedZj55Geedbq54Bfc6wzry/OQovFPmxD5FWxnOy/jrNu147swoXCRTYz8rCm+UmnGWcJPk1eu4z9n2Py/jN2QCr+M+U+1tnselEvEyHnOO/cDzeLFMjfvEj0qOV/BOmcMbeOCrXYtn8AxZyvO4UIq8iKulwCt4p5R4Aw84173zDJ4rN/MCXi4VXsYNchWv4QOygodpnlOp8iyeL9fyIl4tZV7F78koXsdnnOfeeYSnSJbncd/XWOt4jfBj0601T+WjcNls30cON54uY5AmXschr/Wc8BQeK8N4Dn9zvmvxfLd5kwwvYU2u5XU8bq575DlcK1VewxE92vEcXixLeQkP7TWHPIc3FOxbHs2LwqlS4Xm8Tgq8hkP6rAsv4Q1yFa/hnv3mjUd4jpR5Ad8lJV7BDw1YC17H/eZbUx7heMnxAr5LJvAq7rvQHPICfkym8uqiKNwvh77MGi32/VnqcRv8pKTUq/iI7MVTr4vCabIzvhf8gAxXr+BeF1gL9QhfI0G9gA/Ltrh+YRQ+L5F6HTteb855CW+TKm/gUW8w5zyHFanxGo4vmk9ewUMuMVe8hmGJdjyFs2UFL+N+bzJvPIOdUuIV3O/N1ohncIYs4gUc8hbryDN4hoziebxUsryMX5cCr+OQpeaQp/AImcCzeL7M4UU=
*/