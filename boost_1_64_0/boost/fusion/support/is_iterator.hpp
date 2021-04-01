/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_IS_ITERATOR_05062005_1219)
#define FUSION_IS_ITERATOR_05062005_1219

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_base_of.hpp>

namespace boost { namespace fusion
{
    struct iterator_root;

    template <typename T>
    struct is_fusion_iterator : is_base_of<iterator_root, T> {};
}}

#endif

/* is_iterator.hpp
8a8TBVVUx5zw0BjSwdpMdW4N1zijbYOsL/F76T1x14IKWDq/17fnY4KxMrsaZSSHVKZ6/qoIHn0DuIrYDwLd+Ba2YOsGwuNRDPqLaWfZjJdWZcLSWbFg9+Htiu04ucZ5Q19Rc4QlBuKKW3g47gq6JrDvaoEaBWRaIMgXa6Gfkte7ZvPkqNw6YBiMxgbGHjVJ2umjpjfCp7f+WCciLyAbf6NxmTSMc2MVgS9gNgCNGCWjbo9evyn1yyPJ6H8n98poaoth9vuesyXClJ3j1ZnQec5Gkk5VwvpPSqfoAthvbKvJP2Pf/gwRd8i+ORR10uw27mamxPYBlrMI/JzwSDuw/V8Lau8oQcK3vtdpilvQhjbuY4UmefK31AKU5qK8BoXjzH9VmyJmDQeMcpO/gvM06TYcz/C41vFlc7KJ3wYESLbOzNjaC4kOFSvsuCxnUhOxU9k7dp9BdS6FgE8qvTJVWLtRGQJXiq4hFdRODLQSygkGsR59+grkAQp3gBnQFq/hDm59ylZyprpo82hVc6m23hUAuXQono8anKU+elf/FRLzm3FSGj2OUZMLoA==
*/