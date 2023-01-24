
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR_HPP_

#include <boost/local_function/aux_/preprocessor/traits/decl_/index.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

// PUBLIC //

// Expand: `[ERROR_message_text] EMPTY`, EMPTY iff no pp-parsing error.
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR(decl_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_MAX, \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_ERROR, decl_traits)

// Expand: `[ERROR_message_text]`, EMPTY iff no pp-parsing error.
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR_MSG(decl_traits) \
    BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR(decl_traits) \
    (/* expand EMPTY */)

#endif // #include guard


/* decl_error.hpp
c74kPrnhtr0rdwpfwCg594NvemPV3+lPXPf1YqWpLnPUCfX0rtXy9ml3drtssthGUNuggsZ41ZN9F752t6vhReNtSt8582ADTaPwXFKgFHVKOWl8SL/OC9XCBjXr6P5q9WVOgZfypdqyCrU8jGeZKmOA8ZKTEQcQmQvym7Kq06oMOV9kvDUsOR8iZxuA6jHcefG53ZtlvbGuXUmNHGh4G7serSeoNxZrnnFnrDdhTtwqLUU6cOc3geh03KS7rMjEBxF+NL4nn5Dr1y4UUQ9ZrplKPXRcVGR6IbqYPDyGoEko+Mn4hbQhHdYcqs/6Ji6WwNB8MqEpXeLrRd0F3d/kmATH4Z12ZDrWxGqmhJeV1gvO+9Z5XRJ9RWESMHnYVxgKmuJj68Lmndbmw1nPYlXeNa/NHlFW5RwIKpbFMQdhfqGdCFqSewwW3iS607nRGS9utPbkR32v8NtUlffQFO0ZbsGh9eIHT7xCe57uNv8t6pcJaHUr6JNZxqZMxi79I3vsTo7tYRvyrQ9hdpmxZ+Tnp+wsnnKS1K79mZmXm9WXKohp6kqhYPOT3u/iBs2L58AjIXLiSTOXFIgsN3zkQoMVeO+ycqcR7VlM+7BJnhs+fROvcaytMDBeU9A438VVa16pcFp2mSkf8klTVbOeFCDadHL/abvMUVM/MQOhO12mVT2GyGU4Ptsfowud4TMIPQ/NeXazTNd6O/4wa8Et
*/