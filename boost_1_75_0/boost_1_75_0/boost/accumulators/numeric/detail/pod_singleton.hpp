// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_DETAIL_POD_SINGLETON_DWA200655_HPP
# define BOOST_DETAIL_POD_SINGLETON_DWA200655_HPP

namespace boost { namespace detail {

template<typename T>
struct pod_singleton
{
    static T instance;
};

template<typename T>
T pod_singleton<T>::instance;

}} // namespace boost::detail

#endif // BOOST_DETAIL_POD_SINGLETON_DWA200655_HPP

/* pod_singleton.hpp
peFMksZjefJwfLuwPRsmaZU48VV44LzD123HyFC2Ybcara9ETWj/q4iRhUp1SqIigOQ7nh6npSVjVQccZZ6b5YJOJcOjuO+CF2WKb7eSlEYCZ+8yse4A51sM72WuacbNA5JXGyF96ML00yl9CabPMUKGrskok5zJDfJPtukC/apnrogToPOHrcFjEupwRG4nZVasNblL0opLlnxHuhLaCo7Q5pDvBLsUt2wyZN9xNkILdbChFIopam1AyF93BHrCsx8G5h4gJFo88ez+52L2kSb2VOCpk2HsEzTZGYdPg2wbNY3AM92UsbxFVJJ4P+oyiMplvH8FBeJ5fyMFeO+ySHgmmg0zAmCahYEhfODPEFDG77oTx9OIsng0DyWeA6oYFSsAXnAQuR7fR9YgdQTcDlXlEdxFJTBTlj6L+2adnKq5Jp6Dst/G6s4ZAB5SvYD756OGDcc2PBv7Koyk5k3ceyd+3iiPzp11Ygi0Ye/zuDcLK+sdaOp6fBssVIr4gB0FNONDP2un1xxrI76Ldc106tZOzvdHuZVdDtW2/G/++G78R5wAXef7SwRVgEQFat8DtUf+O5PcoIh1pjini1/+BDYYDUaQ02KrUujymFjJur5+T8ivVgJOdxMXm7kOaSy0ssv7X6ToVAAi7Go12k5WrZ6CeHc3AEMgGF5ElSmy1wUPrR/3cyp+SAMgSY6H+czCZ2Oubh+qNJCjzEy5
*/