
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_FUNCTION_ARITY_HPP_INCLUDED
#define BOOST_FT_FUNCTION_ARITY_HPP_INCLUDED

#include <boost/blank.hpp>
#include <boost/mpl/if.hpp>

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/is_callable_builtin.hpp>
#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template<typename T> struct function_arity
      : mpl::if_
        < function_types::is_callable_builtin<T>
        , typename components<T>::function_arity, boost::blank
        >::type
    {
      BOOST_MPL_AUX_LAMBDA_SUPPORT(1,function_arity,(T)) 
    };
  }
}

#endif


/* function_arity.hpp
9ty58+YtWLBw4aJFf/nLkiXLln3xxfLlX321cuWqVatXr1mzbt369Zs2bd68dev33+/cuWvXnj379x84cPDgjz8ePnz06IkTp06dPv3zz2fPnjt38WJOzpUr165dv37r1u3bd+/ev//w4aNHjx8/ffrs2cuXr19zHMMHjg/VMZTAkIPhIQaGc/7hP/2rnlM9p8TDEg8xqv4QvzA5+PeQeUgj/KvOVedK4B/Hf2Gq418JpgSN8C+Hy+Ee4h/Hf6GLB96P+CIAulJfBIxZXwS6iKGzNtIRQIV0BFAhHYFFkhqBxX81As7NmKZzNKaRrkI6AqtCOgKrQjoCq0I6AgCu2REAp3NfBIDC4IuAMeuLACqkI4AK6QigQjoCqJCOgAhQI2DMqhFYzKtGwBjTSFchHQFjlId0FdIRWBXSEdyzEJ1yMcYPBEzTuVtB5xqkKzGJoFAiHUGhRDoCPQuCoIDaAAgKRAICpllAUNAVLNKVSEdQKJGOoFAiHYGeyEDwAxZ8Efz4bvBD2b4IfkqkI/gpkY7gp0Q6AqYxRjrK9kXwQ9m+CH4o2xfBD2X7IvgpkY7gp0Q6gp8S6Qh+SqQjoDzRWh0Bg7CsRlAgwgdBgTQfBAXSfBAUSPNBoAi63sD8CIDzNkPnb8yPoECaDwKOcvBBUCDNB0GBNB8EALQkBJSnYhAAO55BwHRhBkGBNB8EBdJ8EBRI80FQIM0HARSYHwEUmB8BFJgfARSYH0GBNB8EBdJ8EBRI80FQIM0HwX2lRU2eWiICxtTEfZEECPhRChAQ7wsIGJcCBDpyaBdhfgRfVAAQMGYAAfG+gIBxKUBAvC8gYFwKEBBP1wd+KFuB4IeyFQgYMwoExPsqEPxQtgIB8b4KBD+UrUBAPCioeWB+BD+UrUDwczYGpjE/gh/KViAg3leB4IeyFQiIlzWAUlYhOiroEGdYBDW/1FcjjUVQyxrIo8JIYxHUSGMR1EhjEdRIYxHUgBwI+McAgq8S0wgYM4CA3+jIUCONRVAjjUVQI41FUAOKRkC+UoCA+XwBAeNSgOCLNBZBjTQWQY00FkGNNBbB/bMNtN/x3zmeMY0xgopfTLt2UJBOF8lIVwCCw0wAAT0KAILKuejGNMYISKeDAenUKFX84hvpCkBQ8YvHIg5BCEXoEFNiGmOEIoAjBgHpCgUC0hUKBKRjGmMGiQhFCmOMUARlKxCKFMYYAekKBQLSFQoEpCsUCEjHNMbgcgD0shEBP+kfqPCTjgDaNWjxGCMAGgWDAEhDunPKQIC6GCMAi1QEqItxXYZ2H4MAdTFGABbzIQDSkA5uB6PCGEGBsn0QsKkwzVDz90FAuq8PAtIxjXikIZ0ui30QFHUxRlCgbB8ERV2MUQbSfX0QkO7rg4B0TCMeaUgHGoQ9EQV+ImCsBAQltX7q8qnlK50rd6RjGkFJyXRqoDODsiYAIGCsBAQlnUboVIF0FumYRsBYCQjuK2I0JkCgFkGtjBoA0usCIGCM9LpIxzQCxkpAUOK8CggYKwFBWRPTCBgrAUHJIj8Cxkivi3RMI2CsBASlex3mDfJB+yP8/4XO3YR9/cgewVG1mrGdu8l+HCumdePAAETLzylSvAe7EKpQEMLadfz7Jvk4a0ZJGj+Y5YxhmjPO4WP42BkHzePj6c7YvMAZZ/NxzgIe/4kzZvn09IU8/VNn7MvHWbR8IUTOKPlO92Hm+VBwh5/4et38D61f9vR3q+c/KuR1X0qbjP+xGocledxJRAuLdD563whfuyPF0+f4KdqZdr2Twgr03BJb19/x8glbvSLC8/uN8IxEG3C/b8iVpPRUHX5N0uEjOxo8BkTR9P1J9BgfHhzV6ihShk/UJLg=
*/