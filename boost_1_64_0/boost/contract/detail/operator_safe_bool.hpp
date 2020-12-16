
#ifndef BOOST_CONTRACT_DETAIL_OPERATOR_SAFE_BOOL_HPP_
#define BOOST_CONTRACT_DETAIL_OPERATOR_SAFE_BOOL_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/detail/name.hpp>
#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

// NOTE: This code is inspired by <boost/shared_ptr/detail/operator_bool.hpp>.

/* PRIVATE */

// operator! is redundant, but some compilers need it.
#define BOOST_CONTRACT_OPERATOR_SAFE_BOOL_NOT_(bool_expr) \
    bool operator!() const BOOST_NOEXCEPT { return !(bool_expr); }
    
/* PUBLIC */

#if !defined(BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS) && \
        !defined(BOOST_NO_CXX11_NULLPTR)
    #define BOOST_CONTRACT_DETAIL_OPERATOR_SAFE_BOOL(this_type, bool_expr) \
        explicit operator bool() const BOOST_NOEXCEPT { return (bool_expr); } \
        BOOST_CONTRACT_OPERATOR_SAFE_BOOL_NOT_(bool_expr)
#elif (defined(__SUNPRO_CC) && BOOST_WORKAROUND(__SUNPRO_CC, < 0x570) ) || \
        defined(__CINT__)
    #define BOOST_CONTRACT_DETAIL_OPERATOR_SAFE_BOOL(this_type, bool_expr) \
        operator bool() const BOOST_NOEXCEPT { return (bool_expr); } \
        BOOST_CONTRACT_OPERATOR_SAFE_BOOL_NOT_(bool_expr)
#elif defined(_MANAGED)
    #define BOOST_CONTRACT_DETAIL_OPERATOR_SAFE_BOOL(this_type, bool_expr) \
        static void BOOST_CONTRACT_DETAIL_NAME1(operator_safe_bool_func)( \
                this_type***) {} \
        typedef void (*BOOST_CONTRACT_DETAIL_NAME1(operator_safe_bool_type))( \
                this_type***); \
        operator BOOST_CONTRACT_DETAIL_NANE(operator_safe_bool_type)() \
                const BOOST_NOEXCEPT { \
            return (bool_expr) ? \
                    &BOOST_CONTRACT_DETAIL_NAME1(operator_safe_bool_func) : 0; \
        } \
        BOOST_CONTRACT_OPERATOR_SAFE_BOOL_NOT_(bool_expr)
#elif (defined(__MWERKS__) && BOOST_WORKAROUND(__MWERKS__, < 0x3200)) || \
        (defined(__GNUC__) && (__GNUC__ * 100 + __GNUC_MINOR__ < 304)) || \
        (defined(__SUNPRO_CC) && BOOST_WORKAROUND(__SUNPRO_CC, <= 0x590))
    #define BOOST_CONTRACT_DETAIL_OPERATOR_SAFE_BOOL(this_type, bool_expr) \
        void BOOST_CONTRACT_DETAIL_NAME1(operator_safe_bool_func)() const {} \
        typedef void (this_type::*BOOST_CONTRACT_DETAIL_NAME1( \
                operator_safe_bool_type))() const; \
        operator BOOST_CONTRACT_DETAIL_NAME1(operator_safe_bool_type)() \
                const BOOST_NOEXCEPT { \
            return (bool_expr) ? &this_type:: \
                    BOOST_CONTRACT_DETAIL_NAME1(operator_safe_bool_func) : 0; \
        } \
        BOOST_CONTRACT_OPERATOR_SAFE_BOOL_NOT_(bool_expr)
#else
    #define BOOST_CONTRACT_DETAIL_OPERATOR_SAFE_BOOL(this_type, bool_expr) \
        void* BOOST_CONTRACT_DETAIL_NAME1(operator_safe_bool_data); \
        typedef void* this_type::*BOOST_CONTRACT_DETAIL_NAME1( \
                operator_safe_bool_type);\
        operator BOOST_CONTRACT_DETAIL_NAME1(operator_safe_bool_type)() \
                const BOOST_NOEXCEPT { \
            return (bool_expr) ? &this_type:: \
                    BOOST_CONTRACT_DETAIL_NAME1(operator_safe_bool_data) : 0; \
        } \
        BOOST_CONTRACT_OPERATOR_SAFE_BOOL_NOT_(bool_expr)
#endif

#endif // #include guard


/* operator_safe_bool.hpp
OzYkrUlVO3Eu5WYH0roH9X5TJy2RKFhwH/N5lB+p80w7Mb0pbfENuiy1uU01qvRsHahyvjEXs5t6Mxw9m6H1rONXe4zfNT3KDw7qi2r4wZLWXfoG7flCTetOqv2qa0qdVZpiVWNPr3/9gxkoKGa/btCOK73sXyyDlo5/7/H77QGopH18J71K7LCrlH0dD3DW3Hrodc9Igz5h1dCHuVXkMZbm3bKj5LEox0k11xZ1H6TQONnuPGevoBOL6mbqkT8hrhB6XV/FsmMy4pJQRSZkC5GuYxM9tE04avrMTpw4NdvYp/x7Xz7c5cs7ZbF5nB1mO2hZnq9UTaMwfNGMrFK2tSeXqDQVu+ro+J1as8n0OtTfRTi3f2gTZOi8XkKnGWu2v0hsjx0uk6tkrvV21vuyi0t8yUU5vonmXKbItdeCLoqepzJPvYx5Sj1JeoaKy/WkPjMuF9XX2cukyqh8m//mvq8+5jNzcx37AHvo+ZF1i9C2QLVX20XLWB3n6GfGOUxdnjokeXAgBBoi/Vi8dpJ1SF6L6Vt1D1Asz+Z5+TieZbl4XW7AMdodihDoXQcJ6XFpyakgJNV06KwA/knU9RZV4XUJ6d37Bsx9Go6e1rpMpakd6IHnei4b5F7LGKDtaZI5B39wHFdVWZvS+6kdHevSz8oeyL0iRUXqbI2BieVpGwMP66UbI54ahpyWjTVxL1u7J/h5ra/WuQNCjSf0UMxRhI6DnsT7ci5T9Fyqe1mN9YnBpJtrYWeFBZ+jbP1daW23itVuCS0vmj6DVZ6OX+jn2vK5a/A5XD5HBp+byecLg88R8rlb8LmjfO4efO4in3sEn3vJ557B52j53Cv4nCSfewefU4WOX+jn4eq5a+B5pHqODDznqecLA88l6rmb8ww+DcYvUiXmEcmQZLSv1CGN4+dIjGLGycJUXCzbfJ5jxsnCVFxslPm8SMfJnOel5JvPT5CfbzyvpD7z+VUzTham4mK9jWcVF+tilN9sxsnC/HGxSON5lxknC/PHxboZz4d0nGwEPNtWnoUxeF5Y3oGDhwweOiQlJoOtVI4lcKnD4xZRMj0ipDz8OXWrMzVBvavkxtmTmanTHd1sfld8mMsGDefZyUvQefxVeSO03r5M12fsR3adobbF5brsFcY6RuoZOl5k3PneVv+f5vpmRpbRjwOuPeDZuu4cXbexZ1jN5S+6PApI1ZWry4/W5dtTvrZu1/HdKEs7qh+qjgw9dolP1A0nuo4xuo5Ogb0QRWiX8b7gvofs4sLAHgcWK0E1UpeWilqk1FZ7Fgqow+sdn+3NKi8vzR9VUe4ri4ryjVcnE4srSrN9MU56VJQ82uj1+fcy+H9HhywZ7aoQptjfItBHDpbRC3//ypTdm0R/bN2fopPoTzFwpJAanD7p55Pq15gQclDdHih5qG5LB/38X+Li+UKeW4hTFD/JvHFyjtnHW6rmOlSeOquh/jUQYQ0URUlXdyTxV55hC2/sr1fP1375XMyzQa/9p0PxCtJCdl/rIuqQtTq4Q9VRw6lFp3VRHJkjgV8WLyp61hIN7PGm7/FvomdsgKd8scXFBb6sIqH53qeNidC871OG15ELIpHxxRwdk+OcK/fvaN6bGIr38nwF7HGskjS+qzeroBy6nEA4QpSL/l11IYZ2ffV4sno9U0T9oz3x8+wkF89WGjwr867UPDtZz3lfzYOVBg/Wl9+Q5zlUD9UdhQavyfF74KGpZmzvvzT+A3aAx2KKKjPL5I5RzWNxxXEFWWVlwTSbtCGDJOuV5mZl+1SGw3PsRXRlqHS5H3GQTwbL/IkqLZw0dcrbSIsw3jczZV60kedU5uRND/RT5xhtC8vJ0zWaeR6fP2A=
*/