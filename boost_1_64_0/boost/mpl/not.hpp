
#ifndef BOOST_MPL_NOT_HPP_INCLUDED
#define BOOST_MPL_NOT_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>
#include <boost/mpl/aux_/nested_type_wknd.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

namespace aux {

template< BOOST_MPL_AUX_NTTP_DECL(long, C_) > // 'long' is intentional here
struct not_impl
    : bool_<!C_>
{
};

} // namespace aux


template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct not_
    : aux::not_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T)::value
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,not_,(T))
};

BOOST_MPL_AUX_NA_SPEC(1,not_)

}}

#endif // BOOST_MPL_NOT_HPP_INCLUDED

/* not.hpp
ukV90zJcP4OlBHaDBmV0cYp49lUU2CTHjN1egXc0QajyoGBjjmkYfnK9yDiKQDpk3IOIhhxnZ59AitqOnuR+qH5KfZsKmZTvEZ/0dRiQunqIZX0rf0c/V7+Ba1/wHdKVlIoJY9TdpaZkMtOQEa1SIZcgU9UvEAlM0cxpvmTbRY6sgzh7IBYQbSWokKcx1FQiIqVaZFLka8MXTPlCH1QQ6c30hT8RH5EGUYbUAS5ytv3K/6ac6fH8vXLeTyJDXgENT2uycP9L3mNDsFUwgKXHgECad3lzymNOcH8aeMARThNcJ8pxJ7g/DTxgh9f00FXRAdqSV/OGl7Z6kcmjShnqvpm8OX/AGrAXDPAF78joBUQYSDjB/WngAUc4NpvbKfc6wf1p4AEbPEH7IbGtq7cIFw0nd/smaKtCe3JHVm94XFY7nxqsp/CwMUgiiToKP3ZYu2y2lH3Q5FfUZmOHlAubHmnLpTdtij9tSsApxbIe3o5uimM/No0otS7CRMzXR9Bmw5suwZ8uIeCQ0OPHSng0kTc9gAPyUd6Vf5mLBMGbXBHD7S1RXCnexVHqNygr72EZmDdrKzC66G60Vk8+G7uaHhet2WPjuLu5K0DG1gb05xBJB7jXEe4IBOWEE+WEE9zrCBfghxaTXef/34gJzRpMaIChAUADBEUBzgn+dAkBx4S4M9S5AKmBc4JzAT3zsIRKRpCEuFuDBcInG0q6neD+NPCAHQ7KhhNlwwnuTwMP2OFkjGGpo7DUZKC1rRYD/YrcoQMGEnplCBBhIOEE96eBB/rB+2mDKqjXqaBeJ7g/DTzQD55Oz7bb9ayouJtUzaoFReWGbNp1ll5nRRA5dU5wVoSPQdMS2G9PLWP05GvjPJCNM4yWacaa+5s3J7g/DTzQD57cqp9Ay5sF9QLB2UL3L8gZHugH14vlBKZu5MP49eXt9MjfWOuuULNDu8kD0jJBbNGxBLl5icxg/Tg/yaCPFWEbKUInzZ9pc4RsxKNRaYcsm/aNqDdoVOLGfcO51a0J/nQJXucEJyjkJl2C3znBuYB+opzAtjc5rtGthoQADwnakevGAJMmxZ82JeCcYqQBpy3ESFuIkaYQ8/IRQoAp7ZaRTMZQNgy4HFtJwPaxWdiwapoB+j0Mv+Uu2jf/RffP0t+t9Hcj/V1Ef2+nv9fS30vo7wJ3vn8K/f0m/T2f/p5Ifw+iv++78v2vu/L/43tRP/t89vk0fvR89rivRPuSI70XZx27xdSQ4sIf6KZjqKSiyWHaW5dv7sY9CkjFMTE15KPQ1hVPBvbBZCVPT5xNJxlwAEOfk8A5nGhzV04dn0rLymk2CRkUxN794nCeJhqjtlHYd3hJbFQzGYRRbhMjystnBi9Kspf8Wi5laH7Dk/O84tcgS7K7bTjPZ4xRrWQ/h5fHRz1PmUZ5FUqMV6B6MmFp4s27BsPWu3Paqnchvdyg4XD3TiqZj8btJD5pCW1UG2UaNUShxPkc+xuZmHUmmrvyKMfOHmstolyLuFmL2PCSaGotEpZadGJq0pk3Ay+cqVlWJT1FSDMtNz/Z0D7AXKdr50ZFZL2TqNa8dnYd2nFU5mzVOtRkChwDWPVPQoHjSXCcWl+BE0lwomci+R+URRqMGgnVxnHf50VW2jI4ju3jVxIVUrQfEkSlnJDc/72ozb5/tD4cOnbP+hBX+hDbgz5ElT4YpAiiDx0WfciAPnTRkgVk0GBZiXnK4xA1w8Oi5tGilsCVCaao8dGkRHNPXk6zPKLEOaMeDhgZw4vje8pJZ/iQdTBnjZlqZnjYqYoPL47tOasHWXM5a1TJtqfcwFG56J6zZiFrDmc1SNAg3B2VP9R+G8n598h3c5LzknY=
*/