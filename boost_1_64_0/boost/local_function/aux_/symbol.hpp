
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_SYMBOL_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_SYMBOL_HPP_

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/cat.hpp>
#include <boost/preprocessor/seq/transform.hpp>

// PRIVATE //

// NOTE: INFIX is used to separate symbols concatenated together. Some of these
// symbols are user-defined so they can be anything. Because they can contain
// underscore `_` and/or start with capital letters, it is NOT safe for the
// INFIX to be the underscore `_` character because that could lead to library
// defined symbols containing double underscores `__` or a leading underscore
// (followed or not by a capital letter) in the global namespace. All these
// symbols are reserved by the C++ standard: (1) "each name that contains a
// double underscore (_ _) or begins with an underscore followed by an
// uppercase letter is reserved to the implementation" and (2) "each name that
// begins with an underscore is reserved to the implementation for use as a
// name in the global namespace".
#define BOOST_LOCAL_FUNCTION_AUX_SYMBOL_INFIX_ X // `X` used as separator.
            
#define BOOST_LOCAL_FUNCTION_AUX_SYMBOL_PREFIX_ boost_local_function_aux

#define BOOST_LOCAL_FUNCTION_AUX_SYMBOL_POSTFIX_(s, unused, tokens) \
    BOOST_PP_CAT(tokens, BOOST_LOCAL_FUNCTION_AUX_SYMBOL_INFIX_)

// PUBLIC //

// Prefixes this library reserved symbol.
#define BOOST_LOCAL_FUNCTION_AUX_SYMBOL(seq) \
    BOOST_PP_SEQ_CAT(BOOST_PP_SEQ_TRANSFORM( \
            BOOST_LOCAL_FUNCTION_AUX_SYMBOL_POSTFIX_, \
            ~, (BOOST_LOCAL_FUNCTION_AUX_SYMBOL_PREFIX_) seq ))

// Postfixes this library reserved symbol.
#define BOOST_LOCAL_FUNCTION_AUX_SYMBOL_POSTFIX(seq) \
    BOOST_PP_SEQ_CAT(BOOST_PP_SEQ_TRANSFORM( \
            BOOST_LOCAL_FUNCTION_AUX_SYMBOL_POSTFIX_, \
            ~, seq (BOOST_LOCAL_FUNCTION_AUX_SYMBOL_PREFIX_) ))

#endif // #include guard


/* symbol.hpp
U/XbuLQ0ZCgyH9mGnEVSmMfXD5mHGPP8WndlrhmSi1jn/B3AvwTGdDPn/fnN+euDLLjCOvcP4Xwf3AzPwOg/o4u/m0DPfMAqzPNLRjohnrmBvdqemx+4kvNiJDyd+XBIJ2Qm7kOhdb7gRM7XyLzB6CvdcweXIUn8XQTbwhLYBfZDErpznTAPec5nbuFE5Cv+ngfPwKVwI2Kda9hE5htmWOYcRvbg+jlPhmnIMv7OhIWwGCkxwrZHP24LkE7t8YMZ8DA05ifmtkc3zIOeeYo5MldxObIPWYBfP/yWwjOcG/MXN/P3KcSYx5iENJH5jMZcxkyY0AvdhjtMR6ancX3I0F7mHEcWaOGG7EtDF7K8l/d8x/CryH9vl9+8x9q4pyDG/MdimQOZxnmVGykjJJu/+8GpSIHBq87Nj9xnmSO5z2GeZBLnTZA0pBfSB7eJyAJkpWUe5Uw4H1mJbEaO4nbAMreyPtJF5ljmIdY5lgWcd5K5lpv5+zCSw99TkXzDH9H6kmeYDDsjGUiREQYuQIo7wouZV4vsQ84iScnMwUT6IZORAqQQKUa0RqF5jKHjv/MIR0b9vr//DxqZlTu0f/awgWoKwG8wB+DDJM0c72wh6x57yNhWd+RlHqLLVpljFR2vS+98dY/+KheZ43Lc9gf/FKvhL6ZlLWMWK1S8zvbj46tkzILfrVdyfkbnnYi8REdElq9Uvkv5+uXr8iN4WJh13EX2mzHT6m8M/1v2792kdLaxhBuYPXrQiP7q1zfLnknvqHBttTgVTmxbWvauSYAbLGEKGuHgc31xsEiFSVW/q5dmL9JqK9Eoq6qiy3e8+Ssp/yoSsTLyKuVfe7Vt+atBNMmftfztylt06DKOdd4xNK88o98vzx0kz/PDvH8njUBeI89p9nkekpUre6OYbef8eU9bfd7fPM5bxu0kv53C/fP7OvlNd8yvGkwOOK//Zu884KMo1gC+e0kggRCSQAIEAiH0XgwQOg8p0lvoJQmEHiAkoaN0BARMEBHpKCAiggryUBSCgoKV92yoPEUFG1hAVFCU97/Jd5u9y16KRHzllt+XPzu97dzOzLczPQsgrR0krVct0rqftMa5T2vCJGOL57yXb1wBpLmzpPkJn+xpfpo0J7lNs5L4lIkNYpPik+MnpOQ93UkFkG5HuxhSKHu6D9gHIW7TrdYo85zWuQWQVkcZlyxsXcZp7tOa8kfLOK0A0u3o35ZLgmuKxxrIXtK9xTrdTLy76fOt0yrh6Jb9v7v1RPGT/bfAzRqOuHf7uxAE9yg35fK1ZhAm5SdrMk55DTOv17jkKdRp3UbS7tJHL/RzXrMNRA5S7metyz3F1Efn+fflrKlcwtV+0xKEO/2efLYr19+gUCkT4sJc4nJ5ppOKZM/3s+RbO+Q+3/T1ec4z4RhrdJUy84x3y/zi9ubyGyz5JR7MVTxOvxWJRbPn9Tn7u4PbvJp/K/Jez4Rn1HOYyrMRjPV5rDeZb0c9ExfmRlxO7XuIf/a8H7a/g7jP+6jE+NEp+cl3G1NdR6p+QgVhvff5TebZUdfEg7mKx6n/Ty2WPb8Z9vcCN/nN/hub93zHGXlBf0DVt3NQI9nym+Csz3e4yXKIlHIgXswt43Uul4Ds5fKC/TfcfbnYlYV46Ker/jQ/7YEwXX43jFAsy2LuTZZFqPk3wIjLub+LK549/8fqEZab/Ms7TJ7zTDhZOk2qLSjv1r+rN5lfQ1fJXvcSj7m/GxJoXdcZOeR1qv23cXTqmPzUc0a2elbBuNdPusl8O9ezxOXazoOsn/+z7vOe8kef/7PZnv+UPD//Z2+yLJyef+t4DX2EMbo7PYL8743vbt0+pLOOeY/d4Tva36g=
*/